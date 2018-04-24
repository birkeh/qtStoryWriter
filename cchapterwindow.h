#ifndef CCHAPTERWINDOW_H
#define CCHAPTERWINDOW_H


#include "cpart.h"
#include "cchapter.h"
#include "cscene.h"

#include <QWidget>
#include <QStandardItemModel>


namespace Ui {
class cChapterWindow;
}

class cChapterWindow : public QWidget
{
	Q_OBJECT

public:
	explicit cChapterWindow(QWidget *parent = 0);
	~cChapterWindow();

	void				setChapter(cChapter* lpChapter, cSceneList* lpSceneList);
	cChapter*			chapter();

private:
	Ui::cChapterWindow *ui;
	cChapter*			m_lpChapter;
	cSceneList*			m_lpSceneList;
	QStandardItemModel*	m_lpSceneModel;
};

#endif // CCHAPTERWINDOW_H
