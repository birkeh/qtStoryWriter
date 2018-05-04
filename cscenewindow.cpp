/*!
 \file cscenewindow.cpp

*/

#include "cscenewindow.h"
#include "ui_cscenewindow.h"

#include "cmainwindow.h"

#include <QStandardItem>


cSceneWindow::cSceneWindow(QWidget *parent) :
	cMDISubWindow(parent),
	ui(new Ui::cSceneWindow),
	m_lpScene(0)
{
	ui->setupUi(this);

	ui->m_lpTabs->setCurrentIndex(0);

	m_lpCharacterModel	= new QStandardItemModel(0, 1);
	ui->m_lpCharacterList->setModel(m_lpCharacterModel);

	m_lpPlaceModel		= new QStandardItemModel(0, 1);
	ui->m_lpPlaceList->setModel(m_lpPlaceModel);

	m_lpObjectModel		= new QStandardItemModel(0, 1);
	ui->m_lpObjectList->setModel(m_lpObjectModel);

	ui->m_lpState->addItem(cScene::stateText(cScene::STATE_init), cScene::STATE_init);
	ui->m_lpState->setItemData(0, QBrush(cScene::stateColor(cScene::STATE_init)), Qt::TextColorRole);

	ui->m_lpState->addItem(cScene::stateText(cScene::STATE_progress), cScene::STATE_progress);
	ui->m_lpState->setItemData(1, QBrush(cScene::stateColor(cScene::STATE_progress)), Qt::BackgroundColorRole);

	ui->m_lpState->addItem(cScene::stateText(cScene::STATE_delayed), cScene::STATE_delayed);
	ui->m_lpState->setItemData(2, QBrush(cScene::stateColor(cScene::STATE_delayed)), Qt::BackgroundColorRole);

	ui->m_lpState->addItem(cScene::stateText(cScene::STATE_finished), cScene::STATE_finished);
	ui->m_lpState->setItemData(3, QBrush(cScene::stateColor(cScene::STATE_finished)), Qt::BackgroundColorRole);

	ui->m_lpState->addItem(cScene::stateText(cScene::STATE_unknown), cScene::STATE_unknown);
	ui->m_lpState->setItemData(4, QBrush(cScene::stateColor(cScene::STATE_unknown)), Qt::BackgroundColorRole);

	connect(ui->m_lpState, SIGNAL(currentIndexChanged(int)), this, SLOT(onStateCurrentIndexChanged(int)));

	connect(ui->m_lpCharacterList, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(onCharacterDoubleClicked(QModelIndex)));
	connect(ui->m_lpPlaceList, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(onPlaceDoubleClicked(QModelIndex)));
	connect(ui->m_lpObjectList, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(onObjectDoubleClicked(QModelIndex)));

	connect(ui->m_lpPart, SIGNAL(gotFocus(cLineEdit*)), (cMainWindow*)parent, SLOT(onLineEditGotFocus(cLineEdit*)));
	connect(ui->m_lpPart, SIGNAL(lostFocus(cLineEdit*)), (cMainWindow*)parent, SLOT(onLineEditLostFocus(cLineEdit*)));

	connect(ui->m_lpChapter, SIGNAL(gotFocus(cLineEdit*)), (cMainWindow*)parent, SLOT(onLineEditGotFocus(cLineEdit*)));
	connect(ui->m_lpChapter, SIGNAL(lostFocus(cLineEdit*)), (cMainWindow*)parent, SLOT(onLineEditLostFocus(cLineEdit*)));

	connect(ui->m_lpName, SIGNAL(gotFocus(cLineEdit*)), (cMainWindow*)parent, SLOT(onLineEditGotFocus(cLineEdit*)));
	connect(ui->m_lpName, SIGNAL(lostFocus(cLineEdit*)), (cMainWindow*)parent, SLOT(onLineEditLostFocus(cLineEdit*)));

	connect(ui->m_lpDescription, SIGNAL(gotFocus(cTextEdit*)), (cMainWindow*)parent, SLOT(onTextEditGotFocus(cTextEdit*)));
	connect(ui->m_lpDescription, SIGNAL(lostFocus(cTextEdit*)), (cMainWindow*)parent, SLOT(onTextEditLostFocus(cTextEdit*)));

	connect(ui->m_lpCharacterList, SIGNAL(gotFocus(cTreeView*)), (cMainWindow*)parent, SLOT(onTreeViewGotFocus(cTreeView*)));
	connect(ui->m_lpCharacterList, SIGNAL(lostFocus(cTreeView*)), (cMainWindow*)parent, SLOT(onTreeViewLostFocus(cTreeView*)));

	connect(ui->m_lpObjectList, SIGNAL(gotFocus(cTreeView*)), (cMainWindow*)parent, SLOT(onTreeViewGotFocus(cTreeView*)));
	connect(ui->m_lpObjectList, SIGNAL(lostFocus(cTreeView*)), (cMainWindow*)parent, SLOT(onTreeViewLostFocus(cTreeView*)));

	connect(ui->m_lpPlaceList, SIGNAL(gotFocus(cTreeView*)), (cMainWindow*)parent, SLOT(onTreeViewGotFocus(cTreeView*)));
	connect(ui->m_lpPlaceList, SIGNAL(lostFocus(cTreeView*)), (cMainWindow*)parent, SLOT(onTreeViewLostFocus(cTreeView*)));

	connect(ui->m_lpState, SIGNAL(gotFocus(cComboBox*)), (cMainWindow*)parent, SLOT(onComboBoxGotFocus(cComboBox*)));
	connect(ui->m_lpState, SIGNAL(lostFocus(cComboBox*)), (cMainWindow*)parent, SLOT(onComboBoxLostFocus(cComboBox*)));

	connect(ui->m_lpStartedAt, SIGNAL(gotFocus(cDateTimeEdit*)), (cMainWindow*)parent, SLOT(onDateTimeEditGotFocus(cDateTimeEdit*)));
	connect(ui->m_lpStartedAt, SIGNAL(lostFocus(cDateTimeEdit*)), (cMainWindow*)parent, SLOT(onDateTimeEditLostFocus(cDateTimeEdit*)));

	connect(ui->m_lpFinishedAt, SIGNAL(gotFocus(cDateTimeEdit*)), (cMainWindow*)parent, SLOT(onDateTimeEditGotFocus(cDateTimeEdit*)));
	connect(ui->m_lpFinishedAt, SIGNAL(lostFocus(cDateTimeEdit*)), (cMainWindow*)parent, SLOT(onDateTimeEditLostFocus(cDateTimeEdit*)));

	connect(ui->m_lpTargetDate, SIGNAL(gotFocus(cDateTimeEdit*)), (cMainWindow*)parent, SLOT(onDateTimeEditGotFocus(cDateTimeEdit*)));
	connect(ui->m_lpTargetDate, SIGNAL(lostFocus(cDateTimeEdit*)), (cMainWindow*)parent, SLOT(onDateTimeEditLostFocus(cDateTimeEdit*)));

	connect(ui->m_lpText, SIGNAL(gotFocus(cTextEdit*)), (cMainWindow*)parent, SLOT(onTextEditGotFocus(cTextEdit*)));
	connect(ui->m_lpText, SIGNAL(lostFocus(cTextEdit*)), (cMainWindow*)parent, SLOT(onTextEditLostFocus(cTextEdit*)));
}

