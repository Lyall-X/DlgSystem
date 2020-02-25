// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "CheckHP.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API UCheckHP: public UDlgNode
{
	GENERATED_BODY()

public:
	UCheckHP() { OwnerName = TEXT("npc血量检测"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("npc血量检测"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int npcid;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int percent;;
    
    
};
