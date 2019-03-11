#include "PluginAPI.h"
#include "Types.h"

extern "C" {

EXPORT int CALL gln64RomOpen(void)
{
	api().RomOpen();
	return 1;
}

EXPORT m64p_error CALL gln64PluginGetVersion(
	m64p_plugin_type * _PluginType,
	int * _PluginVersion,
	int * _APIVersion,
	const char ** _PluginNamePtr,
	int * _Capabilities
)
{
	return api().PluginGetVersion(_PluginType, _PluginVersion, _APIVersion, _PluginNamePtr, _Capabilities);
}

EXPORT m64p_error CALL gln64PluginStartup(
	m64p_dynlib_handle CoreLibHandle,
	void *Context,
	void (*DebugCallback)(void *, int, const char *)
)
{
    printf("PluginStartup\n");
	return api().PluginStartup(CoreLibHandle);
}

EXPORT m64p_error CALL gln64PluginShutdown(void)
{
	return api().PluginShutdown();
}

EXPORT void CALL gln64ReadScreen2(void *dest, int *width, int *height, int front)
{
    printf("ReadScreen2\n");
	api().ReadScreen2(dest, width, height, front);
}

EXPORT void CALL gln64SetRenderingCallback(void (*callback)(int))
{
	api().SetRenderingCallback(callback);
}

} // extern "C"
