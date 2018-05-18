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

	ui->m_lpTab->setCurrentIndex(0);

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


	connect(ui->m_lpCharacterShowDetails,	&QPushButton::clicked,					this,					&cSceneWindow::onCharacterShowDetails);
	connect(ui->m_lpPlaceShowDetails,		&QPushButton::clicked,					this,					&cSceneWindow::onPlaceShowDetails);
	connect(ui->m_lpObjectShowDetails,		&QPushButton::clicked,					this,					&cSceneWindow::onObjectShowDetails);

	connect(ui->m_lpPart,					&cLineEdit::gotFocus,					(cMainWindow*)parent,	&cMainWindow::onLineEditGotFocus);
	connect(ui->m_lpPart,					&cLineEdit::lostFocus,					(cMainWindow*)parent,	&cMainWindow::onLineEditLostFocus);

	connect(ui->m_lpChapter,				&cLineEdit::gotFocus,					(cMainWindow*)parent,	&cMainWindow::onLineEditGotFocus);
	connect(ui->m_lpChapter,				&cLineEdit::lostFocus,					(cMainWindow*)parent,	&cMainWindow::onLineEditLostFocus);

	connect(ui->m_lpName,					&cLineEdit::gotFocus,					(cMainWindow*)parent,	&cMainWindow::onLineEditGotFocus);
	connect(ui->m_lpName,					&cLineEdit::lostFocus,					(cMainWindow*)parent,	&cMainWindow::onLineEditLostFocus);

	connect(ui->m_lpState,					&cComboBox::gotFocus,					(cMainWindow*)parent,	&cMainWindow::onComboBoxGotFocus);
	connect(ui->m_lpState,					&cComboBox::lostFocus,					(cMainWindow*)parent,	&cMainWindow::onComboBoxLostFocus);

	connect(ui->m_lpStartedAt,				&cDateTimeEdit::gotFocus,				(cMainWindow*)parent,	&cMainWindow::onDateTimeEditGotFocus);
	connect(ui->m_lpStartedAt,				&cDateTimeEdit::lostFocus,				(cMainWindow*)parent,	&cMainWindow::onDateTimeEditLostFocus);

	connect(ui->m_lpFinishedAt,				&cDateTimeEdit::gotFocus,				(cMainWindow*)parent,	&cMainWindow::onDateTimeEditGotFocus);
	connect(ui->m_lpFinishedAt,				&cDateTimeEdit::lostFocus,				(cMainWindow*)parent,	&cMainWindow::onDateTimeEditLostFocus);

	connect(ui->m_lpTargetDate,				&cDateTimeEdit::gotFocus,				(cMainWindow*)parent,	&cMainWindow::onDateTimeEditGotFocus);
	connect(ui->m_lpTargetDate,				&cDateTimeEdit::lostFocus,				(cMainWindow*)parent,	&cMainWindow::onDateTimeEditLostFocus);

	connect(ui->m_lpText,					&cTextEdit::gotFocus,					(cMainWindow*)parent,	&cMainWindow::onTextEditGotFocus);
	connect(ui->m_lpText,					&cTextEdit::lostFocus,					(cMainWindow*)parent,	&cMainWindow::onTextEditLostFocus);

	connect(ui->m_lpCharacterList,			&cComboBox::gotFocus,					(cMainWindow*)parent,	&cMainWindow::onComboBoxGotFocus);
	connect(ui->m_lpCharacterList,			&cComboBox::lostFocus,					(cMainWindow*)parent,	&cMainWindow::onComboBoxLostFocus);

	connect(ui->m_lpPlaceList,				&cComboBox::gotFocus,					(cMainWindow*)parent,	&cMainWindow::onComboBoxGotFocus);
	connect(ui->m_lpPlaceList,				&cComboBox::lostFocus,					(cMainWindow*)parent,	&cMainWindow::onComboBoxLostFocus);

	connect(ui->m_lpObjectList,				&cComboBox::gotFocus,					(cMainWindow*)parent,	&cMainWindow::onComboBoxGotFocus);
	connect(ui->m_lpObjectList,				&cComboBox::lostFocus,					(cMainWindow*)parent,	&cMainWindow::onComboBoxLostFocus);

	connect(ui->m_lpCaracterAdd,			&QPushButton::clicked,					this,					&cSceneWindow::onAddCharacterToList);
	connect(ui->m_lpCharacterRemove,		&QPushButton::clicked,					this,					&cSceneWindow::onRemoveCharacterFromList);

	connect(ui->m_lpPlaceAdd,				&QPushButton::clicked,					this,					&cSceneWindow::onAddPlaceToList);
	connect(ui->m_lpPlaceRemove,			&QPushButton::clicked,					this,					&cSceneWindow::onRemovePlaceFromList);

	connect(ui->m_lpObjectAdd,				&QPushButton::clicked,					this,					&cSceneWindow::onAddObjectToList);
	connect(ui->m_lpObjectRemove,			&QPushButton::clicked,					this,					&cSceneWindow::onRemoveObjectFromList);
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

	for(int x = 0;x < characterList.count();x++)
	{
		cCharacterDescription*	lpCharacterDescription	= characterList[x];
		cCharacter*				lpCharacter				= lpCharacterDescription->character();

		ui->m_lpCharacterList->addItem(lpCharacter->name(), QVariant::fromValue(lpCharacterDescription));
		cTextEdit*				lpTextEdit				= new cTextEdit(ui->m_lpCharacterDetails);
		lpTextEdit->setDocument(lpCharacterDescription->description());
		ui->m_lpCharacterDetails->addWidget(lpTextEdit);

		connect(lpTextEdit,	&cTextEdit::gotFocus,		m_lpMainWindow,	&cMainWindow::onTextEditGotFocus);
		connect(lpTextEdit,	&cTextEdit::lostFocus,		m_lpMainWindow,	&cMainWindow::onTextEditLostFocus);

		connect(lpTextEdit,	&cTextEdit::textChanged,	this,			&cSceneWindow::onCharacterDescriptionChanged);
	}
	ui->m_lpCharacterList->setCurrentText(0);
	ui->m_lpCharacterDetails->setCurrentIndex(0);

	for(int x = 0;x < placeList.count();x++)
	{
		cPlaceDescription*	lpPlaceDescription	= placeList[x];
		cPlace*				lpPlace				= lpPlaceDescription->place();

		ui->m_lpPlaceList->addItem(lpPlace->name(), QVariant::fromValue(lpPlaceDescription));
		cTextEdit*				lpTextEdit				= new cTextEdit(ui->m_lpPlaceDetails);
		lpTextEdit->setDocument(lpPlaceDescription->description());
		ui->m_lpPlaceDetails->addWidget(lpTextEdit);

		connect(lpTextEdit,	&cTextEdit::gotFocus,		m_lpMainWindow,	&cMainWindow::onTextEditGotFocus);
		connect(lpTextEdit,	&cTextEdit::lostFocus,		m_lpMainWindow,	&cMainWindow::onTextEditLostFocus);

		connect(lpTextEdit,	&cTextEdit::textChanged,	this,			&cSceneWindow::onPlaceDescriptionChanged);
	}
	ui->m_lpPlaceList->setCurrentText(0);
	ui->m_lpPlaceDetails->setCurrentIndex(0);

	for(int x = 0;x < objectList.count();x++)
	{
		cObjectDescription*	lpObjectDescription	= objectList[x];
		cObject*			lpObject			= lpObjectDescription->object();

		ui->m_lpObjectList->addItem(lpObject->name(), QVariant::fromValue(lpObjectDescription));
		cTextEdit*				lpTextEdit				= new cTextEdit(ui->m_lpObjectDetails);
		lpTextEdit->setDocument(lpObjectDescription->description());
		ui->m_lpObjectDetails->addWidget(lpTextEdit);

		connect(lpTextEdit,	&cTextEdit::gotFocus,		m_lpMainWindow,	&cMainWindow::onTextEditGotFocus);
		connect(lpTextEdit,	&cTextEdit::lostFocus,		m_lpMainWindow,	&cMainWindow::onTextEditLostFocus);

		connect(lpTextEdit,	&cTextEdit::textChanged,	this,			&cSceneWindow::onObjectDescriptionChanged);
	}
	ui->m_lpObjectList->setCurrentText(0);
	ui->m_lpObjectDetails->setCurrentIndex(0);

	connect(ui->m_lpCharacterList,		QOverload<int>::of(&cComboBox::currentIndexChanged),	this,	&cSceneWindow::onCharacterIndexChanged);
	connect(ui->m_lpPlaceList,			QOverload<int>::of(&cComboBox::currentIndexChanged),	this,	&cSceneWindow::onPlaceIndexChanged);
	connect(ui->m_lpObjectList,			QOverload<int>::of(&cComboBox::currentIndexChanged),	this,	&cSceneWindow::onObjectIndexChanged);

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

