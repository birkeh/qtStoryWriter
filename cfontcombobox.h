#ifndef CFONTCOMBOBOX_H
#define CFONTCOMBOBOX_H


#include <QFontComboBox>
#include <QMetaType>


class cFontComboBox : public QFontComboBox
{
	Q_OBJECT

public:
	cFontComboBox(QWidget* parent = Q_NULLPTR);

signals:
	void		gotFocus(cFontComboBox* lpComboBox);
	void		lostFocus(cFontComboBox* lpComboBox);

protected:
	void		focusInEvent(QFocusEvent *event);
	void		focusOutEvent(QFocusEvent *event);
};

Q_DECLARE_METATYPE(cFontComboBox*)

#endif // CFONTCOMBOBOX_H
