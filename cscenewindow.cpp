/*!
 \file cscenewindow.cpp

*/

#include "cscenewindow.h"
#include "ui_cscenewindow.h"

#include "cmainwindow.h"

#include "common.h"

#include <QStandardItem>
#include <QMenu>


cSceneWindow::cSceneWindow(QWidget *parent) :
	cMDISubWindow(parent),
	ui(new Ui::cSceneWindow),
	m_lpMainWindow((cMainWindow*)parent),
	m_lpScene(0),
	m_lpCharacterList(0),
	m_lpPlaceList(0),
	m_lpObjectList(0)
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


	connect(ui->m_lpCharacterList,	&cTreeView::doubleClicked,				this,					&cSceneWindow::onCharacterDoubleClicked);
	connect(ui->m_lpPlaceList,		&cTreeView::doubleClicked,				this,					&cSceneWindow::onPlaceDoubleClicked);
	connect(ui->m_lpObjectList,		&cTreeView::doubleClicked,				this,					&cSceneWindow::onObjectDoubleClicked);

	connect(ui->m_lpPart,			&cLineEdit::gotFocus,					(cMainWindow*)parent,	&cMainWindow::onLineEditGotFocus);
	connect(ui->m_lpPart,			&cLineEdit::lostFocus,					(cMainWindow*)parent,	&cMainWindow::onLineEditLostFocus);

	connect(ui->m_lpChapter,		&cLineEdit::gotFocus,					(cMainWindow*)parent,	&cMainWindow::onLineEditGotFocus);
	connect(ui->m_lpChapter,		&cLineEdit::lostFocus,					(cMainWindow*)parent,	&cMainWindow::onLineEditLostFocus);

	connect(ui->m_lpName,			&cLineEdit::gotFocus,					(cMainWindow*)parent,	&cMainWindow::onLineEditGotFocus);
	connect(ui->m_lpName,			&cLineEdit::lostFocus,					(cMainWindow*)parent,	&cMainWindow::onLineEditLostFocus);

	connect(ui->m_lpDescription,	&cTextEdit::gotFocus,					(cMainWindow*)parent,	&cMainWindow::onTextEditGotFocus);
	connect(ui->m_lpDescription,	&cTextEdit::lostFocus,					(cMainWindow*)parent,	&cMainWindow::onTextEditLostFocus);

	connect(ui->m_lpCharacterList,	&cTreeView::gotFocus,					(cMainWindow*)parent,	&cMainWindow::onTreeViewGotFocus);
	connect(ui->m_lpCharacterList,	&cTreeView::lostFocus,					(cMainWindow*)parent,	&cMainWindow::onTreeViewLostFocus);

	connect(ui->m_lpObjectList,		&cTreeView::gotFocus,					(cMainWindow*)parent,	&cMainWindow::onTreeViewGotFocus);
	connect(ui->m_lpObjectList,		&cTreeView::lostFocus,					(cMainWindow*)parent,	&cMainWindow::onTreeViewLostFocus);

	connect(ui->m_lpPlaceList,		&cTreeView::gotFocus,					(cMainWindow*)parent,	&cMainWindow::onTreeViewGotFocus);
	connect(ui->m_lpPlaceList,		&cTreeView::lostFocus,					(cMainWindow*)parent,	&cMainWindow::onTreeViewLostFocus);

	connect(ui->m_lpState,			&cComboBox::gotFocus,					(cMainWindow*)parent,	&cMainWindow::onComboBoxGotFocus);
	connect(ui->m_lpState,			&cComboBox::lostFocus,					(cMainWindow*)parent,	&cMainWindow::onComboBoxLostFocus);

	connect(ui->m_lpStartedAt,		&cDateTimeEdit::gotFocus,				(cMainWindow*)parent,	&cMainWindow::onDateTimeEditGotFocus);
	connect(ui->m_lpStartedAt,		&cDateTimeEdit::lostFocus,				(cMainWindow*)parent,	&cMainWindow::onDateTimeEditLostFocus);

	connect(ui->m_lpFinishedAt,		&cDateTimeEdit::gotFocus,				(cMainWindow*)parent,	&cMainWindow::onDateTimeEditGotFocus);
	connect(ui->m_lpFinishedAt,		&cDateTimeEdit::lostFocus,				(cMainWindow*)parent,	&cMainWindow::onDateTimeEditLostFocus);

	connect(ui->m_lpTargetDate,		&cDateTimeEdit::gotFocus,				(cMainWindow*)parent,	&cMainWindow::onDateTimeEditGotFocus);
	connect(ui->m_lpTargetDate,		&cDateTimeEdit::lostFocus,				(cMainWindow*)parent,	&cMainWindow::onDateTimeEditLostFocus);

	connect(ui->m_lpText,			&cTextEdit::gotFocus,					(cMainWindow*)parent,	&cMainWindow::onTextEditGotFocus);
	connect(ui->m_lpText,			&cTextEdit::lostFocus,					(cMainWindow*)parent,	&cMainWindow::onTextEditLostFocus);

	connect(ui->m_lpCharacterList,	&cTreeView::customContextMenuRequested,	this,					&cSceneWindow::onCharacterContextMenu);
	connect(ui->m_lpPlaceList,		&cTreeView::customContextMenuRequested,	this,					&cSceneWindow::onPlaceContextMenu);
	connect(ui->m_lpObjectList,		&cTreeView::customContextMenuRequested,	this,					&cSceneWindow::onObjectContextMenu);
}

