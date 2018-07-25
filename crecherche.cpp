/*!
 \file crecherche.cpp

*/

#include "crecherche.h"

#include "common.h"

#include <QSqlQuery>
#include <QSqlError>


cRecherche::cRecherche(qint32 iID, QObject *parent) :
	QObject(parent),
	m_iID(iID),
	m_szName(""),
	m_szLink(""),
	m_lpDescription(new cTextDocument(parent)),
	m_bDeleted(false)
{
}

void cRecherche::setID(const qint32& iID)
{
	m_iID	= iID;
}

qint32 cRecherche::id()
{
	return(m_iID);
}

void cRecherche::setName(const QString& szName)
{
	m_szName	= szName;
}

QString cRecherche::name()
{
	return(m_szName);
}

void cRecherche::setLink(const QString& szLink)
{
	m_szLink	= szLink;
}

QString cRecherche::link()
{
	return(m_szLink);
}

void cRecherche::setDescription(cTextDocument* lpDescription)
{
	m_lpDescription	= lpDescription;
}

cTextDocument* cRecherche::description()
{
	return(m_lpDescription);
}

void cRecherche::setItem(QList<QStandardItem*> itemList)
{
	m_itemList	= itemList;
}

QList<QStandardItem*> cRecherche::item()
{
	return(m_itemList);
}

void cRecherche::setDeleted(bool bDeleted)
{
	m_bDeleted	= bDeleted;
}

bool cRecherche::deleted()
{
	return(m_bDeleted);
}

void cRecherche::addImage(cImage* lpImage)
{
	m_imageList.append(lpImage);
}

void cRecherche::addCharacter(cCharacter* lpCharacter, cTextDocument* lpDescription)
{
	m_characterList.append(new cCharacterDescription(lpCharacter, lpDescription));
}

void cRecherche::removeCharacter(cCharacterDescription* lpCharacter)
{
	m_characterList.removeOne(lpCharacter);
}

void cRecherche::addObject(cObject* lpObject, cTextDocument* lpDescription)
{
	m_objectList.append(new cObjectDescription(lpObject, lpDescription));
}

void cRecherche::removeObject(cObjectDescription* lpObject)
{
	m_objectList.removeOne(lpObject);
}

void cRecherche::addPlace(cPlace* lpPlace, cTextDocument* lpDescription)
{
	m_placeList.append(new cPlaceDescription(lpPlace, lpDescription));
}

void cRecherche::removePlace(cPlaceDescription* lpPlace)
{
	m_placeList.removeOne(lpPlace);
}

QList<cImage*> cRecherche::images()
{
	return(m_imageList);
}

QList<cCharacterDescription*> cRecherche::characterList()
{
	return(m_characterList);
}

QList<cObjectDescription*> cRecherche::objectList()
{
	return(m_objectList);
}

QList<cPlaceDescription*> cRecherche::placeList()
{
	return(m_placeList);
}

cRecherche* cRechercheList::add(const qint32& iID)
{
	cRecherche*	lpRecherche	= find(iID);

	if(!lpRecherche)
	{
		lpRecherche	= new cRecherche(iID);
		append(lpRecherche);
	}

	return(lpRecherche);
}

cRecherche* cRechercheList::find(const qint32& iID)
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

QList<cRecherche*> cRechercheList::find(cCharacter* lpCharacter)
{
	QList<cRecherche*>	rechercheList;

	for(int x = 0;x < count();x++)
	{
		QList<cCharacterDescription*>	list	= at(x)->characterList();

		for(int y = 0;y < list.count();y++)
		{
			if(list.at(y)->character() == lpCharacter)
			{
				rechercheList.append(at(x));
				break;
			}
		}
	}
	return(rechercheList);
}

QList<cRecherche*> cRechercheList::find(cPlace* lpPlace)
{
	QList<cRecherche*>	rechercheList;

	for(int x = 0;x < count();x++)
	{
		QList<cPlaceDescription*>	list	= at(x)->placeList();

		for(int y = 0;y < list.count();y++)
		{
			if(list.at(y)->place() == lpPlace)
			{
				rechercheList.append(at(x));
				break;
			}
		}
	}
	return(rechercheList);
}

QList<cRecherche*> cRechercheList::find(cObject* lpObject)
{
	QList<cRecherche*>	rechercheList;

	for(int x = 0;x < count();x++)
	{
		QList<cObjectDescription*>	list	= at(x)->objectList();

		for(int y = 0;y < list.count();y++)
		{
			if(list.at(y)->object() == lpObject)
			{
				rechercheList.append(at(x));
				break;
			}
		}
	}
	return(rechercheList);
}

