#pragma once



#ifdef PUL_DLL_BUILD
	#define PUL_API __declspec(dllexport) 
#else
	#define PUL_API __declspec(dllimport)
#endif


#ifdef _MSC_VER
	#ifdef _DEBUG
		#define ASSERT(x) if(!(x)) {__debugbreak();}
	#else 
		#define ASSERT
	#endif
#else
	#error "Currently only supporting Windows MSVC builds..."
#endif
