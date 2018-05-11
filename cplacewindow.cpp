/*!
 \file cplacewindow.cpp

*/

#include "cplacewindow.h"
#include "ui_cplacewindow.h"

#include "cimagewidget.h"

#include "cmainwindow.h"

#include "common.h"

#include <QStandardItem>


cPlaceWindow::cPlaceWindow(QWidget *parent) :
	cMDISubWindow(parent),
	ui(new Ui::cPlaceWindow),
	m_lpMainWindow((cMainWindow*)parent),
	m_lpPlace(0)
{
	ui->setupUi(this);

	connect(ui->m_lpName,			&cLineEdit::gotFocus,	(cMainWindow*)parent,	&cMainWindow::onLineEditGotFocus);
	connect(ui->m_lpName,			&cLineEdit::lostFocus,	(cMainWindow*)parent,	&cMainWindow::onLineEditLostFocus);

	connect(ui->m_lpType,			&cLineEdit::gotFocus,	(cMainWindow*)parent,	&cMainWindow::onLineEditGotFocus);
	connect(ui->m_lpType,			&cLineEdit::lostFocus,	(cMainWindow*)parent,	&cMainWindow::onLineEditLostFocus);

	connect(ui->m_lpLocation,		&cLineEdit::gotFocus,	(cMainWindow*)parent,	&cMainWindow::onLineEditGotFocus);
	connect(ui->m_lpLocation,		&cLineEdit::lostFocus,	(cMainWindow*)parent,	&cMainWindow::onLineEditLostFocus);

	connect(ui->m_lpDescription,	&cTextEdit::gotFocus,	(cMainWindow*)parent,	&cMainWindow::onTextEditGotFocus);
	connect(ui->m_lpDescription,	&cTextEdit::lostFocus,	(cMainWindow*)parent,	&cMainWindow::onTextEditLostFocus);
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
		QPixmap			pixmap			= lpImage->image();
		cImageWidget*	lpImageWidget	= new cImageWidget;

		lpImageWidget->setValues(lpImage->name(), lpImage->type(), lpImage->description(), pixmap);
		ui->m_lpLayout->addWidget(lpImageWidget);
	}

	QSpacerItem*	lpSpacer		= new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
	ui->m_lpLayout->addItem(lpSpacer);

	setWindowTitle(tr("[place] - ") + lpPlace->name());

	connect(ui->m_lpName,			&cLineEdit::textChanged,	this,	&cPlaceWindow::onNameChanged);
	connect(ui->m_lpType,			&cLineEdit::textChanged,	this,	&cPlaceWindow::onTypeChanged);
	connect(ui->m_lpLocation,		&cLineEdit::textChanged,	this,	&cPlaceWindow::onLocationChanged);
	connect(ui->m_lpDescription,	&cTextEdit::textChanged,	this,	&cPlaceWindow::onDescriptionChanged);
}

cPlace* cPlaceWindow::place()
{
	return(m_lpPlace);
}

void cPlaceWindow::onNameChanged(const QString& szName)
{
	m_lpPlace->setName(szName);
	m_lpMainWindow->somethingChanged();
}

void cPlaceWindow::onTypeChanged(const QString& szName)
{
	m_lpPlace->setType(szName);
	m_lpMainWindow->somethingChanged();
}

void cPlaceWindow::onLocationChanged(const QString& szName)
{
	m_lpPlace->setLocation(szName);
	m_lpMainWindow->somethingChanged();
}

void cPlaceWindow::onDescriptionChanged()
{
	m_lpMainWindow->somethingChanged();
}
