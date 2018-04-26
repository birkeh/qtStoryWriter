#include "cimagewidget.h"
#include "ui_cimagewidget.h"


cImageWidget::cImageWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::cImageWidget)
{
	ui->setupUi(this);
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
