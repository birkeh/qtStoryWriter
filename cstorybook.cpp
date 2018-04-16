#include "cstorybook.h"
#include "common.h"

#include <QVariant>

#include <QSqlQuery>
#include <QSqlError>

#include <QDir>


cStoryBook::cStoryBook(const QString &szProjectPath) :
	m_szProjectPath(szProjectPath),
	m_bIsOpen(false)
{
	if(!openDatabase())
		return;

	if(!loadBook())
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
	m_db	= QSqlDatabase::addDatabase("QSQLITE");
	m_db.setHostName("localhost");
	m_db.setDatabaseName(QString("%1%2storyBook.project").arg(m_szProjectPath).arg(QDir::separator()));

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
					"    shortDescription TEXT, "
					"    description      TEXT, "
					"    author           TEXT, "
					"    startedAt        DATE, "
					"    finishedAt       DATE, "
					"    targetDate       DATE "
					");"))
		return(false);

	if(!createTable("CREATE TABLE chapter ( "
					"	id          INTEGER PRIMARY KEY AUTOINCREMENT "
					"						UNIQUE, "
					"	partID      INTEGER REFERENCES part (id), "
					"	name        TEXT, "
					"	[order]     INTEGER, "
					"	description TEXT, "
					"	file        TEXT "
					");"))
		return(false);

	if(!createTable("CREATE TABLE character ( "
					"	id              INTEGER PRIMARY KEY AUTOINCREMENT "
					"							UNIQUE, "
					"	mainCharacter   BOOLEAN, "
					"	gender          BOOLEAN, "
					"	title           TEXT, "
					"	firstName       TEXT, "
					"	middleName      TEXT, "
					"	lastName        TEXT, "
					"	height          DOUBLE, "
					"	weight          DOUBLE, "
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
					"	description     TEXT "
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
					"	file        TEXT "
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
					"	file        TEXT "
					");"))
		return(false);

	if(!createTable("CREATE TABLE place ( "
					"	id          INTEGER PRIMARY KEY AUTOINCREMENT "
					"						UNIQUE, "
					"	name        TEXT, "
					"	location    TEXT, "
					"	type        TEXT, "
					"	description TEXT "
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
					"	startedAt   DATE, "
					"	finishedAt  DATE, "
					"	targetDate  DATE, "
					"	file        TEXT "
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
					"	description TEXT "
					");"))
		return(false);

	if(!createTable("CREATE TABLE scenePlace ( "
					"	sceneID     INTEGER REFERENCES scene (id), "
					"	placeID     INTEGER REFERENCES place (id), "
					"	description TEXT "
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
	QSqlQuery	query;

	query.prepare("SELECT title, subTitle, shortDescription, description, author, startedAt, finishedAt, targetDate FROM book;");
	if(!query.exec())
	{
		myDebug << query.lastError().text();
		return(false);
	}

	query.first();

	m_book.setTitle(query.value("title").toString());
	m_book.setSubTitle(query.value("subtitle").toString());
	m_book.setShortDescription(query.value("shortDescription").toString());
	m_book.setDescription(query.value("description").toString());
	m_book.setAuthor(query.value("author").toString());
	m_book.setStartedAt(query.value("startedAt").toDate());
	m_book.setFinishedAt(query.value("finishedAt").toDate());
	m_book.setTargetDate(query.value("targetDate").toDate());

	return(true);
}
