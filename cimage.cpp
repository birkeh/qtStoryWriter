/*!
 \file cimage.cpp

*/

#include "cimage.h"

#include "common.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QBuffer>


cImage::cImage(QObject *parent) :
	QObject(parent)
{
}

void cImage::setName(const QString& szName)
{
	m_szName	= szName;
}

QString cImage::name()
{
	return(m_szName);
}

void cImage::setDescription(cTextDocument* lpDescription)
{
	m_lpDescription	= lpDescription;
}

cTextDocument* cImage::description()
{
	return(m_lpDescription);
}

void cImage::setImage(const QPixmap& image)
{
	m_image	= image;
}

QPixmap cImage::image()
{
	return(m_image);
}
