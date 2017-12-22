#include "AppFunctions.h"
#include "FunctionError.h"
#include <app_common.h>

std::string Kystsoft::appId()
{
	char* id = nullptr;
	int error = app_get_id(&id);
	if (error != APP_ERROR_NONE)
		throw FunctionError("app_get_id", error);
	std::string appId(id);
	free(id);
	return appId;
}

std::string Kystsoft::appName()
{
	char* name = nullptr;
	int error = app_get_name(&name);
	if (error != APP_ERROR_NONE)
		throw FunctionError("app_get_name", error);
	std::string appName(name);
	free(name);
	return appName;
}

std::string Kystsoft::appVersion()
{
	char* version = nullptr;
	int error = app_get_version(&version);
	if (error != APP_ERROR_NONE)
		throw FunctionError("app_get_version", error);
	std::string appVersion(version);
	free(version);
	return appVersion;
}

std::string Kystsoft::appDataPath()
{
	char* path = app_get_data_path();
	std::string appPath(path);
	free(path);
	return appPath;
}

std::string Kystsoft::appResourcePath()
{
	char* path = app_get_resource_path();
	std::string appPath(path);
	free(path);
	return appPath;
}

std::string Kystsoft::appSharedResourcePath()
{
	char* path = app_get_shared_resource_path();
	std::string appPath(path);
	free(path);
	return appPath;
}
