#pragma once
#include "CBaseProperty.h"
#include <QDate>

namespace NestUI {

	class NESTUI_API CDateProperty : public CBaseProperty
	{
	public:
		CDateProperty(const QByteArray& id, const QString& name, const QDate& value, const QDate& defaultValue = QDate::currentDate());
		CDateProperty(CBaseProperty* top, const QByteArray& id, const QString& name, const QDate& value, const QDate& defaultValue = QDate::currentDate());

		void setDate(const QDate& value);
		QDate getDate() const;

		void setMaximumDate(const QDate& value);
		QDate getMaximumDate() const;
		void setMinimumDate(const QDate& value);
		QDate getMinimumDate() const;
		void setDateRange(const QDate& min, const QDate& max);

		void setDisplayFormat(const QString& format);
		QString	displayFormat() const;

		// reimp
		virtual QVariant getVariantValue() const;
		virtual void displayValue();
		virtual void validateValue();

		virtual QWidget* createEditor() const;
		virtual void valueToEditor();
		virtual void valueFromEditor();

	protected:
		mutable QDate m_value;
		QDate m_defaultValue, m_maxDate, m_minDate;
		QString m_format;
	};

}
