#ifndef CCHECKBOX_H
#define CCHECKBOX_H


#include <QCheckBox>
#include <QMetaType>


class cCheckBox : public QCheckBox
{
	Q_OBJECT

public:
	cCheckBox(QWidget* parent = Q_NULLPTR);

signals:
	void		gotFocus(cCheckBox* lpCheckBox);
	void		lostFocus(cCheckBox* lpCheckBox);

protected:
	void		focusInEvent(QFocusEvent *event);
	void		focusOutEvent(QFocusEvent *event);
};

Q_DECLARE_METATYPE(cCheckBox*)

#endif // CCHECKBOX_H
