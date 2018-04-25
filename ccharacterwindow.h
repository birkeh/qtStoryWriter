#ifndef CCHARACTERWINDOW_H
#define CCHARACTERWINDOW_H

#include <QWidget>

namespace Ui {
class cCharacterWindow;
}

class cCharacterWindow : public QWidget
{
	Q_OBJECT

public:
	explicit cCharacterWindow(QWidget *parent = 0);
	~cCharacterWindow();

private:
	Ui::cCharacterWindow *ui;
};

#endif // CCHARACTERWINDOW_H
