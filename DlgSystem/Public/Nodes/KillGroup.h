// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "KillGroup.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API UKillGroup: public UDlgNode
{
	GENERATED_BODY()

public:
	UKillGroup() { OwnerName = TEXT("杀怪组"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("杀怪组"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int groupid = 0;;
    
    
};