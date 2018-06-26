#include "cpropertieswindow.h"
#include "ui_cpropertieswindow.h"

#include "cmainwindow.h"

#include "common.h"


cPropertiesWindow::cPropertiesWindow(QWidget *parent) :
	cMDISubWindow(parent),
	ui(new Ui::cPropertiesWindow),
	m_lpMainWindow((cMainWindow*)parent),
	m_lpBook(0)
{
	ui->setupUi(this);
	ui->m_lpTab->setCurrentIndex(0);

	connect(ui->m_lpTitle,				&cLineEdit::gotFocus,	(cMainWindow*)parent,		&cMainWindow::onLineEditGotFocus);
	connect(ui->m_lpTitle,				&cLineEdit::lostFocus,	(cMainWindow*)parent,		&cMainWindow::onLineEditLostFocus);

	connect(ui->m_lpSubTitle,			&cLineEdit::gotFocus,	(cMainWindow*)parent,		&cMainWindow::onLineEditGotFocus);
	connect(ui->m_lpSubTitle,			&cLineEdit::lostFocus,	(cMainWindow*)parent,		&cMainWindow::onLineEditLostFocus);

	connect(ui->m_lpAuthor,				&cLineEdit::gotFocus,	(cMainWindow*)parent,		&cMainWindow::onLineEditGotFocus);
	connect(ui->m_lpAuthor,				&cLineEdit::lostFocus,	(cMainWindow*)parent,		&cMainWindow::onLineEditLostFocus);

	connect(ui->m_lpStartedAt,			&cDateTimeEdit::gotFocus,	(cMainWindow*)parent,	&cMainWindow::onDateTimeEditGotFocus);
	connect(ui->m_lpStartedAt,			&cDateTimeEdit::lostFocus,	(cMainWindow*)parent,	&cMainWindow::onDateTimeEditLostFocus);

	connect(ui->m_lpFinishedAt,			&cDateTimeEdit::gotFocus,	(cMainWindow*)parent,	&cMainWindow::onDateTimeEditGotFocus);
	connect(ui->m_lpFinishedAt,			&cDateTimeEdit::lostFocus,	(cMainWindow*)parent,	&cMainWindow::onDateTimeEditLostFocus);

	connect(ui->m_lpTargetDate,			&cDateTimeEdit::gotFocus,	(cMainWindow*)parent,	&cMainWindow::onDateTimeEditGotFocus);
	connect(ui->m_lpTargetDate,			&cDateTimeEdit::lostFocus,	(cMainWindow*)parent,	&cMainWindow::onDateTimeEditLostFocus);

	connect(ui->m_lpShortDescription,	&cTextEdit::gotFocus,	(cMainWindow*)parent,		&cMainWindow::onTextEditGotFocus);
	connect(ui->m_lpShortDescription,	&cTextEdit::lostFocus,	(cMainWindow*)parent,		&cMainWindow::onTextEditLostFocus);

	connect(ui->m_lpDescription,		&cTextEdit::gotFocus,	(cMainWindow*)parent,		&cMainWindow::onTextEditGotFocus);
	connect(ui->m_lpDescription,		&cTextEdit::lostFocus,	(cMainWindow*)parent,		&cMainWindow::onTextEditLostFocus);
}


cPropertiesWindow::~cPropertiesWindow()
{
	delete ui;
}

void cPropertiesWindow::setBook(cBook* lpBook)
{
	m_lpBook		= lpBook;

	ui->m_lpTitle->setText(lpBook->title());
	ui->m_lpSubTitle->setText(lpBook->subTitle());
	ui->m_lpAuthor->setText(lpBook->author());
	ui->m_lpStartedAt->setDateTime(lpBook->startedAt());
	ui->m_lpFinishedAt->setDateTime(lpBook->finishedAt());
	ui->m_lpTargetDate->setDateTime(lpBook->targetDate());
	ui->m_lpShortDescription->setDocument(lpBook->shortDescription());
	ui->m_lpDescription->setDocument(lpBook->description());

	connect(ui->m_lpTitle,				&cLineEdit::textChanged,			this,	&cPropertiesWindow::onTitleChanged);
	connect(ui->m_lpSubTitle,			&cLineEdit::textChanged,			this,	&cPropertiesWindow::onSubTitleChanged);
	connect(ui->m_lpAuthor,				&cLineEdit::textChanged,			this,	&cPropertiesWindow::onAuthorChanged);
	connect(ui->m_lpStartedAt,			&cDateTimeEdit::dateTimeChanged,	this,	&cPropertiesWindow::onStartedAtChanged);
	connect(ui->m_lpFinishedAt,			&cDateTimeEdit::dateTimeChanged,	this,	&cPropertiesWindow::onFinishedAtChanged);
	connect(ui->m_lpTargetDate,			&cDateTimeEdit::dateTimeChanged,	this,	&cPropertiesWindow::onTargetDateChanged);
	connect(ui->m_lpShortDescription,	&cTextEdit::textChanged,			this,	&cPropertiesWindow::onShortDescriptionChanged);
	connect(ui->m_lpDescription,		&cTextEdit::textChanged,			this,	&cPropertiesWindow::onDescriptionChanged);
}

cBook* cPropertiesWindow::book()
{
	return(m_lpBook);
}

void cPropertiesWindow::retranslateUI()
{
	ui->retranslateUi(this);
}

void cPropertiesWindow::onTitleChanged(const QString& szName)
{
	m_lpBook->setTitle(szName);
	m_lpMainWindow->somethingChanged();
	m_lpMainWindow->updateWindowTitle();
}

void cPropertiesWindow::onSubTitleChanged(const QString& szName)
{
	m_lpBook->setSubTitle(szName);
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onShortDescriptionChanged()
{
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onAuthorChanged(const QString& szName)
{
	m_lpBook->setAuthor(szName);
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onStartedAtChanged(const QDateTime& dateTime)
{
	m_lpBook->setStartedAt(dateTime);
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onFinishedAtChanged(const QDateTime& dateTime)
{
	m_lpBook->setFinishedAt(dateTime);
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onTargetDateChanged(const QDateTime& dateTime)
{
	m_lpBook->setTargetDate(dateTime);
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onDescriptionChanged()
{
	m_lpMainWindow->somethingChanged();
}
