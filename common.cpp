/*!
 \file common.cpp

*/

#include "common.h"

#include <QBuffer>
#include <QSettings>
#include <QCoreApplication>
#include <QDir>


QString uncompressText(const QByteArray& compressed)
{
	if(compressed.isNull() || compressed.isEmpty())
		return("");
	return(qUncompress(compressed));
}

QByteArray compressText(const QString& uncompressed)
{
	if(uncompressed.isNull() || uncompressed.isEmpty())
		return(QByteArray());
	return(qCompress(uncompressed.toUtf8()));
}

QPixmap blob2Image(const QByteArray& ba)
{
	QPixmap		image;

	if(!ba.isEmpty())
	{
		if(!image.loadFromData(ba))
			myDebug << "image load error.";
	}

	return(image);
}

QByteArray image2Blob(const QPixmap &image)
{
	QByteArray	ba;
	QBuffer		buffer(&ba);
	buffer.open(QIODevice::WriteOnly);
	image.save(&buffer, "JPG");
	buffer.close();

	return(ba);
}

cTextDocument*	blob2TextDocument(const QByteArray& ba)
{
	cTextDocument*	lpTextDocument	= new cTextDocument;
	if(ba.isEmpty())
	{
		lpTextDocument->setHtml("");
		return(lpTextDocument);
	}

	lpTextDocument->setHtml(uncompressText(ba));
	return(lpTextDocument);
}

QByteArray textDocument2Blob(cTextDocument* lpTextDocument)
{
	QByteArray	ba;

	if(!lpTextDocument)
		return(ba);

	ba	= compressText(lpTextDocument->toHtml());

	return(ba);
}

QString	 localePath()
{
	QSettings	settings;
	QString		szAppPath	= QCoreApplication::applicationDirPath();
	QString		szPath		= settings.value("file/locale", QString("%1%2locale").arg(szAppPath).arg(QDir::separator())).toString();
	return(szPath);
}
