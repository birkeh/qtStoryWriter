/*!
 \file cscene.cpp

*/

#include "cscene.h"

#include "common.h"

#include <QSqlQuery>
#include <QSqlError>

#include <QMutableListIterator>


cScene::cScene(qint32 iID, QObject *parent) :
	QObject(parent),
	m_iID(iID),
	m_lpChapter(0),
	m_szName(""),
	m_iSortOrder(-1),
	m_lpDescription(new cTextDocument(parent)),
	m_state(STATE::STATE_unknown),
	m_lpText(new cTextDocument(parent)),
	m_lpItem(0),
	m_lpStateItem(0),
	m_bDeleted(false)
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

void cScene::setSceneDate(const QDateTime& sceneDate)
{
	m_sceneDate	= sceneDate;
}

QDateTime cScene::sceneDate()
{
	return(m_sceneDate);
}

void cScene::setText(cTextDocument* lpText)
{
	m_lpText	= lpText;
}

cTextDocument* cScene::text()
{
	return(m_lpText);
}

void cScene::addCharacter(cCharacter* lpCharacter, cTextDocument* lpDescription)
{
	m_characterList.append(new cCharacterDescription(lpCharacter, lpDescription));
}

void cScene::removeCharacter(cCharacterDescription* lpCharacter)
{
	m_characterList.removeOne(lpCharacter);
}

QList<cCharacterDescription*> cScene::characterList()
{
	return(m_characterList);
}

void cScene::addObject(cObject* lpObject, cTextDocument* lpDescription)
{
	m_objectList.append(new cObjectDescription(lpObject, lpDescription));
}

void cScene::removeObject(cObjectDescription* lpObject)
{
	m_objectList.removeOne(lpObject);
}

QList<cObjectDescription*> cScene::objectList()
{
	return(m_objectList);
}

void cScene::addPlace(cPlace* lpPlace, cTextDocument* lpDescription)
{
	m_placeList.append(new cPlaceDescription(lpPlace, lpDescription));
}

void cScene::removePlace(cPlaceDescription* lpPlace)
{
	m_placeList.removeOne(lpPlace);
}

QList<cPlaceDescription*> cScene::placeList()
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

void cScene::setItem(QStandardItem* lpItem)
{
	m_lpItem	= lpItem;
}

QStandardItem* cScene::item()
{
	return(m_lpItem);
}

void cScene::setStateItem(QStandardItem* lpItem)
{
	m_lpStateItem	= lpItem;
}

QStandardItem* cScene::stateItem()
{
	return(m_lpStateItem);
}

void cScene::setDeleted(bool bDeleted)
{
	m_bDeleted	= bDeleted;
}

bool cScene::deleted()
{
	return(m_bDeleted);
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
	if(iID == -1)
		return(0);

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
		if(at(x)->chapter() == lpChapter && !at(x)->deleted())
			sceneList.append(at(x));
	}
	return(sceneList);
}

QList<cScene*> cSceneList::find(cCharacter* lpCharacter)
{
	QList<cScene*>	sceneList;

	for(int x = 0;x < count();x++)
	{
		QList<cCharacterDescription*>	list	= at(x)->characterList();

		for(int y = 0;y < list.count();y++)
		{
			if(list.at(y)->character() == lpCharacter)
			{
				sceneList.append(at(x));
				break;
			}
		}
	}
	return(sceneList);
}

QList<cScene*> cSceneList::find(cPlace* lpPlace)
{
	QList<cScene*>	sceneList;

	for(int x = 0;x < count();x++)
	{
		QList<cPlaceDescription*>	list	= at(x)->placeList();

		for(int y = 0;y < list.count();y++)
		{
			if(list.at(y)->place() == lpPlace)
			{
				sceneList.append(at(x));
				break;
			}
		}
	}
	return(sceneList);
}

QList<cScene*> cSceneList::find(cObject* lpObject)
{
	QList<cScene*>	sceneList;

	for(int x = 0;x < count();x++)
	{
		QList<cObjectDescription*>	list	= at(x)->objectList();

		for(int y = 0;y < list.count();y++)
		{
			if(list.at(y)->object() == lpObject)
			{
				sceneList.append(at(x));
				break;
			}
		}
	}
	return(sceneList);
}

qint32 cSceneList::nextSort(cChapter* lpChapter)
{
	qint32	iSort	= -1;

	for(int x = 0;x < count();x++)
	{
		if(lpChapter == at(x)->chapter() && iSort < at(x)->sortOrder())
			iSort	= at(x)->sortOrder();
	}
	return(iSort+1);
}

bool cSceneList::load(cChapterList* lpChapterList, cCharacterList *lpCharacterList, cObjectList *lpObjectList, cPlaceList *lpPlaceList)
{
	QSqlQuery	query;

	query.prepare("SELECT id, chapterID, name, sortOrder, description, state, startedAt, finishedAt, targetDate, sceneDate, text FROM scene ORDER BY sortOrder;");
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
		lpScene->setSceneDate(query.value("sceneDate").toDateTime());
		lpScene->setText(blob2TextDocument(query.value("text").toByteArray()));
	}

	query.prepare("SELECT sceneID, characterID, description FROM sceneCharacter;");
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
				lpScene->addCharacter(lpCharacter, blob2TextDocument(query.value("description").toByteArray()));
		}
	}

	query.prepare("SELECT sceneID, objectID, description FROM sceneObject;");
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
				lpScene->addObject(lpObject, blob2TextDocument(query.value("description").toByteArray()));
		}
	}

	query.prepare("SELECT sceneID, placeID, description FROM scenePlace;");
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
				lpScene->addPlace(lpPlace, blob2TextDocument(query.value("description").toByteArray()));
		}
	}

	return(true);
}

