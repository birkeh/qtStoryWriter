#include "cmainwindow.h"
#include "ui_cmainwindow.h"

#include "ctextdocument.h"
#include "cdocumentreader.h"

#include "cstructurewindow.h"
#include "cwidget.h"

#include <QTextDocument>
#include <QTextBlockFormat>
#include <QTextCharFormat>


cMainWindow::cMainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::cMainWindow),
	m_bUpdatingTab(false),
	m_lpStoryBook(0)
{
	initUI();
	createActions();

	m_lpStoryBook	= new cStoryBook("c:/temp/qtStoryWriter/DerAdler");

	cStructureWindow*	lpStructureWindow	= new cStructureWindow(this);
	cWidget*	lpWidget1	= new cWidget(lpStructureWindow);
	lpWidget1->setWindow(ui->m_lpMdiArea->addSubWindow(lpStructureWindow));

	QMainWindow*		lpMainWindow		= new QMainWindow(this);
	lpMainWindow->setWindowTitle("Bla");
	cWidget*	lpWidget2	= new cWidget(lpMainWindow);
	lpWidget2->setWindow(ui->m_lpMdiArea->addSubWindow(lpMainWindow));

	ui->m_lpMainTab->addTab((QWidget*)lpWidget1, "Structure");
	ui->m_lpMainTab->addTab((QWidget*)lpWidget2, "Bla");
}

cMainWindow::~cMainWindow()
{
	if(m_lpStoryBook)
		delete m_lpStoryBook;

	delete ui;
}

void cMainWindow::initUI()
{
	ui->setupUi(this);

	ui->m_lpMainToolBox->setCurrentIndex(0);
}

void cMainWindow::createActions()
{
	connect(ui->m_lpMainTab, SIGNAL(currentChanged(int)), this, SLOT(onMainTabCurrentChanged(int)));
	connect(ui->m_lpMainTab, SIGNAL(tabCloseRequested(int)), this,SLOT(onMainTabTabCloseRequested(int)));
	connect(ui->m_lpMdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(onMdiAreaSubWindowActivated(QMdiSubWindow*)));
}

void cMainWindow::onMainTabCurrentChanged(int index)
{
	if(m_bUpdatingTab)
		return;

	m_bUpdatingTab	= true;
	cWidget*		lpWidget	= (cWidget*)ui->m_lpMainTab->currentWidget();
	QMdiSubWindow*	lpWindow	= lpWidget->window();
	ui->m_lpMdiArea->setActiveSubWindow(lpWindow);
	m_bUpdatingTab	= false;
}

void cMainWindow::onMainTabTabCloseRequested(int index)
{
	if(m_bUpdatingTab)
		return;

	m_bUpdatingTab	= true;
	cWidget*		lpWidget	= (cWidget*)ui->m_lpMainTab->currentWidget();
	QMdiSubWindow*	lpWindow	= lpWidget->window();
	ui->m_lpMainTab->removeTab(index);
	ui->m_lpMdiArea->removeSubWindow(lpWindow);
	delete(lpWidget);
	m_bUpdatingTab	= false;
}

void cMainWindow::onMdiAreaSubWindowActivated(QMdiSubWindow *arg1)
{
	if(m_bUpdatingTab)
		return;

	m_bUpdatingTab	= true;

	for(int x = 0;x < ui->m_lpMainTab->count();x++)
	{
		cWidget*	lpWidget	= (cWidget*)ui->m_lpMainTab->widget(x);
		if(lpWidget->window() == arg1)
		{
			ui->m_lpMainTab->setCurrentIndex(x);
			m_bUpdatingTab	= false;
			return;
		}
	}
	m_bUpdatingTab	= false;
}
