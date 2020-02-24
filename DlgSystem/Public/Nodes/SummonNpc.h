// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
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

	static FName GetMemberNameNpcId() { return GET_MEMBER_NAME_CHECKED(USummonNpc, NpcId); }
	static FName GetMemberNameMapID() { return GET_MEMBER_NAME_CHECKED(USummonNpc, MapID); }
	static FName GetMemberNameName() { return GET_MEMBER_NAME_CHECKED(USummonNpc, Name); }

#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("杀怪"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
	int32 NpcId = 0;

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
	int32 MapID = 0;

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
	FText Name;
};
