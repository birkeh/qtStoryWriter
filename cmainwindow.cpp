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

#include "coptionsdialog.h"

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

#include <QMenu>


QDataStream&	operator<<(QDataStream& out, cPart* const &rhs)
{
	out.writeRawData(reinterpret_cast<const char*>(&rhs), sizeof(rhs));
	return out;
}

QDataStream&	operator>>(QDataStream& in, cPart* &rhs)
{
	in.readRawData(reinterpret_cast<char*>(&rhs), sizeof(rhs));
	return in;
}

QDataStream&	operator<<(QDataStream& out, cChapter* const &rhs)
{
	out.writeRawData(reinterpret_cast<const char*>(&rhs), sizeof(rhs));
	return out;
}

QDataStream&	operator>>(QDataStream& in, cChapter* &rhs)
{
	in.readRawData(reinterpret_cast<char*>(&rhs), sizeof(rhs));
	return in;
}

QDataStream&	operator<<(QDataStream& out, cScene* const &rhs)
{
	out.writeRawData(reinterpret_cast<const char*>(&rhs), sizeof(rhs));
	return out;
}

QDataStream&	operator>>(QDataStream& in, cScene* &rhs)
{
	in.readRawData(reinterpret_cast<char*>(&rhs), sizeof(rhs));
	return in;
}

cMainWindow::cMainWindow(cSplashScreen *lpSplashScreen, QTranslator *lpTranslator, QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::cMainWindow),
	m_lpSplashScreen(lpSplashScreen),
	m_lpTranslator(lpTranslator),
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
	m_lpToolsMenu(0),
	m_lpWindowMenu(0),
	m_lpHelpMenu(0),
	m_lpFileToolBar(0),
	m_lpEditToolBar(0),
	m_lpTextToolBar(0),
	m_lpFormatToolBar(0),
	m_lpViewToolBar(0),
	m_lpOldTextEdit(0),
	m_lpOptionsDialog(0)
{
	qRegisterMetaTypeStreamOperators<cPart*>("cPart*");
	qRegisterMetaTypeStreamOperators<cChapter*>("cChapter*");
	qRegisterMetaTypeStreamOperators<cScene*>("cScene*");

	initUI();
	createActions();
	onLanguageChanged();

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
	return(m_lpAlignLeftAction);
}

QAction* cMainWindow::actionAlignCenter()
{
	return(m_lpAlignCenterAction);
}

QAction* cMainWindow::actionAlignRight()
{
	return(m_lpAlignRightAction);
}

QAction* cMainWindow::actionAlignJustify()
{
	return(m_lpAlignJustifyAction);
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

	QIcon::setThemeName("TangoMFK");

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
	createToolsActions();
	createWindowActions();
	createHelpActions();

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

	connect(ui->m_lpOutlineList,	&cTreeView::dropped,					this,	&cMainWindow::onOutlineDropped);
}

void cMainWindow::createFileActions()
{
	m_lpFileMenu				= menuBar()->addMenu(tr("&File"));
	m_lpFileToolBar				= addToolBar(tr("File Actions"));

	const QIcon	newIcon			= QIcon::fromTheme("document-new");
	m_lpFileNewAction			= m_lpFileMenu->addAction(newIcon, tr("&New"), this, &cMainWindow::onFileNew);
	m_lpFileToolBar->addAction(m_lpFileNewAction);
	m_lpFileNewAction->setPriority(QAction::LowPriority);
	m_lpFileNewAction->setShortcut(QKeySequence::New);

	const QIcon	openIcon		= QIcon::fromTheme("document-open");
	m_lpFileOpenAction			= m_lpFileMenu->addAction(openIcon, tr("&Open..."), this, &cMainWindow::onFileOpen);
	m_lpFileOpenAction->setShortcut(QKeySequence::Open);
	m_lpFileToolBar->addAction(m_lpFileOpenAction);

	m_lpFileMenu->addSeparator();

	const QIcon	saveIcon		= QIcon::fromTheme("document-save");
	m_lpFileSaveAction			= m_lpFileMenu->addAction(saveIcon, tr("&Save"), this, &cMainWindow::onFileSave);
	m_lpFileSaveAction->setShortcut(QKeySequence::Save);
	m_lpFileSaveAction->setEnabled(false);
	m_lpFileToolBar->addAction(m_lpFileSaveAction);

	m_lpFileSaveAsAction		= m_lpFileMenu->addAction(tr("Save &As..."), this, &cMainWindow::onFileSaveAs);
	m_lpFileSaveAsAction->setPriority(QAction::LowPriority);
	m_lpFileMenu->addSeparator();

#ifndef QT_NO_PRINTER
	const QIcon	printIcon		= QIcon::fromTheme("document-print");
	m_lpFilePrintAction			= m_lpFileMenu->addAction(printIcon, tr("&Print..."), this, &cMainWindow::onFilePrint);
	m_lpFilePrintAction->setPriority(QAction::LowPriority);
	m_lpFilePrintAction->setShortcut(QKeySequence::Print);
	m_lpFileToolBar->addAction(m_lpFilePrintAction);

	const QIcon	filePrintIcon	= QIcon::fromTheme("document-print");
	m_lpFilePrintPreviewAction	= m_lpFileMenu->addAction(filePrintIcon, tr("Print Preview..."), this, &cMainWindow::onFilePrintPreview);

	const QIcon	exportPdfIcon	= QIcon::fromTheme("document-pdf");
	m_lpFileExportPDFAction		= m_lpFileMenu->addAction(exportPdfIcon, tr("&Export PDF..."), this, &cMainWindow::onFilePrintPdf);
	m_lpFileExportPDFAction->setPriority(QAction::LowPriority);
	m_lpFileExportPDFAction->setShortcut(Qt::CTRL + Qt::Key_D);
	m_lpFileToolBar->addAction(m_lpFileExportPDFAction);

	m_lpFileMenu->addSeparator();
#endif

	m_lpFilePropertiesAction	= m_lpFileMenu->addAction(tr("P&roperties..."), this, &cMainWindow::onFileProperties);
	m_lpFilePropertiesAction->setPriority(QAction::LowPriority);
	m_lpFileMenu->addSeparator();

	for(int i = 0; i < MaxRecentFiles;i++)
	{
		m_lpRecentFileAction[i]	= new QAction(this);
		m_lpRecentFileAction[i]->setVisible(false);
		m_lpFileMenu->addAction(m_lpRecentFileAction[i]);
		connect(m_lpRecentFileAction[i], &QAction::triggered, this, &cMainWindow::openRecentFile);
	}
	m_lpSeparatorRecent			= m_lpFileMenu->addSeparator();
	m_lpSeparatorRecent->setVisible(false);

	m_lpFileQuitAction			= m_lpFileMenu->addAction(tr("&Quit"), this, &QWidget::close);
	m_lpFileQuitAction->setShortcut(Qt::CTRL + Qt::Key_Q);
}

