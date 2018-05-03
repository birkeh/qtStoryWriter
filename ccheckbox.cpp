#include "ccheckbox.h"


cCheckBox::cCheckBox(QWidget* parent) :
	QCheckBox(parent)
{

}

void cCheckBox::focusInEvent(QFocusEvent* event)
{
	gotFocus(this);
	QCheckBox::focusInEvent(event);
}

void cCheckBox::focusOutEvent(QFocusEvent* event)
{
	lostFocus(this);
	QCheckBox::focusOutEvent(event);
}
