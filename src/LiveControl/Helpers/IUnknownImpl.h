#pragma once
#include "..\stdafx.h"

namespace LiVEZer {
    namespace AIMP {
        namespace LiveControl {
            namespace Helpers {
                template <typename T>
                class IUnknownImpl : public T
                {
                    private:
                    ULONG refCount;

                    public:
                    IUnknownImpl() : refCount(0)
                    {
                    };

                    virtual HRESULT WINAPI QueryInterface(REFIID iid, void** object)
                    {
                        if (!object)
                        {
                            return E_INVALIDARG;
                        }

                        *object = nullptr;
                        if (IID_IUnknown == iid)
                        {
                            *object = this;
                            AddRef();
                            return S_OK;
                        }

                        return E_NOINTERFACE;
                    }

                    virtual ULONG WINAPI AddRef()
                    {
                        return InterlockedIncrement(&refCount);
                    }

                    virtual ULONG WINAPI Release()
                    {
                        ULONG currentRefCount = InterlockedDecrement(&refCount);
                        if (currentRefCount == 0)
                        {
                            delete this;
                        }

                        return currentRefCount;
                    }
                };
            }
        }
    }
}