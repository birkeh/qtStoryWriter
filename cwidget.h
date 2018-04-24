#ifndef CWIDGET_H
#define CWIDGET_H


#include "cpartwindow.h"

#include <QWidget>
#include <QMdiSubWindow>


class cWidget : public QWidget
{
	Q_OBJECT
public:
	enum TYPE
	{
		TYPE_unknown	= 0,
		TYPE_part		= 1,
	};

	explicit			cWidget(cPartWindow* parent);
	explicit			cWidget(QWidget* parent);

	QWidget*			widget();

	void				setWindow(QMdiSubWindow* lpWindow);
	QMdiSubWindow*		window();

	TYPE				type();
signals:

public slots:

private:
	TYPE				m_type;
	QWidget*			m_lpWidget;
	QMdiSubWindow*		m_lpWindow;
};

#endif // CWIDGET_H
