// Copyright 2017-2018 Csaba Molnar, Daniel Butum
#include "DialogueGraphNode_Details.h"

#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"

#include "Nodes/DlgNode.h"
#include "Nodes/DlgNode_SpeechSequence.h"
#include "Nodes/DlgNode_Speech.h"
#include "DialogueEditor/Nodes/DialogueGraphNode.h"
#include "Widgets/SDialogueTextPropertyPickList.h"
#include "Widgets/DialogueTextPropertyPickList_CustomRowHelper.h"
#include "Widgets/DialogueMultiLineEditableTextBox_CustomRowHelper.h"

//新增各种节点
#include "AddCount.h"
#include "AddPartner.h"
#include "AddQuest.h"
#include "Aside.h"
#include "AttackNpcAction.h"
#include "BossShowUp.h"
#include "ChangeNpcStatus.h"
#include "ChangeRepairObjState.h"
#include "CheckHP.h"
#include "CheckVar.h"
#include "CountNum.h"
#include "Countdown.h"
#include "Dead.h"
#include "DelayTimeAction.h"
#include "DeleteNpcAction.h"
#include "DeleteQuest.h"
#include "EnterCamera.h"
#include "EquipAction.h"
#include "FinishRepair.h"
#include "GetItemAction.h"
#include "HaveBuff.h"
#include "HaveDoneQuest.h"
#include "HaveItem.h"
#include "HaveQuest.h"
#include "HideCountdown.h"
#include "InteractionAction.h"
#include "InteractionCount.h"
#include "InteractionState.h"
#include "Kill.h"
#include "KillGroup.h"
#include "PlayerLevel.h"
#include "LiftUp.h"
#include "LocalDungeon.h"
#include "LocalDungeonSucceed.h"
#include "MoveCamera.h"
#include "MovePlayerTo.h"
#include "MovetoAction.h"
#include "MoveToTarget.h"
#include "NpcScale.h"
#include "PauseCountdown.h"
#include "PlayAnime.h"
#include "PlayCG.h"
#include "PlayEffect.h"
#include "PlayExpression.h"
#include "PlayShakeScreen.h"
#include "PlaySound.h"
#include "PlayTopDialog.h"
#include "PosTrigger.h"
#include "ReduceHp.h"
#include "ReduceItem.h"
#include "Repair.h"
#include "ResumeCountdown.h"
#include "Reward.h"
#include "SetBuff.h"
#include "SetCamp.h"
#include "SetDropReward.h"
#include "setFollower.h"
#include "SetNpcDefaultAction.h"
#include "SetNpcDefaultExpression.h"
#include "SetNpcDefaultTalkText.h"
#include "SetNpcFeature.h"
#include "SetNpcHeadBubbleText.h"
#include "SetNpcName.h"
#include "SetNpcTalkAction.h"
#include "SetNpcTalkExpression.h"
#include "SetSubmitNpc.h"
#include "SetTalkNpc.h"
#include "ShowBubble.h"
#include "ShowCountdown.h"
#include "ShowQuest.h"
#include "ShowStar.h"
#include "ShowStarGuide.h"
#include "SocketShow.h"
#include "Story.h"
#include "Summon.h"
#include "SummonGroup.h"
#include "TraceAction.h"
#include "TransportArrive.h"
#include "UseSkillCount.h"
#include "VisiableNpc.h"
#include "WeatherControl.h"

#define LOCTEXT_NAMESPACE "DialoguGraphNode_Details"

