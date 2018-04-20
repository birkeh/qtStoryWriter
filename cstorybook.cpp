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


cStoryBook::cStoryBook(const QString &szProjectPath, QObject *parent) :
	QObject(parent),
	m_szProjectPath(szProjectPath),
	m_bIsOpen(false)
{
	if(!openDatabase())
		return;

	if(!loadBook())
		return;

	if(!loadPartList())
		return;

	if(!loadChapterList())
		return;

	if(!loadSceneList())
		return;

	if(!loadCharacterList())
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
	QString		szDatabase	= QString("%1%2storyBook.project").arg(m_szProjectPath).arg(QDir::separator());
	QFile		file(szDatabase);

	if(!file.exists())
	{
		myDebug << QObject::tr("project does not exist");
		return(false);

	}
	m_db	= QSqlDatabase::addDatabase("QSQLITE");
	m_db.setHostName("localhost");
	m_db.setDatabaseName(szDatabase);

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
					"	description TEXT, "
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

	if(!createTable("CREATE TABLE characterImage ( "
					"	characterID INTEGER REFERENCES character (id), "
					"	imageID     INTEGER REFERENCES image (id)  "
					");"))
		return(false);

	if(!createTable("CREATE TABLE image ( "
					"	id          INTEGER PRIMARY KEY AUTOINCREMENT "
					"						UNIQUE, "
					"	type        TEXT, "
					"	name        TEXT, "
					"	description TEXT, "
					"	image       BLOB "
					");"))
		return(false);

	if(!createTable("CREATE TABLE object ( "
					"	id          INTEGER PRIMARY KEY AUTOINCREMENT "
					"						UNIQUE, "
					"	name        TEXT, "
					"	type        TEXT, "
					"	description TEXT "
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
					"	description TEXT, "
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
					"	description TEXT, "
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
					"	description TEXT "
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
	return(m_sceneList.load(&m_chapterList));
}

bool cStoryBook::loadCharacterList()
{
	return(m_characterList.load());
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
		lpItem->setToolTip(lpPart->description());
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
			lpItem->setToolTip(lpChapter->description());
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
			lpItems[0]->setToolTip(lpScene->description());

			lpItems[1]->setData(QVariant::fromValue(lpScene));
			lpItems[1]->setBackground(QBrush(lpScene->stateColor()));
			lpItems[1]->setTextAlignment(Qt::AlignCenter);
			lpItems[1]->setToolTip(lpScene->description());

			lpChapterItem->appendRow(lpItems);
		}
	}

	lpView->header()->setStretchLastSection(false);
	lpView->header()->setSectionResizeMode(0, QHeaderView::Stretch);
	lpView->header()->setSectionResizeMode(1, QHeaderView::Interactive);

	lpView->expandAll();
	lpView->resizeColumnToContents(0);
	lpView->resizeColumnToContents(1);

	return(true);
}

bool cStoryBook::fillCharacterList(QTreeView* lpView)
{
	QStandardItemModel*				lpModel					= (QStandardItemModel*)lpView->model();
	QStandardItem*					lpRootItem				= lpModel->invisibleRootItem();
	QFont							fontMainCharacter		= lpRootItem->font();
	QFont							fontNonMainCharacter	= lpRootItem->font();

	lpModel->clear();

	QStringList						headerLabels	= QStringList() << tr("name");
	lpModel->setHorizontalHeaderLabels(headerLabels);

	fontMainCharacter.setBold(true);
	fontNonMainCharacter.setItalic(true);

	for(int x = 0;x < m_characterList.count();x++)
	{
		cCharacter*		lpCharacter	= m_characterList.at(x);
		QStandardItem*	lpItem		= new QStandardItem(lpCharacter->name());
		lpItem->setData(QVariant::fromValue(lpCharacter));

		if(lpCharacter->mainCharacter())
			lpItem->setFont(fontMainCharacter);
		else
			lpItem->setFont(fontNonMainCharacter);

//		lpItem->setToolTip(lpPart->description());
		lpModel->appendRow(lpItem);
	}

	lpView->header()->setStretchLastSection(true);

	lpView->expandAll();
	lpView->resizeColumnToContents(0);

	return(true);
}
