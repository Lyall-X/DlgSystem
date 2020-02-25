// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "Countdown.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API UCountdown: public UDlgNode
{
	GENERATED_BODY()

public:
	UCountdown() { OwnerName = TEXT("计时停止"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("计时停止"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    FText id;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int time = 0;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    bool show = false;;
    
    
};

