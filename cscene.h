/*!
 \file cscene.h

*/

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


/*!
 \brief

 \class cScene cscene.h "cscene.h"
*/
class cScene : public QObject
{
	Q_OBJECT

public:
	/*!
	 \brief

	 \enum STATE
	*/
	enum STATE
	{
		STATE_unknown	= 0,
		STATE_init		= 1,
		STATE_progress	= 2,
		STATE_delayed	= 3,
		STATE_finished	= 4,
	};

	/*!
	 \brief

	 \fn cScene
	 \param iID
	 \param parent
	*/
	explicit cScene(qint32 iID = -1, QObject *parent = nullptr);

	/*!
	 \brief

	 \fn setID
	 \param iID
	*/
	void				setID(const qint32& iID);
	/*!
	 \brief

	 \fn id
	 \return qint32
	*/
	qint32				id();

	/*!
	 \brief

	 \fn setChapter
	 \param lpChapter
	*/
	void				setChapter(cChapter *lpChapter);
	/*!
	 \brief

	 \fn chapter
	 \return cChapter
	*/
	cChapter*			chapter();

	/*!
	 \brief

	 \fn setName
	 \param szName
	*/
	void				setName(const QString& szName);
	/*!
	 \brief

	 \fn name
	 \return QString
	*/
	QString				name();

	/*!
	 \brief

	 \fn setSortOrder
	 \param iSortOrder
	*/
	void				setSortOrder(const qint32& iSortOrder);
	/*!
	 \brief

	 \fn sortOrder
	 \return qint32
	*/
	qint32				sortOrder();

	/*!
	 \brief

	 \fn setDescription
	 \param lpDescription
	*/
	void				setDescription(cTextDocument* lpDescription);
	/*!
	 \brief

	 \fn description
	 \return cTextDocument
	*/
	cTextDocument*		description();

	/*!
	 \brief

	 \fn setState
	 \param state
	*/
	void				setState(const STATE state);
	/*!
	 \brief

	 \fn state
	 \return STATE
	*/
	STATE				state();

	/*!
	 \brief

	 \fn setStartedAt
	 \param startedAt
	*/
	void				setStartedAt(const QDateTime& startedAt);
	/*!
	 \brief

	 \fn startedAt
	 \return QDateTime
	*/
	QDateTime			startedAt();

	/*!
	 \brief

	 \fn setFinishedAt
	 \param finishedAt
	*/
	void				setFinishedAt(const QDateTime& finishedAt);
	/*!
	 \brief

	 \fn finishedAt
	 \return QDateTime
	*/
	QDateTime			finishedAt();

	/*!
	 \brief

	 \fn setTargetDate
	 \param targetDate
	*/
	void				setTargetDate(const QDateTime& targetDate);
	/*!
	 \brief

	 \fn targetDate
	 \return QDateTime
	*/
	QDateTime			targetDate();

	/*!
	 \brief

	 \fn setText
	 \param lpText
	*/
	void				setText(cTextDocument* lpText);
	/*!
	 \brief

	 \fn text
	 \return cTextDocument
	*/
	cTextDocument*		text();

	/*!
	 \brief

	 \fn addCharacter
	 \param lpCharacter
	*/
	void				addCharacter(cCharacter* lpCharacter);
	/*!
	 \brief

	 \fn characterList
	 \return QList<cCharacter *>
	*/
	QList<cCharacter*>	characterList();

	/*!
	 \brief

	 \fn addObject
	 \param lpObject
	*/
	void				addObject(cObject* lpObject);
	/*!
	 \brief

	 \fn objectList
	 \return QList<cObject *>
	*/
	QList<cObject*>		objectList();

	/*!
	 \brief

	 \fn addPlace
	 \param lpPlace
	*/
	void				addPlace(cPlace* lpPlace);
	/*!
	 \brief

	 \fn placeList
	 \return QList<cPlace *>
	*/
	QList<cPlace*>		placeList();

	/*!
	 \brief

	 \fn stateText
	 \return QString
	*/
	QString				stateText();
	/*!
	 \brief

	 \fn stateText
	 \param state
	 \return QString
	*/
	static QString		stateText(STATE state);
	/*!
	 \brief

	 \fn stateColor
	 \return QColor
	*/
	QColor				stateColor();
	/*!
	 \brief

	 \fn stateColor
	 \param state
	 \return QColor
	*/
	static QColor		stateColor(STATE state);

	/*!
	 \brief

	 \fn setItem
	 \param lpItem
	*/
	void				setItem(QStandardItem* lpItem);
	/*!
	 \brief

	 \fn item
	 \return QStandardItem
	*/
	QStandardItem*		item();

	/*!
	 \brief

	 \fn setStateItem
	 \param lpItem
	*/
	void				setStateItem(QStandardItem* lpItem);
	/*!
	 \brief

	 \fn stateItem
	 \return QStandardItem
	*/
	QStandardItem*		stateItem();

	/*!
	 \brief

	 \fn setDeleted
	 \param bDeleted
	*/
	void				setDeleted(bool bDeleted);
	/*!
	 \brief

	 \fn deleted
	 \return bool
	*/
	bool				deleted();

private:
	qint32				m_iID; /*!< TODO: describe */
	cChapter*			m_lpChapter; /*!< TODO: describe */
	QString				m_szName; /*!< TODO: describe */
	qint32				m_iSortOrder; /*!< TODO: describe */
	cTextDocument*		m_lpDescription; /*!< TODO: describe */
	STATE				m_state; /*!< TODO: describe */
	QDateTime			m_startedAt; /*!< TODO: describe */
	QDateTime			m_finishedAt; /*!< TODO: describe */
	QDateTime			m_targetDate; /*!< TODO: describe */
	cTextDocument*		m_lpText; /*!< TODO: describe */
	QList<cCharacter*>	m_characterList; /*!< TODO: describe */
	QList<cObject*>		m_objectList; /*!< TODO: describe */
	QList<cPlace*>		m_placeList; /*!< TODO: describe */
	QStandardItem*		m_lpItem; /*!< TODO: describe */
	QStandardItem*		m_lpStateItem; /*!< TODO: describe */
	bool				m_bDeleted; /*!< TODO: describe */
};

Q_DECLARE_METATYPE(cScene*)

/*!
 \brief

 \class cSceneList cscene.h "cscene.h"
*/
class cSceneList : public QList<cScene*>
{
public:
	/*!
	 \brief

	 \fn load
	 \param lpChapterList
	 \param lpCharacterList
	 \param lpObjectList
	 \param lpPlaceList
	 \return bool
	*/
	bool				load(cChapterList *lpChapterList, cCharacterList* lpCharacterList, cObjectList* lpObjectList, cPlaceList* lpPlaceList);
	/*!
	 \brief

	 \fn save
	 \return bool
	*/
	bool				save();

	/*!
	 \brief

	 \fn add
	 \param iID
	 \return cScene
	*/
	cScene*				add(const qint32& iID);
	/*!
	 \brief

	 \fn find
	 \param iID
	 \return cScene
	*/
	cScene*				find(const qint32& iID);

	/*!
	 \brief

	 \fn find
	 \param lpChapter
	 \return QList<cScene *>
	*/
	QList<cScene*>		find(cChapter* lpChapter);

	/*!
	 \brief

	 \fn nextSort
	 \param lpPart
	 \return cPart
	*/
	qint32				nextSort(cChapter* lpChapter);
};

#endif // CSCENE_H
