/*!
 \file crecherchewindow.cpp

*/

#include "crecherchewindow.h"
#include "ui_crecherchewindow.h"

#include "cimagewidget.h"

#include "cmainwindow.h"

#include "ccharacterselectdialog.h"
#include "cplaceselectdialog.h"
#include "cobjectselectdialog.h"

#include "common.h"

#include <QStandardItem>
#include <QMessageBox>


cRechercheWindow::cRechercheWindow(QWidget *parent) :
	cMDISubWindow(parent),
	ui(new Ui::cRechercheWindow),
	m_lpMainWindow((cMainWindow*)parent),
	m_lpRecherche(0),
	m_lpCharacterList(0),
	m_lpPlaceList(0),
	m_lpObjectList(0)
{
	ui->setupUi(this);

	ui->m_lpTab->setCurrentIndex(0);

	connect(ui->m_lpName,					&cLineEdit::gotFocus,			(cMainWindow*)parent,	&cMainWindow::onLineEditGotFocus);
	connect(ui->m_lpName,					&cLineEdit::lostFocus,			(cMainWindow*)parent,	&cMainWindow::onLineEditLostFocus);

	connect(ui->m_lpLink,					&cLineEdit::gotFocus,			(cMainWindow*)parent,	&cMainWindow::onLineEditGotFocus);
	connect(ui->m_lpLink,					&cLineEdit::lostFocus,			(cMainWindow*)parent,	&cMainWindow::onLineEditLostFocus);

	connect(ui->m_lpDescription,			&cTextEdit::gotFocus,			(cMainWindow*)parent,	&cMainWindow::onTextEditGotFocus);
	connect(ui->m_lpDescription,			&cTextEdit::lostFocus,			(cMainWindow*)parent,	&cMainWindow::onTextEditLostFocus);

	connect(ui->m_lpCharacterList,			&cComboBox::gotFocus,			(cMainWindow*)parent,	&cMainWindow::onComboBoxGotFocus);
	connect(ui->m_lpCharacterList,			&cComboBox::lostFocus,			(cMainWindow*)parent,	&cMainWindow::onComboBoxLostFocus);

	connect(ui->m_lpPlaceList,				&cComboBox::gotFocus,			(cMainWindow*)parent,	&cMainWindow::onComboBoxGotFocus);
	connect(ui->m_lpPlaceList,				&cComboBox::lostFocus,			(cMainWindow*)parent,	&cMainWindow::onComboBoxLostFocus);

	connect(ui->m_lpObjectList,				&cComboBox::gotFocus,			(cMainWindow*)parent,	&cMainWindow::onComboBoxGotFocus);
	connect(ui->m_lpObjectList,				&cComboBox::lostFocus,			(cMainWindow*)parent,	&cMainWindow::onComboBoxLostFocus);

	connect(ui->m_lpCaracterAdd,			&QPushButton::clicked,			this,					&cRechercheWindow::onAddCharacterToList);
	connect(ui->m_lpCharacterRemove,		&QPushButton::clicked,			this,					&cRechercheWindow::onRemoveCharacterFromList);

	connect(ui->m_lpPlaceAdd,				&QPushButton::clicked,			this,					&cRechercheWindow::onAddPlaceToList);
	connect(ui->m_lpPlaceRemove,			&QPushButton::clicked,			this,					&cRechercheWindow::onRemovePlaceFromList);

	connect(ui->m_lpObjectAdd,				&QPushButton::clicked,			this,					&cRechercheWindow::onAddObjectToList);
	connect(ui->m_lpObjectRemove,			&QPushButton::clicked,			this,					&cRechercheWindow::onRemoveObjectFromList);
}

cRechercheWindow::~cRechercheWindow()
{
	delete ui;
}

