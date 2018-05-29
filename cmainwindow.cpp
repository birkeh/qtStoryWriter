/*!
 \file cmainwindow.cpp

*/

#include "common.h"

#include "cmainwindow.h"
#include "ui_cmainwindow.h"

#include "ctextdocument.h"
#include "ctextedit.h"

#include "cpartwindow.h"

#include "cwidget.h"

#include <QTextDocument>
#include <QTextBlockFormat>
#include <QTextCharFormat>

#include <QSettings>

#include <QDir>
#include <QThread>

#include <QTextEdit>

#include <QClipboard>
#include <QMimeData>

#include <QToolBar>

#include <QSqlQuery>
#include <QSqlError>

#include <QMessageBox>
#include <QInputDialog>

#include <QFileDialog>

#include <QDesktopServices>


cMainWindow::cMainWindow(cSplashScreen *lpSplashScreen, QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::cMainWindow),
	m_lpSplashScreen(lpSplashScreen),
	m_lpOutlineModel(0),
	m_lpCharacterModel(0),
	m_lpPlaceModel(0),
	m_lpObjectModel(0),
	m_bUpdatingTab(false),
	m_bSomethingChanged(false),
	m_lpStoryBook(0),
	m_lpFileMenu(0),
	m_lpEditMenu(0),
	m_lpTextMenu(0),
	m_lpFileToolBar(0),
	m_lpEditToolBar(0),
	m_lpTextToolBar(0),
	m_lpFormatToolBar(0),
	m_lpOldTextEdit(0)
{
	initUI();
	createActions();

	disableTextEdit();

	onFileNew();

	QSettings	settings;
	m_szOldPath	= settings.value("file/lastPath", QDir::homePath()).toString();
	updateRecentFileActions();

	QThread::msleep(2000);
}

cMainWindow::~cMainWindow()
{
	if(m_lpStoryBook)
		delete m_lpStoryBook;

	delete ui;
}

void cMainWindow::somethingChanged()
{
	if(!m_bSomethingChanged)
	{
		m_bSomethingChanged	= true;
		updateWindowTitle();
	}
}

QAction* cMainWindow::actionAlignLeft()
{
	return(m_lpActionAlignLeft);
}

QAction* cMainWindow::actionAlignCenter()
{
	return(m_lpActionAlignCenter);
}

QAction* cMainWindow::actionAlignRight()
{
	return(m_lpActionAlignRight);
}

QAction* cMainWindow::actionAlignJustify()
{
	return(m_lpActionAlignJustify);
}

void cMainWindow::closeEvent(QCloseEvent *event)
{
	if(m_bSomethingChanged)
	{
		switch(QMessageBox::question(this, tr("Save"), m_lpStoryBook->title() + tr(" has been changed.\nDo you want to save?"), QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel))
		{
		case QMessageBox::Yes:
			onFileSave();
			event->accept();
			return;
		case QMessageBox::No:
			event->accept();
			return;
		case QMessageBox::Cancel:
			event->ignore();
			return;
		default:
			return;
		}
	}

	QSettings	settings;
	settings.setValue("main/width", QVariant::fromValue(size().width()));
	settings.setValue("main/height", QVariant::fromValue(size().height()));
	settings.setValue("main/x", QVariant::fromValue(x()));
	settings.setValue("main/y", QVariant::fromValue(y()));
	settings.setValue("main/splitter1", QVariant::fromValue(ui->m_lpMainSplitter->sizes()[0]));
	settings.setValue("main/splitter2", QVariant::fromValue(ui->m_lpMainSplitter->sizes()[1]));
	if(this->isMaximized())
		settings.setValue("main/maximized", QVariant::fromValue(true));
	else
		settings.setValue("main/maximized", QVariant::fromValue(false));

	settings.setValue("file/lastPath", QVariant::fromValue(m_szOldPath));

	event->accept();
}

void cMainWindow::initUI()
{
	ui->setupUi(this);

	m_lpOutlineModel	= new QStandardItemModel(0, 1);
	ui->m_lpOutlineList->setModel(m_lpOutlineModel);

	m_lpCharacterModel	= new QStandardItemModel(0, 1);
	ui->m_lpCharacterList->setModel(m_lpCharacterModel);

	m_lpPlaceModel	= new QStandardItemModel(0, 1);
	ui->m_lpPlaceList->setModel(m_lpPlaceModel);

	m_lpObjectModel	= new QStandardItemModel(0, 1);
	ui->m_lpObjectList->setModel(m_lpObjectModel);

	m_lpRechercheModel	= new QStandardItemModel(0, 1);
	ui->m_lpRechercheList->setModel(m_lpRechercheModel);

	QSettings	settings;
	qint16		iX			= settings.value("main/x", QVariant::fromValue(-1)).toInt();
	qint16		iY			= settings.value("main/y", QVariant::fromValue(-1)).toInt();
	qint16		iWidth		= settings.value("main/width", QVariant::fromValue(-1)).toInt();
	qint16		iHeight		= settings.value("main/height", QVariant::fromValue(-1)).toInt();
	qint16		iSplitter1	= settings.value("main/splitter1", QVariant::fromValue(-1)).toInt();
	qint16		iSplitter2	= settings.value("main/splitter2", QVariant::fromValue(-1)).toInt();

	if(iWidth != -1 && iHeight != -1)
		resize(iWidth, iHeight);
	if(iX != -1 && iY != -1)
		move(iX, iY);

	if(iSplitter1 != -1 && iSplitter2 != -1)
		ui->m_lpMainSplitter->setSizes(QList<int>() << iSplitter1 << iSplitter2);

	ui->m_lpMainToolBox->setCurrentIndex(0);
}

void cMainWindow::createActions()
{
	setToolButtonStyle(Qt::ToolButtonFollowStyle);
	createFileActions();
	createEditActions();
	createTextActions();

	createContextActions();

	connect(ui->m_lpMainTab,		&QTabWidget::currentChanged,			this,	&cMainWindow::onMainTabCurrentChanged);
	connect(ui->m_lpMainTab,		&QTabWidget::tabCloseRequested,			this,	&cMainWindow::onMainTabTabCloseRequested);
	connect(ui->m_lpMdiArea,		&QMdiArea::subWindowActivated,			this,	&cMainWindow::onMdiAreaSubWindowActivated);

	connect(ui->m_lpOutlineList,	&QTreeView::doubleClicked,				this,	&cMainWindow::onOutlineDoubleClicked);
	connect(ui->m_lpCharacterList,	&QTreeView::doubleClicked,				this,	&cMainWindow::onCharacterDoubleClicked);
	connect(ui->m_lpPlaceList,		&QTreeView::doubleClicked,				this,	&cMainWindow::onPlaceDoubleClicked);
	connect(ui->m_lpObjectList,		&QTreeView::doubleClicked,				this,	&cMainWindow::onObjectDoubleClicked);
	connect(ui->m_lpRechercheList,	&QTreeView::doubleClicked,				this,	&cMainWindow::onRechercheDoubleClicked);

	connect(ui->m_lpOutlineList,	&QTreeView::customContextMenuRequested,	this,	&cMainWindow::onOutlineContextMenu);
	connect(ui->m_lpCharacterList,	&QTreeView::customContextMenuRequested,	this,	&cMainWindow::onCharacterContextMenu);
	connect(ui->m_lpPlaceList,		&QTreeView::customContextMenuRequested,	this,	&cMainWindow::onPlaceContextMenu);
	connect(ui->m_lpObjectList,		&QTreeView::customContextMenuRequested,	this,	&cMainWindow::onObjectContextMenu);
	connect(ui->m_lpRechercheList,	&QTreeView::customContextMenuRequested,	this,	&cMainWindow::onRechercheContextMenu);
}

void cMainWindow::createFileActions()
{
	QAction*	lpAction;

	m_lpFileMenu		= menuBar()->addMenu(tr("&File"));
	m_lpFileToolBar		= addToolBar(tr("File Actions"));

	const QIcon	newIcon			= QIcon::fromTheme("document-new", QIcon(":/images/mac/filenew.png"));
	lpAction					= m_lpFileMenu->addAction(newIcon, tr("&New"), this, &cMainWindow::onFileNew);
	m_lpFileToolBar->addAction(lpAction);
	lpAction->setPriority(QAction::LowPriority);
	lpAction->setShortcut(QKeySequence::New);

	const QIcon	openIcon		= QIcon::fromTheme("document-open", QIcon(":/images/mac/fileopen.png"));
	lpAction					= m_lpFileMenu->addAction(openIcon, tr("&Open..."), this, &cMainWindow::onFileOpen);
	lpAction->setShortcut(QKeySequence::Open);
	m_lpFileToolBar->addAction(lpAction);

	m_lpFileMenu->addSeparator();

	const QIcon	saveIcon		= QIcon::fromTheme("document-save", QIcon(":/images/mac/filesave.png"));
	m_lpActionSave				= m_lpFileMenu->addAction(saveIcon, tr("&Save"), this, &cMainWindow::onFileSave);
	m_lpActionSave->setShortcut(QKeySequence::Save);
	m_lpActionSave->setEnabled(false);
	m_lpFileToolBar->addAction(m_lpActionSave);

	lpAction					= m_lpFileMenu->addAction(tr("Save &As..."), this, &cMainWindow::onFileSaveAs);
	lpAction->setPriority(QAction::LowPriority);
	m_lpFileMenu->addSeparator();

#ifndef QT_NO_PRINTER
	const QIcon	printIcon		= QIcon::fromTheme("document-print", QIcon(":/images/mac/fileprint.png"));
	lpAction					= m_lpFileMenu->addAction(printIcon, tr("&Print..."), this, &cMainWindow::onFilePrint);
	lpAction->setPriority(QAction::LowPriority);
	lpAction->setShortcut(QKeySequence::Print);
	m_lpFileToolBar->addAction(lpAction);

	const QIcon	filePrintIcon	= QIcon::fromTheme("fileprint", QIcon(":/images/mac/fileprint.png"));
	m_lpFileMenu->addAction(filePrintIcon, tr("Print Preview..."), this, &cMainWindow::onFilePrintPreview);

	const QIcon	exportPdfIcon	= QIcon::fromTheme("exportpdf", QIcon(":/images/mac/exportpdf.png"));
	lpAction					= m_lpFileMenu->addAction(exportPdfIcon, tr("&Export PDF..."), this, &cMainWindow::onFilePrintPdf);
	lpAction->setPriority(QAction::LowPriority);
	lpAction->setShortcut(Qt::CTRL + Qt::Key_D);
	m_lpFileToolBar->addAction(lpAction);

	m_lpFileMenu->addSeparator();
#endif

	lpAction					= m_lpFileMenu->addAction(tr("P&roperties..."), this, &cMainWindow::onFileProperties);
	lpAction->setPriority(QAction::LowPriority);
	m_lpFileMenu->addSeparator();

	for(int i = 0; i < MaxRecentFiles;i++)
	{
		m_lpActionRecentFile[i]	= new QAction(this);
		m_lpActionRecentFile[i]->setVisible(false);
		m_lpFileMenu->addAction(m_lpActionRecentFile[i]);
		connect(m_lpActionRecentFile[i], &QAction::triggered, this, &cMainWindow::openRecentFile);
	}
	m_lpSeparatorRecent			= m_lpFileMenu->addSeparator();
	m_lpSeparatorRecent->setVisible(false);

	lpAction					= m_lpFileMenu->addAction(tr("&Quit"), this, &QWidget::close);
	lpAction->setShortcut(Qt::CTRL + Qt::Key_Q);
}

