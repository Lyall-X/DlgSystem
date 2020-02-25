// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "PosTrigger.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API UPosTrigger: public UDlgNode
{
	GENERATED_BODY()

public:
	UPosTrigger() { OwnerName = TEXT("坐标触发器"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("坐标触发器"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int posAx = 0;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int posAy = 0;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int posBx = 0;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int posBy = 0;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int posCx = 0;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int posCy = 0;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int posDx = 0;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int posDy = 0;;
    
    
};

