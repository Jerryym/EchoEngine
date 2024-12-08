#include "pch.h"
#include "GLWidget.h"

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
	}

	void GLWidget::resizeGL(int w, int h)
	{
	}

	void GLWidget::paintGL()
	{
	}

}
