/*!
 \file crecherchewindow.h

*/

#ifndef CRECHERCHEWINDOW_H
#define CRECHERCHEWINDOW_H


#include "crecherche.h"

#include "cmdisubwindow.h"

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
	void					setRecherche(cRecherche* lpRecherche);
	/*!
	 \brief

	 \fn recherche
	 \return cRecherche
	*/
	cRecherche*				recherche();

private slots:
	/*!
	 \brief

	 \fn onCharacterDoubleClicked
	 \param index
	*/
	void					onCharacterDoubleClicked(const QModelIndex& index);
	/*!
	 \brief

	 \fn onPlaceDoubleClicked
	 \param index
	*/
	void					onPlaceDoubleClicked(const QModelIndex& index);
	/*!
	 \brief

	 \fn onObjectDoubleClicked
	 \param index
	*/
	void					onObjectDoubleClicked(const QModelIndex& index);

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
	Ui::cRechercheWindow*	ui; /*!< TODO: describe */
	QStandardItemModel*		m_lpCharacterModel; /*!< TODO: describe */
	QStandardItemModel*		m_lpPlaceModel; /*!< TODO: describe */
	QStandardItemModel*		m_lpObjectModel; /*!< TODO: describe */
	cRecherche*				m_lpRecherche; /*!< TODO: describe */
};

#endif // CRECHERCHEWINDOW_H
