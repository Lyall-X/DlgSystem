// Copyright 2017-2018 Csaba Molnar, Daniel Butum
#include "DialogueGraphSchema.h"

#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "UObject/UObjectIterator.h"
#include "ScopedTransaction.h"
#include "AssetData.h"
#include "GraphEditorActions.h"

#include "DialogueGraph.h"
#include "DialogueEditor/Nodes/DialogueGraphNode.h"
#include "DialogueEditor/Nodes/DialogueGraphNode_Edge.h"
#include "SchemaActions/NewComment_DialogueGraphSchemaAction.h"
#include "SchemaActions/NewNode_DialogueGraphSchemaAction.h"
#include "SchemaActions/ConvertSpeechNodesToSpeechSequence_DialogueGraphSchemaAction.h"

#define LOCTEXT_NAMESPACE "DlgDialogueGraphSchema"

// Initialize static properties
const FName UDialogueGraphSchema::PIN_CATEGORY_Input(TEXT("ParentInputs"));
const FName UDialogueGraphSchema::PIN_CATEGORY_Output(TEXT("ChildOutputs"));

const FText UDialogueGraphSchema::NODE_CATEGORY_Choice(LOCTEXT("SayAction", "Say (对话)"));
const FText UDialogueGraphSchema::NODE_CATEGORY_Dialogue(LOCTEXT("DialogueNodeAction", "Task Action (行为)"));
const FText UDialogueGraphSchema::NODE_CATEGORY_Graph(LOCTEXT("GraphAction", "节点注释"));
const FText UDialogueGraphSchema::NODE_CATEGORY_Convert(LOCTEXT("NodesConvertAction", "Convert Node(s)"));

TArray<TSubclassOf<UDlgNode>> UDialogueGraphSchema::DialogueNodeClasses;
bool UDialogueGraphSchema::bDialogueNodeClassesInitialized = false;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// UDialogueGraphSchema
void UDialogueGraphSchema::GetPaletteActions(FGraphActionMenuBuilder& ActionMenuBuilder) const
{
	GetAllDialogueNodeActions(ActionMenuBuilder);
	GetCommentAction(ActionMenuBuilder);
}

bool UDialogueGraphSchema::ConnectionCausesLoop(const UEdGraphPin* InputPin, const UEdGraphPin* OutputPin) const
{
	UDialogueGraphNode_Base* InputNode = CastChecked<UDialogueGraphNode_Base>(InputPin->GetOwningNode());
	UDialogueGraphNode_Base* OutputNode = CastChecked<UDialogueGraphNode_Base>(OutputPin->GetOwningNode());

	// Same Node
	if (InputNode == OutputNode)
	{
		return true;
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Begin EdGraphSchema Interface
void UDialogueGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	GetAllDialogueNodeActions(ContextMenuBuilder);
	GetConvertActions(ContextMenuBuilder, ContextMenuBuilder.CurrentGraph);
	GetCommentAction(ContextMenuBuilder, ContextMenuBuilder.CurrentGraph);

	// Menu not from a pin, directly right clicked on the graph canvas
	if (!ContextMenuBuilder.FromPin)
	{
		// TODO paste nodes here
	}
}

void UDialogueGraphSchema::GetContextMenuActions(const UEdGraph* CurrentGraph, const UEdGraphNode* InGraphNode, const UEdGraphPin* InGraphPin, FMenuBuilder* MenuBuilder, bool bIsDebugging) const
{
	if (InGraphNode)
	{
		// Menu for right clicking on node
		MenuBuilder->BeginSection("DialogueGraphSchemaNodeActions", LOCTEXT("NodeActionsMenuHeader", "Node Actions"));
		{
			// This action is handled in UDialogueGraphSchema::BreakNodeLinks, and the action is registered in SGraphEditorImpl (not by us)
			MenuBuilder->AddMenuEntry(FGraphEditorCommands::Get().BreakNodeLinks);
		}
		MenuBuilder->EndSection();
	}

	// The rest of the menus are implemented in the each nodes GetContextMenuActions method
	Super::GetContextMenuActions(CurrentGraph, InGraphNode, InGraphPin, MenuBuilder, bIsDebugging);
}

void UDialogueGraphSchema::CreateDefaultNodesForGraph(UEdGraph& Graph) const
{
	// This should only be called on empty graphs
	check(Graph.Nodes.Num() == 0);
	UDialogueGraph* DialogueGraph = CastChecked<UDialogueGraph>(&Graph);

	// Create, link and position nodes
	DialogueGraph->CreateGraphNodesFromDialogue();
	DialogueGraph->LinkGraphNodesFromDialogue();
	DialogueGraph->AutoPositionGraphNodes();

	// TODO(vampy): Fix editor crash
	//SetNodeMetaData(ResultRootNode, FNodeMetadata::DefaultGraphNode);
}

FPinConnectionResponse UDialogueGraphSchema::MovePinLinks(UEdGraphPin& MoveFromPin, UEdGraphPin& MoveToPin, bool bIsIntermediateMove, bool bNotifyLinkedNodes) const
{
	return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, LOCTEXT("ConnectionMovePinLinks", "Move Pin Links Not implemented"));
}

