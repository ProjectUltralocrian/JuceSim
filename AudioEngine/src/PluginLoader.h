#pragma once

#include "PulEngine.h"
#include <windows.h> 


namespace pul {

    /**
     * @brief RAII class for loading and using audio processor plugin dll's at runtime.
     *        Currently only supporting Windows API.
     */
    class PluginLoader
    {
    public:
        using DynLibFunc = void(__cdecl*)(AudioEngine&);
        explicit PluginLoader(const wchar_t* dllName);
        PluginLoader(const wchar_t* dllName, AudioEngine* engine);
        PluginLoader(const PluginLoader&) = delete;
        ~PluginLoader();
        bool callFuncOnPlugin(const char* funcName);
        bool isLoadSuccessful() const noexcept { return m_RunTimeLinkSuccess; }
    private:
        HINSTANCE m_DynLib{ nullptr };
        AudioEngine* m_Engine{ nullptr };
        bool m_FreeResult{ false };
        bool m_RunTimeLinkSuccess{ false };
    };

}