cSceneWindow::~cSceneWindow()
{
	delete ui;
}

void cSceneWindow::setScene(cScene* lpScene)
{
	m_lpScene			= lpScene;

	ui->m_lpPart->setText(lpScene->chapter()->part()->name());
	ui->m_lpChapter->setText(lpScene->chapter()->name());
	ui->m_lpName->setText(lpScene->name());
	ui->m_lpDescription->setDocument(lpScene->description());
	ui->m_lpState->setCurrentText(lpScene->stateText());
	if(lpScene->startedAt().isValid())
		ui->m_lpStartedAt->setDateTime(lpScene->startedAt());
	else
	{
		ui->m_lpStartedLabel->setVisible(false);
		ui->m_lpStartedAt->setVisible(false);
	}
	if(lpScene->finishedAt().isValid())
		ui->m_lpFinishedAt->setDateTime(lpScene->finishedAt());
	else
	{
		ui->m_lpFinishedLabel->setVisible(false);
		ui->m_lpFinishedAt->setVisible(false);
	}
	ui->m_lpTargetDate->setDateTime(lpScene->targetDate());
	ui->m_lpText->setDocument(lpScene->text());

	QList<cCharacter*>	characterList	= lpScene->characterList();
	QList<cPlace*>		placeList		= lpScene->placeList();
	QList<cObject*>		objectList		= lpScene->objectList();

	QStringList			headerLabels;

	headerLabels	= QStringList() << tr("name") << tr("creature") << tr("gender") << tr("title");
	m_lpCharacterModel->setHorizontalHeaderLabels(headerLabels);
	for(int x = 0;x < characterList.count();x++)
	{
		cCharacter*				lpCharacter	= characterList[x];
		QList<QStandardItem*>	items;

		items.append(new QStandardItem(lpCharacter->name()));
		items.append(new QStandardItem(lpCharacter->creature()));
		items.append(new QStandardItem(lpCharacter->genderText()));
		items.append(new QStandardItem(lpCharacter->title()));

		if(lpCharacter->mainCharacter())
		{
			QFont	font	= items[0]->font();
			font.setBold(true);

			for(int y = 0;y < headerLabels.count();y++)
				items[y]->setFont(font);
		}

		for(int y = 0;y < headerLabels.count();y++)
		{
			items[y]->setData(QVariant::fromValue(lpCharacter));
			items[y]->setToolTip(lpCharacter->description()->toPlainText());
		}

		m_lpCharacterModel->appendRow(items);
	}

	ui->m_lpCharacterList->header()->setStretchLastSection(true);

	for(int i = 0;i < headerLabels.count();i++)
		ui->m_lpCharacterList->resizeColumnToContents(i);

	headerLabels	= QStringList() << tr("name") << tr("location") << tr("type");
	m_lpPlaceModel->setHorizontalHeaderLabels(headerLabels);
	for(int x = 0;x < placeList.count();x++)
	{
		cPlace*					lpPlace	= placeList[x];
		QList<QStandardItem*>	items;

		items.append(new QStandardItem(lpPlace->name()));
		items.append(new QStandardItem(lpPlace->location()));
		items.append(new QStandardItem(lpPlace->type()));

		for(int y = 0;y < headerLabels.count();y++)
		{
			items[y]->setData(QVariant::fromValue(lpPlace));
			items[y]->setToolTip(lpPlace->description()->toPlainText());
		}

		m_lpPlaceModel->appendRow(items);
	}

	ui->m_lpPlaceList->header()->setStretchLastSection(true);

	for(int i = 0;i < headerLabels.count();i++)
		ui->m_lpPlaceList->resizeColumnToContents(i);

	headerLabels	= QStringList() << tr("name") << tr("type");
	m_lpObjectModel->setHorizontalHeaderLabels(headerLabels);
	for(int x = 0;x < objectList.count();x++)
	{
		cObject*				lpObject	= objectList[x];
		QList<QStandardItem*>	items;

		items.append(new QStandardItem(lpObject->name()));
		items.append(new QStandardItem(lpObject->type()));

		for(int y = 0;y < headerLabels.count();y++)
		{
			items[y]->setData(QVariant::fromValue(lpObject));
			items[y]->setToolTip(lpObject->description()->toPlainText());
		}

		m_lpObjectModel->appendRow(items);
	}

	ui->m_lpObjectList->header()->setStretchLastSection(true);

	for(int i = 0;i < headerLabels.count();i++)
		ui->m_lpObjectList->resizeColumnToContents(i);

	setWindowTitle(tr("[scene] - ") + lpScene->name());
}

