/*!
 \file cwidget.cpp

*/

#include "cwidget.h"


cWidget::cWidget(cPropertiesWindow* parent) :
	QWidget(parent),
	m_type(TYPE_properties),
	m_lpWidget(parent),
	m_lpWindow(0)
{
}

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
	m_lpWidget(parent),
	m_lpWindow(0)
{
}

cWidget::cWidget(cPlaceWindow* parent) :
	QWidget(parent),
	m_type(TYPE_place),
	m_lpWidget(parent),
	m_lpWindow(0)
{
}

cWidget::cWidget(cRechercheWindow* parent) :
	QWidget(parent),
	m_type(TYPE_recherche),
	m_lpWidget(parent),
	m_lpWindow(0)
{
}

cWidget::cWidget(QWidget* parent) :
	QWidget(parent),
	m_type(TYPE_unknown),
	m_lpWidget(parent),
	m_lpWindow(0)
{
}

void cWidget::retranslateUI()
{
	switch(m_type)
	{
	case TYPE_part:
		{
			cPartWindow*		lpWindow	= (cPartWindow*)m_lpWidget;
			lpWindow->retranslateUI();
		}
		break;
	case TYPE_chapter:
		{
			cChapterWindow*		lpWindow	= (cChapterWindow*)m_lpWidget;
			lpWindow->retranslateUI();
		}
		break;
	case TYPE_scene:
		{
			cSceneWindow*		lpWindow	= (cSceneWindow*)m_lpWidget;
			lpWindow->retranslateUI();
		}
		break;
	case TYPE_character:
		{
			cCharacterWindow*	lpWindow	= (cCharacterWindow*)m_lpWidget;
			lpWindow->retranslateUI();
		}
		break;
	case TYPE_object:
		{
			cObjectWindow*		lpWindow	= (cObjectWindow*)m_lpWidget;
			lpWindow->retranslateUI();
		}
		break;
	case TYPE_place:
		{
			cPlaceWindow*		lpWindow	= (cPlaceWindow*)m_lpWidget;
			lpWindow->retranslateUI();
		}
		break;
	case TYPE_recherche:
		{
			cRechercheWindow*	lpWindow	= (cRechercheWindow*)m_lpWidget;
			lpWindow->retranslateUI();
		}
		break;
	case TYPE_properties:
		{
			cPropertiesWindow*	lpWindow	= (cPropertiesWindow*)m_lpWidget;
			lpWindow->retranslateUI();
		}
		break;
	default:
		break;
	}
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
