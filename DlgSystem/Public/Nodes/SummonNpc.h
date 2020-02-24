// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "SummonNpc.generated.h"

/**
 * 
 */
UCLASS()
class DLGSYSTEM_API USummonNpc : public UDlgNode
{
	GENERATED_BODY()

public:
	USummonNpc() { OwnerName = TEXT("杀怪"); }

#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("杀怪"); }
#endif
};
