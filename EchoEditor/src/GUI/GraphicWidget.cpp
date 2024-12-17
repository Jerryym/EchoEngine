#include "pch.h"
#include "GraphicWidget.h"

namespace EchoEditor {

	GraphicWidget::GraphicWidget(uint32_t nWidth, uint32_t nHeight, QWidget* parent)
		: QWidget(parent)
	{
		resize((int)nWidth, (int)nHeight);

		//设置帧率为60
		m_pTimer = new QTimer(this);
		connect(m_pTimer, &QTimer::timeout, this, QOverload<>::of(&GraphicWidget::update));
		m_pTimer->start(1000 / 60.0);
	}
	
	GraphicWidget::~GraphicWidget()
	{
		if (m_pTimer != nullptr)
		{
			delete m_pTimer;
			m_pTimer = nullptr;
		}
	}

	void GraphicWidget::paintEvent(QPaintEvent* event)
	{
	}

}
