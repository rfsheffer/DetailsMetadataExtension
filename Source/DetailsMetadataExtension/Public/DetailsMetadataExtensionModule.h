// Copyright 2020-2021 Sheffer Online Services. All Rights Reserved.

#pragma once

#include "Engine.h"

// Declare an outside visible logging category so generated class code can use the ToLife log category from different modules.
DETAILSMETADATAEXTENSION_API DECLARE_LOG_CATEGORY_EXTERN(LogDetailsMetadataExtension, Log, All);

#define DETAILSMETADATAEXTENSION_MODULE_NAME "DetailsMetadataExtension"

//////////////////////////////////////////////////////////////////////////
// IDetailsMetadataExtensionModule

class IDetailsMetadataExtensionModule : public IModuleInterface
{
public:
    /**
    * Singleton-like access to this module's interface.  This is just for convenience!
    * Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already.
    *
    * @return Returns singleton instance, loading the module on demand if needed
    */
    static FORCEINLINE IDetailsMetadataExtensionModule& Get()
    {
        return FModuleManager::LoadModuleChecked< IDetailsMetadataExtensionModule >(DETAILSMETADATAEXTENSION_MODULE_NAME);
    }

    /**
    * Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true.
    *
    * @return True if the module is loaded and ready to use
    */
    static FORCEINLINE bool IsAvailable()
    {
        return FModuleManager::Get().IsModuleLoaded(DETAILSMETADATAEXTENSION_MODULE_NAME);
    }
};