FPinConnectionResponse UDialogueGraphSchema::CopyPinLinks(UEdGraphPin& CopyFromPin, UEdGraphPin& CopyToPin, bool bIsIntermediateCopy) const
{
	return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, LOCTEXT("ConnectionMovePinLinks", "Copy Pin Links Not implemented"));
}

const FPinConnectionResponse UDialogueGraphSchema::CanCreateConnection(const UEdGraphPin* PinA, const UEdGraphPin* PinB) const
{
	// Make sure the pins are not on the same node
	if (PinA->GetOwningNode() == PinB->GetOwningNode())
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, LOCTEXT("ConnectionSameNode", "Both are on the same node"));
	}

	// Causes loop
	if (ConnectionCausesLoop(PinA, PinB))
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, LOCTEXT("ConnectionLoop", "Connection would cause loop"));
	}

	// Compare the directions
	const UDialogueGraphNode_Base* SourceNode = CastChecked<UDialogueGraphNode_Base>(PinA->GetOwningNode());
	const UDialogueGraphNode_Base* TargetNode = CastChecked<UDialogueGraphNode_Base>(PinB->GetOwningNode());

	// Does the source Node accept output connection?
	if (!SourceNode->CanHaveOutputConnections())
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT("Cannot wire an edge from this node because it does not accept output connection "));
	}

	// Does the targe Node accept input connection?
	if (!TargetNode->CanHaveInputConnections())
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT("Cannot wire an edge to this node because it does not accept input connection "));
	}

	// Only allow one connection from an output (parent node)
	if (SourceNode->HasOutputConnectionToNode(TargetNode))
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, LOCTEXT("ConnectionAlreadyMade", "Connection between nodes already made"));
	}

	const bool bPinAIsEdge = SourceNode->IsA(UDialogueGraphNode_Edge::StaticClass());
	const bool bPinBIsEdge = TargetNode->IsA(UDialogueGraphNode_Edge::StaticClass());
	// Can't connect edges to edges
	if (bPinAIsEdge && bPinBIsEdge)
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT("Cannot wire an edge to an edge"));
	}

	// Handle connection from and Edge to a Node OR Node to an Edge
	// Edges connections are exclusive so we break them
	if (bPinAIsEdge)
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_BREAK_OTHERS_A, TEXT("SHOULD NOT BE VISIBLE"));
	}
	if (bPinBIsEdge)
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_BREAK_OTHERS_B, TEXT("SHOULD NOT BE VISIBLE"));
	}

	// Handle Connection from a Node to a Node
	// Create and Edge by the means of conversion
	if (!bPinAIsEdge && !bPinBIsEdge)
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_MAKE_WITH_CONVERSION_NODE, TEXT("Create an Edge"));
	}

	return FPinConnectionResponse(CONNECT_RESPONSE_MAKE, FText::GetEmpty());
}

