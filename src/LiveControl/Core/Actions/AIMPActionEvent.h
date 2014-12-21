/*************************************************************************
*   File        : AIMPActionEvent.h
*   Autor       : Vyacheslav Lisnevskyi
*   Created     : 21/12/2014
*   Description :
*************************************************************************/
#pragma once
#include "..\..\stdafx.h"

#include "AIMPActionEventWrapper.h"
#include "..\..\Helpers\IUnknownImpl.h"
#include <vcclr.h>

namespace LiVEZer {
    namespace AIMP {
        namespace LiveControl {
            namespace Core {
                namespace Actions {
                    using namespace System;

                    public delegate void AIMPActionEventHandler(void* data);

                    public ref class AIMPActionEvent abstract
                    {
                        private:
                        AIMPActionEventWrapper* _AIMPActionEventWrapper = nullptr;
                        CallBackOnExecute callBackOnExecute = nullptr;

                        bool _AIMPActionEventCreated = false;
                        bool callbackInitialized = false;
                        AIMPActionEventHandler^ callbackHandler;

                        public:
                        AIMPActionEvent();

                        AIMPActionEvent(AIMPActionEventHandler^ callbackHandler);

                        virtual ~AIMPActionEvent();

                        virtual void HandleEvent(void* data);

                        internal:
                        AIMPActionEventWrapper* WINAPI GetAIMPActionEventWrapper();

                        void WINAPI OnExecute(IUnknown* data);
                    };
                }
            }
        }
    }
}