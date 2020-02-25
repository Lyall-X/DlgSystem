// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "Reward.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API UReward: public UDlgNode
{
	GENERATED_BODY()

public:
	UReward() { OwnerName = TEXT("奖励"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("奖励"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int id = 0;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int count = 1;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    FText text;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    bool dropreward = false;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    bool show = false;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    bool closedialog = false;;
    
    
};

