// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "PlayTopDialog.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API UPlayTopDialog: public UDlgNode
{
	GENERATED_BODY()

public:
	UPlayTopDialog() { OwnerName = TEXT("播放头顶文字气泡"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("播放头顶文字气泡"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int npcid;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int talkid;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int lasttime = 3000;;
    
    
};