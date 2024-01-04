#pragma once
#ifdef NESTUI_BUILD_DLL
	#define NESTUI_API __declspec(dllexport)
#else
	#define NESTUI_API __declspec(dllimport)
#endif // NESTUI_BUILD_DLL
