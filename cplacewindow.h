#ifndef CPLACEWINDOW_H
#define CPLACEWINDOW_H


#include "cplace.h"

#include "cmdisubwindow.h"
#include "cmainwindow.h"

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

private slots:
	/*!
	 \brief

	 \fn onNameChanged
	 \param szName
	*/
	void					onNameChanged(const QString& szName);
	/*!
	 \brief

	 \fn onTypeChanged
	 \param szName
	*/
	void					onTypeChanged(const QString& szName);
	/*!
	 \brief

	 \fn onLocationChanged
	 \param szName
	*/
	void					onLocationChanged(const QString& szName);
	/*!
	 \brief

	 \fn onDescriptionChanged
	*/
	void					onDescriptionChanged();

private:
	Ui::cPlaceWindow*		ui; /*!< TODO: describe */
	cMainWindow*			m_lpMainWindow; /*!< TODO: describe */
	cPlace*					m_lpPlace; /*!< TODO: describe */
};

#endif // CPLACEWINDOW_H
