/*************************************************************************
*   File        : PluginManager.cpp
*   Autor       : Vyacheslav Lisnevskyi
*   Created     : 15/12/2014
*   Description : Contains implementation of class PluginManager.
*************************************************************************/
#include "..\stdafx.h"
#include "PluginManager.h"

namespace LiVEZer {
    namespace AIMP {
        namespace LiveControl {
            namespace Core {
                using namespace System;
                using namespace System::IO;
                using namespace System::Reflection;
                using namespace System::Threading;

                PluginManager::PluginManager()
                {
                    //TODO: Plugin Manager creation
                    AppDomain::CurrentDomain->AssemblyResolve
                        += gcnew ResolveEventHandler(this, &PluginManager::MyResolveEventHandler);
                    AppDomain::CurrentDomain->UnhandledException
                        += gcnew UnhandledExceptionEventHandler(this, &PluginManager::OnUnhandledException);
                }

                PluginManager::~PluginManager()
                {
                    /*if (isDisposed)
                    {
                        return;
                    }

                    AppDomain::CurrentDomain->AssemblyResolve
                        -= gcnew ResolveEventHandler(this, &PluginManager::MyResolveEventHandler);
                    AppDomain::CurrentDomain->UnhandledException
                        -= gcnew UnhandledExceptionEventHandler(this, &PluginManager::OnUnhandledException);

                    instance = nullptr;
                    isDisposed = true;*/
                }

                void PluginManager::Initialize(HMODULE pluginInstance)
                {
                    this->pluginInstance = pluginInstance;
                }

                Assembly^ PluginManager::MyResolveEventHandler(Object^ sender, ResolveEventArgs^ args)
                {
                    String^ direcory = Path::GetDirectoryName(Assembly::GetExecutingAssembly()->Location);
                    String^ fileName = args->Name->Substring(0, args->Name->IndexOf(","));

                    fileName = Path::Combine(direcory, fileName + ".dll");

                    if (File::Exists(fileName))
                    {
                        Assembly^ assembly = Assembly::LoadFrom(fileName);
                        return assembly;
                    }
                    else
                    {
                        return Assembly::GetExecutingAssembly()->FullName == args->Name
                            ? Assembly::GetExecutingAssembly()
                            : nullptr;
                    }
                }

                void PluginManager::OnUnhandledException(Object^ sender, UnhandledExceptionEventArgs^ e)
                {
                    //:TODO Handle unhandeled exceptions
                    throw gcnew System::NotImplementedException();
                }

                PluginManager^ PluginManager::Instance::get()
                {
                    if (nullptr == instance)
                    {
                        Monitor::Enter(lockInstance);
                        try
                        {
                            if (nullptr == instance)
                            {
                                instance = gcnew PluginManager();
                            }
                        }
                        finally
                        {
                            Monitor::Exit(lockInstance);
                        }
                    }

                    return instance;
                }

                IAIMPPlugin* PluginManager::GetAimpPlugin()
                {
                    if (nullptr == aimpPlugin)
                    {
                        Monitor::Enter(this);
                        try
                        {
                            if (nullptr == aimpPlugin)
                            {
                                aimpPlugin = new ApiTestPlugin(pluginInstance);
                            }
                        }
                        finally
                        {
                            Monitor::Exit(this);
                        }
                    }

                    return aimpPlugin;
                }
            }
        }
    }
}