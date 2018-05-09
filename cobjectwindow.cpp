/*!
 \file cobjectwindow.cpp

*/

#include "cobjectwindow.h"
#include "ui_cobjectwindow.h"

#include "cimagewidget.h"

#include "cmainwindow.h"

#include "common.h"

#include <QStandardItem>


cObjectWindow::cObjectWindow(QWidget *parent) :
	cMDISubWindow(parent),
	ui(new Ui::cObjectWindow),
	m_lpMainWindow((cMainWindow*)parent),
	m_lpObject(0)
{
	ui->setupUi(this);

	connect(ui->m_lpName,			&cLineEdit::gotFocus,	(cMainWindow*)parent,	&cMainWindow::onLineEditGotFocus);
	connect(ui->m_lpName,			&cLineEdit::lostFocus,	(cMainWindow*)parent,	&cMainWindow::onLineEditLostFocus);

	connect(ui->m_lpType,			&cLineEdit::gotFocus,	(cMainWindow*)parent,	&cMainWindow::onLineEditGotFocus);
	connect(ui->m_lpType,			&cLineEdit::lostFocus,	(cMainWindow*)parent,	&cMainWindow::onLineEditLostFocus);

	connect(ui->m_lpDescription,	&cTextEdit::gotFocus,	(cMainWindow*)parent,	&cMainWindow::onTextEditGotFocus);
	connect(ui->m_lpDescription,	&cTextEdit::lostFocus,	(cMainWindow*)parent,	&cMainWindow::onTextEditLostFocus);
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

	connect(ui->m_lpName,			&cLineEdit::textChanged,	this,	&cObjectWindow::onNameChanged);
	connect(ui->m_lpType,			&cLineEdit::textChanged,	this,	&cObjectWindow::onTypeChanged);
	connect(ui->m_lpDescription,	&cTextEdit::textChanged,	this,	&cObjectWindow::onDescriptionChanged);
}

cObject* cObjectWindow::object()
{
	return(m_lpObject);
}

void cObjectWindow::onNameChanged(const QString& szName)
{
	m_lpObject->setName(szName);
	m_lpMainWindow->somethingChanged();
}

void cObjectWindow::onTypeChanged(const QString& szName)
{
	m_lpObject->setType(szName);
	m_lpMainWindow->somethingChanged();
}

void cObjectWindow::onDescriptionChanged()
{
	m_lpMainWindow->somethingChanged();
}
