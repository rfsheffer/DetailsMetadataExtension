// Copyright 2020-2023 Solar Storm Interactive

#include "VariableMetadataDetailsCustomization.h"
#include "Kismet2/BlueprintEditorUtils.h"
//#include "ControlRig.h"
#include "DetailLayoutBuilder.h"
#include "BlueprintEditorModule.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"
#include "Widgets/Text/STextBlock.h"
#include "SlateCore/Public/Widgets/SBoxPanel.h"
#include "Editor/PropertyEditor/Public/PropertyCustomizationHelpers.h"
#include "Widgets/Input/SMultiLineEditableTextBox.h"
#include "Widgets/Input/SEditableTextBox.h"

#define LOCTEXT_NAMESPACE "VariableMetadataDetailsCustomization"

TSharedPtr<IDetailCustomization> FVariableMetadataDetailsCustomization::MakeInstance(TSharedPtr<IBlueprintEditor> InBlueprintEditor)
{
	const TArray<UObject*>* Objects = (InBlueprintEditor.IsValid() ? InBlueprintEditor->GetObjectsCurrentlyBeingEdited() : nullptr);
	if (Objects && Objects->Num() == 1)
	{
		if (UBlueprint* Blueprint = Cast<UBlueprint>((*Objects)[0]))
		{
			return MakeShareable(new FVariableMetadataDetailsCustomization(InBlueprintEditor, Blueprint));
		}
	}

	return nullptr;
}

void FVariableMetadataDetailsCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailLayout)
{
	const FText VariableMetadataEntry = LOCTEXT("VariableMetadataEntry", "Metadata Entry");
	const FText VariableMetadataControl = LOCTEXT("VariableMetadataControl", "Metadata Control");
	const FText VariableMetadataInfo = LOCTEXT("VariableMetadataInfo", "Describes the variables internal metadata");

	// Hide these ones. Might have to add more over time...
	const TSet<FName> NonEditable = {
		TEXT("tooltip"), TEXT("ExposeOnSpawn"), TEXT("MakeEditWidget"), TEXT("BlueprintPrivate"), TEXT("Bitmask"),
		TEXT("BitmaskEnum"), TEXT("MultiLine"), TEXT("DeprecationMessage")
	};

	// Event on add new meta element
	auto OnAddMetadata = [&](FName varName)
	{
		int32 curIndex = 1;
		FString tmp;
		while(FBlueprintEditorUtils::GetBlueprintVariableMetaData(BlueprintPtr.Get(),
																  varName,
																  nullptr,
																  *FString::Printf(TEXT("NewMeta_%d"), curIndex),
																  tmp))
		{
			++curIndex;
		}

		FBlueprintEditorUtils::SetBlueprintVariableMetaData(BlueprintPtr.Get(),
															varName,
															nullptr,
															*FString::Printf(TEXT("NewMeta_%d"), curIndex), 
															TEXT(""));
	};

	// Event on remove meta
	auto OnRemoveMetadata = [&](FName varName, FName metadataKey)
	{
		FBlueprintEditorUtils::RemoveBlueprintVariableMetaData(BlueprintPtr.Get(), varName, nullptr, metadataKey);
	};

	// Event On Meta Key Changed
	auto OnMetaKeyChanged = [&](const FText& newKeyName, ETextCommit::Type changeType, FName varName, FName oldKeyName)
	{
		FString tmp;
		FBlueprintEditorUtils::GetBlueprintVariableMetaData(BlueprintPtr.Get(),
																varName,
																nullptr,
																oldKeyName,
																tmp);

		FBlueprintEditorUtils::RemoveBlueprintVariableMetaData(BlueprintPtr.Get(), varName, nullptr, oldKeyName);

		FBlueprintEditorUtils::SetBlueprintVariableMetaData(BlueprintPtr.Get(),
															varName,
															nullptr,
															*newKeyName.ToString(), 
															tmp);
	};

	// On event Meta Value changed
	auto OnMetaValueChanged = [&](const FText& newName, ETextCommit::Type changeType, FName varName, FName keyName)
	{
		FBlueprintEditorUtils::SetBlueprintVariableMetaData(BlueprintPtr.Get(),
															varName,
															nullptr,
															keyName, 
															newName.ToString());
	};
	
	TArray<TWeakObjectPtr<UObject>> ObjectsBeingCustomized;
	DetailLayout.GetObjectsBeingCustomized(ObjectsBeingCustomized);
	if (ObjectsBeingCustomized.Num() > 0)
	{
		UPropertyWrapper* PropertyWrapper = Cast<UPropertyWrapper>(ObjectsBeingCustomized[0].Get());
		const TWeakFieldPtr<FProperty> PropertyBeingCustomized = PropertyWrapper ? PropertyWrapper->GetProperty() : nullptr;
		if (PropertyBeingCustomized.IsValid())
		{
			const FName varName = PropertyBeingCustomized->GetFName();
			const int32 varIndex = FBlueprintEditorUtils::FindNewVariableIndex(BlueprintPtr.Get(), varName);
            if (varIndex != INDEX_NONE)
            {
	            DetailLayout.EditCategory("Variable")
					.AddCustomRow(VariableMetadataControl, true)
					.NameContent()
					[
						SNew(SHorizontalBox)
						+SHorizontalBox::Slot()
						.HAlign(HAlign_Fill)
						.VAlign(VAlign_Fill)
						[
							SNew(STextBlock)
							.ToolTip(FSlateApplicationBase::Get().MakeToolTip(VariableMetadataInfo))
							.Text(LOCTEXT("VariableMetadataHeader", "Metadata"))
							.Font(IDetailLayoutBuilder::GetDetailFontBold())
						]
						+SHorizontalBox::Slot()
						.AutoWidth()
						.VAlign(VAlign_Fill)
						[
							PropertyCustomizationHelpers::MakeAddButton(FSimpleDelegate::CreateLambda(OnAddMetadata, varName),
																		LOCTEXT("VariableMetadataAdd", "Add"))
						]
					];
			
            	for(const FBPVariableMetaDataEntry& bpMeta : BlueprintPtr->NewVariables[varIndex].MetaDataArray)
            	{
					bool nonEditable = NonEditable.Contains(bpMeta.DataKey);
            		
            		DetailLayout.EditCategory("Variable")
						.AddCustomRow(VariableMetadataEntry, true)
						.NameContent()
						[
							SNew(SEditableTextBox)
							.Text(FText::FromName(bpMeta.DataKey))
							.Font(DetailLayout.GetDetailFont())
							.SelectAllTextWhenFocused( true )
							.ClearKeyboardFocusOnCommit(false)
							.OnTextCommitted(FOnTextCommitted::CreateLambda(OnMetaKeyChanged, varName, bpMeta.DataKey))
							.IsReadOnly(nonEditable)
							.SelectAllTextOnCommit( true )
							.IsPassword(false)
						]
						.ValueContent()
						[
							SNew(SHorizontalBox)
							+SHorizontalBox::Slot()
							.AutoWidth()
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Fill)
							[
								SNew(SMultiLineEditableTextBox)
								.Text(FText::FromString(bpMeta.DataValue))
								.Font(DetailLayout.GetDetailFont())
								.SelectAllTextWhenFocused(false)
								.ClearKeyboardFocusOnCommit(false)
								.OnTextCommitted(FOnTextCommitted::CreateLambda(OnMetaValueChanged, varName, bpMeta.DataKey))
								.SelectAllTextOnCommit(false)
								.IsReadOnly(nonEditable)
								.ModiferKeyForNewLine(EModifierKey::Shift)
								.WrapTextAt(200.0f)
							]
							+SHorizontalBox::Slot()
							.AutoWidth()
							.VAlign(VAlign_Fill)
							[
								PropertyCustomizationHelpers::MakeRemoveButton(FSimpleDelegate::CreateLambda(OnRemoveMetadata, varName, bpMeta.DataKey),
																			   LOCTEXT("VariableMetadataRemove", "Remove"), !nonEditable)
							]
						];
            	}
            }
		}
	}
}

#undef LOCTEXT_NAMESPACE
