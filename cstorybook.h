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
	 \param parent
	*/
	explicit cStoryBook(QObject *parent = nullptr);
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

	 \fn save
	 \return bool
	*/
	bool			save();
	/*!
	 \brief

	 \fn saveAs
	 \param szProject
	 \return bool
	*/
	bool			saveAs(const QString& szProject);

	/*!
	 \brief

	 \fn printPdf
	 \param szFileName
	 \return bool
	*/
	bool			printPdf(const QString& szFileName);

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

	 \fn project
	 \return QString
	*/
	QString			project();
	/*!
	 \brief

	 \fn book
	 \return cBook
	*/
	cBook*			book();
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
	/*!
	 \brief

	 \fn characterList
	 \return cCharacterList
	*/
	cCharacterList*	characterList();
	/*!
	 \brief

	 \fn placeList
	 \return cPlaceList
	*/
	cPlaceList*		placeList();
	/*!
	 \brief

	 \fn objectList
	 \return cObjectList
	*/
	cObjectList*	objectList();

	/*!
	 \brief

	 \fn addPart
	 \param szPartName
	 \return bool
	*/
	bool			addPart(const QString& szPartName);

	/*!
	 \brief

	 \fn addChapter
	 \param lpPart
	 \param szChapterName
	 \return bool
	*/
	bool			addChapter(cPart* lpPart, const QString& szChapterName);

	/*!
	 \brief

	 \fn addScene
	 \param lpChapter
	 \param szSceneName
	 \return bool
	*/
	bool			addScene(cChapter* lpChapter, const QString& szSceneName);

	/*!
	 \brief

	 \fn addCharacter
	 \param szCharacterName
	 \return bool
	*/
	bool			addCharacter(const QString& szCharacterName);

	/*!
	 \brief

	 \fn addPlace
	 \param szPlaceName
	 \return bool
	*/
	bool			addPlace(const QString& szPlaceName);

	/*!
	 \brief

	 \fn addObject
	 \param szObjectName
	 \return bool
	*/
	bool			addObject(const QString& szObjectName);

	/*!
	 \brief

	 \fn addRecherche
	 \param szRechercheName
	 \return bool
	*/
	bool			addRecherche(const QString& szRechercheName);

	/*!
	 \brief

	 \fn hasChapter
	 \param lpPart
	 \return bool
	*/
	bool			hasChapter(cPart* lpPart);

	/*!
	 \brief

	 \fn cChapter
	 \param lpChapter
	 \return bool
	*/
	bool			hasScene(cChapter* lpChapter);

	/*!
	 \brief

	 \fn characterInUse
	 \param lpCharacter
	 \return bool
	*/
	bool			characterInUse(cCharacter* lpCharacter);

	/*!
	 \brief

	 \fn placeInUse
	 \param lpPlace
	 \return bool
	*/
	bool			placeInUse(cPlace* lpPlace);

	/*!
	 \brief

	 \fn objectInUse
	 \param lpObject
	 \return bool
	*/
	bool			objectInUse(cObject* lpObject);

	/*!
	 \brief

	 \fn rechercheInUse
	 \param lpRecherche
	 \return bool
	*/
	bool			rechercheInUse(cRecherche* lpRecherche);

