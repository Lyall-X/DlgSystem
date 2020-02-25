// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "SetDropReward.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API USetDropReward: public UDlgNode
{
	GENERATED_BODY()

public:
	USetDropReward() { OwnerName = TEXT("设置任务额外掉落奖励"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("设置任务额外掉落奖励"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int mapid;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int npcid;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int npcgroupid = 0;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int rewardid;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    bool clear = false;;
    
    
};
