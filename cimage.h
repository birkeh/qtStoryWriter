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
	/*!
	 \brief

	 \fn cImage
	 \param iID
	 \param parent
	*/
	cImage(qint32 iID = -1, QObject* parent = nullptr);

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

	 \fn setImage
	 \param image
	*/
	void			setName(const QString& szName);
	/*!
	 \brief

	 \fn image
	 \return QPixmap
	*/
	QString			name();

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
	qint32			m_iID;				/*!< TODO: describe */
	QString			m_szName;			/*!< TODO: describe */
	cTextDocument*	m_lpDescription;	/*!< TODO: describe */
	QPixmap			m_image;			/*!< TODO: describe */
};

Q_DECLARE_METATYPE(cImage*)

#endif // CIMAGE_H
