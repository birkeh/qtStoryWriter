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
#include <QPrinter>
#include <QPagedPaintDevice>


#ifdef __GNUC__
	#define myDebug qDebug() << __FILE__ << "(" << __LINE__ << ") - " << __PRETTY_FUNCTION__ << ":"
#elif __MINGW32__
	#define myDebug qDebug() << __FILE__ << "(" << __LINE__ << ") - " << __PRETTY_FUNCTION__ << ":"
#else
	#define myDebug qDebug() << __FILE__ << "(" << __LINE__ << ") - " << __FUNCTION__ << ":"
#endif


/*!
 \brief

 \enum ALIGN
*/
enum ALIGN
{
	ALIGN_left		= 1,
	ALIGN_right		= 2,
	ALIGN_center	= 3,
	ALIGN_block		= 4,
};

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

QString paperName(QPagedPaintDevice::PageSize paperSize);
/*!
 \brief

 \fn paperKey
 \param szPaperSize
 \return QPagedPaintDevice::PageSize
*/
QPagedPaintDevice::PageSize paperKey(const QString& szPaperSize);
/*!
 \brief

 \fn paperList
 \return QMap<QPagedPaintDevice::PageSize, QString>
*/
QMap<QPagedPaintDevice::PageSize, QString> paperList();

/*!
 \brief

 \fn unitName
 \param unit
 \return QString
*/
QString unitName(QPrinter::Unit unit);
/*!
 \brief

 \fn unitKey
 \param szUnit
 \return QPrinter::Unit
*/
QPrinter::Unit unitKey(const QString& szUnit);
/*!
 \brief

 \fn unitList
 \return QMap<QPrinter::Unit, QString>
*/
QMap<QPrinter::Unit, QString> unitList();

#endif // COMMON_H
