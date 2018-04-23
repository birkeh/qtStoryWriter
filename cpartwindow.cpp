#include "cpartwindow.h"
#include "ui_cpartwindow.h"


cPartWindow::cPartWindow(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::cPartWindow),
	m_lpPart(0)
{
	ui->setupUi(this);
}

cPartWindow::~cPartWindow()
{
	delete ui;
}

void cPartWindow::setPart(cPart* lpPart)
{
	m_lpPart			= lpPart;
	ui->m_lpName->setText(lpPart->name());
	ui->m_lpDescription->setDocument(lpPart->description());
	ui->m_lpText->setDocument(lpPart->text());

	setWindowTitle(tr("[part] - ") + lpPart->name());
}
