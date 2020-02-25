// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "UseSkillCount.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API UUseSkillCount: public UDlgNode
{
	GENERATED_BODY()

public:
	UUseSkillCount() { OwnerName = TEXT("打击次数"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("打击次数"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int npcid = 0;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int skillid = 0;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int count = 0;;
    
    
};