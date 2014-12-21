/*************************************************************************
*   File        : MenuItemEvent.cpp
*   Autor       : Vyacheslav Lisnevskyi
*   Created     : 15/12/2014
*   Description :
*************************************************************************/
#include "..\..\stdafx.h"
#include "MenuItemEvent.h"

namespace LiVEZer {
    namespace AIMP {
        namespace LiveControl {
            namespace Core {
                namespace Actions {
                    using namespace System;
                    using namespace System::Windows;
                    using namespace System::Windows::Forms;

                    //using namespace Helpers;

                    void WINAPI MenuItemEvent::OnExecute(IUnknown* data)
                    {
                        MessageBox::Show("Action Done", "AIMP Live Control", MessageBoxButtons::OK, MessageBoxIcon::Asterisk);
                    }

                    HRESULT WINAPI MenuItemEvent::QueryInterface(REFIID iid, void** object)
                    {
                        if (!SUCCEEDED(IUnknownImpl<IAIMPActionEvent>::QueryInterface(iid, object)))
                        {
                            if (!object)
                            {
                                return E_INVALIDARG;
                            }

                            *object = nullptr;
                            if (IID_IAIMPActionEvent == iid)
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
                }
            }
        }
    }
}