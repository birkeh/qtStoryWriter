#ifndef CPLACEWINDOW_H
#define CPLACEWINDOW_H


#include "cplace.h"

#include "cmdisubwindow.h"

#include <QWidget>
#include <QStandardItemModel>


namespace Ui {
class cPlaceWindow;
}

/*!
 \brief

 \class cPlaceWindow cplacewindow.h "cplacewindow.h"
*/
class cPlaceWindow : public cMDISubWindow
{
	Q_OBJECT

public:
	/*!
	 \brief

	 \fn cPlaceWindow
	 \param parent
	*/
	explicit cPlaceWindow(QWidget *parent = 0);
	/*!
	 \brief

	 \fn ~cPlaceWindow
	*/
	~cPlaceWindow();

	/*!
	 \brief

	 \fn setPlace
	 \param lpPlace
	*/
	void					setPlace(cPlace* lpPlace);
	/*!
	 \brief

	 \fn place
	 \return cPlace
	*/
	cPlace*					place();

private:
	Ui::cPlaceWindow*		ui; /*!< TODO: describe */
	cPlace*					m_lpPlace; /*!< TODO: describe */
};

#endif // CPLACEWINDOW_H
