#pragma once
#include <QMessagebox>

#include "GUI/Windows_MainWindow.h"

extern Nest::Application* Nest::CreateApplication(int argc, char** argv);

int main(int argc, char** argv)
{
	try
	{
		//创建Application
		auto app = Nest::CreateApplication(argc, argv);
		//创建主窗口
		NestUI::sWindowProps props(1600, 900, "Echo Engine");
		Nest::Windows_MainWindow* pMainWindow = new Nest::Windows_MainWindow(props);
		app->SetMainWindow(pMainWindow);
		//运行应用程序
		app->Run();
		return app->exec();
	}
	catch (const std::exception& e)
	{
		QString SMsg(e.what());
		QMessageBox::warning(0, "EchoEngine", SMsg);
		return 0;
	}
	catch (...)
	{
		QMessageBox::warning(0, "EchoEngine", "未知的异常...");
		return 0;
	}
	return 0;
}