cSceneWindow::~cSceneWindow()
{
	delete ui;
}

void cSceneWindow::setScene(cScene* lpScene, cCharacterList* lpCharacterList, cPlaceList* lpPlaceList, cObjectList* lpObjectList)
{
	m_lpScene			= lpScene;
	m_lpCharacterList	= lpCharacterList;
	m_lpPlaceList		= lpPlaceList;
	m_lpObjectList		= lpObjectList;

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

	QList<cCharacterDescription*>	characterList	= lpScene->characterList();
	QList<cPlaceDescription*>		placeList		= lpScene->placeList();
	QList<cObjectDescription*>		objectList		= lpScene->objectList();

	QStringList			headerLabels;

	headerLabels	= QStringList() << tr("name") << tr("creature") << tr("gender") << tr("title");
	m_lpCharacterModel->setHorizontalHeaderLabels(headerLabels);
	for(int x = 0;x < characterList.count();x++)
	{
		cCharacterDescription*	lpCharacterDescription	= characterList[x];
		cCharacter*				lpCharacter				= lpCharacterDescription->character();
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
			items[y]->setData(QVariant::fromValue(lpCharacterDescription));
			items[y]->setToolTip(lpCharacterDescription->description()->toPlainText());
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
		cPlaceDescription*		lpPlaceDescription	= placeList[x];
		cPlace*					lpPlace				= lpPlaceDescription->place();
		QList<QStandardItem*>	items;

		items.append(new QStandardItem(lpPlace->name()));
		items.append(new QStandardItem(lpPlace->location()));
		items.append(new QStandardItem(lpPlace->type()));

		for(int y = 0;y < headerLabels.count();y++)
		{
			items[y]->setData(QVariant::fromValue(lpPlaceDescription));
			items[y]->setToolTip(lpPlaceDescription->description()->toPlainText());
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
		cObjectDescription*		lpObjectDescription	= objectList[x];
		cObject*				lpObject			= lpObjectDescription->object();
		QList<QStandardItem*>	items;

		items.append(new QStandardItem(lpObject->name()));
		items.append(new QStandardItem(lpObject->type()));

		for(int y = 0;y < headerLabels.count();y++)
		{
			items[y]->setData(QVariant::fromValue(lpObjectDescription));
			items[y]->setToolTip(lpObjectDescription->description()->toPlainText());
		}

		m_lpObjectModel->appendRow(items);
	}

	ui->m_lpObjectList->header()->setStretchLastSection(true);

	for(int i = 0;i < headerLabels.count();i++)
		ui->m_lpObjectList->resizeColumnToContents(i);

	setWindowTitle(tr("[scene] - ") + lpScene->name());

	connect(ui->m_lpName,				&cLineEdit::textChanged,								this,	&cSceneWindow::onNameChanged);
	connect(ui->m_lpDescription,		&cTextEdit::textChanged,								this,	&cSceneWindow::onDescriptionChanged);
	connect(ui->m_lpState,				QOverload<int>::of(&cComboBox::currentIndexChanged),	this,	&cSceneWindow::onStateChanged);
	connect(ui->m_lpStartedAt,			&cDateEdit::dateTimeChanged,							this,	&cSceneWindow::onStartedChanged);
	connect(ui->m_lpFinishedAt,			&cDateEdit::dateTimeChanged,							this,	&cSceneWindow::onFinishedChanged);
	connect(ui->m_lpTargetDate,			&cDateEdit::dateTimeChanged,							this,	&cSceneWindow::onTargetDateChanged);
	connect(ui->m_lpText,				&cTextEdit::textChanged,								this,	&cSceneWindow::onTextChanged);
}

cScene* cSceneWindow::scene()
{
	return(m_lpScene);
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

void cSceneWindow::onNameChanged(const QString& szName)
{
	m_lpScene->setName(szName);

	if(m_lpScene->item())
		m_lpScene->item()->setText(szName);

	m_lpMainWindow->somethingChanged();
}

void cSceneWindow::onDescriptionChanged()
{
	m_lpMainWindow->somethingChanged();
}

void cSceneWindow::onStateChanged(int index)
{
	QBrush	brush	= qvariant_cast<QBrush>(ui->m_lpState->currentData(Qt::BackgroundColorRole));
	QColor	color	= brush.color();

	ui->m_lpState->setStyleSheet(QString("background-color: rgb(%1, %2, %3);").arg(color.red()).arg(color.green()).arg(color.blue()));

	switch(index)
	{
	case 0:
		m_lpScene->setState(cScene::STATE_init);
		break;
	case 1:
		m_lpScene->setState(cScene::STATE_progress);
		break;
	case 2:
		m_lpScene->setState(cScene::STATE_delayed);
		break;
	case 3:
		m_lpScene->setState(cScene::STATE_finished);
		break;
	default:
		m_lpScene->setState(cScene::STATE_unknown);
		break;
	}
	m_lpScene->stateItem()->setBackground(QBrush(m_lpScene->stateColor()));
	m_lpScene->stateItem()->setText(m_lpScene->stateText());

	m_lpMainWindow->somethingChanged();
}

void cSceneWindow::onStartedChanged(const QDateTime& dateTime)
{
	m_lpScene->setStartedAt(dateTime);
	m_lpMainWindow->somethingChanged();
}

void cSceneWindow::onFinishedChanged(const QDateTime& dateTime)
{
	m_lpScene->setFinishedAt(dateTime);
	m_lpMainWindow->somethingChanged();
}

void cSceneWindow::onTargetDateChanged(const QDateTime& dateTime)
{
	m_lpScene->setTargetDate(dateTime);
	m_lpMainWindow->somethingChanged();
}

void cSceneWindow::onTextChanged()
{
	m_lpMainWindow->somethingChanged();
}

void cSceneWindow::onCharacterContextMenu(const QPoint& pos)
{
	QMenu			menu(this);

	QStandardItem*	lpItem	= m_lpCharacterModel->itemFromIndex(ui->m_lpCharacterList->currentIndex());

	if(!lpItem)
	{
		menu.addAction(tr("add character to list"), this, SLOT(onAddCharacterToList()));
	}
	else
	{
		cCharacterDescription*	lpCharacterDescription	= qvariant_cast<cCharacterDescription*>(lpItem->data());

		if(lpCharacterDescription)
		{
			menu.addAction(tr("add character to list"), this, SLOT(onAddCharacterToList()));
			menu.addAction(tr("edit character description"), this, SLOT(onEditCharacterDescription()));
			menu.addAction(tr("remove character from list"), this, SLOT(onRemoveCharacterFromList()));
		}
		else
			menu.addAction(tr("add character to list"), this, SLOT(onAddCharacterToList()));
	}

	menu.exec(ui->m_lpCharacterList->mapToGlobal(pos));
}

void cSceneWindow::onPlaceContextMenu(const QPoint& pos)
{
	QMenu			menu(this);

	QStandardItem*	lpItem	= m_lpPlaceModel->itemFromIndex(ui->m_lpPlaceList->currentIndex());

	if(!lpItem)
	{
		menu.addAction(tr("add place to list"), this, SLOT(onAddPlaceToList()));
	}
	else
	{
		cPlaceDescription*	lpPlaceDescription	= qvariant_cast<cPlaceDescription*>(lpItem->data());

		if(lpPlaceDescription)
		{
			menu.addAction(tr("add place to list"), this, SLOT(onAddPlaceToList()));
			menu.addAction(tr("edit place description"), this, SLOT(onEditPlaceDescription()));
			menu.addAction(tr("remove place from list"), this, SLOT(onRemovePlaceFromList()));
		}
		else
			menu.addAction(tr("add place to list"), this, SLOT(onAddPlaceToList()));
	}

	menu.exec(ui->m_lpPlaceList->mapToGlobal(pos));
}

void cSceneWindow::onObjectContextMenu(const QPoint& pos)
{
	QMenu			menu(this);

	QStandardItem*	lpItem	= m_lpObjectModel->itemFromIndex(ui->m_lpObjectList->currentIndex());

	if(!lpItem)
	{
		menu.addAction(tr("add object to list"), this, SLOT(onAddObjectToList()));
	}
	else
	{
		cObjectDescription*	lpObjectDescription	= qvariant_cast<cObjectDescription*>(lpItem->data());

		if(lpObjectDescription)
		{
			menu.addAction(tr("add object to list"), this, SLOT(onAddObjectToList()));
			menu.addAction(tr("edit object description"), this, SLOT(onEditObjectDescription()));
			menu.addAction(tr("remove object from list"), this, SLOT(onRemoveObjectFromList()));
		}
		else
			menu.addAction(tr("add object to list"), this, SLOT(onAddObjectToList()));
	}

	menu.exec(ui->m_lpObjectList->mapToGlobal(pos));
}

void cSceneWindow::onAddCharacterToList()
{
}

void cSceneWindow::onRemoveCharacterFromList()
{
}

void cSceneWindow::onEditCharacterDescription()
{
}

void cSceneWindow::onAddPlaceToList()
{
}

void cSceneWindow::onRemovePlaceFromList()
{
}

void cSceneWindow::onEditPlaceDescription()
{
}

void cSceneWindow::onAddObjectToList()
{
}

void cSceneWindow::onRemoveObjectFromList()
{
}

void cSceneWindow::onEditObjectDescription()
{
}
