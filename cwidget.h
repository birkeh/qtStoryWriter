#ifndef CWIDGET_H
#define CWIDGET_H

#include <QWidget>
#include <QMdiSubWindow>


class cWidget : public QWidget
{
	Q_OBJECT
public:
	explicit			cWidget(QWidget *parent = nullptr);
	void				setWindow(QMdiSubWindow* lpWindow);
	QMdiSubWindow*		window();

signals:

public slots:

private:
	QMdiSubWindow*		m_lpWindow;
};

#endif // CWIDGET_H
