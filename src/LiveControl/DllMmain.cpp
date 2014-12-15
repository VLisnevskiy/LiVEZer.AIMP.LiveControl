#include "AimpApi\apiPlugin.h"
#include "Core\ApiTestPlugin.h"

namespace LiVEZer {
    namespace AIMP {
        namespace LiveControl {
            HMODULE PluginInstance = 0;

            BOOLEAN WINAPI DllMain(HINSTANCE hDllHandle, DWORD nReason, LPVOID Reserved)
            {
                switch (nReason)
                {
                    case DLL_PROCESS_ATTACH:
                    case DLL_THREAD_ATTACH:
                    case DLL_THREAD_DETACH:
                    case DLL_PROCESS_DETACH:
                    default:
                        PluginInstance = hDllHandle;
                        break;
                }

                return true;
            }

            _declspec(dllexport) HRESULT WINAPI AIMPPluginGetHeader(IAIMPPlugin **Header)
            {
                Core::ApiTestPlugin *Plugin =
                    new Core::ApiTestPlugin(PluginInstance);
                Plugin->AddRef();
                *Header = Plugin;

                return S_OK;
            }
        }
    }
}