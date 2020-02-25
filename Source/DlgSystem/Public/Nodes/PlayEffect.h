// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "PlayEffect.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API UPlayEffect: public UDlgNode
{
	GENERATED_BODY()

public:
	UPlayEffect() { OwnerName = TEXT("播放特效"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("播放特效"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int postype;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int npcid;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int x;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int y;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int z;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    FText effectname;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    FText attachname;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int looptime;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int dir = 0;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    bool isstop = false;;
    
    
};
