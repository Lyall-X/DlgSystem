// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "Kill.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API UKill: public UDlgNode
{
	GENERATED_BODY()

public:
	UKill() { OwnerName = TEXT("杀怪"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("杀怪"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int npcid = 0;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int npcgroupid = 0;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int count = 1;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    FText updatetracename;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int sign_mapid;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int sign_npcid;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int sign_npcgroupid;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int sign_posx;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int sign_posy;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int sign_posz;;
    
    
};
