#pragma once
#if ECHOENGINE_DYNAMIC_LINK
	#ifdef ECHOENGINE_BUILD_DLL
		#define ECHO_API __declspec(dllexport)
	#else
		#define ECHO_API __declspec(dllimport)
	#endif // ECHOENGINE_BUILD_DLL
#elif ECHOENGINE_STATIC_LINK
	#define ECHO_API
#endif // ECHOENGINE_DYNAMIC_LINK

