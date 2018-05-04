/*!
 \file cdateedit.h

*/

#ifndef CDATEEDIT_H
#define CDATEEDIT_H


#include <QDateEdit>
#include <QMetaType>


/*!
 \brief

 \class cDateEdit cdateedit.h "cdateedit.h"
*/
class cDateEdit : public QDateEdit
{
	Q_OBJECT

public:
	cDateEdit(QWidget* parent = Q_NULLPTR);

signals:
	/*!
	 \brief

	 \fn gotFocus
	 \param lpDateEdit
	*/
	void		gotFocus(cDateEdit* lpDateEdit);
	/*!
	 \brief

	 \fn lostFocus
	 \param lpDateEdit
	*/
	void		lostFocus(cDateEdit* lpDateEdit);

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

Q_DECLARE_METATYPE(cDateEdit*)

#endif // CDATEEDIT_H
