/*!
 \file cstorybook.cpp

*/

#include "cstorybook.h"
#include "common.h"

#include <QVariant>

#include <QSqlQuery>
#include <QSqlError>

#include <QStandardItem>
#include <QListView>
#include <QHeaderView>

#include <QMap>

#include <QFile>
#include <QDir>

#include <QThread>


//sceneCharacter
//sceneObject
//scenePlace
//config

cStoryBook::cStoryBook(const QString &szProject, QObject *parent) :
	QObject(parent),
	m_szProject(szProject),
	m_bIsOpen(false)
{
	if(!openDatabase())
		return;

	if(!loadImageList())
		return;

	if(!loadCharacterList())
		return;

	if(!loadPlaceList())
		return;

	if(!loadObjectList())
		return;

	if(!loadBook())
		return;

	if(!loadPartList())
		return;

	if(!loadChapterList())
		return;

	if(!loadSceneList())
		return;

	if(!loadRechercheList())
		return;

	m_bIsOpen	= true;
}

cStoryBook::~cStoryBook()
{
	if(m_db.isOpen())
		m_db.close();
}

bool cStoryBook::openDatabase()
{
	QFile		file(m_szProject);

	if(!file.exists())
	{
		myDebug << QObject::tr("project does not exist");
		return(false);

	}
	m_db	= QSqlDatabase::addDatabase("QSQLITE");
	m_db.setHostName("localhost");
	m_db.setDatabaseName(m_szProject);

	if(!m_db.open())
	{
		myDebug << m_db.lastError().text();
		return(false);
	}

	if(!m_db.tables().contains("config"))
		createDatabase();
	else
	{
		QSqlQuery	query;

		query.prepare("SELECT value FROM config WHERE key = 'version';");
		if(!query.exec())
		{
			myDebug << query.lastError().text();
			m_db.close();
			return(false);
		}

		query.first();
		if(query.value("value").toDouble() < 0.1)
			updateDatabase();
	}

	return(true);
}

bool cStoryBook::createTable(const QString& szSQL)
{
	QSqlQuery	query;

	query.prepare(szSQL);

	if(!query.exec())
	{
		myDebug << szSQL << "\n" << query.lastError().text();
		return(false);
	}
	return(true);
}

