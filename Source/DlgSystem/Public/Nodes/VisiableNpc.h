// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "VisiableNpc.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API UVisiableNpc: public UDlgNode
{
	GENERATED_BODY()

public:
	UVisiableNpc() { OwnerName = TEXT("设置NPC显示隐藏"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("设置NPC显示隐藏"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int npcid = 0;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int mapid = 0;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    bool show = false;;
    
    
};