void cRechercheWindow::setRecherche(cRecherche* lpRecherche, cCharacterList* lpCharacterList, cPlaceList* lpPlaceList, cObjectList* lpObjectList)
{
	m_lpRecherche		= lpRecherche;
	m_lpCharacterList	= lpCharacterList;
	m_lpPlaceList		= lpPlaceList;
	m_lpObjectList		= lpObjectList;

	ui->m_lpName->setText(lpRecherche->name());
	ui->m_lpLink->setText(lpRecherche->link());
	ui->m_lpDescription->setDocument(lpRecherche->description());

	QList<cImage*>	images	= lpRecherche->images();
	for(int x = 0;x < images.count();x++)
	{
		cImage*				lpImage				= images[x];
		QPixmap				pixmap				= lpImage->image();
		cImageWidget*		lpImageWidget		= new cImageWidget;

		lpImageWidget->setValues(lpImage->name(), lpImage->description(), pixmap);
		ui->m_lpLayout->addWidget(lpImageWidget);
	}

	fillCharacterList();
	fillPlaceList();
	fillObjectList();

	connect(ui->m_lpCharacterList,	QOverload<int>::of(&cComboBox::currentIndexChanged),	this,	&cRechercheWindow::onCharacterIndexChanged);
	connect(ui->m_lpPlaceList,		QOverload<int>::of(&cComboBox::currentIndexChanged),	this,	&cRechercheWindow::onPlaceIndexChanged);
	connect(ui->m_lpObjectList,		QOverload<int>::of(&cComboBox::currentIndexChanged),	this,	&cRechercheWindow::onObjectIndexChanged);

	setWindowTitle(tr("[recherche] - ") + lpRecherche->name());

	connect(ui->m_lpName,			&cLineEdit::textChanged,	this,	&cRechercheWindow::onNameChanged);
	connect(ui->m_lpLink,			&cLineEdit::textChanged,	this,	&cRechercheWindow::onLinkChanged);
	connect(ui->m_lpDescription,	&cTextEdit::textChanged,	this,	&cRechercheWindow::onDescriptionChanged);
}

cRecherche* cRechercheWindow::recherche()
{
	return(m_lpRecherche);
}

void cRechercheWindow::onNameChanged(const QString& szName)
{
	m_lpRecherche->setName(szName);

	QList<QStandardItem*>	items	= m_lpRecherche->item();

	if(items.count())
		items[0]->setText(szName);

	m_lpMainWindow->somethingChanged();
}

void cRechercheWindow::onLinkChanged(const QString& szName)
{
	m_lpRecherche->setLink(szName);

	QList<QStandardItem*>	items	= m_lpRecherche->item();

	if(items.count() >= 2)
		items[1]->setText(szName);

	m_lpMainWindow->somethingChanged();
}

void cRechercheWindow::onDescriptionChanged()
{
	m_lpMainWindow->somethingChanged();
}

void cRechercheWindow::onCharacterIndexChanged(int index)
{
	ui->m_lpCharacterDetails->setCurrentIndex(index);
}

void cRechercheWindow::onPlaceIndexChanged(int index)
{
	ui->m_lpPlaceDetails->setCurrentIndex(index);
}

void cRechercheWindow::onObjectIndexChanged(int index)
{
	ui->m_lpObjectDetails->setCurrentIndex(index);
}

void cRechercheWindow::onCharacterDescriptionChanged()
{
	m_lpMainWindow->somethingChanged();
}

void cRechercheWindow::onPlaceDescriptionChanged()
{
	m_lpMainWindow->somethingChanged();
}

void cRechercheWindow::onObjectDescriptionChanged()
{
	m_lpMainWindow->somethingChanged();
}

void cRechercheWindow::onAddCharacterToList()
{
	cCharacterSelectDialog*	lpDialog	= new cCharacterSelectDialog(this);
	lpDialog->setCharacterList(m_lpCharacterList, m_lpRecherche->characterList());

	if(lpDialog->exec() == QDialog::Rejected)
	{
		delete lpDialog;
		return;
	}

	cCharacter*	lpCharacterNew	= lpDialog->selected();
	delete lpDialog;

	if(!lpCharacterNew)
		return;

	m_lpRecherche->addCharacter(lpCharacterNew, new cTextDocument);

	fillCharacterList(lpCharacterNew);

	m_lpMainWindow->somethingChanged();
}

void cRechercheWindow::onRemoveCharacterFromList()
{
	cCharacterDescription*	lpCharacterDescription	= qvariant_cast<cCharacterDescription*>(ui->m_lpCharacterList->currentData());

	if(!lpCharacterDescription)
		return;

	if(QMessageBox::question(this, "Scene", QString(tr("Do you want to delete \"%1\" from list?")).arg(lpCharacterDescription->character()->name())) == QMessageBox::No)
		return;

	m_lpRecherche->removeCharacter(lpCharacterDescription);

	fillCharacterList();

	m_lpMainWindow->somethingChanged();
}

