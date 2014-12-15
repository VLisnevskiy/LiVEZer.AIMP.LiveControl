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

                    class MenuItemEvent : public IUnknownImpl<IAIMPActionEvent>
                    {
                        public:
                        virtual void WINAPI OnExecute(IUnknown* data);

                        virtual HRESULT WINAPI QueryInterface(REFIID iid, void** object)
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
                    };
                }
            }
        }
    }
}