#include "cmainwindow.h"
#include "ui_cmainwindow.h"

#include "ctextdocument.h"

#include "cpartwindow.h"
#include "cchapterwindow.h"
#include "cscenewindow.h"

#include "cwidget.h"

#include <QTextDocument>
#include <QTextBlockFormat>
#include <QTextCharFormat>

#include <QSettings>

#include <QDir>
#include <QThread>

#include <QTextEdit>

#include <QMessageBox>


cMainWindow::cMainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::cMainWindow),
	m_lpOutlineModel(0),
	m_lpCharacterModel(0),
	m_lpPlaceModel(0),
	m_lpObjectModel(0),
	m_bUpdatingTab(false),
	m_lpStoryBook(0)
{
	initUI();
	createActions();

	QString		szPath	= QDir::homePath() + QDir::separator() + "OneDrive - WINDESIGN" + QDir::separator() + "__BOOKS__" + QDir::separator() + "qtStoryWriter" + QDir::separator() + "rückwärts.storyWriter" ;
	m_lpStoryBook		= new cStoryBook(szPath);
	m_lpStoryBook->fillOutlineList(ui->m_lpOutlineList);
	m_lpStoryBook->fillCharacterList(ui->m_lpCharacterList);
	m_lpStoryBook->fillPlaceList(ui->m_lpPlaceList);
	m_lpStoryBook->fillObjectList(ui->m_lpObjectList);
	m_lpStoryBook->fillRechercheList(ui->m_lpRechercheList);

	updateWindowTitle();
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
	ui->m_lpOutlineList->setModel(m_lpOutlineModel);

	m_lpCharacterModel	= new QStandardItemModel(0, 1);
	ui->m_lpCharacterList->setModel(m_lpCharacterModel);

	m_lpPlaceModel	= new QStandardItemModel(0, 1);
	ui->m_lpPlaceList->setModel(m_lpPlaceModel);

	m_lpObjectModel	= new QStandardItemModel(0, 1);
	ui->m_lpObjectList->setModel(m_lpObjectModel);

	m_lpRechercheModel	= new QStandardItemModel(0, 1);
	ui->m_lpRechercheList->setModel(m_lpRechercheModel);

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

	connect(ui->m_lpOutlineList, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(onOutlineDoubleClicked(QModelIndex)));
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
		setWindowTitle(QString("\"%1\" - qtStoryWriter").arg(szTitle));
	else
		setWindowTitle(QString("\"%1\" by %2 - qtStoryWriter").arg(szTitle).arg(szAuthor));
}

void cMainWindow::onMainTabCurrentChanged(int /*index*/)
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

void cMainWindow::onOutlineDoubleClicked(const QModelIndex& index)
{
	QStandardItem*	lpItem		= m_lpOutlineModel->itemFromIndex(index);
	cPart*			lpPart		= qvariant_cast<cPart*>(lpItem->data());
	cChapter*		lpChapter	= qvariant_cast<cChapter*>(lpItem->data());
	cScene*			lpScene		= qvariant_cast<cScene*>(lpItem->data());

	if(lpPart)
		showPartWindow(lpPart);
	else if(lpChapter)
		showChapterWindow(lpChapter);
	else if(lpScene)
		showSceneWindow(lpScene);
	else
		QMessageBox::information(this, "DoubleClicked", "outline");
}

void cMainWindow::showPartWindow(cPart* lpPart)
{
	for(int x = 0;x < ui->m_lpMainTab->count();x++)
	{
		cWidget*	lpWidget	= (cWidget*)ui->m_lpMainTab->widget(x);
		if(lpWidget->type() == cWidget::TYPE_part)
		{
			cPartWindow*	lpPartWindow	= (cPartWindow*)lpWidget->widget();
			if(lpPartWindow->part() == lpPart)
			{
				ui->m_lpMainTab->setCurrentIndex(x);
				ui->m_lpMdiArea->setActiveSubWindow(lpWidget->window());
				m_bUpdatingTab	= false;
				return;
			}
		}
	}

	cPartWindow*		lpPartWindow		= new cPartWindow(this);
	lpPartWindow->setPart(lpPart, m_lpStoryBook->chapterList());
	cWidget*			lpWidget1			= new cWidget(lpPartWindow);
	lpWidget1->setWindow(ui->m_lpMdiArea->addSubWindow(lpPartWindow));
	ui->m_lpMainTab->addTab((QWidget*)lpWidget1, lpPartWindow->windowTitle());

	lpPartWindow->show();
}

void cMainWindow::showChapterWindow(cChapter* lpChapter)
{
	for(int x = 0;x < ui->m_lpMainTab->count();x++)
	{
		cWidget*	lpWidget	= (cWidget*)ui->m_lpMainTab->widget(x);
		if(lpWidget->type() == cWidget::TYPE_chapter)
		{
			cChapterWindow*	lpChapterWindow	= (cChapterWindow*)lpWidget->widget();
			if(lpChapterWindow->chapter() == lpChapter)
			{
				ui->m_lpMainTab->setCurrentIndex(x);
				ui->m_lpMdiArea->setActiveSubWindow(lpWidget->window());
				m_bUpdatingTab	= false;
				return;
			}
		}
	}

	cChapterWindow*		lpChapterWindow		= new cChapterWindow(this);
	lpChapterWindow->setChapter(lpChapter, m_lpStoryBook->sceneList());
	cWidget*			lpWidget1			= new cWidget(lpChapterWindow);
	lpWidget1->setWindow(ui->m_lpMdiArea->addSubWindow(lpChapterWindow));
	ui->m_lpMainTab->addTab((QWidget*)lpWidget1, lpChapterWindow->windowTitle());

	lpChapterWindow->show();
}

void cMainWindow::showSceneWindow(cScene* lpScene)
{
	for(int x = 0;x < ui->m_lpMainTab->count();x++)
	{
		cWidget*	lpWidget	= (cWidget*)ui->m_lpMainTab->widget(x);
		if(lpWidget->type() == cWidget::TYPE_scene)
		{
			cSceneWindow*	lpSceneWindow	= (cSceneWindow*)lpWidget->widget();
			if(lpSceneWindow->scene() == lpScene)
			{
				ui->m_lpMainTab->setCurrentIndex(x);
				ui->m_lpMdiArea->setActiveSubWindow(lpWidget->window());
				m_bUpdatingTab	= false;
				return;
			}
		}
	}

	cSceneWindow*		lpSceneWindow		= new cSceneWindow(this);
	lpSceneWindow->setScene(lpScene);
	cWidget*			lpWidget1			= new cWidget(lpSceneWindow);
	lpWidget1->setWindow(ui->m_lpMdiArea->addSubWindow(lpSceneWindow));
	ui->m_lpMainTab->addTab((QWidget*)lpWidget1, lpSceneWindow->windowTitle());

	lpSceneWindow->show();
}
