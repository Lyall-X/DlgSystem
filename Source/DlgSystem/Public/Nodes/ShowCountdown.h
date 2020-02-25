// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "ShowCountdown.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API UShowCountdown: public UDlgNode
{
	GENERATED_BODY()

public:
	UShowCountdown() { OwnerName = TEXT("计时器显示"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("计时器显示"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    FText id;;
    
    
};
