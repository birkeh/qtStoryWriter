/*!
 \file clineedit.h

*/

#ifndef CLINEEDIT_H
#define CLINEEDIT_H


#include <QLineEdit>
#include <QMetaType>


/*!
 \brief

 \class cLineEdit clineedit.h "clineedit.h"
*/
class cLineEdit : public QLineEdit
{
	Q_OBJECT

public:
	/*!
	 \brief

	 \fn cLineEdit
	 \param parent
	*/
	cLineEdit(QWidget* parent = Q_NULLPTR);

signals:
	/*!
	 \brief

	 \fn gotFocus
	 \param lpLineEdit
	*/
	void		gotFocus(cLineEdit* lpLineEdit);
	/*!
	 \brief

	 \fn lostFocus
	 \param lpLineEdit
	*/
	void		lostFocus(cLineEdit* lpLineEdit);

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

Q_DECLARE_METATYPE(cLineEdit*)

#endif // CLINEEDIT_H
