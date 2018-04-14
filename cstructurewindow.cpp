#include "cstructurewindow.h"
#include "ui_cstructurewindow.h"

#include <QCloseEvent>


cStructureWindow::cStructureWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::cStructureWindow)
{
	ui->setupUi(this);
}

cStructureWindow::~cStructureWindow()
{
	delete ui;
}

void cStructureWindow::closeEvent(QCloseEvent *event)
{
	event->ignore();
}
