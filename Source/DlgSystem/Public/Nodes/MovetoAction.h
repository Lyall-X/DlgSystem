// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "MovetoAction.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API UMovetoAction: public UDlgNode
{
	GENERATED_BODY()

public:
	UMovetoAction() { OwnerName = TEXT("引导主角移动"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("引导主角移动"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int mapid;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int x;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int y;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int z;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int range;;
    
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