// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "ChangeRepairObjState.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API UChangeRepairObjState: public UDlgNode
{
	GENERATED_BODY()

public:
	UChangeRepairObjState() { OwnerName = TEXT("修改npc显示状态"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("修改npc显示状态"); }
#endif

};
