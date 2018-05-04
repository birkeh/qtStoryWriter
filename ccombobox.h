/*!
 \file ccombobox.h

*/

#ifndef CCOMBOBOX_H
#define CCOMBOBOX_H


#include <QComboBox>
#include <QMetaType>


/*!
 \brief

 \class cComboBox ccombobox.h "ccombobox.h"
*/
class cComboBox : public QComboBox
{
	Q_OBJECT

public:
	cComboBox(QWidget* parent = Q_NULLPTR);

signals:
	/*!
	 \brief

	 \fn gotFocus
	 \param lpComboBox
	*/
	void		gotFocus(cComboBox* lpComboBox);
	/*!
	 \brief

	 \fn lostFocus
	 \param lpComboBox
	*/
	void		lostFocus(cComboBox* lpComboBox);

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

Q_DECLARE_METATYPE(cComboBox*)

#endif // CCOMBOBOX_H
