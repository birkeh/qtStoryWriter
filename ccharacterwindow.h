#ifndef CCHARACTERWINDOW_H
#define CCHARACTERWINDOW_H


#include "ccharacter.h"

#include <QWidget>
#include <QStandardItemModel>


namespace Ui {
class cCharacterWindow;
}

class cCharacterWindow : public QWidget
{
	Q_OBJECT

public:
	explicit cCharacterWindow(QWidget *parent = 0);
	~cCharacterWindow();

	void					setCharacter(cCharacter* lpCharacter);
	cCharacter*				character();

private:
	Ui::cCharacterWindow*	ui;
	cCharacter*				m_lpCharacter;
};

#endif // CCHARACTERWINDOW_H
