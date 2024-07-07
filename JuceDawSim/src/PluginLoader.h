#pragma once

#include <windows.h> 
#include "Daw.h"


/**
 * @brief RAII class for loading and using audio processor plugin dll's at runtime.
 *        Currently only supporting Windows API.
 */
class PluginLoader
{
public:
    using MYPROC = void(__cdecl*)(pul::Daw&);
    explicit PluginLoader(const wchar_t* dllName, pul::Daw& daw);
    PluginLoader(const PluginLoader&) = delete;
    ~PluginLoader();
    void callFuncOnPlugin(const char* funcName);

private:
    HINSTANCE m_hInstLib{ nullptr };
    pul::Daw& m_Daw;
    bool m_FreeResult{ false };
    bool m_RunTimeLinkSuccess{ false };

};