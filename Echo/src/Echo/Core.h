#pragma once
#ifdef ECHO_BUILD_DLL
	#define ECHO_API __declspec(dllexport)
#else
	#define ECHO_API __declspec(dllimport)
#endif
