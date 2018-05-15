/*!
 \file cchapterwindow.cpp

*/

#include "cchapterwindow.h"
#include "ui_cchapterwindow.h"

#include "common.h"

#include <QStandardItem>


cChapterWindow::cChapterWindow(QWidget *parent) :
	cMDISubWindow(parent),
	ui(new Ui::cChapterWindow),
	m_lpMainWindow((cMainWindow*)parent),
	m_lpChapter(0),
	m_lpSceneList(0)
{
	ui->setupUi(this);

	m_lpSceneModel	= new QStandardItemModel(0, 1);
	ui->m_lpSceneList->setModel(m_lpSceneModel);

	connect(ui->m_lpSceneList,		&cTreeView::doubleClicked,	this,			&cChapterWindow::onSceneDoubleClicked);

	connect(ui->m_lpName,			&cLineEdit::gotFocus,		m_lpMainWindow,	&cMainWindow::onLineEditGotFocus);
	connect(ui->m_lpName,			&cLineEdit::lostFocus,		m_lpMainWindow,	&cMainWindow::onLineEditLostFocus);

	connect(ui->m_lpPart,			&cLineEdit::gotFocus,		m_lpMainWindow,	&cMainWindow::onLineEditGotFocus);
	connect(ui->m_lpPart,			&cLineEdit::lostFocus,		m_lpMainWindow,	&cMainWindow::onLineEditLostFocus);

	connect(ui->m_lpSceneList,		&cTreeView::gotFocus,		m_lpMainWindow,	&cMainWindow::onTreeViewGotFocus);
	connect(ui->m_lpSceneList,		&cTreeView::lostFocus,		m_lpMainWindow,	&cMainWindow::onTreeViewLostFocus);

	connect(ui->m_lpDescription,	&cTextEdit::gotFocus,		m_lpMainWindow,	&cMainWindow::onTextEditGotFocus);
	connect(ui->m_lpDescription,	&cTextEdit::lostFocus,		m_lpMainWindow,	&cMainWindow::onTextEditLostFocus);

	connect(ui->m_lpText,			&cTextEdit::gotFocus,		m_lpMainWindow,	&cMainWindow::onTextEditGotFocus);
	connect(ui->m_lpText,			&cTextEdit::lostFocus,		m_lpMainWindow,	&cMainWindow::onTextEditLostFocus);
}

cChapterWindow::~cChapterWindow()
{
	delete ui;
}

void cChapterWindow::setChapter(cChapter* lpChapter, cSceneList* lpSceneList)
{
	m_lpChapter			= lpChapter;
	m_lpSceneList		= lpSceneList;

	ui->m_lpPart->setText(lpChapter->part()->name());
	ui->m_lpName->setText(lpChapter->name());
	ui->m_lpDescription->setDocument(lpChapter->description());
	ui->m_lpText->setDocument(lpChapter->text());

	QStringList			headerLabels	= QStringList() << tr("name");
	m_lpSceneModel->setHorizontalHeaderLabels(headerLabels);

	QList<cScene*>		sceneList		= m_lpSceneList->find(lpChapter);
	for(int x = 0;x < sceneList.count();x++)
	{
		cScene*		lpScene	= sceneList.at(x);

		QStandardItem*	lpItem		= new QStandardItem(lpScene->name());
		lpItem->setData(QVariant::fromValue(lpScene));
		if(lpScene->description())
			lpItem->setToolTip(lpScene->description()->toPlainText());
		m_lpSceneModel->appendRow(lpItem);
	}

	ui->m_lpSceneList->resizeColumnToContents(0);

	setWindowTitle(tr("[chapter] - ") + lpChapter->name());

	connect(ui->m_lpName,			&cLineEdit::textChanged,	this,	&cChapterWindow::onNameChanged);
	connect(ui->m_lpDescription,	&cTextEdit::textChanged,	this,	&cChapterWindow::onDescriptionChanged);
	connect(ui->m_lpText,			&cTextEdit::textChanged,	this,	&cChapterWindow::onTextChanged);
}

cChapter* cChapterWindow::chapter()
{
	return(m_lpChapter);
}

void cChapterWindow::onSceneDoubleClicked(const QModelIndex& index)
{
	QStandardItem*	lpItem		= m_lpSceneModel->itemFromIndex(index);
	cScene*			lpScene		= qvariant_cast<cScene*>(lpItem->data());
	if(lpScene)
		showSceneWindow(lpScene);
}

void cChapterWindow::onNameChanged(const QString& szName)
{
	m_lpChapter->setName(szName);

	if(m_lpChapter->item())
		m_lpChapter->item()->setText(szName);

	m_lpMainWindow->somethingChanged();
}

void cChapterWindow::onDescriptionChanged()
{
	m_lpMainWindow->somethingChanged();
}

void cChapterWindow::onTextChanged()
{
	m_lpMainWindow->somethingChanged();
}
