#pragma once
#include "..\stdafx.h"
//#include <vcclr.h>

#include "ApiTestPlugin.h"

namespace LiVEZer {
    namespace AIMP {
        namespace LiveControl {
            namespace Core {
                using namespace System;
                using namespace System::Reflection;

                /*Plugin Manager*/
                public ref class PluginManager : public System::MarshalByRefObject
                {
                    private:
                    PluginManager();

                    bool isDisposed = false;
                    static Object^ lockInstance = gcnew Object();
                    static PluginManager^ instance;

                    ApiTestPlugin* aimpPlugin = nullptr;

                    Assembly^ MyResolveEventHandler(Object^ sender, ResolveEventArgs^ args);
                    void OnUnhandledException(System::Object ^sender, System::UnhandledExceptionEventArgs ^e);

                    public:

                    ~PluginManager();

                    /*Single instance of PluginManager*/
                    static property PluginManager^ Instance
                    {
                        PluginManager^ get();
                    }

                    void SetAimpPlugin(ApiTestPlugin *aimpPlugin);

                    ApiTestPlugin GetAimpPlugin();

                    void Initialize();
                };
            }
        }
    }
}