bool cSceneList::save()
{
	QSqlQuery	queryUpdate;
	QSqlQuery	queryInsert;
	QSqlQuery	querySelect;
	QSqlQuery	queryDelete;

	queryUpdate.prepare("UPDATE scene SET name=:name, chapterID=:chapterID, sortOrder=:sortOrder, description=:description, state=:state, startedAt=:startedAt, finishedAt=:finishedAt, targetDate=:targetDate, sceneDate=:sceneDate, text=:text WHERE id=:id;");
	queryInsert.prepare("INSERT INTO scene (name, chapterID, sortOrder, description, state, startedAt, finishedAt, targetDate, sceneDate, text) VALUES (:name, :chapterID, :sortOrder, :description, :state, :startedAt, :finishedAt, :targetDate, :sceneDate, :text);");
	querySelect.prepare("SELECT id FROM scene WHERE _rowid_=(SELECT MAX(_rowid_) FROM scene);");
	queryDelete.prepare("DELETE FROM scene WHERE id=:id;");

	QSqlQuery	characterDelete;
	QSqlQuery	characterAdd;

	characterDelete.prepare("DELETE FROM sceneCharacter WHERE sceneID=:sceneID;");
	characterAdd.prepare("INSERT INTO sceneCharacter (sceneID, characterID, description) VALUES (:sceneID, :characterID, :description);");

	QSqlQuery	placeDelete;
	QSqlQuery	placeAdd;

	placeDelete.prepare("DELETE FROM scenePlace WHERE sceneID=:sceneID;");
	placeAdd.prepare("INSERT INTO scenePlace (sceneID, placeID, description) VALUES (:sceneID, :placeID, :description);");

	QSqlQuery	objectDelete;
	QSqlQuery	objectAdd;

	objectDelete.prepare("DELETE FROM sceneObject WHERE sceneID=:sceneID;");
	objectAdd.prepare("INSERT INTO sceneObject (sceneID, objectID, description) VALUES (:sceneID, :objectID, :description);");

	cSceneList::iterator	sceneIterator	= begin();

	while(sceneIterator != end())
	{
		cScene*	lpScene		= *sceneIterator;

		characterDelete.bindValue(":sceneID", lpScene->id());
		if(!characterDelete.exec())
		{
			myDebug << characterDelete.lastError().text();
			return(false);
		}

		placeDelete.bindValue(":sceneID", lpScene->id());
		if(!placeDelete.exec())
		{
			myDebug << placeDelete.lastError().text();
			return(false);
		}

		objectDelete.bindValue(":sceneID", lpScene->id());
		if(!objectDelete.exec())
		{
			myDebug << objectDelete.lastError().text();
			return(false);
		}

		if(lpScene->deleted())
		{
			queryDelete.bindValue(":id", lpScene->id());

			if(!queryDelete.exec())
			{
				myDebug << queryDelete.lastError().text();
				return(false);
			}
			lpScene	= 0;
		}
		else if(lpScene->id() != -1)
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
			queryUpdate.bindValue(":sceneDate", lpScene->sceneDate());
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
			queryInsert.bindValue(":sceneDate", lpScene->sceneDate());
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

		if(!lpScene)
			sceneIterator	= erase(sceneIterator);
		else
		{
			QList<cCharacterDescription*>	character	= lpScene->characterList();

			for(int x = 0;x < character.count();x++)
			{
				cCharacterDescription*	lpCharacter	= character.at(x);

				characterAdd.bindValue(":sceneID", lpScene->id());
				characterAdd.bindValue(":characterID", lpCharacter->character()->id());
				characterAdd.bindValue(":description", textDocument2Blob(lpCharacter->description()));

				if(!characterAdd.exec())
				{
					myDebug << characterAdd.lastError().text();
					return(false);
				}
			}

			QList<cPlaceDescription*>	place	= lpScene->placeList();

			for(int x = 0;x < place.count();x++)
			{
				cPlaceDescription*	lpPlace = place.at(x);

				placeAdd.bindValue(":sceneID", lpScene->id());
				placeAdd.bindValue(":placeID", lpPlace->place()->id());
				placeAdd.bindValue(":description", textDocument2Blob(lpPlace->description()));

				if(!placeAdd.exec())
				{
					myDebug << placeAdd.lastError().text();
					return(false);
				}
			}

			QList<cObjectDescription*>	object	= lpScene->objectList();

			for(int x = 0;x < object.count();x++)
			{
				cObjectDescription*	lpObject	= object.at(x);

				objectAdd.bindValue(":sceneID", lpScene->id());
				objectAdd.bindValue(":objectID", lpObject->object()->id());
				objectAdd.bindValue(":description", textDocument2Blob(lpObject->description()));

				if(!objectAdd.exec())
				{
					myDebug << objectAdd.lastError().text();
					return(false);
				}
			}
			sceneIterator++;
		}
	}

	return(true);
}
