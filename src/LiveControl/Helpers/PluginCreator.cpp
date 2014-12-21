/*************************************************************************
*   File        : PluginCreator.cpp
*   Autor       : Vyacheslav Lisnevskyi
*   Created     : 15/12/2014
*   Description : Contains implementation of class PluginCreator
*************************************************************************/
#include "..\stdafx.h"
#include "PluginCreator.h"

#include "..\Core\ApiTestPlugin.h"
#include "..\Core\PluginManager.h"

namespace LiVEZer {
    namespace AIMP {
        namespace LiveControl {
            namespace Helpers {
                using namespace System;
                using namespace System::Windows;
                using namespace System::Windows::Forms;

                using namespace Core;

                HMODULE PluginCreator::pluginInstance;

                IAIMPPlugin* PluginCreator::CreatePlugin()
                {
#ifdef _DEBUG
                    MessageBox::Show(
                        "Entry point for DEBUGGING!\nWill be removed after release.",
                        "AIMP Live Control",
                        MessageBoxButtons::OK,
                        MessageBoxIcon::Asterisk);
#endif
                    PluginManager::Instance->Initialize(pluginInstance);
                    IAIMPPlugin* plugin = PluginManager::Instance->GetAimpPlugin();
                    plugin->AddRef();

                    return plugin;
                }

                bool PluginCreator::DllMain(HINSTANCE hDllHandle, DWORD nReason, LPVOID Reserved)
                {
                    switch (nReason)
                    {
                        case DLL_PROCESS_ATTACH:
                        case DLL_THREAD_ATTACH:
                        case DLL_THREAD_DETACH:
                        case DLL_PROCESS_DETACH:
                        default:
                            pluginInstance = hDllHandle;
                            break;
                    }

                    return true;
                }
            }
        }
    }
}