#pragma once
#ifdef EchoUI_BUILD_DLL
	#define GUI_API __declspec(dllexport)
#else
	#define GUI_API __declspec(dllimport)
#endif // EchoUI_BUILD_DLL
