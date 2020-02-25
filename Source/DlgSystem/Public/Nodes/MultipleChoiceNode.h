// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "MultipleChoiceNode.generated.h"

/**
 * 
 */


USTRUCT()
struct DLGSYSTEM_API FDlgChoice
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
		int32 Textid;

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
		FText MetaData;
};

UCLASS()
class DLGSYSTEM_API UMultipleChoiceNode : public UDlgNode
{
	GENERATED_BODY()

public:
	UMultipleChoiceNode() { OwnerName = TEXT("对话节点"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("对话节点"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
	float availableTime = 0;

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
	bool saySelection = false;

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
	int npcid;

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
	int textid;

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
	FText cameraid;

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
	bool showreward = false;

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
	bool closedialog = false;

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
	bool shownpcinfo = false;

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
	int facenpcid;

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
	int actionid;

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
	int actiontype = 1;

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
	int actionlooptime = 1;

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
	bool forceplayaction = false;

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
	FText expressionname;

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
	int expressiontype = 1;

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
	int expressionlooptime = 1;

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
	bool forceplayexpression = false;

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
	bool opendialog = false;

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
	bool forcenpcid = false;

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
	int x = 0;

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
	int y = 0;

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
	int z = 0;

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
	int dir = 0;

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
	//演员列表
	FText ActorList;

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
	TArray<FDlgChoice> availableChoices;
};

