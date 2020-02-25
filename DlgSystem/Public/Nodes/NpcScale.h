// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "NpcScale.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API UNpcScale: public UDlgNode
{
	GENERATED_BODY()

public:
	UNpcScale() { OwnerName = TEXT("Npc缩放"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("Npc缩放"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int npcid;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int scale;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int time;;
    
    
};
