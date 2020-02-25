// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "GetItemAction.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API UGetItemAction: public UDlgNode
{
	GENERATED_BODY()

public:
	UGetItemAction() { OwnerName = TEXT("获取道具"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("获取道具"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int itemid;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int itemnum;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    FText updatetracename;;
    
    
};