void cSceneWindow::onCharacterShowDetails()
{
	if(!ui->m_lpCharacterList->count())
		return;

	cCharacterDescription*	lpCharacter	= qvariant_cast<cCharacterDescription*>(ui->m_lpCharacterList->currentData());
	if(lpCharacter)
		showCharacterWindow(lpCharacter->character());
}

void cSceneWindow::onPlaceShowDetails()
{
	if(!ui->m_lpPlaceList->count())
		return;

	cPlaceDescription*	lpPlace	= qvariant_cast<cPlaceDescription*>(ui->m_lpPlaceList->currentData());
	if(lpPlace)
		showPlaceWindow(lpPlace->place());
}

void cSceneWindow::onObjectShowDetails()
{
	if(!ui->m_lpObjectList->count())
		return;

	cObjectDescription*	lpObject	= qvariant_cast<cObjectDescription*>(ui->m_lpObjectList->currentData());
	if(lpObject)
		showObjectWindow(lpObject->object());
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

void cSceneWindow::onCharacterDescriptionChanged()
{
	m_lpMainWindow->somethingChanged();
}

void cSceneWindow::onPlaceDescriptionChanged()
{
	m_lpMainWindow->somethingChanged();
}

void cSceneWindow::onObjectDescriptionChanged()
{
	m_lpMainWindow->somethingChanged();
}

void cSceneWindow::onCharacterIndexChanged(int index)
{
	ui->m_lpCharacterDetails->setCurrentIndex(index);
}

void cSceneWindow::onPlaceIndexChanged(int index)
{
	ui->m_lpPlaceDetails->setCurrentIndex(index);
}

void cSceneWindow::onObjectIndexChanged(int index)
{
	ui->m_lpObjectDetails->setCurrentIndex(index);
}

void cSceneWindow::onAddCharacterToList()
{
}

void cSceneWindow::onRemoveCharacterFromList()
{
}

void cSceneWindow::onAddPlaceToList()
{
}

void cSceneWindow::onRemovePlaceFromList()
{
}

void cSceneWindow::onAddObjectToList()
{
}

void cSceneWindow::onRemoveObjectFromList()
{
}
