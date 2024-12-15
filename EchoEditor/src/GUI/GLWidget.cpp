#include "pch.h"
#include "GLWidget.h"

#include <QOpenGLFunctions>

namespace EchoEditor {

	GLWidget::GLWidget(uint32_t nWidth, uint32_t nHeight, const QString& STitle, bool bVsync, QWidget* parent)
		: QOpenGLWidget(parent)
	{
	}

	GLWidget::~GLWidget()
	{
	}

	void GLWidget::initializeGL()
	{
		//为当前上下文初始化 OpenGL 函数解析
		initializeOpenGLFunctions();
	}

	void GLWidget::resizeGL(int w, int h)
	{
	}

	void GLWidget::paintGL()
	{
	}

}
