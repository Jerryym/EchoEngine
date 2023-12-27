#include <Echo.h>
#include <QMessageBox>
#include <GUI/MainWindow.h>
#include <iostream>

int main(int argc, char* argv[])
{
	try
	{
		//创建Application
		Echo::Application App(argc, argv);

		//创建主窗口
		EchoUI::MainWindow* mainWindow = EchoUI::MainWindow::Create();
		if (mainWindow == nullptr)
		{
			// 抛出异常，以便在 catch 块中处理
			throw std::runtime_error("Failed to create MainWindow");
		}

		//设置应用程序的主窗口
		Echo::Application::SetMainWindow(mainWindow);
		Echo::Application::GetApplication().GetWindow().show();

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