void cMainWindow::createEditActions()
{
	m_lpEditMenu	= menuBar()->addMenu(tr("&Edit"));
	m_lpEditToolBar	= addToolBar(tr("Edit Actions"));

	const QIcon	undoIcon	= QIcon::fromTheme("edit-undo", QIcon(":/images/mac/editundo.png"));
	m_lpActionUndo			= m_lpEditMenu->addAction(undoIcon, tr("&Undo"));
	m_lpActionUndo->setShortcut(QKeySequence::Undo);
	m_lpEditToolBar->addAction(m_lpActionUndo);

	const QIcon redoIcon	= QIcon::fromTheme("edit-redo", QIcon(":/images/mac/editredo.png"));
	m_lpActionRedo			= m_lpEditMenu->addAction(redoIcon, tr("&Redo"));
	m_lpActionRedo->setPriority(QAction::LowPriority);
	m_lpActionRedo->setShortcut(QKeySequence::Redo);
	m_lpEditToolBar->addAction(m_lpActionRedo);
	m_lpEditMenu->addSeparator();

#ifndef QT_NO_CLIPBOARD
	const QIcon	cutIcon		= QIcon::fromTheme("edit-cut", QIcon(":/images/mac/editcut.png"));
	m_lpActionCut			= m_lpEditMenu->addAction(cutIcon, tr("Cu&t"));
	m_lpActionCut->setPriority(QAction::LowPriority);
	m_lpActionCut->setShortcut(QKeySequence::Cut);
	m_lpEditToolBar->addAction(m_lpActionCut);

	const QIcon	copyIcon	= QIcon::fromTheme("edit-copy", QIcon(":/images/mac/editcopy.png"));
	m_lpActionCopy			= m_lpEditMenu->addAction(copyIcon, tr("&Copy"));
	m_lpActionCopy->setPriority(QAction::LowPriority);
	m_lpActionCopy->setShortcut(QKeySequence::Copy);
	m_lpEditToolBar->addAction(m_lpActionCopy);

	const QIcon	pasteIcon	= QIcon::fromTheme("edit-paste", QIcon(":/images/mac/editpaste.png"));
	m_lpActionPaste			= m_lpEditMenu->addAction(pasteIcon, tr("&Paste"));
	m_lpActionPaste->setPriority(QAction::LowPriority);
	m_lpActionPaste->setShortcut(QKeySequence::Paste);
	m_lpEditToolBar->addAction(m_lpActionPaste);
	if(const QMimeData*	md	= QApplication::clipboard()->mimeData())
		m_lpActionPaste->setEnabled(md->hasText());
#endif
}

void cMainWindow::createTextActions()
{
	m_lpTextMenu	= menuBar()->addMenu(tr("F&ormat"));
	m_lpTextToolBar	= addToolBar(tr("Format Actions"));

	const QIcon boldIcon	= QIcon::fromTheme("format-text-bold", QIcon(":/images/mac/textbold.png"));
	m_lpActionTextBold		= m_lpTextMenu->addAction(boldIcon, tr("&Bold"));
	m_lpActionTextBold->setShortcut(Qt::CTRL + Qt::Key_B);
	m_lpActionTextBold->setPriority(QAction::LowPriority);
	QFont	bold;
	bold.setBold(true);
	m_lpActionTextBold->setFont(bold);
	m_lpTextToolBar->addAction(m_lpActionTextBold);
	m_lpActionTextBold->setCheckable(true);

	const QIcon	italicIcon	= QIcon::fromTheme("format-text-italic", QIcon(":/images/mac/textitalic.png"));
	m_lpActionTextItalic	= m_lpTextMenu->addAction(italicIcon, tr("&Italic"));
	m_lpActionTextItalic->setPriority(QAction::LowPriority);
	m_lpActionTextItalic->setShortcut(Qt::CTRL + Qt::Key_I);
	QFont	italic;
	italic.setItalic(true);
	m_lpActionTextItalic->setFont(italic);
	m_lpTextToolBar->addAction(m_lpActionTextItalic);
	m_lpActionTextItalic->setCheckable(true);

	const QIcon	underlineIcon	= QIcon::fromTheme("format-text-underline", QIcon(":/images/mac/textunder.png"));
	m_lpActionTextUnderline = m_lpTextMenu->addAction(underlineIcon, tr("&Underline"));
	m_lpActionTextUnderline->setShortcut(Qt::CTRL + Qt::Key_U);
	m_lpActionTextUnderline->setPriority(QAction::LowPriority);
	QFont underline;
	underline.setUnderline(true);
	m_lpActionTextUnderline->setFont(underline);
	m_lpTextToolBar->addAction(m_lpActionTextUnderline);
	m_lpActionTextUnderline->setCheckable(true);

	m_lpTextMenu->addSeparator();

	const QIcon	leftIcon	= QIcon::fromTheme("format-justify-left", QIcon(":/images/mac/textleft.png"));
	m_lpActionAlignLeft = new QAction(leftIcon, tr("&Left"), this);
	m_lpActionAlignLeft->setShortcut(Qt::CTRL + Qt::Key_L);
	m_lpActionAlignLeft->setCheckable(true);
	m_lpActionAlignLeft->setPriority(QAction::LowPriority);
	const QIcon	centerIcon	= QIcon::fromTheme("format-justify-center", QIcon(":/images/mac/textcenter.png"));
	m_lpActionAlignCenter = new QAction(centerIcon, tr("C&enter"), this);
	m_lpActionAlignCenter->setShortcut(Qt::CTRL + Qt::Key_E);
	m_lpActionAlignCenter->setCheckable(true);
	m_lpActionAlignCenter->setPriority(QAction::LowPriority);
	const QIcon	rightIcon	= QIcon::fromTheme("format-justify-right", QIcon(":/images/mac/textright.png"));
	m_lpActionAlignRight = new QAction(rightIcon, tr("&Right"), this);
	m_lpActionAlignRight->setShortcut(Qt::CTRL + Qt::Key_R);
	m_lpActionAlignRight->setCheckable(true);
	m_lpActionAlignRight->setPriority(QAction::LowPriority);
	const QIcon	fillIcon	= QIcon::fromTheme("format-justify-fill", QIcon(":/images/mac/textjustify.png"));
	m_lpActionAlignJustify = new QAction(fillIcon, tr("&Justify"), this);
	m_lpActionAlignJustify->setShortcut(Qt::CTRL + Qt::Key_J);
	m_lpActionAlignJustify->setCheckable(true);
	m_lpActionAlignJustify->setPriority(QAction::LowPriority);

	// Make sure the alignLeft  is always left of the alignRight
	m_lpAlignGroup	= new QActionGroup(this);

	if(QApplication::isLeftToRight())
	{
		m_lpAlignGroup->addAction(m_lpActionAlignLeft);
		m_lpAlignGroup->addAction(m_lpActionAlignCenter);
		m_lpAlignGroup->addAction(m_lpActionAlignRight);
	}
	else
	{
		m_lpAlignGroup->addAction(m_lpActionAlignRight);
		m_lpAlignGroup->addAction(m_lpActionAlignCenter);
		m_lpAlignGroup->addAction(m_lpActionAlignLeft);
	}
	m_lpAlignGroup->addAction(m_lpActionAlignJustify);

	m_lpTextToolBar->addActions(m_lpAlignGroup->actions());
	m_lpTextMenu->addActions(m_lpAlignGroup->actions());

	m_lpTextMenu->addSeparator();

	QPixmap pix(16, 16);
	pix.fill(Qt::black);
	m_lpActionTextColor = m_lpTextMenu->addAction(pix, tr("&Color..."));
	m_lpTextToolBar->addAction(m_lpActionTextColor);

	m_lpFormatToolBar = addToolBar(tr("Format Actions"));
	m_lpFormatToolBar->setAllowedAreas(Qt::TopToolBarArea | Qt::BottomToolBarArea);
	addToolBar(m_lpFormatToolBar);

	m_lpComboFont	= new QFontComboBox(m_lpFormatToolBar);
	m_lpFormatToolBar->addWidget(m_lpComboFont);
	m_focusException.append(m_lpComboFont);

	m_lpComboSize	= new QComboBox(m_lpFormatToolBar);
	m_lpComboSize->setObjectName("comboSize");
	m_lpFormatToolBar->addWidget(m_lpComboSize);
	m_lpComboSize->setEditable(true);

	const QList<int> standardSizes	= QFontDatabase::standardSizes();
	foreach(int size, standardSizes)
		m_lpComboSize->addItem(QString::number(size));
	m_lpComboSize->setCurrentIndex(standardSizes.indexOf(QApplication::font().pointSize()));
	m_focusException.append(m_lpComboSize);
}

