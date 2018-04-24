#ifndef CSCENE_H
#define CSCENE_H


#include "cchapter.h"
#include "ctextdocument.h"
#include "ccharacter.h"
#include "cobject.h"
#include "cplace.h"

#include <QMetaType>
#include <QList>
#include <QString>
#include <QDateTime>
#include <QColor>
#include <QObject>


class cScene : public QObject
{
	Q_OBJECT

public:
	enum STATE
	{
		STATE_unknown	= 0,
		STATE_init		= 1,
		STATE_progress	= 2,
		STATE_delayed	= 3,
		STATE_finished	= 4,
	};

	explicit cScene(qint32 iID = -1, QObject *parent = nullptr);

	void				setID(const qint32& iID);
	qint32				id();

	void				setChapter(cChapter *lpChapter);
	cChapter*			chapter();

	void				setName(const QString& szName);
	QString				name();

	void				setSortOrder(const qint32& iSortOrder);
	qint32				sortOrder();

	void				setDescription(cTextDocument* lpDescription);
	cTextDocument*		description();

	void				setState(const STATE state);
	STATE				state();

	void				setStartedAt(const QDateTime& startedAt);
	QDateTime			startedAt();

	void				setFinishedAt(const QDateTime& finishedAt);
	QDateTime			finishedAt();

	void				setTargetDate(const QDateTime& targetDate);
	QDateTime			targetDate();

	void				setText(cTextDocument* lpText);
	cTextDocument*		text();

	void				addCharacter(cCharacter* lpCharacter);
	QList<cCharacter*>	characterList();

	void				addObject(cObject* lpObject);
	QList<cObject*>		objectList();

	void				addPlace(cPlace* lpPlace);
	QList<cPlace*>		placeList();

	QString				stateText();
	static QString		stateText(STATE state);
	QColor				stateColor();
	static QColor		stateColor(STATE state);
private:
	qint32				m_iID;
	cChapter*			m_lpChapter;
	QString				m_szName;
	qint32				m_iSortOrder;
	cTextDocument*		m_lpDescription;
	STATE				m_state;
	QDateTime			m_startedAt;
	QDateTime			m_finishedAt;
	QDateTime			m_targetDate;
	cTextDocument*		m_lpText;
	QList<cCharacter*>	m_characterList;
	QList<cObject*>		m_objectList;
	QList<cPlace*>		m_placeList;
};

Q_DECLARE_METATYPE(cScene*)

class cSceneList : public QList<cScene*>
{
public:
	bool				load(cChapterList *lpChapterList, cCharacterList* lpCharacterList, cObjectList* lpObjectList, cPlaceList* lpPlaceList);
	bool				save();

	cScene*				add(const qint32& iID);
	cScene*				find(const qint32& iID);

	QList<cScene*>		find(cChapter* lpChapter);
};

#endif // CSCENE_H
