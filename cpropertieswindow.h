#ifndef CPROPERTIESWINDOW_H
#define CPROPERTIESWINDOW_H


#include "cbook.h"

#include "cmdisubwindow.h"
#include "cmainwindow.h"


#include <QWidget>


namespace Ui {
class cPropertiesWindow;
}

/*!
 \brief

 \class cPropertiesWindow cpropertieswindow.h "cpropertieswindow.h"
*/
class cPropertiesWindow : public cMDISubWindow
{
	Q_OBJECT

public:
	/*!
	 \brief

	 \fn cPropertiesWindow
	 \param parent
	*/
	explicit cPropertiesWindow(QWidget *parent = 0);
	/*!
	 \brief

	 \fn ~cPropertiesWindow
	*/
	~cPropertiesWindow();

	/*!
	 \brief

	 \fn setBook
	 \param lpBook
	*/
	void					setBook(cBook* lpBook);
	/*!
	 \brief

	 \fn book
	 \return cBook
	*/
	cBook*					book();

	/*!
	 \brief

	 \fn retranslateUI
	*/
	void					retranslateUI();

private slots:
	/*!
	 \brief

	 \fn onTitleChanged
	 \param szName
	*/
	void					onTitleChanged(const QString& szName);
	/*!
	 \brief

	 \fn onSubTitleChanged
	 \param szName
	*/
	void					onSubTitleChanged(const QString& szName);
	/*!
	 \brief

	 \fn onAuthorChanged
	 \param szName
	*/
	void					onAuthorChanged(const QString& szName);
	/*!
	 \brief

	 \fn onShortDescriptionChanged
	*/
	void					onShortDescriptionChanged();
	/*!
	 \brief

	 \fn onDescriptionChanged
	*/
	void					onDescriptionChanged();
	/*!
	 \brief

	 \fn onStartedAtChanged
	 \param dateTime
	*/
	void					onStartedAtChanged(const QDateTime& dateTime);
	/*!
	 \brief

	 \fn onFinishedAtChanged
	 \param dateTime
	*/
	void					onFinishedAtChanged(const QDateTime& dateTime);
	/*!
	 \brief

	 \fn onTargetDateChanged
	 \param dateTime
	*/
	void					onTargetDateChanged(const QDateTime& dateTime);

private:
	Ui::cPropertiesWindow*	ui;				/*!< TODO: describe */
	cMainWindow*			m_lpMainWindow;	/*!< TODO: describe */
	cBook*					m_lpBook;		/*!< TODO: describe */
};

#endif // CPROPERTIESWINDOW_H
