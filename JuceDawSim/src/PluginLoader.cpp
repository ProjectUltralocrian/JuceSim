#include "PluginLoader.h"
#include <iostream>
#include <wchar.h>


PluginLoader::PluginLoader(const wchar_t* dllName, pul::Daw& daw)
#ifdef _MSC_VER
    : m_hInstLib{ LoadLibrary(dllName) }, m_Daw{ daw }
{
    if (!m_hInstLib)
    {
        std::wcerr << "Unable to load " << dllName << std::endl;
    }
    callFuncOnPlugin("AudioProcessorInit");
}
#else 
    : m_Daw{daw}
{
    std::cerr << "Currently only supporting Windows. Unable to load plugin dll's...\n";
}
#endif

PluginLoader::~PluginLoader()
{
    if (m_hInstLib) {
        auto ProcAdd = (MYPROC)GetProcAddress(m_hInstLib, "AudioProcessorFinalise");

        if (ProcAdd)
        {
            std::cout << "Finalising...\n";
            m_RunTimeLinkSuccess = true;
            ProcAdd(m_Daw);
        }
        m_FreeResult = FreeLibrary(m_hInstLib);
    }
}

void PluginLoader::callFuncOnPlugin(const char* funcName)
{

    if (m_hInstLib)
    {
        MYPROC ProcAdd = (MYPROC)GetProcAddress(m_hInstLib, funcName);

        // If the function address is valid, call the function.
        if (ProcAdd)
        {
            m_RunTimeLinkSuccess = true;
            ProcAdd(m_Daw);
        }
    }
    if (!m_RunTimeLinkSuccess) {
        std::cerr << "Unable to call requested function.\n";
    }
}
