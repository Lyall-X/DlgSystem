// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "WeatherControl.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API UWeatherControl: public UDlgNode
{
	GENERATED_BODY()

public:
	UWeatherControl() { OwnerName = TEXT("天气控制"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("天气控制"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int mapid;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int weatherid;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int direction;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int strengthcurveid;;
    
    
};
