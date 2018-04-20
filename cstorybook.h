#ifndef CSTORYBOOK_H
#define CSTORYBOOK_H


#include "cbook.h"
#include "cpart.h"
#include "cchapter.h"
#include "cscene.h"
#include "ccharacter.h"

#include <QString>
#include <QObject>

#include <QTreeView>
#include <QStandardItemModel>

#include <QSqlDatabase>


class cStoryBook : public QObject
{
	Q_OBJECT
public:
	explicit cStoryBook(const QString& szProjectPath, QObject *parent = nullptr);
	~cStoryBook();

	bool			openDatabase();
	bool			verify();

	QString			title();
	QString			author();

	bool			fillOutlineList(QTreeView* lpView);
	bool			fillCharacterList(QTreeView* lpView);
private:
	QString			m_szProjectPath;
	bool			m_bIsOpen;
	QSqlDatabase	m_db;
	cBook			m_book;
	cPartList		m_partList;
	cChapterList	m_chapterList;
	cSceneList		m_sceneList;
	cCharacterList	m_characterList;

	bool			createDatabase();
	bool			updateDatabase();
	bool			createTable(const QString& szSQL);

	bool			loadBook();
	bool			loadPartList();
	bool			loadChapterList();
	bool			loadSceneList();
	bool			loadCharacterList();
};

#endif // CSTORYBOOK_H
