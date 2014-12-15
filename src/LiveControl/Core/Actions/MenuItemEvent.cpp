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

                    void WINAPI MenuItemEvent::OnExecute(IUnknown* data)
                    {
                        /*SimpleCShaerp::Class1^ c = gcnew SimpleCShaerp::Class1();
                        c->DoSomething();*/

                        //MessageBox(0, L"Action Done", L"Caption", MB_ICONINFORMATION);
                        MessageBox::Show("Action Done", "AIMP Live Control", MessageBoxButtons::OK, MessageBoxIcon::Asterisk);
                    }
                }
            }
        }
    }
}