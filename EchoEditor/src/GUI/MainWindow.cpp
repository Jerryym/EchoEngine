#include "pch.h"
#include "MainWindow.h"
#include "ConsoleDock.h"
#include "GLWidget.h"

namespace EchoEditor {

	MainWindow::MainWindow(const NestUI::sWindowProp& sProp, QWidget* parent)
		: NestUI::NestMainWindow(parent)
	{
		m_pDockManager = NestUI::DockWidgetManager::GetDockManager(this);
		Initialize(sProp);
	}

	void MainWindow::SetVSync(bool enabled)
	{
		m_sData.m_bVSync = enabled;
	}

	void MainWindow::Initialize(const NestUI::sWindowProp& sProp)
	{
		m_sData.m_nWidth = sProp.m_nWidth;
		m_sData.m_nHeight = sProp.m_nHeight;
		m_sData.m_STitle = sProp.m_STitle;

		//设置窗口标题
		setWindowTitle(sProp.m_STitle);
		//初始化窗口大小
		resize(QSize(sProp.m_nWidth, sProp.m_nHeight));
		//设置窗口图标
		setWindowIcon(QIcon(":/icons/EchoEditor.png"));
		//初始化DockWidget
		InitializeDockWidgets();
		//初始化GLWidget
		InitializeGLWidget(m_sData.m_bVSync);
		
		NEST_CLIENT_INFO("Create MainWindow {0} ({1}, {2})", sProp.m_STitle.toStdString(), sProp.m_nWidth, sProp.m_nHeight);
	}

	void MainWindow::InitializeDockWidgets()
	{
		//ConSoleWidget
		ConsoleDock* pConsole = new ConsoleDock(this);
		NEST_CORE_ASSERT(pConsole == nullptr, "Create Console DockWidget Fail!");
		m_pDockManager->AddDockWidget("ConSole", pConsole, Qt::BottomDockWidgetArea);
		
		//TODO: SceneTree


		//TODO: Inspector

		
		NEST_CLIENT_INFO("DockWidgetNum = {0}", m_pDockManager->GetDockWidgetNum());
	}

	void MainWindow::InitializeGLWidget(bool bVsync)
	{
		GLWidget* pGLWidget = new GLWidget(m_sData.m_nWidth, m_sData.m_nHeight, m_sData.m_STitle, bVsync, this);
		NEST_CORE_ASSERT(pGLWidget == nullptr, "Create GLWidget Fail!");
		setCentralWidget(pGLWidget);
	}

}
