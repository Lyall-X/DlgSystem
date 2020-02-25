// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "AddPartner.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API UAddPartner: public UDlgNode
{
	GENERATED_BODY()

public:
	UAddPartner() { OwnerName = TEXT("添加伙伴到背包并出战"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("添加伙伴到背包并出战"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int partnerid;
    
    
};