void cMainWindow::createEditActions()
{
	m_lpEditMenu	= menuBar()->addMenu(tr("&Edit"));
	m_lpEditToolBar	= addToolBar(tr("Edit Actions"));

	const QIcon	undoIcon	= QIcon::fromTheme("edit-undo");
	m_lpUndoAction			= m_lpEditMenu->addAction(undoIcon, tr("&Undo"));
	m_lpUndoAction->setShortcut(QKeySequence::Undo);
	m_lpEditToolBar->addAction(m_lpUndoAction);

	const QIcon redoIcon	= QIcon::fromTheme("edit-redo");
	m_lpRedoAction			= m_lpEditMenu->addAction(redoIcon, tr("&Redo"));
	m_lpRedoAction->setPriority(QAction::LowPriority);
	m_lpRedoAction->setShortcut(QKeySequence::Redo);
	m_lpEditToolBar->addAction(m_lpRedoAction);
	m_lpEditMenu->addSeparator();

#ifndef QT_NO_CLIPBOARD
	const QIcon	cutIcon		= QIcon::fromTheme("edit-cut");
	m_lpCutAction			= m_lpEditMenu->addAction(cutIcon, tr("Cu&t"));
	m_lpCutAction->setPriority(QAction::LowPriority);
	m_lpCutAction->setShortcut(QKeySequence::Cut);
	m_lpEditToolBar->addAction(m_lpCutAction);

	const QIcon	copyIcon	= QIcon::fromTheme("edit-copy");
	m_lpCopyAction			= m_lpEditMenu->addAction(copyIcon, tr("&Copy"));
	m_lpCopyAction->setPriority(QAction::LowPriority);
	m_lpCopyAction->setShortcut(QKeySequence::Copy);
	m_lpEditToolBar->addAction(m_lpCopyAction);

	const QIcon	pasteIcon	= QIcon::fromTheme("edit-paste");
	m_lpPasteAction			= m_lpEditMenu->addAction(pasteIcon, tr("&Paste"));
	m_lpPasteAction->setPriority(QAction::LowPriority);
	m_lpPasteAction->setShortcut(QKeySequence::Paste);
	m_lpEditToolBar->addAction(m_lpPasteAction);
	if(const QMimeData*	md	= QApplication::clipboard()->mimeData())
		m_lpPasteAction->setEnabled(md->hasText());
#endif
}

