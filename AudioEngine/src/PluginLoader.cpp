#include "PluginLoader.h"
#include <iostream>
#include <wchar.h>

namespace pul {
    PluginLoader::PluginLoader(const wchar_t* dllName)
        : PluginLoader(dllName, nullptr) { }

    PluginLoader::PluginLoader(const wchar_t* dllName, AudioEngine* engine)
#ifdef _MSC_VER
        : m_DynLib{ LoadLibrary(dllName) }, m_Engine{ engine }
    {
        if (!m_DynLib)
        {
            std::wcerr << "Unable to load " << dllName << std::endl;
            return;
        }
        if (!callFuncOnPlugin("AudioProcessorInit"))
        {
            std::cerr << "Unable to initialize plugin.\n";
            return;
        }
    }
#else 
        : m_Engine{ engine }
    {
        std::cerr << "Currently only supporting Windows. Unable to load plugin dll's...\n";
    }
#endif

    PluginLoader::~PluginLoader()
    {
        if (m_DynLib) {
            auto ProcAdd = (DynLibFunc)GetProcAddress(m_DynLib, "AudioProcessorFinalise");

            if (ProcAdd)
            {
                ASSERT(m_Engine != nullptr);
                std::cout << "Finalising...\n";
                ProcAdd(*m_Engine);
            }
            m_FreeResult = FreeLibrary(m_DynLib);
            ASSERT(m_FreeResult);
        }
    }

    bool PluginLoader::callFuncOnPlugin(const char* funcName)
    {
        if (m_DynLib)
        {
            ASSERT(m_Engine != nullptr);
            DynLibFunc ProcAdd = (DynLibFunc)GetProcAddress(m_DynLib, funcName);

            // If the function address is valid, call the function.
            if (ProcAdd)
            {
                m_RunTimeLinkSuccess = true;
                ProcAdd(*m_Engine);
                return true;
            }
            return false;
        }
    }

}