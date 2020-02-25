// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "PlayerLevel.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API UPlayerLevel: public UDlgNode
{
	GENERATED_BODY()

public:
	UPlayerLevel() { OwnerName = TEXT("玩家等级"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("玩家等级"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int level;;
    
    
};
