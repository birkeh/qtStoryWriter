#ifndef CCOMBOBOX_H
#define CCOMBOBOX_H


#include <QComboBox>
#include <QMetaType>


class cComboBox : public QComboBox
{
	Q_OBJECT

public:
	cComboBox(QWidget* parent = Q_NULLPTR);

signals:
	void		gotFocus(cComboBox* lpComboBox);
	void		lostFocus(cComboBox* lpComboBox);

protected:
	void		focusInEvent(QFocusEvent *event);
	void		focusOutEvent(QFocusEvent *event);
};

Q_DECLARE_METATYPE(cComboBox*)

#endif // CCOMBOBOX_H