void cMainWindow::createContextActions()
{
	m_lpActionPartAdd = new QAction(tr("add part"), this);
	m_lpActionPartAdd->setStatusTip(tr("add a new part"));
	connect(m_lpActionPartAdd, &QAction::triggered, this, &cMainWindow::onAddPart);

	m_lpActionPartEdit = new QAction(tr("edit part"), this);
	m_lpActionPartEdit->setStatusTip(tr("edit the part"));
	connect(m_lpActionPartEdit, &QAction::triggered, this, &cMainWindow::onEditPart);

	m_lpActionPartDelete = new QAction(tr("delete part"), this);
	m_lpActionPartDelete->setStatusTip(tr("delete the part"));
	connect(m_lpActionPartDelete, &QAction::triggered, this, &cMainWindow::onDeletePart);

	m_lpActionChapterAdd = new QAction(tr("add chapter"), this);
	m_lpActionChapterAdd->setStatusTip(tr("add a new chapter"));
	connect(m_lpActionChapterAdd, &QAction::triggered, this, &cMainWindow::onAddChapter);

	m_lpActionChapterEdit = new QAction(tr("edit chapter"), this);
	m_lpActionChapterEdit->setStatusTip(tr("edit the chapter"));
	connect(m_lpActionChapterEdit, &QAction::triggered, this, &cMainWindow::onEditChapter);

	m_lpActionChapterDelete = new QAction(tr("delete chapter"), this);
	m_lpActionChapterDelete->setStatusTip(tr("delete the chapter"));
	connect(m_lpActionChapterDelete, &QAction::triggered, this, &cMainWindow::onDeleteChapter);

	m_lpActionSceneAdd = new QAction(tr("add scene"), this);
	m_lpActionSceneAdd->setStatusTip(tr("add a new scene"));
	connect(m_lpActionSceneAdd, &QAction::triggered, this, &cMainWindow::onAddScene);

	m_lpActionSceneEdit = new QAction(tr("edit scene"), this);
	m_lpActionSceneEdit->setStatusTip(tr("edit the scene"));
	connect(m_lpActionSceneEdit, &QAction::triggered, this, &cMainWindow::onEditScene);

	m_lpActionSceneDelete = new QAction(tr("delete scene"), this);
	m_lpActionSceneDelete->setStatusTip(tr("delete the scene"));
	connect(m_lpActionSceneDelete, &QAction::triggered, this, &cMainWindow::onDeleteScene);

	m_lpActionCharacterAdd = new QAction(tr("add character"), this);
	m_lpActionCharacterAdd->setStatusTip(tr("add a new character"));
	connect(m_lpActionCharacterAdd, &QAction::triggered, this, &cMainWindow::onAddCharacter);

	m_lpActionCharacterEdit = new QAction(tr("edit character"), this);
	m_lpActionCharacterEdit->setStatusTip(tr("edit the character"));
	connect(m_lpActionCharacterEdit, &QAction::triggered, this, &cMainWindow::onEditCharacter);

	m_lpActionCharacterDelete = new QAction(tr("delete character"), this);
	m_lpActionCharacterDelete->setStatusTip(tr("delete the character"));
	connect(m_lpActionCharacterDelete, &QAction::triggered, this, &cMainWindow::onDeleteCharacter);

	m_lpActionPlaceAdd = new QAction(tr("add place"), this);
	m_lpActionPlaceAdd->setStatusTip(tr("add a new place"));
	connect(m_lpActionPlaceAdd, &QAction::triggered, this, &cMainWindow::onAddPlace);

	m_lpActionPlaceEdit = new QAction(tr("edit place"), this);
	m_lpActionPlaceEdit->setStatusTip(tr("edit the place"));
	connect(m_lpActionPlaceEdit, &QAction::triggered, this, &cMainWindow::onEditPlace);

	m_lpActionPlaceDelete = new QAction(tr("delete place"), this);
	m_lpActionPlaceDelete->setStatusTip(tr("delete the place"));
	connect(m_lpActionPlaceDelete, &QAction::triggered, this, &cMainWindow::onDeletePlace);

	m_lpActionObjectAdd = new QAction(tr("add object"), this);
	m_lpActionObjectAdd->setStatusTip(tr("add a new object"));
	connect(m_lpActionObjectAdd, &QAction::triggered, this, &cMainWindow::onAddObject);

	m_lpActionObjectEdit = new QAction(tr("edit object"), this);
	m_lpActionObjectEdit->setStatusTip(tr("edit the object"));
	connect(m_lpActionObjectEdit, &QAction::triggered, this, &cMainWindow::onEditObject);

	m_lpActionObjectDelete = new QAction(tr("delete object"), this);
	m_lpActionObjectDelete->setStatusTip(tr("delete the object"));
	connect(m_lpActionObjectDelete, &QAction::triggered, this, &cMainWindow::onDeleteObject);

	m_lpActionRechercheAdd = new QAction(tr("add recherche"), this);
	m_lpActionRechercheAdd->setStatusTip(tr("add a new recherche"));
	connect(m_lpActionRechercheAdd, &QAction::triggered, this, &cMainWindow::onAddRecherche);

	m_lpActionRechercheEdit = new QAction(tr("edit recherche"), this);
	m_lpActionRechercheEdit->setStatusTip(tr("edit the recherche"));
	connect(m_lpActionRechercheEdit, &QAction::triggered, this, &cMainWindow::onEditRecherche);

	m_lpActionRechercheDelete = new QAction(tr("delete recherche"), this);
	m_lpActionRechercheDelete->setStatusTip(tr("delete the recherche"));
	connect(m_lpActionRechercheDelete, &QAction::triggered, this, &cMainWindow::onDeleteRecherche);

	m_lpActionRechercheOpenLink	= new QAction(tr("open link"), this);
	m_lpActionRechercheOpenLink->setStatusTip(tr("open the link"));
	connect(m_lpActionRechercheOpenLink, &QAction::triggered, this, &cMainWindow::onOpenRechercheLink);
}

void cMainWindow::disableTextEdit()
{
	m_lpEditMenu->setEnabled(false);
	m_lpEditToolBar->setEnabled(false);
	m_lpTextMenu->setEnabled(false);
	m_lpTextToolBar->setEnabled(false);
	m_lpFormatToolBar->setEnabled(false);

	if(m_lpOldTextEdit)
		disconnectTextEdit();

	m_lpOldTextEdit	= 0;
}

void cMainWindow::prepareTextEdit(cTextEdit* lpTextEdit)
{
	m_lpEditMenu->setEnabled(true);
	m_lpEditToolBar->setEnabled(true);
	m_lpTextMenu->setEnabled(true);
	m_lpTextToolBar->setEnabled(true);
	m_lpFormatToolBar->setEnabled(true);

	if(m_lpOldTextEdit == lpTextEdit)
		return;

	if(m_lpOldTextEdit)
		disconnectTextEdit();

	connect(m_lpActionTextBold,				&QAction::triggered,			lpTextEdit,				&cTextEdit::onTextBold);
	connect(m_lpActionTextItalic,			&QAction::triggered,			lpTextEdit,				&cTextEdit::onTextItalic);
	connect(m_lpActionTextUnderline,		&QAction::triggered,			lpTextEdit,				&cTextEdit::onTextUnderline);

	connect(m_lpActionTextColor,			&QAction::triggered,			lpTextEdit,				&cTextEdit::onTextColor);

	connect(lpTextEdit->document(),			&cTextDocument::undoAvailable,	m_lpActionUndo,			&QAction::setEnabled);
	connect(lpTextEdit->document(),			&cTextDocument::redoAvailable,	m_lpActionRedo,			&QAction::setEnabled);
	m_lpActionUndo->setEnabled(lpTextEdit->document()->isUndoAvailable());
	m_lpActionRedo->setEnabled(lpTextEdit->document()->isRedoAvailable());

	connect(m_lpActionUndo,					&QAction::triggered,			lpTextEdit,				&cTextEdit::undo);
	connect(m_lpActionRedo,					&QAction::triggered,			lpTextEdit,				&cTextEdit::redo);

#ifndef QT_NO_CLIPBOARD
	m_lpActionCut->setEnabled(false);
	m_lpActionCopy->setEnabled(false);

	connect(QApplication::clipboard(),		&QClipboard::dataChanged,		this,					&cMainWindow::onClipboardDataChanged);

	connect(m_lpActionCut,					&QAction::triggered,			lpTextEdit,				&cTextEdit::cut);
	connect(m_lpActionCopy,					&QAction::triggered,			lpTextEdit,				&cTextEdit::copy);
	connect(m_lpActionPaste,				&QAction::triggered,			lpTextEdit,				&cTextEdit::paste);
#endif

	connect(m_lpAlignGroup,					&QActionGroup::triggered,		lpTextEdit,		&cTextEdit::onTextAlign);

	connect(m_lpComboFont,					QOverload<const QString &>::of(&QComboBox::activated),	lpTextEdit,	&cTextEdit::onTextFamily);
	connect(m_lpComboSize,					QOverload<const QString &>::of(&QComboBox::activated),	lpTextEdit,	&cTextEdit::onTextSize);

	connect(lpTextEdit,						&cTextEdit::fontChanged,		this,			&cMainWindow::onFontChanged);
	connect(lpTextEdit,						&cTextEdit::colorChanged,		this,			&cMainWindow::onColorChanged);
	connect(lpTextEdit,						&cTextEdit::alignmentChanged,	this,			&cMainWindow::onAlignmentChanged);

	m_lpOldTextEdit	= lpTextEdit;
}

void cMainWindow::disconnectTextEdit()
{
	if(m_lpOldTextEdit)
	{
		disconnect(m_lpActionTextBold,			&QAction::triggered,			m_lpOldTextEdit,		&cTextEdit::onTextBold);
		disconnect(m_lpActionTextItalic,		&QAction::triggered,			m_lpOldTextEdit,		&cTextEdit::onTextItalic);
		disconnect(m_lpActionTextUnderline,		&QAction::triggered,			m_lpOldTextEdit,		&cTextEdit::onTextUnderline);

		disconnect(m_lpActionTextColor,			&QAction::triggered,			m_lpOldTextEdit,		&cTextEdit::onTextColor);

		disconnect(m_lpOldTextEdit->document(),	&cTextDocument::undoAvailable,	m_lpActionUndo,			&QAction::setEnabled);
		disconnect(m_lpOldTextEdit->document(),	&cTextDocument::redoAvailable,	m_lpActionRedo,			&QAction::setEnabled);

		disconnect(m_lpActionUndo,				&QAction::triggered,			m_lpOldTextEdit,		&cTextEdit::undo);
		disconnect(m_lpActionRedo,				&QAction::triggered,			m_lpOldTextEdit,		&cTextEdit::redo);

#ifndef QT_NO_CLIPBOARD
		disconnect(QApplication::clipboard(),	&QClipboard::dataChanged,		this,					&cMainWindow::onClipboardDataChanged);

		disconnect(m_lpActionCut,				&QAction::triggered,			m_lpOldTextEdit,		&cTextEdit::cut);
		disconnect(m_lpActionCopy,				&QAction::triggered,			m_lpOldTextEdit,		&cTextEdit::copy);
		disconnect(m_lpActionPaste,				&QAction::triggered,			m_lpOldTextEdit,		&cTextEdit::paste);
#endif

		disconnect(m_lpAlignGroup,				&QActionGroup::triggered,		m_lpOldTextEdit,		&cTextEdit::onTextAlign);

		disconnect(m_lpComboFont,				QOverload<const QString &>::of(&QComboBox::activated),	m_lpOldTextEdit,	&cTextEdit::onTextFamily);
		disconnect(m_lpComboSize,				QOverload<const QString &>::of(&QComboBox::activated),	m_lpOldTextEdit,	&cTextEdit::onTextSize);

		disconnect(m_lpOldTextEdit,				&cTextEdit::fontChanged,		this,			&cMainWindow::onFontChanged);
		disconnect(m_lpOldTextEdit,				&cTextEdit::colorChanged,		this,			&cMainWindow::onColorChanged);
		disconnect(m_lpOldTextEdit,				&cTextEdit::alignmentChanged,	this,			&cMainWindow::onAlignmentChanged);
	}
}

