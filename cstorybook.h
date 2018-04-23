#ifndef CSTORYBOOK_H
#define CSTORYBOOK_H


#include "cbook.h"
#include "cpart.h"
#include "cchapter.h"
#include "cscene.h"
#include "ccharacter.h"
#include "cplace.h"
#include "cobject.h"
#include "crecherche.h"
#include "cimage.h"

#include <QString>
#include <QObject>

#include <QTreeView>
#include <QStandardItemModel>

#include <QSqlDatabase>


class cStoryBook : public QObject
{
	Q_OBJECT
public:
	explicit cStoryBook(const QString& szProject, QObject *parent = nullptr);
	~cStoryBook();

	bool			openDatabase();
	bool			verify();

	QString			title();
	QString			author();

	bool			fillOutlineList(QTreeView* lpView);
	bool			fillCharacterList(QTreeView* lpView);
	bool			fillPlaceList(QTreeView* lpView);
	bool			fillObjectList(QTreeView* lpView);
	bool			fillRechercheList(QTreeView* lpView);

private:
	QString			m_szProject;
	bool			m_bIsOpen;
	QSqlDatabase	m_db;
	cBook			m_book;
	cPartList		m_partList;
	cChapterList	m_chapterList;
	cSceneList		m_sceneList;
	cCharacterList	m_characterList;
	cPlaceList		m_placeList;
	cObjectList		m_objectList;
	cRechercheList	m_rechercheList;
	cImageList		m_imageList;

	bool			createDatabase();
	bool			updateDatabase();
	bool			createTable(const QString& szSQL);

	bool			loadBook();
	bool			loadPartList();
	bool			loadChapterList();
	bool			loadSceneList();
	bool			loadCharacterList();
	bool			loadPlaceList();
	bool			loadObjectList();
	bool			loadRechercheList();
	bool			loadImageList();
};

#endif // CSTORYBOOK_H
