/*!
 \file cimage.h

*/

#ifndef CIMAGE_H
#define CIMAGE_H


#include "ctextdocument.h"

#include <QMetaType>
#include <QList>
#include <QString>
#include <QPixmap>


/*!
 \brief

 \class cImage cimage.h "cimage.h"
*/
class cImage : public QObject
{
	Q_OBJECT
public:
	cImage(qint32 iID = -1, QObject* parent = nullptr);

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

	 \fn setImage
	 \param image
	*/
	void			setImage(const QPixmap& image);
	/*!
	 \brief

	 \fn image
	 \return QPixmap
	*/
	QPixmap			image();
private:
	qint32			m_iID; /*!< TODO: describe */
	QString			m_szName; /*!< TODO: describe */
	QString			m_szType; /*!< TODO: describe */
	cTextDocument*	m_lpDescription; /*!< TODO: describe */
	QPixmap			m_image; /*!< TODO: describe */
};

/*!
 \brief

 \class cImageDescription cimage.h "cimage.h"
*/
class cImageDescription : public QObject
{
	Q_OBJECT
public:
	cImageDescription(cImage* lpImage, cTextDocument* lpDescription, QObject* parent = nullptr);

	/*!
	 \brief

	 \fn setImage
	 \param lpImage
	*/
	void			setImage(cImage* lpImage);
	/*!
	 \brief

	 \fn image
	 \return cImage
	*/
	cImage*			image();

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
private:
	cImage*			m_lpImage; /*!< TODO: describe */
	cTextDocument*	m_lpDescription; /*!< TODO: describe */
};

Q_DECLARE_METATYPE(cImage*)

/*!
 \brief

 \class cImageList cimage.h "cimage.h"
*/
class cImageList : public QList<cImage*>
{
public:
	/*!
	 \brief

	 \fn load
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
	 \return cImage
	*/
	cImage*			add(const qint32& iID);
	/*!
	 \brief

	 \fn find
	 \param iID
	 \return cImage
	*/
	cImage*			find(const qint32& iID);
};

#endif // CIMAGE_H
