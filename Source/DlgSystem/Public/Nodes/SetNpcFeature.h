// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "SetNpcFeature.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API USetNpcFeature: public UDlgNode
{
	GENERATED_BODY()

public:
	USetNpcFeature() { OwnerName = TEXT("修改npc特性"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("修改npc特性"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int npcid;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int featureid;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    bool isadd = true;;
    
    
};