private:
	QString			m_szProject;				/*!< TODO: describe */
	bool			m_bIsOpen;					/*!< TODO: describe */
	QSqlDatabase	m_db;						/*!< TODO: describe */
	cBook			m_book;						/*!< TODO: describe */
	cPartList		m_partList;					/*!< TODO: describe */
	cChapterList	m_chapterList;				/*!< TODO: describe */
	cSceneList		m_sceneList;				/*!< TODO: describe */
	cCharacterList	m_characterList;			/*!< TODO: describe */
	cPlaceList		m_placeList;				/*!< TODO: describe */
	cObjectList		m_objectList;				/*!< TODO: describe */
	cRechercheList	m_rechercheList;			/*!< TODO: describe */

	bool			m_bPrintTitle;				/*!< TODO: describe */
	QString			m_szTitleFont;				/*!< TODO: describe */
	qint16			m_iTitleFontSize;			/*!< TODO: describe */
	bool			m_bTitleBold;				/*!< TODO: describe */
	bool			m_bTitleItalic;				/*!< TODO: describe */
	bool			m_bTitleUnderline;			/*!< TODO: describe */
	qint16			m_iTitleAlign;				/*!< TODO: describe */
	bool			m_bPrintSubTitle;			/*!< TODO: describe */
	QString			m_szSubtitleFont;			/*!< TODO: describe */
	qint16			m_iSubtitleFontSize;		/*!< TODO: describe */
	bool			m_bSubtitleBold;			/*!< TODO: describe */
	bool			m_bSubtitleItalic;			/*!< TODO: describe */
	bool			m_bSubtitleUnderline;		/*!< TODO: describe */
	qint16			m_iSubtitleAlign;			/*!< TODO: describe */
	bool			m_bPrintShortDescription;	/*!< TODO: describe */
	bool			m_bPrintDescription;		/*!< TODO: describe */
	bool			m_bPrintAuthor;				/*!< TODO: describe */
	QString			m_szAuthorFont;				/*!< TODO: describe */
	qint16			m_iAuthorFontSize;			/*!< TODO: describe */
	bool			m_bAuthorBold;				/*!< TODO: describe */
	bool			m_bAuthorItalic;			/*!< TODO: describe */
	bool			m_bAuthorUnderline;			/*!< TODO: describe */
	qint16			m_iAuthorAlign;				/*!< TODO: describe */
	bool			m_bPrintPartName;			/*!< TODO: describe */
	QString			m_szPartFont;				/*!< TODO: describe */
	qint16			m_iPartFontSize;			/*!< TODO: describe */
	bool			m_bPartBold;				/*!< TODO: describe */
	bool			m_bPartItalic;				/*!< TODO: describe */
	bool			m_bPartUnderline;			/*!< TODO: describe */
	qint16			m_iPartAlign;				/*!< TODO: describe */
	bool			m_bPrintPartDescription;	/*!< TODO: describe */
	bool			m_bPrintPartText;			/*!< TODO: describe */
	bool			m_bPrintChapterName;		/*!< TODO: describe */
	QString			m_szChapterFont;			/*!< TODO: describe */
	qint16			m_iChapterFontSize;			/*!< TODO: describe */
	bool			m_bChapterBold;				/*!< TODO: describe */
	bool			m_bChapterItalic;			/*!< TODO: describe */
	bool			m_bChapterUnderline;		/*!< TODO: describe */
	qint16			m_iChapterAlign;			/*!< TODO: describe */
	bool			m_bPrintChapterDescription;	/*!< TODO: describe */
	bool			m_bPrintChapterText;		/*!< TODO: describe */
	bool			m_bPrintSceneName;			/*!< TODO: describe */
	QString			m_szSceneFont;				/*!< TODO: describe */
	qint16			m_iSceneFontSize;			/*!< TODO: describe */
	bool			m_bSceneBold;				/*!< TODO: describe */
	bool			m_bSceneItalic;				/*!< TODO: describe */
	bool			m_bSceneUnderline;			/*!< TODO: describe */
	qint16			m_iSceneAlign;				/*!< TODO: describe */
	bool			m_bPrintSceneDescription;	/*!< TODO: describe */
	bool			m_bPrintSceneText;			/*!< TODO: describe */
	QString			m_szPaperSize;				/*!< TODO: describe */
	qint16			m_iPaperOrientation;		/*!< TODO: describe */
	qreal			m_dLeftMargin;				/*!< TODO: describe */
	qreal			m_dRightMargin;				/*!< TODO: describe */
	qreal			m_dTopMargin;				/*!< TODO: describe */
	qreal			m_dBottomMargin;			/*!< TODO: describe */
	qint16			m_iUnit;					/*!< TODO: describe */

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

	 \fn loadConfig
	 \return bool
	*/
	bool			loadConfig();

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

	 \fn saveConfig
	 \return bool
	*/
	bool			saveConfig();

	/*!
	 \brief

	 \fn saveBook
	 \return bool
	*/
	bool			saveBook();
	/*!
	 \brief

	 \fn savePartList
	 \return bool
	*/
	bool			savePartList();
	/*!
	 \brief

	 \fn saveChapterList
	 \return bool
	*/
	bool			saveChapterList();
	/*!
	 \brief

	 \fn saveSceneList
	 \return bool
	*/
	bool			saveSceneList();
	/*!
	 \brief

	 \fn saveCharacterList
	 \return bool
	*/
	bool			saveCharacterList();
	/*!
	 \brief

	 \fn savePlaceList
	 \return bool
	*/
	bool			savePlaceList();
	/*!
	 \brief

	 \fn saveObjectList
	 \return bool
	*/
	bool			saveObjectList();
	/*!
	 \brief

	 \fn saveRechercheList
	 \return bool
	*/
	bool			saveRechercheList();
	/*!
	 \brief

	 \fn saveImageList
	 \return bool
	*/
	bool			saveImageList();
};

#endif // CSTORYBOOK_H
