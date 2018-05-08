#ifndef COBJECTWINDOW_H
#define COBJECTWINDOW_H


#include "cobject.h"

#include "cmdisubwindow.h"

#include <QWidget>
#include <QStandardItemModel>


namespace Ui {
class cObjectWindow;
}

/*!
 \brief

 \class cObjectWindow cobjectwindow.h "cobjectwindow.h"
*/
class cObjectWindow : public cMDISubWindow
{
	Q_OBJECT

public:
	/*!
	 \brief

	 \fn cObjectWindow
	 \param parent
	*/
	explicit cObjectWindow(QWidget *parent = 0);
	/*!
	 \brief

	 \fn ~cObjectWindow
	*/
	~cObjectWindow();

	/*!
	 \brief

	 \fn setObject
	 \param lpObject
	*/
	void					setObject(cObject* lpObject);
	/*!
	 \brief

	 \fn object
	 \return cObject
	*/
	cObject*				object();

private:
	Ui::cObjectWindow*		ui; /*!< TODO: describe */
	cObject*				m_lpObject; /*!< TODO: describe */
};

#endif // COBJECTWINDOW_H
