#include "enginepch.h"
#include "EchoApplication.h"

namespace Echo {
	
	EchoApplication::EchoApplication(int& argc, char** argv)
		: Nest::Application(argc, argv)
	{
		//创建主窗口
		NestUI::sWindowProps props(1600, 900, "Echo Engine");
		//设置应用程序的主窗口
		SetMainWindow(Windows_MainWindow::Create(props));
	}

}
