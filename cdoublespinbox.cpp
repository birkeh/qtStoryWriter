#include "cdoublespinbox.h"

cDoubleSpinBox::cDoubleSpinBox(QWidget* parent) :
	QDoubleSpinBox(parent)
{

}

void cDoubleSpinBox::focusInEvent(QFocusEvent* event)
{
	gotFocus(this);
	QDoubleSpinBox::focusInEvent(event);
}

void cDoubleSpinBox::focusOutEvent(QFocusEvent* event)
{
	lostFocus(this);
	QDoubleSpinBox::focusOutEvent(event);
}