void cMainWindow::updateWindowTitle()
{
	if(!m_lpStoryBook)
	{
		setWindowTitle("storyWriter");
		return;
	}

	QString	szTitle		= m_lpStoryBook->title();
	QString	szAuthor	= m_lpStoryBook->author();
	QString	szWindowTitle;
	if(szAuthor.isEmpty())
		szWindowTitle	= QString("\"%1\" - storyWriter").arg(szTitle);
	else
		szWindowTitle	= QString("\"%1\" by %2 - storyWriter").arg(szTitle).arg(szAuthor);

	if(m_bSomethingChanged)
		szWindowTitle.append(" *");

	m_lpActionSave->setEnabled(m_bSomethingChanged);

	setWindowTitle(szWindowTitle);
}

void cMainWindow::onTextEditGotFocus(cTextEdit* lpTextEdit)
{
	prepareTextEdit(lpTextEdit);
}

void cMainWindow::onTextEditLostFocus(cTextEdit* /*lpTextEdit*/)
{
}

void cMainWindow::onLineEditGotFocus(cLineEdit* /*lpLineEdit*/)
{
	disableTextEdit();
}

void cMainWindow::onLineEditLostFocus(cLineEdit* /*lpLineEdit*/)
{
}

void cMainWindow::onTreeViewGotFocus(cTreeView* /*lpTreeView*/)
{
	disableTextEdit();
}

void cMainWindow::onTreeViewLostFocus(cTreeView * /*lpTreeView*/)
{
}

void cMainWindow::onCheckBoxGotFocus(cCheckBox* /*lpCheckBox*/)
{
	disableTextEdit();
}

void cMainWindow::onCheckBoxLostFocus(cCheckBox* /*lpCheckBox*/)
{
}

void cMainWindow::onRadioButtonGotFocus(cRadioButton* /*lpRadioButton*/)
{
	disableTextEdit();
}

void cMainWindow::onRadioButtonLostFocus(cRadioButton* /*lpRadioButton*/)
{
}

void cMainWindow::onDateEditGotFocus(cDateEdit* /*lpDateEdit*/)
{
	disableTextEdit();
}

void cMainWindow::onDateEditLostFocus(cDateEdit* /*lpDateEdit*/)
{
}

void cMainWindow::onDoubleSpinBoxGotFocus(cDoubleSpinBox* /*lpDoubleSpinBox*/)
{
	disableTextEdit();
}

void cMainWindow::onDoubleSpinBoxLostFocus(cDoubleSpinBox* /*lpDoubleSpinBox*/)
{
}

void cMainWindow::onDateTimeEditGotFocus(cDateTimeEdit* /*lpDateTimeEdit*/)
{
	disableTextEdit();
}

void cMainWindow::onDateTimeEditLostFocus(cDateTimeEdit* /*lpDateTimeEdit*/)
{
}

void cMainWindow::onComboBoxGotFocus(cComboBox* /*lpComboBox*/)
{
	disableTextEdit();
}

void cMainWindow::onComboBoxLostFocus(cComboBox* /*lpComboBox*/)
{
}

void cMainWindow::onMainTabCurrentChanged(int /*index*/)
{
	if(m_bUpdatingTab)
		return;

	m_bUpdatingTab	= true;
	cWidget*		lpWidget	= (cWidget*)ui->m_lpMainTab->currentWidget();
	QMdiSubWindow*	lpWindow	= lpWidget->window();
	ui->m_lpMdiArea->setActiveSubWindow(lpWindow);
	m_bUpdatingTab	= false;
}

void cMainWindow::onMainTabTabCloseRequested(int index)
{
	if(m_bUpdatingTab)
		return;

	m_bUpdatingTab	= true;
	disconnectTextEdit();
	m_lpOldTextEdit	= 0;
	cWidget*		lpWidget	= (cWidget*)ui->m_lpMainTab->currentWidget();
	QMdiSubWindow*	lpWindow	= lpWidget->window();
	ui->m_lpMainTab->removeTab(index);
	ui->m_lpMdiArea->removeSubWindow(lpWindow);
	delete(lpWidget);
	m_bUpdatingTab	= false;
}

void cMainWindow::onMdiAreaSubWindowActivated(QMdiSubWindow *arg1)
{
	if(m_bUpdatingTab)
		return;

	m_bUpdatingTab	= true;

	for(int x = 0;x < ui->m_lpMainTab->count();x++)
	{
		cWidget*	lpWidget	= (cWidget*)ui->m_lpMainTab->widget(x);
		if(lpWidget->window() == arg1)
		{
			ui->m_lpMainTab->setCurrentIndex(x);
			m_bUpdatingTab	= false;
			return;
		}
	}
	m_bUpdatingTab	= false;
}

void cMainWindow::onSubWindowClosed(QWidget* lpSubWindow)
{
	if(m_bUpdatingTab)
		return;

	m_bUpdatingTab	= true;
	disconnectTextEdit();
	m_lpOldTextEdit	= 0;

	for(int x = 0;x < ui->m_lpMainTab->count();x++)
	{
		cWidget*	lpWidget	= (cWidget*)ui->m_lpMainTab->widget(x);
		if(lpWidget->widget() == lpSubWindow)
		{
			ui->m_lpMainTab->removeTab(x);
			m_bUpdatingTab	= false;
			return;
		}
	}
	m_bUpdatingTab	= false;
}

void cMainWindow::onOutlineDoubleClicked(const QModelIndex& index)
{
	QStandardItem*	lpItem		= m_lpOutlineModel->itemFromIndex(index);
	cPart*			lpPart		= qvariant_cast<cPart*>(lpItem->data());
	cChapter*		lpChapter	= qvariant_cast<cChapter*>(lpItem->data());
	cScene*			lpScene		= qvariant_cast<cScene*>(lpItem->data());

	if(lpPart)
		onShowPartWindow(lpPart);
	else if(lpChapter)
		onShowChapterWindow(lpChapter);
	else if(lpScene)
		onShowSceneWindow(lpScene);
	else
		QMessageBox::information(this, "DoubleClicked", "outline");
}

void cMainWindow::onCharacterDoubleClicked(const QModelIndex& index)
{
	QStandardItem*	lpItem		= m_lpCharacterModel->itemFromIndex(index);
	cCharacter*		lpCharacter	= qvariant_cast<cCharacter*>(lpItem->data());

	onShowCharacterWindow(lpCharacter);
}

void cMainWindow::onPlaceDoubleClicked(const QModelIndex& index)
{
	QStandardItem*	lpItem		= m_lpPlaceModel->itemFromIndex(index);
	cPlace*			lpPlace		= qvariant_cast<cPlace*>(lpItem->data());

	onShowPlaceWindow(lpPlace);
}

void cMainWindow::onObjectDoubleClicked(const QModelIndex& index)
{
	QStandardItem*	lpItem		= m_lpObjectModel->itemFromIndex(index);
	cObject*		lpObject	= qvariant_cast<cObject*>(lpItem->data());

	onShowObjectWindow(lpObject);
}

void cMainWindow::onRechercheDoubleClicked(const QModelIndex& index)
{
	QStandardItem*	lpItem		= m_lpRechercheModel->itemFromIndex(index);
	cRecherche*		lpRecherche	= qvariant_cast<cRecherche*>(lpItem->data());

	onShowRechercheWindow(lpRecherche);
}

void cMainWindow::onShowPropertiesWindow()
{
	for(int x = 0;x < ui->m_lpMainTab->count();x++)
	{
		cWidget*	lpWidget	= (cWidget*)ui->m_lpMainTab->widget(x);
		if(lpWidget->type() == cWidget::TYPE_properties)
		{
			ui->m_lpMainTab->setCurrentIndex(x);
			ui->m_lpMdiArea->setActiveSubWindow(lpWidget->window());
			m_bUpdatingTab	= false;
			return;
		}
	}

	cPropertiesWindow*		lpPropertiesWindow		= new cPropertiesWindow(this);
	lpPropertiesWindow->setBook(m_lpStoryBook->book());
	cWidget*			lpWidget1			= new cWidget(lpPropertiesWindow);
	lpWidget1->setWindow(ui->m_lpMdiArea->addSubWindow(lpPropertiesWindow));
	ui->m_lpMainTab->addTab((QWidget*)lpWidget1, lpPropertiesWindow->windowTitle());

	connect(lpPropertiesWindow,	&cPropertiesWindow::subWindowClosed,	this,	&cMainWindow::onSubWindowClosed);

	lpPropertiesWindow->show();
}

void cMainWindow::onShowPartWindow(cPart* lpPart)
{
	for(int x = 0;x < ui->m_lpMainTab->count();x++)
	{
		cWidget*	lpWidget	= (cWidget*)ui->m_lpMainTab->widget(x);
		if(lpWidget->type() == cWidget::TYPE_part)
		{
			cPartWindow*	lpPartWindow	= (cPartWindow*)lpWidget->widget();
			if(lpPartWindow->part() == lpPart)
			{
				ui->m_lpMainTab->setCurrentIndex(x);
				ui->m_lpMdiArea->setActiveSubWindow(lpWidget->window());
				m_bUpdatingTab	= false;
				return;
			}
		}
	}

	cPartWindow*		lpPartWindow		= new cPartWindow(this);
	lpPartWindow->setPart(lpPart, m_lpStoryBook->chapterList());
	cWidget*			lpWidget1			= new cWidget(lpPartWindow);
	lpWidget1->setWindow(ui->m_lpMdiArea->addSubWindow(lpPartWindow));
	ui->m_lpMainTab->addTab((QWidget*)lpWidget1, lpPartWindow->windowTitle());

	connect(lpPartWindow,	&cPartWindow::showChapterWindow,	this,	&cMainWindow::onShowChapterWindow);
	connect(lpPartWindow,	&cPartWindow::subWindowClosed,		this,	&cMainWindow::onSubWindowClosed);

	lpPartWindow->show();
}

