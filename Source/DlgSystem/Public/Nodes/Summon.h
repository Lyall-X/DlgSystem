// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "Summon.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API USummon: public UDlgNode
{
	GENERATED_BODY()

public:
	USummon() { OwnerName = TEXT("召唤npc"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("召唤npc"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int mapid;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int npcid = 0;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int count = 1;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int x = 0;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int y = 0;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int z = 0;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int range = 70;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int dir = 0;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int actionid;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int status = 0;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int level = 0;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    FText name;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int fromid = 0;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    bool ignorenavmesh = false;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    bool playcamera = false;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    FText relatedquest;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int searchrange = 0;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int uniqueid = 0;;
    
    
};

