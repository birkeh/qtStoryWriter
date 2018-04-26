#ifndef CWIDGET_H
#define CWIDGET_H


#include "cpartwindow.h"
#include "cchapterwindow.h"
#include "cscenewindow.h"
#include "ccharacterwindow.h"

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
		TYPE_chapter	= 2,
		TYPE_scene		= 3,
		TYPE_character	= 4,
	};

	explicit			cWidget(cPartWindow* parent);
	explicit			cWidget(cChapterWindow* parent);
	explicit			cWidget(cSceneWindow* parent);
	explicit			cWidget(cCharacterWindow* parent);
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
