// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "ShowStarGuide.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API UShowStarGuide: public UDlgNode
{
	GENERATED_BODY()

public:
	UShowStarGuide() { OwnerName = TEXT("显示星星引导"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("显示星星引导"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    bool show = false;;
    
    
};
