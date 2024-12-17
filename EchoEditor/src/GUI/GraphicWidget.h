#pragma once
#include <QWidget>
#include <QTimer>

namespace EchoEditor {

	/// @brief 图形显示组件
	class GraphicWidget : public QWidget
	{
		Q_OBJECT
	public:
		GraphicWidget(uint32_t nWidth, uint32_t nHeight, QWidget* parent = nullptr);
		virtual ~GraphicWidget();

	public:
		virtual void paintEvent(QPaintEvent* event) override;

	private:
		/// @brief 定时器：用于刷新界面
		QTimer* m_pTimer = nullptr;
	};

}
