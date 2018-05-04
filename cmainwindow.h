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

#include <QMainWindow>
#include <QMdiSubWindow>

#include <QStandardItemModel>

#include <QComboBox>
#include <QFontComboBox>

#include <QCloseEvent>

#include <QActionGroup>


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
	 \param parent
	*/
	explicit cMainWindow(QWidget* parent = 0);
	/*!
	 \brief

	 \fn ~cMainWindow
	*/
	~cMainWindow();

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

private slots:
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

private:
	Ui::cMainWindow*	ui; /*!< TODO: describe */
	QStandardItemModel*	m_lpOutlineModel; /*!< TODO: describe */
	QStandardItemModel*	m_lpCharacterModel; /*!< TODO: describe */
	QStandardItemModel*	m_lpPlaceModel; /*!< TODO: describe */
	QStandardItemModel*	m_lpObjectModel; /*!< TODO: describe */
	QStandardItemModel*	m_lpRechercheModel; /*!< TODO: describe */
	bool				m_bUpdatingTab; /*!< TODO: describe */
	cStoryBook*			m_lpStoryBook; /*!< TODO: describe */

	QList<QWidget*>		m_focusException; /*!< TODO: describe */

	QMenu*				m_lpFileMenu; /*!< TODO: describe */
	QMenu*				m_lpEditMenu; /*!< TODO: describe */
	QMenu*				m_lpTextMenu; /*!< TODO: describe */

	QToolBar*			m_lpFileToolBar; /*!< TODO: describe */
	QToolBar*			m_lpEditToolBar; /*!< TODO: describe */
	QToolBar*			m_lpTextToolBar; /*!< TODO: describe */
	QToolBar*			m_lpFormatToolBar; /*!< TODO: describe */
	QAction*			m_lpActionSave; /*!< TODO: describe */
	QAction*			m_lpActionUndo; /*!< TODO: describe */
	QAction*			m_lpActionRedo; /*!< TODO: describe */

	QAction*			m_lpActionTextBold; /*!< TODO: describe */
	QAction*			m_lpActionTextItalic; /*!< TODO: describe */
	QAction*			m_lpActionTextUnderline; /*!< TODO: describe */

	QAction*			m_lpActionAlignLeft; /*!< TODO: describe */
	QAction*			m_lpActionAlignCenter; /*!< TODO: describe */
	QAction*			m_lpActionAlignRight; /*!< TODO: describe */
	QAction*			m_lpActionAlignJustify; /*!< TODO: describe */

	QAction*			m_lpActionTextColor; /*!< TODO: describe */

	QAction*			m_lpActionCut; /*!< TODO: describe */
	QAction*			m_lpActionCopy; /*!< TODO: describe */
	QAction*			m_lpActionPaste; /*!< TODO: describe */

	QActionGroup*		m_lpAlignGroup; /*!< TODO: describe */

	QFontComboBox*		m_lpComboFont; /*!< TODO: describe */
	QComboBox*			m_lpComboSize; /*!< TODO: describe */

	cTextEdit*			m_lpOldTextEdit; /*!< TODO: describe */

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

protected:
	/*!
	 \brief

	 \fn closeEvent
	 \param event
	*/
	void				closeEvent(QCloseEvent *event);
};

#endif // CMAINWINDOW_H
