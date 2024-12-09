#include "SARibbonBar.h"
#include "MainWindow.h"

int main(int argc, char* argv[])
{
	SARibbonBar::initHighDpi();

	NestApp::Application app(argc, argv);
	//获取设备屏幕大小
	QRect screenRect = QGuiApplication::primaryScreen()->availableGeometry();
	NestUI::sWindowProp sProp(screenRect.width(), screenRect.height(), "Echo Engine");
	EchoEditor::MainWindow* pMainWindow = new EchoEditor::MainWindow(sProp);
	app.SetMainWindow(pMainWindow);
	app.Run();

	return app.exec();
}
