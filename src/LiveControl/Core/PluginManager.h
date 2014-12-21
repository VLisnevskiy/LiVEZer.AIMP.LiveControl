/*************************************************************************
*   File        : PluginManager.h
*   Autor       : Vyacheslav Lisnevskyi
*   Created     : 15/12/2014
*   Description : Plugin manager.
*************************************************************************/
#pragma once
#include "..\stdafx.h"

#include "..\AimpApi\apiPlugin.h"
#include "ApiTestPlugin.h"

namespace LiVEZer {
    namespace AIMP {
        namespace LiveControl {
            namespace Core {
                using namespace System;
                using namespace System::Reflection;

                /*Plugin Manager*/
                private ref class PluginManager : public MarshalByRefObject
                {
                    private:
                    PluginManager();

                    static Object^ lockInstance = gcnew Object();
                    static PluginManager^ instance;

                    bool isDisposed = false;
                    ApiTestPlugin* aimpPlugin = nullptr;

                    HMODULE pluginInstance;

                    Assembly^ MyResolveEventHandler(Object^ sender, ResolveEventArgs^ args);
                    void OnUnhandledException(System::Object ^sender, System::UnhandledExceptionEventArgs ^e);

                    public:

                    ~PluginManager();

                    /*Single instance of PluginManager*/
                    static property PluginManager^ Instance
                    {
                        PluginManager^ get();
                    }

                    IAIMPPlugin* GetAimpPlugin();

                    void Initialize(HMODULE pluginInstance);
                };
            }
        }
    }
}