// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "PlayCG.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API UPlayCG: public UDlgNode
{
	GENERATED_BODY()

public:
	UPlayCG() { OwnerName = TEXT("播放CG"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("播放CG"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    FText name;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int npcid = 0;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    bool needwait = false;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int cameramode = 0;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int adaptiveguid = 0;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int x = 0;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int y = 0;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int z = 0;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    FText fashionnpclist;;
    
    
};
