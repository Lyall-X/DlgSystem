// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "SetNpcDefaultTalkText.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API USetNpcDefaultTalkText: public UDlgNode
{
	GENERATED_BODY()

public:
	USetNpcDefaultTalkText() { OwnerName = TEXT("设置npc默认对话文字"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("设置npc默认对话文字"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int mapid;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int npcid;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int value;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    bool isremove = false;;
    
    
};