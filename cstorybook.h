/*!
 \file cstorybook.h

*/

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


/*!
 \brief

 \class cStoryBook cstorybook.h "cstorybook.h"
*/
class cStoryBook : public QObject
{
	Q_OBJECT
public:
	/*!
	 \brief

	 \fn cStoryBook
	 \param szProject
	 \param parent
	*/
	explicit cStoryBook(const QString& szProject, QObject *parent = nullptr);
	/*!
	 \brief

	 \fn ~cStoryBook
	*/
	~cStoryBook();

	/*!
	 \brief

	 \fn openDatabase
	 \return bool
	*/
	bool			openDatabase();
	/*!
	 \brief

	 \fn verify
	 \return bool
	*/
	bool			verify();

	/*!
	 \brief

	 \fn title
	 \return QString
	*/
	QString			title();
	/*!
	 \brief

	 \fn author
	 \return QString
	*/
	QString			author();

	/*!
	 \brief

	 \fn fillOutlineList
	 \param lpView
	 \return bool
	*/
	bool			fillOutlineList(QTreeView* lpView);
	/*!
	 \brief

	 \fn fillCharacterList
	 \param lpView
	 \return bool
	*/
	bool			fillCharacterList(QTreeView* lpView);
	/*!
	 \brief

	 \fn fillPlaceList
	 \param lpView
	 \return bool
	*/
	bool			fillPlaceList(QTreeView* lpView);
	/*!
	 \brief

	 \fn fillObjectList
	 \param lpView
	 \return bool
	*/
	bool			fillObjectList(QTreeView* lpView);
	/*!
	 \brief

	 \fn fillRechercheList
	 \param lpView
	 \return bool
	*/
	bool			fillRechercheList(QTreeView* lpView);

	/*!
	 \brief

	 \fn chapterList
	 \return cChapterList
	*/
	cChapterList*	chapterList();
	/*!
	 \brief

	 \fn sceneList
	 \return cSceneList
	*/
	cSceneList*		sceneList();
private:
	QString			m_szProject; /*!< TODO: describe */
	bool			m_bIsOpen; /*!< TODO: describe */
	QSqlDatabase	m_db; /*!< TODO: describe */
	cBook			m_book; /*!< TODO: describe */
	cPartList		m_partList; /*!< TODO: describe */
	cChapterList	m_chapterList; /*!< TODO: describe */
	cSceneList		m_sceneList; /*!< TODO: describe */
	cCharacterList	m_characterList; /*!< TODO: describe */
	cPlaceList		m_placeList; /*!< TODO: describe */
	cObjectList		m_objectList; /*!< TODO: describe */
	cRechercheList	m_rechercheList; /*!< TODO: describe */
	cImageList		m_imageList; /*!< TODO: describe */

	/*!
	 \brief

	 \fn createDatabase
	 \return bool
	*/
	bool			createDatabase();
	/*!
	 \brief

	 \fn updateDatabase
	 \return bool
	*/
	bool			updateDatabase();
	/*!
	 \brief

	 \fn createTable
	 \param szSQL
	 \return bool
	*/
	bool			createTable(const QString& szSQL);

	/*!
	 \brief

	 \fn loadBook
	 \return bool
	*/
	bool			loadBook();
	/*!
	 \brief

	 \fn loadPartList
	 \return bool
	*/
	bool			loadPartList();
	/*!
	 \brief

	 \fn loadChapterList
	 \return bool
	*/
	bool			loadChapterList();
	/*!
	 \brief

	 \fn loadSceneList
	 \return bool
	*/
	bool			loadSceneList();
	/*!
	 \brief

	 \fn loadCharacterList
	 \return bool
	*/
	bool			loadCharacterList();
	/*!
	 \brief

	 \fn loadPlaceList
	 \return bool
	*/
	bool			loadPlaceList();
	/*!
	 \brief

	 \fn loadObjectList
	 \return bool
	*/
	bool			loadObjectList();
	/*!
	 \brief

	 \fn loadRechercheList
	 \return bool
	*/
	bool			loadRechercheList();
	/*!
	 \brief

	 \fn loadImageList
	 \return bool
	*/
	bool			loadImageList();
};

#endif // CSTORYBOOK_H
