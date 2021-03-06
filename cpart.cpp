/*!
 \file cpart.cpp

*/

#include "cpart.h"

#include "common.h"

#include <QSqlQuery>
#include <QSqlError>


cPart::cPart(qint32 iID, QObject *parent) :
	QObject(parent),
	m_iID(iID),
	m_szName(""),
	m_iSortOrder(-1),
	m_lpDescription(new cTextDocument(parent)),
	m_lpText(new cTextDocument(parent)),
	m_lpItem(0),
	m_bDeleted(false)
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

void cPart::setItem(QStandardItem* lpItem)
{
	m_lpItem	= lpItem;
}

QStandardItem* cPart::item()
{
	return(m_lpItem);
}

void cPart::setDeleted(bool bDeleted)
{
	m_bDeleted	= bDeleted;
}

bool cPart::deleted()
{
	return(m_bDeleted);
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
	if(iID == -1)
		return(0);

	for(int x = 0;x < count();x++)
	{
		if(at(x)->id() == iID)
			return(at(x));
	}

	return(0);
}

qint32 cPartList::nextSort()
{
	qint32	iSort	= -1;

	for(int x = 0;x < count();x++)
	{
		if(iSort < at(x)->sortOrder())
			iSort	= at(x)->sortOrder();
	}
	return(iSort+1);
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
	QSqlQuery	queryUpdate;
	QSqlQuery	queryInsert;
	QSqlQuery	querySelect;
	QSqlQuery	queryDelete;

	queryUpdate.prepare("UPDATE part SET name=:name, sortOrder=:sortOrder, description=:description, text=:text WHERE id=:id;");
	queryInsert.prepare("INSERT INTO part (name, sortOrder, description, text) VALUES (:name, :sortOrder, :description, :text);");
	querySelect.prepare("SELECT id FROM part WHERE _rowid_=(SELECT MAX(_rowid_) FROM part);");
	queryDelete.prepare("DELETE FROM part WHERE id=:id;");

	cPartList::iterator	partIterator	= begin();

	while(partIterator != end())
	{
		cPart*	lpPart	= *partIterator;

		if(lpPart->deleted())
		{
			queryDelete.bindValue(":id", lpPart->id());

			if(!queryDelete.exec())
			{
				myDebug << queryDelete.lastError().text();
				return(false);
			}
			lpPart	= 0;
		}
		else if(lpPart->id() != -1)
		{
			queryUpdate.bindValue(":id", lpPart->id());
			queryUpdate.bindValue(":name", lpPart->name());
			queryUpdate.bindValue(":sortOrder", lpPart->sortOrder());
			queryUpdate.bindValue(":description",  textDocument2Blob(lpPart->description()));
			queryUpdate.bindValue(":text",  textDocument2Blob(lpPart->text()));

			if(!queryUpdate.exec())
			{
				myDebug << queryUpdate.lastError().text();
				return(false);
			}
		}
		else
		{
			queryInsert.bindValue(":name", lpPart->name());
			queryInsert.bindValue(":sortOrder", lpPart->sortOrder());
			queryInsert.bindValue(":description",  textDocument2Blob(lpPart->description()));
			queryInsert.bindValue(":text",  textDocument2Blob(lpPart->text()));

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
			lpPart->setID(querySelect.value("id").toInt());
		}

		if(!lpPart)
			partIterator	= erase(partIterator);
		else
			partIterator++;
	}

	return(true);
}