cScene* cSceneWindow::scene()
{
	return(m_lpScene);
}

void cSceneWindow::onStateCurrentIndexChanged(int /*index*/)
{
	QBrush	brush	= qvariant_cast<QBrush>(ui->m_lpState->currentData(Qt::BackgroundColorRole));
	QColor	color	= brush.color();

	ui->m_lpState->setStyleSheet(QString("background-color: rgb(%1, %2, %3);").arg(color.red()).arg(color.green()).arg(color.blue()));
}

void cSceneWindow::onCharacterDoubleClicked(const QModelIndex& index)
{
	QStandardItem*	lpItem		= m_lpCharacterModel->itemFromIndex(index);
	cCharacter*		lpCharacter	= qvariant_cast<cCharacter*>(lpItem->data());
	if(lpCharacter)
		showCharacterWindow(lpCharacter);
}

void cSceneWindow::onPlaceDoubleClicked(const QModelIndex& index)
{
	QStandardItem*	lpItem		= m_lpPlaceModel->itemFromIndex(index);
	cPlace*			lpPlace		= qvariant_cast<cPlace*>(lpItem->data());
	if(lpPlace)
		showPlaceWindow(lpPlace);
}

void cSceneWindow::onObjectDoubleClicked(const QModelIndex& index)
{
	QStandardItem*	lpItem		= m_lpObjectModel->itemFromIndex(index);
	cObject*		lpObject	= qvariant_cast<cObject*>(lpItem->data());
	if(lpObject)
		showObjectWindow(lpObject);
}
