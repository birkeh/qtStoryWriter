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

bool cRechercheList::load()
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

	return(true);
}

bool cRechercheList::save()
{
	return(true);
}
