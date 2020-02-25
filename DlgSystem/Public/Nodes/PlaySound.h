// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "PlaySound.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API UPlaySound: public UDlgNode
{
	GENERATED_BODY()

public:
	UPlaySound() { OwnerName = TEXT("播放音效"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("播放音效"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int npcid;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int x;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int y;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int z;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    FText soundname;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int looptime = 1;;
    
    
};
