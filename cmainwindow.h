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

class cMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit cMainWindow(QWidget* parent = 0);
	~cMainWindow();

	void				updateWindowTitle();

	QAction*			actionAlignLeft();
	QAction*			actionAlignCenter();
	QAction*			actionAlignRight();
	QAction*			actionAlignJustify();

private slots:
	void				onTextEditGotFocus(cTextEdit* lpTextEdit);
	void				onTextEditLostFocus(cTextEdit* lpTextEdit);
	void				onLineEditGotFocus(cLineEdit* lpLineEdit);
	void				onLineEditLostFocus(cLineEdit* lpLineEdit);
	void				onTreeViewGotFocus(cTreeView* lpTreeView);
	void				onTreeViewLostFocus(cTreeView* lpTreeView);
	void				onCheckBoxGotFocus(cCheckBox* CheckBox);
	void				onCheckBoxLostFocus(cCheckBox* lpCheckBox);
	void				onRadioButtonGotFocus(cRadioButton* lpRadioButton);
	void				onRadioButtonLostFocus(cRadioButton* lpRadioButton);
	void				onDateEditGotFocus(cDateEdit* lpDateEdit);
	void				onDateEditLostFocus(cDateEdit* lpDateEdit);
	void				onDoubleSpinBoxGotFocus(cDoubleSpinBox* lpDoubleSpinBox);
	void				onDoubleSpinBoxLostFocus(cDoubleSpinBox* lpDoubleSpinBox);
	void				onDateTimeEditGotFocus(cDateTimeEdit* lpDateTimeEdit);
	void				onDateTimeEditLostFocus(cDateTimeEdit* lpDateTimeEdit);
	void				onComboBoxGotFocus(cComboBox* lpComboBox);
	void				onComboBoxLostFocus(cComboBox* lpComboBox);

	void				onMainTabCurrentChanged(int index);
	void				onMainTabTabCloseRequested(int index);
	void				onMdiAreaSubWindowActivated(QMdiSubWindow *arg1);

	void				onSubWindowClosed(QWidget* lpSubWindow);

	void				onOutlineDoubleClicked(const QModelIndex& index);
	void				onCharacterDoubleClicked(const QModelIndex& index);
	void				onPlaceDoubleClicked(const QModelIndex& index);
	void				onObjectDoubleClicked(const QModelIndex& index);
	void				onRechercheDoubleClicked(const QModelIndex& index);

	void				onShowPartWindow(cPart* lpPart);
	void				onShowChapterWindow(cChapter* lpChapter);
	void				onShowSceneWindow(cScene* lpScene);
	void				onShowCharacterWindow(cCharacter* lpCharacter);
	void				onShowPlaceWindow(cPlace* lpPlace);
	void				onShowObjectWindow(cObject* lpObject);
	void				onShowRechercheWindow(cRecherche* lpRecherche);

	void				onFileNew();
	void				onFileOpen();
	bool				onFileSave();
	bool				onFileSaveAs();
	void				onFilePrint();
	void				onFilePrintPreview();
	void				onFilePrintPdf();

	void				onClipboardDataChanged();

	void				onFontChanged(const QFont& font);
	void				onColorChanged(const QColor& color);
	void				onAlignmentChanged(const Qt::Alignment& alignment);

private:
	Ui::cMainWindow*	ui;
	QStandardItemModel*	m_lpOutlineModel;
	QStandardItemModel*	m_lpCharacterModel;
	QStandardItemModel*	m_lpPlaceModel;
	QStandardItemModel*	m_lpObjectModel;
	QStandardItemModel*	m_lpRechercheModel;
	bool				m_bUpdatingTab;
	cStoryBook*			m_lpStoryBook;

	QList<QWidget*>		m_focusException;

	QMenu*				m_lpFileMenu;
	QMenu*				m_lpEditMenu;
	QMenu*				m_lpTextMenu;

	QToolBar*			m_lpFileToolBar;
	QToolBar*			m_lpEditToolBar;
	QToolBar*			m_lpTextToolBar;
	QToolBar*			m_lpFormatToolBar;
	QAction*			m_lpActionSave;
	QAction*			m_lpActionUndo;
	QAction*			m_lpActionRedo;

	QAction*			m_lpActionTextBold;
	QAction*			m_lpActionTextItalic;
	QAction*			m_lpActionTextUnderline;

	QAction*			m_lpActionAlignLeft;
	QAction*			m_lpActionAlignCenter;
	QAction*			m_lpActionAlignRight;
	QAction*			m_lpActionAlignJustify;

	QAction*			m_lpActionTextColor;

	QAction*			m_lpActionCut;
	QAction*			m_lpActionCopy;
	QAction*			m_lpActionPaste;

	QActionGroup*		m_lpAlignGroup;

	QFontComboBox*		m_lpComboFont;
	QComboBox*			m_lpComboSize;

	cTextEdit*			m_lpOldTextEdit;

	void				initUI();
	void				createActions();

	void				createFileActions();
	void				createEditActions();
	void				createTextActions();

	void				disableTextEdit();
	void				prepareTextEdit(cTextEdit* lpTextEdit);
	void				disconnectTextEdit();

protected:
	void				closeEvent(QCloseEvent *event);
};

#endif // CMAINWINDOW_H
