// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "DeleteNpcAction.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API UDeleteNpcAction: public UDlgNode
{
	GENERATED_BODY()

public:
	UDeleteNpcAction() { OwnerName = TEXT("删除npc"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("删除npc"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int npcid;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int actionid;;
    
    
};