void cMainWindow::onShowChapterWindow(cChapter* lpChapter)
{
	for(int x = 0;x < ui->m_lpMainTab->count();x++)
	{
		cWidget*	lpWidget	= (cWidget*)ui->m_lpMainTab->widget(x);
		if(lpWidget->type() == cWidget::TYPE_chapter)
		{
			cChapterWindow*	lpChapterWindow	= (cChapterWindow*)lpWidget->widget();
			if(lpChapterWindow->chapter() == lpChapter)
			{
				ui->m_lpMainTab->setCurrentIndex(x);
				ui->m_lpMdiArea->setActiveSubWindow(lpWidget->window());
				m_bUpdatingTab	= false;
				return;
			}
		}
	}

	cChapterWindow*		lpChapterWindow		= new cChapterWindow(this);
	lpChapterWindow->setChapter(lpChapter, m_lpStoryBook->sceneList());
	cWidget*			lpWidget1			= new cWidget(lpChapterWindow);
	lpWidget1->setWindow(ui->m_lpMdiArea->addSubWindow(lpChapterWindow));
	ui->m_lpMainTab->addTab((QWidget*)lpWidget1, lpChapterWindow->windowTitle());

	connect(lpChapterWindow,	&cChapterWindow::showSceneWindow,	this,	&cMainWindow::onShowSceneWindow);
	connect(lpChapterWindow,	&cChapterWindow::subWindowClosed,	this,	&cMainWindow::onSubWindowClosed);

	lpChapterWindow->show();
}

void cMainWindow::onShowSceneWindow(cScene* lpScene)
{
	for(int x = 0;x < ui->m_lpMainTab->count();x++)
	{
		cWidget*	lpWidget	= (cWidget*)ui->m_lpMainTab->widget(x);
		if(lpWidget->type() == cWidget::TYPE_scene)
		{
			cSceneWindow*	lpSceneWindow	= (cSceneWindow*)lpWidget->widget();
			if(lpSceneWindow->scene() == lpScene)
			{
				ui->m_lpMainTab->setCurrentIndex(x);
				ui->m_lpMdiArea->setActiveSubWindow(lpWidget->window());
				m_bUpdatingTab	= false;
				return;
			}
		}
	}

	cSceneWindow*		lpSceneWindow		= new cSceneWindow(this);
	lpSceneWindow->setScene(lpScene, m_lpStoryBook->characterList(), m_lpStoryBook->placeList(), m_lpStoryBook->objectList());

	cWidget*			lpWidget1			= new cWidget(lpSceneWindow);
	lpWidget1->setWindow(ui->m_lpMdiArea->addSubWindow(lpSceneWindow));
	ui->m_lpMainTab->addTab((QWidget*)lpWidget1, lpSceneWindow->windowTitle());

	connect(lpSceneWindow,	&cSceneWindow::showCharacterWindow,	this,	&cMainWindow::onShowCharacterWindow);
	connect(lpSceneWindow,	&cSceneWindow::showPlaceWindow,		this,	&cMainWindow::onShowPlaceWindow);
	connect(lpSceneWindow,	&cSceneWindow::showObjectWindow,	this,	&cMainWindow::onShowObjectWindow);

	connect(lpSceneWindow,	&cSceneWindow::subWindowClosed,		this,	&cMainWindow::onSubWindowClosed);

	lpSceneWindow->show();
}

void cMainWindow::onShowCharacterWindow(cCharacter* lpCharacter)
{
	for(int x = 0;x < ui->m_lpMainTab->count();x++)
	{
		cWidget*	lpWidget	= (cWidget*)ui->m_lpMainTab->widget(x);
		if(lpWidget->type() == cWidget::TYPE_character)
		{
			cCharacterWindow*	lpCharacterWindow	= (cCharacterWindow*)lpWidget->widget();
			if(lpCharacterWindow->character() == lpCharacter)
			{
				ui->m_lpMainTab->setCurrentIndex(x);
				ui->m_lpMdiArea->setActiveSubWindow(lpWidget->window());
				m_bUpdatingTab	= false;
				return;
			}
		}
	}

	cCharacterWindow*		lpCharacterWindow		= new cCharacterWindow(this);
	lpCharacterWindow->setCharacter(lpCharacter);
	cWidget*			lpWidget1			= new cWidget(lpCharacterWindow);
	lpWidget1->setWindow(ui->m_lpMdiArea->addSubWindow(lpCharacterWindow));
	ui->m_lpMainTab->addTab((QWidget*)lpWidget1, lpCharacterWindow->windowTitle());

	connect(lpCharacterWindow,	&cSceneWindow::subWindowClosed,		this,	&cMainWindow::onSubWindowClosed);

	lpCharacterWindow->show();
}

void cMainWindow::onShowPlaceWindow(cPlace* lpPlace)
{
	for(int x = 0;x < ui->m_lpMainTab->count();x++)
	{
		cWidget*	lpWidget	= (cWidget*)ui->m_lpMainTab->widget(x);
		if(lpWidget->type() == cWidget::TYPE_place)
		{
			cPlaceWindow*	lpPlaceWindow	= (cPlaceWindow*)lpWidget->widget();
			if(lpPlaceWindow->place() == lpPlace)
			{
				ui->m_lpMainTab->setCurrentIndex(x);
				ui->m_lpMdiArea->setActiveSubWindow(lpWidget->window());
				m_bUpdatingTab	= false;
				return;
			}
		}
	}

	cPlaceWindow*		lpPlaceWindow		= new cPlaceWindow(this);
	lpPlaceWindow->setPlace(lpPlace);
	cWidget*			lpWidget1			= new cWidget(lpPlaceWindow);
	lpWidget1->setWindow(ui->m_lpMdiArea->addSubWindow(lpPlaceWindow));
	ui->m_lpMainTab->addTab((QWidget*)lpWidget1, lpPlaceWindow->windowTitle());

	connect(lpPlaceWindow,	&cPlaceWindow::subWindowClosed,		this,	&cMainWindow::onSubWindowClosed);

	lpPlaceWindow->show();
}

void cMainWindow::onShowObjectWindow(cObject* lpObject)
{
	for(int x = 0;x < ui->m_lpMainTab->count();x++)
	{
		cWidget*	lpWidget	= (cWidget*)ui->m_lpMainTab->widget(x);
		if(lpWidget->type() == cWidget::TYPE_object)
		{
			cObjectWindow*	lpObjectWindow	= (cObjectWindow*)lpWidget->widget();
			if(lpObjectWindow->object() == lpObject)
			{
				ui->m_lpMainTab->setCurrentIndex(x);
				ui->m_lpMdiArea->setActiveSubWindow(lpWidget->window());
				m_bUpdatingTab	= false;
				return;
			}
		}
	}

	cObjectWindow*		lpObjectWindow		= new cObjectWindow(this);
	lpObjectWindow->setObject(lpObject);
	cWidget*			lpWidget1			= new cWidget(lpObjectWindow);
	lpWidget1->setWindow(ui->m_lpMdiArea->addSubWindow(lpObjectWindow));
	ui->m_lpMainTab->addTab((QWidget*)lpWidget1, lpObjectWindow->windowTitle());

	connect(lpObjectWindow,	&cObjectWindow::subWindowClosed,		this,	&cMainWindow::onSubWindowClosed);

	lpObjectWindow->show();
}

void cMainWindow::onShowRechercheWindow(cRecherche* lpRecherche)
{
	for(int x = 0;x < ui->m_lpMainTab->count();x++)
	{
		cWidget*	lpWidget	= (cWidget*)ui->m_lpMainTab->widget(x);
		if(lpWidget->type() == cWidget::TYPE_recherche)
		{
			cRechercheWindow*	lpRechercheWindow	= (cRechercheWindow*)lpWidget->widget();
			if(lpRechercheWindow->recherche() == lpRecherche)
			{
				ui->m_lpMainTab->setCurrentIndex(x);
				ui->m_lpMdiArea->setActiveSubWindow(lpWidget->window());
				m_bUpdatingTab	= false;
				return;
			}
		}
	}

	cRechercheWindow*		lpRechercheWindow		= new cRechercheWindow(this);
	lpRechercheWindow->setRecherche(lpRecherche);
	cWidget*			lpWidget1			= new cWidget(lpRechercheWindow);
	lpWidget1->setWindow(ui->m_lpMdiArea->addSubWindow(lpRechercheWindow));
	ui->m_lpMainTab->addTab((QWidget*)lpWidget1, lpRechercheWindow->windowTitle());

	connect(lpRechercheWindow,	&cRechercheWindow::showCharacterWindow,	this,	&cMainWindow::onShowCharacterWindow);
	connect(lpRechercheWindow,	&cRechercheWindow::showPlaceWindow,		this,	&cMainWindow::onShowPlaceWindow);
	connect(lpRechercheWindow,	&cRechercheWindow::showObjectWindow,	this,	&cMainWindow::onShowObjectWindow);

	connect(lpRechercheWindow,	&cRechercheWindow::subWindowClosed,		this,	&cMainWindow::onSubWindowClosed);

	lpRechercheWindow->show();
}

void cMainWindow::onOutlineContextMenu(const QPoint& pos)
{
	QMenu			menu(this);

	QStandardItem*	lpItem	= m_lpOutlineModel->itemFromIndex(ui->m_lpOutlineList->currentIndex());
	if(!lpItem)
	{
		menu.addAction(m_lpActionPartAdd);
	}
	else
	{
		cPart*			lpPart		= qvariant_cast<cPart*>(lpItem->data());
		cChapter*		lpChapter	= qvariant_cast<cChapter*>(lpItem->data());
		cScene*			lpScene		= qvariant_cast<cScene*>(lpItem->data());

		if(lpPart)
		{
			menu.addAction(m_lpActionPartAdd);
			menu.addAction(m_lpActionPartEdit);
			menu.addAction(m_lpActionPartDelete);
			menu.addSeparator();
			menu.addAction(m_lpActionChapterAdd);
		}
		else if(lpChapter)
		{
			menu.addAction(m_lpActionChapterAdd);
			menu.addAction(m_lpActionChapterEdit);
			menu.addAction(m_lpActionChapterDelete);
			menu.addSeparator();
			menu.addAction(m_lpActionSceneAdd);
		}
		else if(lpScene)
		{
			menu.addAction(m_lpActionSceneAdd);
			menu.addAction(m_lpActionSceneEdit);
			menu.addAction(m_lpActionSceneDelete);
		}
		else
			menu.addAction(m_lpActionPartAdd);
	}

	menu.exec(ui->m_lpOutlineList->mapToGlobal(pos));
}

