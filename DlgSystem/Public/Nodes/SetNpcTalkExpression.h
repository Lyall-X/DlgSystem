// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "SetNpcTalkExpression.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API USetNpcTalkExpression: public UDlgNode
{
	GENERATED_BODY()

public:
	USetNpcTalkExpression() { OwnerName = TEXT("设置npc任务中默认谈话表情"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("设置npc任务中默认谈话表情"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int mapid;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int npcid;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    FText valuestr;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    bool isremove = false;;
    
    
};
