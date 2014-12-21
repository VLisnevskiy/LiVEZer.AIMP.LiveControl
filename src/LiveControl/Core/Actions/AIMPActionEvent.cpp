/*************************************************************************
*   File        : AIMPActionEvent.cpp
*   Autor       : Vyacheslav Lisnevskyi
*   Created     : 21/12/2014
*   Description :
*************************************************************************/
#include "..\..\stdafx.h"
#include "AIMPActionEvent.h"

namespace LiVEZer {
    namespace AIMP {
        namespace LiveControl {
            namespace Core {
                namespace Actions {
                    using namespace System;
                    using namespace System::Runtime::InteropServices;

                    AIMPActionEvent::AIMPActionEvent()
                    {
                        this->callbackHandler = gcnew AIMPActionEventHandler(this, &AIMPActionEvent::HandleEvent);
                        this->callbackInitialized = false;
                        this->_AIMPActionEventCreated = false;

                        //callBackOnExecute = &OnExecute;
                    }

                    AIMPActionEvent::AIMPActionEvent(AIMPActionEventHandler^ callbackHandler)
                        : AIMPActionEvent()
                    {
                        if (nullptr != callbackHandler)
                        {
                            this->callbackHandler = callbackHandler;
                            this->callbackInitialized = true;
                        }
                    }

                    AIMPActionEvent::~AIMPActionEvent()
                    {
                    }

                    void AIMPActionEvent::HandleEvent(void* data)
                    {
                        if (callbackInitialized)
                        {
                            callbackHandler->Invoke(data);
                        }
                    }

                    AIMPActionEventWrapper* WINAPI AIMPActionEvent::GetAIMPActionEventWrapper()
                    {
                        if (!_AIMPActionEventCreated)
                        {
                            _AIMPActionEventWrapper = new AIMPActionEventWrapper();
                            void* funcPtr = Marshal::GetFunctionPointerForDelegate(callbackHandler)
                                .ToPointer();

                            _AIMPActionEventWrapper->SetEventHandlerPtr(funcPtr);
                        }

                        return _AIMPActionEventWrapper;
                    }

                    void WINAPI AIMPActionEvent::OnExecute(IUnknown* data)
                    {
                        HandleEvent(nullptr);
                    }
                }
            }
        }
    }
}