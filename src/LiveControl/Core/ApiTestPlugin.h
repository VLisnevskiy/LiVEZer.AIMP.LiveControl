#pragma once
#include "..\stdafx.h"

#include "..\AimpApi\apiPlugin.h"

#include "..\Helpers\IUnknownImpl.h"

namespace LiVEZer {
    namespace AIMP {
        namespace LiveControl {
            namespace Core {
                using namespace Helpers;

                class IAIMPPluginWithSettings : public IAIMPPlugin, public IAIMPExternalSettingsDialog
                {

                };

                class ApiTestPlugin : public IUnknownImpl<IAIMPPluginWithSettings>
                {
                    private:
                    bool CreateObject(REFIID iid, void** object);

                    bool GetService(REFIID iid, void** service);

                    bool IsServiceAvailable(IUnknown* provider, REFIID serviceIid);

                    IAIMPString* MakeString(PWCHAR strSeq);

                    IAIMPCore* aimpCore;

                    HMODULE pluginInstance;

                    public:
                    ApiTestPlugin(HMODULE PluginInstance);

                    ~ApiTestPlugin();

                    // Information about the plugin
                    /*Get Plugin Info
                    Index:
                    AIMP_PLUGIN_INFO_NAME
                    AIMP_PLUGIN_INFO_AUTHOR
                    AIMP_PLUGIN_INFO_SHORT_DESCRIPTION
                    AIMP_PLUGIN_INFO_FULL_DESCRIPTION */
                    PWCHAR WINAPI InfoGet(int Index);

                    /*Get Plugin category
                    Return:
                    AIMP_PLUGIN_CATEGORY_ADDONS
                    AIMP_PLUGIN_CATEGORY_DECODERS
                    AIMP_PLUGIN_CATEGORY_VISUALS
                    AIMP_PLUGIN_CATEGORY_DSP */
                    DWORD WINAPI InfoGetCategories();

                    //Initialization / Finalization
                    /*Initialize Plugin
                    Core: Link on main program core*/
                    HRESULT WINAPI Initialize(IN IAIMPCore* Core);

                    /*Finalize Plugin*/
                    HRESULT WINAPI Finalize();

                    // System Notifications
                    /*Receive system notification about changes in Aimp
                    NotifyID:
                    AIMP_SYSTEM_NOTIFICATION_SERVICE_ADDED
                    AIMP_SYSTEM_NOTIFICATION_SERVICE_REMOVED
                    Data: Object that changing or was changed. Can br NULL*/
                    void WINAPI SystemNotification(int NotifyID, IUnknown* Data);

                    void WINAPI Show(HWND ParentWindow);

                    IAIMPCore* GetAIMPCore();

                    HRESULT WINAPI QueryInterface(REFIID iid, void** object)
                    {
                        if (!SUCCEEDED(IUnknownImpl<IAIMPPluginWithSettings>::QueryInterface(iid, object)))
                        {
                            if (!object)
                            {
                                return E_INVALIDARG;
                            }

                            *object = nullptr;
                            if (IID_IAIMPExternalSettingsDialog == iid)
                            {
                                *object = this;
                                AddRef();
                                return S_OK;
                            }

                            return E_NOINTERFACE;
                        }
                        else
                        {
                            return S_OK;
                        }
                    }
                };
            }
        }
    }
}