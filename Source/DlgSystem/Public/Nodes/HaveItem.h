// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "HaveItem.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API UHaveItem: public UDlgNode
{
	GENERATED_BODY()

public:
	UHaveItem() { OwnerName = TEXT("是否拥有道具"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("是否拥有道具"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int itemid;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int number;;
    
    
};
