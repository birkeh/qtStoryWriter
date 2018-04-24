#include "cchapterwindow.h"
#include "ui_cchapterwindow.h"

#include <QStandardItem>


cChapterWindow::cChapterWindow(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::cChapterWindow),
	m_lpChapter(0),
	m_lpSceneList(0)
{
	ui->setupUi(this);

	m_lpSceneModel	= new QStandardItemModel(0, 1);
	ui->m_lpSceneList->setModel(m_lpSceneModel);
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
		lpItem->setToolTip(lpScene->description()->toPlainText());
		m_lpSceneModel->appendRow(lpItem);
	}

	ui->m_lpSceneList->resizeColumnToContents(0);

	setWindowTitle(tr("[chapter] - ") + lpChapter->name());
}

cChapter* cChapterWindow::chapter()
{
	return(m_lpChapter);
}
