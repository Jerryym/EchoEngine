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

		//初始化引擎Log
		Echo::EngineLog::InitLogger();
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
