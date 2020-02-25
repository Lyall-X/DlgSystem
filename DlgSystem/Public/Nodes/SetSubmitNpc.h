// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "SetSubmitNpc.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API USetSubmitNpc: public UDlgNode
{
	GENERATED_BODY()

public:
	USetSubmitNpc() { OwnerName = TEXT("设置交任务的NPC"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("设置交任务的NPC"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int npcid;;
    
    
};