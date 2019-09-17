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
#include "common.h"

#include <QString>
#include <QObject>

#include <QTreeView>
#include <QStandardItemModel>

#include <QSqlDatabase>

#include <QPrinter>
#include <QPagedPaintDevice>


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
	bool						save();
	/*!
	 \brief

	 \fn saveAs
	 \param szProject
	 \return bool
	*/
	bool						saveAs(const QString& szProject);

	/*!
	 \brief

	 \fn printPdf
	 \param szFileName
	 \return bool
	*/
	bool						printPdf(const QString& szFileName);

	/*!
	 \brief

	 \fn openDatabase
	 \return bool
	*/
	bool						openDatabase();
	/*!
	 \brief

	 \fn verify
	 \return bool
	*/
	bool						verify();

	/*!
	 \brief

	 \fn title
	 \return QString
	*/
	QString						title();
	/*!
	 \brief

	 \fn author
	 \return QString
	*/
	QString						author();

	/*!
	 \brief

	 \fn fillOutlineList
	 \param lpView
	 \return bool
	*/
	bool						fillOutlineList(QTreeView* lpView);
	/*!
	 \brief

	 \fn fillCharacterList
	 \param lpView
	 \return bool
	*/
	bool						fillCharacterList(QTreeView* lpView);
	/*!
	 \brief

	 \fn fillPlaceList
	 \param lpView
	 \return bool
	*/
	bool						fillPlaceList(QTreeView* lpView);
	/*!
	 \brief

	 \fn fillObjectList
	 \param lpView
	 \return bool
	*/
	bool						fillObjectList(QTreeView* lpView);
	/*!
	 \brief

	 \fn fillRechercheList
	 \param lpView
	 \return bool
	*/
	bool						fillRechercheList(QTreeView* lpView);

	/*!
	 \brief

	 \fn project
	 \return QString
	*/
	QString						project();
	/*!
	 \brief

	 \fn book
	 \return cBook
	*/
	cBook*						book();
	/*!
	 \brief

	 \fn chapterList
	 \return cChapterList
	*/
	cChapterList*				chapterList();
	/*!
	 \brief

	 \fn sceneList
	 \return cSceneList
	*/
	cSceneList*					sceneList();
	/*!
	 \brief

	 \fn characterList
	 \return cCharacterList
	*/
	cCharacterList*				characterList();
	/*!
	 \brief

	 \fn placeList
	 \return cPlaceList
	*/
	cPlaceList*					placeList();
	/*!
	 \brief

	 \fn objectList
	 \return cObjectList
	*/
	cObjectList*				objectList();

	/*!
	 \brief

	 \fn addPart
	 \param szPartName
	 \return bool
	*/
	bool						addPart(const QString& szPartName);

	/*!
	 \brief

	 \fn addChapter
	 \param lpPart
	 \param szChapterName
	 \return bool
	*/
	bool						addChapter(cPart* lpPart, const QString& szChapterName);

	/*!
	 \brief

	 \fn addScene
	 \param lpChapter
	 \param szSceneName
	 \return bool
	*/
	bool						addScene(cChapter* lpChapter, const QString& szSceneName);

	/*!
	 \brief

	 \fn addCharacter
	 \param szCharacterName
	 \return bool
	*/
	bool						addCharacter(const QString& szCharacterName);

	/*!
	 \brief

	 \fn addPlace
	 \param szPlaceName
	 \return bool
	*/
	bool						addPlace(const QString& szPlaceName);

	/*!
	 \brief

	 \fn addObject
	 \param szObjectName
	 \return bool
	*/
	bool						addObject(const QString& szObjectName);

	/*!
	 \brief

	 \fn addRecherche
	 \param szRechercheName
	 \return bool
	*/
	bool						addRecherche(const QString& szRechercheName);

	/*!
	 \brief

	 \fn hasChapter
	 \param lpPart
	 \return bool
	*/
	bool						hasChapter(cPart* lpPart);

	/*!
	 \brief

	 \fn cChapter
	 \param lpChapter
	 \return bool
	*/
	bool						hasScene(cChapter* lpChapter);

	/*!
	 \brief

	 \fn characterInUse
	 \param lpCharacter
	 \return bool
	*/
	bool						characterInUse(cCharacter* lpCharacter);

	/*!
	 \brief

	 \fn placeInUse
	 \param lpPlace
	 \return bool
	*/
	bool						placeInUse(cPlace* lpPlace);

	/*!
	 \brief

	 \fn objectInUse
	 \param lpObject
	 \return bool
	*/
	bool						objectInUse(cObject* lpObject);

	/*!
	 \brief

	 \fn rechercheInUse
	 \param lpRecherche
	 \return bool
	*/
	bool						rechercheInUse(cRecherche* lpRecherche);

	bool						printTitle();
	/*!
	 \brief

	 \fn setPrintTitle
	 \param value
	*/
	void						setPrintTitle(const bool& value);

	/*!
	 \brief

	 \fn titleFont
	 \return QString
	*/
	QString						titleFont();
	/*!
	 \brief

	 \fn setTitleFont
	 \param value
	*/
	void						setTitleFont(const QString& value);

	/*!
	 \brief

	 \fn titleFontSize
	 \return qint16
	*/
	qint16						titleFontSize();
	/*!
	 \brief

	 \fn setTitleFontSize
	 \param value
	*/
	void						setTitleFontSize(const qint16& value);

	/*!
	 \brief

	 \fn titleBold
	 \return bool
	*/
	bool						titleBold();
	/*!
	 \brief

	 \fn setTitleBold
	 \param value
	*/
	void						setTitleBold(const bool& value);

	/*!
	 \brief

	 \fn titleItalic
	 \return bool
	*/
	bool						titleItalic();
	/*!
	 \brief

	 \fn setTitleItalic
	 \param value
	*/
	void						setTitleItalic(const bool& value);

	/*!
	 \brief

	 \fn titleUnderline
	 \return bool
	*/
	bool						titleUnderline();
	/*!
	 \brief

	 \fn setTitleUnderline
	 \param value
	*/
	void						setTitleUnderline(const bool& value);

	/*!
	 \brief

	 \fn titleAlign
	 \return ALIGN
	*/
	ALIGN						titleAlign();
	/*!
	 \brief

	 \fn setTitleAlign
	 \param value
	*/
	void						setTitleAlign(const ALIGN& value);

	/*!
	 \brief

	 \fn printSubTitle
	 \return bool
	*/
	bool						printSubTitle();
	/*!
	 \brief

	 \fn setPrintSubTitle
	 \param value
	*/
	void						setPrintSubTitle(const bool& value);

	/*!
	 \brief

	 \fn subtitleFont
	 \return QString
	*/
	QString						subtitleFont();
	/*!
	 \brief

	 \fn setSubtitleFont
	 \param value
	*/
	void						setSubtitleFont(const QString& value);

	/*!
	 \brief

	 \fn subtitleFontSize
	 \return qint16
	*/
	qint16						subtitleFontSize();
	/*!
	 \brief

	 \fn setSubtitleFontSize
	 \param value
	*/
	void						setSubtitleFontSize(const qint16& value);

	/*!
	 \brief

	 \fn subtitleBold
	 \return bool
	*/
	bool						subtitleBold();
	/*!
	 \brief

	 \fn setSubtitleBold
	 \param value
	*/
	void						setSubtitleBold(const bool& value);

	/*!
	 \brief

	 \fn subtitleItalic
	 \return bool
	*/
	bool						subtitleItalic();
	/*!
	 \brief

	 \fn setSubtitleItalic
	 \param value
	*/
	void						setSubtitleItalic(const bool& value);

	/*!
	 \brief

	 \fn subtitleUnderline
	 \return bool
	*/
	bool						subtitleUnderline();
	/*!
	 \brief

	 \fn setSubtitleUnderline
	 \param value
	*/
	void						setSubtitleUnderline(const bool& value);

	/*!
	 \brief

	 \fn subtitleAlign
	 \return ALIGN
	*/
	ALIGN						subtitleAlign();
	/*!
	 \brief

	 \fn setSubtitleAlign
	 \param value
	*/
	void						setSubtitleAlign(const ALIGN& value);

	/*!
	 \brief

	 \fn printShortDescription
	 \return bool
	*/
	bool						printShortDescription();
	/*!
	 \brief

	 \fn setPrintShortDescription
	 \param value
	*/
	void						setPrintShortDescription(const bool& value);

	/*!
	 \brief

	 \fn printDescription
	 \return bool
	*/
	bool						printDescription();
	/*!
	 \brief

	 \fn setPrintDescription
	 \param value
	*/
	void						setPrintDescription(const bool& value);

	/*!
	 \brief

	 \fn printAuthor
	 \return bool
	*/
	bool						printAuthor();
	/*!
	 \brief

	 \fn setPrintAuthor
	 \param value
	*/
	void						setPrintAuthor(const bool& value);

	/*!
	 \brief

	 \fn authorFont
	 \return QString
	*/
	QString						authorFont();
	/*!
	 \brief

	 \fn setAuthorFont
	 \param value
	*/
	void						setAuthorFont(const QString& value);

	/*!
	 \brief

	 \fn authorFontSize
	 \return qint16
	*/
	qint16						authorFontSize();
	/*!
	 \brief

	 \fn setAuthorFontSize
	 \param value
	*/
	void						setAuthorFontSize(const qint16& value);

	/*!
	 \brief

	 \fn authorBold
	 \return bool
	*/
	bool						authorBold();
	/*!
	 \brief

	 \fn setAuthorBold
	 \param value
	*/
	void						setAuthorBold(const bool& value);

	/*!
	 \brief

	 \fn authorItalic
	 \return bool
	*/
	bool						authorItalic();
	/*!
	 \brief

	 \fn setAuthorItalic
	 \param value
	*/
	void						setAuthorItalic(const bool& value);

	/*!
	 \brief

	 \fn authorUnderline
	 \return bool
	*/
	bool						authorUnderline();
	/*!
	 \brief

	 \fn setAuthorUnderline
	 \param value
	*/
	void						setAuthorUnderline(const bool& value);

	/*!
	 \brief

	 \fn authorAlign
	 \return ALIGN
	*/
	ALIGN						authorAlign();
	/*!
	 \brief

	 \fn setAuthorAlign
	 \param value
	*/
	void						setAuthorAlign(const ALIGN& value);

	/*!
	 \brief

	 \fn printPartName
	 \return bool
	*/
	bool						printPartName();
	/*!
	 \brief

	 \fn setPrintPartName
	 \param value
	*/
	void						setPrintPartName(const bool& value);

	/*!
	 \brief

	 \fn partFont
	 \return QString
	*/
	QString						partFont();
	/*!
	 \brief

	 \fn setPartFont
	 \param value
	*/
	void						setPartFont(const QString& value);

	/*!
	 \brief

	 \fn partFontSize
	 \return qint16
	*/
	qint16						partFontSize();
	/*!
	 \brief

	 \fn setPartFontSize
	 \param value
	*/
	void						setPartFontSize(const qint16& value);

	/*!
	 \brief

	 \fn partBold
	 \return bool
	*/
	bool						partBold();
	/*!
	 \brief

	 \fn setPartBold
	 \param value
	*/
	void						setPartBold(const bool& value);

	/*!
	 \brief

	 \fn partItalic
	 \return bool
	*/
	bool						partItalic();
	/*!
	 \brief

	 \fn setPartItalic
	 \param value
	*/
	void						setPartItalic(const bool& value);

	/*!
	 \brief

	 \fn partUnderline
	 \return bool
	*/
	bool						partUnderline();
	/*!
	 \brief

	 \fn setPartUnderline
	 \param value
	*/
	void						setPartUnderline(const bool& value);

	/*!
	 \brief

	 \fn partAlign
	 \return ALIGN
	*/
	ALIGN						partAlign();
	/*!
	 \brief

	 \fn setPartAlign
	 \param value
	*/
	void						setPartAlign(const ALIGN& value);

	/*!
	 \brief

	 \fn printPartDescription
	 \return bool
	*/
	bool						printPartDescription();
	/*!
	 \brief

	 \fn setPrintPartDescription
	 \param value
	*/
	void						setPrintPartDescription(const bool& value);

	/*!
	 \brief

	 \fn printPartText
	 \return bool
	*/
	bool						printPartText();
	/*!
	 \brief

	 \fn setPrintPartText
	 \param value
	*/
	void						setPrintPartText(const bool& value);

	/*!
	 \brief

	 \fn printChapterName
	 \return bool
	*/
	bool						printChapterName();
	/*!
	 \brief

	 \fn setPrintChapterName
	 \param value
	*/
	void						setPrintChapterName(const bool& value);

	/*!
	 \brief

	 \fn chapterFont
	 \return QString
	*/
	QString						chapterFont();
	/*!
	 \brief

	 \fn setChapterFont
	 \param value
	*/
	void						setChapterFont(const QString& value);

	/*!
	 \brief

	 \fn chapterFontSize
	 \return qint16
	*/
	qint16						chapterFontSize();
	/*!
	 \brief

	 \fn setChapterFontSize
	 \param value
	*/
	void						setChapterFontSize(const qint16& value);

	/*!
	 \brief

	 \fn chapterBold
	 \return bool
	*/
	bool						chapterBold();
	/*!
	 \brief

	 \fn setChapterBold
	 \param value
	*/
	void						setChapterBold(const bool& value);

	/*!
	 \brief

	 \fn chapterItalic
	 \return bool
	*/
	bool						chapterItalic();
	/*!
	 \brief

	 \fn setChapterItalic
	 \param value
	*/
	void						setChapterItalic(const bool& value);

	/*!
	 \brief

	 \fn chapterUnderline
	 \return bool
	*/
	bool						chapterUnderline();
	/*!
	 \brief

	 \fn setChapterUnderline
	 \param value
	*/
	void						setChapterUnderline(const bool& value);

	/*!
	 \brief

	 \fn chapterAlign
	 \return ALIGN
	*/
	ALIGN						chapterAlign();
	/*!
	 \brief

	 \fn setChapterAlign
	 \param value
	*/
	void						setChapterAlign(const ALIGN& value);

	/*!
	 \brief

	 \fn printChapterDescription
	 \return bool
	*/
	bool						printChapterDescription();
	/*!
	 \brief

	 \fn setPrintChapterDescription
	 \param value
	*/
	void						setPrintChapterDescription(const bool& value);

	/*!
	 \brief

	 \fn printChapterText
	 \return bool
	*/
	bool						printChapterText();
	/*!
	 \brief

	 \fn setPrintChapterText
	 \param value
	*/
	void						setPrintChapterText(const bool& value);

	/*!
	 \brief

	 \fn printSceneName
	 \return bool
	*/
	bool						printSceneName();
	/*!
	 \brief

	 \fn setPrintSceneName
	 \param value
	*/
	void						setPrintSceneName(const bool& value);

	/*!
	 \brief

	 \fn sceneFont
	 \return QString
	*/
	QString						sceneFont();
	/*!
	 \brief

	 \fn setSceneFont
	 \param value
	*/
	void						setSceneFont(const QString& value);

	/*!
	 \brief

	 \fn sceneFontSize
	 \return qint16
	*/
	qint16						sceneFontSize();
	/*!
	 \brief

	 \fn setSceneFontSize
	 \param value
	*/
	void						setSceneFontSize(const qint16& value);

	/*!
	 \brief

	 \fn sceneBold
	 \return bool
	*/
	bool						sceneBold();
	/*!
	 \brief

	 \fn setSceneBold
	 \param value
	*/
	void						setSceneBold(const bool& value);

	/*!
	 \brief

	 \fn sceneItalic
	 \return bool
	*/
	bool						sceneItalic();
	/*!
	 \brief

	 \fn setSceneItalic
	 \param value
	*/
	void						setSceneItalic(const bool& value);

	/*!
	 \brief

	 \fn sceneUnderline
	 \return bool
	*/
	bool						sceneUnderline();
	/*!
	 \brief

	 \fn setSceneUnderline
	 \param value
	*/
	void						setSceneUnderline(const bool& value);

	/*!
	 \brief

	 \fn sceneAlign
	 \return ALIGN
	*/
	ALIGN						sceneAlign();
	/*!
	 \brief

	 \fn setSceneAlign
	 \param value
	*/
	void						setSceneAlign(const ALIGN& value);

	/*!
	 \brief

	 \fn printSceneDescription
	 \return bool
	*/
	bool						printSceneDescription();
	/*!
	 \brief

	 \fn setPrintSceneDescription
	 \param value
	*/
	void						setPrintSceneDescription(const bool& value);

	/*!
	 \brief

	 \fn printSceneText
	 \return bool
	*/
	bool						printSceneText();
	/*!
	 \brief

	 \fn setPrintSceneText
	 \param value
	*/
	void						setPrintSceneText(const bool& value);

	/*!
	 \brief

	 \fn paperSize
	 \return QPagedPaintDevice::PageSize
	*/
	QPagedPaintDevice::PageSize	paperSize();
	/*!
	 \brief

	 \fn setPaperSize
	 \param value
	*/
	void						setPaperSize(const QPagedPaintDevice::PageSize& value);

	/*!
	 \brief

	 \fn paperOrientation
	 \return QPrinter::Orientation
	*/
	QPrinter::Orientation		paperOrientation();
	/*!
	 \brief

	 \fn setPaperOrientation
	 \param value
	*/
	void						setPaperOrientation(const QPrinter::Orientation& value);

	/*!
	 \brief

	 \fn leftMargin
	 \return qreal
	*/
	qreal						leftMargin();
	/*!
	 \brief

	 \fn setLeftMargin
	 \param value
	*/
	void						setLeftMargin(const qreal& value);

	/*!
	 \brief

	 \fn rightMargin
	 \return qreal
	*/
	qreal						rightMargin();
	/*!
	 \brief

	 \fn setRightMargin
	 \param value
	*/
	void						setRightMargin(const qreal& value);

	/*!
	 \brief

	 \fn topMargin
	 \return qreal
	*/
	qreal						topMargin();
	/*!
	 \brief

	 \fn setTopMargin
	 \param value
	*/
	void						setTopMargin(const qreal& value);

	/*!
	 \brief

	 \fn bottomMargin
	 \return qreal
	*/
	qreal						bottomMargin();
	/*!
	 \brief

	 \fn setBottomMargin
	 \param value
	*/
	void						setBottomMargin(const qreal& value);

	/*!
	 \brief

	 \fn unit
	 \return QPageLayout::Unit
	*/
	QPageLayout::Unit			unit();
	/*!
	 \brief

	 \fn setUnit
	 \param value
	*/
	void						setUnit(const QPageLayout::Unit& value);

