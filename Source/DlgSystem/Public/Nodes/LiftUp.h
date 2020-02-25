// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "LiftUp.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API ULiftUp: public UDlgNode
{
	GENERATED_BODY()

public:
	ULiftUp() { OwnerName = TEXT("搬起"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("搬起"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int npcid = 0;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int mapid = 0;;
    
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
