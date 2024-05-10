#pragma once
#include "CBaseProperty.h"

namespace NestUI {

	class CStringProperty : public CBaseProperty
	{
	public:
		CStringProperty(const QByteArray& id, const QString& name, const QString& value, const QString& defaultValue = "");
		CStringProperty(CBaseProperty* top, const QByteArray& id, const QString& name, const QString& value, const QString& defaultValue = "");

		void setValue(const QString& value);
		const QString& getValue() const;

		// reimp
		virtual QVariant getVariantValue() const;
		virtual void displayValue();

		virtual void startEdit();
		virtual void finishEdit(bool cancel = false);

	protected:
		mutable QString m_value;
		QString m_defaultValue;
	};

}