private:
	QString						m_szProject;				/*!< TODO: describe */
	bool						m_bIsOpen;					/*!< TODO: describe */
	QSqlDatabase				m_db;						/*!< TODO: describe */
	cBook						m_book;						/*!< TODO: describe */
	cPartList					m_partList;					/*!< TODO: describe */
	cChapterList				m_chapterList;				/*!< TODO: describe */
	cSceneList					m_sceneList;				/*!< TODO: describe */
	cCharacterList				m_characterList;			/*!< TODO: describe */
	cPlaceList					m_placeList;				/*!< TODO: describe */
	cObjectList					m_objectList;				/*!< TODO: describe */
	cRechercheList				m_rechercheList;			/*!< TODO: describe */

	bool						m_bPrintTitle;				/*!< TODO: describe */
	QString						m_szTitleFont;				/*!< TODO: describe */
	qint16						m_iTitleFontSize;			/*!< TODO: describe */
	bool						m_bTitleBold;				/*!< TODO: describe */
	bool						m_bTitleItalic;				/*!< TODO: describe */
	bool						m_bTitleUnderline;			/*!< TODO: describe */
	ALIGN						m_iTitleAlign;				/*!< TODO: describe */
	bool						m_bPrintSubTitle;			/*!< TODO: describe */
	QString						m_szSubtitleFont;			/*!< TODO: describe */
	qint16						m_iSubtitleFontSize;		/*!< TODO: describe */
	bool						m_bSubtitleBold;			/*!< TODO: describe */
	bool						m_bSubtitleItalic;			/*!< TODO: describe */
	bool						m_bSubtitleUnderline;		/*!< TODO: describe */
	ALIGN						m_iSubtitleAlign;			/*!< TODO: describe */
	bool						m_bPrintShortDescription;	/*!< TODO: describe */
	bool						m_bPrintDescription;		/*!< TODO: describe */
	bool						m_bPrintAuthor;				/*!< TODO: describe */
	QString						m_szAuthorFont;				/*!< TODO: describe */
	qint16						m_iAuthorFontSize;			/*!< TODO: describe */
	bool						m_bAuthorBold;				/*!< TODO: describe */
	bool						m_bAuthorItalic;			/*!< TODO: describe */
	bool						m_bAuthorUnderline;			/*!< TODO: describe */
	ALIGN						m_iAuthorAlign;				/*!< TODO: describe */
	bool						m_bPrintPartName;			/*!< TODO: describe */
	QString						m_szPartFont;				/*!< TODO: describe */
	qint16						m_iPartFontSize;			/*!< TODO: describe */
	bool						m_bPartBold;				/*!< TODO: describe */
	bool						m_bPartItalic;				/*!< TODO: describe */
	bool						m_bPartUnderline;			/*!< TODO: describe */
	ALIGN						m_iPartAlign;				/*!< TODO: describe */
	bool						m_bPrintPartDescription;	/*!< TODO: describe */
	bool						m_bPrintPartText;			/*!< TODO: describe */
	bool						m_bPrintChapterName;		/*!< TODO: describe */
	QString						m_szChapterFont;			/*!< TODO: describe */
	qint16						m_iChapterFontSize;			/*!< TODO: describe */
	bool						m_bChapterBold;				/*!< TODO: describe */
	bool						m_bChapterItalic;			/*!< TODO: describe */
	bool						m_bChapterUnderline;		/*!< TODO: describe */
	ALIGN						m_iChapterAlign;			/*!< TODO: describe */
	bool						m_bPrintChapterDescription;	/*!< TODO: describe */
	bool						m_bPrintChapterText;		/*!< TODO: describe */
	bool						m_bPrintSceneName;			/*!< TODO: describe */
	QString						m_szSceneFont;				/*!< TODO: describe */
	qint16						m_iSceneFontSize;			/*!< TODO: describe */
	bool						m_bSceneBold;				/*!< TODO: describe */
	bool						m_bSceneItalic;				/*!< TODO: describe */
	bool						m_bSceneUnderline;			/*!< TODO: describe */
	ALIGN						m_iSceneAlign;				/*!< TODO: describe */
	bool						m_bPrintSceneDescription;	/*!< TODO: describe */
	bool						m_bPrintSceneText;			/*!< TODO: describe */
	QPagedPaintDevice::PageSize	m_paperSize;				/*!< TODO: describe */
	QPrinter::Orientation		m_iPaperOrientation;		/*!< TODO: describe */
	qreal						m_dLeftMargin;				/*!< TODO: describe */
	qreal						m_dRightMargin;				/*!< TODO: describe */
	qreal						m_dTopMargin;				/*!< TODO: describe */
	qreal						m_dBottomMargin;			/*!< TODO: describe */
	QPageLayout::Unit			m_iUnit;					/*!< TODO: describe */

	/*!
	 \brief

	 \fn createDatabase
	 \return bool
	*/
	bool			createDatabase();
	/*!
	 \brief

	 \fn updateDatabase
	 \param version
	 \return bool
	*/
	bool			updateDatabase(qint32 version);
	/*!
	 \brief

	 \fn updateDatabase01
	 \return bool
	*/
	bool			updateDatabase01();
	/*!
	 \brief

	 \fn updateDatabase1
	 \return bool
	*/
	bool			updateDatabase1();
	/*!
	 \brief

	 \fn updateDatabase2
	 \return bool
	*/
	bool			updateDatabase2();
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

	/*!
	 \brief

	 \fn printDocument
	 \param printer
	 \return bool
	*/
	bool			printDocument(QPrinter &printer);
	/*!
	 \brief

	 \fn configPrinter
	 \param printer
	*/
	void			configPrinter(QPrinter &printer);

	/*!
	 \brief

	 \fn configPrinter
	 \param printer
	*/
	void			printBlock(QTextCursor& cursor, const QString& szText, const QString& szFont, const qint16& iFontSize, const ALIGN align, const bool& bold, const bool& italic, const bool& underline);
};

#endif // CSTORYBOOK_H
