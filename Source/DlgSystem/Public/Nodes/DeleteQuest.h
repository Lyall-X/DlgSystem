// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "DeleteQuest.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API UDeleteQuest: public UDlgNode
{
	GENERATED_BODY()

public:
	UDeleteQuest() { OwnerName = TEXT("删除任务"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("删除任务"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int delquestid = 0;;
    
    
};
