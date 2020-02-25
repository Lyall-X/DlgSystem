// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "ReduceItem.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API UReduceItem: public UDlgNode
{
	GENERATED_BODY()

public:
	UReduceItem() { OwnerName = TEXT("扣除道具"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("扣除道具"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    FText item;;
    
    
};