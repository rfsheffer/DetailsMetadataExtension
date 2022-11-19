// Copyright 2020-2023 Solar Storm Interactive

#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"
#include "UObject/WeakFieldPtr.h"

class IDetailLayoutBuilder;
class IBlueprintEditor;
class UBlueprint;

class FVariableMetadataDetailsCustomization : public IDetailCustomization
{
public:
	/** Makes a new instance of this detail layout class for a specific detail view requesting it */
	static TSharedPtr<IDetailCustomization> MakeInstance(TSharedPtr<IBlueprintEditor> InBlueprintEditor);

	FVariableMetadataDetailsCustomization(TSharedPtr<IBlueprintEditor> InBlueprintEditor, UBlueprint* Blueprint)
		: BlueprintEditorPtr(InBlueprintEditor)
		, BlueprintPtr(Blueprint)
	{}

	// IDetailCustomization interface
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;

	/** The Blueprint editor we are embedded in */
	TWeakPtr<IBlueprintEditor> BlueprintEditorPtr;

	/** The blueprint we are editing */
	TWeakObjectPtr<UBlueprint> BlueprintPtr;
};
