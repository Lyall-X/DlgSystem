// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "PlayAnime.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API UPlayAnime: public UDlgNode
{
	GENERATED_BODY()

public:
	UPlayAnime() { OwnerName = TEXT("播放人物动作"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("播放人物动作"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int npcid;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int actionid;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int actiontype = 1;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int looptime = 1;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    bool force = false;;
    
    
};

