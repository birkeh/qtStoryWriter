/*!
 \file ccheckbox.h

*/

#ifndef CCHECKBOX_H
#define CCHECKBOX_H


#include <QCheckBox>
#include <QMetaType>


/*!
 \brief

 \class cCheckBox ccheckbox.h "ccheckbox.h"
*/
class cCheckBox : public QCheckBox
{
	Q_OBJECT

public:
	/*!
	 \brief

	 \fn cCheckBox
	 \param parent
	*/
	cCheckBox(QWidget* parent = Q_NULLPTR);

signals:
	/*!
	 \brief

	 \fn gotFocus
	 \param lpCheckBox
	*/
	void		gotFocus(cCheckBox* lpCheckBox);
	/*!
	 \brief

	 \fn lostFocus
	 \param lpCheckBox
	*/
	void		lostFocus(cCheckBox* lpCheckBox);

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

Q_DECLARE_METATYPE(cCheckBox*)

#endif // CCHECKBOX_H