void FDialogueGraphNode_Details::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	TArray<TWeakObjectPtr<UObject>> ObjectsBeingCustomized;
	DetailBuilder.GetObjectsBeingCustomized(ObjectsBeingCustomized);

	// Only support one object being customized
	if (ObjectsBeingCustomized.Num() != 1)
	{
		return;
	}

	TWeakObjectPtr<UDialogueGraphNode> WeakGraphNode = Cast<UDialogueGraphNode>(ObjectsBeingCustomized[0].Get());
	if (!WeakGraphNode.IsValid())
	{
		return;
	}

	GraphNode = WeakGraphNode.Get();
	if (!IsValid(GraphNode))
	{
		return;
	}

	DetailLayoutBuilder = &DetailBuilder;
	Dialogue = GraphNode->GetDialogue();
	const UDlgNode& DialogueNode = GraphNode->GetDialogueNode();
	const bool bIsRootNode = GraphNode->IsRootNode();
	const bool bIsEndNode = GraphNode->IsEndNode();
	const bool bIsSpeechNode = GraphNode->IsSpeechNode();
	const bool bIsSpeechSequenceNode = GraphNode->IsSpeechSequenceNode();

	// Hide the existing category
	DetailLayoutBuilder->HideCategory(UDialogueGraphNode::StaticClass()->GetFName());

	// Fill with the properties of the DialogueNode
	IDetailCategoryBuilder& BaseDataCategory = DetailLayoutBuilder->EditCategory(TEXT("基础属性"));
	BaseDataCategory.InitiallyCollapsed(false);
	const TSharedPtr<IPropertyHandle> PropertyDialogueNode =
		DetailLayoutBuilder->GetProperty(UDialogueGraphNode::GetMemberNameDialogueNode(), UDialogueGraphNode::StaticClass());

	if (!bIsRootNode)
	{
		// NodeIndex
		BaseDataCategory.AddProperty(UDialogueGraphNode::GetMemberNameNodeIndex(), UDialogueGraphNode::StaticClass());

		// OwnerName
		{
			const TSharedPtr<IPropertyHandle> ParticipantNamePropertyHandle =
				PropertyDialogueNode->GetChildHandle(UDlgNode::GetMemberNameOwnerName());
			FDetailWidgetRow* DetailWidgetRow = &BaseDataCategory.AddCustomRow(LOCTEXT("ParticipantNameSearcKey", "节点名称"));

			ParticipantNamePropertyRow = MakeShared<FDialogueTextPropertyPickList_CustomRowHelper>(DetailWidgetRow, ParticipantNamePropertyHandle);
			ParticipantNamePropertyRow->SetTextPropertyPickListWidget(
				SNew(SDialogueTextPropertyPickList)
				.AvailableSuggestions(this, &Self::GetAllDialoguesParticipantNames)
				.OnTextCommitted(this, &Self::HandleParticipantTextCommitted)
				.HasContextCheckbox(true)
				.IsContextCheckBoxChecked(true)
				.CurrentContextAvailableSuggestions(this, &Self::GetCurrentDialogueParticipantNames)
			)
			.Update();
		}
		BaseDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(UDlgNode::GetMemberNameOwnerTag()));
		//暂时删除的属性  lyyyyyy
		//BaseDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(UDlgNode::GetMemberNameCheckChildrenOnEvaluation()));
		//BaseDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(UDlgNode::GetMemberNameEnterConditions()))
		//	.ShouldAutoExpand(true);
		//BaseDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(UDlgNode::GetMemberNameEnterEvents()))
		//	.ShouldAutoExpand(true);
	}
	if (!bIsEndNode)
	{
		//暂时删除的属性  lyyyyyy
		//BaseDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(UDlgNode::GetMemberNameChildren()))
		//	.ShouldAutoExpand(true);
	}

	// Do nothing
	if (bIsRootNode)
	{
		return;
	}

	// NOTE: be careful here with the child handle names that are common. For example 'Text' so that we do not get the child
	// property from some inner properties
	if (bIsSpeechNode)
	{
		IDetailCategoryBuilder& SpeechCategory = DetailLayoutBuilder->EditCategory(TEXT("Speech Node"));
		SpeechCategory.InitiallyCollapsed(false);

		IsVirtualParentPropertyHandle = PropertyDialogueNode->GetChildHandle(UDlgNode_Speech::GetMemberNameIsVirtualParent());
		IsVirtualParentPropertyHandle->SetOnPropertyValueChanged(FSimpleDelegate::CreateSP(this, &Self::OnIsVirtualParentChanged));
		SpeechCategory.AddProperty(IsVirtualParentPropertyHandle);

		// Text
		{
			TextPropertyHandle = PropertyDialogueNode->GetChildHandle(UDlgNode_Speech::GetMemberNameText());
			FDetailWidgetRow* DetailWidgetRow = &SpeechCategory.AddCustomRow(LOCTEXT("TextSearchKey", "Text"));

			TextPropertyRow = MakeShared<FDialogueMultiLineEditableTextBox_CustomRowHelper>(DetailWidgetRow, TextPropertyHandle);
			TextPropertyRow->SetPropertyUtils(DetailBuilder.GetPropertyUtilities());
			TextPropertyRow->Update();

			TextPropertyRow->OnTextCommittedEvent().AddRaw(this, &Self::HandleTextCommitted);
			TextPropertyRow->OnTextChangedEvent().AddRaw(this, &Self::HandleTextChanged);
		}

		// Text arguments
		SpeechCategory.AddProperty(PropertyDialogueNode->GetChildHandle(UDlgNode_Speech::GetMemberNameTextArguments()))
			.ShouldAutoExpand(true);

		//
		// Data
		//

		IDetailCategoryBuilder& SpeechDataCategory = DetailLayoutBuilder->EditCategory(TEXT("Speech Node Data"));
		SpeechDataCategory.InitiallyCollapsed(false);

		// Speaker State
		{
			const TSharedPtr<IPropertyHandle> SpeakerStatePropertyHandle =
				PropertyDialogueNode->GetChildHandle(UDlgNode_Speech::GetMemberNameSpeakerState());

			FDetailWidgetRow* DetailWidgetRow = &SpeechDataCategory.AddCustomRow(LOCTEXT("SpeakerStateSearchKey", "Speaker State"));

			SpeakerStatePropertyRow = MakeShared<FDialogueTextPropertyPickList_CustomRowHelper>(DetailWidgetRow, SpeakerStatePropertyHandle);
			SpeakerStatePropertyRow->SetTextPropertyPickListWidget(
				SNew(SDialogueTextPropertyPickList)
				.AvailableSuggestions(this, &Self::GetAllDialoguesSpeakerStates)
				.OnTextCommitted(this, &Self::HandleSpeakerStateCommitted)
				.HasContextCheckbox(false)
			)
			.SetVisibility(CREATE_VISIBILITY_CALLBACK_STATIC(&FDialogueDetailsPanelUtils::GetSpeakerStateNodeVisibility))
			.Update();
		}

		// Node Data that can be anything set by the user
		NodeDataPropertyRow = &SpeechDataCategory.AddProperty(
			PropertyDialogueNode->GetChildHandle(UDlgNode_Speech::GetMemberNameNodeData())
		);
		NodeDataPropertyRow->Visibility(CREATE_VISIBILITY_CALLBACK_STATIC(&FDialogueDetailsPanelUtils::GetNodeDataVisibility));
		NodeDataPropertyRow->ShouldAutoExpand(true);

		// SoundWave
		VoiceSoundWavePropertyRow = &SpeechDataCategory.AddProperty(
			PropertyDialogueNode->GetChildHandle(UDlgNode_Speech::GetMemberNameVoiceSoundWave())
		);
		VoiceSoundWavePropertyRow->Visibility(CREATE_VISIBILITY_CALLBACK_STATIC(&FDialogueDetailsPanelUtils::GetVoiceSoundWaveVisibility));

		// DialogueWave
		VoiceDialogueWavePropertyRow =  &SpeechDataCategory.AddProperty(
			PropertyDialogueNode->GetChildHandle(UDlgNode_Speech::GetMemberNameVoiceDialogueWave())
		);
		VoiceDialogueWavePropertyRow->Visibility(CREATE_VISIBILITY_CALLBACK_STATIC(&FDialogueDetailsPanelUtils::GetVoiceDialogueWaveVisibility));

		// Generic Data, can be FMOD sound
		GenericDataPropertyRow = &SpeechDataCategory.AddProperty(
			PropertyDialogueNode->GetChildHandle(UDlgNode_Speech::GetMemberNameGenericData())
		);
		GenericDataPropertyRow->Visibility(CREATE_VISIBILITY_CALLBACK_STATIC(&FDialogueDetailsPanelUtils::GetGenericDataVisibility));
	}
	else if (bIsSpeechSequenceNode)
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("Speech Sequence Node"));
		SpeechSequenceDataCategory.InitiallyCollapsed(false)
			.RestoreExpansionState(true);
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(UDlgNode_SpeechSequence::GetMemberNameSpeechSequence()))
			.ShouldAutoExpand(true);;
	}
	/**************************************************************************************************************************************************/
	if (GraphNode->DialogueNode->IsA<UMultipleChoiceNode>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("对话配置"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("availableTime")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("saySelection")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("npcid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("textid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("cameraid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("showreward")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("closedialog")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("shownpcinfo")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("facenpcid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("actionid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("actiontype")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("actionlooptime")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("forceplayaction")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("expressionname")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("expressiontype")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("expressionlooptime")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("forceplayexpression")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("opendialog")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("forcenpcid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("x")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("y")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("z")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("dir")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("ActorList")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("availableChoices")));
	}
	if (GraphNode->DialogueNode->IsA<UAddCount>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("计数增加属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("npcid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("stateid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("count")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("updatetracename")));

	}
	if (GraphNode->DialogueNode->IsA<UAddPartner>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("添加伙伴到背包并出战属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("partnerid")));

	}
	if (GraphNode->DialogueNode->IsA<UAddQuest>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("接取任务属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("questid")));

	}

	if (GraphNode->DialogueNode->IsA<UAside>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("旁白属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("npcid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("textid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("lasttime")));

	}

	if (GraphNode->DialogueNode->IsA<UAttackNpcAction>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("攻击npc属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("npcid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("npcgroupid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("mapid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("attackcount")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("updatetracename")));

	}

	if (GraphNode->DialogueNode->IsA<UBossShowUp>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("Boss登场表演属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("npcid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("x")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("y")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("z")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("cgname")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("needwait")));

	}

	if (GraphNode->DialogueNode->IsA<UChangeNpcStatus>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("修改npc显示状态属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("mapid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("npcid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("status")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("isremove")));

	}

	if (GraphNode->DialogueNode->IsA<UCheckHP>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("npc血量检测属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("npcid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("percent")));

	}
	if (GraphNode->DialogueNode->IsA<UCheckVar>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("检查任务变量属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("questid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("varname")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("var")));

	}

	if (GraphNode->DialogueNode->IsA<UCountNum>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("计数器属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("id")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("maxcount")));

	}

	if (GraphNode->DialogueNode->IsA<UCountdown>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("计时停止属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("id")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("time")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("show")));

	}
	if (GraphNode->DialogueNode->IsA<UDead>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("死亡属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("npcid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("mapid")));

	}
	if (GraphNode->DialogueNode->IsA<UDelayTimeAction>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("延时属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("delay")));

	}

	if (GraphNode->DialogueNode->IsA<UDeleteNpcAction>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("删除npc属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("npcid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("actionid")));

	}

	if (GraphNode->DialogueNode->IsA<UDeleteQuest>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("删除任务属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("delquestid")));

	}
	if (GraphNode->DialogueNode->IsA<UEnterCamera>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("npc进入镜头属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("npcid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("delay")));

	}
	if (GraphNode->DialogueNode->IsA<UEquipAction>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("穿戴装备属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("equipid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("fighterid")));

	}

	if (GraphNode->DialogueNode->IsA<UFinishRepair>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("修复任务完成处理事件属性"));

	}

	if (GraphNode->DialogueNode->IsA<UGetItemAction>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("获取道具属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("itemid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("itemnum")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("updatetracename")));

	}
	if (GraphNode->DialogueNode->IsA<UHaveBuff>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("是否拥有BUFF属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("buffid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("buffname")));

	}


	if (GraphNode->DialogueNode->IsA<UHaveDoneQuest>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("是否完成过任务属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("questid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("havenotdone")));

	}
	if (GraphNode->DialogueNode->IsA<UHaveItem>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("是否拥有道具属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("itemid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("number")));

	}

	if (GraphNode->DialogueNode->IsA<UHaveQuest>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("是否已接取任务属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("questid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("donothave")));

	}

	if (GraphNode->DialogueNode->IsA<UHideCountdown>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("计时器隐藏属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("id")));

	}


	if (GraphNode->DialogueNode->IsA<UInteractionAction>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("物件交互属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("npcid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("stateid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("count")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("updatetracename")));

	}

	if (GraphNode->DialogueNode->IsA<UInteractionCount>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("交互计数属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("npcid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("count")));

	}
	if (GraphNode->DialogueNode->IsA<UInteractionState>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("交互状态属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("npcid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("state")));

	}

	if (GraphNode->DialogueNode->IsA<UKill>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("杀怪属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("npcid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("npcgroupid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("count")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("updatetracename")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("sign_mapid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("sign_npcid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("sign_npcgroupid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("sign_posx")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("sign_posy")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("sign_posz")));

	}

	if (GraphNode->DialogueNode->IsA<UKillGroup>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("杀怪组属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("groupid")));

	}


	if (GraphNode->DialogueNode->IsA<ULiftUp>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("搬起属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("npcid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("mapid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("sign_mapid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("sign_npcid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("sign_npcgroupid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("sign_posx")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("sign_posy")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("sign_posz")));

	}
	if (GraphNode->DialogueNode->IsA<ULocalDungeon>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("开启原地副本属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("copyid")));

	}

	if (GraphNode->DialogueNode->IsA<ULocalDungeonSucceed>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("通关原地副本属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("copyid")));

	}

	if (GraphNode->DialogueNode->IsA<UMoveCamera>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("设置关注镜头属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("pos")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("len")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("npcid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("targetpos")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("rotation")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("movetime")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("curve")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("staytime")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("servertime")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("textid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("showText")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("skipAnimation_permit")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("time1")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("time2")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("time3")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("time4")));

	}
	///////////////////////////////////////////////
	if (GraphNode->DialogueNode->IsA<UMovePlayerTo>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("将玩家瞬移到某地属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("mapid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("x")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("y")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("z")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("dir")));

	}

	if (GraphNode->DialogueNode->IsA<UMovetoAction>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("引导主角移动属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("mapid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("x")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("y")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("z")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("range")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("updatetracename")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("sign_mapid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("sign_npcid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("sign_npcgroupid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("sign_posx")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("sign_posy")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("sign_posz")));

	}

	if (GraphNode->DialogueNode->IsA<UMoveToTarget>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("控制npc移动属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("mapid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("npcid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("x")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("y")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("z")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("dir")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("arrivecheck")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("arrivedelete")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("isrun")));

	}


	if (GraphNode->DialogueNode->IsA<UNpcScale>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("Npc缩放属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("npcid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("scale")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("time")));

	}

	if (GraphNode->DialogueNode->IsA<UPauseCountdown>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("计时器暂停属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("id")));

	}
	if (GraphNode->IsA<UPlayAnime>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("播放人物动作属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("npcid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("actionid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("actiontype")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("looptime")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("force")));

	}

	if (GraphNode->DialogueNode->IsA<UPlayCG>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("播放CG属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("name")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("npcid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("needwait")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("cameramode")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("adaptiveguid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("x")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("y")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("z")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("fashionnpclist")));

	}

	if (GraphNode->DialogueNode->IsA<UPlayEffect>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("播放特效属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("postype")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("npcid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("x")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("y")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("z")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("effectname")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("attachname")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("looptime")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("dir")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("isstop")));

	}

	if (GraphNode->DialogueNode->IsA<UPlayerLevel>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("玩家等级属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("level")));

	}

	if (GraphNode->DialogueNode->IsA<UPlayExpression>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("播放人物表情属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("npcid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("name")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("type")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("looptime")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("force")));

	}

	if (GraphNode->DialogueNode->IsA<UPlayShakeScreen>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("播放震屏属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("curvename")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("scale")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("lasttime")));

	}


	if (GraphNode->DialogueNode->IsA<UPlaySound>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("播放音效属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("npcid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("x")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("y")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("z")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("soundname")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("looptime")));

	}


	if (GraphNode->DialogueNode->IsA<UPlayTopDialog>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("播放头顶文字气泡属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("npcid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("talkid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("lasttime")));

	}
	if (GraphNode->DialogueNode->IsA<UPosTrigger>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("坐标触发器属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("posAx")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("posAy")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("posBx")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("posBy")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("posCx")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("posCy")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("posDx")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("posDy")));

	}

	if (GraphNode->DialogueNode->IsA<UReduceHp>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("强制扣血属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("npcid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("percent")));

	}

	if (GraphNode->DialogueNode->IsA<UReduceItem>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("扣除道具属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("item")));

	}


	if (GraphNode->DialogueNode->IsA<URepair>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("打开修复窗口属性"));

	}

	if (GraphNode->DialogueNode->IsA<UResumeCountdown>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("计时器恢复属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("id")));

	}
	if (GraphNode->DialogueNode->IsA<UReward>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("奖励属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("id")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("count")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("text")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("dropreward")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("show")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("closedialog")));

	}
	if (GraphNode->DialogueNode->IsA<USetBuff>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("修改buff属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("npcid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("buffid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("isadd")));

	}
	if (GraphNode->DialogueNode->IsA<USetCamp>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("设置阵营属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("npcid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("campid")));

	}

	if (GraphNode->DialogueNode->IsA<USetDropReward>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("设置任务额外掉落奖励属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("mapid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("npcid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("npcgroupid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("rewardid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("clear")));

	}
	if (GraphNode->DialogueNode->IsA<UsetFollower>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("设置跟随伙伴属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("npcid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("followerid")));

	}


	if (GraphNode->DialogueNode->IsA<USetNpcDefaultAction>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("设置npc默认待机动作属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("mapid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("npcid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("value")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("isremove")));

	}

	if (GraphNode->DialogueNode->IsA<USetNpcDefaultExpression>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("设置npc默认待机表情属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("mapid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("npcid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("valuestr")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("isremove")));

	}


	if (GraphNode->DialogueNode->IsA<USetNpcDefaultTalkText>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("设置npc默认对话文字属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("mapid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("npcid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("value")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("isremove")));

	}

	if (GraphNode->DialogueNode->IsA<USetNpcFeature>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("修改npc特性属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("npcid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("featureid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("isadd")));

	}

	if (GraphNode->DialogueNode->IsA<USetNpcHeadBubbleText>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("设置npc头顶气泡文字属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("mapid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("npcid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("value")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("isremove")));

	}
	if (GraphNode->DialogueNode->IsA<USetNpcName>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("修改私有npc名称属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("mapid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("npcid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("valuestr")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("isremove")));

	}

	if (GraphNode->DialogueNode->IsA<USetNpcTalkAction>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("设置npc任务中默认谈话动作属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("mapid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("npcid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("value")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("isremove")));

	}

	if (GraphNode->DialogueNode->IsA<USetNpcTalkExpression>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("设置npc任务中默认谈话表情属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("mapid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("npcid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("valuestr")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("isremove")));

	}


	if (GraphNode->DialogueNode->IsA<USetSubmitNpc>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("设置交任务的NPC属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("npcid")));

	}


	if (GraphNode->DialogueNode->IsA<USetTalkNpc>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("设置对话的NPC属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("npcid")));

	}

	if (GraphNode->DialogueNode->IsA<UShowBubble>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("显示气泡属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("npcid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("name")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("time")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("force")));

	}
	if (GraphNode->DialogueNode->IsA<UShowCountdown>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("计时器显示属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("id")));

	}


	if (GraphNode->DialogueNode->IsA<UShowQuest>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("显示新增与完成属性"));

	}

	if (GraphNode->DialogueNode->IsA<UShowStar>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("提前展示星星属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("mapid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("npcid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("dir")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("x")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("y")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("z")));

	}
	if (GraphNode->DialogueNode->IsA<UShowStarGuide>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("显示星星引导属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("show")));

	}


	if (GraphNode->DialogueNode->IsA<USocketShow>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("交互显示控制器(关联server/interactiveSocket.txt)属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("npcid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("socketid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("hide")));

	}

	if (GraphNode->DialogueNode->IsA<UStory>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("剧情属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("story")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("ActorMates")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("ActorObjects")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("actorid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("cameraid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("openfilter")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("shownpcinfo")));

	}

	if (GraphNode->DialogueNode->IsA<USummon>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("召唤npc属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("mapid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("npcid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("count")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("x")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("y")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("z")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("range")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("dir")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("actionid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("status")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("level")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("name")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("fromid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("ignorenavmesh")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("playcamera")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("relatedquest")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("searchrange")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("uniqueid")));

	}

	if (GraphNode->DialogueNode->IsA<USummonGroup>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("召唤怪物组属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("groupid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("publicGroup")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("x")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("y")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("z")));

	}

	if (GraphNode->DialogueNode->IsA<UTraceAction>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("任务追踪属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("text")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("mapid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("npcid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("npcgroupid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("x")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("y")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("z")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("boshow")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("tracename")));

	}


	if (GraphNode->DialogueNode->IsA<UTransportArrive>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("搬运到达属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("mapid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("npcid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("x")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("y")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("z")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("range")));

	}


	if (GraphNode->DialogueNode->IsA<UUseSkillCount>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("打击次数属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("npcid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("skillid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("count")));

	}

	if (GraphNode->DialogueNode->IsA<UVisiableNpc>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("设置NPC显示隐藏属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("npcid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("mapid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("show")));

	}

	if (GraphNode->DialogueNode->IsA<UWeatherControl>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("天气控制属性"));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("mapid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("weatherid")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("direction")));
		SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("strengthcurveid")));

	}


}

void FDialogueGraphNode_Details::HandleTextCommitted(const FText& InText, ETextCommit::Type CommitInfo)
{
	// Text arguments already handled in node post change properties
}

void FDialogueGraphNode_Details::HandleTextChanged(const FText& InText)
{
	if (GraphNode)
	{
		GraphNode->GetMutableDialogueNode()->RebuildTextArgumentsFromPreview(InText);
	}
}


void FDialogueGraphNode_Details::OnIsVirtualParentChanged()
{
	DetailLayoutBuilder->ForceRefreshDetails();
}

//////////////////////////////////////////////////////////////////////////

#undef LOCTEXT_NAMESPACE
