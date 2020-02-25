// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "Aside.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API UAside: public UDlgNode
{
	GENERATED_BODY()

public:
	UAside() { OwnerName = TEXT("旁白"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("旁白"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int npcid = 0;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int textid;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int lasttime = 3000;
    
    
};
