#pragma once
#include <QOpenGLWidget>
#include <GLFW/glfw3.h>
#include <QTimer>

#include "Platform/OpenGL/OpenGLContext.h"
#include "Core/LayerStack.h"

namespace Nest {

	class GLWidget : public QOpenGLWidget
	{
		Q_OBJECT
	public:
		GLWidget(const std::string& strTitle, int nWidth, int nHeight, QWidget* parent = nullptr);
		virtual ~GLWidget();

	public:
		/// @brief 设置垂直同步
		/// @param enabled 
		void SetVSync(bool enabled);
		/// @brief 是否开启了垂直同步
		/// @return 
		bool IsVSync() const { return m_bVSync; }

		/// @brief GLFW窗口关闭
		void ShutDown();

	protected:
		virtual void initializeGL() override;
		virtual void resizeGL(int w, int h) override;
		virtual void paintGL() override;

	protected:
		/// @brief 
		/// @param event 
		virtual void keyPressEvent(QKeyEvent* event) override;
		/// @brief 
		/// @param event 
		virtual void mousePressEvent(QMouseEvent* event) override;
		/// @brief 
		/// @param event 
		virtual void mouseReleaseEvent(QMouseEvent* event) override;
		/// @brief 
		/// @param event 
		virtual void mouseMoveEvent(QMouseEvent* event) override;
		/// @brief 
		/// @param event 
		virtual void wheelEvent(QWheelEvent* event) override;

	private:
		/// @brief 初始化GLFW
		void InitializeGLWidget(const std::string& strTitle, int nWidth, int nHeight);

	private:
		GLFWwindow* m_pGLFWwindow;
		/// @brief OpenGL上下文
		Echo::GraphicContext* m_pContext;
		/// @brief 是否开启垂直同步
		bool m_bVSync = true;
		/// @brief 定时器, 用于实现按帧刷新
		QTimer* m_pTimer;
		/// @brief 层栈
		Nest::LayerStack m_layerStack;
	};

}

