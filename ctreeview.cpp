/*!
 \file ctreeview.cpp

*/

#include "ctreeview.h"

#include "cpart.h"
#include "cchapter.h"
#include "cscene.h"

#include <QDropEvent>
#include <QStandardItemModel>


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

qint16 level(QModelIndex index)
{
	QModelIndex	tmp		= index;
	qint16		level	= 0;

	while(tmp.parent().isValid())
	{
		level++;
		tmp	= tmp.parent();
	}
	return(level);
}

void cTreeView::dropEvent(QDropEvent* event)
{
	QStandardItemModel*		lpModel			= (QStandardItemModel*)model();
	QModelIndex				fromIndex		= selectedIndexes()[0];
	QStandardItem*			lpFromItem		= lpModel->itemFromIndex(fromIndex);
	QModelIndex				droppedIndex	= indexAt(event->pos());
	DropIndicatorPosition	pos	= dropIndicatorPosition();

	qint16		fromLevel		= level(fromIndex);
	qint16		droppedLevel	= level(droppedIndex);

	if(droppedLevel < fromLevel-1)
		return;
	else if(droppedLevel > fromLevel)
		return;
	else if(droppedLevel == fromLevel && pos == DropIndicatorPosition::OnItem)
		return;
	else if(droppedLevel == fromLevel-1 && pos == DropIndicatorPosition::BelowItem)
		return;

	QTreeView::dropEvent(event);

	QModelIndex				toIndex			= selectedIndexes()[0];
	lpFromItem->setData(toIndex.row(), Qt::UserRole+2);

	dropped(this);
}
