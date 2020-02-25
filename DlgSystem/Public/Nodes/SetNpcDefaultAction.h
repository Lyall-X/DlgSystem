// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "SetNpcDefaultAction.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API USetNpcDefaultAction: public UDlgNode
{
	GENERATED_BODY()

public:
	USetNpcDefaultAction() { OwnerName = TEXT("设置npc默认待机动作"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("设置npc默认待机动作"); }
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