#include "echopch.h"
#include "MainWindow.h"

#ifdef ECHO_PLATFORM_WINDOWS
	#include "Platform/Windows/MainWindow_Windows.h"
#endif // ECHO_PLATFORM_WINDOWS


namespace Echo {

	Scope<MainWindow> MainWindow::CreateMainWindow(const sWindowProp& prop)
	{
	#ifdef ECHO_PLATFORM_WINDOWS
		return CreateScope<MainWindow_Windows>(prop);
	#else
		ECHO_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
	#endif // ECHO_PLATFORM_WINDOWS
	}

}
