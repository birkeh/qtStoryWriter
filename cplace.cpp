/*!
 \file cplace.cpp

*/

#include "cplace.h"

#include "common.h"

#include <QSqlQuery>
#include <QSqlError>


cPlace::cPlace(qint32 iID, QObject *parent) :
	QObject(parent),
	m_iID(iID),
	m_szName(""),
	m_szLocation(""),
	m_szType(""),
	m_lpDescription(0)
{
}

void cPlace::setID(const qint32& iID)
{
	m_iID	= iID;
}

qint32 cPlace::id()
{
	return(m_iID);
}

void cPlace::setName(const QString& szName)
{
	m_szName	= szName;
}

QString cPlace::name()
{
	return(m_szName);
}

void cPlace::setLocation(const QString& szLocation)
{
	m_szLocation	= szLocation;
}

QString cPlace::location()
{
	return(m_szLocation);
}

void cPlace::setType(const QString& szType)
{
	m_szType	= szType;
}

QString cPlace::type()
{
	return(m_szType);
}

void cPlace::setDescription(cTextDocument* lpDescription)
{
	m_lpDescription	= lpDescription;
}

cTextDocument* cPlace::description()
{
	return(m_lpDescription);
}

void cPlace::addImage(cImage* lpImage)
{
	if(m_imageList.contains(lpImage))
		return;
	m_imageList.append(lpImage);
}

QList<cImage*> cPlace::images()
{
	return(m_imageList);
}

cPlace* cPlaceList::add(const qint32& iID)
{
	cPlace*	lpPlace	= find(iID);

	if(!lpPlace)
	{
		lpPlace	= new cPlace(iID);
		append(lpPlace);
	}

	return(lpPlace);
}

cPlace* cPlaceList::find(const qint32& iID)
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

bool cPlaceList::load(cImageList *lpImageList)
{
	QSqlQuery	query;

	query.prepare("SELECT id, name, location, type, description FROM place ORDER BY name, location, type;");
	if(!query.exec())
	{
		myDebug << query.lastError().text();
		return(false);
	}

	while(query.next())
	{
		cPlace*	lpPlace	= add(query.value("id").toInt());

		lpPlace->setName(query.value("name").toString());
		lpPlace->setLocation(query.value("location").toString());
		lpPlace->setType(query.value("type").toString());
		lpPlace->setDescription(blob2TextDocument(query.value("description").toByteArray()));
	}

	query.prepare("SELECT placeID, imageID FROM placeImage;");
	if(!query.exec())
	{
		myDebug << query.lastError().text();
		return(false);
	}

	while(query.next())
	{
		cPlace*	lpPlace	= find(query.value("placeID").toInt());
		if(lpPlace)
		{
			cImage*	lpImage		= lpImageList->find(query.value("imageID").toInt());
			if(lpImage)
				lpPlace->addImage(lpImage);
		}
	}

	return(true);
}

bool cPlaceList::save()
{
	QSqlQuery	queryUpdate;
	QSqlQuery	queryInsert;
	QSqlQuery	querySelect;

	queryUpdate.prepare("UPDATE place SET name=:name, location=:location, type=:type, description=:description WHERE id=:id;");
	queryInsert.prepare("INSERT INTO place (name, location, type, description) VALUES (:name, :location, :type, :description);");
	querySelect.prepare("SELECT id FROM place WHERE _rowid_=(SELECT MAX(_rowid_) FROM place);");

	QSqlQuery	imageDelete;
	QSqlQuery	imageAdd;

	imageDelete.prepare("DELETE FROM placeImage WHERE placeID=:placeID;");
	imageAdd.prepare("INSERT INTO placeImage (placeID, imageID) VALUES (:placeID, :imageID);");

	for(int x = 0;x < count();x++)
	{
		cPlace*	lpPlace	= at(x);

		if(lpPlace->id() != -1)
		{
			queryUpdate.bindValue(":id", lpPlace->id());
			queryUpdate.bindValue(":name", lpPlace->name());
			queryUpdate.bindValue(":location", lpPlace->location());
			queryUpdate.bindValue(":type", lpPlace->type());
			queryUpdate.bindValue(":description",  textDocument2Blob(lpPlace->description()));

			if(!queryUpdate.exec())
			{
				myDebug << queryUpdate.lastError().text();
				return(false);
			}
		}
		else
		{
			queryInsert.bindValue(":name", lpPlace->name());
			queryInsert.bindValue(":location", lpPlace->location());
			queryInsert.bindValue(":type", lpPlace->type());
			queryInsert.bindValue(":description",  textDocument2Blob(lpPlace->description()));

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
			lpPlace->setID(querySelect.value("id").toInt());
		}

		imageDelete.bindValue(":placeID", lpPlace->id());
		if(!imageDelete.exec())
		{
			myDebug << imageDelete.lastError().text();
			return(false);
		}

		QList<cImage*>	images	= lpPlace->images();

		for(int x = 0;x < images.count();x++)
		{
			cImage*	lpImage	= images.at(x);

			imageAdd.bindValue(":placeID", lpPlace->id());
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
