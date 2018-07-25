/*!
 \file cchapter.cpp

*/

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
	m_lpDescription(0),
	m_lpText(0),
	m_lpItem(0),
	m_bDeleted(false)
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

void cChapter::setDescription(cTextDocument* lpDescription)
{
	m_lpDescription	= lpDescription;
}

cTextDocument* cChapter::description()
{
	return(m_lpDescription);
}

void cChapter::setText(cTextDocument* lpText)
{
	m_lpText	= lpText;
}

cTextDocument* cChapter::text()
{
	return(m_lpText);
}

void cChapter::setItem(QStandardItem* lpItem)
{
	m_lpItem	= lpItem;
}

QStandardItem* cChapter::item()
{
	return(m_lpItem);
}

void cChapter::setDeleted(bool bDeleted)
{
	m_bDeleted	= bDeleted;
}

bool cChapter::deleted()
{
	return(m_bDeleted);
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
	if(iID == -1)
		return(0);

	for(int x = 0;x < count();x++)
	{
		if(at(x)->id() == iID)
			return(at(x));
	}

	return(0);
}

QList<cChapter*> cChapterList::find(cPart* lpPart)
{
	QList<cChapter*>	chapterList;

	for(int x = 0;x < count();x++)
	{
		if(at(x)->part() == lpPart)
			chapterList.append(at(x));
	}
	return(chapterList);
}

qint32 cChapterList::nextSort(cPart* lpPart)
{
	qint32	iSort	= -1;

	for(int x = 0;x < count();x++)
	{
		if(lpPart == at(x)->part() && iSort < at(x)->sortOrder())
			iSort	= at(x)->sortOrder();
	}
	return(iSort+1);
}

bool cChapterList::load(cPartList* lpPartList)
{
	QSqlQuery	query;

	query.prepare("SELECT id, partID, name, sortOrder, description, text FROM chapter ORDER BY sortOrder;");
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
		lpChapter->setDescription(blob2TextDocument(query.value("description").toByteArray()));
		lpChapter->setText(blob2TextDocument(query.value("text").toByteArray()));
	}

	return(true);
}

bool cChapterList::save()
{
	QSqlQuery	queryUpdate;
	QSqlQuery	queryInsert;
	QSqlQuery	querySelect;
	QSqlQuery	queryDelete;

	queryUpdate.prepare("UPDATE chapter SET name=:name, partID=:partID, sortOrder=:sortOrder, description=:description, text=:text WHERE id=:id;");
	queryInsert.prepare("INSERT INTO chapter (name, partID, sortOrder, description, text) VALUES (:name, :partID, :sortOrder, :description, :text);");
	querySelect.prepare("SELECT id FROM chapter WHERE _rowid_=(SELECT MAX(_rowid_) FROM chapter);");
	queryDelete.prepare("DELETE FROM chapter WHERE id=:id;");

	cChapterList::iterator	chapterIterator	= begin();

	while(chapterIterator != end())
	{
		cChapter*	lpChapter	= *chapterIterator;

		if(lpChapter->deleted())
		{
			queryDelete.bindValue(":id", lpChapter->id());

			if(!queryDelete.exec())
			{
				myDebug << queryDelete.lastError().text();
				return(false);
			}
			lpChapter	= 0;
		}
		else if(lpChapter->id() != -1)
		{
			queryUpdate.bindValue(":id", lpChapter->id());
			queryUpdate.bindValue(":name", lpChapter->name());
			queryUpdate.bindValue(":partID", lpChapter->part()->id());
			queryUpdate.bindValue(":sortOrder", lpChapter->sortOrder());
			queryUpdate.bindValue(":description",  textDocument2Blob(lpChapter->description()));
			queryUpdate.bindValue(":text",  textDocument2Blob(lpChapter->text()));

			if(!queryUpdate.exec())
			{
				myDebug << queryUpdate.lastError().text();
				return(false);
			}
		}
		else
		{
			queryInsert.bindValue(":name", lpChapter->name());
			queryInsert.bindValue(":partID", lpChapter->part()->id());
			queryInsert.bindValue(":sortOrder", lpChapter->sortOrder());
			queryInsert.bindValue(":description",  textDocument2Blob(lpChapter->description()));
			queryInsert.bindValue(":text",  textDocument2Blob(lpChapter->text()));

			if(!queryInsert.exec())
			{
				myDebug << queryInsert.lastError().text();
				return(false);
			}

			if(!querySelect.exec())
			{
				myDebug << querySelect.lastError().text();
				return(false);
			}
			querySelect.next();
			lpChapter->setID(querySelect.value("id").toInt());
		}

		if(!lpChapter)
			chapterIterator	= erase(chapterIterator);
		else
			chapterIterator++;
	}

	return(true);
}
