// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "SetCamp.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API USetCamp: public UDlgNode
{
	GENERATED_BODY()

public:
	USetCamp() { OwnerName = TEXT("设置阵营"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("设置阵营"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int npcid;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int campid;;
    
    
};

