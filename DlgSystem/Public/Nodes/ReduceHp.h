// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "ReduceHp.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API UReduceHp: public UDlgNode
{
	GENERATED_BODY()

public:
	UReduceHp() { OwnerName = TEXT("强制扣血"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("强制扣血"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int npcid;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int percent;;
    
    
};
