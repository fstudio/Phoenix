#ifdef PHOENIXAPI_PLUGIN_H
#define PHOENIXAPI_PLUGIN_H


#ifdef _WIN32
#include <windows.h>

#define PHGEXPORT __declspec(dllexport)

#else
#define PHGEXPORT extern
#endif


#define PHO_APISET_MAJOR  1
#define PHO_APISET_MINOR  0
#define PHO_APISET_FIXOR    0
#define PHO_APISET_BULIDOR  0

#define PHO_APISET_STR "Phoenix.Plugins.API.v1"


typedef struct PhoPluginAPIRevision_{
	int major;
	int minor;
	int fixor;
	int buildor;
}PhoPluginAPIRevision;







#endif
