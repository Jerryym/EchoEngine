#include "enginepch.h"
#include "Windows_MainWindow.h"

#include <Nest.h>

namespace Echo {

	Windows_MainWindow* Windows_MainWindow::Create(const NestUI::sWindowProps& props)
	{
		return new Windows_MainWindow(props);
	}

	Windows_MainWindow::Windows_MainWindow(const NestUI::sWindowProps& prop)
	{
		Initialize(prop);
	}

	Windows_MainWindow::~Windows_MainWindow()
	{
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
	}

}
