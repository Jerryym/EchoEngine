#include "pch.h"
#include "GraphicWidget.h"

namespace EchoEditor {

	GraphicWidget::GraphicWidget(uint32_t nWidth, uint32_t nHeight, QWidget* parent)
		: QWidget(parent)
	{
		// 设置直接绘制在屏幕上
		setAttribute(Qt::WA_PaintOnScreen);
		// 禁用背景填充
		setAutoFillBackground(false);
		// 设置大小
		resize((int)nWidth, (int)nHeight);
		// 初始化
		Initialize();

		// 创建定时器，每秒刷新60次
		m_pTimer = new QTimer(this);
		connect(m_pTimer, &QTimer::timeout, this, QOverload<>::of(&GraphicWidget::update));
		m_pTimer->start(16.6); // 16ms间隔，大约等于60FPS
	}
	
	GraphicWidget::~GraphicWidget()
	{
		m_pGraphicsContext->Destroy();
		if (m_pTimer != nullptr)
		{
			delete m_pTimer;
			m_pTimer = nullptr;
		}
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
