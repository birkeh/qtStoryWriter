/*!
 \file cpartwindow.cpp

*/

#include "cpartwindow.h"
#include "ui_cpartwindow.h"

#include "cmainwindow.h"

#include <QStandardItem>


cPartWindow::cPartWindow(QWidget *parent) :
	cMDISubWindow(parent),
	ui(new Ui::cPartWindow),
	m_lpPart(0),
	m_lpChapterList(0)
{
	ui->setupUi(this);

	m_lpChapterModel	= new QStandardItemModel(0, 1);
	ui->m_lpChapterList->setModel(m_lpChapterModel);

	connect(ui->m_lpDescription, SIGNAL(gotFocus(cTextEdit*)), (cMainWindow*)parent, SLOT(onTextEditGotFocus(cTextEdit*)));
	connect(ui->m_lpDescription, SIGNAL(lostFocus(cTextEdit*)), (cMainWindow*)parent, SLOT(onTextEditLostFocus(cTextEdit*)));

	connect(ui->m_lpText, SIGNAL(gotFocus(cTextEdit*)), (cMainWindow*)parent, SLOT(onTextEditGotFocus(cTextEdit*)));
	connect(ui->m_lpText, SIGNAL(lostFocus(cTextEdit*)), (cMainWindow*)parent, SLOT(onTextEditLostFocus(cTextEdit*)));

	connect(ui->m_lpName, SIGNAL(gotFocus(cLineEdit*)), (cMainWindow*)parent, SLOT(onLineEditGotFocus(cLineEdit*)));
	connect(ui->m_lpName, SIGNAL(lostFocus(cLineEdit*)), (cMainWindow*)parent, SLOT(onLineEditLostFocus(cLineEdit*)));

	connect(ui->m_lpChapterList, SIGNAL(gotFocus(cTreeView*)), (cMainWindow*)parent, SLOT(onTreeViewGotFocus(cTreeView*)));
	connect(ui->m_lpChapterList, SIGNAL(lostFocus(cTreeView*)), (cMainWindow*)parent, SLOT(onTreeViewLostFocus(cTreeView*)));
}

cPartWindow::~cPartWindow()
{
	delete ui;
}

void cPartWindow::setPart(cPart* lpPart, cChapterList* lpChapterList)
{
	m_lpPart			= lpPart;
	m_lpChapterList		= lpChapterList;

	ui->m_lpName->setText(lpPart->name());
	ui->m_lpDescription->setDocument(lpPart->description());
	ui->m_lpText->setDocument(lpPart->text());

	QStringList			headerLabels	= QStringList() << tr("name");
	m_lpChapterModel->setHorizontalHeaderLabels(headerLabels);

	QList<cChapter*>	chapterList		= m_lpChapterList->find(lpPart);
	for(int x = 0;x < chapterList.count();x++)
	{
		cChapter*		lpChapter	= chapterList.at(x);

		QStandardItem*	lpItem		= new QStandardItem(lpChapter->name());
		lpItem->setData(QVariant::fromValue(lpChapter));
		lpItem->setToolTip(lpChapter->description()->toPlainText());
		m_lpChapterModel->appendRow(lpItem);
	}

	ui->m_lpChapterList->resizeColumnToContents(0);

	setWindowTitle(tr("[part] - ") + lpPart->name());
}

cPart* cPartWindow::part()
{
	return(m_lpPart);
}