bool cStoryBook::createDatabase()
{
	QSqlQuery	query;

	if(!createTable("CREATE TABLE config ( "
					"    key             STRING, "
					"    value           STRING "
					");"))
		return(false);

	query.prepare("INSERT INTO config (key, value) VALUES (:key, :value);");
	query.bindValue(":key", "version");
	query.bindValue(":value", 0.1);
	if(!query.exec())
	{
		myDebug << query.lastError().text();
		return(false);
	}

	if(!createTable("CREATE TABLE book ( "
					"    title            TEXT, "
					"    subTitle         TEXT, "
					"    shortDescription BLOB, "
					"    description      BLOB, "
					"    author           TEXT, "
					"    startedAt        DATETIME, "
					"    finishedAt       DATETIME, "
					"    targetDate       DATETIME "
					");"))
		return(false);

	if(!createTable("CREATE TABLE chapter ( "
					"	id          INTEGER PRIMARY KEY AUTOINCREMENT "
					"						UNIQUE, "
					"	partID      INTEGER REFERENCES part (id), "
					"	name        TEXT, "
					"	sortOrder   INTEGER, "
					"	description BLOB, "
					"	text        BLOB "
					");"))
		return(false);

	if(!createTable("CREATE TABLE character ( "
					"	id              INTEGER PRIMARY KEY AUTOINCREMENT "
					"							UNIQUE, "
					"	mainCharacter   BOOLEAN, "
					"	gender          INTEGER, "
					"	title           TEXT, "
					"	firstName       TEXT, "
					"	middleName      TEXT, "
					"	lastName        TEXT, "
					"   nickName        TEXT, "
					"	height          DOUBLE, "
					"	weight          DOUBLE, "
					"   age             DOUBLE, "
					"	dateOfBirth     DATE, "
					"	placeOfBirth    TEXT, "
					"	dateOfDeath     DATE, "
					"	placeOfDeath    TEXT, "
					"	hairColor       TEXT, "
					"	hairCut         TEXT, "
					"	hairLength      TEXT, "
					"	figure          TEXT, "
					"	nature          TEXT, "
					"	spokenLanguages TEXT, "
					"	skin            TEXT, "
					"	school          TEXT, "
					"	job             TEXT, "
					"	description     BLOB "
					");"))
		return(false);

	if(!createTable("CREATE TABLE image ( "
					"	id          INTEGER PRIMARY KEY AUTOINCREMENT "
					"						UNIQUE, "
					"	type        TEXT, "
					"	name        TEXT, "
					"	description BLOB, "
					"	image       BLOB "
					");"))
		return(false);

	if(!createTable("CREATE TABLE characterImage ( "
					"	characterID INTEGER REFERENCES character (id), "
					"	imageID     INTEGER REFERENCES image (id)  "
					");"))
		return(false);

	if(!createTable("CREATE TABLE object ( "
					"	id          INTEGER PRIMARY KEY AUTOINCREMENT "
					"						UNIQUE, "
					"	name        TEXT, "
					"	type        TEXT, "
					"	description BLOB "
					");"))
		return(false);

	if(!createTable("CREATE TABLE objectImage ( "
					"	objectID INTEGER REFERENCES object (id), "
					"	imageID  INTEGER REFERENCES image (id) "
					");"))
		return(false);

	if(!createTable("CREATE TABLE part ( "
					"	id          INTEGER PRIMARY KEY AUTOINCREMENT "
					"						UNIQUE, "
					"	name        TEXT, "
					"	[order]     INTEGER, "
					"	description BLOB, "
					"	text        BLOB "
					");"))
		return(false);

	if(!createTable("CREATE TABLE place ( "
					"	id          INTEGER PRIMARY KEY AUTOINCREMENT "
					"						UNIQUE, "
					"	name        TEXT, "
					"	location    TEXT, "
					"	type        TEXT, "
					"	description BLOB "
					");"))
		return(false);

	if(!createTable("CREATE TABLE placeImage ( "
					"	placeID INTEGER REFERENCES place (id), "
					"	imageID INTEGER REFERENCES image (id)  "
					");"))
		return(false);

	if(!createTable("CREATE TABLE recherche ( "
					"	id          INTEGER PRIMARY KEY AUTOINCREMENT "
					"						UNIQUE, "
					"	name        TEXT, "
					"	description BLOB, "
					"	link        TEXT "
					");"))
		return(false);

	if(!createTable("CREATE TABLE rechercheCharacter ( "
					"	rechercheID INTEGER REFERENCES recherche (id), "
					"	characterID INTEGER REFERENCES character (id) "
					");"))
		return(false);

	if(!createTable("CREATE TABLE rechercheImage ( "
					"	rechercheID INTEGER REFERENCES recherche (id), "
					"	imageID     INTEGER REFERENCES image (id)  "
					");"))
		return(false);

	if(!createTable("CREATE TABLE rechercheObject ( "
					"	rechercheID INTEGER REFERENCES recherche (id), "
					"	objectID    INTEGER REFERENCES object (id)  "
					");"))
		return(false);

	if(!createTable("CREATE TABLE recherchePlace ( "
					"	rechercheID INTEGER REFERENCES recherche (id), "
					"	placeID     INTEGER REFERENCES place (id)  "
					");"))
		return(false);

	if(!createTable("CREATE TABLE scene ( "
					"	id          INTEGER PRIMARY KEY AUTOINCREMENT "
					"						UNIQUE, "
					"	chapterID   INTEGER REFERENCES chapter (id), "
					"	name        TEXT, "
					"	[order]     INTEGER, "
					"	description TEXT, "
					"	state       INTEGER, "
					"	startedAt   DATETIME, "
					"	finishedAt  DATETIME, "
					"	targetDate  DATETIME, "
					"	text        BLOB "
					");"))
		return(false);

	if(!createTable("CREATE TABLE sceneCharacter ( "
					"	sceneID     INTEGER REFERENCES scene (id), "
					"	characterID INTEGER REFERENCES character (id), "
					"	description BLOB "
					");"))
		return(false);

	if(!createTable("CREATE TABLE sceneObject ( "
					"	sceneID     INTEGER REFERENCES scene (id), "
					"	objectID    INTEGER REFERENCES object (id), "
					"	description BLOB "
					");"))
		return(false);

	if(!createTable("CREATE TABLE scenePlace ( "
					"	sceneID     INTEGER REFERENCES scene (id), "
					"	placeID     INTEGER REFERENCES place (id), "
					"	description BLOB "
					");"))
		return(false);

	return(true);
}

