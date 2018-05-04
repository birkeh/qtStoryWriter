/*!
 \file cchapter.h

*/

#ifndef CCHAPTER_H
#define CCHAPTER_H


#include "cpart.h"
#include "ctextdocument.h"
				  

#include <QMetaType>
#include <QList>
#include <QString>
#include <QObject>


/*!
 \brief

 \class cChapter cchapter.h "cchapter.h"
*/
class cChapter : public QObject
{
	Q_OBJECT
public:
	/*!
	 \brief

	 \fn cChapter
	 \param iID
	 \param parent
	*/
	explicit cChapter(qint32 iID = -1, QObject *parent = nullptr);

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

	 \fn setPart
	 \param lpPart
	*/
	void				setPart(cPart *lpPart);
	/*!
	 \brief

	 \fn part
	 \return cPart
	*/
	cPart*				part();

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

private:
	qint32				m_iID; /*!< TODO: describe */
	cPart*				m_lpPart; /*!< TODO: describe */
	QString				m_szName; /*!< TODO: describe */
	qint32				m_iSortOrder; /*!< TODO: describe */
	cTextDocument*		m_lpDescription; /*!< TODO: describe */
	cTextDocument*		m_lpText; /*!< TODO: describe */
};

Q_DECLARE_METATYPE(cChapter*)

/*!
 \brief

 \class cChapterList cchapter.h "cchapter.h"
*/
class cChapterList : public QList<cChapter*>
{
public:
	/*!
	 \brief

	 \fn load
	 \param lpPartList
	 \return bool
	*/
	bool				load(cPartList *lpPartList);
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
	 \return cChapter
	*/
	cChapter*			add(const qint32& iID);
	/*!
	 \brief

	 \fn find
	 \param iID
	 \return cChapter
	*/
	cChapter*			find(const qint32& iID);

	/*!
	 \brief

	 \fn find
	 \param lpPart
	 \return QList<cChapter *>
	*/
	QList<cChapter*>	find(cPart* lpPart);
};

#endif // CCHAPTER_H
