#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

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

	void on_m_lpMainTab_currentChanged(int index);
	void on_m_lpMdiArea_subWindowActivated(QMdiSubWindow *arg1);

private:
	Ui::cMainWindow*	ui;

	bool				m_bUpdatingTab;
};

#endif // CMAINWINDOW_H
