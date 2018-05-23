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
		STATE_unknown	= 0, /*!< TODO: describe */
		STATE_init		= 1, /*!< TODO: describe */
		STATE_progress	= 2, /*!< TODO: describe */
		STATE_delayed	= 3, /*!< TODO: describe */
		STATE_finished	= 4, /*!< TODO: describe */
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
	void							setID(const qint32& iID);
	/*!
	 \brief

	 \fn id
	 \return qint32
	*/
	qint32							id();

	/*!
	 \brief

	 \fn setChapter
	 \param lpChapter
	*/
	void							setChapter(cChapter *lpChapter);
	/*!
	 \brief

	 \fn chapter
	 \return cChapter
	*/
	cChapter*						chapter();

	/*!
	 \brief

	 \fn setName
	 \param szName
	*/
	void							setName(const QString& szName);
	/*!
	 \brief

	 \fn name
	 \return QString
	*/
	QString							name();

	/*!
	 \brief

	 \fn setSortOrder
	 \param iSortOrder
	*/
	void							setSortOrder(const qint32& iSortOrder);
	/*!
	 \brief

	 \fn sortOrder
	 \return qint32
	*/
	qint32							sortOrder();

	/*!
	 \brief

	 \fn setDescription
	 \param lpDescription
	*/
	void							setDescription(cTextDocument* lpDescription);
	/*!
	 \brief

	 \fn description
	 \return cTextDocument
	*/
	cTextDocument*					description();

	/*!
	 \brief

	 \fn setState
	 \param state
	*/
	void							setState(const STATE state);
	/*!
	 \brief

	 \fn state
	 \return STATE
	*/
	STATE							state();

	/*!
	 \brief

	 \fn setStartedAt
	 \param startedAt
	*/
	void							setStartedAt(const QDateTime& startedAt);
	/*!
	 \brief

	 \fn startedAt
	 \return QDateTime
	*/
	QDateTime						startedAt();

	/*!
	 \brief

	 \fn setFinishedAt
	 \param finishedAt
	*/
	void							setFinishedAt(const QDateTime& finishedAt);
	/*!
	 \brief

	 \fn finishedAt
	 \return QDateTime
	*/
	QDateTime						finishedAt();

	/*!
	 \brief

	 \fn setTargetDate
	 \param targetDate
	*/
	void							setTargetDate(const QDateTime& targetDate);
	/*!
	 \brief

	 \fn targetDate
	 \return QDateTime
	*/
	QDateTime						targetDate();

	/*!
	 \brief

	 \fn setText
	 \param lpText
	*/
	void							setText(cTextDocument* lpText);
	/*!
	 \brief

	 \fn text
	 \return cTextDocument
	*/
	cTextDocument*					text();

	/*!
	 \brief

	 \fn addCharacter
	 \param lpCharacter
	 \param lpDescription
	*/
	void							addCharacter(cCharacter* lpCharacter, cTextDocument* lpDescription);
	/*!
	 \brief

	 \fn addCharacter
	 \param lpCharacter
	 \param lpDescription
	*/
	void							removeCharacter(cCharacterDescription* lpCharacter);
	/*!
	 \brief

	 \fn characterList
	 \return QList<cCharacter *>
	*/
	QList<cCharacterDescription*>	characterList();

	/*!
	 \brief

	 \fn addObject
	 \param lpObject
	 \param lpDescription
	*/
	void							addObject(cObject* lpObject, cTextDocument* lpDescription);
	/*!
	 \brief

	 \fn objectList
	 \return QList<cObject *>
	*/
	QList<cObjectDescription*>		objectList();

	/*!
	 \brief

	 \fn addPlace
	 \param lpPlace
	 \param lpDescription
	*/
	void							addPlace(cPlace* lpPlace, cTextDocument* lpDescription);
	/*!
	 \brief

	 \fn placeList
	 \return QList<cPlace *>
	*/
	QList<cPlaceDescription*>		placeList();

	/*!
	 \brief

	 \fn stateText
	 \return QString
	*/
	QString							stateText();
	/*!
	 \brief

	 \fn stateText
	 \param state
	 \return QString
	*/
	static QString					stateText(STATE state);
	/*!
	 \brief

	 \fn stateColor
	 \return QColor
	*/
	QColor							stateColor();
	/*!
	 \brief

	 \fn stateColor
	 \param state
	 \return QColor
	*/
	static QColor					stateColor(STATE state);

	/*!
	 \brief

	 \fn setItem
	 \param lpItem
	*/
	void							setItem(QStandardItem* lpItem);
	/*!
	 \brief

	 \fn item
	 \return QStandardItem
	*/
	QStandardItem*					item();

	/*!
	 \brief

	 \fn setStateItem
	 \param lpItem
	*/
	void							setStateItem(QStandardItem* lpItem);
	/*!
	 \brief

	 \fn stateItem
	 \return QStandardItem
	*/
	QStandardItem*					stateItem();

	/*!
	 \brief

	 \fn setDeleted
	 \param bDeleted
	*/
	void							setDeleted(bool bDeleted);
	/*!
	 \brief

	 \fn deleted
	 \return bool
	*/
	bool							deleted();

private:
	qint32							m_iID;				/*!< TODO: describe */
	cChapter*						m_lpChapter;		/*!< TODO: describe */
	QString							m_szName;			/*!< TODO: describe */
	qint32							m_iSortOrder;		/*!< TODO: describe */
	cTextDocument*					m_lpDescription;	/*!< TODO: describe */
	STATE							m_state;			/*!< TODO: describe */
	QDateTime						m_startedAt;		/*!< TODO: describe */
	QDateTime						m_finishedAt;		/*!< TODO: describe */
	QDateTime						m_targetDate;		/*!< TODO: describe */
	cTextDocument*					m_lpText;			/*!< TODO: describe */
	QList<cCharacterDescription*>	m_characterList;	/*!< TODO: describe */
	QList<cObjectDescription*>		m_objectList;		/*!< TODO: describe */
	QList<cPlaceDescription*>		m_placeList;		/*!< TODO: describe */
	QStandardItem*					m_lpItem;			/*!< TODO: describe */
	QStandardItem*					m_lpStateItem;		/*!< TODO: describe */
	bool							m_bDeleted;			/*!< TODO: describe */
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
	 \param lpCharacter
	 \return QList<cCharacter *>
	*/
	QList<cScene *> find(cCharacter* lpCharacter);

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
