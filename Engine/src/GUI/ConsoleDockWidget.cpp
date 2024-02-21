#include "echopch.h"
#include "ConsoleDockWidget.h"
#include <QGridLayout>

namespace Echo {

	ConsoleDockWidget::ConsoleDockWidget(QWidget* parent)
		: DockWidget(parent)
	{
		//设置标题
		setWindowTitle("Console");
		
		//初始化LogWidget
		m_LogWidget = new QTextEdit(this);
		m_LogWidget->setStyleSheet("QTextEdit{        \
                        color: #ffffff;        \
                        border: 0px;        \
                        background-color:rgb(54,54,54);        \
                }");
		m_LogWidget->setReadOnly(true);
		connect(m_LogWidget, SIGNAL(textChanged()), SLOT(addLogger()));

		//设置栅格布局
		QWidget* dockWidgetContents = new QWidget();
		QGridLayout* layout = new QGridLayout(dockWidgetContents);
		layout->addWidget(m_LogWidget, 0, 0, 1, 1);
		setWidget(dockWidgetContents);

		//初始化引擎Log
		Echo::EngineLog::InitLogger(m_LogWidget);
		ECHO_CORE_WARN("Initialiazed Log!");
		ECHO_CLIENT_INFO("Hello Echo Engine!");
	}

	void ConsoleDockWidget::clearWidget()
	{
		m_LogWidget->clear();
	}

	void ConsoleDockWidget::refreshWidget()
	{
	}

	void ConsoleDockWidget::addLogger()
	{
		m_LogWidget->moveCursor(QTextCursor::End);
	}

}
