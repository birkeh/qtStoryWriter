/*!
 \file cmainwindow.h

*/

#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H


#include "cstorybook.h"
#include "ctextedit.h"
#include "clineedit.h"
#include "ctreeview.h"
#include "ccheckbox.h"
#include "cradiobutton.h"
#include "cdateedit.h"
#include "cdoublespinbox.h"
#include "cdatetimeedit.h"
#include "ccombobox.h"
#include "coptionsdialog.h"
#include "cfontcombobox.h"

#include "csplashscreen.h"

#include <QMainWindow>
#include <QMdiSubWindow>

#include <QTranslator>

#include <QStandardItemModel>

#include <QComboBox>
#include <QFontComboBox>

#include <QCloseEvent>

#include <QActionGroup>

#include <QPoint>


namespace Ui {
class cMainWindow;
}

/*!
 \brief

 \class cMainWindow cmainwindow.h "cmainwindow.h"
*/
class cMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	/*!
	 \brief

	 \fn cMainWindow
	 \param lpSplashScreen
	 \param parent
	*/
	explicit cMainWindow(cSplashScreen* lpSplashScreen, QTranslator* lpTranslator, QWidget* parent = 0);
	/*!
	 \brief

	 \fn ~cMainWindow
	*/
	~cMainWindow();

	/*!
	 \brief

	 \fn somethingChanged
	*/
	void				somethingChanged();

	/*!
	 \brief

	 \fn updateWindowTitle
	*/
	void				updateWindowTitle();

	/*!
	 \brief

	 \fn actionAlignLeft
	 \return QAction
	*/
	QAction*			actionAlignLeft();
	/*!
	 \brief

	 \fn actionAlignCenter
	 \return QAction
	*/
	QAction*			actionAlignCenter();
	/*!
	 \brief

	 \fn actionAlignRight
	 \return QAction
	*/
	QAction*			actionAlignRight();
	/*!
	 \brief

	 \fn actionAlignJustify
	 \return QAction
	*/
	QAction*			actionAlignJustify();

public slots:
	/*!
	 \brief

	 \fn onLanguageChanged
	*/
	void				onLanguageChanged();
	/*!
	 \brief

	 \fn onTextEditGotFocus
	 \param lpTextEdit
	*/
	void				onTextEditGotFocus(cTextEdit* lpTextEdit);
	/*!
	 \brief

	 \fn onTextEditLostFocus
	 \param lpTextEdit
	*/
	void				onTextEditLostFocus(cTextEdit* lpTextEdit);
	/*!
	 \brief

	 \fn onLineEditGotFocus
	 \param lpLineEdit
	*/
	void				onLineEditGotFocus(cLineEdit* lpLineEdit);
	/*!
	 \brief

	 \fn onLineEditLostFocus
	 \param lpLineEdit
	*/
	void				onLineEditLostFocus(cLineEdit* lpLineEdit);
	/*!
	 \brief

	 \fn onTreeViewGotFocus
	 \param lpTreeView
	*/
	void				onTreeViewGotFocus(cTreeView* lpTreeView);
	/*!
	 \brief

	 \fn onTreeViewLostFocus
	 \param lpTreeView
	*/
	void				onTreeViewLostFocus(cTreeView* lpTreeView);
	/*!
	 \brief

	 \fn onCheckBoxGotFocus
	 \param CheckBox
	*/
	void				onCheckBoxGotFocus(cCheckBox* CheckBox);
	/*!
	 \brief

	 \fn onCheckBoxLostFocus
	 \param lpCheckBox
	*/
	void				onCheckBoxLostFocus(cCheckBox* lpCheckBox);
	/*!
	 \brief

	 \fn onRadioButtonGotFocus
	 \param lpRadioButton
	*/
	void				onRadioButtonGotFocus(cRadioButton* lpRadioButton);
	/*!
	 \brief

	 \fn onRadioButtonLostFocus
	 \param lpRadioButton
	*/
	void				onRadioButtonLostFocus(cRadioButton* lpRadioButton);
	/*!
	 \brief

	 \fn onDateEditGotFocus
	 \param lpDateEdit
	*/
	void				onDateEditGotFocus(cDateEdit* lpDateEdit);
	/*!
	 \brief

	 \fn onDateEditLostFocus
	 \param lpDateEdit
	*/
	void				onDateEditLostFocus(cDateEdit* lpDateEdit);
	/*!
	 \brief

	 \fn onDoubleSpinBoxGotFocus
	 \param lpDoubleSpinBox
	*/
	void				onDoubleSpinBoxGotFocus(cDoubleSpinBox* lpDoubleSpinBox);
	/*!
	 \brief

	 \fn onDoubleSpinBoxLostFocus
	 \param lpDoubleSpinBox
	*/
	void				onDoubleSpinBoxLostFocus(cDoubleSpinBox* lpDoubleSpinBox);
	/*!
	 \brief

	 \fn onDateTimeEditGotFocus
	 \param lpDateTimeEdit
	*/
	void				onDateTimeEditGotFocus(cDateTimeEdit* lpDateTimeEdit);
	/*!
	 \brief

	 \fn onDateTimeEditLostFocus
	 \param lpDateTimeEdit
	*/
	void				onDateTimeEditLostFocus(cDateTimeEdit* lpDateTimeEdit);
	/*!
	 \brief

	 \fn onComboBoxGotFocus
	 \param lpComboBox
	*/
	void				onComboBoxGotFocus(cComboBox* lpComboBox);
	/*!
	 \brief

	 \fn onComboBoxLostFocus
	 \param lpComboBox
	*/
	void				onComboBoxLostFocus(cComboBox* lpComboBox);
	/*!
	 \brief

	 \fn onFontComboBoxGotFocus
	 \param lpComboBox
	*/
	void				onFontComboBoxGotFocus(cFontComboBox* lpComboBox);
	/*!
	 \brief

	 \fn onFontComboBoxLostFocus
	 \param lpComboBox
	*/
	void				onFontComboBoxLostFocus(cFontComboBox* lpComboBox);
	/*!
	 \brief

	 \fn onOutlineDropped
	 \param lpTreeView
	*/
	void				onOutlineDropped(cTreeView* lpTreeView);
