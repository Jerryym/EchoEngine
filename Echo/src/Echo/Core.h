#pragma once

#ifdef ECHO_PLATFORM_WINDOWS
	#ifdef ECHO_BUILD_DLL
		#define ECHO_API __declspec(dllexport)
	#else
		#define ECHO_API __declspec(dllimport)
	#endif // ECHO_BUILD_DLL
#else
	#error Echo only supports Windows!
#endif // ECHO_PLATFORM_WINDOWS
