// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "PlayShakeScreen.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API UPlayShakeScreen: public UDlgNode
{
	GENERATED_BODY()

public:
	UPlayShakeScreen() { OwnerName = TEXT("播放震屏"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("播放震屏"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    FText curvename;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    float scale = 1;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int lasttime = 3000;;
    
    
};