private slots:
	/*!
	 \brief

	 \fn onMainTabCurrentChanged
	 \param index
	*/
	void				onMainTabCurrentChanged(int index);
	/*!
	 \brief

	 \fn onMainTabTabCloseRequested
	 \param index
	*/
	void				onMainTabTabCloseRequested(int index);
	/*!
	 \brief

	 \fn onMdiAreaSubWindowActivated
	 \param arg1
	*/
	void				onMdiAreaSubWindowActivated(QMdiSubWindow *arg1);

	/*!
	 \brief

	 \fn onSubWindowClosed
	 \param lpSubWindow
	*/
	void				onSubWindowClosed(QWidget* lpSubWindow);

	/*!
	 \brief

	 \fn onOutlineClicked
	 \param index
	*/
	void				onOutlineClicked(const QModelIndex& index);
	/*!
	 \brief

	 \fn onOutlineDoubleClicked
	 \param index
	*/
	void				onOutlineDoubleClicked(const QModelIndex& index);
	/*!
	 \brief

	 \fn onCharacterClicked
	 \param index
	*/
	void				onCharacterClicked(const QModelIndex& index);
	/*!
	 \brief

	 \fn onCharacterDoubleClicked
	 \param index
	*/
	void				onCharacterDoubleClicked(const QModelIndex& index);
	/*!
	 \brief

	 \fn onPlaceClicked
	 \param index
	*/
	void				onPlaceClicked(const QModelIndex& index);
	/*!
	 \brief

	 \fn onPlaceDoubleClicked
	 \param index
	*/
	void				onPlaceDoubleClicked(const QModelIndex& index);
	/*!
	 \brief

	 \fn onObjectClicked
	 \param index
	*/
	void				onObjectClicked(const QModelIndex& index);
	/*!
	 \brief

	 \fn onObjectDoubleClicked
	 \param index
	*/
	void				onObjectDoubleClicked(const QModelIndex& index);
	/*!
	 \brief

	 \fn onRechercheClicked
	 \param index
	*/
	void				onRechercheClicked(const QModelIndex& index);
	/*!
	 \brief

	 \fn onRechercheDoubleClicked
	 \param index
	*/
	void				onRechercheDoubleClicked(const QModelIndex& index);

	/*!
	 \brief

	 \fn onShowPropertiesWindow
	*/
	void				onShowPropertiesWindow();

	/*!
	 \brief

	 \fn onShowPartWindow
	 \param lpPart
	*/
	void				onShowPartWindow(cPart* lpPart);
	/*!
	 \brief

	 \fn onShowChapterWindow
	 \param lpChapter
	*/
	void				onShowChapterWindow(cChapter* lpChapter);
	/*!
	 \brief

	 \fn onShowSceneWindow
	 \param lpScene
	*/
	void				onShowSceneWindow(cScene* lpScene);
	/*!
	 \brief

	 \fn onShowCharacterWindow
	 \param lpCharacter
	*/
	void				onShowCharacterWindow(cCharacter* lpCharacter);
	/*!
	 \brief

	 \fn onShowPlaceWindow
	 \param lpPlace
	*/
	void				onShowPlaceWindow(cPlace* lpPlace);
	/*!
	 \brief

	 \fn onShowObjectWindow
	 \param lpObject
	*/
	void				onShowObjectWindow(cObject* lpObject);
	/*!
	 \brief

	 \fn onShowRechercheWindow
	 \param lpRecherche
	*/
	void				onShowRechercheWindow(cRecherche* lpRecherche);

	/*!
	 \brief

	 \fn onOutlineContextMenu
	 \param index
	*/
	void				onOutlineContextMenu(const QPoint& pos);
	/*!
	 \brief

	 \fn onCharacterContextMenu
	 \param index
	*/
	void				onCharacterContextMenu(const QPoint& pos);
	/*!
	 \brief

	 \fn onPlaceContextMenu
	 \param index
	*/
	void				onPlaceContextMenu(const QPoint& pos);
	/*!
	 \brief

	 \fn onObjectContextMenu
	 \param index
	*/
	void				onObjectContextMenu(const QPoint& pos);
	/*!
	 \brief

	 \fn onRechercheContextMenu
	 \param index
	*/
	void				onRechercheContextMenu(const QPoint& pos);

	/*!
	 \brief

	 \fn onFileNew
	*/
	void				onFileNew();
	/*!
	 \brief

	 \fn onFileOpen
	*/
	void				onFileOpen();
	/*!
	 \brief

	 \fn onFileSave
	 \return bool
	*/
	bool				onFileSave();
	/*!
	 \brief

	 \fn onFileSaveAs
	 \return bool
	*/
	bool				onFileSaveAs();
	/*!
	 \brief

	 \fn onFilePrint
	*/
	void				onFilePrint();
	/*!
	 \brief

	 \fn onFilePrintPreview
	*/
	void				onFilePrintPreview();
	/*!
	 \brief

	 \fn onFilePrintPdf
	*/
	void				onFilePrintPdf();
	/*!
	 \brief

	 \fn onFilePrintPdf
	*/
	void				onFileProperties();

	/*!
	 \brief

	 \fn onToolsOptions
	*/
	void				onToolsOptions();

	/*!
	 \brief

	 \fn onHelpContents
	*/
	void				onHelpContents();
	/*!
	 \brief

	 \fn onHelpIndex
	*/
	void				onHelpIndex();
	/*!
	 \brief

	 \fn onHelpAbout
	*/
	void				onHelpAbout();

	/*!
	 \brief

	 \fn onClipboardDataChanged
	*/
	void				onClipboardDataChanged();

	/*!
	 \brief

	 \fn onFontChanged
	 \param font
	*/
	void				onFontChanged(const QFont& font);
	/*!
	 \brief

	 \fn onColorChanged
	 \param color
	*/
	void				onColorChanged(const QColor& color);
	/*!
	 \brief

	 \fn onAlignmentChanged
	 \param alignment
	*/
	void				onAlignmentChanged(const Qt::Alignment& alignment);

	/*!
	 \brief

	 \fn onAddPart
	*/
	void				onAddPart();
	/*!
	 \brief

	 \fn onEditPart
	*/
	void				onEditPart();
	/*!
	 \brief

	 \fn onDeletePart
	*/
	void				onDeletePart();

	/*!
	 \brief

	 \fn onAddChapter
	*/
	void				onAddChapter();
	/*!
	 \brief

	 \fn onEditChapter
	*/
	void				onEditChapter();
	/*!
	 \brief

	 \fn onDeleteChapter
	*/
	void				onDeleteChapter();

	/*!
	 \brief

	 \fn onAddScene
	*/
	void				onAddScene();
	/*!
	 \brief

	 \fn onEditScene
	*/
	void				onEditScene();
	/*!
	 \brief

	 \fn onDeleteScene
	*/
	void				onDeleteScene();

	/*!
	 \brief

	 \fn onAddCharacter
	*/
	void				onAddCharacter();
	/*!
	 \brief

	 \fn onEditCharacter
	*/
	void				onEditCharacter();
	/*!
	 \brief

	 \fn onDeleteCharacter
	*/
	void				onDeleteCharacter();

	/*!
	 \brief

	 \fn onAddPlace
	*/
	void				onAddPlace();
	/*!
	 \brief

	 \fn onEditPlace
	*/
	void				onEditPlace();
	/*!
	 \brief

	 \fn onDeletePlace
	*/
	void				onDeletePlace();

	/*!
	 \brief

	 \fn onAddObject
	*/
	void				onAddObject();
	/*!
	 \brief

	 \fn onEditObject
	*/
	void				onEditObject();
	/*!
	 \brief

	 \fn onDeleteObject
	*/
	void				onDeleteObject();

	/*!
	 \brief

	 \fn onAddRecherche
	*/
	void				onAddRecherche();

	/*!
	 \brief

	 \fn onEditRecherche
	*/
	void				onEditRecherche();

	/*!
	 \brief

	 \fn onDeleteRecherche
	*/
	void				onDeleteRecherche();

	/*!
	 \brief

	 \fn onOpenRechercheLink
	*/
	void				onOpenRechercheLink();

