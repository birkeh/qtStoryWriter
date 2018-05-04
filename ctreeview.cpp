/*!
 \file ctreeview.cpp

*/

#include "ctreeview.h"

cTreeView::cTreeView(QWidget* parent) :
	QTreeView(parent)
{
}

void cTreeView::focusInEvent(QFocusEvent* event)
{
	gotFocus(this);
	QTreeView::focusInEvent(event);
}

void cTreeView::focusOutEvent(QFocusEvent* event)
{
	lostFocus(this);
	QTreeView::focusOutEvent(event);
}
