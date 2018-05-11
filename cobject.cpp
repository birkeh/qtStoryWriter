/*!
 \file cobject.cpp

*/

#include "cobject.h"

#include "common.h"

#include <QSqlQuery>
#include <QSqlError>


cObject::cObject(qint32 iID, QObject *parent) :
	QObject(parent),
	m_iID(iID),
	m_szName(""),
	m_szType(""),
	m_lpDescription(0)
{
}

void cObject::setID(const qint32& iID)
{
	m_iID	= iID;
}

qint32 cObject::id()
{
	return(m_iID);
}

void cObject::setName(const QString& szName)
{
	m_szName	= szName;
}

QString cObject::name()
{
	return(m_szName);
}

void cObject::setType(const QString& szType)
{
	m_szType	= szType;
}

QString cObject::type()
{
	return(m_szType);
}

void cObject::setDescription(cTextDocument* lpDescription)
{
	m_lpDescription	= lpDescription;
}

cTextDocument* cObject::description()
{
	return(m_lpDescription);
}

void cObject::addImage(cImage* lpImage)
{
	if(m_imageList.contains(lpImage))
		return;
	m_imageList.append(lpImage);
}

QList<cImage*> cObject::images()
{
	return(m_imageList);
}

cObject* cObjectList::add(const qint32& iID)
{
	cObject*	lpObject	= find(iID);

	if(!lpObject)
	{
		lpObject	= new cObject(iID);
		append(lpObject);
	}

	return(lpObject);
}

cObject* cObjectList::find(const qint32& iID)
{
	for(int x = 0;x < count();x++)
	{
		if(at(x)->id() == iID)
			return(at(x));
	}

	return(0);
}

bool cObjectList::load(cImageList *lpImageList)
{
	QSqlQuery	query;

	query.prepare("SELECT id, name, type, description FROM object ORDER BY name, type;");
	if(!query.exec())
	{
		myDebug << query.lastError().text();
		return(false);
	}

	while(query.next())
	{
		cObject*	lpObject	= add(query.value("id").toInt());

		lpObject->setName(query.value("name").toString());
		lpObject->setType(query.value("type").toString());
		lpObject->setDescription(blob2TextDocument(query.value("description").toByteArray()));
	}

	query.prepare("SELECT objectID, imageID FROM objectImage;");
	if(!query.exec())
	{
		myDebug << query.lastError().text();
		return(false);
	}

	while(query.next())
	{
		cObject*	lpObject	= find(query.value("objectID").toInt());
		if(lpObject)
		{
			cImage*	lpImage		= lpImageList->find(query.value("imageID").toInt());
			if(lpImage)
				lpObject->addImage(lpImage);
		}
	}

	return(true);
}

bool cObjectList::save()
{
	QSqlQuery	queryUpdate;
	QSqlQuery	queryInsert;
	QSqlQuery	querySelect;

	queryUpdate.prepare("UPDATE object SET name=:name, type=:type, description=:description WHERE id=:id;");
	queryInsert.prepare("INSERT INTO object (name, type, description) VALUES (:name, :type, :description);");
	querySelect.prepare("SELECT id FROM object WHERE _rowid_=(SELECT MAX(_rowid_) FROM object);");

	QSqlQuery	imageDelete;
	QSqlQuery	imageAdd;

	imageDelete.prepare("DELETE FROM objectImage WHERE objectID=:objectID;");
	imageAdd.prepare("INSERT INTO objectImage (objectID, imageID) VALUES (:objectID, :imageID);");

	for(int x = 0;x < count();x++)
	{
		cObject*	lpObject	= at(x);

		if(lpObject->id() != -1)
		{
			queryUpdate.bindValue(":id", lpObject->id());
			queryUpdate.bindValue(":name", lpObject->name());
			queryUpdate.bindValue(":type", lpObject->type());
			queryUpdate.bindValue(":description",  textDocument2Blob(lpObject->description()));

			if(!queryUpdate.exec())
			{
				myDebug << queryUpdate.lastError().text();
				return(false);
			}
		}
		else
		{
			queryInsert.bindValue(":name", lpObject->name());
			queryInsert.bindValue(":type", lpObject->type());
			queryInsert.bindValue(":description",  textDocument2Blob(lpObject->description()));

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
			lpObject->setID(querySelect.value("id").toInt());
		}

		imageDelete.bindValue(":objectID", lpObject->id());
		if(!imageDelete.exec())
		{
			myDebug << imageDelete.lastError().text();
			return(false);
		}

		QList<cImage*>	images	= lpObject->images();

		for(int x = 0;x < images.count();x++)
		{
			cImage*	lpImage	= images.at(x);

			imageAdd.bindValue(":objectID", lpObject->id());
			imageAdd.bindValue(":imageID", lpImage->id());
			if(!imageAdd.exec())
			{
				myDebug << imageAdd.lastError().text();
				return(false);
			}
		}
	}

	return(true);
}
