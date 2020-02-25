// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "MoveCamera.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API UMoveCamera: public UDlgNode
{
	GENERATED_BODY()

public:
	UMoveCamera() { OwnerName = TEXT("设置关注镜头"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("设置关注镜头"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    FText pos;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int len;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int npcid;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    FText targetpos;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    FText rotation;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int movetime;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    FText curve;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int staytime;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int servertime;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int textid;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    bool showText;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    bool skipAnimation_permit;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int time1;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int time2;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int time3;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int time4;;
    
    
};
