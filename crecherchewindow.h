#ifndef CRECHERCHEWINDOW_H
#define CRECHERCHEWINDOW_H


#include "crecherche.h"

#include "cmdisubwindow.h"

#include <QWidget>
#include <QStandardItemModel>


namespace Ui {
class cRechercheWindow;
}

class cRechercheWindow : public cMDISubWindow
{
	Q_OBJECT

public:
	explicit cRechercheWindow(QWidget *parent = 0);
	~cRechercheWindow();

	void					setRecherche(cRecherche* lpRecherche);
	cRecherche*				recherche();

private slots:
	void					onCharacterDoubleClicked(const QModelIndex& index);
	void					onPlaceDoubleClicked(const QModelIndex& index);
	void					onObjectDoubleClicked(const QModelIndex& index);

signals:
	void					showCharacterWindow(cCharacter* lpCharacter);
	void					showPlaceWindow(cPlace* lpPlace);
	void					showObjectWindow(cObject* lpObject);

private:
	Ui::cRechercheWindow*	ui;
	QStandardItemModel*		m_lpCharacterModel;
	QStandardItemModel*		m_lpPlaceModel;
	QStandardItemModel*		m_lpObjectModel;
	cRecherche*				m_lpRecherche;
};

#endif // CRECHERCHEWINDOW_H
