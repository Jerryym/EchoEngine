#include "echopch.h"
#include "MainWindow.h"
#include <Echo/Application.h>

namespace EchoUI {

	MainWindow::MainWindow(const sWindowProps& props, QWidget* parent)
		: m_Props(props), QMainWindow(parent)
	{
		Initialize();
	}

	MainWindow* MainWindow::Create(const sWindowProps& props)
	{
		auto mainWindow = new MainWindow(props);
		return mainWindow;
	}

	void MainWindow::Initialize()
	{
		//初始化窗口大小
		resize(QSize(m_Props.m_nWidth, m_Props.m_nHeight));
		setWindowTitle(m_Props.m_STitle);
	}

}