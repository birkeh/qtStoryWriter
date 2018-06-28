#include "cfontcombobox.h"


cFontComboBox::cFontComboBox(QWidget* parent) :
	QFontComboBox(parent)
{

}

void cFontComboBox::focusInEvent(QFocusEvent* event)
{
	gotFocus(this);
	QComboBox::focusInEvent(event);
}

void cFontComboBox::focusOutEvent(QFocusEvent* event)
{
	lostFocus(this);
	QComboBox::focusOutEvent(event);
}
