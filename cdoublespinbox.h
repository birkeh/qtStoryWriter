#ifndef CDOUBLESPINBOX_H
#define CDOUBLESPINBOX_H


#include <QDoubleSpinBox>
#include <QMetaType>


class cDoubleSpinBox : public QDoubleSpinBox
{
	Q_OBJECT

public:
	cDoubleSpinBox(QWidget* parent = Q_NULLPTR);

signals:
	void		gotFocus(cDoubleSpinBox* lpDoubleSpinBox);
	void		lostFocus(cDoubleSpinBox* lpDoubleSpinBox);

protected:
	void		focusInEvent(QFocusEvent *event);
	void		focusOutEvent(QFocusEvent *event);
};

Q_DECLARE_METATYPE(cDoubleSpinBox*)

#endif // CDOUBLESPINBOX_H
