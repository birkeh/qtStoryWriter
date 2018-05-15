#ifndef CPROPERTIESWINDOW_H
#define CPROPERTIESWINDOW_H


#include "cbook.h"

#include "cmdisubwindow.h"
#include "cmainwindow.h"


#include <QWidget>


namespace Ui {
class cPropertiesWindow;
}

class cPropertiesWindow : public cMDISubWindow
{
	Q_OBJECT

public:
	explicit cPropertiesWindow(QWidget *parent = 0);
	~cPropertiesWindow();

	void					setBook(cBook* lpBook);
	cBook*					book();

private slots:
	void					onTitleChanged(const QString& szName);
	void					onSubTitleChanged(const QString& szName);
	void					onAuthorChanged(const QString& szName);
	void					onShortDescriptionChanged();
	void					onDescriptionChanged();
	void					onStartedAtChanged(const QDateTime& dateTime);
	void					onFinishedAtChanged(const QDateTime& dateTime);
	void					onTargetDateChanged(const QDateTime& dateTime);

private:
	Ui::cPropertiesWindow*	ui;
	cMainWindow*			m_lpMainWindow;
	cBook*					m_lpBook;
};

#endif // CPROPERTIESWINDOW_H
