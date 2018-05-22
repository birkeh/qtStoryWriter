#ifndef CSPLASHSCREEN_H
#define CSPLASHSCREEN_H


#include <QSplashScreen>
#include <QPainter>


class cSplashScreen : public QSplashScreen
{
public:
	cSplashScreen(const QPixmap& pixmap);

	virtual void	drawContents(QPainter *painter);
	void			setStatusMessageColor(const QColor& color);
	void			showStatusMessage(const QString &message);
	void			addStatusMessage(const QString &message);
	void			setMessageRect(QRect rect, int alignment = Qt::AlignLeft);

private:
	QString			m_szMessage;
	int				m_iAlignement;
	QColor			m_color;
	QRect			m_rect;
};

#endif // CSPLASHSCREEN_H
