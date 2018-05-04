/*!
 \file cscenewindow.h

*/

#ifndef CSCENEWINDOW_H
#define CSCENEWINDOW_H


#include "cpart.h"
#include "cchapter.h"
#include "cscene.h"

#include "cmdisubwindow.h"

#include <QWidget>
#include <QStandardItemModel>


namespace Ui {
class cSceneWindow;
}

/*!
 \brief

 \class cSceneWindow cscenewindow.h "cscenewindow.h"
*/
class cSceneWindow : public cMDISubWindow
{
	Q_OBJECT

public:
	/*!
	 \brief

	 \fn cSceneWindow
	 \param parent
	*/
	explicit cSceneWindow(QWidget *parent = 0);
	/*!
	 \brief

	 \fn ~cSceneWindow
	*/
	~cSceneWindow();

	/*!
	 \brief

	 \fn setScene
	 \param lpScene
	*/
	void				setScene(cScene* lpScene);
	/*!
	 \brief

	 \fn scene
	 \return cScene
	*/
	cScene*				scene();

private slots:
	/*!
	 \brief

	 \fn onStateCurrentIndexChanged
	 \param index
	*/
	void				onStateCurrentIndexChanged(int index);
	/*!
	 \brief

	 \fn onCharacterDoubleClicked
	 \param index
	*/
	void				onCharacterDoubleClicked(const QModelIndex& index);
	/*!
	 \brief

	 \fn onPlaceDoubleClicked
	 \param index
	*/
	void				onPlaceDoubleClicked(const QModelIndex& index);
	/*!
	 \brief

	 \fn onObjectDoubleClicked
	 \param index
	*/
	void				onObjectDoubleClicked(const QModelIndex& index);

signals:
	/*!
	 \brief

	 \fn showCharacterWindow
	 \param lpCharacter
	*/
	void				showCharacterWindow(cCharacter* lpCharacter);
	/*!
	 \brief

	 \fn showPlaceWindow
	 \param lpPlace
	*/
	void				showPlaceWindow(cPlace* lpPlace);
	/*!
	 \brief

	 \fn showObjectWindow
	 \param lpObject
	*/
	void				showObjectWindow(cObject* lpObject);

private:
	Ui::cSceneWindow*	ui; /*!< TODO: describe */
	QStandardItemModel*	m_lpCharacterModel; /*!< TODO: describe */
	QStandardItemModel*	m_lpPlaceModel; /*!< TODO: describe */
	QStandardItemModel*	m_lpObjectModel; /*!< TODO: describe */
	cScene*				m_lpScene; /*!< TODO: describe */
};

#endif // CSCENEWINDOW_H
