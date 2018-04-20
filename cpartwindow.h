#ifndef CPARTWINDOW_H
#define CPARTWINDOW_H


#include "cpart.h"

#include <QWidget>


namespace Ui {
class cPartWindow;
}

class cPartWindow : public QWidget
{
	Q_OBJECT

public:
	explicit cPartWindow(QWidget *parent = 0);
	~cPartWindow();

	void				setPart(cPart* lpPart);
private:
	Ui::cPartWindow*	ui;
	cPart*				m_lpPart;
};

#endif // CPARTWINDOW_H
