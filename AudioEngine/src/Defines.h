#pragma once

#include <signal.h>


#if defined (_MSC_VER) && defined (PUL_DLL_BUILD)
	#define PUL_API __declspec(dllexport) 
#elif defined (_MSC_VER)
	#define PUL_API __declspec(dllimport)
#elif defined (__GNUC__) && defined (PUL_DLL_BUILD)
	#define PUL_API __attribute__((visibility("default")))
#else 
	#define PUL_API
#endif


#if defined _MSC_VER
	#if defined PUL_DEBUG
		#define ASSERT(x) if(!(x)) {__debugbreak();}
	#else 
		#define ASSERT(x)
	#endif
#elif defined (SIGTRAP)
	#if defined PUL_DEBUG
		#define ASSERT(x) if(!(x)) {raise(SIGTRAP);}
	#else
		#define ASSERT(x)
	#endif
#else 
	#define ASSERT(x) if(!(x)) {raise(SIGABRT);}
#endif
