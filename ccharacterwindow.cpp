#include "ccharacterwindow.h"
#include "ui_ccharacterwindow.h"

cCharacterWindow::cCharacterWindow(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::cCharacterWindow)
{
	ui->setupUi(this);
}

cCharacterWindow::~cCharacterWindow()
{
	delete ui;
}
