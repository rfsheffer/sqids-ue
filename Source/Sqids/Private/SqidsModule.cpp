
#include "SqidsModule.h"

#define LOCTEXT_NAMESPACE "SqidsModule"

//---------------------------------------------------------------------------------------------------------------------
/**
*/
void FSqidsModule::StartupModule()
{
}

//---------------------------------------------------------------------------------------------------------------------
/**
*/
void FSqidsModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSqidsModule, Sqids)
DEFINE_LOG_CATEGORY(LogSqids);