void cMainWindow::onCharacterContextMenu(const QPoint& pos)
{
	QMenu			menu(this);

	QStandardItem*	lpItem	= m_lpCharacterModel->itemFromIndex(ui->m_lpCharacterList->currentIndex());
	if(!lpItem)
	{
		menu.addAction(m_lpActionCharacterAdd);
	}
	else
	{
		menu.addAction(m_lpActionCharacterAdd);
		menu.addAction(m_lpActionCharacterEdit);
		menu.addAction(m_lpActionCharacterDelete);
	}

	menu.exec(ui->m_lpCharacterList->mapToGlobal(pos));
}

void cMainWindow::onPlaceContextMenu(const QPoint& pos)
{
	QMenu			menu(this);

	QStandardItem*	lpItem	= m_lpPlaceModel->itemFromIndex(ui->m_lpPlaceList->currentIndex());
	if(!lpItem)
	{
		menu.addAction(m_lpActionPlaceAdd);
	}
	else
	{
		menu.addAction(m_lpActionPlaceAdd);
		menu.addAction(m_lpActionPlaceEdit);
		menu.addAction(m_lpActionPlaceDelete);
	}

	menu.exec(ui->m_lpPlaceList->mapToGlobal(pos));
}

void cMainWindow::onObjectContextMenu(const QPoint& pos)
{
	QMenu			menu(this);

	QStandardItem*	lpItem	= m_lpObjectModel->itemFromIndex(ui->m_lpObjectList->currentIndex());
	if(!lpItem)
	{
		menu.addAction(m_lpActionObjectAdd);
	}
	else
	{
		menu.addAction(m_lpActionObjectAdd);
		menu.addAction(m_lpActionObjectEdit);
		menu.addAction(m_lpActionObjectDelete);
	}

	menu.exec(ui->m_lpObjectList->mapToGlobal(pos));
}

void cMainWindow::onRechercheContextMenu(const QPoint& pos)
{
	QMenu			menu(this);

	QStandardItem*	lpItem	= m_lpRechercheModel->itemFromIndex(ui->m_lpRechercheList->currentIndex());
	if(!lpItem)
	{
		menu.addAction(m_lpActionRechercheAdd);
	}
	else
	{
		menu.addAction(m_lpActionRechercheAdd);
		menu.addAction(m_lpActionRechercheEdit);
		menu.addAction(m_lpActionRechercheDelete);
		menu.addSeparator();
		menu.addAction(m_lpActionRechercheOpenLink);
	}

	menu.exec(ui->m_lpRechercheList->mapToGlobal(pos));
}

void cMainWindow::onFileNew()
{
	if(m_bSomethingChanged)
	{
		switch(QMessageBox::question(this, tr("Save"), m_lpStoryBook->title() + tr(" has been changed.\nDo you want to save?"), QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel))
		{
		case QMessageBox::Yes:
			if(!onFileSave())
				return;
			break;
		case QMessageBox::No:
			break;
		case QMessageBox::Cancel:
			return;
		default:
			return;
		}
	}

	ui->m_lpMdiArea->closeAllSubWindows();

	if(m_lpStoryBook)
		delete m_lpStoryBook;

	m_lpStoryBook	= new cStoryBook;

	m_lpStoryBook->fillOutlineList(ui->m_lpOutlineList);
	m_lpStoryBook->fillCharacterList(ui->m_lpCharacterList);
	m_lpStoryBook->fillPlaceList(ui->m_lpPlaceList);
	m_lpStoryBook->fillObjectList(ui->m_lpObjectList);
	m_lpStoryBook->fillRechercheList(ui->m_lpRechercheList);

	updateWindowTitle();
}

void cMainWindow::onFileOpen()
{
	if(m_lpStoryBook)
	{
		if(m_bSomethingChanged)
		{
			switch(QMessageBox::question(this, tr("Save"), m_lpStoryBook->title() + tr(" has been changed.\nDo you want to save?"), QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel))
			{
			case QMessageBox::Yes:
				if(!onFileSave())
					return;
				break;
			case QMessageBox::No:
				break;
			case QMessageBox::Cancel:
				return;
			default:
				return;
			}
		}
	}

	QString	szProjectName	= getProjectLoadName();
	if(szProjectName.isEmpty())
		return;

	ui->m_lpMdiArea->closeAllSubWindows();

	if(m_lpStoryBook)
		delete m_lpStoryBook;

	m_lpStoryBook	= new cStoryBook(szProjectName);

	m_lpStoryBook->fillOutlineList(ui->m_lpOutlineList);
	m_lpStoryBook->fillCharacterList(ui->m_lpCharacterList);
	m_lpStoryBook->fillPlaceList(ui->m_lpPlaceList);
	m_lpStoryBook->fillObjectList(ui->m_lpObjectList);
	m_lpStoryBook->fillRechercheList(ui->m_lpRechercheList);

	setCurrentFile(szProjectName);
	updateWindowTitle();
}

bool cMainWindow::onFileSave()
{
	if(m_lpStoryBook)
	{
		if(m_lpStoryBook->project().isEmpty())
		{
			QString	szProjectName	= getProjectSaveName();
			if(szProjectName.isEmpty())
				return(false);

			QFile	file(szProjectName);
			if(file.exists())
				file.remove();

			if(!m_lpStoryBook->saveAs(szProjectName))
				return(false);

			setCurrentFile(szProjectName);
		}
		else
			m_lpStoryBook->save();
	}
	m_bSomethingChanged	= false;
	updateWindowTitle();

	return(true);
}

bool cMainWindow::onFileSaveAs()
{
	QString	szProjectName	= getProjectSaveName();
	if(szProjectName.isEmpty())
		return(false);

	QFile	file(szProjectName);
	if(file.exists())
		file.remove();

	if(!m_lpStoryBook->saveAs(szProjectName))
		return(false);

	m_bSomethingChanged	= false;
	setCurrentFile(szProjectName);
	updateWindowTitle();

	return(true);
}

void cMainWindow::onFilePrint()
{
}

void cMainWindow::onFilePrintPreview()
{
}

void cMainWindow::onFilePrintPdf()
{
}

void cMainWindow::onFileProperties()
{
	onShowPropertiesWindow();
}

void cMainWindow::onClipboardDataChanged()
{
#ifndef QT_NO_CLIPBOARD
	if(const QMimeData *md = QApplication::clipboard()->mimeData())
		m_lpActionPaste->setEnabled(md->hasText());
#endif
}

void cMainWindow::onFontChanged(const QFont& font)
{
	m_lpComboFont->setCurrentIndex(m_lpComboFont->findText(QFontInfo(font).family()));
	m_lpComboSize->setCurrentIndex(m_lpComboSize->findText(QString::number(font.pointSize())));
	m_lpActionTextBold->setChecked(font.bold());
	m_lpActionTextItalic->setChecked(font.italic());
	m_lpActionTextUnderline->setChecked(font.underline());
}

void cMainWindow::onColorChanged(const QColor& color)
{
	QPixmap pix(16, 16);
	pix.fill(color);
	m_lpActionTextColor->setIcon(pix);
}

void cMainWindow::onAlignmentChanged(const Qt::Alignment &alignment)
{
	if(alignment & Qt::AlignLeft)
		m_lpActionAlignLeft->setChecked(true);
	else if(alignment & Qt::AlignHCenter)
		m_lpActionAlignCenter->setChecked(true);
	else if(alignment & Qt::AlignRight)
		m_lpActionAlignRight->setChecked(true);
	else if(alignment & Qt::AlignJustify)
		m_lpActionAlignJustify->setChecked(true);
}

void cMainWindow::onAddPart()
{
	bool	bOK;
	QString	szPartName	= "";

	for(;;)
	{
		szPartName	= QInputDialog::getText(this, tr("New Part"), tr("Name:"), QLineEdit::Normal, "", &bOK);
		if(!bOK)
			return;

		if(szPartName.isEmpty())
		{
			QMessageBox::critical(this, tr("New Part"), tr("Part Name is empty."));
			bOK	= false;
		}
		else
			break;
	}

	if(bOK && !szPartName.isEmpty())
	{
		if(!m_lpStoryBook->addPart(szPartName))
		{
			QMessageBox::critical(this, tr("New Part"), tr("Part could not be created."));
			return;
		}

		m_lpStoryBook->fillOutlineList(ui->m_lpOutlineList);
		m_bSomethingChanged	= true;
		updateWindowTitle();
	}
}

void cMainWindow::onEditPart()
{
	QStandardItem*	lpItem	= m_lpOutlineModel->itemFromIndex(ui->m_lpOutlineList->currentIndex());
	if(!lpItem)
		return;

	cPart*			lpPart	= qvariant_cast<cPart*>(lpItem->data());

	if(!lpPart)
		return;

	onShowPartWindow(lpPart);
}

void cMainWindow::onDeletePart()
{
	QStandardItem*	lpItem		= m_lpOutlineModel->itemFromIndex(ui->m_lpOutlineList->currentIndex());
	if(!lpItem)
		return;

	cPart*			lpPart		= qvariant_cast<cPart*>(lpItem->data());

	if(!lpPart)
		return;

	if(m_lpStoryBook->hasChapter(lpPart))
	{
		QMessageBox::critical(this, "Delete Part", tr("There are still some chapter in this part.\nPlease delete them before deleting the part."));
		return;

	}

	if(QMessageBox::question(this, "Delete Part", tr("Are you sure you want to delete this part:<br>") + "<b>" + lpPart->name() + "</b>") != QMessageBox::Yes)
		return;

	lpPart->setDeleted(true);
	m_lpStoryBook->fillOutlineList(ui->m_lpOutlineList);
	m_bSomethingChanged	= true;
	updateWindowTitle();

	for(int x = 0;x < ui->m_lpMainTab->count();x++)
	{
		cWidget*	lpWidget	= (cWidget*)ui->m_lpMainTab->widget(x);
		if(lpWidget->type() == cWidget::TYPE_part)
		{
			cPartWindow*	lpPartWindow	= (cPartWindow*)lpWidget->widget();
			if(lpPartWindow->part() == lpPart)
			{
				onMainTabTabCloseRequested(x);
				return;
			}
		}
	}
}

