#include "cpart.h"

#include "common.h"

#include <QSqlQuery>
#include <QSqlError>


cPart::cPart(qint32 iID, QObject *parent) :
	QObject(parent),
	m_iID(iID),
	m_szName(""),
	m_iSortOrder(-1),
	m_lpDescription(0),
	m_lpText(0)
{
}

void cPart::setID(const qint32& iID)
{
	m_iID	= iID;
}

qint32 cPart::id()
{
	return(m_iID);
}

void cPart::setName(const QString& szName)
{
	m_szName	= szName;
}

QString cPart::name()
{
	return(m_szName);
}

void cPart::setSortOrder(const qint32& iSortOrder)
{
	m_iSortOrder	= iSortOrder;
}

qint32 cPart::sortOrder()
{
	return(m_iSortOrder);
}

void cPart::setDescription(cTextDocument* lpDescription)
{
	m_lpDescription	= lpDescription;
}

cTextDocument* cPart::description()
{
	return(m_lpDescription);
}

void cPart::setText(cTextDocument* lpText)
{
	m_lpText	= lpText;
}

cTextDocument* cPart::text()
{
	return(m_lpText);
}

cPart* cPartList::add(const qint32& iID)
{
	cPart*	lpPart	= find(iID);

	if(!lpPart)
	{
		lpPart	= new cPart(iID);
		append(lpPart);
	}

	return(lpPart);
}

cPart* cPartList::find(const qint32& iID)
{
	for(int x = 0;x < count();x++)
	{
		if(at(x)->id() == iID)
			return(at(x));
	}

	return(0);
}

bool cPartList::load()
{
	QSqlQuery	query;

	query.prepare("SELECT id, name, sortOrder, description, text FROM part ORDER BY sortOrder;");
	if(!query.exec())
	{
		myDebug << query.lastError().text();
		return(false);
	}

	while(query.next())
	{
		cPart*	lpPart	= add(query.value("id").toInt());
		lpPart->setName(query.value("name").toString());
		lpPart->setSortOrder(query.value("sortOrder").toInt());
		lpPart->setDescription(blob2TextDocument(query.value("description").toByteArray()));
		lpPart->setText(blob2TextDocument(query.value("text").toByteArray()));
	}

	return(true);
}

bool cPartList::save()
{
	return(true);
}
