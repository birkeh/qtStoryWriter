#ifndef CSTRUCTUREWINDOW_H
#define CSTRUCTUREWINDOW_H

#include <QMainWindow>

namespace Ui {
class cStructureWindow;
}

class cStructureWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit				cStructureWindow(QWidget *parent = 0);
	~cStructureWindow();

protected:
	void					closeEvent(QCloseEvent *event) override;

private:
	Ui::cStructureWindow*	ui;
};

#endif // CSTRUCTUREWINDOW_H
