// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "EquipAction.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API UEquipAction: public UDlgNode
{
	GENERATED_BODY()

public:
	UEquipAction() { OwnerName = TEXT("穿戴装备"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("穿戴装备"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int equipid = 0;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int fighterid = 0;;
    
    
};
