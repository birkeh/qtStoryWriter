/*!
 \file cimage.cpp

*/

#include "cimage.h"

#include "common.h"

#include <QSqlQuery>
#include <QSqlError>


cImage::cImage(qint32 iID, QObject *parent) :
	QObject(parent),
	m_iID(iID),
	m_szName(""),
	m_szType(""),
	m_lpDescription(0)
{
}

void cImage::setID(const qint32& iID)
{
	m_iID	= iID;
}

qint32 cImage::id()
{
	return(m_iID);
}

void cImage::setName(const QString& szName)
{
	m_szName	= szName;
}

QString cImage::name()
{
	return(m_szName);
}

void cImage::setType(const QString& szType)
{
	m_szType	= szType;
}

QString cImage::type()
{
	return(m_szType);
}

void cImage::setDescription(cTextDocument* lpDescription)
{
	m_lpDescription	= lpDescription;
}

cTextDocument* cImage::description()
{
	return(m_lpDescription);
}

QPixmap cImage::load()
{
	QSqlQuery	query;
	QPixmap		image;

	query.prepare("SELECT image FROM image WHERE id = :id;");
	query.bindValue(":id", m_iID);
	if(!query.exec())
	{
		myDebug << query.lastError().text();
		return(image);
	}

	if(!query.first())
	{
		myDebug << query.lastError().text();
		return(image);
	}

	QByteArray	ba	= query.value("image").toByteArray();
	if(!ba.isEmpty())
	{
		if(!image.loadFromData(ba))
		{
			myDebug << "image load error.";
			return(image);
		}
	}

	return(image);
}

cImage* cImageList::add(const qint32& iID)
{
	cImage*	lpImage	= find(iID);

	if(!lpImage)
	{
		lpImage	= new cImage(iID);
		append(lpImage);
	}

	return(lpImage);
}

cImage* cImageList::find(const qint32& iID)
{
	for(int x = 0;x < count();x++)
	{
		if(at(x)->id() == iID)
			return(at(x));
	}

	return(0);
}

bool cImageList::load()
{
	QSqlQuery	query;

	query.prepare("SELECT id, name, type, description FROM image ORDER BY name, type;");
	if(!query.exec())
	{
		myDebug << query.lastError().text();
		return(false);
	}

	while(query.next())
	{
		cImage*	lpImage	= add(query.value("id").toInt());

		lpImage->setName(query.value("name").toString());
		lpImage->setType(query.value("type").toString());
		lpImage->setDescription(blob2TextDocument(query.value("description").toByteArray()));
	}

	return(true);
}

bool cImageList::save()
{
	QSqlQuery	queryUpdate;
	QSqlQuery	queryInsert;
	QSqlQuery	querySelect;

	queryUpdate.prepare("UPDATE image SET type=:type, name=:name, description=:description WHERE id=:id;");
	queryInsert.prepare("INSERT INTO image (type, name, description) VALUES (:type, :name, :description);");
	querySelect.prepare("SELECT id FROM image WHERE _rowid_=(SELECT MAX(_rowid_) FROM image);");

	for(int x = 0;x < count();x++)
	{
		cImage*	lpImage	= at(x);

		if(lpImage->id() != -1)
		{
			queryUpdate.bindValue(":id", lpImage->id());
			queryUpdate.bindValue(":type", lpImage->type());
			queryUpdate.bindValue(":name", lpImage->name());
			queryUpdate.bindValue(":description", textDocument2Blob(lpImage->description()));
			if(!queryUpdate.exec())
			{
				myDebug << queryUpdate.lastError().text();
				return(false);
			}
// NICHT VOLLSTÄNDIG
		}
		else
		{
			queryInsert.bindValue(":type", lpImage->type());
			queryInsert.bindValue(":name", lpImage->name());
			queryInsert.bindValue(":description", textDocument2Blob(lpImage->description()));
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
			lpImage->setID(querySelect.value("id").toInt());
// NICHT VOLLSTÄNDIG
		}
	}

	return(true);
}
