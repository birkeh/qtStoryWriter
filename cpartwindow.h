#ifndef CPARTWINDOW_H
#define CPARTWINDOW_H


#include "cpart.h"
#include "cchapter.h"

#include <QWidget>
#include <QStandardItemModel>


namespace Ui {
class cPartWindow;
}

class cPartWindow : public QWidget
{
	Q_OBJECT

public:
	explicit cPartWindow(QWidget *parent = 0);
	~cPartWindow();

	void				setPart(cPart* lpPart, cChapterList* lpChapterList);
	cPart*				part();
private:
	Ui::cPartWindow*	ui;
	cPart*				m_lpPart;
	cChapterList*		m_lpChapterList;
	QStandardItemModel*	m_lpChapterModel;
};

#endif // CPARTWINDOW_H
