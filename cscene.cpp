#include "cscene.h"

#include "common.h"

#include <QSqlQuery>
#include <QSqlError>


cScene::cScene(qint32 iID) :
	m_iID(iID),
	m_lpChapter(0),
	m_szName(""),
	m_iSortOrder(-1),
	m_szDescription(""),
	m_state(STATE::STATE_unknown),
	m_szFile("")
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

void cScene::setDescription(const QString& szDescription)
{
	m_szDescription	= szDescription;
}

QString cScene::description()
{
	return(m_szDescription);
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

void cScene::setFile(const QString& szFile)
{
	m_szFile	= szFile;
}

QString cScene::file()
{
	return(m_szFile);
}

QString cScene::stateText()
{
	return(stateText(m_state));
}

QString cScene::stateText(STATE state) const
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

QColor cScene::stateColor(STATE state) const
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

bool cSceneList::load(cChapterList* lpChapterList)
{
	QSqlQuery	query;

	query.prepare("SELECT id, chapterID, name, sortOrder, description, state, startedAt, finishedAt, targetDate, file FROM scene ORDER BY sortOrder;");
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
		lpScene->setDescription(query.value("description").toString());
		lpScene->setState((cScene::STATE)query.value("state").toInt());
		lpScene->setStartedAt(query.value("startedAt").toDateTime());
		lpScene->setFinishedAt(query.value("finishedAt").toDateTime());
		lpScene->setTargetDate(query.value("targetDate").toDateTime());
		lpScene->setFile(query.value("file").toString());
	}

	return(true);
}

bool cSceneList::save()
{
	return(true);
}
