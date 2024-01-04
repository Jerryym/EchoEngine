#pragma once

#include <QDockWidget>
#include "NestUICore.h"

namespace NestUI {

	class NESTUI_API DockWidget : public QDockWidget
	{
		Q_OBJECT

	public:
		DockWidget(QWidget* parent = nullptr);
		~DockWidget();
	};

}

