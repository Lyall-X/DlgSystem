// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "DelayTimeAction.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API UDelayTimeAction : public UDlgNode
{
	GENERATED_BODY()

public:
	UDelayTimeAction() { OwnerName = TEXT("延时"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("延时"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int delay = 0;;
    
    
};

