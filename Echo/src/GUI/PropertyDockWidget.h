#pragma once
#include <NestUI.h>

namespace Echo {

	/// @brief 属性停靠窗口
	class PropertyDockWidget : public NestUI::DockWidget
	{
		Q_OBJECT
	public:
		PropertyDockWidget(QWidget* parent = nullptr);
		virtual ~PropertyDockWidget() {}

	public:
		/// @brief 清空DockWidget中的数据
		virtual void clearWidget() override;
		/// @brief 刷新DockWidget
		virtual void refreshWidget() override;

	private:
		/// @brief 属性控件
		NestUI::CPropertyEditor* m_PropertyEditor;
	};

}