bool cStoryBook::updateDatabase()
{
	return(true);
}

bool cStoryBook::verify()
{
	return(true);
}

bool cStoryBook::loadBook()
{
	return(m_book.load());
}

bool cStoryBook::loadPartList()
{
	return(m_partList.load());
}

bool cStoryBook::loadChapterList()
{
	return(m_chapterList.load(&m_partList));
}

bool cStoryBook::loadSceneList()
{
	return(m_sceneList.load(&m_chapterList, &m_characterList, &m_objectList, &m_placeList));
}

bool cStoryBook::loadCharacterList()
{
	return(m_characterList.load(&m_imageList));
}

bool cStoryBook::loadPlaceList()
{
	return(m_placeList.load(&m_imageList));
}

bool cStoryBook::loadObjectList()
{
	return(m_objectList.load(&m_imageList));
}

bool cStoryBook::loadRechercheList()
{
	return(m_rechercheList.load(&m_imageList, &m_characterList, &m_objectList, &m_placeList));
}

bool cStoryBook::loadImageList()
{
	return(m_imageList.load());
}

QString cStoryBook::title()
{
	if(!m_bIsOpen)
		return("Untitled");
	else
		return(m_book.title());
}

QString cStoryBook::author()
{
	if(!m_bIsOpen)
		return("");
	else
		return(m_book.author());
}

cChapterList* cStoryBook::chapterList()
{
	return(&m_chapterList);
}

cSceneList* cStoryBook::sceneList()
{
	return(&m_sceneList);
}

bool cStoryBook::addPart(const QString& szPartName)
{
	cPart*	lpPart	= m_partList.add(-1);
	lpPart->setName(szPartName);
	return(true);
}

