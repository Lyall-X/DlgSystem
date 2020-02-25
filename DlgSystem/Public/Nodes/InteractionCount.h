// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "InteractionCount.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API UInteractionCount: public UDlgNode
{
	GENERATED_BODY()

public:
	UInteractionCount() { OwnerName = TEXT("交互计数"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("交互计数"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int npcid = 0;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int count = 0;;
    
    
};
