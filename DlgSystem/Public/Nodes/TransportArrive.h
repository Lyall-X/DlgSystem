// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "TransportArrive.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API UTransportArrive: public UDlgNode
{
	GENERATED_BODY()

public:
	UTransportArrive() { OwnerName = TEXT("搬运到达"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("搬运到达"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int mapid;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int npcid = 0;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int x;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int y;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int z;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int range;;
    
    
};