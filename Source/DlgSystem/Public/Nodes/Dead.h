// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "Dead.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API UDead: public UDlgNode
{
	GENERATED_BODY()

public:
	UDead() { OwnerName = TEXT("死亡"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("死亡"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int npcid = 0;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int mapid = 0;;
    
    
};

