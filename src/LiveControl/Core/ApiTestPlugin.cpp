#include "..\stdafx.h"

#include "..\AimpApi\apiMenu.h"

#include "Actions\MenuItemEvent.h"

#include "ApiTestPlugin.h"
#include "PluginManager.h"

namespace LiVEZer {
    namespace AIMP {
        namespace LiveControl {
            namespace Core {
                using namespace System;
                using namespace System::Windows;
                using namespace System::Windows::Forms;

                using namespace Actions;

                ApiTestPlugin::ApiTestPlugin(HMODULE PluginInstance)
                {
                    pluginInstance = PluginInstance;
                    PluginManager::Instance->SetAimpPlugin(this);
                }

                ApiTestPlugin::~ApiTestPlugin()
                {
                    pluginInstance = nullptr;
                }

                HRESULT WINAPI ApiTestPlugin::Initialize(IAIMPCore* core)
                {
#ifdef _DEBUG
                    MessageBox::Show(
                        "Entry point for DEBUGGING!\nWill be removed after release.",
                        "AIMP Live Control",
                        MessageBoxButtons::OK,
                        MessageBoxIcon::Asterisk);
#endif
                    PluginManager::Instance->Initialize();
                    aimpCore = core;
                    aimpCore->AddRef();

                    try
                    {
                        IAIMPMenuItem* menuItem;
                        if (CreateObject(IID_IAIMPMenuItem, (void**)&menuItem))
                        {
                            IAIMPServiceMenuManager* menuManager;
                            if (SUCCEEDED(aimpCore->QueryInterface(IID_IAIMPServiceMenuManager, (void**)&menuManager)))
                            {
                                IAIMPMenuItem* parentMenuItem;
                                if (SUCCEEDED(menuManager->GetBuiltIn(AIMP_MENUID_PLAYER_MAIN_OPEN, &parentMenuItem)))
                                {
                                    auto menuId = MakeString(L"{db2dcb278-274a-4055-9bc2-01f89558b567}");
                                    auto menuName = MakeString(L"Item");

                                    IUnknown* itemEvent = new MenuItemEvent();
                                    itemEvent->AddRef();

                                    menuItem->SetValueAsObject(AIMP_MENUITEM_PROPID_ID, menuId);
                                    menuItem->SetValueAsObject(AIMP_MENUITEM_PROPID_NAME, menuName);
                                    menuItem->SetValueAsObject(AIMP_MENUITEM_PROPID_PARENT, parentMenuItem);

                                    menuItem->SetValueAsInt32(AIMP_MENUITEM_PROPID_STYLE, AIMP_MENUITEM_STYLE_NORMAL);
                                    menuItem->SetValueAsObject(AIMP_MENUITEM_PROPID_EVENT, itemEvent); // <--- E_INVALIDARG

                                    aimpCore->RegisterExtension(IID_IAIMPServiceMenuManager, menuItem);

                                    itemEvent->Release();
                                    parentMenuItem->Release();
                                    menuName->Release();
                                    menuId->Release();
                                }

                                menuManager->Release();
                            }

                            menuItem->Release();
                        }
                    }
                    catch (System::Exception^ e)
                    {
                    }
                    catch (...)
                    {
                    }

                    return S_OK;
                }

                HRESULT WINAPI ApiTestPlugin::Finalize()
                {
                    aimpCore->Release();
                    aimpCore = nullptr;

                    return S_OK;
                }

                PWCHAR WINAPI ApiTestPlugin::InfoGet(int Index)
                {
                    PWCHAR cResult = NULL;
                    switch (Index)
                    {
                        case AIMP_PLUGIN_INFO_NAME:
                            cResult = L"AIMP Live Control";
                            break;
                        case AIMP_PLUGIN_INFO_AUTHOR:
                            cResult = L"Vyacheslav Lisnevskiy";
                            break;
                        case AIMP_PLUGIN_INFO_SHORT_DESCRIPTION:
                            cResult = L"Allow you to have remote control on AIMP";
                            break;
                        case AIMP_PLUGIN_INFO_FULL_DESCRIPTION:
                            cResult = L"AIMP Live Control allow you:\n- Remotely control yours AIMP;\n- Viewing current track;\n- Viewing current playlist;\n- And other cute features.";
                            break;
                        default:
                            cResult = L"Unknown Index";
                            break;
                    }

                    return cResult;
                }

                DWORD WINAPI ApiTestPlugin::InfoGetCategories()
                {
                    return AIMP_PLUGIN_CATEGORY_ADDONS;
                }

                void WINAPI ApiTestPlugin::SystemNotification(int NotifyID, IUnknown* Data)
                {
                    if (AIMP_SYSTEM_NOTIFICATION_SERVICE_ADDED == NotifyID)
                    {
                        //:TODO
                        //MessageBox(0, L"AIMP_SYSTEM_NOTIFICATION_SERVICE_ADDED", L"SystemNotification", MB_ICONINFORMATION);
                    }
                    else if (AIMP_SYSTEM_NOTIFICATION_SERVICE_REMOVED == NotifyID)
                    {
                        //:TODO
                        //MessageBox(0, L"AIMP_SYSTEM_NOTIFICATION_SERVICE_REMOVED", L"SystemNotification", MB_ICONINFORMATION);
                    }
                }

                void WINAPI ApiTestPlugin::Show(HWND ParentWindow)
                {
                    //MessageBox(ParentWindow, L"Settings dialog was shown right now!", L"Caption", MB_ICONINFORMATION);
                }

                IAIMPCore* ApiTestPlugin::GetAIMPCore()
                {
                    return aimpCore;
                }

                bool ApiTestPlugin::CreateObject(REFIID iid, void** object)
                {
                    return SUCCEEDED(aimpCore->CreateObject(iid, object));
                }

                bool ApiTestPlugin::GetService(REFIID iid, void** service)
                {
                    return SUCCEEDED(aimpCore->QueryInterface(iid, service));
                }

                bool ApiTestPlugin::IsServiceAvailable(IUnknown* provider, REFIID serviceIid)
                {
                    IUnknown* dummyService;
                    if (SUCCEEDED(provider->QueryInterface(serviceIid, (void**)&dummyService)))
                    {
                        dummyService->Release();
                        return true;
                    }

                    return false;
                }

                IAIMPString* ApiTestPlugin::MakeString(PWCHAR strSeq)
                {
                    IAIMPString* string;
                    CreateObject(IID_IAIMPString, (void**)&string);
                    string->SetData(strSeq, wcslen(strSeq));

                    return string;
                }
            }
        }
    }
}