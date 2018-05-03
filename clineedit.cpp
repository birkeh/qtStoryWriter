#include "clineedit.h"


cLineEdit::cLineEdit(QWidget* parent) :
	QLineEdit(parent)
{
}

void cLineEdit::focusInEvent(QFocusEvent* event)
{
	gotFocus(this);
	QLineEdit::focusInEvent(event);
}

void cLineEdit::focusOutEvent(QFocusEvent* event)
{
	lostFocus(this);
	QLineEdit::focusOutEvent(event);
}
