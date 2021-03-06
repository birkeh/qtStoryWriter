/*!
 \file cscenewindow.cpp

*/

#include "cscenewindow.h"
#include "ui_cscenewindow.h"

#include "ccharacterselectdialog.h"
#include "cplaceselectdialog.h"
#include "cobjectselectdialog.h"

#include "cmainwindow.h"

#include "common.h"

#include <QStandardItem>
#include <QMenu>
#include <QMessageBox>


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
	ui->m_lpState->setItemData(0, QBrush(cScene::stateColor(cScene::STATE_init)), TEXT_COLOR_ROLE);

	ui->m_lpState->addItem(cScene::stateText(cScene::STATE_progress), cScene::STATE_progress);
	ui->m_lpState->setItemData(1, QBrush(cScene::stateColor(cScene::STATE_progress)), BACKGROUND_COLOR_ROLE);

	ui->m_lpState->addItem(cScene::stateText(cScene::STATE_delayed), cScene::STATE_delayed);
	ui->m_lpState->setItemData(2, QBrush(cScene::stateColor(cScene::STATE_delayed)), BACKGROUND_COLOR_ROLE);

	ui->m_lpState->addItem(cScene::stateText(cScene::STATE_finished), cScene::STATE_finished);
	ui->m_lpState->setItemData(3, QBrush(cScene::stateColor(cScene::STATE_finished)), BACKGROUND_COLOR_ROLE);

	ui->m_lpState->addItem(cScene::stateText(cScene::STATE_unknown), cScene::STATE_unknown);
	ui->m_lpState->setItemData(4, QBrush(cScene::stateColor(cScene::STATE_unknown)), BACKGROUND_COLOR_ROLE);


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

	connect(ui->m_lpSceneDate,				&cDateTimeEdit::gotFocus,				(cMainWindow*)parent,	&cMainWindow::onDateTimeEditGotFocus);
	connect(ui->m_lpSceneDate,				&cDateTimeEdit::lostFocus,				(cMainWindow*)parent,	&cMainWindow::onDateTimeEditLostFocus);

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
	ui->m_lpSceneDate->setDateTime(lpScene->sceneDate());
	ui->m_lpText->setDocument(lpScene->text());

	fillCharacterList();
	fillPlaceList();
	fillObjectList();

	connect(ui->m_lpCharacterList,		QOverload<int>::of(&cComboBox::currentIndexChanged),	this,	&cSceneWindow::onCharacterIndexChanged);
	connect(ui->m_lpPlaceList,			QOverload<int>::of(&cComboBox::currentIndexChanged),	this,	&cSceneWindow::onPlaceIndexChanged);
	connect(ui->m_lpObjectList,			QOverload<int>::of(&cComboBox::currentIndexChanged),	this,	&cSceneWindow::onObjectIndexChanged);

	setWindowTitle(windowTitle() + lpScene->name());

	connect(ui->m_lpName,				&cLineEdit::textChanged,								this,	&cSceneWindow::onNameChanged);
	connect(ui->m_lpDescription,		&cTextEdit::textChanged,								this,	&cSceneWindow::onDescriptionChanged);
	connect(ui->m_lpState,				QOverload<int>::of(&cComboBox::currentIndexChanged),	this,	&cSceneWindow::onStateChanged);
	connect(ui->m_lpStartedAt,			&cDateEdit::dateTimeChanged,							this,	&cSceneWindow::onStartedChanged);
	connect(ui->m_lpFinishedAt,			&cDateEdit::dateTimeChanged,							this,	&cSceneWindow::onFinishedChanged);
	connect(ui->m_lpTargetDate,			&cDateEdit::dateTimeChanged,							this,	&cSceneWindow::onTargetDateChanged);
	connect(ui->m_lpSceneDate,			&cDateEdit::dateTimeChanged,							this,	&cSceneWindow::onSceneDateChanged);
	connect(ui->m_lpText,				&cTextEdit::textChanged,								this,	&cSceneWindow::onTextChanged);
}

cScene* cSceneWindow::scene()
{
	return(m_lpScene);
}