bool cStoryBook::fillOutlineList(QTreeView* lpView)
{
	QMap<qint32, QStandardItem*>	part;
	QMap<qint32, QStandardItem*>	chapter;
	QStandardItemModel*				lpModel			= (QStandardItemModel*)lpView->model();
	QStandardItem*					lpRootItem		= lpModel->invisibleRootItem();
	QFont							fontPart		= lpRootItem->font();
	QFont							fontChapter		= lpRootItem->font();
	QFont							fontScene		= lpRootItem->font();
	QColor							background(241, 241, 241);

	lpModel->clear();

	QStringList						headerLabels	= QStringList() << tr("name") << tr("state");
	lpModel->setHorizontalHeaderLabels(headerLabels);

	fontPart.setBold(true);
	fontChapter.setItalic(true);

	for(int x = 0;x < m_partList.count();x++)
	{
		cPart*			lpPart	= m_partList.at(x);
		QStandardItem*	lpItem		= new QStandardItem(lpPart->name());
		lpItem->setData(QVariant::fromValue(lpPart));
		lpItem->setFont(fontPart);
		lpItem->setBackground(QBrush(background));
		if(lpPart->description())
			lpItem->setToolTip(lpPart->description()->toPlainText());
		part.insert(lpPart->id(), lpItem);
		lpModel->appendRow(lpItem);

		lpView->setFirstColumnSpanned(lpModel->rowCount()-1, lpModel->invisibleRootItem()->index(), true);
	}

	for(int x = 0;x < m_chapterList.count();x++)
	{
		cChapter*		lpChapter	= m_chapterList.at(x);
		QStandardItem*	lpRoot		= part.value(lpChapter->part()->id());

		if(lpRoot)
		{
			QStandardItem*	lpItem		= new QStandardItem(lpChapter->name());
			lpItem->setData(QVariant::fromValue(lpChapter));
			lpItem->setFont(fontChapter);
			lpItem->setForeground(QBrush(Qt::darkBlue));
			lpItem->setBackground(QBrush(background));
			lpItem->setToolTip(lpChapter->description()->toPlainText());
			chapter.insert(lpChapter->id(), lpItem);
			lpRoot->appendRow(lpItem);
			lpView->setFirstColumnSpanned(lpRoot->rowCount()-1, lpRoot->index(), true);
		}
	}

	for(int x = 0;x < m_sceneList.count();x++)
	{
		cScene*			lpScene		= m_sceneList.at(x);
		QStandardItem*	lpChapterItem	= chapter.value(lpScene->chapter()->id());

		if(lpChapterItem)
		{
			QList<QStandardItem*>	lpItems;

			lpItems << new QStandardItem(lpScene->name());
			lpItems << new QStandardItem(lpScene->stateText());

			lpItems[0]->setData(QVariant::fromValue(lpScene));
			lpItems[0]->setFont(fontScene);
			lpItems[0]->setForeground(QBrush(Qt::blue));
			lpItems[0]->setToolTip(lpScene->description()->toPlainText());

			lpItems[1]->setData(QVariant::fromValue(lpScene));
			lpItems[1]->setBackground(QBrush(lpScene->stateColor()));
			lpItems[1]->setTextAlignment(Qt::AlignCenter);
			lpItems[1]->setToolTip(lpScene->description()->toPlainText());

			lpChapterItem->appendRow(lpItems);
		}
	}

	lpView->header()->setStretchLastSection(false);
	lpView->header()->setSectionResizeMode(0, QHeaderView::Stretch);
	lpView->header()->setSectionResizeMode(1, QHeaderView::Interactive);

	lpView->expandAll();


	for(int i = 0;i < headerLabels.count();i++)
		lpView->resizeColumnToContents(i);

	return(true);
}

bool cStoryBook::fillCharacterList(QTreeView* lpView)
{
	QStandardItemModel*				lpModel					= (QStandardItemModel*)lpView->model();
	QStandardItem*					lpRootItem				= lpModel->invisibleRootItem();
	QFont							fontMainCharacter		= lpRootItem->font();
	QFont							fontNonMainCharacter	= lpRootItem->font();

	lpModel->clear();

	QStringList						headerLabels	= QStringList() << tr("name") << tr("creature") << tr("gender");
	lpModel->setHorizontalHeaderLabels(headerLabels);

	fontMainCharacter.setBold(true);
	fontNonMainCharacter.setItalic(true);

	for(int x = 0;x < m_characterList.count();x++)
	{
		cCharacter*				lpCharacter	= m_characterList.at(x);
		QList<QStandardItem*>	lpItems;

		lpItems.append(new QStandardItem(lpCharacter->name()));
		lpItems.append(new QStandardItem(lpCharacter->creature()));
		lpItems.append(new QStandardItem(lpCharacter->genderText()));

		for(int i = 0;i < headerLabels.count();i++)
		{
			lpItems[i]->setData(QVariant::fromValue(lpCharacter));
			if(lpCharacter->mainCharacter())
				lpItems[i]->setFont(fontMainCharacter);
			else
				lpItems[i]->setFont(fontNonMainCharacter);

			lpItems[i]->setToolTip(lpCharacter->description()->toPlainText());
		}

		lpModel->appendRow(lpItems);
	}

	lpView->header()->setStretchLastSection(true);

	lpView->expandAll();

	for(int i = 0;i < headerLabels.count();i++)
		lpView->resizeColumnToContents(i);

	return(true);
}

