// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "ShowQuest.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API UShowQuest: public UDlgNode
{
	GENERATED_BODY()

public:
	UShowQuest() { OwnerName = TEXT("显示新增与完成"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("显示新增与完成"); }
#endif

	
};