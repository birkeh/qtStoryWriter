#ifndef CLINEEDIT_H
#define CLINEEDIT_H


#include <QLineEdit>
#include <QMetaType>


class cLineEdit : public QLineEdit
{
	Q_OBJECT

public:
	cLineEdit(QWidget* parent = Q_NULLPTR);

signals:
	void		gotFocus(cLineEdit* lpLineEdit);
	void		lostFocus(cLineEdit* lpLineEdit);

protected:
	void		focusInEvent(QFocusEvent *event);
	void		focusOutEvent(QFocusEvent *event);
};

Q_DECLARE_METATYPE(cLineEdit*)

#endif // CLINEEDIT_H
