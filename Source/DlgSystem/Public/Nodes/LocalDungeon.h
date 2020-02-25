// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "LocalDungeon.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API ULocalDungeon: public UDlgNode
{
	GENERATED_BODY()

public:
	ULocalDungeon() { OwnerName = TEXT("开启原地副本"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("开启原地副本"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int copyid;;
    
    
};