void cMainWindow::createTextActions()
{
	m_lpTextMenu	= menuBar()->addMenu(tr("F&ormat"));
	m_lpTextToolBar	= addToolBar(tr("Format Actions"));

	const QIcon boldIcon	= QIcon::fromTheme("format-text-bold");
	m_lpTextBoldAction		= m_lpTextMenu->addAction(boldIcon, tr("&Bold"));
	m_lpTextBoldAction->setShortcut(Qt::CTRL + Qt::Key_B);
	m_lpTextBoldAction->setPriority(QAction::LowPriority);
	QFont	bold;
	bold.setBold(true);
	m_lpTextBoldAction->setFont(bold);
	m_lpTextToolBar->addAction(m_lpTextBoldAction);
	m_lpTextBoldAction->setCheckable(true);

	const QIcon	italicIcon	= QIcon::fromTheme("format-text-italic");
	m_lpTextItalicAction	= m_lpTextMenu->addAction(italicIcon, tr("&Italic"));
	m_lpTextItalicAction->setPriority(QAction::LowPriority);
	m_lpTextItalicAction->setShortcut(Qt::CTRL + Qt::Key_I);
	QFont	italic;
	italic.setItalic(true);
	m_lpTextItalicAction->setFont(italic);
	m_lpTextToolBar->addAction(m_lpTextItalicAction);
	m_lpTextItalicAction->setCheckable(true);

	const QIcon	underlineIcon	= QIcon::fromTheme("format-text-underline");
	m_lpTextUnderlineAction = m_lpTextMenu->addAction(underlineIcon, tr("&Underline"));
	m_lpTextUnderlineAction->setShortcut(Qt::CTRL + Qt::Key_U);
	m_lpTextUnderlineAction->setPriority(QAction::LowPriority);
	QFont underline;
	underline.setUnderline(true);
	m_lpTextUnderlineAction->setFont(underline);
	m_lpTextToolBar->addAction(m_lpTextUnderlineAction);
	m_lpTextUnderlineAction->setCheckable(true);

	m_lpTextMenu->addSeparator();

	const QIcon	leftIcon	= QIcon::fromTheme("format-justify-left");
	m_lpAlignLeftAction = new QAction(leftIcon, tr("&Left"), this);
	m_lpAlignLeftAction->setShortcut(Qt::CTRL + Qt::Key_L);
	m_lpAlignLeftAction->setCheckable(true);
	m_lpAlignLeftAction->setPriority(QAction::LowPriority);
	const QIcon	centerIcon	= QIcon::fromTheme("format-justify-center");
	m_lpAlignCenterAction = new QAction(centerIcon, tr("C&enter"), this);
	m_lpAlignCenterAction->setShortcut(Qt::CTRL + Qt::Key_E);
	m_lpAlignCenterAction->setCheckable(true);
	m_lpAlignCenterAction->setPriority(QAction::LowPriority);
	const QIcon	rightIcon	= QIcon::fromTheme("format-justify-right");
	m_lpAlignRightAction = new QAction(rightIcon, tr("&Right"), this);
	m_lpAlignRightAction->setShortcut(Qt::CTRL + Qt::Key_R);
	m_lpAlignRightAction->setCheckable(true);
	m_lpAlignRightAction->setPriority(QAction::LowPriority);
	const QIcon	fillIcon	= QIcon::fromTheme("format-justify-fill");
	m_lpAlignJustifyAction = new QAction(fillIcon, tr("&Justify"), this);
	m_lpAlignJustifyAction->setShortcut(Qt::CTRL + Qt::Key_J);
	m_lpAlignJustifyAction->setCheckable(true);
	m_lpAlignJustifyAction->setPriority(QAction::LowPriority);

	// Make sure the alignLeft  is always left of the alignRight
	m_lpAlignGroup	= new QActionGroup(this);

	if(QApplication::isLeftToRight())
	{
		m_lpAlignGroup->addAction(m_lpAlignLeftAction);
		m_lpAlignGroup->addAction(m_lpAlignCenterAction);
		m_lpAlignGroup->addAction(m_lpAlignRightAction);
	}
	else
	{
		m_lpAlignGroup->addAction(m_lpAlignRightAction);
		m_lpAlignGroup->addAction(m_lpAlignCenterAction);
		m_lpAlignGroup->addAction(m_lpAlignLeftAction);
	}
	m_lpAlignGroup->addAction(m_lpAlignJustifyAction);

	m_lpTextToolBar->addActions(m_lpAlignGroup->actions());
	m_lpTextMenu->addActions(m_lpAlignGroup->actions());

	m_lpTextMenu->addSeparator();

	QPixmap pix(16, 16);
	pix.fill(Qt::black);
	m_lpTextColorAction = m_lpTextMenu->addAction(pix, tr("&Color..."));
	m_lpTextToolBar->addAction(m_lpTextColorAction);

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

	m_lpViewToolBar = addToolBar(tr("Format Actions"));
	m_lpViewToolBar->setAllowedAreas(Qt::TopToolBarArea | Qt::BottomToolBarArea);
	addToolBar(m_lpViewToolBar);
}

void cMainWindow::createToolsActions()
{
	m_lpToolsMenu			= menuBar()->addMenu(tr("&Tools"));
	m_lpToolsOptionsAction	= m_lpToolsMenu->addAction(tr("&Options..."), this, &cMainWindow::onToolsOptions);
}

void cMainWindow::createWindowActions()
{
}

void cMainWindow::createHelpActions()
{
	m_lpHelpMenu					= menuBar()->addMenu(tr("&Help"));

	m_lpHelpContentsAction			= m_lpHelpMenu->addAction(tr("&Contents"), this, &cMainWindow::onHelpContents);
	m_lpHelpContentsAction->setPriority(QAction::LowPriority);
	m_lpHelpContentsAction->setShortcut(QKeySequence::HelpContents);

	m_lpHelpIndexAction				= m_lpHelpMenu->addAction(tr("&Index"), this, &cMainWindow::onHelpIndex);

	m_lpHelpAboutAction				= m_lpHelpMenu->addAction(tr("&About"), this, &cMainWindow::onHelpAbout);
	m_lpHelpAboutAction->setPriority(QAction::LowPriority);
	m_lpHelpAboutAction->setShortcut(QKeySequence::HelpContents);
}

