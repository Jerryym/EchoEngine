#include "pch.h"
#include "ConsoleDock.h"

#include <QGridLayout>

namespace EchoEditor {

	ConsoleDock::ConsoleDock(QWidget* parent)
		: NestUI::DockWidget(parent)
	{
		//设置标题
		setWindowTitle("Console");
		
		//初始化LogWidget
		m_pLogWidget = new QTextEdit(this);
		m_pLogWidget->setStyleSheet("background-color: grey;");
		m_pLogWidget->setReadOnly(true);
		
		//设置栅格布局
		QWidget* dockWidgetContents = new QWidget();
		QGridLayout* layout = new QGridLayout(dockWidgetContents);
		layout->addWidget(m_pLogWidget, 0, 0, 1, 1);
		setWidget(dockWidgetContents);
		
		//初始化Log
		NestApp::Log::Init(m_pLogWidget);
		NEST_CORE_WARN("Initialiazed Log!");
		NEST_CLIENT_INFO("Hello Echo Engine!");
	}

	void ConsoleDock::clearWidget()
	{
		m_pLogWidget->clear();
	}

	void ConsoleDock::refreshWidget()
	{
	}

}
