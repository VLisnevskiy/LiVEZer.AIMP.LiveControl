/*************************************************************************
*   File        : AIMPActionEventWrapper.cpp
*   Autor       : Vyacheslav Lisnevskyi
*   Created     : 21/12/2014
*   Description :
*************************************************************************/
#include "..\..\stdafx.h"
#include "AIMPActionEventWrapper.h"

namespace LiVEZer {
    namespace AIMP {
        namespace LiveControl {
            namespace Core {
                namespace Actions {
                    using namespace System;
                    using namespace System::Windows;
                    using namespace System::Windows::Forms;

                    using namespace Helpers;

                    void WINAPI AIMPActionEventWrapper::OnExecute(IUnknown* data)
                    {
                        try
                        {
                            if (nullptr != callBackOnExecute)
                            {
                                callBackOnExecute(data);
                            }
                        }
                        catch (...)
                        {
                            MessageBox::Show("Action wasn't performed correctly!",
                                "AIMP Live Control",
                                MessageBoxButtons::OK,
                                MessageBoxIcon::Error);
                        }
                    }

                    void WINAPI AIMPActionEventWrapper::SetEventHandler(CallBackOnExecute callBackOnExecutePtr)
                    {
                        if (nullptr != callBackOnExecutePtr && callBackOnExecutePtr > 0)
                        {
                            callBackOnExecute = callBackOnExecutePtr;
                        }
                    }

                    void WINAPI AIMPActionEventWrapper::SetEventHandlerPtr(void* callBackOnExecutePtr)
                    {
                        if (nullptr != callBackOnExecutePtr && callBackOnExecutePtr > 0)
                        {
                            callBackOnExecute = (CallBackOnExecute)callBackOnExecutePtr;
                        }
                    }

                    HRESULT WINAPI AIMPActionEventWrapper::QueryInterface(REFIID iid, void** object)
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