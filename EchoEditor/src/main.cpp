#include "SARibbonBar.h"
#include "MainWindow.h"

int main(int argc, char* argv[])
{
	SARibbonBar::initHighDpi();

	NestApp::Application app(argc, argv);
	NestUI::sWindowProp sProp(1600, 900, "Echo Engine");
	EchoEditor::MainWindow* pMainWindow = new EchoEditor::MainWindow(sProp);
	app.SetMainWindow(pMainWindow);
	app.Run();

	return app.exec();
}