void cMainWindow::onAddChapter()
{
	bool			bOK;
	QString			szChapterName	= "";
	QStandardItem*	lpItem			= m_lpOutlineModel->itemFromIndex(ui->m_lpOutlineList->currentIndex());
	if(!lpItem)
		return;

	cPart*			lpPart			= qvariant_cast<cPart*>(lpItem->data());
	if(!lpPart)
	{
		lpItem	= lpItem->parent();
		lpPart	= qvariant_cast<cPart*>(lpItem->data());

		if(!lpPart)
			return;
	}

	for(;;)
	{
		szChapterName	= QInputDialog::getText(this, tr("New Chapter"), tr("Name:"), QLineEdit::Normal, "", &bOK);
		if(!bOK)
			return;

		if(szChapterName.isEmpty())
		{
			QMessageBox::critical(this, tr("New Chapter"), tr("Chapter Name is empty."));
			bOK	= false;
		}
		else
			break;
	}

	if(bOK && !szChapterName.isEmpty())
	{
		if(!m_lpStoryBook->addChapter(lpPart, szChapterName))
		{
			QMessageBox::critical(this, tr("New Chapter"), tr("Chapter could not be created."));
			return;
		}

		m_lpStoryBook->fillOutlineList(ui->m_lpOutlineList);
		m_bSomethingChanged	= true;
		updateWindowTitle();
	}
}

void cMainWindow::onEditChapter()
{
	QStandardItem*	lpItem		= m_lpOutlineModel->itemFromIndex(ui->m_lpOutlineList->currentIndex());
	if(!lpItem)
		return;

	cChapter*		lpChapter	= qvariant_cast<cChapter*>(lpItem->data());

	if(!lpChapter)
		return;

	onShowChapterWindow(lpChapter);
}

void cMainWindow::onDeleteChapter()
{
	QStandardItem*	lpItem		= m_lpOutlineModel->itemFromIndex(ui->m_lpOutlineList->currentIndex());
	if(!lpItem)
		return;

	cChapter*		lpChapter	= qvariant_cast<cChapter*>(lpItem->data());

	if(!lpChapter)
		return;

	if(m_lpStoryBook->hasScene(lpChapter))
	{
		QMessageBox::critical(this, "Delete Chapter", tr("There are still some scenes in this chapter.\nPlease delete them before deleting the chapter."));
		return;

	}

	if(QMessageBox::question(this, "Delete Chapter", tr("Are you sure you want to delete this chapter:<br>") + "<b>" + lpChapter->name() + "</b>" + tr("<br>from part <br>") + "<b>" + lpChapter->part()->name() + "</b>") != QMessageBox::Yes)
		return;

	lpChapter->setDeleted(true);
	m_lpStoryBook->fillOutlineList(ui->m_lpOutlineList);
	m_bSomethingChanged	= true;
	updateWindowTitle();

	for(int x = 0;x < ui->m_lpMainTab->count();x++)
	{
		cWidget*	lpWidget	= (cWidget*)ui->m_lpMainTab->widget(x);
		if(lpWidget->type() == cWidget::TYPE_chapter)
		{
			cChapterWindow*	lpChapterWindow	= (cChapterWindow*)lpWidget->widget();
			if(lpChapterWindow->chapter() == lpChapter)
			{
				onMainTabTabCloseRequested(x);
				return;
			}
		}
	}
}

void cMainWindow::onAddScene()
{
	bool			bOK;
	QString			szSceneName		= "";
	QStandardItem*	lpItem			= m_lpOutlineModel->itemFromIndex(ui->m_lpOutlineList->currentIndex());
	if(!lpItem)
		return;

	cChapter*		lpChapter		= qvariant_cast<cChapter*>(lpItem->data());
	if(!lpChapter)
	{
		lpItem		= lpItem->parent();
		lpChapter	= qvariant_cast<cChapter*>(lpItem->data());

		if(!lpChapter)
		{
			lpItem		= lpItem->parent();
			lpChapter	= qvariant_cast<cChapter*>(lpItem->data());

			if(!lpChapter)
				return;
		}
	}

	for(;;)
	{
		szSceneName	= QInputDialog::getText(this, tr("New Scene"), tr("Name:"), QLineEdit::Normal, "", &bOK);
		if(!bOK)
			return;

		if(szSceneName.isEmpty())
		{
			QMessageBox::critical(this, tr("New Scene"), tr("Scene Name is empty."));
			bOK	= false;
		}
		else
			break;
	}

	if(bOK && !szSceneName.isEmpty())
	{
		if(!m_lpStoryBook->addScene(lpChapter, szSceneName))
		{
			QMessageBox::critical(this, tr("New Scene"), tr("Scene could not be created."));
			return;
		}

		m_lpStoryBook->fillOutlineList(ui->m_lpOutlineList);
		m_bSomethingChanged	= true;
		updateWindowTitle();
	}
}

void cMainWindow::onEditScene()
{
	QStandardItem*	lpItem	= m_lpOutlineModel->itemFromIndex(ui->m_lpOutlineList->currentIndex());
	if(!lpItem)
		return;

	cScene*			lpScene	= qvariant_cast<cScene*>(lpItem->data());

	if(!lpScene)
		return;

	onShowSceneWindow(lpScene);
}

void cMainWindow::onDeleteScene()
{
	QStandardItem*	lpItem	= m_lpOutlineModel->itemFromIndex(ui->m_lpOutlineList->currentIndex());
	if(!lpItem)
		return;

	cScene*			lpScene	= qvariant_cast<cScene*>(lpItem->data());

	if(!lpScene)
		return;

	if(QMessageBox::question(this, "Delete Scene", tr("Are you sure you want to delete this scene:<br>") + "<b>" + lpScene->name() + "</b>" + tr("<br>from chapter <br>") + "<b>" + lpScene->chapter()->name() + "</b>") != QMessageBox::Yes)
		return;

	lpScene->setDeleted(true);
	m_lpStoryBook->fillOutlineList(ui->m_lpOutlineList);
	m_bSomethingChanged	= true;
	updateWindowTitle();

	for(int x = 0;x < ui->m_lpMainTab->count();x++)
	{
		cWidget*	lpWidget	= (cWidget*)ui->m_lpMainTab->widget(x);
		if(lpWidget->type() == cWidget::TYPE_scene)
		{
			cSceneWindow*	lpSceneWindow	= (cSceneWindow*)lpWidget->widget();
			if(lpSceneWindow->scene() == lpScene)
			{
				onMainTabTabCloseRequested(x);
				return;
			}
		}
	}
}

void cMainWindow::onAddCharacter()
{
	bool	bOK;
	QString	szCharacterName	= "";

	for(;;)
	{
		szCharacterName	= QInputDialog::getText(this, tr("New Character"), tr("Name:"), QLineEdit::Normal, "", &bOK);
		if(!bOK)
			return;

		if(szCharacterName.isEmpty())
		{
			QMessageBox::critical(this, tr("New Character"), tr("Character Name is empty."));
			bOK	= false;
		}
		else
			break;
	}

	if(bOK && !szCharacterName.isEmpty())
	{
		if(!m_lpStoryBook->addCharacter(szCharacterName))
		{
			QMessageBox::critical(this, tr("New Character"), tr("Character could not be created."));
			return;
		}

		m_lpStoryBook->fillCharacterList(ui->m_lpCharacterList);
		m_bSomethingChanged	= true;
		updateWindowTitle();
	}
}

void cMainWindow::onEditCharacter()
{
	QStandardItem*	lpItem		= m_lpCharacterModel->itemFromIndex(ui->m_lpCharacterList->currentIndex());
	if(!lpItem)
		return;

	cCharacter*		lpCharacter	= qvariant_cast<cCharacter*>(lpItem->data());

	if(!lpCharacter)
		return;

	onShowCharacterWindow(lpCharacter);
}

void cMainWindow::onDeleteCharacter()
{
	QStandardItem*	lpItem		= m_lpCharacterModel->itemFromIndex(ui->m_lpCharacterList->currentIndex());
	if(!lpItem)
		return;

	cCharacter*		lpCharacter	= qvariant_cast<cCharacter*>(lpItem->data());

	if(!lpCharacter)
		return;

	if(m_lpStoryBook->characterInUse(lpCharacter))
	{
		QMessageBox::critical(this, "Delete Character", tr("This character is still in use.\nPlease delete the usage before deleting the character."));
		return;

	}

	if(QMessageBox::question(this, "Delete Character", tr("Are you sure you want to delete this character:<br>") + "<b>" + lpCharacter->name() + "</b>?") != QMessageBox::Yes)
		return;

	lpCharacter->setDeleted(true);
	m_lpStoryBook->fillCharacterList(ui->m_lpCharacterList);
	m_bSomethingChanged	= true;
	updateWindowTitle();

	for(int x = 0;x < ui->m_lpMainTab->count();x++)
	{
		cWidget*	lpWidget	= (cWidget*)ui->m_lpMainTab->widget(x);
		if(lpWidget->type() == cWidget::TYPE_character)
		{
			cCharacterWindow*	lpCharacterWindow	= (cCharacterWindow*)lpWidget->widget();
			if(lpCharacterWindow->character() == lpCharacter)
			{
				onMainTabTabCloseRequested(x);
				return;
			}
		}
	}
}

void cMainWindow::onAddPlace()
{
	bool	bOK;
	QString	szPlaceName	= "";

	for(;;)
	{
		szPlaceName	= QInputDialog::getText(this, tr("New Place"), tr("Name:"), QLineEdit::Normal, "", &bOK);
		if(!bOK)
			return;

		if(szPlaceName.isEmpty())
		{
			QMessageBox::critical(this, tr("New Place"), tr("Place Name is empty."));
			bOK	= false;
		}
		else
			break;
	}

	if(bOK && !szPlaceName.isEmpty())
	{
		if(!m_lpStoryBook->addPlace(szPlaceName))
		{
			QMessageBox::critical(this, tr("New Place"), tr("Place could not be created."));
			return;
		}

		m_lpStoryBook->fillPlaceList(ui->m_lpPlaceList);
		m_bSomethingChanged	= true;
		updateWindowTitle();
	}
}

void cMainWindow::onEditPlace()
{
	QStandardItem*	lpItem	= m_lpPlaceModel->itemFromIndex(ui->m_lpPlaceList->currentIndex());
	if(!lpItem)
		return;

	cPlace*			lpPlace	= qvariant_cast<cPlace*>(lpItem->data());

	if(!lpPlace)
		return;

	onShowPlaceWindow(lpPlace);
}

