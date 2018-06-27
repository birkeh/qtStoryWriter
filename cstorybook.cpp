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

#ifndef QT_NO_PRINTER
#include <QPrinter>
#endif


cStoryBook::cStoryBook(QObject *parent) :
	QObject(parent),
	m_szProject(""),
	m_bIsOpen(false)
{
	m_book.setTitle("untitled");
	m_bIsOpen	= true;
}

cStoryBook::cStoryBook(const QString &szProject, QObject *parent) :
	QObject(parent),
	m_szProject(szProject),
	m_bIsOpen(false)
{
	if(!openDatabase())
		return;

	if(!loadConfig())
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

bool cStoryBook::save()
{
	if(m_szProject.isEmpty())
		return(false);

	if(!m_db.isOpen())
		return(false);

	if(!saveConfig())
		return(false);

	if(!saveCharacterList())
		return(false);

	if(!savePlaceList())
		return(false);

	if(!saveObjectList())
		return(false);

	if(!saveBook())
		return(false);

	if(!savePartList())
		return(false);

	if(!saveChapterList())
		return(false);

	if(!saveSceneList())
		return(false);

	if(!saveRechercheList())
		return(false);

	QSqlQuery	query;
	query.prepare("VACUUM;");
	if(!query.exec())
		myDebug << query.lastError().text();

	return(true);
}

bool cStoryBook::saveAs(const QString& szProject)
{
	if(m_szProject == szProject)
		return(save());

	m_szProject	= szProject;

	if(m_db.isOpen())
		m_db.close();

	if(!openDatabase())
		return(false);

	for(int x = 0;x < m_characterList.count();x++)
		m_characterList.at(x)->setID(-1);

	for(int x = 0;x < m_placeList.count();x++)
		m_placeList.at(x)->setID(-1);

	for(int x = 0;x < m_objectList.count();x++)
		m_objectList.at(x)->setID(-1);

	for(int x = 0;x < m_partList.count();x++)
		m_partList.at(x)->setID(-1);

	for(int x = 0;x < m_chapterList.count();x++)
		m_chapterList.at(x)->setID(-1);

	for(int x = 0;x < m_sceneList.count();x++)
		m_sceneList.at(x)->setID(-1);

	for(int x = 0;x < m_rechercheList.count();x++)
		m_rechercheList.at(x)->setID(-1);


	return(save());
}

bool cStoryBook::printPdf(const QString& szFileName)
{
	QPrinter	printer(QPrinter::PrinterResolution);

	printer.setOutputFormat(QPrinter::PdfFormat);
	printer.setPaperSize(QPrinter::A4);
	printer.setOutputFileName(szFileName);

//	QMap<qint32, QStandardItem*>	part;
//	QMap<qint32, QStandardItem*>	chapter;
//	QStandardItemModel*				lpModel			= (QStandardItemModel*)lpView->model();
//	QStandardItem*					lpRootItem		= lpModel->invisibleRootItem();
//	QFont							fontPart		= lpRootItem->font();
//	QFont							fontChapter		= lpRootItem->font();
//	QFont							fontScene		= lpRootItem->font();
//	QColor							background(241, 241, 241);

//	for(int x = 0;x < m_partList.count();x++)
//	{
//		cPart*			lpPart	= m_partList.at(x);
//		if(lpPart->deleted())
//			continue;

//		QStandardItem*	lpItem		= new QStandardItem(lpPart->name());
//		lpItem->setData(QVariant::fromValue(lpPart));
//		lpItem->setFont(fontPart);
//		lpItem->setBackground(QBrush(background));
//		if(lpPart->description())
//			lpItem->setToolTip(lpPart->description()->toPlainText());
//		part.insert(lpPart->id(), lpItem);
//		lpModel->appendRow(lpItem);
//		lpPart->setItem(lpItem);

//		lpView->setFirstColumnSpanned(lpModel->rowCount()-1, lpModel->invisibleRootItem()->index(), true);
//	}

//	for(int x = 0;x < m_chapterList.count();x++)
//	{
//		cChapter*		lpChapter	= m_chapterList.at(x);

//		if(lpChapter->deleted())
//			continue;

//		QStandardItem*	lpRoot		= part.value(lpChapter->part()->id());

//		if(lpRoot)
//		{
//			QStandardItem*	lpItem		= new QStandardItem(lpChapter->name());
//			lpItem->setData(QVariant::fromValue(lpChapter));
//			lpItem->setFont(fontChapter);
//			lpItem->setForeground(QBrush(Qt::darkBlue));
//			lpItem->setBackground(QBrush(background));
//			if(lpChapter->description())
//				lpItem->setToolTip(lpChapter->description()->toPlainText());
//			chapter.insert(lpChapter->id(), lpItem);
//			lpRoot->appendRow(lpItem);
//			lpChapter->setItem(lpItem);

//			lpView->setFirstColumnSpanned(lpRoot->rowCount()-1, lpRoot->index(), true);
//		}
//	}

	for(int x = 0;x < m_sceneList.count();x++)
	{
		cScene*			lpScene		= m_sceneList.at(x);

		if(lpScene->deleted())
			continue;

		lpScene->text()->setPageSize(printer.pageRect().size());
		lpScene->text()->print(&printer);
	}

	return(true);
}

bool cStoryBook::openDatabase()
{
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

		query.prepare("SELECT version FROM config;");
		if(!query.exec())
		{
			myDebug << query.lastError().text();
			m_db.close();
			return(false);
		}

		query.first();
		if(query.value("version").toDouble() < 0.1)
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
					"    version                  REAL, "
					"    printTitle               BOOLEAN, "
					"    titleFont                TEXT, "
					"    titleFontSize            INTEGER, "
					"    titleBold                BOOLEAN, "
					"    titleItalic              BOOLEAN, "
					"    titleUnderline           BOOLEAN, "
					"    titleAlign               INTEGER, "
					"    printSubTitle            BOOLEAN, "
					"    subtitleFont             TEXT, "
					"    subtitleFontSize         INTEGER, "
					"    subtitleBold             BOOLEAN, "
					"    subtitleItalic           BOOLEAN, "
					"    subtitleUnderline        BOOLEAN, "
					"    subtitleAlign            INTEGER, "
					"    printShortDescription    BOOLEAN, "
					"    printDescription         BOOLEAN, "
					"    printAuthor              BOOLEAN, "
					"    authorFont               TEXT, "
					"    authorFontSize           INTEGER, "
					"    authorBold               BOOLEAN, "
					"    authorItalic             BOOLEAN, "
					"    authorUnderline          BOOLEAN, "
					"    authorAlign              INTEGER, "
					"    printPartName            BOOLEAN, "
					"    partFont                 TEXT, "
					"    partFontSize             INTEGER, "
					"    partBold                 BOOLEAN, "
					"    partItalic               BOOLEAN, "
					"    partUnderline            BOOLEAN, "
					"    partAlign                INTEGER, "
					"    printPartDescription     BOOLEAN, "
					"    printPartText            BOOLEAN, "
					"    printChapterName         BOOLEAN, "
					"    chapterFont              TEXT, "
					"    chapterFontSize          INTEGER, "
					"    chapterBold              BOOLEAN, "
					"    chapterItalic            BOOLEAN, "
					"    chapterUnderline         BOOLEAN, "
					"    chapterAlign             INTEGER, "
					"    printChapterDescription  BOOLEAN, "
					"    printChapterText         BOOLEAN, "
					"    printSceneName           BOOLEAN, "
					"    sceneFont                TEXT, "
					"    sceneFontSize            INTEGER, "
					"    sceneBold                BOOLEAN, "
					"    sceneItalic              BOOLEAN, "
					"    sceneUnderline           BOOLEAN, "
					"    sceneAlign               INTEGER, "
					"    printSceneDescription    BOOLEAN, "
					"    printSceneText           BOOLEAN, "
					"    paperSize                TEXT, "
					"    paperOrientation         INTEGER, "
					"    leftMargin               REAL, "
					"    rightMargin              REAL, "
					"    topMargin                REAL, "
					"    bottomMargin             REAL, "
					"    unit                     INTEGER"
					"); "))
		return(false);

	query.prepare("INSERT INTO config (version) VALUES (:version);");
	query.bindValue(":version", 0.1);
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
					"); "))
		return(false);

	if(!createTable("CREATE TABLE chapter ( "
					"    id          INTEGER PRIMARY KEY AUTOINCREMENT "
					"                        UNIQUE, "
					"    partID      INTEGER REFERENCES part (id), "
					"    name        TEXT, "
					"    sortOrder   INTEGER, "
					"    description BLOB, "
					"    text        BLOB "
					"); "))
		return(false);

	if(!createTable("CREATE TABLE character ( "
					"    id              INTEGER PRIMARY KEY AUTOINCREMENT "
					"                            UNIQUE, "
					"    mainCharacter   BOOLEAN, "
					"    creature        TEXT, "
					"    gender          INTEGER, "
					"    title           TEXT, "
					"    firstName       TEXT, "
					"    middleName      TEXT, "
					"    lastName        TEXT, "
					"    nickName        TEXT, "
					"    height          DOUBLE, "
					"    weight          DOUBLE, "
					"    dateOfBirth     DATE, "
					"    placeOfBirth    TEXT, "
					"    dateOfDeath     DATE, "
					"    placeOfDeath    TEXT, "
					"    hairColor       TEXT, "
					"    hairCut         TEXT, "
					"    hairLength      TEXT, "
					"    figure          TEXT, "
					"    nature          TEXT, "
					"    spokenLanguages TEXT, "
					"    skin            TEXT, "
					"    school          TEXT, "
					"    job             TEXT, "
					"    description     BLOB "
					"); "))
		return(false);

	if(!createTable("CREATE TABLE characterImage ( "
					"    characterID INTEGER REFERENCES character (id), "
					"    name        TEXT, "
					"    description BLOB, "
					"    image       BLOB "
					"); "))
		return(false);

	if(!createTable("CREATE TABLE object ( "
					"    id          INTEGER PRIMARY KEY AUTOINCREMENT "
					"                        UNIQUE, "
					"    name        TEXT, "
					"    type        TEXT, "
					"    description BLOB "
					"); "))
		return(false);

	if(!createTable("CREATE TABLE objectImage ( "
					"    objectID INTEGER REFERENCES object (id), "
					"    name        TEXT, "
					"    description BLOB, "
					"    image       BLOB "
					"); "))
		return(false);

	if(!createTable("CREATE TABLE part ( "
					"    id          INTEGER PRIMARY KEY AUTOINCREMENT "
					"                        UNIQUE, "
					"    name        TEXT, "
					"    sortOrder   INTEGER, "
					"    description BLOB, "
					"    text        BLOB "
					"); "))
		return(false);

	if(!createTable("CREATE TABLE place ( "
					"    id          INTEGER PRIMARY KEY AUTOINCREMENT "
					"                        UNIQUE, "
					"    name        TEXT, "
					"    location    TEXT, "
					"    type        TEXT, "
					"    description BLOB "
					"); "))
		return(false);

	if(!createTable("CREATE TABLE placeImage ( "
					"    placeID INTEGER REFERENCES place (id), "
					"    name        TEXT, "
					"    description BLOB, "
					"    image       BLOB "
					"); "))
		return(false);

	if(!createTable("CREATE TABLE recherche ( "
					"    id          INTEGER PRIMARY KEY AUTOINCREMENT "
					"                        UNIQUE, "
					"    name        TEXT, "
					"    description BLOB, "
					"    link        TEXT "
					"); "))
		return(false);

	if(!createTable("CREATE TABLE rechercheCharacter ( "
					"    rechercheID INTEGER REFERENCES recherche (id), "
					"    characterID INTEGER REFERENCES character (id), "
					"    description BLOB "
					"); "))
		return(false);

	if(!createTable("CREATE TABLE rechercheImage ( "
					"    rechercheID INTEGER REFERENCES recherche (id), "
					"    name        TEXT, "
					"    description BLOB, "
					"    image       BLOB "
					"); "))
		return(false);

	if(!createTable("CREATE TABLE rechercheObject ( "
					"    rechercheID INTEGER REFERENCES recherche (id), "
					"    objectID    INTEGER REFERENCES object (id), "
					"    description BLOB "
					"); "))
		return(false);

	if(!createTable("CREATE TABLE recherchePlace ( "
					"    rechercheID INTEGER REFERENCES recherche (id), "
					"    placeID     INTEGER REFERENCES place (id), "
					"    description BLOB "
					"); "))
		return(false);

	if(!createTable("CREATE TABLE scene ( "
					"    id          INTEGER  PRIMARY KEY AUTOINCREMENT "
					"                         UNIQUE, "
					"    chapterID   INTEGER  REFERENCES chapter (id), "
					"    name        TEXT, "
					"    sortOrder   INTEGER, "
					"    description BLOB, "
					"    state       INTEGER, "
					"    startedAt   DATETIME, "
					"    finishedAt  DATETIME, "
					"    targetDate  DATETIME, "
					"    text        BLOB "
					"); "))
		return(false);

	if(!createTable("CREATE TABLE sceneCharacter ( "
					"    sceneID     INTEGER REFERENCES scene (id), "
					"    characterID INTEGER REFERENCES character (id), "
					"    description BLOB "
					"); "))
		return(false);

	if(!createTable("CREATE TABLE sceneObject ( "
					"    sceneID     INTEGER REFERENCES scene (id), "
					"    objectID    INTEGER REFERENCES object (id), "
					"    description BLOB "
					"); "))
		return(false);

	if(!createTable("CREATE TABLE scenePlace ( "
					"    sceneID     INTEGER REFERENCES scene (id), "
					"    placeID     INTEGER REFERENCES place (id), "
					"    description BLOB "
					"); "))
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

