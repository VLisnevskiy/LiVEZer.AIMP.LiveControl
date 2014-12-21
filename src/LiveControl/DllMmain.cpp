#include "stdafx.h"

#include "Helpers\PluginCreator.h"

namespace LiVEZer {
    namespace AIMP {
        namespace LiveControl {
            _declspec(dllexport) BOOLEAN WINAPI DllMain(HINSTANCE hDllHandle, DWORD nReason, LPVOID Reserved)
            {
                return Helpers::PluginCreator::DllMain(hDllHandle, nReason, Reserved);
            }

            _declspec(dllexport) HRESULT WINAPI AIMPPluginGetHeader(IAIMPPlugin **Header)
            {
                *Header = Helpers::PluginCreator::CreatePlugin();
                return S_OK;
            }
        }
    }
}