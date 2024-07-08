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
    explicit PluginLoader(const wchar_t* dllName);
    PluginLoader(const wchar_t* dllName, pul::Daw* daw);
    PluginLoader(const PluginLoader&) = delete;
    ~PluginLoader();
    bool callFuncOnPlugin(const char* funcName);
    bool isLoadSuccessful() const noexcept { return m_RunTimeLinkSuccess; }
private:
    HINSTANCE m_hInstLib{ nullptr };
    pul::Daw* m_Daw{ nullptr };
    bool m_FreeResult{ false };
    bool m_RunTimeLinkSuccess{ false };

};