// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "ResumeCountdown.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API UResumeCountdown: public UDlgNode
{
	GENERATED_BODY()

public:
	UResumeCountdown() { OwnerName = TEXT("计时器恢复"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("计时器恢复"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    FText id;;
    
    
};
