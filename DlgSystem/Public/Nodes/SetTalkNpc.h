// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "SetTalkNpc.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API USetTalkNpc: public UDlgNode
{
	GENERATED_BODY()

public:
	USetTalkNpc() { OwnerName = TEXT("设置对话的NPC"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("设置对话的NPC"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int npcid;;
    
    
};
