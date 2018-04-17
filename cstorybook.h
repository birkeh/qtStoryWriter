#ifndef CSTORYBOOK_H
#define CSTORYBOOK_H


#include "cbook.h"
#include "cpart.h"
#include "cchapter.h"
#include "cscene.h"

#include <QString>

#include <QStandardItemModel>

#include <QSqlDatabase>


class cStoryBook
{
public:
	cStoryBook(const QString& szProjectPath);
	~cStoryBook();

	bool			openDatabase();
	bool			verify();

	QString			title();
	QString			author();

	bool			fillOutlineList(QStandardItemModel* lpModel);
private:
	QString			m_szProjectPath;
	bool			m_bIsOpen;
	QSqlDatabase	m_db;
	cBook			m_book;
	cPartList		m_partList;
	cChapterList	m_chapterList;
	cSceneList		m_sceneList;

	bool			createDatabase();
	bool			updateDatabase();
	bool			createTable(const QString& szSQL);

	bool			loadBook();
	bool			loadPartList();
	bool			loadChapterList();
	bool			loadSceneList();
};

#endif // CSTORYBOOK_H
