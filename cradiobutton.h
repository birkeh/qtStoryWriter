#ifndef CRADIOBUTTON_H
#define CRADIOBUTTON_H


#include <QRadioButton>
#include <QMetaType>


class cRadioButton : public QRadioButton
{
	Q_OBJECT

public:
	cRadioButton(QWidget* parent = Q_NULLPTR);

signals:
	void		gotFocus(cRadioButton* lpRadioButton);
	void		lostFocus(cRadioButton* lpRadioButton);

protected:
	void		focusInEvent(QFocusEvent *event);
	void		focusOutEvent(QFocusEvent *event);
};

Q_DECLARE_METATYPE(cRadioButton*)

#endif // CRADIOBUTTON_H
