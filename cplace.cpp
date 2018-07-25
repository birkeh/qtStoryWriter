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
	m_lpDescription(0),
	m_bDeleted(false)
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

void cPlace::setItem(QList<QStandardItem*> itemList)
{
	m_itemList	= itemList;
}

QList<QStandardItem*> cPlace::item()
{
	return(m_itemList);
}

void cPlace::setDeleted(bool bDeleted)
{
	m_bDeleted	= bDeleted;
}

bool cPlace::deleted()
{
	return(m_bDeleted);
}

void cPlace::addImage(cImage* lpImage)
{
	m_imageList.append(lpImage);
}

QList<cImage*> cPlace::images()
{
	return(m_imageList);
}

cPlaceDescription::cPlaceDescription(cPlace* lpPlace, cTextDocument* lpDescription, QObject* parent) :
	QObject(parent)
{
	setPlace(lpPlace);
	setDescription(lpDescription);
}

void cPlaceDescription::setPlace(cPlace* lpPlace)
{
	m_lpPlace	= lpPlace;
}

cPlace* cPlaceDescription::place()
{
	return(m_lpPlace);
}

void cPlaceDescription::setDescription(cTextDocument* lpDescription)
{
	m_lpDescription	= lpDescription;
}

cTextDocument* cPlaceDescription::description()
{
	return(m_lpDescription);
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

bool cPlaceList::load()
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

	query.prepare("SELECT placeID, name, image, description FROM placeImage;");
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
			cImage*	lpImage	= new cImage;
			lpImage->setName(query.value("name").toString());
			lpImage->setDescription(blob2TextDocument(query.value("description").toByteArray()));
			lpImage->setImage(blob2Image(query.value("image").toByteArray()));
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
	QSqlQuery	queryDelete;

	queryUpdate.prepare("UPDATE place SET name=:name, location=:location, type=:type, description=:description WHERE id=:id;");
	queryInsert.prepare("INSERT INTO place (name, location, type, description) VALUES (:name, :location, :type, :description);");
	querySelect.prepare("SELECT id FROM place WHERE _rowid_=(SELECT MAX(_rowid_) FROM place);");
	queryDelete.prepare("DELETE FROM place WHERE id=:id;");

	QSqlQuery	imageDelete;
	QSqlQuery	imageAdd;

	imageDelete.prepare("DELETE FROM placeImage WHERE placeID=:placeID;");
	imageAdd.prepare("INSERT INTO placeImage (placeID, name, description, image) VALUES (:placeID, :name, :description, :image);");

	cPlaceList::iterator	placeIterator	= begin();

	while(placeIterator != end())
	{
		cPlace*	lpPlace	= *placeIterator;

		if(lpPlace->deleted())
		{
			queryDelete.bindValue(":id", lpPlace->id());

			if(!queryDelete.exec())
			{
				myDebug << queryDelete.lastError().text();
				return(false);
			}
			lpPlace	= 0;
		}
		else if(lpPlace->id() != -1)
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

		if(!lpPlace)
			placeIterator	= erase(placeIterator);
		else
		{
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
				imageAdd.bindValue(":name", lpImage->name());
				imageAdd.bindValue(":description", textDocument2Blob(lpImage->description()));
				imageAdd.bindValue(":image", image2Blob(lpImage->image()));
				if(!imageAdd.exec())
				{
					myDebug << imageAdd.lastError().text();
					return(false);
				}
			}
			placeIterator++;
		}
	}

	return(true);
}
