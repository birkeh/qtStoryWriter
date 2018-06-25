#ifndef CCHAPTERWINDOW_H
#define CCHAPTERWINDOW_H


#include "cpart.h"
#include "cchapter.h"
#include "cscene.h"

#include "cmdisubwindow.h"
#include "cmainwindow.h"

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
	void					setChapter(cChapter* lpChapter, cSceneList* lpSceneList);
	/*!
	 \brief

	 \fn chapter
	 \return cChapter
	*/
	cChapter*				chapter();

	/*!
	 \brief

	 \fn retranslateUI
	*/
	void					retranslateUI();

private slots:
	/*!
	 \brief

	 \fn onSceneDoubleClicked
	 \param index
	*/
	void					onSceneDoubleClicked(const QModelIndex& index);

	/*!
	 \brief

	 \fn onNameChanged
	 \param szName
	*/
	void					onNameChanged(const QString& szName);
	/*!
	 \brief

	 \fn onDescriptionChanged
	*/
	void					onDescriptionChanged();
	/*!
	 \brief

	 \fn onTextChanged
	*/
	void					onTextChanged();

signals:
	/*!
	 \brief

	 \fn showSceneWindow
	 \param lpScene
	*/
	void					showSceneWindow(cScene* lpScene);

private:
	Ui::cChapterWindow*		ui;				/*!< TODO: describe */
	cMainWindow*			m_lpMainWindow;	/*!< TODO: describe */
	cChapter*				m_lpChapter;	/*!< TODO: describe */
	cSceneList*				m_lpSceneList;	/*!< TODO: describe */
	QStandardItemModel*		m_lpSceneModel;	/*!< TODO: describe */
};

#endif // CCHAPTERWINDOW_H
