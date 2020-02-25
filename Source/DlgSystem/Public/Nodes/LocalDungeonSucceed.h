// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "LocalDungeonSucceed.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API ULocalDungeonSucceed: public UDlgNode
{
	GENERATED_BODY()

public:
	ULocalDungeonSucceed() { OwnerName = TEXT("通关原地副本"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("通关原地副本"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int copyid;;
    
    
};