bool cStoryBook::loadConfig()
{
	QSqlQuery	query;

	query.prepare("SELECT version, printTitle, titleFont, titleFontSize, titleBold, titleItalic, titleUnderline, titleAlign, printSubTitle, subtitleFont, subtitleFontSize, subtitleBold, subtitleItalic, subtitleUnderline, subtitleAlign, printShortDescription, printDescription, printAuthor, authorFont, authorFontSize, authorBold, authorItalic, authorUnderline, authorAlign, printPartName, partFont, partFontSize, partBold, partItalic, partUnderline, partAlign, printPartDescription, printPartText, printChapterName, chapterFont, chapterFontSize, chapterBold, chapterItalic, chapterUnderline, chapterAlign, printChapterDescription, printChapterText, printSceneName, sceneFont, sceneFontSize, sceneBold, sceneItalic, sceneUnderline, sceneAlign, printSceneDescription, printSceneText, paperSize, paperOrientation, leftMargin, rightMargin, topMargin, bottomMargin, unit FROM config;");

	if(!query.exec())
	{
		myDebug << query.lastError().text();
		return(false);
	}
	query.first();

	m_bPrintTitle				= query.value("printTitle").toBool();
	m_szTitleFont				= query.value("titleFont").toString();
	m_iTitleFontSize			= query.value("titleFontSize").toInt();
	m_bTitleBold				= query.value("titleBold").toBool();
	m_bTitleItalic				= query.value("titleItalic").toBool();
	m_bTitleUnderline			= query.value("titleUnderline").toBool();
	m_iTitleAlign				= query.value("titleAlign").toInt();
	m_bPrintSubTitle			= query.value("printSubTitle").toBool();
	m_szSubtitleFont			= query.value("subtitleFont").toString();
	m_iSubtitleFontSize			= query.value("subtitleFontSize").toInt();
	m_bSubtitleBold				= query.value("subtitleBold").toBool();
	m_bSubtitleItalic			= query.value("subtitleItalic").toBool();
	m_bSubtitleUnderline		= query.value("subtitleUnderline").toBool();
	m_iSubtitleAlign			= query.value("subtitleAlign").toInt();
	m_bPrintShortDescription	= query.value("printShortDescription").toBool();
	m_bPrintDescription			= query.value("printDescription").toBool();
	m_bPrintAuthor				= query.value("printAuthor").toBool();
	m_szAuthorFont				= query.value("authorFont").toString();
	m_iAuthorFontSize			= query.value("authorFontSize").toInt();
	m_bAuthorBold				= query.value("authorBold").toBool();
	m_bAuthorItalic				= query.value("authorItalic").toBool();
	m_bAuthorUnderline			= query.value("authorUnderline").toBool();
	m_iAuthorAlign				= query.value("authorAlign").toInt();
	m_bPrintPartName			= query.value("printPartName").toBool();
	m_szPartFont				= query.value("partFont").toString();
	m_iPartFontSize				= query.value("partFontSize").toInt();
	m_bPartBold					= query.value("partBold").toBool();
	m_bPartItalic				= query.value("partItalic").toBool();
	m_bPartUnderline			= query.value("partUnderline").toBool();
	m_iPartAlign				= query.value("partAlign").toInt();
	m_bPrintPartDescription		= query.value("printPartDescription").toBool();
	m_bPrintPartText			= query.value("printPartText").toBool();
	m_bPrintChapterName			= query.value("printChapterName").toBool();
	m_szChapterFont				= query.value("chapterFont").toString();
	m_iChapterFontSize			= query.value("chapterFontSize").toInt();
	m_bChapterBold				= query.value("chapterBold").toBool();
	m_bChapterItalic			= query.value("chapterItalic").toBool();
	m_bChapterUnderline			= query.value("chapterUnderline").toBool();
	m_iChapterAlign				= query.value("chapterAlign").toInt();
	m_bPrintChapterDescription	= query.value("printChapterDescription").toBool();
	m_bPrintChapterText			= query.value("printChapterText").toBool();
	m_bPrintSceneName			= query.value("printSceneName").toBool();
	m_szSceneFont				= query.value("sceneFont").toString();
	m_iSceneFontSize			= query.value("sceneFontSize").toInt();
	m_bSceneBold				= query.value("sceneBold").toBool();
	m_bSceneItalic				= query.value("sceneItalic").toBool();
	m_bSceneUnderline			= query.value("sceneUnderline").toBool();
	m_iSceneAlign				= query.value("sceneAlign").toInt();
	m_bPrintSceneDescription	= query.value("printSceneDescription").toBool();
	m_bPrintSceneText			= query.value("printSceneText").toBool();
	m_szPaperSize				= query.value("paperSize").toString();
	m_iPaperOrientation			= query.value("paperOrientation").toInt();
	m_dLeftMargin				= query.value("leftMargin").toDouble();
	m_dRightMargin				= query.value("rightMargin").toDouble();
	m_dTopMargin				= query.value("topMargin").toDouble();
	m_dBottomMargin				= query.value("bottomMargin").toDouble();
	m_iUnit						= query.value("unit").toInt();

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
	return(m_characterList.load());
}

