// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "MovePlayerTo.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API UMovePlayerTo: public UDlgNode
{
	GENERATED_BODY()

public:
	UMovePlayerTo() { OwnerName = TEXT("将玩家瞬移到某地"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("将玩家瞬移到某地"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int mapid;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int x;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int y;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int z;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int dir;;
    
    
};
