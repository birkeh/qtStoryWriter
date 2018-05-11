/*!
 \file cpartwindow.cpp

*/

#include "cpartwindow.h"
#include "ui_cpartwindow.h"

#include "cmainwindow.h"

#include "common.h"

#include <QStandardItem>


cPartWindow::cPartWindow(QWidget *parent) :
	cMDISubWindow(parent),
	ui(new Ui::cPartWindow),
	m_lpMainWindow((cMainWindow*)parent),
	m_lpPart(0),
	m_lpChapterList(0)
{
	ui->setupUi(this);

	m_lpChapterModel	= new QStandardItemModel(0, 1);
	ui->m_lpChapterList->setModel(m_lpChapterModel);

	connect(ui->m_lpChapterList,	&cTreeView::doubleClicked,	this,			&cPartWindow::onChapterDoubleClicked);

	connect(ui->m_lpName,			&cLineEdit::gotFocus,		m_lpMainWindow,	&cMainWindow::onLineEditGotFocus);
	connect(ui->m_lpName,			&cLineEdit::lostFocus,		m_lpMainWindow,	&cMainWindow::onLineEditLostFocus);

	connect(ui->m_lpChapterList,	&cTreeView::gotFocus,		m_lpMainWindow,	&cMainWindow::onTreeViewGotFocus);
	connect(ui->m_lpChapterList,	&cTreeView::lostFocus,		m_lpMainWindow,	&cMainWindow::onTreeViewLostFocus);

	connect(ui->m_lpDescription,	&cTextEdit::gotFocus,		m_lpMainWindow,	&cMainWindow::onTextEditGotFocus);
	connect(ui->m_lpDescription,	&cTextEdit::lostFocus,		m_lpMainWindow,	&cMainWindow::onTextEditLostFocus);

	connect(ui->m_lpText,			&cTextEdit::gotFocus,		m_lpMainWindow,	&cMainWindow::onTextEditGotFocus);
	connect(ui->m_lpText,			&cTextEdit::lostFocus,		m_lpMainWindow,	&cMainWindow::onTextEditLostFocus);
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

	connect(ui->m_lpName,			&cLineEdit::textChanged,	this,	&cPartWindow::onNameChanged);
	connect(ui->m_lpDescription,	&cTextEdit::textChanged,	this,	&cPartWindow::onDescriptionChanged);
	connect(ui->m_lpText,			&cTextEdit::textChanged,	this,	&cPartWindow::onTextChanged);
}

cPart* cPartWindow::part()
{
	return(m_lpPart);
}

void cPartWindow::onChapterDoubleClicked(const QModelIndex& index)
{
	QStandardItem*	lpItem		= m_lpChapterModel->itemFromIndex(index);
	cChapter*		lpChapter	= qvariant_cast<cChapter*>(lpItem->data());
	if(lpChapter)
		showChapterWindow(lpChapter);
}

void cPartWindow::onNameChanged(const QString& szName)
{
	m_lpPart->setName(szName);

	if(m_lpPart->item())
		m_lpPart->item()->setText(szName);

	m_lpMainWindow->somethingChanged();
}

void cPartWindow::onDescriptionChanged()
{
	m_lpMainWindow->somethingChanged();
}

void cPartWindow::onTextChanged()
{
	m_lpMainWindow->somethingChanged();
}
