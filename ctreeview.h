/*!
 \file ctreeview.h

*/

#ifndef CTREEVIEW_H
#define CTREEVIEW_H


#include <QTreeView>
#include <QMetaType>

#include <QStandardItem>


/*!
 \brief

 \class cTreeView ctreeview.h "ctreeview.h"
*/
class cTreeView : public QTreeView
{
	Q_OBJECT

public:
	/*!
	 \brief

	 \fn cTreeView
	 \param parent
	*/
	cTreeView(QWidget* parent = Q_NULLPTR);

signals:
	/*!
	 \brief

	 \fn gotFocus
	 \param lpTreeView
	*/
	void		gotFocus(cTreeView* lpTreeView);
	/*!
	 \brief

	 \fn lostFocus
	 \param lpTreeView
	*/
	void		lostFocus(cTreeView* lpTreeView);
	/*!
	 \brief

	 \fn dropped
	 \param lpTreeView
	*/
	void		dropped(cTreeView* lpTreeView);

protected:
	/*!
	 \brief

	 \fn focusInEvent
	 \param event
	*/
	void		focusInEvent(QFocusEvent *event);
	/*!
	 \brief

	 \fn focusOutEvent
	 \param event
	*/
	void		focusOutEvent(QFocusEvent *event);
	/*!
	 \brief

	 \fn dropEvent
	 \param event
	*/
	void		dropEvent(QDropEvent *event);
};

Q_DECLARE_METATYPE(cTreeView*)

#endif // CTREEVIEW_H
