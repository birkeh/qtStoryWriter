#ifndef COMMON_H
#define COMMON_H


#include <QString>
#include <QByteArray>

#include <QDebug>

#ifdef __GNUC__
	#define myDebug qDebug() << __FILE__ << "(" << __LINE__ << ") - " << __PRETTY_FUNCTION__ << ":"
#elif __MINGW32__
	#define myDebug qDebug() << __FILE__ << "(" << __LINE__ << ") - " << __PRETTY_FUNCTION__ << ":"
#else
	#define myDebug qDebug() << __FILE__ << "(" << __LINE__ << ") - " << __FUNCTION__ << ":"
#endif

QString			uncompressText(const QByteArray& compressed);
QByteArray		compressText(const QString& uncompressed);

#endif // COMMON_H
