// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "HideCountdown.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API UHideCountdown: public UDlgNode
{
	GENERATED_BODY()

public:
	UHideCountdown() { OwnerName = TEXT("计时器隐藏"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("计时器隐藏"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    FText id;;
    
    
};	