void cSceneWindow::retranslateUI()
{
	ui->retranslateUi(this);
	setWindowTitle(windowTitle() + m_lpScene->name());
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
	QBrush	brush	= qvariant_cast<QBrush>(ui->m_lpState->currentData(BACKGROUND_COLOR_ROLE));
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

void cSceneWindow::onSceneDateChanged(const QDateTime& dateTime)
{
	m_lpScene->setSceneDate(dateTime);
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
	cCharacterSelectDialog*	lpDialog	= new cCharacterSelectDialog(this);
	lpDialog->setCharacterList(m_lpCharacterList, m_lpScene->characterList());

	if(lpDialog->exec() == QDialog::Rejected)
	{
		delete lpDialog;
		return;
	}

	cCharacter*	lpCharacterNew	= lpDialog->selected();
	delete lpDialog;

	if(!lpCharacterNew)
		return;

	m_lpScene->addCharacter(lpCharacterNew, new cTextDocument);

	fillCharacterList(lpCharacterNew);

	m_lpMainWindow->somethingChanged();
}

void cSceneWindow::onRemoveCharacterFromList()
{
	cCharacterDescription*	lpCharacterDescription	= qvariant_cast<cCharacterDescription*>(ui->m_lpCharacterList->currentData());

	if(!lpCharacterDescription)
		return;

	if(QMessageBox::question(this, "Scene", QString(tr("Do you want to delete \"%1\" from list?")).arg(lpCharacterDescription->character()->name())) == QMessageBox::No)
		return;

	m_lpScene->removeCharacter(lpCharacterDescription);

	fillCharacterList();

	m_lpMainWindow->somethingChanged();
}

void cSceneWindow::onAddPlaceToList()
{
	cPlaceSelectDialog*	lpDialog	= new cPlaceSelectDialog(this);
	lpDialog->setPlaceList(m_lpPlaceList, m_lpScene->placeList());

	if(lpDialog->exec() == QDialog::Rejected)
	{
		delete lpDialog;
		return;
	}

	cPlace*		lpPlaceNew	= lpDialog->selected();
	delete lpDialog;

	if(!lpPlaceNew)
		return;

	m_lpScene->addPlace(lpPlaceNew, new cTextDocument);

	fillPlaceList(lpPlaceNew);

	m_lpMainWindow->somethingChanged();
}

void cSceneWindow::onRemovePlaceFromList()
{
	cPlaceDescription*	lpPlaceDescription	= qvariant_cast<cPlaceDescription*>(ui->m_lpPlaceList->currentData());

	if(!lpPlaceDescription)
		return;

	if(QMessageBox::question(this, "Scene", QString(tr("Do you want to delete \"%1\" from list?")).arg(lpPlaceDescription->place()->name())) == QMessageBox::No)
		return;

	m_lpScene->removePlace(lpPlaceDescription);

	QList<cPlaceDescription*>	placeList	= m_lpScene->placeList();

	fillPlaceList();

	m_lpMainWindow->somethingChanged();
}

void cSceneWindow::onAddObjectToList()
{
	cObjectSelectDialog*	lpDialog	= new cObjectSelectDialog(this);
	lpDialog->setObjectList(m_lpObjectList, m_lpScene->objectList());

	if(lpDialog->exec() == QDialog::Rejected)
	{
		delete lpDialog;
		return;
	}

	cObject*	lpObjectNew	= lpDialog->selected();
	delete lpDialog;

	if(!lpObjectNew)
		return;

	m_lpScene->addObject(lpObjectNew, new cTextDocument);

	fillObjectList(lpObjectNew);

	m_lpMainWindow->somethingChanged();
}

void cSceneWindow::onRemoveObjectFromList()
{
	cObjectDescription*	lpObjectDescription	= qvariant_cast<cObjectDescription*>(ui->m_lpObjectList->currentData());

	if(!lpObjectDescription)
		return;

	if(QMessageBox::question(this, "Scene", QString(tr("Do you want to delete \"%1\" from list?")).arg(lpObjectDescription->object()->name())) == QMessageBox::No)
		return;

	m_lpScene->removeObject(lpObjectDescription);

	fillObjectList();

	m_lpMainWindow->somethingChanged();
}

void cSceneWindow::fillCharacterList(cCharacter* lpCharacterNew)
{
	QList<cCharacterDescription*>	characterList	= m_lpScene->characterList();

	ui->m_lpCharacterList->clear();

	for(int x = ui->m_lpCharacterDetails->count()-1;x >= 0;x--)
		ui->m_lpCharacterDetails->removeWidget(ui->m_lpCharacterDetails->widget(x));

	qint16	index	= 0;

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

		if(lpCharacter == lpCharacterNew)
			index	= x;
	}

	ui->m_lpCharacterList->setCurrentIndex(index);
	ui->m_lpCharacterDetails->setCurrentIndex(index);

	ui->m_lpCharacterRemove->setEnabled((ui->m_lpCharacterList->count() > 0));
	ui->m_lpCharacterShowDetails->setEnabled((ui->m_lpCharacterList->count() > 0));
}

