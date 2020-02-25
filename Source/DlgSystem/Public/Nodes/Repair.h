// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "Repair.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API URepair: public UDlgNode
{
	GENERATED_BODY()

public:
	URepair() { OwnerName = TEXT("打开修复窗口"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("打开修复窗口"); }
#endif

	
};
