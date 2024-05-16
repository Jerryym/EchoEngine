#pragma once
#include "NestUICore.h"
#include <QToolButton>

namespace NestUI {

	class NESTUI_API CButtonBasedEditor : public QWidget
	{
		Q_OBJECT
	public:
		explicit CButtonBasedEditor(QWidget* hostedEditor, QWidget* parent = 0);
		virtual ~CButtonBasedEditor();

	public Q_SLOTS:
		void enableButton(bool on);

	protected Q_SLOTS:
		// reimp
		virtual void onEditButtonActivated() = 0;

	protected:
		virtual bool event(QEvent* e);
		virtual void showEvent(QShowEvent* e);

		QWidget* m_hostedEditor;
		QToolButton* m_button;
	};


	template<class EditorClass>
	class NESTUI_API TButtonBasedEditor : public CButtonBasedEditor
	{
	public:
		TButtonBasedEditor(EditorClass* hostedEditor, QWidget* parent = 0)
			: CButtonBasedEditor(hostedEditor, parent)
		{
		}

	protected:
		EditorClass* getEditor() const
		{
			return dynamic_cast<EditorClass*>(m_hostedEditor);
		}
	};


}
