#ifndef CMDISUBWINDOW_H
#define CMDISUBWINDOW_H


#include <QWidget>


class cMDISubWindow : public QWidget
{
	Q_OBJECT
public:
	explicit cMDISubWindow(QWidget *parent = nullptr);

signals:
	void					subWindowClosed(QWidget* lpWidget);

public slots:

protected:
	void					closeEvent(QCloseEvent *event);
};

#endif // CMDISUBWINDOW_H
