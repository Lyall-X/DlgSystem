// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "SummonGroup.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API USummonGroup: public UDlgNode
{
	GENERATED_BODY()

public:
	USummonGroup() { OwnerName = TEXT("召唤怪物组"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("召唤怪物组"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int groupid = 0;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    bool publicGroup = false;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int x = 0;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int y = 0;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int z = 0;;
    
    
};