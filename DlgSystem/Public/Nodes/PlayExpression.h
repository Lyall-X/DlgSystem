// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "PlayExpression.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API UPlayExpression: public UDlgNode
{
	GENERATED_BODY()

public:
	UPlayExpression() { OwnerName = TEXT("播放人物表情"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("播放人物表情"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int npcid;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    FText name;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int type = 1;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int looptime = 1;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    bool force = false;;
    
    
};
