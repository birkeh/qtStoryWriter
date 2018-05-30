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
	cImage(QObject* parent = nullptr);

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
	QString			m_szName;			/*!< TODO: describe */
	cTextDocument*	m_lpDescription;	/*!< TODO: describe */
	QPixmap			m_image;			/*!< TODO: describe */
};

Q_DECLARE_METATYPE(cImage*)

#endif // CIMAGE_H
