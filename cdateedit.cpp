/*!
 \file cdateedit.cpp

*/

#include "cdateedit.h"


cDateEdit::cDateEdit(QWidget* parent) :
	QDateEdit(parent)
{
}

void cDateEdit::focusInEvent(QFocusEvent* event)
{
	gotFocus(this);
	QDateEdit::focusInEvent(event);
}

void cDateEdit::focusOutEvent(QFocusEvent* event)
{
	lostFocus(this);
	QDateEdit::focusOutEvent(event);
}
