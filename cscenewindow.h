#ifndef CSCENEWINDOW_H
#define CSCENEWINDOW_H


#include "cpart.h"
#include "cchapter.h"
#include "cscene.h"

#include "cmdisubwindow.h"
#include "cmainwindow.h"

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
	void				setScene(cScene* lpScene, cCharacterList* lpCharacterList, cPlaceList* lpPlaceList, cObjectList* lpObjectList);
	/*!
	 \brief

	 \fn scene
	 \return cScene
	*/
	cScene*				scene();

private slots:
	/*!
	 \brief

	 \fn onCharacterDoubleClicked
	 \param index
	*/
	void				onCharacterShowDetails();
	/*!
	 \brief

	 \fn onPlaceDoubleClicked
	 \param index
	*/
	void				onPlaceShowDetails();
	/*!
	 \brief

	 \fn onObjectDoubleClicked
	 \param index
	*/
	void				onObjectShowDetails();

	/*!
	 \brief

	 \fn onNameChanged
	*/
	void				onNameChanged(const QString& szName);
	/*!
	 \brief

	 \fn onDescriptionChanged
	*/
	void				onDescriptionChanged();
	/*!
	 \brief

	 \fn onStateChanged
	 \param index
	*/
	void				onStateChanged(int index);
	/*!
	 \brief

	 \fn onStartedChanged
	 \param dateTime
	*/
	void				onStartedChanged(const QDateTime& dateTime);
	/*!
	 \brief

	 \fn onFinishedChanged
	 \param dateTime
	*/
	void				onFinishedChanged(const QDateTime& dateTime);
	/*!
	 \brief

	 \fn onTargetDateChanged
	 \param dateTime
	*/
	void				onTargetDateChanged(const QDateTime& dateTime);
	/*!
	 \brief

	 \fn onTextChanged
	*/
	void				onTextChanged();

	/*!
	 \brief

	 \fn onCharacterDescriptionChanged
	*/
	void				onCharacterDescriptionChanged();

	/*!
	 \brief

	 \fn onPlaceDescriptionChanged
	*/
	void				onPlaceDescriptionChanged();

	/*!
	 \brief

	 \fn onPlaceDescriptionChanged
	*/
	void				onObjectDescriptionChanged();

	/*!
	 \brief

	 \fn onCharacterIndexChanged
	 \param index
	*/
	void				onCharacterIndexChanged(int index);
	/*!
	 \brief

	 \fn onPlaceIndexChanged
	 \param index
	*/
	void				onPlaceIndexChanged(int index);
	/*!
	 \brief

	 \fn onObjectIndexChanged
	 \param index
	*/
	void				onObjectIndexChanged(int index);

	/*!
	 \brief

	 \fn onAddCharacterToList
	*/
	void				onAddCharacterToList();
	/*!
	 \brief

	 \fn onRemoveCharacterFromList
	*/
	void				onRemoveCharacterFromList();

	/*!
	 \brief

	 \fn onAddPlaceToList
	*/
	void				onAddPlaceToList();
	/*!
	 \brief

	 \fn onRemovePlaceFromList
	*/
	void				onRemovePlaceFromList();

	/*!
	 \brief

	 \fn onAddObjectToList
	*/
	void				onAddObjectToList();
	/*!
	 \brief

	 \fn onRemoveObjectFromList
	*/
	void				onRemoveObjectFromList();

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
	Ui::cSceneWindow*	ui;					/*!< TODO: describe */
	cMainWindow*		m_lpMainWindow;		/*!< TODO: describe */
	cScene*				m_lpScene;			/*!< TODO: describe */
	cCharacterList*		m_lpCharacterList;	/*!< TODO: describe */
	cPlaceList*			m_lpPlaceList;		/*!< TODO: describe */
	cObjectList*		m_lpObjectList;		/*!< TODO: describe */
};

#endif // CSCENEWINDOW_H
