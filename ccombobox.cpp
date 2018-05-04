/*!
 \file ccombobox.cpp

*/

#include "ccombobox.h"


cComboBox::cComboBox(QWidget* parent) :
	QComboBox(parent)
{

}

void cComboBox::focusInEvent(QFocusEvent* event)
{
	gotFocus(this);
	QComboBox::focusInEvent(event);
}

void cComboBox::focusOutEvent(QFocusEvent* event)
{
	lostFocus(this);
	QComboBox::focusOutEvent(event);
}
