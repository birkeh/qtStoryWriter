/*!
 \file common.h

*/

#ifndef COMMON_H
#define COMMON_H


#include "ctextdocument.h"

#include <QString>
#include <QByteArray>
#include <QPixmap>

#include <QDebug>

#ifdef __GNUC__
	#define myDebug qDebug() << __FILE__ << "(" << __LINE__ << ") - " << __PRETTY_FUNCTION__ << ":"
#elif __MINGW32__
	#define myDebug qDebug() << __FILE__ << "(" << __LINE__ << ") - " << __PRETTY_FUNCTION__ << ":"
#else
	#define myDebug qDebug() << __FILE__ << "(" << __LINE__ << ") - " << __FUNCTION__ << ":"
#endif

/*!
 \brief

 \fn uncompressText
 \param compressed
 \return QString
*/
QString			uncompressText(const QByteArray& compressed);
/*!
 \brief

 \fn compressText
 \param uncompressed
 \return QByteArray
*/
QByteArray		compressText(const QString& uncompressed);
/*!
 \brief

 \fn blob2Image
 \param ba
 \return QPixmap
*/
QPixmap			blob2Image(const QByteArray& ba);
/*!
 \brief

 \fn image2Blob
 \param image
 \return QByteArray
*/
QByteArray		image2Blob(const QPixmap& image);
/*!
 \brief

 \fn blob2TextDocument
 \param ba
 \return cTextDocument
*/
cTextDocument*	blob2TextDocument(const QByteArray& ba);
/*!
 \brief

 \fn textDocument2Blob
 \param lpTextDocument
 \return QByteArray
*/
QByteArray		textDocument2Blob(cTextDocument* lpTextDocument);
/*!
 \brief

 \fn localePath
 \return QString
*/
QString			localePath();

#endif // COMMON_H
