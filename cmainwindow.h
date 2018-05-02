#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H


#include "cstorybook.h"

#include <QMainWindow>
#include <QMdiSubWindow>

#include <QStandardItemModel>

#include <QComboBox>
#include <QFontComboBox>

#include <QCloseEvent>


namespace Ui {
class cMainWindow;
}

class cMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit cMainWindow(QWidget *parent = 0);
	~cMainWindow();

	void				updateWindowTitle();

private slots:
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

	void				onTextBold();
	void				onTextItalic();
	void				onTextUnderline();

	void				onTextFamily(const QString &f);
	void				onTextSize(const QString &p);
	void				onTextStyle(int styleIndex);
	void				onTextColor();

	void				onTextAlign(QAction *a);

	void				onSpecialUndo();
	void				onSpecialRedo();
	void				onSpecialCut();
	void				onSpecialCopy();
	void				onSpecialPaste();

private:
	Ui::cMainWindow*	ui;
	QStandardItemModel*	m_lpOutlineModel;
	QStandardItemModel*	m_lpCharacterModel;
	QStandardItemModel*	m_lpPlaceModel;
	QStandardItemModel*	m_lpObjectModel;
	QStandardItemModel*	m_lpRechercheModel;
	bool				m_bUpdatingTab;
	cStoryBook*			m_lpStoryBook;

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

	QComboBox*			m_lpComboStyle;
	QFontComboBox*		m_lpComboFont;
	QComboBox*			m_lpComboSize;

	void				initUI();
	void				createActions();

	void				createFileActions();
	void				createEditActions();
	void				createTextActions();

protected:
	void				closeEvent(QCloseEvent *event);
};

#endif // CMAINWINDOW_H
