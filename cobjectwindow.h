#ifndef COBJECTWINDOW_H
#define COBJECTWINDOW_H


#include "cobject.h"

#include "cmdisubwindow.h"

#include <QWidget>
#include <QStandardItemModel>


namespace Ui {
class cObjectWindow;
}

class cObjectWindow : public cMDISubWindow
{
	Q_OBJECT

public:
	explicit cObjectWindow(QWidget *parent = 0);
	~cObjectWindow();

	void					setObject(cObject* lpObject);
	cObject*				object();

private:
	Ui::cObjectWindow*		ui;
	cObject*				m_lpObject;
};

#endif // COBJECTWINDOW_H
