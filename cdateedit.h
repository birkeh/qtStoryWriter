#ifndef CDATEEDIT_H
#define CDATEEDIT_H


#include <QDateEdit>
#include <QMetaType>


class cDateEdit : public QDateEdit
{
	Q_OBJECT

public:
	cDateEdit(QWidget* parent = Q_NULLPTR);

signals:
	void		gotFocus(cDateEdit* lpDateEdit);
	void		lostFocus(cDateEdit* lpDateEdit);

protected:
	void		focusInEvent(QFocusEvent *event);
	void		focusOutEvent(QFocusEvent *event);
};

Q_DECLARE_METATYPE(cDateEdit*)

#endif // CDATEEDIT_H
