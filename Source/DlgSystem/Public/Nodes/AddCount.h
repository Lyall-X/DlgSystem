// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "AddCount.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API UAddCount: public UDlgNode
{
	GENERATED_BODY()

public:
	UAddCount() { OwnerName = TEXT("计数增加"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("计数增加"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    FText id;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int num;
    
    
};
