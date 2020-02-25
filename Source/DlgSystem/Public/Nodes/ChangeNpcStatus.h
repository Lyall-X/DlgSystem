// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "ChangeNpcStatus.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API UChangeNpcStatus: public UDlgNode
{
	GENERATED_BODY()

public:
	UChangeNpcStatus() { OwnerName = TEXT("修改npc显示状态"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("修改npc显示状态"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int mapid;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int npcid;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int status;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    bool isremove;;
    
    
};
