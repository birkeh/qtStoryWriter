/*!
 \file cimagewidget.cpp

*/

#include "cimagewidget.h"
#include "ui_cimagewidget.h"

#include "cmainwindow.h"

#include "common.h"


cImageWidget::cImageWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::cImageWidget)
{
	ui->setupUi(this);

// CONNECT CURRENTLY NOT POSSIBLE
	connect(ui->m_lpDescription, SIGNAL(gotFocus(cTextEdit*)), (cMainWindow*)parent, SLOT(onTextEditGotFocus(cTextEdit*)));
	connect(ui->m_lpDescription, SIGNAL(lostFocus(cTextEdit*)), (cMainWindow*)parent, SLOT(onTextEditLostFocus(cTextEdit*)));
}

cImageWidget::~cImageWidget()
{
	delete ui;
}

void cImageWidget::setValues(const QString &szName, const QString &szType, cTextDocument* lpDocument, const QPixmap &pixmap)
{
	ui->m_lpName->setTitle(szName);
	ui->m_lpType->setText(szType);
	ui->m_lpDescription->setDocument(lpDocument);
	if(pixmap.width() > 200)
		ui->m_lpImage->setPixmap(pixmap.scaled(200, 9999, Qt::KeepAspectRatio));
	else
		ui->m_lpImage->setPixmap(pixmap);
}
