#include "pch.h"
#include "GraphicWidget.h"

#include <glad/glad.h>

namespace EchoEditor {

	static bool s_bGLFWInitialiazed = false;

	GraphicWidget::GraphicWidget(uint32_t nWidth, uint32_t nHeight, QWidget* parent)
		: QWidget(parent)
	{
		// 设置直接绘制在屏幕上
		setAttribute(Qt::WA_PaintOnScreen);
		setAutoFillBackground(false);  // 禁用背景填充
		// 设置大小
		resize((int)nWidth, (int)nHeight);
		// 初始化
		Initialize();
	}
	
	GraphicWidget::~GraphicWidget()
	{
		m_pGraphicsContext->Destroy();
	}

	void GraphicWidget::paintEvent(QPaintEvent* event)
	{
		//设置当前上下文
		m_pGraphicsContext->MakeCurrent();

		Echo::Renderer::InitScene();
		Echo::RenderCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
		Echo::RenderCommand::Clear();

		// 交换缓冲区
		m_pGraphicsContext->SwapBuffers();
	}

	void GraphicWidget::resizeEvent(QResizeEvent* event)
	{
		int iWidth = event->size().width();
		int iHeight = event->size().height();

		//设置当前上下文
		m_pGraphicsContext->MakeCurrent();
		Echo::Renderer::WindowResize(iWidth, iHeight);
		//交换缓冲区
		m_pGraphicsContext->SwapBuffers();
	}

	void GraphicWidget::Initialize()
	{
		// 创建渲染上下文
        m_pGraphicsContext = Echo::GraphicsContext::CreateContext(width(), height(), "EchoEngine", false);
		m_pGraphicsContext->Init();

		//将GLFW嵌入到GraphicWidget中
		QWindow* window = QWindow::fromWinId((WId)m_pGraphicsContext->GetWindowHandle());
		QWidget* container = QWidget::createWindowContainer(window, this);
		QVBoxLayout* layout = new QVBoxLayout(this);
		layout->addWidget(container);
		layout->setContentsMargins(0, 0, 0, 0);
		setLayout(layout);
	}

}
