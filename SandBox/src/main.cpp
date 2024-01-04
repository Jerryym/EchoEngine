#include <Nest.h>
#include <NestUI.h>
#include <QMessageBox>
#include <iostream>

int main(int argc, char* argv[])
{
	try
	{
		//创建Application
		Nest::Application App(argc, argv);

		//创建主窗口
		NestUI::MainWindow* mainWindow = NestUI::MainWindow::Create();
		if (mainWindow == nullptr)
		{
			// 抛出异常，以便在 catch 块中处理
			throw std::runtime_error("Failed to create MainWindow");
		}

		//设置应用程序的主窗口
		Nest::Application::SetMainWindow(mainWindow);
		Nest::Application::GetApplication().GetMainWindow()->show();

		return App.exec();
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
