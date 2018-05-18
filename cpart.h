/*!
 \file cpart.h

*/

#ifndef CPART_H
#define CPART_H


#include "ctextdocument.h"

#include <QMetaType>
#include <QList>
#include <QString>
#include <QObject>
#include <QStandardItem>


/*!
 \brief

 \class cPart cpart.h "cpart.h"
*/
class cPart : public QObject
{
	Q_OBJECT
public:
	/*!
	 \brief

	 \fn cPart
	 \param iID
	 \param parent
	*/
	explicit cPart(qint32 iID = -1, QObject *parent = nullptr);

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
	qint32				m_iID;				/*!< TODO: describe */
	QString				m_szName;			/*!< TODO: describe */
	qint32				m_iSortOrder;		/*!< TODO: describe */
	cTextDocument*		m_lpDescription;	/*!< TODO: describe */
	cTextDocument*		m_lpText;			/*!< TODO: describe */
	QStandardItem*		m_lpItem;			/*!< TODO: describe */
	bool				m_bDeleted;			/*!< TODO: describe */
};

Q_DECLARE_METATYPE(cPart*)

/*!
 \brief

 \class cPartList cpart.h "cpart.h"
*/
class cPartList : public QList<cPart*>
{
public:
	/*!
	 \brief

	 \fn load
	 \return bool
	*/
	bool				load();
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
	 \return cPart
	*/
	cPart*				add(const qint32& iID);
	/*!
	 \brief

	 \fn find
	 \param iID
	 \return cPart
	*/
	cPart*				find(const qint32& iID);

	/*!
	 \brief

	 \fn nextSort
	 \return cPart
	*/
	qint32				nextSort();
};

#endif // CPART_H
