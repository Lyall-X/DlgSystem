// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "InteractionState.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API UInteractionState: public UDlgNode
{
	GENERATED_BODY()

public:
	UInteractionState() { OwnerName = TEXT("交互状态"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("交互状态"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int npcid = 0;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int state = 0;;
    
    
};

