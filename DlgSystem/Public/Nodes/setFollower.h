// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "setFollower.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API UsetFollower: public UDlgNode
{
	GENERATED_BODY()

public:
	UsetFollower() { OwnerName = TEXT("设置跟随伙伴"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("设置跟随伙伴"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int npcid;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int followerid;;
    
    
};
