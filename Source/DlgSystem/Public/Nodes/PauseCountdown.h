// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "PauseCountdown.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API UPauseCountdown: public UDlgNode
{
	GENERATED_BODY()

public:
	UPauseCountdown() { OwnerName = TEXT("计时器暂停"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("计时器暂停"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    FText id;;
    
    
};
