#include "cchapter.h"

#include "common.h"

#include <QSqlQuery>
#include <QSqlError>


cChapter::cChapter(qint32 iID, QObject *parent) :
	QObject(parent),
	m_iID(iID),
	m_lpPart(0),
	m_szName(""),
	m_iSortOrder(-1),
	m_szDescription(""),
	m_szFile("")
{
}

void cChapter::setID(const qint32& iID)
{
	m_iID	= iID;
}

qint32 cChapter::id()
{
	return(m_iID);
}

void cChapter::setPart(cPart* lpPart)
{
	m_lpPart	= lpPart;
}

cPart* cChapter::part()
{
	return(m_lpPart);
}

void cChapter::setName(const QString& szName)
{
	m_szName	= szName;
}

QString cChapter::name()
{
	return(m_szName);
}

void cChapter::setSortOrder(const qint32& iSortOrder)
{
	m_iSortOrder	= iSortOrder;
}

qint32 cChapter::sortOrder()
{
	return(m_iSortOrder);
}

void cChapter::setDescription(const QString& szDescription)
{
	m_szDescription	= szDescription;
}

QString cChapter::description()
{
	return(m_szDescription);
}

void cChapter::setFile(const QString& szFile)
{
	m_szFile	= szFile;
}

QString cChapter::file()
{
	return(m_szFile);
}

cChapter* cChapterList::add(const qint32& iID)
{
	cChapter*	lpChapter	= find(iID);

	if(!lpChapter)
	{
		lpChapter	= new cChapter(iID);
		append(lpChapter);
	}

	return(lpChapter);
}

cChapter* cChapterList::find(const qint32& iID)
{
	for(int x = 0;x < count();x++)
	{
		if(at(x)->id() == iID)
			return(at(x));
	}

	return(0);
}

bool cChapterList::load(cPartList* lpPartList)
{
	QSqlQuery	query;

	query.prepare("SELECT id, partID, name, sortOrder, description, file FROM chapter ORDER BY sortOrder;");
	if(!query.exec())
	{
		myDebug << query.lastError().text();
		return(false);
	}

	while(query.next())
	{
		cChapter*	lpChapter	= add(query.value("id").toInt());

		lpChapter->setPart(lpPartList->find(query.value("partID").toInt()));
		lpChapter->setName(query.value("name").toString());
		lpChapter->setSortOrder(query.value("sortOrder").toInt());
		lpChapter->setDescription(query.value("description").toString());
		lpChapter->setFile(query.value("file").toString());
	}

	return(true);
}

bool cChapterList::save()
{
	return(true);
}
