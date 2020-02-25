// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "ShowStar.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API UShowStar: public UDlgNode
{
	GENERATED_BODY()

public:
	UShowStar() { OwnerName = TEXT("提前展示星星"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("提前展示星星"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int mapid = 0;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int npcid = 0;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int dir = 0;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int x = 0;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int y = 0;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int z = 0;;
    
    
};

