#include "csplashscreen.h"


cSplashScreen::cSplashScreen(const QPixmap& pixmap) :
	QSplashScreen(pixmap)
{
}

void cSplashScreen::drawContents(QPainter *painter)
{
	painter->setPen(m_color);
	painter->drawText(m_rect, m_iAlignement, m_szMessage);
}

void cSplashScreen::setStatusMessageColor(const QColor& color)
{
	m_color		= color;
}

void cSplashScreen::showStatusMessage(const QString& message)
{
	m_szMessage	= message;
	showMessage(m_szMessage, m_iAlignement, m_color);
}

void cSplashScreen::addStatusMessage(const QString& message)
{
	m_szMessage.append(message);
	showMessage(m_szMessage, m_iAlignement, m_color);
}

void cSplashScreen::setMessageRect(QRect rect, int alignement)
{
	m_rect			= rect;
	m_iAlignement	= alignement;
}
