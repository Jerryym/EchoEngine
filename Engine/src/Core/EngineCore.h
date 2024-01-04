#pragma once
#if ECHOENGINE_DYNAMIC_LINK
	#ifdef ECHOENGINE_BUILD_DLL
		#define ECHOENGINE_API __declspec(dllexport)
	#else
		#define ECHOENGINE_API __declspec(dllimport)
	#endif // ECHOENGINE_BUILD_DLL
#elif ECHOENGINE_STATIC_LINK
	#define ECHOENGINE_API
#endif // ECHO_DYNAMIC_LINK

