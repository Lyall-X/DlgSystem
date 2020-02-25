// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "Story.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API UStory: public UDlgNode
{
	GENERATED_BODY()

public:
	UStory() { OwnerName = TEXT("剧情"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("剧情"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    FText story;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    FText ActorMates;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    FText ActorObjects; ;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int actorid;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    FText cameraid;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    bool openfilter = false;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    bool shownpcinfo = false;;
    
    
};
