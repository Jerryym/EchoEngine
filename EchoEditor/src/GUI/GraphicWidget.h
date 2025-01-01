#pragma once

struct GLFWwindow;

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
		virtual void resizeEvent(QResizeEvent* event) override;

		/// @brief 获取绘制引擎
		/// @return 返回nullptr：表示禁用QPainter绘制组件，完全使用渲染引擎来绘制
		virtual QPaintEngine* paintEngine() const override { return nullptr; }

	private:
		/// @brief 初始化
		void Initialize();

	private:
		/// @brief GLFW窗口
		GLFWwindow* m_pWindow;
		/// @brief 渲染上下文
		Echo::Ref<Echo::GraphicsContext> m_pGraphicsContext;

		unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;
	};

}