bool cStoryBook::fillPlaceList(QTreeView* lpView)
{
	QStandardItemModel*				lpModel					= (QStandardItemModel*)lpView->model();

	lpModel->clear();

	QStringList						headerLabels	= QStringList() << tr("name") << tr("location") << tr("type");
	lpModel->setHorizontalHeaderLabels(headerLabels);

	for(int x = 0;x < m_placeList.count();x++)
	{
		cPlace*					lpPlace		= m_placeList.at(x);
		QList<QStandardItem*>	lpItems;

		lpItems.append(new QStandardItem(lpPlace->name()));
		lpItems.append(new QStandardItem(lpPlace->location()));
		lpItems.append(new QStandardItem(lpPlace->type()));

		for(int i = 0;i < headerLabels.count();i++)
		{
			lpItems[i]->setData(QVariant::fromValue(lpPlace));
			lpItems[i]->setToolTip(lpPlace->description()->toPlainText());
		}

		lpModel->appendRow(lpItems);
	}

	lpView->header()->setStretchLastSection(true);

	lpView->expandAll();

	for(int i = 0;i < headerLabels.count();i++)
		lpView->resizeColumnToContents(i);

	return(true);
}

bool cStoryBook::fillObjectList(QTreeView* lpView)
{
	QStandardItemModel*				lpModel					= (QStandardItemModel*)lpView->model();

	lpModel->clear();

	QStringList						headerLabels	= QStringList() << tr("name") << tr("type");
	lpModel->setHorizontalHeaderLabels(headerLabels);

	for(int x = 0;x < m_objectList.count();x++)
	{
		cObject*				lpObject		= m_objectList.at(x);
		QList<QStandardItem*>	lpItems;

		lpItems.append(new QStandardItem(lpObject->name()));
		lpItems.append(new QStandardItem(lpObject->type()));

		for(int i = 0;i < headerLabels.count();i++)
		{
			lpItems[i]->setData(QVariant::fromValue(lpObject));
			lpItems[i]->setToolTip(lpObject->description()->toPlainText());
		}

		lpModel->appendRow(lpItems);
	}

	lpView->header()->setStretchLastSection(true);

	lpView->expandAll();

	for(int i = 0;i < headerLabels.count();i++)
		lpView->resizeColumnToContents(i);

	return(true);
}

bool cStoryBook::fillRechercheList(QTreeView* lpView)
{
	QStandardItemModel*				lpModel					= (QStandardItemModel*)lpView->model();

	lpModel->clear();

	QStringList						headerLabels	= QStringList() << tr("name") << tr("link");
	lpModel->setHorizontalHeaderLabels(headerLabels);

	for(int x = 0;x < m_rechercheList.count();x++)
	{
		cRecherche*				lpRecherche		= m_rechercheList.at(x);
		QList<QStandardItem*>	lpItems;

		lpItems.append(new QStandardItem(lpRecherche->name()));
		lpItems.append(new QStandardItem(lpRecherche->link()));

		for(int i = 0;i < headerLabels.count();i++)
		{
			lpItems[i]->setData(QVariant::fromValue(lpRecherche));
			lpItems[i]->setToolTip(lpRecherche->description()->toPlainText());
		}

		lpModel->appendRow(lpItems);
	}

	lpView->header()->setStretchLastSection(true);

	lpView->expandAll();

	for(int i = 0;i < headerLabels.count();i++)
		lpView->resizeColumnToContents(i);

	return(true);
}
