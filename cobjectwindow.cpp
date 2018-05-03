#include "cobjectwindow.h"
#include "ui_cobjectwindow.h"

#include "cimagewidget.h"

#include "cmainwindow.h"

#include <QStandardItem>


cObjectWindow::cObjectWindow(QWidget *parent) :
	cMDISubWindow(parent),
	ui(new Ui::cObjectWindow),
	m_lpObject(0)
{
	ui->setupUi(this);

	connect(ui->m_lpName, SIGNAL(gotFocus(cLineEdit*)), (cMainWindow*)parent, SLOT(onLineEditGotFocus(cLineEdit*)));
	connect(ui->m_lpName, SIGNAL(lostFocus(cLineEdit*)), (cMainWindow*)parent, SLOT(onLineEditLostFocus(cLineEdit*)));

	connect(ui->m_lpType, SIGNAL(gotFocus(cLineEdit*)), (cMainWindow*)parent, SLOT(onLineEditGotFocus(cLineEdit*)));
	connect(ui->m_lpType, SIGNAL(lostFocus(cLineEdit*)), (cMainWindow*)parent, SLOT(onLineEditLostFocus(cLineEdit*)));

	connect(ui->m_lpDescription, SIGNAL(gotFocus(cTextEdit*)), (cMainWindow*)parent, SLOT(onTextEditGotFocus(cTextEdit*)));
	connect(ui->m_lpDescription, SIGNAL(lostFocus(cTextEdit*)), (cMainWindow*)parent, SLOT(onTextEditLostFocus(cTextEdit*)));
}

cObjectWindow::~cObjectWindow()
{
	delete ui;
}

void cObjectWindow::setObject(cObject* lpObject)
{
	m_lpObject		= lpObject;

	ui->m_lpName->setText(lpObject->name());
	ui->m_lpType->setText(lpObject->type());
	ui->m_lpDescription->setDocument(lpObject->description());

	QList<cImage*>	images	= lpObject->images();
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

	setWindowTitle(tr("[object] - ") + lpObject->name());
}

cObject* cObjectWindow::object()
{
	return(m_lpObject);
}