bool cRechercheList::load(cCharacterList *lpCharacterList, cObjectList *lpObjectList, cPlaceList *lpPlaceList)
{
	QSqlQuery	query;

	query.prepare("SELECT id, name, link, description FROM recherche ORDER BY name, link;");
	if(!query.exec())
	{
		myDebug << query.lastError().text();
		return(false);
	}

	while(query.next())
	{
		cRecherche*	lpObject	= add(query.value("id").toInt());

		lpObject->setName(query.value("name").toString());
		lpObject->setLink(query.value("link").toString());
		lpObject->setDescription(blob2TextDocument(query.value("description").toByteArray()));
	}

	query.prepare("SELECT rechercheID, name, image, description FROM rechercheImage;");
	if(!query.exec())
	{
		myDebug << query.lastError().text();
		return(false);
	}

	while(query.next())
	{
		cRecherche*	lpRecherche	= find(query.value("rechercheID").toInt());
		if(lpRecherche)
		{
			cImage*	lpImage	= new cImage;
			lpImage->setName(query.value("name").toString());
			lpImage->setDescription(blob2TextDocument(query.value("description").toByteArray()));
			lpImage->setImage(blob2Image(query.value("image").toByteArray()));
			lpRecherche->addImage(lpImage);
		}
	}

	query.prepare("SELECT rechercheID, characterID, description FROM rechercheCharacter;");
	if(!query.exec())
	{
		myDebug << query.lastError().text();
		return(false);
	}

	while(query.next())
	{
		cRecherche*	lpRecherche	= find(query.value("rechercheID").toInt());
		if(lpRecherche)
		{
			cCharacter*	lpCharacter		= lpCharacterList->find(query.value("characterID").toInt());
			if(lpCharacter)
				lpRecherche->addCharacter(lpCharacter, blob2TextDocument(query.value("description").toByteArray()));
		}
	}

	query.prepare("SELECT rechercheID, objectID, description FROM rechercheObject;");
	if(!query.exec())
	{
		myDebug << query.lastError().text();
		return(false);
	}

	while(query.next())
	{
		cRecherche*	lpRecherche	= find(query.value("rechercheID").toInt());
		if(lpRecherche)
		{
			cObject*	lpObject		= lpObjectList->find(query.value("objectID").toInt());
			if(lpObject)
				lpRecherche->addObject(lpObject, blob2TextDocument(query.value("description").toByteArray()));
		}
	}

	query.prepare("SELECT rechercheID, placeID, description FROM recherchePlace;");
	if(!query.exec())
	{
		myDebug << query.lastError().text();
		return(false);
	}

	while(query.next())
	{
		cRecherche*	lpRecherche	= find(query.value("rechercheID").toInt());
		if(lpRecherche)
		{
			cPlace*	lpPlace		= lpPlaceList->find(query.value("placeID").toInt());
			if(lpPlace)
				lpRecherche->addPlace(lpPlace, blob2TextDocument(query.value("description").toByteArray()));
		}
	}

	return(true);
}

