#include "cwidget.h"


cWidget::cWidget(cPartWindow* parent) :
	QWidget(parent),
	m_type(TYPE_part),
	m_lpWidget(parent),
	m_lpWindow(0)
{
}

cWidget::cWidget(cChapterWindow* parent) :
	QWidget(parent),
	m_type(TYPE_chapter),
	m_lpWidget(parent),
	m_lpWindow(0)
{
}

cWidget::cWidget(cSceneWindow* parent) :
	QWidget(parent),
	m_type(TYPE_scene),
	m_lpWidget(parent),
	m_lpWindow(0)
{
}

cWidget::cWidget(cCharacterWindow* parent) :
	QWidget(parent),
	m_type(TYPE_character),
	m_lpWidget(parent),
	m_lpWindow(0)
{
}

cWidget::cWidget(cObjectWindow* parent) :
	QWidget(parent),
	m_type(TYPE_object),
	m_lpWidget(0),
	m_lpWindow(0)
{
}

cWidget::cWidget(cPlaceWindow* parent) :
	QWidget(parent),
	m_type(TYPE_place),
	m_lpWidget(0),
	m_lpWindow(0)
{
}

cWidget::cWidget(cRechercheWindow* parent) :
	QWidget(parent),
	m_type(TYPE_recherche),
	m_lpWidget(0),
	m_lpWindow(0)
{
}

cWidget::cWidget(QWidget* parent) :
	QWidget(parent),
	m_type(TYPE_unknown),
	m_lpWidget(0),
	m_lpWindow(0)
{
}

void cWidget::setWindow(QMdiSubWindow* lpWindow)
{
	m_lpWindow	= lpWindow;
}

QMdiSubWindow* cWidget::window()
{
	return(m_lpWindow);
}

QWidget* cWidget::widget()
{
	return(m_lpWidget);
}

cWidget::TYPE cWidget::type()
{
	return(m_type);
}
