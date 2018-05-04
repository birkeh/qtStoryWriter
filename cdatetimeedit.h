/*!
 \file cdatetimeedit.h

*/

#ifndef CDATETIMEEDIT_H
#define CDATETIMEEDIT_H


#include <QDateTimeEdit>
#include <QMetaType>


/*!
 \brief

 \class cDateTimeEdit cdatetimeedit.h "cdatetimeedit.h"
*/
class cDateTimeEdit : public QDateTimeEdit
{
	Q_OBJECT

public:
	cDateTimeEdit(QWidget* parent = Q_NULLPTR);

signals:
	/*!
	 \brief

	 \fn gotFocus
	 \param lpDateTimeEdit
	*/
	void		gotFocus(cDateTimeEdit* lpDateTimeEdit);
	/*!
	 \brief

	 \fn lostFocus
	 \param lpDateTimeEdit
	*/
	void		lostFocus(cDateTimeEdit* lpDateTimeEdit);

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

Q_DECLARE_METATYPE(cDateTimeEdit*)

#endif // CDATETIMEEDIT_H
