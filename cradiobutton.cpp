/*!
 \file cradiobutton.cpp

*/

#include "cradiobutton.h"


cRadioButton::cRadioButton(QWidget* parent) :
	QRadioButton(parent)
{
}

void cRadioButton::focusInEvent(QFocusEvent* event)
{
	gotFocus(this);
	QRadioButton::focusInEvent(event);
}

void cRadioButton::focusOutEvent(QFocusEvent* event)
{
	lostFocus(this);
	QRadioButton::focusOutEvent(event);
}
