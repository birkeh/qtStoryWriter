/*!
 \file cradiobutton.h

*/

#ifndef CRADIOBUTTON_H
#define CRADIOBUTTON_H


#include <QRadioButton>
#include <QMetaType>


/*!
 \brief

 \class cRadioButton cradiobutton.h "cradiobutton.h"
*/
class cRadioButton : public QRadioButton
{
	Q_OBJECT

public:
	cRadioButton(QWidget* parent = Q_NULLPTR);

signals:
	/*!
	 \brief

	 \fn gotFocus
	 \param lpRadioButton
	*/
	void		gotFocus(cRadioButton* lpRadioButton);
	/*!
	 \brief

	 \fn lostFocus
	 \param lpRadioButton
	*/
	void		lostFocus(cRadioButton* lpRadioButton);

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

Q_DECLARE_METATYPE(cRadioButton*)

#endif // CRADIOBUTTON_H
