/*************************************************************************
*   File        : AIMPActionEventWrapper.h
*   Autor       : Vyacheslav Lisnevskyi
*   Created     : 21/12/2014
*   Description :
*************************************************************************/
#pragma once
#include "..\..\stdafx.h"

#include "..\..\AimpApi\apiActions.h"
#include "..\..\Helpers\IUnknownImpl.h"

namespace LiVEZer {
    namespace AIMP {
        namespace LiveControl {
            namespace Core {
                namespace Actions {
                    using namespace Helpers;

                    typedef void(WINAPI *CallBackOnExecute)(IUnknown* data);

                    class AIMPActionEventWrapper : public IUnknownImpl<IAIMPActionEvent>
                    {
                        private:
                        CallBackOnExecute callBackOnExecute = nullptr;

                        public:
                        void WINAPI OnExecute(IUnknown* data);

                        void WINAPI SetEventHandler(CallBackOnExecute callBackOnExecutePtr);

                        void WINAPI SetEventHandlerPtr(void* callBackOnExecutePtr);

                        HRESULT WINAPI QueryInterface(REFIID iid, void** object);
                    };
                }
            }
        }
    }
}