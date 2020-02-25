// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "SocketShow.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API USocketShow: public UDlgNode
{
	GENERATED_BODY()

public:
	USocketShow() { OwnerName = TEXT("交互显示控制器(关联server/interactiveSocket.txt)"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("交互显示控制器(关联server/interactiveSocket.txt)"); }
#endif

	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int npcid;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    int socketid;;
    
    UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    bool hide = false;;
    
    
};