bool cStoryBook::loadPlaceList()
{
	return(m_placeList.load());
}

bool cStoryBook::loadObjectList()
{
	return(m_objectList.load());
}

bool cStoryBook::loadRechercheList()
{
	return(m_rechercheList.load(&m_characterList, &m_objectList, &m_placeList));
}

bool cStoryBook::saveConfig()
{
	QSqlQuery	query;

	query.prepare("DELETE FROM config;");
	if(!query.exec())
	{
		myDebug << query.lastError().text();
		return(false);
	}

	query.prepare("INSERT INTO config (version, printTitle, titleFont, titleFontSize, titleBold, titleItalic, titleUnderline, titleAlign, printSubTitle, subtitleFont, subtitleFontSize, subtitleBold, subtitleItalic, subtitleUnderline, subtitleAlign, printShortDescription, printDescription, printAuthor, authorFont, authorFontSize, authorBold, authorItalic, authorUnderline, authorAlign, printPartName, partFont, partFontSize, partBold, partItalic, partUnderline, partAlign, printPartDescription, printPartText, printChapterName, chapterFont, chapterFontSize, chapterBold, chapterItalic, chapterUnderline, chapterAlign, printChapterDescription, printChapterText, printSceneName, sceneFont, sceneFontSize, sceneBold, sceneItalic, sceneUnderline, sceneAlign, printSceneDescription, printSceneText, paperSize, paperOrientation, leftMargin, rightMargin, topMargin, bottomMargin, unit) VALUES (0.1, :printTitle, :titleFont, :titleFontSize, :titleBold, :titleItalic, :titleUnderline, :titleAlign, :printSubTitle, :subtitleFont, :subtitleFontSize, :subtitleBold, :subtitleItalic, :subtitleUnderline, :subtitleAlign, :printShortDescription, :printDescription, :printAuthor, :authorFont, :authorFontSize, :authorBold, :authorItalic, :authorUnderline, :authorAlign, :printPartName, :partFont, :partFontSize, :partBold, :partItalic, :partUnderline, :partAlign, :printPartDescription, :printPartText, :printChapterName, :chapterFont, :chapterFontSize, :chapterBold, :chapterItalic, :chapterUnderline, :chapterAlign, :printChapterDescription, :printChapterText, :printSceneName, :sceneFont, :sceneFontSize, :sceneBold, :sceneItalic, :sceneUnderline, :sceneAlign, :printSceneDescription, :printSceneText, :paperSize, :paperOrientation, :leftMargin, :rightMargin, :topMargin, :bottomMargin, :unit);");
	query.bindValue("printTitle", m_bPrintTitle);
	query.bindValue("titleFont", m_szTitleFont);
	query.bindValue("titleFontSize", m_iTitleFontSize);
	query.bindValue("titleBold", m_bTitleBold);
	query.bindValue("titleItalic", m_bTitleItalic);
	query.bindValue("titleUnderline", m_bTitleUnderline);
	query.bindValue("titleAlign", m_iTitleAlign);
	query.bindValue("printSubTitle", m_bPrintSubTitle);
	query.bindValue("subtitleFont", m_szSubtitleFont);
	query.bindValue("subtitleFontSize", m_iSubtitleFontSize);
	query.bindValue("subtitleBold", m_bSubtitleBold);
	query.bindValue("subtitleItalic", m_bSubtitleItalic);
	query.bindValue("subtitleUnderline", m_bSubtitleUnderline);
	query.bindValue("subtitleAlign", m_iSubtitleAlign);
	query.bindValue("printShortDescription", m_bPrintShortDescription);
	query.bindValue("printDescription", m_bPrintDescription);
	query.bindValue("printAuthor", m_bPrintAuthor);
	query.bindValue("authorFont", m_szAuthorFont);
	query.bindValue("authorFontSize", m_iAuthorFontSize);
	query.bindValue("authorBold", m_bAuthorBold);
	query.bindValue("authorItalic", m_bAuthorItalic);
	query.bindValue("authorUnderline", m_bAuthorUnderline);
	query.bindValue("authorAlign", m_iAuthorAlign);
	query.bindValue("printPartName", m_bPrintPartName);
	query.bindValue("partFont", m_szPartFont);
	query.bindValue("partFontSize", m_iPartFontSize);
	query.bindValue("partBold", m_bPartBold);
	query.bindValue("partItalic", m_bPartItalic);
	query.bindValue("partUnderline", m_bPartUnderline);
	query.bindValue("partAlign", m_iPartAlign);
	query.bindValue("printPartDescription", m_bPrintPartDescription);
	query.bindValue("printPartText", m_bPrintPartText);
	query.bindValue("printChapterName", m_bPrintChapterName);
	query.bindValue("chapterFont", m_szChapterFont);
	query.bindValue("chapterFontSize", m_iChapterFontSize);
	query.bindValue("chapterBold", m_bChapterBold);
	query.bindValue("chapterItalic", m_bChapterItalic);
	query.bindValue("chapterUnderline", m_bChapterUnderline);
	query.bindValue("chapterAlign", m_iChapterAlign);
	query.bindValue("printChapterDescription", m_bPrintChapterDescription);
	query.bindValue("printChapterText", m_bPrintChapterText);
	query.bindValue("printSceneName", m_bPrintSceneName);
	query.bindValue("sceneFont", m_szSceneFont);
	query.bindValue("sceneFontSize", m_iSceneFontSize);
	query.bindValue("sceneBold", m_bSceneBold);
	query.bindValue("sceneItalic", m_bSceneItalic);
	query.bindValue("sceneUnderline", m_bSceneUnderline);
	query.bindValue("sceneAlign", m_iSceneAlign);
	query.bindValue("printSceneDescription", m_bPrintSceneDescription);
	query.bindValue("printSceneText", m_bPrintSceneText);
	query.bindValue("paperSize", m_szPaperSize);
	query.bindValue("paperOrientation", m_iPaperOrientation);
	query.bindValue("leftMargin", m_dLeftMargin);
	query.bindValue("rightMargin", m_dRightMargin);
	query.bindValue("topMargin", m_dTopMargin);
	query.bindValue("bottomMargin", m_dBottomMargin);
	query.bindValue("unit", m_iUnit);

	if(!query.exec())
	{
		myDebug << query.lastError().text();
		return(false);
	}
	return(true);
}

