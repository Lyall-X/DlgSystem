import os
import re
import sys

filename = "InteractionState.h"
name = "交互状态"
title = '''
        public int npcid = 0;
        public int state = 0;
'''


array_temp = title.splitlines();
array = []
for item in array_temp:
    if ('[' not in item) and item != '':
        array.append(item.split("public", 1)[1].lstrip())
#遍历
propy = ""
propy2 = ""
for item in array:
    propy += '''UPROPERTY(EditAnywhere, Category = DialogueNodeData)
    ''' + item + ''';
    
    '''
    pro_name = item.split(" ")
    propy2 += '''SpeechSequenceDataCategory.AddProperty(PropertyDialogueNode->GetChildHandle(TEXT("''' + pro_name[1] + '''")));
        '''

os.chdir('E:\\UE4Pro\\MyProject3\\Plugins\\h')
portion = os.path.splitext(filename)
with open(filename, "r+", encoding='UTF-8') as f:
    read_data = f.read()
    f.seek(0)
    f.truncate()
    f.write(u'''// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/DlgNode.h"
#include "DlgTextArgument.h"
#include "''' + portion[0] + '''.generated.h"

/**
 * 
 */

UCLASS()
class DLGSYSTEM_API U''' + portion[0] + ''': public UDlgNode
{
	GENERATED_BODY()

public:
	U''' + portion[0] + '''() { OwnerName = TEXT("''' + name + '''"); }


#if WITH_EDITOR
	FString GetNodeTypeString() const override { return TEXT("''' + name + '''"); }
#endif

	''' +  propy + '''
};

	if (GraphNode->IsA<U''' + portion[0] + '''>())
	{
		IDetailCategoryBuilder& SpeechSequenceDataCategory = DetailLayoutBuilder->EditCategory(TEXT("''' + name + '''属性"));
        ''' + propy2 + '''
	}
''')