void cMainWindow::onDeletePlace()
{
	QStandardItem*	lpItem		= m_lpPlaceModel->itemFromIndex(ui->m_lpPlaceList->currentIndex());
	if(!lpItem)
		return;

	cPlace*			lpPlace		= qvariant_cast<cPlace*>(lpItem->data());

	if(!lpPlace)
		return;

	if(m_lpStoryBook->placeInUse(lpPlace))
	{
		QMessageBox::critical(this, "Delete Place", tr("This place is still in use.\nPlease delete the usage before deleting the place."));
		return;

	}

	if(QMessageBox::question(this, "Delete Place", tr("Are you sure you want to delete this place:<br>") + "<b>" + lpPlace->name() + "</b>?") != QMessageBox::Yes)
		return;

	lpPlace->setDeleted(true);
	m_lpStoryBook->fillPlaceList(ui->m_lpPlaceList);
	m_bSomethingChanged	= true;
	updateWindowTitle();

	for(int x = 0;x < ui->m_lpMainTab->count();x++)
	{
		cWidget*	lpWidget	= (cWidget*)ui->m_lpMainTab->widget(x);
		if(lpWidget->type() == cWidget::TYPE_place)
		{
			cPlaceWindow*	lpPlaceWindow	= (cPlaceWindow*)lpWidget->widget();
			if(lpPlaceWindow->place() == lpPlace)
			{
				onMainTabTabCloseRequested(x);
				return;
			}
		}
	}
}

void cMainWindow::onAddObject()
{
	bool	bOK;
	QString	szObjectName	= "";

	for(;;)
	{
		szObjectName	= QInputDialog::getText(this, tr("New Object"), tr("Name:"), QLineEdit::Normal, "", &bOK);
		if(!bOK)
			return;

		if(szObjectName.isEmpty())
		{
			QMessageBox::critical(this, tr("New Object"), tr("Object Name is empty."));
			bOK	= false;
		}
		else
			break;
	}

	if(bOK && !szObjectName.isEmpty())
	{
		if(!m_lpStoryBook->addObject(szObjectName))
		{
			QMessageBox::critical(this, tr("New Object"), tr("Object could not be created."));
			return;
		}

		m_lpStoryBook->fillObjectList(ui->m_lpObjectList);
		m_bSomethingChanged	= true;
		updateWindowTitle();
	}
}

void cMainWindow::onEditObject()
{
	QStandardItem*	lpItem		= m_lpObjectModel->itemFromIndex(ui->m_lpObjectList->currentIndex());
	if(!lpItem)
		return;

	cObject*		lpObject	= qvariant_cast<cObject*>(lpItem->data());

	if(!lpObject)
		return;

	onShowObjectWindow(lpObject);
}

void cMainWindow::onDeleteObject()
{
	QStandardItem*	lpItem		= m_lpObjectModel->itemFromIndex(ui->m_lpObjectList->currentIndex());
	if(!lpItem)
		return;

	cObject*		lpObject	= qvariant_cast<cObject*>(lpItem->data());

	if(!lpObject)
		return;

	if(m_lpStoryBook->objectInUse(lpObject))
	{
		QMessageBox::critical(this, "Delete Object", tr("This object is still in use.\nPlease delete the usage before deleting the object."));
		return;

	}

	if(QMessageBox::question(this, "Delete Object", tr("Are you sure you want to delete this object:<br>") + "<b>" + lpObject->name() + "</b>?") != QMessageBox::Yes)
		return;

	lpObject->setDeleted(true);
	m_lpStoryBook->fillObjectList(ui->m_lpObjectList);
	m_bSomethingChanged	= true;
	updateWindowTitle();

	for(int x = 0;x < ui->m_lpMainTab->count();x++)
	{
		cWidget*	lpWidget	= (cWidget*)ui->m_lpMainTab->widget(x);
		if(lpWidget->type() == cWidget::TYPE_object)
		{
			cObjectWindow*	lpObjectWindow	= (cObjectWindow*)lpWidget->widget();
			if(lpObjectWindow->object() == lpObject)
			{
				onMainTabTabCloseRequested(x);
				return;
			}
		}
	}
}

void cMainWindow::onAddRecherche()
{
	bool	bOK;
	QString	szRechercheName	= "";

	for(;;)
	{
		szRechercheName	= QInputDialog::getText(this, tr("New Recherche"), tr("Name:"), QLineEdit::Normal, "", &bOK);
		if(!bOK)
			return;

		if(szRechercheName.isEmpty())
		{
			QMessageBox::critical(this, tr("New Recherche"), tr("Recherche Name is empty."));
			bOK	= false;
		}
		else
			break;
	}

	if(bOK && !szRechercheName.isEmpty())
	{
		if(!m_lpStoryBook->addRecherche(szRechercheName))
		{
			QMessageBox::critical(this, tr("New Recherche"), tr("Recherche could not be created."));
			return;
		}

		m_lpStoryBook->fillRechercheList(ui->m_lpRechercheList);
		m_bSomethingChanged	= true;
		updateWindowTitle();
	}
}

void cMainWindow::onEditRecherche()
{
	QStandardItem*	lpItem		= m_lpRechercheModel->itemFromIndex(ui->m_lpRechercheList->currentIndex());
	if(!lpItem)
		return;

	cRecherche*		lpRecherche	= qvariant_cast<cRecherche*>(lpItem->data());

	if(!lpRecherche)
		return;

	onShowRechercheWindow(lpRecherche);
}

void cMainWindow::onDeleteRecherche()
{
	QStandardItem*	lpItem		= m_lpRechercheModel->itemFromIndex(ui->m_lpRechercheList->currentIndex());
	if(!lpItem)
		return;

	cRecherche*		lpRecherche	= qvariant_cast<cRecherche*>(lpItem->data());

	if(!lpRecherche)
		return;

	if(m_lpStoryBook->rechercheInUse(lpRecherche))
	{
		QMessageBox::critical(this, "Delete Recherche", tr("This recherche is still in use.\nPlease delete the usage before deleting the recherche."));
		return;

	}

	if(QMessageBox::question(this, "Delete Recherche", tr("Are you sure you want to delete this recherche:<br>") + "<b>" + lpRecherche->name() + "</b>?") != QMessageBox::Yes)
		return;

	lpRecherche->setDeleted(true);
	m_lpStoryBook->fillRechercheList(ui->m_lpRechercheList);
	m_bSomethingChanged	= true;
	updateWindowTitle();

	for(int x = 0;x < ui->m_lpMainTab->count();x++)
	{
		cWidget*	lpWidget	= (cWidget*)ui->m_lpMainTab->widget(x);
		if(lpWidget->type() == cWidget::TYPE_recherche)
		{
			cRechercheWindow*	lpRechercheWindow	= (cRechercheWindow*)lpWidget->widget();
			if(lpRechercheWindow->recherche() == lpRecherche)
			{
				onMainTabTabCloseRequested(x);
				return;
			}
		}
	}
}

void cMainWindow::onOpenRechercheLink()
{
	QStandardItem*	lpItem		= m_lpRechercheModel->itemFromIndex(ui->m_lpRechercheList->currentIndex());
	if(!lpItem)
		return;

	cRecherche*		lpRecherche	= qvariant_cast<cRecherche*>(lpItem->data());

	if(!lpRecherche)
		return;

	QString			szLink		= lpRecherche->link();

	if(szLink.isEmpty())
		return;

	QDesktopServices::openUrl(QUrl(szLink));
}

QString cMainWindow::getProjectLoadName()
{
	QString		szPath	= m_szOldPath;

	QString		szProjectName	= QFileDialog::getOpenFileName(this, tr("Save Project"), m_szOldPath, tr("StoryWriter Files (*.storyWriter)"));
	QFileInfo	fileInfo(szProjectName);
	m_szOldPath	= fileInfo.absolutePath();

	return(szProjectName);
}

QString cMainWindow::getProjectSaveName(const QString& szFileName)
{
	QString		szPath	= szFileName;

	if(szPath.isEmpty())
		szPath	= m_szOldPath;

	QString		szProjectName	= QFileDialog::getSaveFileName(this, tr("Save Project"), m_szOldPath, tr("StoryWriter Files (*.storyWriter)"));
	QFileInfo	fileInfo(szProjectName);
	m_szOldPath	= fileInfo.absolutePath();

	return(szProjectName);
}

void cMainWindow::setCurrentFile(const QString& fileName)
{
	QSettings	settings;
	QStringList	files	= settings.value("file/recentFiles").toStringList();
	files.removeAll(fileName);
	files.prepend(fileName);
	while(files.size() > MaxRecentFiles)
		files.removeLast();

	settings.setValue("file/recentFiles", files);

	updateRecentFileActions();
}

void cMainWindow::updateRecentFileActions()
{
	QSettings	settings;
	QStringList	files			= settings.value("file/recentFiles").toStringList();

	int			numRecentFiles	= qMin(files.size(), (int)MaxRecentFiles);

	for(int i = 0; i < numRecentFiles; i++)
	{
		QString	text	= tr("&%1 %2").arg(i + 1).arg(QFileInfo(files[i]).fileName());
		m_lpActionRecentFile[i]->setText(text);
		m_lpActionRecentFile[i]->setData(files[i]);
		m_lpActionRecentFile[i]->setVisible(true);
	}

	for(int j = numRecentFiles; j < MaxRecentFiles; j++)
		m_lpActionRecentFile[j]->setVisible(false);

	m_lpSeparatorRecent->setVisible(numRecentFiles > 0);
}

void cMainWindow::openRecentFile()
{
	QAction*	lpAction	= qobject_cast<QAction*>(sender());
	if(lpAction)
	{
		if(m_lpStoryBook)
		{
			if(m_bSomethingChanged)
			{
				switch(QMessageBox::question(this, tr("Save"), m_lpStoryBook->title() + tr(" has been changed.\nDo you want to save?"), QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel))
				{
				case QMessageBox::Yes:
					if(!onFileSave())
						return;
					break;
				case QMessageBox::No:
					break;
				case QMessageBox::Cancel:
					return;
				default:
					return;
				}
			}
		}

		QString	szProjectName	= lpAction->data().toString();
		if(szProjectName.isEmpty())
			return;

		delete m_lpStoryBook;

		m_lpStoryBook	= new cStoryBook(szProjectName);

		m_lpStoryBook->fillOutlineList(ui->m_lpOutlineList);
		m_lpStoryBook->fillCharacterList(ui->m_lpCharacterList);
		m_lpStoryBook->fillPlaceList(ui->m_lpPlaceList);
		m_lpStoryBook->fillObjectList(ui->m_lpObjectList);
		m_lpStoryBook->fillRechercheList(ui->m_lpRechercheList);

		setCurrentFile(szProjectName);
		updateWindowTitle();
	}
}