void cRechercheWindow::onAddPlaceToList()
{
	cPlaceSelectDialog*	lpDialog	= new cPlaceSelectDialog(this);
	lpDialog->setPlaceList(m_lpPlaceList, m_lpRecherche->placeList());

	if(lpDialog->exec() == QDialog::Rejected)
	{
		delete lpDialog;
		return;
	}

	cPlace*		lpPlaceNew	= lpDialog->selected();
	delete lpDialog;

	if(!lpPlaceNew)
		return;

	m_lpRecherche->addPlace(lpPlaceNew, new cTextDocument);

	fillPlaceList(lpPlaceNew);

	m_lpMainWindow->somethingChanged();
}

void cRechercheWindow::onRemovePlaceFromList()
{
	cPlaceDescription*	lpPlaceDescription	= qvariant_cast<cPlaceDescription*>(ui->m_lpPlaceList->currentData());

	if(!lpPlaceDescription)
		return;

	if(QMessageBox::question(this, "Scene", QString(tr("Do you want to delete \"%1\" from list?")).arg(lpPlaceDescription->place()->name())) == QMessageBox::No)
		return;

	m_lpRecherche->removePlace(lpPlaceDescription);

	fillPlaceList();

	m_lpMainWindow->somethingChanged();
}

void cRechercheWindow::onAddObjectToList()
{
	cObjectSelectDialog*	lpDialog	= new cObjectSelectDialog(this);
	lpDialog->setObjectList(m_lpObjectList, m_lpRecherche->objectList());

	if(lpDialog->exec() == QDialog::Rejected)
	{
		delete lpDialog;
		return;
	}

	cObject*	lpObjectNew	= lpDialog->selected();
	delete lpDialog;

	if(!lpObjectNew)
		return;

	m_lpRecherche->addObject(lpObjectNew, new cTextDocument);

	fillObjectList(lpObjectNew);

	m_lpMainWindow->somethingChanged();
}

void cRechercheWindow::onRemoveObjectFromList()
{
	cObjectDescription*	lpObjectDescription	= qvariant_cast<cObjectDescription*>(ui->m_lpObjectList->currentData());

	if(!lpObjectDescription)
		return;

	if(QMessageBox::question(this, "Scene", QString(tr("Do you want to delete \"%1\" from list?")).arg(lpObjectDescription->object()->name())) == QMessageBox::No)
		return;

	m_lpRecherche->removeObject(lpObjectDescription);

	fillObjectList();

	m_lpMainWindow->somethingChanged();
}

void cRechercheWindow::fillCharacterList(cCharacter* lpCharacterNew)
{
	QList<cCharacterDescription*>	characterList	= m_lpRecherche->characterList();

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

		connect(lpTextEdit,	&cTextEdit::textChanged,	this,			&cRechercheWindow::onCharacterDescriptionChanged);

		if(lpCharacter == lpCharacterNew)
			index	= x;
	}

	ui->m_lpCharacterList->setCurrentIndex(index);
	ui->m_lpCharacterDetails->setCurrentIndex(index);

	ui->m_lpCharacterRemove->setEnabled((ui->m_lpCharacterList->count() > 0));
	ui->m_lpCharacterShowDetails->setEnabled((ui->m_lpCharacterList->count() > 0));
}

void cRechercheWindow::fillPlaceList(cPlace* lpPlaceNew)
{
	QList<cPlaceDescription*>	placeList	= m_lpRecherche->placeList();

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

		connect(lpTextEdit,	&cTextEdit::textChanged,	this,			&cRechercheWindow::onPlaceDescriptionChanged);

		if(lpPlace == lpPlaceNew)
			index	= x;
	}

	ui->m_lpPlaceList->setCurrentIndex(index);
	ui->m_lpPlaceDetails->setCurrentIndex(index);

	ui->m_lpPlaceRemove->setEnabled((ui->m_lpPlaceList->count() > 0));
	ui->m_lpPlaceShowDetails->setEnabled((ui->m_lpPlaceList->count() > 0));
}

void cRechercheWindow::fillObjectList(cObject* lpObjectNew)
{
	QList<cObjectDescription*>	objectList	= m_lpRecherche->objectList();

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

		connect(lpTextEdit,	&cTextEdit::textChanged,	this,			&cRechercheWindow::onObjectDescriptionChanged);

		if(lpObject == lpObjectNew)
			index	= x;
	}
	ui->m_lpObjectList->setCurrentIndex(index);
	ui->m_lpObjectDetails->setCurrentIndex(index);

	ui->m_lpObjectRemove->setEnabled((ui->m_lpObjectList->count() > 0));
	ui->m_lpObjectShowDetails->setEnabled((ui->m_lpObjectList->count() > 0));
}
