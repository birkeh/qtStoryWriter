/*!
 \file cobject.h

*/

#ifndef COBJECT_H
#define COBJECT_H


#include "ctextdocument.h"
#include "cimage.h"

#include <QMetaType>
#include <QList>
#include <QString>
#include <QObject>

#include <QStandardItem>


/*!
 \brief

 \class cObject cobject.h "cobject.h"
*/
class cObject : public QObject
{
	Q_OBJECT
public:
	/*!
	 \brief

	 \fn cObject
	 \param iID
	 \param parent
	*/
	explicit cObject(qint32 iID = -1, QObject *parent = nullptr);

	/*!
	 \brief

	 \fn setID
	 \param iID
	*/
	void						setID(const qint32& iID);
	/*!
	 \brief

	 \fn id
	 \return qint32
	*/
	qint32						id();

	/*!
	 \brief

	 \fn setName
	 \param szName
	*/
	void						setName(const QString& szName);
	/*!
	 \brief

	 \fn name
	 \return QString
	*/
	QString						name();

	/*!
	 \brief

	 \fn setType
	 \param szType
	*/
	void						setType(const QString& szType);
	/*!
	 \brief

	 \fn type
	 \return QString
	*/
	QString						type();

	/*!
	 \brief

	 \fn setDescription
	 \param lpDescription
	*/
	void						setDescription(cTextDocument* lpDescription);
	/*!
	 \brief

	 \fn description
	 \return cTextDocument
	*/
	cTextDocument*				description();

	/*!
	 \brief

	 \fn addImage
	 \param lpImage
	*/
	void						addImage(cImage* lpImage);
	/*!
	 \brief

	 \fn images
	 \return QList<cImage *>
	*/
	QList<cImage*>				images();

	/*!
	 \brief

	 \fn setItem
	 \param itemList
	*/
	void						setItem(QList<QStandardItem*> itemList);
	/*!
	 \brief

	 \fn item
	 \return QList<QStandardItem*>
	*/
	QList<QStandardItem*>		item();

	/*!
	 \brief

	 \fn setDeleted
	 \param bDeleted
	*/
	void						setDeleted(bool bDeleted);
	/*!
	 \brief

	 \fn deleted
	 \return bool
	*/
	bool						deleted();

private:
	qint32						m_iID;				/*!< TODO: describe */
	QString						m_szName;			/*!< TODO: describe */
	QString						m_szType;			/*!< TODO: describe */
	cTextDocument*				m_lpDescription;	/*!< TODO: describe */
	QList<cImage*>				m_imageList;		/*!< TODO: describe */
	QList<QStandardItem*>		m_itemList;			/*!< TODO: describe */
	bool						m_bDeleted;			/*!< TODO: describe */

signals:

public slots:
};

/*!
 \brief

 \class cObjectDescription cobject.h "cobject.h"
*/
class cObjectDescription : public QObject
{
	Q_OBJECT
public:
	cObjectDescription(cObject* lpObject, cTextDocument* lpDescription, QObject* parent = nullptr);

	/*!
	 \brief

	 \fn setObject
	 \param lpObject
	*/
	void				setObject(cObject* lpObject);
	/*!
	 \brief

	 \fn object
	 \return cObject
	*/
	cObject*			object();

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
private:
	cObject*			m_lpObject;			/*!< TODO: describe */
	cTextDocument*		m_lpDescription;	/*!< TODO: describe */
};

Q_DECLARE_METATYPE(cObject*)

/*!
 \brief

 \class cObjectList cobject.h "cobject.h"
*/
class cObjectList : public QList<cObject*>
{
public:
	/*!
	 \brief

	 \fn load
	 \param lpImageList
	 \return bool
	*/
	bool			load();
	/*!
	 \brief

	 \fn save
	 \return bool
	*/
	bool			save();

	/*!
	 \brief

	 \fn add
	 \param iID
	 \return cObject
	*/
	cObject*		add(const qint32& iID);
	/*!
	 \brief

	 \fn find
	 \param iID
	 \return cObject
	*/
	cObject*		find(const qint32& iID);
};

#endif // COBJECT_H
