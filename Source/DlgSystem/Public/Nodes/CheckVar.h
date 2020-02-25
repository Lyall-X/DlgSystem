// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "CheckVar.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API UCheckVar: public UDlgNode
{
	GENERATED_BODY()

public:
	UCheckVar() { OwnerName = TEXT("检查任务变量"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("检查任务变量"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int questid;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    FText varname;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    FText var;;
    
    
};

