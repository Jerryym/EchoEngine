#pragma once
#include <QDockWidget>
#include <Core.h>

namespace NestUI {

	class NESTUI_API DockWidget : public QDockWidget
	{
		Q_OBJECT
	public:
		DockWidget(QWidget* parent = nullptr);
		~DockWidget();

	public:
		/// @brief 清空DockWidget内容
		virtual void clearWidget() = 0;
		/// @brief 刷新DockWidget
		virtual void refreshWidget() = 0;
	};

}

