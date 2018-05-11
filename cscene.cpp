/*!
 \file cscene.cpp

*/

#include "cscene.h"

#include "common.h"

#include <QSqlQuery>
#include <QSqlError>


cScene::cScene(qint32 iID, QObject *parent) :
	QObject(parent),
	m_iID(iID),
	m_lpChapter(0),
	m_szName(""),
	m_iSortOrder(-1),
	m_lpDescription(0),
	m_state(STATE::STATE_unknown),
	m_lpText(0)
{
}

void cScene::setID(const qint32& iID)
{
	m_iID	= iID;
}

qint32 cScene::id()
{
	return(m_iID);
}

void cScene::setChapter(cChapter* lpChapter)
{
	m_lpChapter	= lpChapter;
}

cChapter* cScene::chapter()
{
	return(m_lpChapter);
}

void cScene::setName(const QString& szName)
{
	m_szName	= szName;
}

QString cScene::name()
{
	return(m_szName);
}

void cScene::setSortOrder(const qint32& iSortOrder)
{
	m_iSortOrder	= iSortOrder;
}

qint32 cScene::sortOrder()
{
	return(m_iSortOrder);
}

void cScene::setDescription(cTextDocument* lpDescription)
{
	m_lpDescription	= lpDescription;
}

cTextDocument* cScene::description()
{
	return(m_lpDescription);
}

void cScene::setState(const cScene::STATE state)
{
	m_state	= state;
}

cScene::STATE cScene::state()
{
	return(m_state);
}

void cScene::setStartedAt(const QDateTime& startedAt)
{
	m_startedAt	= startedAt;
}

QDateTime cScene::startedAt()
{
	return(m_startedAt);
}

void cScene::setFinishedAt(const QDateTime& finishedAt)
{
	m_finishedAt	= finishedAt;
}

QDateTime cScene::finishedAt()
{
	return(m_finishedAt);
}

void cScene::setTargetDate(const QDateTime& targetDate)
{
	m_targetDate	= targetDate;
}

QDateTime cScene::targetDate()
{
	return(m_targetDate);
}

void cScene::setText(cTextDocument* lpText)
{
	m_lpText	= lpText;
}

cTextDocument* cScene::text()
{
	return(m_lpText);
}

void cScene::addCharacter(cCharacter* lpCharacter)
{
	if(m_characterList.contains(lpCharacter))
		return;
	m_characterList.append(lpCharacter);
}

QList<cCharacter*> cScene::characterList()
{
	return(m_characterList);
}

void cScene::addObject(cObject* lpObject)
{
	if(m_objectList.contains(lpObject))
		return;
	m_objectList.append(lpObject);
}

QList<cObject*> cScene::objectList()
{
	return(m_objectList);
}

void cScene::addPlace(cPlace* lpPlace)
{
	if(m_placeList.contains(lpPlace))
		return;
	m_placeList.append(lpPlace);
}

QList<cPlace*> cScene::placeList()
{
	return(m_placeList);
}

QString cScene::stateText()
{
	return(stateText(m_state));
}

QString cScene::stateText(STATE state)
{
	switch(state)
	{
	case cScene::STATE::STATE_unknown:
		return(tr("unknown"));
	case cScene::STATE::STATE_init:
		return(tr("initialized"));
	case cScene::STATE::STATE_progress:
		return(tr("progress"));
	case cScene::STATE::STATE_delayed:
		return(tr("delayed"));
	case cScene::STATE::STATE_finished:
		return(tr("finished"));
	}
	return("unknown");
}

QColor cScene::stateColor()
{
	return(stateColor(m_state));
}

QColor cScene::stateColor(STATE state)
{
	switch(state)
	{
	case cScene::STATE::STATE_unknown:
		return(Qt::red);
	case cScene::STATE::STATE_init:
		return(QColor(127, 127, 255));
	case cScene::STATE::STATE_progress:
		return(QColor(127, 255, 127));
	case cScene::STATE::STATE_delayed:
		return(Qt::yellow);
	case cScene::STATE::STATE_finished:
		return(Qt::green);
	}
	return(Qt::darkRed);
}

cScene* cSceneList::add(const qint32& iID)
{
	cScene*	lpScene	= find(iID);

	if(!lpScene)
	{
		lpScene	= new cScene(iID);
		append(lpScene);
	}

	return(lpScene);
}

cScene* cSceneList::find(const qint32& iID)
{
	for(int x = 0;x < count();x++)
	{
		if(at(x)->id() == iID)
			return(at(x));
	}

	return(0);
}

QList<cScene*> cSceneList::find(cChapter* lpChapter)
{
	QList<cScene*>	sceneList;

	for(int x = 0;x < count();x++)
	{
		if(at(x)->chapter() == lpChapter)
			sceneList.append(at(x));
	}
	return(sceneList);
}

