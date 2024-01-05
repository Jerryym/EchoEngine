#pragma once
#include "Core/EngineCore.h"
#include <QOpenGLWidget>
#include <GLFW/glfw3.h>

namespace Echo {

	class GLWidget : public QOpenGLWidget
	{
		Q_OBJECT
	public:
		GLWidget(QWidget* parent = nullptr);
		virtual ~GLWidget();

	public:
		/// @brief 设置垂直同步
		/// @param enabled 
		void SetVSync(bool enabled);
		/// @brief 是否开启了垂直同步
		/// @return 
		bool IsVSync() const { return m_bVSync; }

	protected:
		virtual void initializeGL() override;
		virtual void resizeGL(int w, int h) override;
		virtual void paintGL() override;

	private:
		/// @brief 初始化GLFW
		void InitializeGLFW();

	private:
		GLFWwindow* m_pGLFWwindow;
		bool m_bVSync = true;			//是否开启垂直同步
	};

}

