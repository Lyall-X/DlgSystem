// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "MoveToTarget.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API UMoveToTarget: public UDlgNode
{
	GENERATED_BODY()

public:
	UMoveToTarget() { OwnerName = TEXT("控制npc移动"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("控制npc移动"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int mapid;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int npcid;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int x;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int y;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int z;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int dir;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    bool arrivecheck = false;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    bool arrivedelete = false;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    bool isrun = false;;
    
    
};
