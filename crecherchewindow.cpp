#include "crecherchewindow.h"
#include "ui_crecherchewindow.h"

#include "cimagewidget.h"

#include "cmainwindow.h"

#include <QStandardItem>



cRechercheWindow::cRechercheWindow(QWidget *parent) :
	cMDISubWindow(parent),
	ui(new Ui::cRechercheWindow),
	m_lpRecherche(0)
{
	ui->setupUi(this);

	ui->m_lpTab->setCurrentIndex(0);

	m_lpCharacterModel	= new QStandardItemModel(0, 1);
	ui->m_lpCharacterList->setModel(m_lpCharacterModel);

	m_lpPlaceModel		= new QStandardItemModel(0, 1);
	ui->m_lpPlaceList->setModel(m_lpPlaceModel);

	m_lpObjectModel		= new QStandardItemModel(0, 1);
	ui->m_lpObjectList->setModel(m_lpObjectModel);

	connect(ui->m_lpCharacterList, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(onCharacterDoubleClicked(QModelIndex)));
	connect(ui->m_lpPlaceList, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(onPlaceDoubleClicked(QModelIndex)));
	connect(ui->m_lpObjectList, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(onObjectDoubleClicked(QModelIndex)));

	connect(ui->m_lpName, SIGNAL(gotFocus(cLineEdit*)), (cMainWindow*)parent, SLOT(onLineEditGotFocus(cLineEdit*)));
	connect(ui->m_lpName, SIGNAL(lostFocus(cLineEdit*)), (cMainWindow*)parent, SLOT(onLineEditLostFocus(cLineEdit*)));

	connect(ui->m_lpLink, SIGNAL(gotFocus(cLineEdit*)), (cMainWindow*)parent, SLOT(onLineEditGotFocus(cLineEdit*)));
	connect(ui->m_lpLink, SIGNAL(lostFocus(cLineEdit*)), (cMainWindow*)parent, SLOT(onLineEditLostFocus(cLineEdit*)));

	connect(ui->m_lpDescription, SIGNAL(gotFocus(cTextEdit*)), (cMainWindow*)parent, SLOT(onTextEditGotFocus(cTextEdit*)));
	connect(ui->m_lpDescription, SIGNAL(lostFocus(cTextEdit*)), (cMainWindow*)parent, SLOT(onTextEditLostFocus(cTextEdit*)));

	connect(ui->m_lpCharacterList, SIGNAL(gotFocus(cTreeView*)), (cMainWindow*)parent, SLOT(onTreeViewGotFocus(cTreeView*)));
	connect(ui->m_lpCharacterList, SIGNAL(lostFocus(cTreeView*)), (cMainWindow*)parent, SLOT(onTreeViewLostFocus(cTreeView*)));

	connect(ui->m_lpObjectList, SIGNAL(gotFocus(cTreeView*)), (cMainWindow*)parent, SLOT(onTreeViewGotFocus(cTreeView*)));
	connect(ui->m_lpObjectList, SIGNAL(lostFocus(cTreeView*)), (cMainWindow*)parent, SLOT(onTreeViewLostFocus(cTreeView*)));

	connect(ui->m_lpPlaceList, SIGNAL(gotFocus(cTreeView*)), (cMainWindow*)parent, SLOT(onTreeViewGotFocus(cTreeView*)));
	connect(ui->m_lpPlaceList, SIGNAL(lostFocus(cTreeView*)), (cMainWindow*)parent, SLOT(onTreeViewLostFocus(cTreeView*)));
}

cRechercheWindow::~cRechercheWindow()
{
	delete ui;
}

void cRechercheWindow::setRecherche(cRecherche* lpRecherche)
{
	m_lpRecherche	= lpRecherche;

	ui->m_lpName->setText(lpRecherche->name());
	ui->m_lpLink->setText(lpRecherche->link());
	ui->m_lpDescription->setDocument(lpRecherche->description());

	QList<cImage*>	images	= lpRecherche->images();
	for(int x = 0;x < images.count();x++)
	{
		cImage*			lpImage			= images[x];
		QPixmap			pixmap			= lpImage->load();
		cImageWidget*	lpImageWidget	= new cImageWidget;

		lpImageWidget->setValues(lpImage->name(), lpImage->type(), lpImage->description(), pixmap);
		ui->m_lpLayout->addWidget(lpImageWidget);
	}

	QSpacerItem*	lpSpacer		= new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
	ui->m_lpLayout->addItem(lpSpacer);

	QList<cCharacter*>	characterList	= lpRecherche->characterList();
	QList<cPlace*>		placeList		= lpRecherche->placeList();
	QList<cObject*>		objectList		= lpRecherche->objectList();

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

	setWindowTitle(tr("[recherche] - ") + lpRecherche->name());
}

cRecherche* cRechercheWindow::recherche()
{
	return(m_lpRecherche);
}

void cRechercheWindow::onCharacterDoubleClicked(const QModelIndex& index)
{
	QStandardItem*	lpItem		= m_lpCharacterModel->itemFromIndex(index);
	cCharacter*		lpCharacter	= qvariant_cast<cCharacter*>(lpItem->data());
	if(lpCharacter)
		showCharacterWindow(lpCharacter);
}

void cRechercheWindow::onPlaceDoubleClicked(const QModelIndex& index)
{
	QStandardItem*	lpItem		= m_lpPlaceModel->itemFromIndex(index);
	cPlace*			lpPlace		= qvariant_cast<cPlace*>(lpItem->data());
	if(lpPlace)
		showPlaceWindow(lpPlace);
}

void cRechercheWindow::onObjectDoubleClicked(const QModelIndex& index)
{
	QStandardItem*	lpItem		= m_lpObjectModel->itemFromIndex(index);
	cObject*		lpObject	= qvariant_cast<cObject*>(lpItem->data());
	if(lpObject)
		showObjectWindow(lpObject);
}
