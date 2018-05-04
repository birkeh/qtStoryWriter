/*!
 \file ctreeview.h

*/

#ifndef CTREEVIEW_H
#define CTREEVIEW_H


#include <QTreeView>
#include <QMetaType>


/*!
 \brief

 \class cTreeView ctreeview.h "ctreeview.h"
*/
class cTreeView : public QTreeView
{
	Q_OBJECT

public:
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
};

Q_DECLARE_METATYPE(cTreeView*)

#endif // CTREEVIEW_H
