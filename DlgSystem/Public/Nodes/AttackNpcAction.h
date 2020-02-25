// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "AttackNpcAction.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API UAttackNpcAction: public UDlgNode
{
	GENERATED_BODY()

public:
	UAttackNpcAction() { OwnerName = TEXT("攻击npc"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("攻击npc"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int npcid = 0;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int npcgroupid = 0;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int mapid = 0;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int attackcount = 0;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    FText updatetracename;;
    
    
};