bool cRechercheList::save()
{
	QSqlQuery	queryUpdate;
	QSqlQuery	queryInsert;
	QSqlQuery	querySelect;
	QSqlQuery	queryDelete;

	queryUpdate.prepare("UPDATE recherche SET name=:name, description=:description, link=:link WHERE id=:id;");
	queryInsert.prepare("INSERT INTO recherche (name, description, link) VALUES (:name, :description, :link);");
	querySelect.prepare("SELECT id FROM recherche WHERE _rowid_=(SELECT MAX(_rowid_) FROM recherche);");
	queryDelete.prepare("DELETE FROM recherche WHERE id=:id;");

	QSqlQuery	imageDelete;
	QSqlQuery	imageAdd;

	imageDelete.prepare("DELETE FROM rechercheImage WHERE rechercheID=:rechercheID;");
	imageAdd.prepare("INSERT INTO rechercheImage (rechercheID, name, description, image) VALUES (:rechercheID, :name, :description, :image);");

	QSqlQuery	characterDelete;
	QSqlQuery	characterAdd;
	characterDelete.prepare("DELETE FROM rechercheCharacter WHERE rechercheID=:rechercheID;");
	characterAdd.prepare("INSERT INTO rechercheCharacter (rechercheID, characterID, description) VALUES (:rechercheID, :characterID, :description);");

	QSqlQuery	objectDelete;
	QSqlQuery	objectAdd;
	objectDelete.prepare("DELETE FROM rechercheObject WHERE rechercheID=:rechercheID;");
	objectAdd.prepare("INSERT INTO rechercheObject (rechercheID, ObjectID, description) VALUES (:rechercheID, :objectID, :description);");

	QSqlQuery	placeDelete;
	QSqlQuery	placeAdd;
	placeDelete.prepare("DELETE FROM recherchePlace WHERE rechercheID=:rechercheID;");
	placeAdd.prepare("INSERT INTO recherchePlace (rechercheID, placeID, description) VALUES (:rechercheID, :placeID, :description);");

	cRechercheList::iterator	rechercheIterator	= begin();

	while(rechercheIterator != end())
	{
		cRecherche*	lpRecherche	= *rechercheIterator;

		imageDelete.bindValue(":rechercheID", lpRecherche->id());
		if(!imageDelete.exec())
		{
			myDebug << imageDelete.lastError().text();
			return(false);
		}

		characterDelete.bindValue(":rechercheID", lpRecherche->id());
		if(!characterDelete.exec())
		{
			myDebug << characterDelete.lastError().text();
			return(false);
		}

		objectDelete.bindValue(":rechercheID", lpRecherche->id());
		if(!objectDelete.exec())
		{
			myDebug << objectDelete.lastError().text();
			return(false);
		}

		placeDelete.bindValue(":rechercheID", lpRecherche->id());
		if(!placeDelete.exec())
		{
			myDebug << placeDelete.lastError().text();
			return(false);
		}

		if(lpRecherche->deleted())
		{
			queryDelete.bindValue(":id", lpRecherche->id());

			if(!queryDelete.exec())
			{
				myDebug << queryDelete.lastError().text();
				return(false);
			}
			lpRecherche	= 0;
		}
		else if(lpRecherche->id() != -1)
		{
			queryUpdate.bindValue(":id", lpRecherche->id());
			queryUpdate.bindValue(":name", lpRecherche->name());
			queryUpdate.bindValue(":link", lpRecherche->link());
			queryUpdate.bindValue(":description",  textDocument2Blob(lpRecherche->description()));

			if(!queryUpdate.exec())
			{
				myDebug << queryUpdate.lastError().text();
				return(false);
			}
		}
		else
		{
			queryInsert.bindValue(":name", lpRecherche->name());
			queryInsert.bindValue(":link", lpRecherche->link());
			queryInsert.bindValue(":description",  textDocument2Blob(lpRecherche->description()));

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
			lpRecherche->setID(querySelect.value("id").toInt());
		}

		if(!lpRecherche)
			rechercheIterator	= erase(rechercheIterator);
		else
		{
			QList<cImage*>	images	= lpRecherche->images();

			for(int x = 0;x < images.count();x++)
			{
				cImage*	lpImage	= images.at(x);

				imageAdd.bindValue(":rechercheID", lpRecherche->id());
				imageAdd.bindValue(":name", lpImage->name());
				imageAdd.bindValue(":description", textDocument2Blob(lpImage->description()));
				imageAdd.bindValue(":image", image2Blob(lpImage->image()));
				if(!imageAdd.exec())
				{
					myDebug << imageAdd.lastError().text();
					return(false);
				}
			}

			QList<cCharacterDescription*>	characters	= lpRecherche->characterList();

			for(int x = 0;x < characters.count();x++)
			{
				cCharacterDescription*	lpCharacterDescription	= characters.at(x);
				cCharacter*				lpCharacter				= lpCharacterDescription->character();

				characterAdd.bindValue(":rechercheID", lpRecherche->id());
				characterAdd.bindValue(":characterID", lpCharacter->id());
				characterAdd.bindValue(":description", textDocument2Blob(lpCharacterDescription->description()));
				if(!characterAdd.exec())
				{
					myDebug << characterAdd.lastError().text();
					return(false);
				}
			}

			QList<cObjectDescription*>	objects	= lpRecherche->objectList();

			for(int x = 0;x < objects.count();x++)
			{
				cObjectDescription*	lpObjectDescription	= objects.at(x);
				cObject*			lpObject			= lpObjectDescription->object();

				objectAdd.bindValue(":rechercheID", lpRecherche->id());
				objectAdd.bindValue(":objectID", lpObject->id());
				objectAdd.bindValue(":description", textDocument2Blob(lpObjectDescription->description()));
				if(!objectAdd.exec())
				{
					myDebug << objectAdd.lastError().text();
					return(false);
				}
			}

			QList<cPlaceDescription*>	places	= lpRecherche->placeList();

			for(int x = 0;x < places.count();x++)
			{
				cPlaceDescription*	lpPlaceDescription	= places.at(x);
				cPlace*				lpPlace				= lpPlaceDescription->place();

				placeAdd.bindValue(":rechercheID", lpRecherche->id());
				placeAdd.bindValue(":placeID", lpPlace->id());
				placeAdd.bindValue(":description", textDocument2Blob(lpPlaceDescription->description()));
				if(!placeAdd.exec())
				{
					myDebug << placeAdd.lastError().text();
					return(false);
				}
			}
			rechercheIterator++;
		}
	}

	return(true);
}
