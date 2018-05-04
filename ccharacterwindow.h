/*!
 \file ccharacterwindow.h

*/

#ifndef CCHARACTERWINDOW_H
#define CCHARACTERWINDOW_H


#include "ccharacter.h"

#include "cmdisubwindow.h"

#include <QWidget>
#include <QStandardItemModel>


namespace Ui {
class cCharacterWindow;
}

/*!
 \brief

 \class cCharacterWindow ccharacterwindow.h "ccharacterwindow.h"
*/
class cCharacterWindow : public cMDISubWindow
{
	Q_OBJECT

public:
	/*!
	 \brief

	 \fn cCharacterWindow
	 \param parent
	*/
	explicit cCharacterWindow(QWidget *parent = 0);
	/*!
	 \brief

	 \fn ~cCharacterWindow
	*/
	~cCharacterWindow();

	/*!
	 \brief

	 \fn setCharacter
	 \param lpCharacter
	*/
	void					setCharacter(cCharacter* lpCharacter);
	/*!
	 \brief

	 \fn character
	 \return cCharacter
	*/
	cCharacter*				character();

private:
	Ui::cCharacterWindow*	ui; /*!< TODO: describe */
	cCharacter*				m_lpCharacter; /*!< TODO: describe */
};

#endif // CCHARACTERWINDOW_H
