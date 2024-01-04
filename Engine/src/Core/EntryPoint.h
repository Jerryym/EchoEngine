#pragma once
#include <Nest.h>
#include <NestUI.h>
#include <QMessagebox>

extern Nest::Application* Nest::CreateApplication(int argc, char** argv);

int main(int argc, char** argv)
{
	try
	{
		//创建Application
		auto app = Nest::CreateApplication(argc, argv);
		//创建主窗口
		NestUI::sWindowProps props(1600, 900, "Echo Engine");
		EchoEngine::Windows_MainWindow* mainWindow = EchoEngine::Windows_MainWindow::Create(props);
		if (mainWindow == nullptr)
		{
			// 抛出异常，以便在 catch 块中处理
			throw std::runtime_error("Failed to create MainWindow");
		}
		//设置应用程序的主窗口
		app->SetMainWindow(mainWindow);

		//初始化引擎Log
		EchoEngine::EngineLog::InitLogger();
		ECHOENGINE_CORE_WARN("Initialiazed Log!");
		ECHOENGINE_CLIENT_INFO("Hello Echo Engine!");

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
