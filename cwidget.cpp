#include "cwidget.h"


cWidget::cWidget(QWidget *parent) :
	QWidget(parent),
	m_lpWindow(0)
{
}

void cWidget::setWindow(QMdiSubWindow* lpWindow)
{
	m_lpWindow	= lpWindow;
}

QMdiSubWindow *cWidget::window()
{
	return(m_lpWindow);
}