bool UDialogueGraphSchema::TryCreateConnection(UEdGraphPin* PinA, UEdGraphPin* PinB) const
{
	// Happens when connecting pin to itself, seems to be a editor bug
	if (PinA->GetOwningNode() == PinB->GetOwningNode())
	{
		return false;
	}

	// Handle the CONNECT_RESPONSE_BREAK_OTHERS, this should handle all cases, because there is only
	// one input pin and that is the only one which will loose it's former parent
	UEdGraphPin* FormerParentOutputPin = nullptr;
	{
		// Usually the InputPin is the PinB
//		const ECanCreateConnectionResponse Response = CanCreateConnection(PinA, PinB).Response;
//		if (Response == CONNECT_RESPONSE_BREAK_OTHERS_B || Response == CONNECT_RESPONSE_BREAK_OTHERS_A)
//		{
//			// Should only happen to edges
//			UEdGraphPin* InputPin = nullptr;
//			UEdGraphPin* OutputPin = nullptr;
//			verify(CategorizePinsByDirection(PinA, PinB, /*out*/ InputPin, /*out*/ OutputPin));
//			check(InputPin->GetOwningNode()->IsA(UDialogueGraphNode_Edge::StaticClass()));
//			FormerParentOutputPin = InputPin->LinkedTo[0];
//		}
	}

	// Mark for undo system, we do not know if there is transaction so just mark without verifying
	// This mostly fixes crashing on undo when there is a drag operation
	UEdGraph* Graph = PinA->GetOwningNode()->GetGraph();
	{
		PinA->GetOwningNode()->Modify();
		PinB->GetOwningNode()->Modify();
		Graph->Modify();
		FDialogueEditorUtilities::GetDialogueForGraph(Graph)->Modify();
	}

	const bool bModified = Super::TryCreateConnection(PinA, PinB);
	if (bModified)
	{
		// Notify former parent
		if (FormerParentOutputPin != nullptr)
		{
			FormerParentOutputPin->GetOwningNode()->PinConnectionListChanged(FormerParentOutputPin);
		}

		UDialogueGraphNode_Base* NodeB = CastChecked<UDialogueGraphNode_Base>(PinB->GetOwningNode());
		// Update the internal structure (recompile of the Dialogue Node/Graph Nodes)
		NodeB->GetDialogue()->CompileDialogueNodesFromGraphNodes();
	}

	// Reset the value
	FDialogueEditorUtilities::SetLastTargetGraphEdgeBeforeDrag(Graph, nullptr);

	return bModified;
}

bool UDialogueGraphSchema::CreateAutomaticConversionNodeAndConnections(UEdGraphPin* PinA, UEdGraphPin* PinB) const
{
	UDialogueGraphNode* NodeA = CastChecked<UDialogueGraphNode>(PinA->GetOwningNode());
	UDialogueGraphNode* NodeB = CastChecked<UDialogueGraphNode>(PinB->GetOwningNode());

	UDialogueGraphNode_Edge* GraphNode_Edge = Graph::SpawnGraphNodeFromTemplate<UDialogueGraphNode_Edge>(NodeA->GetGraph(), FVector2D(0.0f, 0.0f), false);
	// Create proxy connection from output -> input
	if (PinA->Direction == EGPD_Output)
	{
		GraphNode_Edge->CreateConnections(NodeA, NodeB);
	}
	else
	{
		GraphNode_Edge->CreateConnections(NodeB, NodeA);
	}

	// Was this from a modify drag and drop event? copy from the previous node
	UEdGraph* Graph = NodeA->GetGraph();
	if (UDialogueGraphNode_Edge* GraphNode_Edge_DragDop = FDialogueEditorUtilities::GetLastTargetGraphEdgeBeforeDrag(Graph))
	{
		// Copy the data from the old node, without the target index
		FDlgEdge NewEdge = GraphNode_Edge->GetDialogueEdge();
		const int32 NewTargetIndex = NewEdge.TargetIndex;

		NewEdge = GraphNode_Edge_DragDop->GetDialogueEdge();
		NewEdge.TargetIndex = NewTargetIndex;

		// Propagate to Node
		GraphNode_Edge->SetDialogueEdge(NewEdge);
		GraphNode_Edge->PostEditChange();
	}

	return true;
}

bool UDialogueGraphSchema::ShouldHidePinDefaultValue(UEdGraphPin* Pin) const
{
	return true;
}

void UDialogueGraphSchema::BreakNodeLinks(UEdGraphNode& TargetNode) const
{
	// NOTE: The SGraphEditorImpl::BreakNodeLinks that calls this (method) has the transaction declared, so do not make another one here.
	UEdGraph* Graph = TargetNode.GetGraph();
	UDlgDialogue* Dialogue = FDialogueEditorUtilities::GetDialogueForGraph(Graph);

	// Mark for undo system
	verify(Graph->Modify());
	verify(TargetNode.Modify());
	verify(Dialogue->Modify());

	Super::BreakNodeLinks(TargetNode);

#if DO_CHECK
	if (UDialogueGraphNode* GraphNode = Cast<UDialogueGraphNode>(&TargetNode))
	{
		GraphNode->CheckAll();
	}
#endif

	Dialogue->CompileDialogueNodesFromGraphNodes();
}

