#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H


#include "cstorybook.h"

#include <QMainWindow>
#include <QMdiSubWindow>

#include <QStandardItemModel>

#include <QCloseEvent>


namespace Ui {
class cMainWindow;
}

class cMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit cMainWindow(QWidget *parent = 0);
	~cMainWindow();

	void				updateWindowTitle();

private slots:
	void				onMainTabCurrentChanged(int index);
	void				onMainTabTabCloseRequested(int index);
	void				onMdiAreaSubWindowActivated(QMdiSubWindow *arg1);

private:
	Ui::cMainWindow*	ui;
	QStandardItemModel*	m_lpOutlineModel;
	QStandardItemModel*	m_lpCharacterModel;
	QStandardItemModel*	m_lpPlaceModel;
	QStandardItemModel*	m_lpObjectModel;
	QStandardItemModel*	m_lpRechercheModel;
	bool				m_bUpdatingTab;
	cStoryBook*			m_lpStoryBook;

	void				initUI();
	void				createActions();

protected:
	void				closeEvent(QCloseEvent *event);
};

#endif // CMAINWINDOW_H
