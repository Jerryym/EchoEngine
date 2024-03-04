#include "echopch.h"
#include "Windows_MainWindow.h"
#include "ConsoleDockWidget.h"
#include "GLWidget.h"

namespace Echo {

	Windows_MainWindow* Windows_MainWindow::Create(const NestUI::sWindowProps& props)
	{
		return new Windows_MainWindow(props);
	}

	Windows_MainWindow::Windows_MainWindow(const NestUI::sWindowProps& prop)
	{
		Initialize(prop);
		m_dockManager = NestUI::DockWidgetManager::GetDockManager(this);
	}

	void Windows_MainWindow::InitializeDockWidgets()
	{
		//ConSoleWidget
		ConsoleDockWidget* pConsole = new ConsoleDockWidget(this);
		ECHO_CORE_ASSERT(pConsole == nullptr, "Create ConsoleDockWidget Fail!");
		m_dockManager->AddDockWidget("ConSole", pConsole, Qt::BottomDockWidgetArea);
		ECHO_CORE_INFO("DockWidgetNum = {0}", m_dockManager->GetDockWidgetNum());
	}

	void Windows_MainWindow::InitializeGLWidget()
	{
		GLWidget* pGLFWWidget = new GLWidget(m_sData.m_STitle.toStdString(), m_sData.m_nWidth, m_sData.m_nHeight, this);
		setCentralWidget(pGLFWWidget);
	}

	NestUI::DockWidget* Windows_MainWindow::GetDockWidget(const QString& STitle)
	{
		return dynamic_cast<NestUI::DockWidget*>(m_dockManager->GetDockWidget(STitle));
	}

	Windows_MainWindow::~Windows_MainWindow()
	{
		ShutDown();
	}

	void Windows_MainWindow::SetVSync(bool enabled)
	{
		m_sData.m_bVSync = enabled;
	}

	void Windows_MainWindow::Initialize(const NestUI::sWindowProps& props)
	{
		m_sData.m_nWidth = props.m_nWidth;
		m_sData.m_nHeight = props.m_nHeight;
		m_sData.m_STitle = props.m_STitle;
		NEST_CORE_INFO("Create MainWindow {0} ({1}, {2})", props.m_STitle.toStdString(), props.m_nWidth, props.m_nHeight);

		//初始化窗口大小
		resize(QSize(props.m_nWidth, props.m_nHeight));
		//设置窗口标题
		setWindowTitle(props.m_STitle);
	}

	void Windows_MainWindow::ShutDown()
	{
		destroy();
	}

}