void UDialogueGraphSchema::BreakPinLinks(UEdGraphPin& TargetPin, bool bSendsNodeNotifcation) const
{
	const FScopedTransaction Transaction(LOCTEXT("GraphEd_BreakPinLinks", "Dialogue Editor: Break Pin Links"));
	UEdGraphNode* Node = TargetPin.GetOwningNode();
	UEdGraph* Graph = Node->GetGraph();
	UDlgDialogue* Dialogue = FDialogueEditorUtilities::GetDialogueForGraph(Graph);

	// Mark for undo system
	verify(Node->Modify());
	verify(Graph->Modify());
	verify(Dialogue->Modify());
	// Modify() is called in BreakLinkTo on the TargetPin

	Super::BreakPinLinks(TargetPin, bSendsNodeNotifcation);

#if DO_CHECK
	if (UDialogueGraphNode* GraphNode = Cast<UDialogueGraphNode>(TargetPin.GetOwningNode()))
	{
		GraphNode->CheckAll();
	}
#endif

	// If this would notify the node then we need to compile the Dialogue
	if (bSendsNodeNotifcation)
	{
		// Recompile
		Dialogue->CompileDialogueNodesFromGraphNodes();
	}
}

void UDialogueGraphSchema::BreakSinglePinLink(UEdGraphPin* SourcePin, UEdGraphPin* TargetPin) const
{
	const FScopedTransaction Transaction(LOCTEXT("GraphEd_BreakSinglePinLink", "Dialogue Editor: Break Pin Link"));
	// Modify() is called in BreakLinkTo
	Super::BreakSinglePinLink(SourcePin, TargetPin);
}

void UDialogueGraphSchema::DroppedAssetsOnGraph(const TArray<FAssetData>& Assets, const FVector2D& GraphPosition, UEdGraph* Graph) const
{

}

void UDialogueGraphSchema::DroppedAssetsOnNode(const TArray<FAssetData>& Assets, const FVector2D& GraphPosition, UEdGraphNode* Node) const
{

}
// End EdGraphSchema Interface
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Begin own functions
void UDialogueGraphSchema::BreakLinkTo(UEdGraphPin* FromPin, UEdGraphPin* ToPin, bool bSendsNodeNotifcation) const
{
	const FScopedTransaction Transaction(LOCTEXT("GraphEd_BreakPinLink", "Dialogue Editor: Break Pin Link"));
	UEdGraphNode* FromNode = FromPin->GetOwningNode();
	UEdGraphNode* ToNode = ToPin->GetOwningNode();
	UEdGraph* Graph = FromNode->GetGraph();
	UDlgDialogue* Dialogue = FDialogueEditorUtilities::GetDialogueForGraph(Graph);

	// Mark for undo system
	verify(FromNode->Modify());
	verify(ToNode->Modify());
	verify(Graph->Modify());
	verify(Dialogue->Modify());

	// Break
	FromPin->BreakLinkTo(ToPin);

	// Notify
	FromNode->PinConnectionListChanged(FromPin);
	ToNode->PinConnectionListChanged(ToPin);
	if (bSendsNodeNotifcation)
	{
		FromNode->NodeConnectionListChanged();
		ToNode->NodeConnectionListChanged();
	}

#if DO_CHECK
	if (UDialogueGraphNode* GraphNode = Cast<UDialogueGraphNode>(FromNode))
	{
		GraphNode->CheckAll();
	}
	if (UDialogueGraphNode* GraphNode = Cast<UDialogueGraphNode>(ToNode))
	{
		GraphNode->CheckAll();
	}
#endif

	// If this would notify the node then we need to Recompile the Dialogue
	if (bSendsNodeNotifcation)
	{
		Dialogue->CompileDialogueNodesFromGraphNodes();
	}
}

void UDialogueGraphSchema::GetCommentAction(FGraphActionMenuBuilder& ActionMenuBuilder, const UEdGraph* CurrentGraph) const
{
	// Do not allow to spawn a comment when we drag are dragging from a selected pin.
	if (ActionMenuBuilder.FromPin)
	{
		return;
	}

	// The rest of the comment actions are in the UEdGraphSchema::GetContextMenuActions
	const bool bIsManyNodesSelected = CurrentGraph ? GetNodeSelectionCount(CurrentGraph) > 0 : false;
	const FText MenuDescription = bIsManyNodesSelected ?
		LOCTEXT("CreateCommentAction", "Create Comment from Selection") : LOCTEXT("AddCommentAction", "Add Comment...");
	const FText ToolTip = LOCTEXT("CreateCommentToolTip", "Creates a comment.");
	constexpr int32 Grouping = 1;

	TSharedPtr<FNewComment_DialogueGraphSchemaAction> NewAction(new FNewComment_DialogueGraphSchemaAction(
		NODE_CATEGORY_Graph, MenuDescription, ToolTip, Grouping));
	ActionMenuBuilder.AddAction(NewAction);
}

