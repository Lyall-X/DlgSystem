// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "BossShowUp.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API UBossShowUp: public UDlgNode
{
	GENERATED_BODY()

public:
	UBossShowUp() { OwnerName = TEXT("Boss登场表演"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("Boss登场表演"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int npcid = 0;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int x = 0;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int y = 0;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int z = 0;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    FText cgname;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    bool needwait = false;;
    
    
};
