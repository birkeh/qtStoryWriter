#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H


#include "cstorybook.h"

#include <QMainWindow>
#include <QMdiSubWindow>


namespace Ui {
class cMainWindow;
}

class cMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit cMainWindow(QWidget *parent = 0);
	~cMainWindow();

private slots:
	void				onMainTabCurrentChanged(int index);
	void				onMainTabTabCloseRequested(int index);
	void				onMdiAreaSubWindowActivated(QMdiSubWindow *arg1);

private:
	Ui::cMainWindow*	ui;
	bool				m_bUpdatingTab;
	cStoryBook*			m_lpStoryBook;

	void				initUI();
	void				createActions();
};

#endif // CMAINWINDOW_H
