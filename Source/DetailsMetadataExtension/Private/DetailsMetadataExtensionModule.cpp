// Copyright 2020-2023 Solar Storm Interactive

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

#if ENGINE_MAJOR_VERSION > 5 || (ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 1)
private:
    FDelegateHandle GetVariableCustomizationInstanceDelegateHandle;
#endif
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
#if ENGINE_MAJOR_VERSION > 5 || (ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 1)
    GetVariableCustomizationInstanceDelegateHandle = BlueprintEditorModule.RegisterVariableCustomization(
        FProperty::StaticClass(),
        FOnGetVariableCustomizationInstance::CreateStatic(&FVariableMetadataDetailsCustomization::MakeInstance));
#else
    BlueprintEditorModule.RegisterVariableCustomization(FProperty::StaticClass(), FOnGetVariableCustomizationInstance::CreateStatic(&FVariableMetadataDetailsCustomization::MakeInstance));
#endif
}

//--------------------------------------------------------------------------------------------------------------------
/**
*/
void FDetailsMetadataExtensionModule::ShutdownModule()
{
    FBlueprintEditorModule* BlueprintEditorModule = FModuleManager::GetModulePtr<FBlueprintEditorModule>("Kismet");
    if (BlueprintEditorModule)
    {
#if ENGINE_MAJOR_VERSION > 5 || (ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 1)
        BlueprintEditorModule->UnregisterVariableCustomization(FProperty::StaticClass(),
                                                                       GetVariableCustomizationInstanceDelegateHandle);
#else
        BlueprintEditorModule->UnregisterVariableCustomization(FProperty::StaticClass());
#endif
    }
}

#undef LOCTEXT_NAMESPACE
