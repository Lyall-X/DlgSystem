// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "SetNpcName.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API USetNpcName : public UDlgNode
{
	GENERATED_BODY()

public:
	USetNpcName() { OwnerName = TEXT("修改私有npc名称"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("修改私有npc名称"); }
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
