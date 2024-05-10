#pragma once
#include <QTreeWidget>
#include <QMap>

namespace NestUI {

	class CBaseProperty;
	class CBoolProperty;
	class CIntegerProperty;

	class CPropertyEditor : public QTreeWidget
	{
		Q_OBJECT
	public:
		explicit CPropertyEditor(QWidget* parent = 0);

		void init();
		void adjustToContents();

		bool add(CBaseProperty* prop);
		bool remove(CBaseProperty* prop);

	public Q_SLOTS:
		void onWidgetEditorFinished();

	private Q_SLOTS:
		void onCurrentItemChanged(QTreeWidgetItem* current, QTreeWidgetItem* previous);
		void onItemClicked(QTreeWidgetItem* item, int column);
		void onItemChanged(QTreeWidgetItem* item, int column);

	protected:
		virtual void keyPressEvent(QKeyEvent* event);

		QMap<QByteArray, CBaseProperty*> m_propertyMap;
		bool m_addingItem;
	};

}