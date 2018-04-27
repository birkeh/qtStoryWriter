#ifndef CPLACEWINDOW_H
#define CPLACEWINDOW_H


#include "cplace.h"

#include <QWidget>
#include <QStandardItemModel>


namespace Ui {
class cPlaceWindow;
}

class cPlaceWindow : public QWidget
{
	Q_OBJECT

public:
	explicit cPlaceWindow(QWidget *parent = 0);
	~cPlaceWindow();

	void					setPlace(cPlace* lpPlace);
	cPlace*					place();

private:
	Ui::cPlaceWindow*		ui;
	cPlace*					m_lpPlace;
};

#endif // CPLACEWINDOW_H
