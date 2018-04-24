#ifndef CSCENEWINDOW_H
#define CSCENEWINDOW_H


#include "cpart.h"
#include "cchapter.h"
#include "cscene.h"

#include <QWidget>
#include <QStandardItemModel>


namespace Ui {
class cSceneWindow;
}

class cSceneWindow : public QWidget
{
	Q_OBJECT

public:
	explicit cSceneWindow(QWidget *parent = 0);
	~cSceneWindow();

	void				setScene(cScene* lpScene);
	cScene*				scene();

private slots:
	void				on_m_lpState_currentIndexChanged(int index);

private:
	Ui::cSceneWindow*	ui;
	QStandardItemModel*	m_lpCharacterModel;
	QStandardItemModel*	m_lpPlaceModel;
	QStandardItemModel*	m_lpObjectModel;
	cScene*				m_lpScene;
};

#endif // CSCENEWINDOW_H
