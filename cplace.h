/*!
 \file cplace.h

*/

#ifndef CPLACE_H
#define CPLACE_H


#include "ctextdocument.h"
#include "cimage.h"

#include <QMetaType>
#include <QList>
#include <QString>
#include <QObject>


/*!
 \brief

 \class cPlace cplace.h "cplace.h"
*/
class cPlace : public QObject
{
	Q_OBJECT
public:
	/*!
	 \brief

	 \fn cPlace
	 \param iID
	 \param parent
	*/
	explicit cPlace(qint32 iID = -1, QObject *parent = nullptr);

	/*!
	 \brief

	 \fn setID
	 \param iID
	*/
	void			setID(const qint32& iID);
	/*!
	 \brief

	 \fn id
	 \return qint32
	*/
	qint32			id();

	/*!
	 \brief

	 \fn setName
	 \param szName
	*/
	void			setName(const QString& szName);
	/*!
	 \brief

	 \fn name
	 \return QString
	*/
	QString			name();

	/*!
	 \brief

	 \fn setLocation
	 \param szLocation
	*/
	void			setLocation(const QString& szLocation);
	/*!
	 \brief

	 \fn location
	 \return QString
	*/
	QString			location();

	/*!
	 \brief

	 \fn setType
	 \param szType
	*/
	void			setType(const QString& szType);
	/*!
	 \brief

	 \fn type
	 \return QString
	*/
	QString			type();

	/*!
	 \brief

	 \fn setDescription
	 \param lpDescription
	*/
	void			setDescription(cTextDocument* lpDescription);
	/*!
	 \brief

	 \fn description
	 \return cTextDocument
	*/
	cTextDocument*	description();

	/*!
	 \brief

	 \fn addImage
	 \param lpImage
	*/
	void			addImage(cImage* lpImage);
	/*!
	 \brief

	 \fn images
	 \return QList<cImage *>
	*/
	QList<cImage*>	images();

private:
	qint32			m_iID; /*!< TODO: describe */
	QString			m_szName; /*!< TODO: describe */
	QString			m_szLocation; /*!< TODO: describe */
	QString			m_szType; /*!< TODO: describe */
	cTextDocument*	m_lpDescription; /*!< TODO: describe */
	QList<cImage*>	m_imageList; /*!< TODO: describe */

signals:

public slots:
};

Q_DECLARE_METATYPE(cPlace*)

/*!
 \brief

 \class cPlaceList cplace.h "cplace.h"
*/
class cPlaceList : public QList<cPlace*>
{
public:
	/*!
	 \brief

	 \fn load
	 \param lpImageList
	 \return bool
	*/
	bool			load(cImageList* lpImageList);
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
	 \return cPlace
	*/
	cPlace*			add(const qint32& iID);
	/*!
	 \brief

	 \fn find
	 \param iID
	 \return cPlace
	*/
	cPlace*			find(const qint32& iID);
};

#endif // CPLACE_H