void UDialogueGraphSchema::GetConvertActions(FGraphActionMenuBuilder& ActionMenuBuilder, const UEdGraph* CurrentGraph) const
{
	if (ActionMenuBuilder.FromPin || !IsValid(CurrentGraph))
	{
		return;
	}

	const TSet<UObject*> SelectedNodes = FDialogueEditorUtilities::GetSelectedNodes(CurrentGraph);
	int32 Grouping = 1;

	// Try conversion from speech nodes to a sequence node
	{
		TArray<UDialogueGraphNode*> SelectedGraphNodes;
		if (FDialogueEditorUtilities::CanConvertSpeechNodesToSpeechSequence(SelectedNodes, SelectedGraphNodes))
		{
			const FText MenuDescription =
				LOCTEXT("ConvertSpeechNodesToSequenceNodeDesc", "Converts selected Speech node(s) to a Speech Sequence Node");
			const FText ToolTip =
				LOCTEXT("ConvertSpeechNodesToSequenceNodeToolTip", "Converts selected (compresses) linear Speech node(s) to a Speech Sequence Node");

			TSharedPtr<FConvertSpeechNodesToSpeechSequence_DialogueGraphSchemaAction> NewAction(new FConvertSpeechNodesToSpeechSequence_DialogueGraphSchemaAction(
				NODE_CATEGORY_Convert, MenuDescription, ToolTip, Grouping++, SelectedGraphNodes));
			ActionMenuBuilder.AddAction(NewAction);
		}
	}
}

void UDialogueGraphSchema::GetAllDialogueNodeActions(FGraphActionMenuBuilder& ActionMenuBuilder) const
{
	InitDialogueNodeClasses();
	FText ToolTip, MenuDesc;

	// when dragging from an input pin
	//所有节点用统一描述
	// Just right clicked on the empty graph
	ToolTip = LOCTEXT("NewDialogueNodeTooltip", "添加 {Name} 到任务中");
	MenuDesc = LOCTEXT("NewDialogueNodeMenuDescription", "{Name}");


	int32 Grouping = 0;
	FFormatNamedArguments Arguments;

	FFormatNamedArguments Choice_Arguments;

	// Generate menu actions for all the node types
	for (TSubclassOf<UDlgNode> DialogueNodeClass : DialogueNodeClasses)
	{
		const UDlgNode* DialogueNode = DialogueNodeClass->GetDefaultObject<UDlgNode>();
		//普通TaskAction节点
		if (DialogueNode->GetNodeTypeString() != TEXT("对话节点"))
		{
			Arguments.Add(TEXT("Name"), FText::FromString(DialogueNode->GetNodeTypeString()));
			TSharedPtr<FNewNode_DialogueGraphSchemaAction> Action(new FNewNode_DialogueGraphSchemaAction(
				NODE_CATEGORY_Dialogue, FText::Format(MenuDesc, Arguments), FText::Format(ToolTip, Arguments),
				Grouping++, DialogueNodeClass));
			ActionMenuBuilder.AddAction(Action);
		}
		else
		{
			//对话节点
			Choice_Arguments.Add(TEXT("Name"), FText::FromString(DialogueNode->GetNodeTypeString()));
			TSharedPtr<FNewNode_DialogueGraphSchemaAction> Action(new FNewNode_DialogueGraphSchemaAction(
				NODE_CATEGORY_Choice, FText::Format(MenuDesc, Choice_Arguments), FText::Format(ToolTip, Choice_Arguments),
				Grouping++, DialogueNodeClass));
			ActionMenuBuilder.AddAction(Action);
		}

	}

}

void UDialogueGraphSchema::InitDialogueNodeClasses()
{
	if (bDialogueNodeClassesInitialized)
	{
		return;
	}

	// Construct list of non-abstract dialogue node classes.
	for (TObjectIterator<UClass> It; It; ++It)
	{
		if (It->IsChildOf(UDlgNode::StaticClass()) && !It->HasAnyClassFlags(CLASS_Abstract))
		{
			DialogueNodeClasses.Add(*It);
		}
	}

//	DialogueNodeClasses.Sort();
	bDialogueNodeClassesInitialized = true;
}
//~ End own functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#undef LOCTEXT_NAMESPACE
