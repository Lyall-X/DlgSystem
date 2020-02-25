// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "EnterCamera.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API UEnterCamera: public UDlgNode
{
	GENERATED_BODY()

public:
	UEnterCamera() { OwnerName = TEXT("npc进入镜头"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("npc进入镜头"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int npcid;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int delay = 0;;
    
    
};

