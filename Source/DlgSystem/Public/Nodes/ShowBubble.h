// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "ShowBubble.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API UShowBubble: public UDlgNode
{
	GENERATED_BODY()

public:
	UShowBubble() { OwnerName = TEXT("显示气泡"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("显示气泡"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int npcid;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    FText name;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int time = 3000;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    bool force = false;;
    
    
};