private:
	Ui::cMainWindow*	ui;										/*!< User Interface */

	cSplashScreen*		m_lpSplashScreen;						/*!< Splash Screen */

	QTranslator*		m_lpTranslator;							/*!< Pointer to the current translator */
	QStandardItemModel*	m_lpOutlineModel;						/*!< Item Model for Outline list */
	QStandardItemModel*	m_lpCharacterModel;						/*!< Item Model for Character list */
	QStandardItemModel*	m_lpPlaceModel;							/*!< Item Model for Place list */
	QStandardItemModel*	m_lpObjectModel;						/*!< Item Model for Object list */
	QStandardItemModel*	m_lpRechercheModel;						/*!< Item Model for Recherche list */
	bool				m_bUpdatingTab;							/*!< TRUE if main tab is currently being updated */
	bool				m_bSomethingChanged;					/*!< TRUE if the current project has unsaved changes */
	cStoryBook*			m_lpStoryBook;							/*!< Pointer to the storybook */

	QList<QWidget*>		m_focusException;						/*!< TODO: describe */

	QMenu*				m_lpFileMenu;							/*!< Pointer to the file menu */
	QMenu*				m_lpEditMenu;							/*!< Pointer to the edit menu */
	QMenu*				m_lpPartMenu;							/*!< TODO: describe */
	QMenu*				m_lpChapterMenu;						/*!< TODO: describe */
	QMenu*				m_lpSceneMenu;							/*!< TODO: describe */
	QMenu*				m_lpCharacterMenu;						/*!< TODO: describe */
	QMenu*				m_lpPlaceMenu;							/*!< TODO: describe */
	QMenu*				m_lpObjectMenu;							/*!< TODO: describe */
	QMenu*				m_lpRechercheMenu;						/*!< TODO: describe */
	QMenu*				m_lpTextMenu;							/*!< Pointer to the text menu */
	QMenu*				m_lpToolsMenu;							/*!< Pointer to the tools menu */
	QMenu*				m_lpWindowMenu;							/*!< Pointer to the window menu */
	QMenu*				m_lpHelpMenu;							/*!< Pointer to the help menu */

	QToolBar*			m_lpFileToolBar;						/*!< Pointer to the file toolbar */
	QToolBar*			m_lpEditToolBar;						/*!< Pointer to the edit toolbar */
	QToolBar*			m_lpTextToolBar;						/*!< Pointer to the text toolbar */
	QToolBar*			m_lpFormatToolBar;						/*!< Pointer to the text format toolbar*/
	QToolBar*			m_lpViewToolBar;						/*!< Pointer to the text view toolbar*/

	QAction*			m_lpFileNewAction;						/*!< TODO: describe */
	QAction*			m_lpFileOpenAction;						/*!< TODO: describe */
	QAction*			m_lpFileSaveAction;						/*!< TODO: describe */
	QAction*			m_lpFileSaveAsAction;					/*!< TODO: describe */
	QAction*			m_lpFilePrintAction;					/*!< TODO: describe */
	QAction*			m_lpFilePrintPreviewAction;				/*!< TODO: describe */
	QAction*			m_lpFileExportPDFAction;				/*!< TODO: describe */
	QAction*			m_lpFilePropertiesAction;				/*!< TODO: describe */
	QAction*			m_lpFileQuitAction;						/*!< TODO: describe */

	QAction*			m_lpUndoAction;							/*!< Pointer to the Undo action. This action is active for Text Edit widgets only. */
	QAction*			m_lpRedoAction;							/*!< Pointer to the Redo action. This action is active for Text Edit widgets only. */

	QAction*			m_lpTextBoldAction;						/*!< Pointer to the Bold text format action. This action is active for Text Edit widgets only. */
	QAction*			m_lpTextItalicAction;					/*!< Pointer to the Italic text format action. This action is active for Text Edit widgets only. */
	QAction*			m_lpTextUnderlineAction;				/*!< Pointer to the Unterline text format action. This action is active for Text Edit widgets only. */

	QAction*			m_lpAlignLeftAction;					/*!< Pointer to the Align Left text format action. This action is active for Text Edit widgets only. */
	QAction*			m_lpAlignCenterAction;					/*!< Pointer to the Align Center text format action.  This action is active for Text Edit widgets only. */
	QAction*			m_lpAlignRightAction;					/*!< Pointer to the Align Right text format action. This action is active for Text Edit widgets only. */
	QAction*			m_lpAlignJustifyAction;					/*!< Pointer to the Align Justify (Block) text format action. This action is active for Text Edit widgets only. */

	QAction*			m_lpTextColorAction;					/*!< Pointer to the Text Color action. This action is active for Text Edit widgets only. */

	QAction*			m_lpCutAction;							/*!< Pointer to the Cut Text action. This action is active for Text Edit widgets only. */
	QAction*			m_lpCopyAction;							/*!< Pointer to the Copy Text action. This action is active for Text Edit widgets only. */
	QAction*			m_lpPasteAction;						/*!< pointer to the Paste Text action. This action is active for Text Edit widgets only. */

	QAction*			m_lpHelpContentsAction;					/*!< TODO: describe */
	QAction*			m_lpHelpIndexAction;					/*!< TODO: describe */
	QAction*			m_lpHelpAboutAction;					/*!< TODO: describe */

	QAction*			m_lpPartAddAction;						/*!< TODO: describe */
	QAction*			m_lpPartEditAction;						/*!< TODO: describe */
	QAction*			m_lpPartDeleteAction;					/*!< TODO: describe */

	QAction*			m_lpChapterAddAction;					/*!< TODO: describe */
	QAction*			m_lpChapterEditAction;					/*!< TODO: describe */
	QAction*			m_lpChapterDeleteAction;				/*!< TODO: describe */

	QAction*			m_lpSceneAddAction;						/*!< TODO: describe */
	QAction*			m_lpSceneEditAction;					/*!< TODO: describe */
	QAction*			m_lpSceneDeleteAction;					/*!< TODO: describe */

	QAction*			m_lpCharacterAddAction;					/*!< TODO: describe */
	QAction*			m_lpCharacterEditAction;				/*!< TODO: describe */
	QAction*			m_lpCharacterDeleteAction;				/*!< TODO: describe */

	QAction*			m_lpPlaceAddAction;						/*!< TODO: describe */
	QAction*			m_lpPlaceEditAction;					/*!< TODO: describe */
	QAction*			m_lpPlaceDeleteAction;					/*!< TODO: describe */

	QAction*			m_lpObjectAddAction;					/*!< TODO: describe */
	QAction*			m_lpObjectEditAction;					/*!< TODO: describe */
	QAction*			m_lpObjectDeleteAction;					/*!< TODO: describe */

	QAction*			m_lpRechercheAddAction;					/*!< TODO: describe */
	QAction*			m_lpRechercheEditAction;				/*!< TODO: describe */
	QAction*			m_lpRechercheDeleteAction;				/*!< TODO: describe */
	QAction*			m_lpRechercheOpenLinkAction;			/*!< TODO: describe */

	QAction*			m_lpToolsOptionsAction;					/*!< TODO: describe */

	QAction*			m_lpSeparatorRecent;

	enum { MaxRecentFiles = 5 };								/*!< TODO: describe */
	QAction*			m_lpRecentFileAction[MaxRecentFiles];	/*!< TODO: describe */

	QActionGroup*		m_lpAlignGroup;							/*!< TODO: describe */

	QFontComboBox*		m_lpComboFont;							/*!< TODO: describe */
	QComboBox*			m_lpComboSize;							/*!< TODO: describe */

	cTextEdit*			m_lpOldTextEdit;						/*!< TODO: describe */
	QString				m_szOldPath;							/*!< TODO: describe */

	cOptionsDialog*		m_lpOptionsDialog;						/*!< TODO: describe */
	/*!
	 \brief

	 \fn initUI
	*/
	void				initUI();
	/*!
	 \brief

	 \fn createActions
	*/
	void				createActions();

	/*!
	 \brief

	 \fn createFileActions
	*/
	void				createFileActions();
	/*!
	 \brief

	 \fn createEditActions
	*/
	void				createEditActions();
	/*!
	 \brief

	 \fn createPartActions
	*/
	void				createPartActions();
	/*!
	 \brief

	 \fn createChapterActions
	*/
	void				createChapterActions();

	/*!
	 \brief

	 \fn createSceneActions
	*/
	void				createSceneActions();
	/*!
	 \brief

	 \fn createCharacterActions
	*/
	void				createCharacterActions();
	/*!
	 \brief

	 \fn createPlaceActions
	*/
	void				createPlaceActions();
	/*!
	 \brief

	 \fn createObjectActions
	*/
	void				createObjectActions();
	/*!
	 \brief

	 \fn createRechercheActions
	*/
	void				createRechercheActions();
	/*!
	 \brief

	 \fn createTextActions
	*/
	void				createTextActions();
	/*!
	 \brief

	 \fn createToolsActions
	*/
	void				createToolsActions();
	/*!
	 \brief

	 \fn createWindowActions
	*/
	void				createWindowActions();
	/*!
	 \brief

	 \fn createHelpActions
	*/
	void				createHelpActions();
	/*!
	 \brief

	 \fn createContextActions
	*/
	void				createContextActions();

	/*!
	 \brief

	 \fn initOutlineActions
	*/
	void				initOutlineActions(cPart* lpPart = nullptr, cChapter* lpChapter = nullptr, cScene* lpScene = nullptr, cCharacter* lpCharacter = nullptr, cPlace* lpPlace = nullptr, cObject* lpObject = nullptr, cRecherche* lpRecherche = nullptr);

	/*!
	 \brief

	 \fn disableTextEdit
	*/
	void				disableTextEdit();
	/*!
	 \brief

	 \fn prepareTextEdit
	 \param lpTextEdit
	*/
	void				prepareTextEdit(cTextEdit* lpTextEdit);
	/*!
	 \brief

	 \fn disconnectTextEdit
	*/
	void				disconnectTextEdit();

	/*!
	 \brief

	 \fn getProjectLoadName
	 \return QString
	*/
	QString				getProjectLoadName();
	/*!
	 \brief

	 \fn getProjectSaveName
	 \param szFileName
	 \return QString
	*/
	QString				getProjectSaveName(const QString& szFileName = QString());

	/*!
	 \brief

	 \fn setCurrentFile
	 \param szFileName
	*/
	void				setCurrentFile(const QString& szFileName);

	/*!
	 \brief

	 \fn openRecentFile
	*/
	void				openRecentFile();
	/*!
	 \brief

	 \fn updateRecentFileActions
	*/
	void				updateRecentFileActions();

	/*!
	 \brief

	 \fn retranslateMenu
	 \param lpMenu
	*/
	void				retranslateMenu();


	/*!
	 \brief

	 \fn retranslateWindows
	*/
	void				retranslateWindows();

	/*!
	 \brief

	 \fn enableMenu
	 \param lpMenu
	*/
	void				enableMenu(QMenu* lpMenuEnable, QList<QAction*>actionListEnable, QMenu* lpMenuDisable, QList<QAction*>actionListDisable);
protected:
	/*!
	 \brief

	 \fn changeEvent
	 \param event
	*/
	void				changeEvent(QEvent* event);
	/*!
	 \brief

	 \fn closeEvent
	 \param event
	*/
	void				closeEvent(QCloseEvent* event);
};

#endif // CMAINWINDOW_H
