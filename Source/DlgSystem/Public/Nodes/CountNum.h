// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "CountNum.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API UCountNum : public UDlgNode
{
	GENERATED_BODY()

public:
	UCountNum() { OwnerName = TEXT("计数器"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("计数器"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    FText id;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int maxcount = 0;;
    
    
};
