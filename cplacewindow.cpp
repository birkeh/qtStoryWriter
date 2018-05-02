#include "cplacewindow.h"
#include "ui_cplacewindow.h"

#include "cimagewidget.h"

#include <QStandardItem>


cPlaceWindow::cPlaceWindow(QWidget *parent) :
	cMDISubWindow(parent),
	ui(new Ui::cPlaceWindow),
	m_lpPlace(0)
{
	ui->setupUi(this);
}

cPlaceWindow::~cPlaceWindow()
{
	delete ui;
}

void cPlaceWindow::setPlace(cPlace* lpPlace)
{
	m_lpPlace		= lpPlace;

	ui->m_lpName->setText(lpPlace->name());
	ui->m_lpType->setText(lpPlace->type());
	ui->m_lpLocation->setText(lpPlace->location());
	ui->m_lpDescription->setDocument(lpPlace->description());

	QList<cImage*>	images	= lpPlace->images();
	for(int x = 0;x < images.count();x++)
	{
		cImage*			lpImage			= images[x];
		QPixmap			pixmap			= lpImage->load();
		cImageWidget*	lpImageWidget	= new cImageWidget;

		lpImageWidget->setValues(lpImage->name(), lpImage->type(), lpImage->description(), pixmap);
		ui->m_lpLayout->addWidget(lpImageWidget);
	}

	QSpacerItem*	lpSpacer		= new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
	ui->m_lpLayout->addItem(lpSpacer);

	setWindowTitle(tr("[place] - ") + lpPlace->name());
}

cPlace* cPlaceWindow::place()
{
	return(m_lpPlace);
}
