#pragma once
#include <NestUI.h>

#include <QTextEdit>
#include <QGridLayout>

namespace Nest {

	/// @brief 控制台Dock: 一般用于Log输出
	class ConsoleDockWidget : public NestUI::DockWidget
	{
		Q_OBJECT
	public:
		ConsoleDockWidget(QWidget* parent = nullptr);
		virtual ~ConsoleDockWidget() {}

	public:
		/// @brief 清空LogWidget中的数据
		virtual void clearWidget() override;
		/// @brief 刷新DockWidget
		virtual void refreshWidget() override;

		/// @brief 获取Log输出控件
		/// @return 
		inline QTextEdit* getLogWidget() { return m_LogWidget; }

	public slots:
		void addLogger();

	private:
		QTextEdit* m_LogWidget;
	};
}


