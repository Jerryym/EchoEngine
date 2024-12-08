#pragma once
#include <QOpenGLWidget>

namespace EchoEditor {

	class GLWidget : public QOpenGLWidget
	{
		Q_OBJECT
	public:
		GLWidget(uint32_t nWidth, uint32_t nHeight, const QString& STitle, bool bVsync, QWidget* parent = nullptr);
		virtual ~GLWidget();

	protected:
		virtual void initializeGL() override;
		virtual void resizeGL(int w, int h) override;
		virtual void paintGL() override;

	};

}