bool cStoryBook::saveBook()
{
	return(m_book.save());
}

bool cStoryBook::savePartList()
{
	return(m_partList.save());
}

bool cStoryBook::saveChapterList()
{
	return(m_chapterList.save());
}

bool cStoryBook::saveSceneList()
{
	return(m_sceneList.save());
}

bool cStoryBook::saveCharacterList()
{
	return(m_characterList.save());
}

bool cStoryBook::savePlaceList()
{
	return(m_placeList.save());
}

bool cStoryBook::saveObjectList()
{
	return(m_objectList.save());
}

bool cStoryBook::saveRechercheList()
{
	return(m_rechercheList.save());
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

cBook* cStoryBook::book()
{
	return(&m_book);
}

cChapterList* cStoryBook::chapterList()
{
	return(&m_chapterList);
}

cSceneList* cStoryBook::sceneList()
{
	return(&m_sceneList);
}

cCharacterList* cStoryBook::characterList()
{
	return(&m_characterList);
}

cPlaceList* cStoryBook::placeList()
{
	return(&m_placeList);
}

cObjectList* cStoryBook::objectList()
{
	return(&m_objectList);
}

QString cStoryBook::project()
{
	return(m_szProject);
}

bool cStoryBook::addPart(const QString& szPartName)
{
	cPart*	lpPart	= m_partList.add(-1);
	lpPart->setName(szPartName);
	lpPart->setSortOrder(m_partList.nextSort());

	return(true);
}

bool cStoryBook::addChapter(cPart* lpPart, const QString& szChapterName)
{
	cChapter*	lpChapter	= m_chapterList.add(-1);
	lpChapter->setName(szChapterName);
	lpChapter->setPart(lpPart);
	lpChapter->setSortOrder(m_chapterList.nextSort(lpPart));

	return(true);
}

bool cStoryBook::addScene(cChapter* lpChapter, const QString& szSceneName)
{
	cScene*	lpScene	= m_sceneList.add(-1);
	lpScene->setName(szSceneName);
	lpScene->setChapter(lpChapter);
	lpScene->setSortOrder(m_sceneList.nextSort(lpChapter));

	return(true);
}

bool cStoryBook::addCharacter(const QString& szCharacterName)
{
	QString		szFirstName;
	QString		szMiddleName;
	QString		szLastName;
	QStringList	list	= szCharacterName.split(" ");

	if(list.count() == 1)
		szFirstName	= list.at(0);
	else if(list.count() == 2)
	{
		szFirstName	= list.at(0);
		szLastName	= list.at(1);
	}
	else
	{
		szFirstName		= list.at(0);
		szLastName		= list.last();
		szMiddleName	= list.at(1);

		for(int x = 2;x < list.count()-1;x++)
		{
			szMiddleName.append(" ");
			szMiddleName.append(list.at(x));
		}
	}

	cCharacter*	lpCharacter	= m_characterList.add(-1);
	lpCharacter->setFirstName(szFirstName);
	lpCharacter->setMiddleName(szMiddleName);
	lpCharacter->setLastName(szLastName);

	return(true);
}

bool cStoryBook::addPlace(const QString& szPlaceName)
{
	cPlace*	lpPlace	= m_placeList.add(-1);
	lpPlace->setName(szPlaceName);

	return(true);
}

bool cStoryBook::addObject(const QString& szObjectName)
{
	cObject*	lpObject	= m_objectList.add(-1);
	lpObject->setName(szObjectName);

	return(true);
}

bool cStoryBook::addRecherche(const QString& szRechercheName)
{
	cRecherche*	lpRecherche	= m_rechercheList.add(-1);
	lpRecherche->setName(szRechercheName);

	return(true);
}

bool cStoryBook::hasChapter(cPart* lpPart)
{
	return(m_chapterList.find(lpPart).count() > 0);
}

bool cStoryBook::hasScene(cChapter* lpChapter)
{
	return(m_sceneList.find(lpChapter).count() > 0);
}

bool cStoryBook::characterInUse(cCharacter* lpCharacter)
{
	if(m_sceneList.find(lpCharacter).count() > 0)
		return(true);

	if(m_rechercheList.find(lpCharacter).count() > 0)
		return(true);

	return(false);
}

bool cStoryBook::placeInUse(cPlace* lpPlace)
{
	if(m_sceneList.find(lpPlace).count() > 0)
		return(true);

	if(m_rechercheList.find(lpPlace).count() > 0)
		return(true);

	return(false);
}

bool cStoryBook::objectInUse(cObject* lpObject)
{
	if(m_sceneList.find(lpObject).count() > 0)
		return(true);

	if(m_rechercheList.find(lpObject).count() > 0)
		return(true);

	return(false);
}

bool cStoryBook::rechercheInUse(cRecherche* /*lpRecherche*/)
{
	return(false);
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
		if(lpPart->deleted())
			continue;

		QStandardItem*	lpItem		= new QStandardItem(lpPart->name());
		lpItem->setData(QVariant::fromValue(lpPart));
		lpItem->setFont(fontPart);
		lpItem->setBackground(QBrush(background));
		if(lpPart->description())
			lpItem->setToolTip(lpPart->description()->toPlainText());
		part.insert(lpPart->id(), lpItem);
		lpModel->appendRow(lpItem);
		lpPart->setItem(lpItem);

		lpView->setFirstColumnSpanned(lpModel->rowCount()-1, lpModel->invisibleRootItem()->index(), true);
	}

	for(int x = 0;x < m_chapterList.count();x++)
	{
		cChapter*		lpChapter	= m_chapterList.at(x);

		if(lpChapter->deleted())
			continue;

		QStandardItem*	lpRoot		= part.value(lpChapter->part()->id());

		if(lpRoot)
		{
			QStandardItem*	lpItem		= new QStandardItem(lpChapter->name());
			lpItem->setData(QVariant::fromValue(lpChapter));
			lpItem->setFont(fontChapter);
			lpItem->setForeground(QBrush(Qt::darkBlue));
			lpItem->setBackground(QBrush(background));
			if(lpChapter->description())
				lpItem->setToolTip(lpChapter->description()->toPlainText());
			chapter.insert(lpChapter->id(), lpItem);
			lpRoot->appendRow(lpItem);
			lpChapter->setItem(lpItem);

			lpView->setFirstColumnSpanned(lpRoot->rowCount()-1, lpRoot->index(), true);
		}
	}

	for(int x = 0;x < m_sceneList.count();x++)
	{
		cScene*			lpScene		= m_sceneList.at(x);

		if(lpScene->deleted())
			continue;

		QStandardItem*	lpChapterItem	= chapter.value(lpScene->chapter()->id());

		if(lpChapterItem)
		{
			QList<QStandardItem*>	lpItems;

			lpItems << new QStandardItem(lpScene->name());
			lpItems << new QStandardItem(lpScene->stateText());

			lpItems[0]->setData(QVariant::fromValue(lpScene));
			lpItems[0]->setFont(fontScene);
			lpItems[0]->setForeground(QBrush(Qt::blue));
			if(lpScene->description())
				lpItems[0]->setToolTip(lpScene->description()->toPlainText());

			lpItems[1]->setData(QVariant::fromValue(lpScene));
			lpItems[1]->setBackground(QBrush(lpScene->stateColor()));
			lpItems[1]->setTextAlignment(Qt::AlignCenter);
			if(lpScene->description())
				lpItems[1]->setToolTip(lpScene->description()->toPlainText());
			lpScene->setItem(lpItems[0]);
			lpScene->setStateItem(lpItems[1]);

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

		if(lpCharacter->deleted())
			continue;

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

			if(lpCharacter->description())
				lpItems[i]->setToolTip(lpCharacter->description()->toPlainText());
		}

		lpModel->appendRow(lpItems);
		lpCharacter->setItem(lpItems);
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

		if(lpPlace->deleted())
			continue;

		lpItems.append(new QStandardItem(lpPlace->name()));
		lpItems.append(new QStandardItem(lpPlace->location()));
		lpItems.append(new QStandardItem(lpPlace->type()));

		for(int i = 0;i < headerLabels.count();i++)
		{
			lpItems[i]->setData(QVariant::fromValue(lpPlace));
			if(lpPlace->description())
				lpItems[i]->setToolTip(lpPlace->description()->toPlainText());
		}

		lpModel->appendRow(lpItems);
		lpPlace->setItem(lpItems);
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

		if(lpObject->deleted())
			continue;

		lpItems.append(new QStandardItem(lpObject->name()));
		lpItems.append(new QStandardItem(lpObject->type()));

		for(int i = 0;i < headerLabels.count();i++)
		{
			lpItems[i]->setData(QVariant::fromValue(lpObject));
			if(lpObject->description())
				lpItems[i]->setToolTip(lpObject->description()->toPlainText());
		}

		lpModel->appendRow(lpItems);
		lpObject->setItem(lpItems);
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

		if(lpRecherche->deleted())
			continue;

		lpItems.append(new QStandardItem(lpRecherche->name()));
		lpItems.append(new QStandardItem(lpRecherche->link()));

		for(int i = 0;i < headerLabels.count();i++)
		{
			lpItems[i]->setData(QVariant::fromValue(lpRecherche));
			if(lpRecherche->description())
				lpItems[i]->setToolTip(lpRecherche->description()->toPlainText());
		}

		lpModel->appendRow(lpItems);
		lpRecherche->setItem(lpItems);
	}

	lpView->header()->setStretchLastSection(true);

	lpView->expandAll();

	for(int i = 0;i < headerLabels.count();i++)
		lpView->resizeColumnToContents(i);

	return(true);
}
