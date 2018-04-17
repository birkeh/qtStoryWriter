#ifndef CSCENE_H
#define CSCENE_H


#include "cchapter.h"

#include <QMetaType>
#include <QList>
#include <QString>
#include <QDateTime>


class cScene
{
public:
	enum STATE
	{
		STATE_unknown	= 0,
		STATE_init		= 1,
		STATE_progress	= 2,
		STATE_delayed	= 3,
		STATE_finished	= 4,
	};

	cScene(qint32 iID = -1);

	void			setID(const qint32& iID);
	qint32			id();

	void			setChapter(cChapter *lpChapter);
	cChapter*		chapter();

	void			setName(const QString& szName);
	QString			name();

	void			setSortOrder(const qint32& iSortOrder);
	qint32			sortOrder();

	void			setDescription(const QString& szDescription);
	QString			description();

	void			setState(const STATE state);
	STATE			state();

	void			setStartedAt(const QDateTime& startedAt);
	QDateTime		startedAt();

	void			setFinishedAt(const QDateTime& finishedAt);
	QDateTime		finishedAt();

	void			setTargetDate(const QDateTime& targetDate);
	QDateTime		targetDate();

	void			setFile(const QString& szFile);
	QString			file();

private:
	qint32			m_iID;
	cChapter*		m_lpChapter;
	QString			m_szName;
	qint32			m_iSortOrder;
	QString			m_szDescription;
	STATE			m_state;
	QDateTime		m_startedAt;
	QDateTime		m_finishedAt;
	QDateTime		m_targetDate;
	QString			m_szFile;
};

Q_DECLARE_METATYPE(cScene*)

class cSceneList : public QList<cScene*>
{
public:
	bool			load(cChapterList *lpChapterList);
	bool			save();

	cScene*			add(const qint32& iID);
	cScene*			find(const qint32& iID);
};

#endif // CSCENE_H
