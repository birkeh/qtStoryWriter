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

	 \fn onOutlineDoubleClicked
	 \param index
	*/
	void				onOutlineDoubleClicked(const QModelIndex& index);
	/*!
	 \brief

	 \fn onCharacterDoubleClicked
	 \param index
	*/
	void				onCharacterDoubleClicked(const QModelIndex& index);
	/*!
	 \brief

	 \fn onPlaceDoubleClicked
	 \param index
	*/
	void				onPlaceDoubleClicked(const QModelIndex& index);
	/*!
	 \brief

	 \fn onObjectDoubleClicked
	 \param index
	*/
	void				onObjectDoubleClicked(const QModelIndex& index);
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
	QMenu*				m_lpTextMenu;							/*!< Pointer to the text menu */
	QMenu*				m_lpToolsMenu;							/*!< Pointer to the tools menu */
	QMenu*				m_lpWindowMenu;							/*!< Pointer to the window menu */
	QMenu*				m_lpHelpMenu;							/*!< Pointer to the help menu */

	QToolBar*			m_lpFileToolBar;						/*!< Pointer to the file toolbar */
	QToolBar*			m_lpEditToolBar;						/*!< Pointer to the edit toolbar */
	QToolBar*			m_lpTextToolBar;						/*!< Pointer to the text toolbar */
	QToolBar*			m_lpFormatToolBar;						/*!< Pointer to the text format toolbar*/

	QAction*			m_lpActionSave;							/*!< Pointer to the File->Save action */
	QAction*			m_lpActionUndo;							/*!< Pointer to the Undo action. This action is active for Text Edit widgets only. */
	QAction*			m_lpActionRedo;							/*!< Pointer to the Redo action. This action is active for Text Edit widgets only. */

	QAction*			m_lpActionTextBold;						/*!< Pointer to the Bold text format action. This action is active for Text Edit widgets only. */
	QAction*			m_lpActionTextItalic;					/*!< Pointer to the Italic text format action. This action is active for Text Edit widgets only. */
	QAction*			m_lpActionTextUnderline;				/*!< Pointer to the Unterline text format action. This action is active for Text Edit widgets only. */

	QAction*			m_lpActionAlignLeft;					/*!< Pointer to the Align Left text format action. This action is active for Text Edit widgets only. */
	QAction*			m_lpActionAlignCenter;					/*!< Pointer to the Align Center text format action.  This action is active for Text Edit widgets only. */
	QAction*			m_lpActionAlignRight;					/*!< Pointer to the Align Right text format action. This action is active for Text Edit widgets only. */
	QAction*			m_lpActionAlignJustify;					/*!< Pointer to the Align Justify (Block) text format action. This action is active for Text Edit widgets only. */

	QAction*			m_lpActionTextColor;					/*!< Pointer to the Text Color action. This action is active for Text Edit widgets only. */

	QAction*			m_lpActionCut;							/*!< Pointer to the Cut Text action. This action is active for Text Edit widgets only. */
	QAction*			m_lpActionCopy;							/*!< Pointer to the Copy Text action. This action is active for Text Edit widgets only. */
	QAction*			m_lpActionPaste;						/*!< pointer to the Paste Text action. This action is active for Text Edit widgets only. */

	QAction*			m_lpActionPartAdd;						/*!< TODO: describe */
	QAction*			m_lpActionPartEdit;						/*!< TODO: describe */
	QAction*			m_lpActionPartDelete;					/*!< TODO: describe */

	QAction*			m_lpActionChapterAdd;					/*!< TODO: describe */
	QAction*			m_lpActionChapterEdit;					/*!< TODO: describe */
	QAction*			m_lpActionChapterDelete;				/*!< TODO: describe */

	QAction*			m_lpActionSceneAdd;						/*!< TODO: describe */
	QAction*			m_lpActionSceneEdit;					/*!< TODO: describe */
	QAction*			m_lpActionSceneDelete;					/*!< TODO: describe */

	QAction*			m_lpActionCharacterAdd;					/*!< TODO: describe */
	QAction*			m_lpActionCharacterEdit;				/*!< TODO: describe */
	QAction*			m_lpActionCharacterDelete;				/*!< TODO: describe */

	QAction*			m_lpActionPlaceAdd;						/*!< TODO: describe */
	QAction*			m_lpActionPlaceEdit;					/*!< TODO: describe */
	QAction*			m_lpActionPlaceDelete;					/*!< TODO: describe */

	QAction*			m_lpActionObjectAdd;					/*!< TODO: describe */
	QAction*			m_lpActionObjectEdit;					/*!< TODO: describe */
	QAction*			m_lpActionObjectDelete;					/*!< TODO: describe */

	QAction*			m_lpActionRechercheAdd;					/*!< TODO: describe */
	QAction*			m_lpActionRechercheEdit;				/*!< TODO: describe */
	QAction*			m_lpActionRechercheDelete;				/*!< TODO: describe */
	QAction*			m_lpActionRechercheOpenLink;			/*!< TODO: describe */

	QAction*			m_lpSeparatorRecent;

	enum { MaxRecentFiles = 5 };								/*!< TODO: describe */
	QAction*			m_lpActionRecentFile[MaxRecentFiles];	/*!< TODO: describe */

	QActionGroup*		m_lpAlignGroup;							/*!< TODO: describe */

	QFontComboBox*		m_lpComboFont;							/*!< TODO: describe */
	QComboBox*			m_lpComboSize;							/*!< TODO: describe */

	cTextEdit*			m_lpOldTextEdit;						/*!< TODO: describe */
	QString				m_szOldPath;							/*!< TODO: describe */

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

	 \fn retranslateActions
	 \param actionList
	*/
	void				retranslateActions(QList<QAction*> actionList);

	/*!
	 \brief

	 \fn retranslateWindows
	*/
	void				retranslateWindows();
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
