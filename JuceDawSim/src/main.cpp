#include "Daw.h"
#include <iostream>
#include <windows.h> 
#include <stdio.h> 

typedef void(__cdecl* MYPROC)(pul::Daw&);

int main()
{
    pul::Daw daw;


    HINSTANCE hinstLib;
    MYPROC ProcAdd;
    BOOL fFreeResult, fRunTimeLinkSuccess = FALSE;

    // Get a handle to the DLL module.

    hinstLib = LoadLibrary(TEXT("JucePluginSim.dll"));

    // If the handle is valid, try to get the function address.

    if (hinstLib != NULL)
    {


        ProcAdd = (MYPROC)GetProcAddress(hinstLib, "Init");

        // If the function address is valid, call the function.

        if (NULL != ProcAdd)
        {
            std::cout << "dll found...\n";
            fRunTimeLinkSuccess = TRUE;
            //(ProcAdd)(L"Message sent to the DLL function\n");
            ProcAdd(daw);
        }
        // Free the DLL module.

        
    }

    // If unable to call the DLL function, use an alternative.
    if (!fRunTimeLinkSuccess)
        printf("Message printed from executable\n");





    daw.run();

    std::cin.get();

    if (hinstLib != NULL) fFreeResult = FreeLibrary(hinstLib);

    return EXIT_SUCCESS;

}