void cMainWindow::createContextActions()
{
	m_lpPartAddAction = new QAction(tr("add part"), this);
	m_lpPartAddAction->setStatusTip(tr("add a new part"));
	connect(m_lpPartAddAction, &QAction::triggered, this, &cMainWindow::onAddPart);

	m_lpPartEditAction = new QAction(tr("edit part"), this);
	m_lpPartEditAction->setStatusTip(tr("edit the part"));
	connect(m_lpPartEditAction, &QAction::triggered, this, &cMainWindow::onEditPart);

	m_lpPartDeleteAction = new QAction(tr("delete part"), this);
	m_lpPartDeleteAction->setStatusTip(tr("delete the part"));
	connect(m_lpPartDeleteAction, &QAction::triggered, this, &cMainWindow::onDeletePart);

	m_lpChapterAddAction = new QAction(tr("add chapter"), this);
	m_lpChapterAddAction->setStatusTip(tr("add a new chapter"));
	connect(m_lpChapterAddAction, &QAction::triggered, this, &cMainWindow::onAddChapter);

	m_lpChapterEditAction = new QAction(tr("edit chapter"), this);
	m_lpChapterEditAction->setStatusTip(tr("edit the chapter"));
	connect(m_lpChapterEditAction, &QAction::triggered, this, &cMainWindow::onEditChapter);

	m_lpChapterDeleteAction = new QAction(tr("delete chapter"), this);
	m_lpChapterDeleteAction->setStatusTip(tr("delete the chapter"));
	connect(m_lpChapterDeleteAction, &QAction::triggered, this, &cMainWindow::onDeleteChapter);

	m_lpSceneAddAction = new QAction(tr("add scene"), this);
	m_lpSceneAddAction->setStatusTip(tr("add a new scene"));
	connect(m_lpSceneAddAction, &QAction::triggered, this, &cMainWindow::onAddScene);

	m_lpSceneEditAction = new QAction(tr("edit scene"), this);
	m_lpSceneEditAction->setStatusTip(tr("edit the scene"));
	connect(m_lpSceneEditAction, &QAction::triggered, this, &cMainWindow::onEditScene);

	m_lpSceneDeleteAction = new QAction(tr("delete scene"), this);
	m_lpSceneDeleteAction->setStatusTip(tr("delete the scene"));
	connect(m_lpSceneDeleteAction, &QAction::triggered, this, &cMainWindow::onDeleteScene);

	m_lpCharacterAddAction = new QAction(tr("add character"), this);
	m_lpCharacterAddAction->setStatusTip(tr("add a new character"));
	connect(m_lpCharacterAddAction, &QAction::triggered, this, &cMainWindow::onAddCharacter);

	m_lpCharacterEditAction = new QAction(tr("edit character"), this);
	m_lpCharacterEditAction->setStatusTip(tr("edit the character"));
	connect(m_lpCharacterEditAction, &QAction::triggered, this, &cMainWindow::onEditCharacter);

	m_lpCharacterDeleteAction = new QAction(tr("delete character"), this);
	m_lpCharacterDeleteAction->setStatusTip(tr("delete the character"));
	connect(m_lpCharacterDeleteAction, &QAction::triggered, this, &cMainWindow::onDeleteCharacter);

	m_lpPlaceAddAction = new QAction(tr("add place"), this);
	m_lpPlaceAddAction->setStatusTip(tr("add a new place"));
	connect(m_lpPlaceAddAction, &QAction::triggered, this, &cMainWindow::onAddPlace);

	m_lpPlaceEditAction = new QAction(tr("edit place"), this);
	m_lpPlaceEditAction->setStatusTip(tr("edit the place"));
	connect(m_lpPlaceEditAction, &QAction::triggered, this, &cMainWindow::onEditPlace);

	m_lpPlaceDeleteAction = new QAction(tr("delete place"), this);
	m_lpPlaceDeleteAction->setStatusTip(tr("delete the place"));
	connect(m_lpPlaceDeleteAction, &QAction::triggered, this, &cMainWindow::onDeletePlace);

	m_lpObjectAddAction = new QAction(tr("add object"), this);
	m_lpObjectAddAction->setStatusTip(tr("add a new object"));
	connect(m_lpObjectAddAction, &QAction::triggered, this, &cMainWindow::onAddObject);

	m_lpObjectEditAction = new QAction(tr("edit object"), this);
	m_lpObjectEditAction->setStatusTip(tr("edit the object"));
	connect(m_lpObjectEditAction, &QAction::triggered, this, &cMainWindow::onEditObject);

	m_lpObjectDeleteAction = new QAction(tr("delete object"), this);
	m_lpObjectDeleteAction->setStatusTip(tr("delete the object"));
	connect(m_lpObjectDeleteAction, &QAction::triggered, this, &cMainWindow::onDeleteObject);

	m_lpRechercheAddAction = new QAction(tr("add recherche"), this);
	m_lpRechercheAddAction->setStatusTip(tr("add a new recherche"));
	connect(m_lpRechercheAddAction, &QAction::triggered, this, &cMainWindow::onAddRecherche);

	m_lpRechercheEditAction = new QAction(tr("edit recherche"), this);
	m_lpRechercheEditAction->setStatusTip(tr("edit the recherche"));
	connect(m_lpRechercheEditAction, &QAction::triggered, this, &cMainWindow::onEditRecherche);

	m_lpRechercheDeleteAction = new QAction(tr("delete recherche"), this);
	m_lpRechercheDeleteAction->setStatusTip(tr("delete the recherche"));
	connect(m_lpRechercheDeleteAction, &QAction::triggered, this, &cMainWindow::onDeleteRecherche);

	m_lpRechercheOpenLinkAction	= new QAction(tr("open link"), this);
	m_lpRechercheOpenLinkAction->setStatusTip(tr("open the link"));
	connect(m_lpRechercheOpenLinkAction, &QAction::triggered, this, &cMainWindow::onOpenRechercheLink);
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

	connect(m_lpTextBoldAction,				&QAction::triggered,			lpTextEdit,				&cTextEdit::onTextBold);
	connect(m_lpTextItalicAction,			&QAction::triggered,			lpTextEdit,				&cTextEdit::onTextItalic);
	connect(m_lpTextUnderlineAction,		&QAction::triggered,			lpTextEdit,				&cTextEdit::onTextUnderline);

	connect(m_lpTextColorAction,			&QAction::triggered,			lpTextEdit,				&cTextEdit::onTextColor);

	connect(lpTextEdit->document(),			&cTextDocument::undoAvailable,	m_lpUndoAction,			&QAction::setEnabled);
	connect(lpTextEdit->document(),			&cTextDocument::redoAvailable,	m_lpRedoAction,			&QAction::setEnabled);
	m_lpUndoAction->setEnabled(lpTextEdit->document()->isUndoAvailable());
	m_lpRedoAction->setEnabled(lpTextEdit->document()->isRedoAvailable());

	connect(m_lpUndoAction,					&QAction::triggered,			lpTextEdit,				&cTextEdit::undo);
	connect(m_lpRedoAction,					&QAction::triggered,			lpTextEdit,				&cTextEdit::redo);

#ifndef QT_NO_CLIPBOARD
	m_lpCutAction->setEnabled(false);
	m_lpCopyAction->setEnabled(false);

	connect(QApplication::clipboard(),		&QClipboard::dataChanged,		this,					&cMainWindow::onClipboardDataChanged);

	connect(m_lpCutAction,					&QAction::triggered,			lpTextEdit,				&cTextEdit::cut);
	connect(m_lpCopyAction,					&QAction::triggered,			lpTextEdit,				&cTextEdit::copy);
	connect(m_lpPasteAction,				&QAction::triggered,			lpTextEdit,				&cTextEdit::paste);
#endif

	connect(m_lpAlignGroup,					&QActionGroup::triggered,		lpTextEdit,				&cTextEdit::onTextAlign);

	connect(m_lpComboFont,					QOverload<const QString &>::of(&QComboBox::activated),	lpTextEdit,	&cTextEdit::onTextFamily);
	connect(m_lpComboSize,					QOverload<const QString &>::of(&QComboBox::activated),	lpTextEdit,	&cTextEdit::onTextSize);

	connect(lpTextEdit,						&cTextEdit::fontChanged,		this,					&cMainWindow::onFontChanged);
	connect(lpTextEdit,						&cTextEdit::colorChanged,		this,					&cMainWindow::onColorChanged);
	connect(lpTextEdit,						&cTextEdit::alignmentChanged,	this,					&cMainWindow::onAlignmentChanged);

	m_lpOldTextEdit	= lpTextEdit;
}

