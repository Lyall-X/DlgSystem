// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "SetNpcDefaultExpression.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API USetNpcDefaultExpression: public UDlgNode
{
	GENERATED_BODY()

public:
	USetNpcDefaultExpression() { OwnerName = TEXT("设置npc默认待机表情"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("设置npc默认待机表情"); }
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
