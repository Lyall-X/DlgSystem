// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "HaveBuff.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API UHaveBuff: public UDlgNode
{
	GENERATED_BODY()

public:
	UHaveBuff() { OwnerName = TEXT("是否拥有BUFF"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("是否拥有BUFF"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int buffid;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    FText buffname;;
    
    
};
