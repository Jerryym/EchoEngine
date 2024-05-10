#include "nestuipch.h"
#include "CPropertyHeader.h"

namespace NestUI {

	CPropertyHeader::CPropertyHeader(const QByteArray& id, const QString& name)
		: CBaseProperty(id, name)
	{
	}


	CPropertyHeader::CPropertyHeader(CBaseProperty* top, const QByteArray& id, const QString& name)
		: CBaseProperty(top, id, name)
	{
	}


	void CPropertyHeader::onAdded()
	{
		setBackground(Qt::darkGray);
		setForeground(Qt::white);

		// important to call this AFTER adding
		setFirstColumnSpanned(true);
	}

}
