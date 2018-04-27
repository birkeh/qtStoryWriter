#include "crecherche.h"

#include "common.h"

#include <QSqlQuery>
#include <QSqlError>


cRecherche::cRecherche(qint32 iID, QObject *parent) :
	QObject(parent),
	m_iID(iID),
	m_szName(""),
	m_szLink(""),
	m_lpDescription(0)
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

void cRecherche::addImage(cImage* lpImage)
{
	if(m_imageList.contains(lpImage))
		return;
	m_imageList.append(lpImage);
}

void cRecherche::addCharacter(cCharacter* lpCharacter)
{
	if(m_characterList.contains(lpCharacter))
		return;
	m_characterList.append(lpCharacter);
}

void cRecherche::addObject(cObject* lpObject)
{
	if(m_objectList.contains(lpObject))
		return;
	m_objectList.append(lpObject);
}

void cRecherche::addPlace(cPlace* lpPlace)
{
	if(m_placeList.contains(lpPlace))
		return;
	m_placeList.append(lpPlace);
}

QList<cImage*> cRecherche::images()
{
	return(m_imageList);
}

QList<cCharacter*> cRecherche::characterList()
{
	return(m_characterList);
}

QList<cObject*> cRecherche::objectList()
{
	return(m_objectList);
}

QList<cPlace*> cRecherche::placeList()
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
	for(int x = 0;x < count();x++)
	{
		if(at(x)->id() == iID)
			return(at(x));
	}

	return(0);
}

bool cRechercheList::load(cImageList *lpImageList, cCharacterList *lpCharacterList, cObjectList *lpObjectList, cPlaceList *lpPlaceList)
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

	query.prepare("SELECT rechercheID, imageID FROM rechercheImage;");
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
			cImage*	lpImage		= lpImageList->find(query.value("imageID").toInt());
			if(lpImage)
				lpRecherche->addImage(lpImage);
		}
	}

	query.prepare("SELECT rechercheID, characterID FROM rechercheCharacter;");
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
				lpRecherche->addCharacter(lpCharacter);
		}
	}

	query.prepare("SELECT rechercheID, objectID FROM rechercheObject;");
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
				lpRecherche->addObject(lpObject);
		}
	}

	query.prepare("SELECT rechercheID, placeID FROM recherchePlace;");
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
				lpRecherche->addPlace(lpPlace);
		}
	}

	return(true);
}

bool cRechercheList::save()
{
	return(true);
}
