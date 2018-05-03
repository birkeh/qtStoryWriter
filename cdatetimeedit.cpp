#include "cdatetimeedit.h"


cDateTimeEdit::cDateTimeEdit(QWidget* parent) :
	QDateTimeEdit(parent)
{

}

void cDateTimeEdit::focusInEvent(QFocusEvent* event)
{
	gotFocus(this);
	QDateTimeEdit::focusInEvent(event);
}

void cDateTimeEdit::focusOutEvent(QFocusEvent* event)
{
	lostFocus(this);
	QDateTimeEdit::focusOutEvent(event);
}
