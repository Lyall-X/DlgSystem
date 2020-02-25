// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "HaveDoneQuest.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API UHaveDoneQuest: public UDlgNode
{
	GENERATED_BODY()

public:
	UHaveDoneQuest() { OwnerName = TEXT("是否完成过任务"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("是否完成过任务"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int questid;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    bool havenotdone;;
    
    
};