void cSceneWindow::fillPlaceList(cPlace* lpPlaceNew)
{
	QList<cPlaceDescription*>	placeList	= m_lpScene->placeList();

	ui->m_lpPlaceList->clear();

	for(int x = ui->m_lpPlaceDetails->count()-1;x >= 0;x--)
		ui->m_lpPlaceDetails->removeWidget(ui->m_lpPlaceDetails->widget(x));

	qint16	index	= 0;

	for(int x = 0;x < placeList.count();x++)
	{
		cPlaceDescription*		lpPlaceDescription		= placeList[x];
		cPlace*					lpPlace					= lpPlaceDescription->place();

		ui->m_lpPlaceList->addItem(lpPlace->name(), QVariant::fromValue(lpPlaceDescription));
		cTextEdit*				lpTextEdit				= new cTextEdit(ui->m_lpPlaceDetails);
		lpTextEdit->setDocument(lpPlaceDescription->description());
		ui->m_lpPlaceDetails->addWidget(lpTextEdit);

		connect(lpTextEdit,	&cTextEdit::gotFocus,		m_lpMainWindow,	&cMainWindow::onTextEditGotFocus);
		connect(lpTextEdit,	&cTextEdit::lostFocus,		m_lpMainWindow,	&cMainWindow::onTextEditLostFocus);

		connect(lpTextEdit,	&cTextEdit::textChanged,	this,			&cSceneWindow::onPlaceDescriptionChanged);

		if(lpPlace == lpPlaceNew)
			index	= x;
	}

	ui->m_lpPlaceList->setCurrentIndex(index);
	ui->m_lpPlaceDetails->setCurrentIndex(index);

	ui->m_lpPlaceRemove->setEnabled((ui->m_lpPlaceList->count() > 0));
	ui->m_lpPlaceShowDetails->setEnabled((ui->m_lpPlaceList->count() > 0));
}

void cSceneWindow::fillObjectList(cObject* lpObjectNew)
{
	QList<cObjectDescription*>	objectList	= m_lpScene->objectList();

	ui->m_lpObjectList->clear();

	for(int x = ui->m_lpObjectDetails->count()-1;x >= 0;x--)
		ui->m_lpObjectDetails->removeWidget(ui->m_lpObjectDetails->widget(x));

	qint16	index	= 0;

	for(int x = 0;x < objectList.count();x++)
	{
		cObjectDescription*		lpObjectDescription		= objectList[x];
		cObject*				lpObject				= lpObjectDescription->object();

		ui->m_lpObjectList->addItem(lpObject->name(), QVariant::fromValue(lpObjectDescription));
		cTextEdit*				lpTextEdit				= new cTextEdit(ui->m_lpObjectDetails);
		lpTextEdit->setDocument(lpObjectDescription->description());
		ui->m_lpObjectDetails->addWidget(lpTextEdit);

		connect(lpTextEdit,	&cTextEdit::gotFocus,		m_lpMainWindow,	&cMainWindow::onTextEditGotFocus);
		connect(lpTextEdit,	&cTextEdit::lostFocus,		m_lpMainWindow,	&cMainWindow::onTextEditLostFocus);

		connect(lpTextEdit,	&cTextEdit::textChanged,	this,			&cSceneWindow::onObjectDescriptionChanged);

		if(lpObject == lpObjectNew)
			index	= x;
	}
	ui->m_lpObjectList->setCurrentIndex(index);
	ui->m_lpObjectDetails->setCurrentIndex(index);

	ui->m_lpObjectRemove->setEnabled((ui->m_lpObjectList->count() > 0));
	ui->m_lpObjectShowDetails->setEnabled((ui->m_lpObjectList->count() > 0));
}
