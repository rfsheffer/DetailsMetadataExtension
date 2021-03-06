// Copyright 2020-2021 Sheffer Online Services. All Rights Reserved.

#include "DetailsMetadataExtensionModule.h"
#include "Modules/ModuleManager.h"
#include "BlueprintEditorModule.h"
#include "VariableMetadataDetailsCustomization.h"

DEFINE_LOG_CATEGORY(LogDetailsMetadataExtension);

#define LOCTEXT_NAMESPACE "DetailsMetadataExtension"

class FDetailsMetadataExtensionModule : public IDetailsMetadataExtensionModule
{
public:
    FDetailsMetadataExtensionModule()
    {
    }

    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};

//////////////////////////////////////////////////////////////////////////

IMPLEMENT_MODULE(FDetailsMetadataExtensionModule, DetailsMetadataExtension);

//////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------------------------------------------------
/**
*/
void FDetailsMetadataExtensionModule::StartupModule()
{
    // Register Blueprint editor variable customization
    FBlueprintEditorModule& BlueprintEditorModule = FModuleManager::LoadModuleChecked<FBlueprintEditorModule>("Kismet");
    BlueprintEditorModule.RegisterVariableCustomization(FProperty::StaticClass(), FOnGetVariableCustomizationInstance::CreateStatic(&FVariableMetadataDetailsCustomization::MakeInstance));
}

//--------------------------------------------------------------------------------------------------------------------
/**
*/
void FDetailsMetadataExtensionModule::ShutdownModule()
{
    FBlueprintEditorModule* BlueprintEditorModule = FModuleManager::GetModulePtr<FBlueprintEditorModule>("Kismet");
    if (BlueprintEditorModule)
    {
        BlueprintEditorModule->UnregisterVariableCustomization(FProperty::StaticClass());
    }
}

#undef LOCTEXT_NAMESPACE