bool cSceneList::load(cChapterList* lpChapterList, cCharacterList *lpCharacterList, cObjectList *lpObjectList, cPlaceList *lpPlaceList)
{
	QSqlQuery	query;

	query.prepare("SELECT id, chapterID, name, sortOrder, description, state, startedAt, finishedAt, targetDate, text FROM scene ORDER BY sortOrder;");
	if(!query.exec())
	{
		myDebug << query.lastError().text();
		return(false);
	}

	while(query.next())
	{
		cScene*	lpScene	= add(query.value("id").toInt());

		lpScene->setChapter(lpChapterList->find(query.value("chapterID").toInt()));
		lpScene->setName(query.value("name").toString());
		lpScene->setSortOrder(query.value("sortOrder").toInt());
		lpScene->setDescription(blob2TextDocument(query.value("description").toByteArray()));
		lpScene->setState((cScene::STATE)query.value("state").toInt());
		lpScene->setStartedAt(query.value("startedAt").toDateTime());
		lpScene->setFinishedAt(query.value("finishedAt").toDateTime());
		lpScene->setTargetDate(query.value("targetDate").toDateTime());
		lpScene->setText(blob2TextDocument(query.value("text").toByteArray()));
	}

	query.prepare("SELECT sceneID, characterID FROM sceneCharacter;");
	if(!query.exec())
	{
		myDebug << query.lastError().text();
		return(false);
	}

	while(query.next())
	{
		cScene*	lpScene	= find(query.value("sceneID").toInt());
		if(lpScene)
		{
			cCharacter*	lpCharacter		= lpCharacterList->find(query.value("characterID").toInt());
			if(lpCharacter)
				lpScene->addCharacter(lpCharacter);
		}
	}

	query.prepare("SELECT sceneID, objectID FROM sceneObject;");
	if(!query.exec())
	{
		myDebug << query.lastError().text();
		return(false);
	}

	while(query.next())
	{
		cScene*	lpScene	= find(query.value("sceneID").toInt());
		if(lpScene)
		{
			cObject*	lpObject		= lpObjectList->find(query.value("objectID").toInt());
			if(lpObject)
				lpScene->addObject(lpObject);
		}
	}

	query.prepare("SELECT sceneID, placeID FROM scenePlace;");
	if(!query.exec())
	{
		myDebug << query.lastError().text();
		return(false);
	}

	while(query.next())
	{
		cScene*	lpScene	= find(query.value("sceneID").toInt());
		if(lpScene)
		{
			cPlace*	lpPlace		= lpPlaceList->find(query.value("placeID").toInt());
			if(lpPlace)
				lpScene->addPlace(lpPlace);
		}
	}

	return(true);
}

bool cSceneList::save()
{
	QSqlQuery	queryUpdate;
	QSqlQuery	queryInsert;
	QSqlQuery	querySelect;

	queryUpdate.prepare("UPDATE scene SET name=:name, chapterID=:chapterID, sortOrder=:sortOrder, description=:description, state=:state, startedAt=:startedAt, finishedAt=:finishedAt, targetDate=:targetDate, text=:text WHERE id=:id;");
	queryInsert.prepare("INSERT INTO scene (name, chapterID, sortOrder, description, state, startedAt, finishedAt, targetDate, text) VALUES (:name, :chapterID, :sortOrder, :description, :state, :startedAt, :finishedAt, :targetDate, :text);");
	querySelect.prepare("SELECT id FROM scene WHERE _rowid_=(SELECT MAX(_rowid_) FROM part);");

	for(int x = 0;x < count();x++)
	{
		cScene*	lpScene	= at(x);

		if(lpScene->id() != -1)
		{
			queryUpdate.bindValue(":id", lpScene->id());
			queryUpdate.bindValue(":name", lpScene->name());
			queryUpdate.bindValue(":chapterID", lpScene->chapter()->id());
			queryUpdate.bindValue(":sortOrder", lpScene->sortOrder());
			queryUpdate.bindValue(":description",  textDocument2Blob(lpScene->description()));
			queryUpdate.bindValue(":state", lpScene->state());
			queryUpdate.bindValue(":startedAt", lpScene->startedAt());
			queryUpdate.bindValue(":finishedAt", lpScene->finishedAt());
			queryUpdate.bindValue(":targetDate", lpScene->targetDate());
			queryUpdate.bindValue(":text",  textDocument2Blob(lpScene->text()));

			if(!queryUpdate.exec())
			{
				myDebug << queryUpdate.lastError().text();
				return(false);
			}
		}
		else
		{
			queryInsert.bindValue(":name", lpScene->name());
			queryInsert.bindValue(":chapterID", lpScene->chapter()->id());
			queryInsert.bindValue(":sortOrder", lpScene->sortOrder());
			queryInsert.bindValue(":description",  textDocument2Blob(lpScene->description()));
			queryInsert.bindValue(":state", lpScene->state());
			queryInsert.bindValue(":startedAt", lpScene->startedAt());
			queryInsert.bindValue(":finishedAt", lpScene->finishedAt());
			queryInsert.bindValue(":targetDate", lpScene->targetDate());
			queryInsert.bindValue(":text",  textDocument2Blob(lpScene->text()));

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
			lpScene->setID(querySelect.value("id").toInt());
		}
	}

	return(true);
}
