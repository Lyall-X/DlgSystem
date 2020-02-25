// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "TraceAction.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API UTraceAction : public UDlgNode
{
	GENERATED_BODY()

public:
	UTraceAction() { OwnerName = TEXT("任务追踪"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("任务追踪"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    FText text;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int mapid = 0;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int npcid = 0;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int npcgroupid = 0;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int x = 0;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int y = 0;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int z = 0;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    bool boshow = true;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    FText tracename;;
    
    
};