void cMainWindow::disconnectTextEdit()
{
	if(m_lpOldTextEdit)
	{
		disconnect(m_lpTextBoldAction,			&QAction::triggered,			m_lpOldTextEdit,		&cTextEdit::onTextBold);
		disconnect(m_lpTextItalicAction,		&QAction::triggered,			m_lpOldTextEdit,		&cTextEdit::onTextItalic);
		disconnect(m_lpTextUnderlineAction,		&QAction::triggered,			m_lpOldTextEdit,		&cTextEdit::onTextUnderline);

		disconnect(m_lpTextColorAction,			&QAction::triggered,			m_lpOldTextEdit,		&cTextEdit::onTextColor);

		disconnect(m_lpOldTextEdit->document(),	&cTextDocument::undoAvailable,	m_lpUndoAction,			&QAction::setEnabled);
		disconnect(m_lpOldTextEdit->document(),	&cTextDocument::redoAvailable,	m_lpRedoAction,			&QAction::setEnabled);

		disconnect(m_lpUndoAction,				&QAction::triggered,			m_lpOldTextEdit,		&cTextEdit::undo);
		disconnect(m_lpRedoAction,				&QAction::triggered,			m_lpOldTextEdit,		&cTextEdit::redo);

#ifndef QT_NO_CLIPBOARD
		disconnect(QApplication::clipboard(),	&QClipboard::dataChanged,		this,					&cMainWindow::onClipboardDataChanged);

		disconnect(m_lpCutAction,				&QAction::triggered,			m_lpOldTextEdit,		&cTextEdit::cut);
		disconnect(m_lpCopyAction,				&QAction::triggered,			m_lpOldTextEdit,		&cTextEdit::copy);
		disconnect(m_lpPasteAction,				&QAction::triggered,			m_lpOldTextEdit,		&cTextEdit::paste);
#endif

		disconnect(m_lpAlignGroup,				&QActionGroup::triggered,		m_lpOldTextEdit,		&cTextEdit::onTextAlign);

		disconnect(m_lpComboFont,				QOverload<const QString &>::of(&QComboBox::activated),	m_lpOldTextEdit,	&cTextEdit::onTextFamily);
		disconnect(m_lpComboSize,				QOverload<const QString &>::of(&QComboBox::activated),	m_lpOldTextEdit,	&cTextEdit::onTextSize);

		disconnect(m_lpOldTextEdit,				&cTextEdit::fontChanged,		this,					&cMainWindow::onFontChanged);
		disconnect(m_lpOldTextEdit,				&cTextEdit::colorChanged,		this,					&cMainWindow::onColorChanged);
		disconnect(m_lpOldTextEdit,				&cTextEdit::alignmentChanged,	this,					&cMainWindow::onAlignmentChanged);
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

	m_lpFileSaveAction->setEnabled(m_bSomethingChanged);

	setWindowTitle(szWindowTitle);
}

bool switchTranslator(QTranslator* lpTranslator, const QString& filename)
{
	qApp->removeTranslator(lpTranslator);

	if(lpTranslator->load(filename))
	{
		qApp->installTranslator(lpTranslator);
		return(true);
	}
	return(false);
}

void cMainWindow::onLanguageChanged()
{
	QSettings	settings;
	QString		szLanguage	= settings.value("main/language").toString();
	QLocale		locale		= QLocale(szLanguage);

	QLocale::setDefault(locale);
	if(!switchTranslator(m_lpTranslator, QString("%1%2storyWriter_%3.qm").arg(localePath()).arg(QDir::separator()).arg(szLanguage)))
		switchTranslator(m_lpTranslator, QString(":/locale/storyWriter_%1.qm").arg(szLanguage));
//	switchTranslator(m_translatorQt, QString("qt_%1.qm").arg(szLanguage));
}

void cMainWindow::changeEvent(QEvent* event)
{
	if(event)
	{
		if(event->type() == QEvent::LanguageChange)
		{
			ui->retranslateUi(this);
			retranslateMenu();
			retranslateWindows();
		}

		// this event is send, if the system, language changes
//		case QEvent::LocaleChange:
//			{
//				QString locale = QLocale::system().name();
//				locale.truncate(locale.lastIndexOf('_'));
//				loadLanguage(locale);
//			}
//			break;
	}
	QMainWindow::changeEvent(event);
}

void cMainWindow::retranslateMenu()
{
	m_lpFileMenu->setTitle(tr("&File"));
	m_lpFileNewAction->setText(tr("&New"));
	m_lpFileOpenAction->setText(tr("&Open..."));
	m_lpFileSaveAction->setText(tr("&Save"));
	m_lpFileSaveAsAction->setText(tr("Save &As..."));

#ifndef QT_NO_PRINTER
	m_lpFilePrintAction->setText(tr("&Print..."));
	m_lpFilePrintPreviewAction->setText(tr("Print Preview..."));
	m_lpFileExportPDFAction->setText(tr("&Export PDF..."));
#endif

	m_lpFilePropertiesAction->setText(tr("P&roperties..."));
	m_lpFileQuitAction->setText(tr("&Quit"));


	m_lpEditMenu->setTitle(tr("&Edit"));
	m_lpUndoAction->setText(tr("&Undo"));
	m_lpRedoAction->setText( tr("&Redo"));

#ifndef QT_NO_CLIPBOARD
	m_lpCutAction->setText(tr("Cu&t"));
	m_lpCopyAction->setText(tr("&Copy"));
	m_lpPasteAction->setText(tr("&Paste"));
#endif


	m_lpTextMenu->setTitle(tr("F&ormat"));
	m_lpTextBoldAction->setText(tr("&Bold"));
	m_lpTextItalicAction->setText(tr("&Italic"));
	m_lpTextUnderlineAction->setText(tr("&Underline"));
	m_lpAlignLeftAction->setText(tr("&Left"));
	m_lpAlignCenterAction->setText(tr("C&enter"));
	m_lpAlignRightAction->setText(tr("&Right"));
	m_lpAlignJustifyAction->setText(tr("&Justify"));
	m_lpTextColorAction->setText(tr("&Color..."));


	m_lpToolsMenu->setTitle(tr("&Tools"));
	m_lpToolsOptionsAction->setText(tr("&Options..."));

//	m_lpWindowMenu;							/*!< Pointer to the window menu */

	m_lpHelpMenu->setTitle(tr("&Help"));
	m_lpHelpContentsAction->setText(tr("&Contents"));
	m_lpHelpIndexAction->setText(tr("&Index"));
	m_lpHelpAboutAction->setText(tr("&About"));


	m_lpPartAddAction->setText(tr("add part"));
	m_lpPartAddAction->setStatusTip(tr("add a new part"));

	m_lpPartEditAction->setText(tr("edit part"));
	m_lpPartEditAction->setStatusTip(tr("edit the part"));

	m_lpPartDeleteAction->setText(tr("delete part"));
	m_lpPartDeleteAction->setStatusTip(tr("delete the part"));

	m_lpChapterAddAction->setText(tr("add chapter"));
	m_lpChapterAddAction->setStatusTip(tr("add a new chapter"));

	m_lpChapterEditAction->setText(tr("edit chapter"));
	m_lpChapterEditAction->setStatusTip(tr("edit the chapter"));

	m_lpChapterDeleteAction->setText(tr("delete chapter"));
	m_lpChapterDeleteAction->setStatusTip(tr("delete the chapter"));

	m_lpSceneAddAction->setText(tr("add scene"));
	m_lpSceneAddAction->setStatusTip(tr("add a new scene"));

	m_lpSceneEditAction->setText(tr("edit scene"));
	m_lpSceneEditAction->setStatusTip(tr("edit the scene"));

	m_lpSceneDeleteAction->setText(tr("delete scene"));
	m_lpSceneDeleteAction->setStatusTip(tr("delete the scene"));

	m_lpCharacterAddAction->setText(tr("add character"));
	m_lpCharacterAddAction->setStatusTip(tr("add a new character"));

	m_lpCharacterEditAction->setText(tr("edit character"));
	m_lpCharacterEditAction->setStatusTip(tr("edit the character"));

	m_lpCharacterDeleteAction->setText(tr("delete character"));
	m_lpCharacterDeleteAction->setStatusTip(tr("delete the character"));

	m_lpPlaceAddAction->setText(tr("add place"));
	m_lpPlaceAddAction->setStatusTip(tr("add a new place"));

	m_lpPlaceEditAction->setText(tr("edit place"));
	m_lpPlaceEditAction->setStatusTip(tr("edit the place"));

	m_lpPlaceDeleteAction->setText(tr("delete place"));
	m_lpPlaceDeleteAction->setStatusTip(tr("delete the place"));

	m_lpObjectAddAction->setText(tr("add object"));
	m_lpObjectAddAction->setStatusTip(tr("add a new object"));

	m_lpObjectEditAction->setText(tr("edit object"));
	m_lpObjectEditAction->setStatusTip(tr("edit the object"));

	m_lpObjectDeleteAction->setText(tr("delete object"));
	m_lpObjectDeleteAction->setStatusTip(tr("delete the object"));

	m_lpRechercheAddAction->setText(tr("add recherche"));
	m_lpRechercheAddAction->setStatusTip(tr("add a new recherche"));

	m_lpRechercheEditAction->setText(tr("edit recherche"));
	m_lpRechercheEditAction->setStatusTip(tr("edit the recherche"));

	m_lpRechercheDeleteAction->setText(tr("delete recherche"));
	m_lpRechercheDeleteAction->setStatusTip(tr("delete the recherche"));

	m_lpRechercheOpenLinkAction->setText(tr("open link"));
	m_lpRechercheOpenLinkAction->setStatusTip(tr("open the link"));
}

void cMainWindow::retranslateWindows()
{
	for(int x = 0;x < ui->m_lpMainTab->count();x++)
	{
		cWidget*	lpWidget	= (cWidget*)ui->m_lpMainTab->widget(x);

		lpWidget->retranslateUI();
	}

	if(m_lpOptionsDialog)
		m_lpOptionsDialog->retranslateUI();
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

void cMainWindow::onFontComboBoxGotFocus(cFontComboBox* /*lpComboBox*/)
{
	disableTextEdit();
}

void cMainWindow::onFontComboBoxLostFocus(cFontComboBox* /*lpComboBox*/)
{
}

void cMainWindow::onOutlineDropped(cTreeView* /*lpTreeView*/, QModelIndex from, QModelIndex /*to*/)
{
	qint32	parts	= m_lpOutlineModel->rowCount(QModelIndex());

	for(qint32 part = 0;part < parts;part++)
	{
		QModelIndex		partIndex	= m_lpOutlineModel->index(part, 0, QModelIndex());
		cPart*			lpPart		= qvariant_cast<cPart*>(m_lpOutlineModel->itemFromIndex(partIndex)->data());
		qint32			chapters	= m_lpOutlineModel->rowCount(partIndex);

		if(partIndex != from)
			lpPart->setSortOrder(part);

		for(qint32 chapter = 0;chapter < chapters;chapter++)
		{
			QModelIndex		chapterIndex	= m_lpOutlineModel->index(chapter, 0, partIndex);
			cChapter*		lpChapter		= qvariant_cast<cChapter*>(m_lpOutlineModel->itemFromIndex(chapterIndex)->data());
			qint32			scenes			= m_lpOutlineModel->rowCount(chapterIndex);

			if(chapterIndex != from)
			{
				lpChapter->setPart(lpPart);
				lpChapter->setSortOrder(chapter);
			}

			lpChapter = lpChapter;
			for(qint32 scene = 0;scene < scenes;scene++)
			{
				QModelIndex	sceneIndex		= m_lpOutlineModel->index(scene, 0, chapterIndex);
				cScene*		lpScene			= qvariant_cast<cScene*>(m_lpOutlineModel->itemFromIndex(sceneIndex)->data());

				if(sceneIndex != from)
				{
					lpScene->setChapter(lpChapter);
					lpScene->setSortOrder(scene);
				}
			}
		}
	}
	somethingChanged();
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
	lpPropertiesWindow->setBook(m_lpStoryBook);
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

	cRechercheWindow*	lpRechercheWindow	= new cRechercheWindow(this);
	lpRechercheWindow->setRecherche(lpRecherche, m_lpStoryBook->characterList(), m_lpStoryBook->placeList(), m_lpStoryBook->objectList());
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
		menu.addAction(m_lpPartAddAction);
	}
	else
	{
		cPart*			lpPart		= qvariant_cast<cPart*>(lpItem->data());
		cChapter*		lpChapter	= qvariant_cast<cChapter*>(lpItem->data());
		cScene*			lpScene		= qvariant_cast<cScene*>(lpItem->data());

		if(lpPart)
		{
			menu.addAction(m_lpPartAddAction);
			menu.addAction(m_lpPartEditAction);
			menu.addAction(m_lpPartDeleteAction);
			menu.addSeparator();
			menu.addAction(m_lpChapterAddAction);
		}
		else if(lpChapter)
		{
			menu.addAction(m_lpChapterAddAction);
			menu.addAction(m_lpChapterEditAction);
			menu.addAction(m_lpChapterDeleteAction);
			menu.addSeparator();
			menu.addAction(m_lpSceneAddAction);
		}
		else if(lpScene)
		{
			menu.addAction(m_lpSceneAddAction);
			menu.addAction(m_lpSceneEditAction);
			menu.addAction(m_lpSceneDeleteAction);
		}
		else
			menu.addAction(m_lpPartAddAction);
	}

	menu.exec(ui->m_lpOutlineList->mapToGlobal(pos));
}

void cMainWindow::onCharacterContextMenu(const QPoint& pos)
{
	QMenu			menu(this);

	QStandardItem*	lpItem	= m_lpCharacterModel->itemFromIndex(ui->m_lpCharacterList->currentIndex());
	if(!lpItem)
	{
		menu.addAction(m_lpCharacterAddAction);
	}
	else
	{
		menu.addAction(m_lpCharacterAddAction);
		menu.addAction(m_lpCharacterEditAction);
		menu.addAction(m_lpCharacterDeleteAction);
	}

	menu.exec(ui->m_lpCharacterList->mapToGlobal(pos));
}

void cMainWindow::onPlaceContextMenu(const QPoint& pos)
{
	QMenu			menu(this);

	QStandardItem*	lpItem	= m_lpPlaceModel->itemFromIndex(ui->m_lpPlaceList->currentIndex());
	if(!lpItem)
	{
		menu.addAction(m_lpPlaceAddAction);
	}
	else
	{
		menu.addAction(m_lpPlaceAddAction);
		menu.addAction(m_lpPlaceEditAction);
		menu.addAction(m_lpPlaceDeleteAction);
	}

	menu.exec(ui->m_lpPlaceList->mapToGlobal(pos));
}

void cMainWindow::onObjectContextMenu(const QPoint& pos)
{
	QMenu			menu(this);

	QStandardItem*	lpItem	= m_lpObjectModel->itemFromIndex(ui->m_lpObjectList->currentIndex());
	if(!lpItem)
	{
		menu.addAction(m_lpObjectAddAction);
	}
	else
	{
		menu.addAction(m_lpObjectAddAction);
		menu.addAction(m_lpObjectEditAction);
		menu.addAction(m_lpObjectDeleteAction);
	}

	menu.exec(ui->m_lpObjectList->mapToGlobal(pos));
}

void cMainWindow::onRechercheContextMenu(const QPoint& pos)
{
	QMenu			menu(this);

	QStandardItem*	lpItem	= m_lpRechercheModel->itemFromIndex(ui->m_lpRechercheList->currentIndex());
	if(!lpItem)
	{
		menu.addAction(m_lpRechercheAddAction);
	}
	else
	{
		menu.addAction(m_lpRechercheAddAction);
		menu.addAction(m_lpRechercheEditAction);
		menu.addAction(m_lpRechercheDeleteAction);
		menu.addSeparator();
		menu.addAction(m_lpRechercheOpenLinkAction);
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
	if(m_lpStoryBook)
		m_lpStoryBook->printPdf("C:\\Temp\\test.pdf");
}

void cMainWindow::onFileProperties()
{
	onShowPropertiesWindow();
}

void cMainWindow::onToolsOptions()
{
	if(m_lpOptionsDialog)
		return;

	m_lpOptionsDialog	= new cOptionsDialog(this);

	connect(m_lpOptionsDialog,	&cOptionsDialog::onLanguageChanged,	this,	&cMainWindow::onLanguageChanged);
	m_lpOptionsDialog->exec();

	delete m_lpOptionsDialog;
	m_lpOptionsDialog	= 0;
}

void cMainWindow::onHelpContents()
{
	QMessageBox::information(this, "Help", "Contents");
}

void cMainWindow::onHelpIndex()
{
	QMessageBox::information(this, "Help", "Index");
}

void cMainWindow::onHelpAbout()
{
	QMessageBox::information(this, "Help", "About");
}

void cMainWindow::onClipboardDataChanged()
{
#ifndef QT_NO_CLIPBOARD
	if(const QMimeData *md = QApplication::clipboard()->mimeData())
		m_lpPasteAction->setEnabled(md->hasText());
#endif
}

void cMainWindow::onFontChanged(const QFont& font)
{
	m_lpComboFont->setCurrentIndex(m_lpComboFont->findText(QFontInfo(font).family()));
	m_lpComboSize->setCurrentIndex(m_lpComboSize->findText(QString::number(font.pointSize())));
	m_lpTextBoldAction->setChecked(font.bold());
	m_lpTextItalicAction->setChecked(font.italic());
	m_lpTextUnderlineAction->setChecked(font.underline());
}

void cMainWindow::onColorChanged(const QColor& color)
{
	QPixmap pix(16, 16);
	pix.fill(color);
	m_lpTextColorAction->setIcon(pix);
}

void cMainWindow::onAlignmentChanged(const Qt::Alignment &alignment)
{
	if(alignment & Qt::AlignLeft)
		m_lpAlignLeftAction->setChecked(true);
	else if(alignment & Qt::AlignHCenter)
		m_lpAlignCenterAction->setChecked(true);
	else if(alignment & Qt::AlignRight)
		m_lpAlignRightAction->setChecked(true);
	else if(alignment & Qt::AlignJustify)
		m_lpAlignJustifyAction->setChecked(true);
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

	QString		szProjectName	= QFileDialog::getOpenFileName(this, tr("Open Project"), m_szOldPath, tr("StoryWriter Files (*.storyWriter)"));
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
		m_lpRecentFileAction[i]->setText(text);
		m_lpRecentFileAction[i]->setData(files[i]);
		m_lpRecentFileAction[i]->setVisible(true);
	}

	for(int j = numRecentFiles; j < MaxRecentFiles; j++)
		m_lpRecentFileAction[j]->setVisible(false);

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
