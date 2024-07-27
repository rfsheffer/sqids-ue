
#pragma once

#include "Modules/ModuleManager.h"

//---------------------------------------------------------------------------------------------------------------------
/**
*/
class FSqidsModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

DECLARE_LOG_CATEGORY_EXTERN(LogSqids, Log, All);
