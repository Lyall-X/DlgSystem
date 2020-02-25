// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "InteractionAction.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API UInteractionAction: public UDlgNode
{
	GENERATED_BODY()

public:
	UInteractionAction() { OwnerName = TEXT("物件交互"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("物件交互"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int npcid;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int stateid;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int count = 1;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    FText updatetracename;;
    
    
};
