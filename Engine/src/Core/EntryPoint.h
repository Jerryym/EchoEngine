#pragma once
#include <Nest.h>
#include <NestUI.h>
#include <QMessagebox>

extern Echo::EchoApplication* Echo::CreateApplication(int argc, char** argv);

int main(int argc, char** argv)
{
	try
	{
		//创建Application
		auto app = Echo::CreateApplication(argc, argv);
		auto mainWindow = dynamic_cast<Echo::Windows_MainWindow*>(app->GetMainWindow());
		if (mainWindow == nullptr)
		{
			// 处理异常...
			throw std::runtime_error("Failed to create MainWindow");
		}
		//初始化dockWidgets
		mainWindow->InitializeDockWidgets();
		//初始化GLWidget
		mainWindow->InitializeGLWidget();
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
}
