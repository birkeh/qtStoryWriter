#include "cpartwindow.h"
#include "ui_cpartwindow.h"

#include <QStandardItem>


cPartWindow::cPartWindow(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::cPartWindow),
	m_lpPart(0),
	m_lpChapterList(0)
{
	ui->setupUi(this);

	m_lpChapterModel	= new QStandardItemModel(0, 1);
	ui->m_lpChapterList->setModel(m_lpChapterModel);
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
