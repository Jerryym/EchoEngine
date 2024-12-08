#pragma once
#include <NestUI.h>
#include <QTextEdit>

namespace EchoEditor {

	class ConsoleDock : public NestUI::DockWidget
	{
		Q_OBJECT
	public:
		ConsoleDock(QWidget* parent = nullptr);
		virtual ~ConsoleDock() {}

	public:
		virtual void clearWidget() override;
		virtual void refreshWidget() override;

	private:
		QTextEdit* m_pLogWidget;
	};

}
