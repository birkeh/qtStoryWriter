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
	m_bUpdatingTab(false)
{
	ui->setupUi(this);

	cStructureWindow*	lpStructureWindow	= new cStructureWindow(this);
	cWidget*	lpWidget1	= new cWidget(lpStructureWindow);
	lpWidget1->setWindow(ui->m_lpMdiArea->addSubWindow(lpStructureWindow));

	QMainWindow*		lpMainWindow		= new QMainWindow(this);
	lpMainWindow->setWindowTitle("Bla");
	cWidget*	lpWidget2	= new cWidget(lpMainWindow);
	lpWidget2->setWindow(ui->m_lpMdiArea->addSubWindow(lpMainWindow));

	ui->m_lpMainTab->addTab((QWidget*)lpWidget1, "Structure");
	ui->m_lpMainTab->addTab((QWidget*)lpWidget2, "Bla");

//	g_lpInputDocument		= new cTextDocument(ui->m_lpInput);
//	g_lpOutputDocument		= new cTextDocument(ui->m_lpOutput);

//	ui->m_lpInput->setDocument(g_lpInputDocument);
}

cMainWindow::~cMainWindow()
{
	delete ui;
}

//void cMainWindow::on_actionSave_triggered()
//{
//#ifdef __linux__
//	#ifdef WITH_ZIP
//		g_lpInputDocument->saveAs("/tmp/qtStoryWriter/documentText.zip", false);
//		cDocumentReader	reader("/tmp/qtStoryWriter/documentText.zip", false);
//	#else
//		g_lpInputDocument->saveAs("/tmp/qtStoryWriter/documentText.xml", false);
//		cDocumentReader	reader("/tmp/qtStoryWriter/documentText.xml", false);
//	#endif
//#elif _WIN32
//	#ifdef WITH_ZIP
//		g_lpInputDocument->saveAs("C:/Temp/qtStoryWriter/documentText.zip", false);
//		cDocumentReader	reader("C:/Temp/qtStoryWriter/documentText.zip", false);
//	#else
//		g_lpInputDocument->saveAs("C:/Temp/qtStoryWriter/documentText.xml", false);
//		cDocumentReader	reader("C:/Temp/qtStoryWriter/documentText.xml", false);
//	#endif
//	g_lpOutputDocument	= reader.readDocument();
//	ui->m_lpOutput->setDocument(g_lpOutputDocument);
//#endif
//}

void cMainWindow::on_m_lpMainTab_currentChanged(int index)
{
	if(m_bUpdatingTab)
		return;

	m_bUpdatingTab	= true;
	cWidget*		lpWidget	= (cWidget*)ui->m_lpMainTab->currentWidget();
	QMdiSubWindow*	lpWindow	= lpWidget->window();
	ui->m_lpMdiArea->setActiveSubWindow(lpWindow);
	m_bUpdatingTab	= false;
}

void cMainWindow::on_m_lpMdiArea_subWindowActivated(QMdiSubWindow *arg1)
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
