#ifndef CRECHERCHEWINDOW_H
#define CRECHERCHEWINDOW_H


#include "crecherche.h"

#include "cmdisubwindow.h"
#include "cmainwindow.h"

#include <QWidget>
#include <QStandardItemModel>


namespace Ui {
class cRechercheWindow;
}

/*!
 \brief

 \class cRechercheWindow crecherchewindow.h "crecherchewindow.h"
*/
class cRechercheWindow : public cMDISubWindow
{
	Q_OBJECT

public:
	/*!
	 \brief

	 \fn cRechercheWindow
	 \param parent
	*/
	explicit cRechercheWindow(QWidget *parent = 0);
	/*!
	 \brief

	 \fn ~cRechercheWindow
	*/
	~cRechercheWindow();

	/*!
	 \brief

	 \fn setRecherche
	 \param lpRecherche
	*/
	void					setRecherche(cRecherche* lpRecherche, cCharacterList* lpCharacterList, cPlaceList* lpPlaceList, cObjectList* lpObjectList);
	/*!
	 \brief

	 \fn recherche
	 \return cRecherche
	*/
	cRecherche*				recherche();

	/*!
	 \brief

	 \fn retranslateUI
	*/
	void					retranslateUI();

private:
	/*!
	 \brief

	 \fn fillCharacterList
	 \param bSelectFirst
	*/
	void					fillCharacterList(cCharacter* lpCharacterNew = 0);
	/*!
	 \brief

	 \fn fillPlaceList
	 \param bSelectFirst
	*/
	void					fillPlaceList(cPlace* lpPlaceNew = 0);
	/*!
	 \brief

	 \fn fillObjectList
	 \param bSelectFirst
	*/
	void					fillObjectList(cObject* lpObjectNew = 0);

private slots:

	/*!
	 \brief

	 \fn onNameChanged
	 \param szName
	*/
	void					onNameChanged(const QString& szName);
	/*!
	 \brief

	 \fn onLinkChanged
	 \param szName
	*/
	void					onLinkChanged(const QString& szName);
	/*!
	 \brief

	 \fn onDescriptionChanged
	*/
	void					onDescriptionChanged();

	/*!
	 \brief

	 \fn onCharacterDescriptionChanged
	*/
	void					onCharacterDescriptionChanged();

	/*!
	 \brief

	 \fn onPlaceDescriptionChanged
	*/
	void					onPlaceDescriptionChanged();

	/*!
	 \brief

	 \fn onPlaceDescriptionChanged
	*/
	void					onObjectDescriptionChanged();

	/*!
	 \brief

	 \fn onCharacterIndexChanged
	 \param index
	*/
	void					onCharacterIndexChanged(int index);
	/*!
	 \brief

	 \fn onPlaceIndexChanged
	 \param index
	*/
	void					onPlaceIndexChanged(int index);
	/*!
	 \brief

	 \fn onObjectIndexChanged
	 \param index
	*/
	void					onObjectIndexChanged(int index);

	/*!
	 \brief

	 \fn onAddCharacterToList
	*/
	void					onAddCharacterToList();
	/*!
	 \brief

	 \fn onRemoveCharacterFromList
	*/
	void					onRemoveCharacterFromList();

	/*!
	 \brief

	 \fn onAddPlaceToList
	*/
	void					onAddPlaceToList();
	/*!
	 \brief

	 \fn onRemovePlaceFromList
	*/
	void					onRemovePlaceFromList();

	/*!
	 \brief

	 \fn onAddObjectToList
	*/
	void					onAddObjectToList();
	/*!
	 \brief

	 \fn onRemoveObjectFromList
	*/
	void					onRemoveObjectFromList();

signals:
	/*!
	 \brief

	 \fn showCharacterWindow
	 \param lpCharacter
	*/
	void					showCharacterWindow(cCharacter* lpCharacter);
	/*!
	 \brief

	 \fn showPlaceWindow
	 \param lpPlace
	*/
	void					showPlaceWindow(cPlace* lpPlace);
	/*!
	 \brief

	 \fn showObjectWindow
	 \param lpObject
	*/
	void					showObjectWindow(cObject* lpObject);

private:
	Ui::cRechercheWindow*	ui;					/*!< TODO: describe */
	cMainWindow*			m_lpMainWindow;		/*!< TODO: describe */
	cRecherche*				m_lpRecherche;		/*!< TODO: describe */
	cCharacterList*			m_lpCharacterList;	/*!< TODO: describe */
	cPlaceList*				m_lpPlaceList;		/*!< TODO: describe */
	cObjectList*			m_lpObjectList;		/*!< TODO: describe */
};

#endif // CRECHERCHEWINDOW_H
