// Copyright 2017-2018 Csaba Molnar, Daniel Butum
#pragma once

#include "CoreMinimal.h"

#include "TreeViewHelpers/DlgTreeViewParticipantProperties.h"
#include "TreeViewHelpers/DlgTreeViewVariableProperties.h"


/** Used as a key for the variable property */
class DLGSYSTEM_API FDlgDataDisplayVariableProperties : public FDlgTreeViewVariableProperties
{
	typedef FDlgTreeViewVariableProperties Super;

public:
	FDlgDataDisplayVariableProperties(const TSet<TWeakObjectPtr<const UDlgDialogue>>& InDialogues) : Super(InDialogues) {}
	FDlgDataDisplayVariableProperties(const TSet<TWeakObjectPtr<const UDlgDialogue>>&& InDialogues) : Super(InDialogues) {}
};

/** Used as a key for the Actor in the fast lookup table. */
class DLGSYSTEM_API FDlgDataDisplayActorProperties : public FDlgTreeViewParticipantProperties<FDlgDataDisplayVariableProperties>
{
	typedef FDlgTreeViewParticipantProperties Super;

public:
	FDlgDataDisplayActorProperties(const TSet<TWeakObjectPtr<const UDlgDialogue>>& InDialogues) : Super(InDialogues) {}
	FDlgDataDisplayActorProperties(const TSet<TWeakObjectPtr<const UDlgDialogue>>&& InDialogues) : Super(InDialogues) {}
};
