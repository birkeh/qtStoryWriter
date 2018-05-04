/*!
 \file cchapterwindow.h

*/

#ifndef CCHAPTERWINDOW_H
#define CCHAPTERWINDOW_H


#include "cpart.h"
#include "cchapter.h"
#include "cscene.h"

#include "cmdisubwindow.h"

#include <QWidget>
#include <QStandardItemModel>


namespace Ui {
class cChapterWindow;
}

/*!
 \brief

 \class cChapterWindow cchapterwindow.h "cchapterwindow.h"
*/
class cChapterWindow : public cMDISubWindow
{
	Q_OBJECT

public:
	/*!
	 \brief

	 \fn cChapterWindow
	 \param parent
	*/
	explicit cChapterWindow(QWidget *parent = 0);
	/*!
	 \brief

	 \fn ~cChapterWindow
	*/
	~cChapterWindow();

	/*!
	 \brief

	 \fn setChapter
	 \param lpChapter
	 \param lpSceneList
	*/
	void				setChapter(cChapter* lpChapter, cSceneList* lpSceneList);
	/*!
	 \brief

	 \fn chapter
	 \return cChapter
	*/
	cChapter*			chapter();

private:
	Ui::cChapterWindow *ui; /*!< TODO: describe */
	cChapter*			m_lpChapter; /*!< TODO: describe */
	cSceneList*			m_lpSceneList; /*!< TODO: describe */
	QStandardItemModel*	m_lpSceneModel; /*!< TODO: describe */
};

#endif // CCHAPTERWINDOW_H
