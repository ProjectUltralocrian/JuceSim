#ifndef JUCE_PLUGIN_H
#define JUCE_PLUGIN_H

#ifdef JUCE_DLL_BUILD
	#define JUCE_DLL __declspec(dllexport) 
#else
	#define JUCE_DLL __declspec(dllimport)
#endif


#endif //JUCE_PLUGIN_H