#include "cmainwindow.h"
#include "ui_cmainwindow.h"

#include "ctextdocument.h"

#include "cstructurewindow.h"
#include "cwidget.h"

#include <QTextDocument>
#include <QTextBlockFormat>
#include <QTextCharFormat>

#include <QSettings>

#include <QDir>


#include <QTextEdit>

cMainWindow::cMainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::cMainWindow),
	m_lpOutlineModel(0),
	m_bUpdatingTab(false),
	m_lpStoryBook(0)
{
	initUI();
	createActions();

	QString		szPath	= QDir::homePath() + QDir::separator() + "OneDrive - WINDESIGN" + QDir::separator() + "__BOOKS__" + QDir::separator() + "qtStoryWriter" + QDir::separator() + "DerAdler";
	m_lpStoryBook		= new cStoryBook(szPath);
	m_lpStoryBook->fillOutlineList(ui->m_lpOutline);
	ui->m_lpOutline->expandAll();
	ui->m_lpOutline->resizeColumnToContents(0);
	ui->m_lpOutline->resizeColumnToContents(1);

	updateWindowTitle();

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

void cMainWindow::closeEvent(QCloseEvent *event)
{
	QSettings	settings;
	settings.setValue("main/width", QVariant::fromValue(size().width()));
	settings.setValue("main/height", QVariant::fromValue(size().height()));
	settings.setValue("main/x", QVariant::fromValue(x()));
	settings.setValue("main/y", QVariant::fromValue(y()));
	settings.setValue("main/splitter1", QVariant::fromValue(ui->m_lpMainSplitter->sizes()[0]));
	settings.setValue("main/splitter2", QVariant::fromValue(ui->m_lpMainSplitter->sizes()[1]));
	if(this->isMaximized())
		settings.setValue("main/maximized", QVariant::fromValue(true));
	else
		settings.setValue("main/maximized", QVariant::fromValue(false));

	event->accept();
}

void cMainWindow::initUI()
{
	ui->setupUi(this);

	m_lpOutlineModel	= new QStandardItemModel(0, 1);
	ui->m_lpOutline->setModel(m_lpOutlineModel);

	QSettings	settings;
	qint16		iX			= settings.value("main/x", QVariant::fromValue(-1)).toInt();
	qint16		iY			= settings.value("main/y", QVariant::fromValue(-1)).toInt();
	qint16		iWidth		= settings.value("main/width", QVariant::fromValue(-1)).toInt();
	qint16		iHeight		= settings.value("main/height", QVariant::fromValue(-1)).toInt();
	qint16		iSplitter1	= settings.value("main/splitter1", QVariant::fromValue(-1)).toInt();
	qint16		iSplitter2	= settings.value("main/splitter2", QVariant::fromValue(-1)).toInt();

	if(iWidth != -1 && iHeight != -1)
		resize(iWidth, iHeight);
	if(iX != -1 && iY != -1)
		move(iX, iY);

	if(iSplitter1 != -1 && iSplitter2 != -1)
		ui->m_lpMainSplitter->setSizes(QList<int>() << iSplitter1 << iSplitter2);

	ui->m_lpMainToolBox->setCurrentIndex(0);
}

void cMainWindow::createActions()
{
	connect(ui->m_lpMainTab, SIGNAL(currentChanged(int)), this, SLOT(onMainTabCurrentChanged(int)));
	connect(ui->m_lpMainTab, SIGNAL(tabCloseRequested(int)), this,SLOT(onMainTabTabCloseRequested(int)));
	connect(ui->m_lpMdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(onMdiAreaSubWindowActivated(QMdiSubWindow*)));
}

void cMainWindow::updateWindowTitle()
{
	if(!m_lpStoryBook)
	{
		setWindowTitle("qtStoryWriter");
		return;
	}

	QString	szTitle		= m_lpStoryBook->title();
	QString	szAuthor	= m_lpStoryBook->author();

	if(szAuthor.isEmpty())
		setWindowTitle(QString("%1 - qtStoryWriter").arg(szTitle));
	else
		setWindowTitle(QString("%1 by %2 - qtStoryWriter").arg(szTitle).arg(szAuthor));
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
