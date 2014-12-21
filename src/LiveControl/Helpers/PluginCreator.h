/*************************************************************************
*   File        : PluginCreator.h
*   Autor       : Vyacheslav Lisnevskyi
*   Created     : 21/12/2014
*   Description : Contains method to create instance of IAIMPPlugin and
                 method for Dll initialization
*************************************************************************/
#pragma once
#include "..\stdafx.h"

#include "..\AimpApi\apiPlugin.h"

namespace LiVEZer {
    namespace AIMP {
        namespace LiveControl {
            namespace Helpers {
                class PluginCreator
                {
                    private:
                    /*Contains handle on loaded Dll instance*/
                    static HMODULE pluginInstance;

                    public:
                    /*Method that create instance of IAIMPPlugin
                    Return: Instance of IAIMPPlugin*/
                    static IAIMPPlugin* CreatePlugin();

                    /*Method for Dll initialization
                    Return: Results of main initialization TRUE or FALSE*/
                    static bool DllMain(HINSTANCE hDllHandle, DWORD nReason, LPVOID Reserved);
                };
            }
        }
    }
}