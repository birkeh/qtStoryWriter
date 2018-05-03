#ifndef CTREEVIEW_H
#define CTREEVIEW_H


#include <QTreeView>
#include <QMetaType>


class cTreeView : public QTreeView
{
	Q_OBJECT

public:
	cTreeView(QWidget* parent = Q_NULLPTR);

signals:
	void		gotFocus(cTreeView* lpTreeView);
	void		lostFocus(cTreeView* lpTreeView);

protected:
	void		focusInEvent(QFocusEvent *event);
	void		focusOutEvent(QFocusEvent *event);
};

Q_DECLARE_METATYPE(cTreeView*)

#endif // CTREEVIEW_H
