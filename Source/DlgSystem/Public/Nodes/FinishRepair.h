// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "FinishRepair.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API UFinishRepair: public UDlgNode
{
	GENERATED_BODY()

public:
	UFinishRepair() { OwnerName = TEXT("修复任务完成处理事件"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("修复任务完成处理事件"); }
#endif

	
};

