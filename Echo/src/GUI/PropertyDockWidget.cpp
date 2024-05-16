#include "echopch.h"
#include "PropertyDockWidget.h"
#include <QGridLayout>

namespace Echo {

	PropertyDockWidget::PropertyDockWidget(QWidget* parent)
		: DockWidget(parent)
	{
		setWindowTitle("Property");
		m_PropertyEditor = new NestUI::CPropertyEditor(this);
		m_PropertyEditor->init();

		//设置栅格布局
		QWidget* dockWidgetContents = new QWidget();
		QGridLayout* layout = new QGridLayout(dockWidgetContents);
		layout->addWidget(m_PropertyEditor, 0, 0, 1, 1);
		setWidget(dockWidgetContents);
	}

	void PropertyDockWidget::clearWidget()
	{
	}

	void PropertyDockWidget::refreshWidget()
	{
	}

}
