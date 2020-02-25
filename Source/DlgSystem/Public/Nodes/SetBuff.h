// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "SetBuff.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API USetBuff: public UDlgNode
{
	GENERATED_BODY()

public:
	USetBuff() { OwnerName = TEXT("修改buff"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("修改buff"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int npcid;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int buffid;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    bool isadd = true;;
    
    
};

