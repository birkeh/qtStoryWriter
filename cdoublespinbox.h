/*!
 \file cdoublespinbox.h

*/

#ifndef CDOUBLESPINBOX_H
#define CDOUBLESPINBOX_H


#include <QDoubleSpinBox>
#include <QMetaType>


/*!
 \brief

 \class cDoubleSpinBox cdoublespinbox.h "cdoublespinbox.h"
*/
class cDoubleSpinBox : public QDoubleSpinBox
{
	Q_OBJECT

public:
	/*!
	 \brief

	 \fn cDoubleSpinBox
	 \param parent
	*/
	cDoubleSpinBox(QWidget* parent = Q_NULLPTR);

signals:
	/*!
	 \brief

	 \fn gotFocus
	 \param lpDoubleSpinBox
	*/
	void		gotFocus(cDoubleSpinBox* lpDoubleSpinBox);
	/*!
	 \brief

	 \fn lostFocus
	 \param lpDoubleSpinBox
	*/
	void		lostFocus(cDoubleSpinBox* lpDoubleSpinBox);

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

Q_DECLARE_METATYPE(cDoubleSpinBox*)

#endif // CDOUBLESPINBOX_H
