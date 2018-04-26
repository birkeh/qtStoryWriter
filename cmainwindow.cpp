#include "cmainwindow.h"
#include "ui_cmainwindow.h"

#include "ctextdocument.h"

#include "cpartwindow.h"
#include "cchapterwindow.h"
#include "cscenewindow.h"
#include "ccharacterwindow.h"

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

#include <QMessageBox>


cMainWindow::cMainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::cMainWindow),
	m_lpOutlineModel(0),
	m_lpCharacterModel(0),
	m_lpPlaceModel(0),
	m_lpObjectModel(0),
	m_bUpdatingTab(false),
	m_lpStoryBook(0)
{
	initUI();
	createActions();

	QString		szPath	= QDir::homePath() + QDir::separator() + "OneDrive - WINDESIGN" + QDir::separator() + "__BOOKS__" + QDir::separator() + "qtStoryWriter" + QDir::separator() + "rückwärts.storyWriter" ;
	m_lpStoryBook		= new cStoryBook(szPath);
	m_lpStoryBook->fillOutlineList(ui->m_lpOutlineList);
	m_lpStoryBook->fillCharacterList(ui->m_lpCharacterList);
	m_lpStoryBook->fillPlaceList(ui->m_lpPlaceList);
	m_lpStoryBook->fillObjectList(ui->m_lpObjectList);
	m_lpStoryBook->fillRechercheList(ui->m_lpRechercheList);

	updateWindowTitle();
}

cMainWindow::~cMainWindow()
{
	if(m_lpStoryBook)
		delete m_lpStoryBook;

	delete ui;
}

void cMainWindow::closeEvent(QCloseEvent *event)
{
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

	connect(ui->m_lpMainTab, SIGNAL(currentChanged(int)), this, SLOT(onMainTabCurrentChanged(int)));
	connect(ui->m_lpMainTab, SIGNAL(tabCloseRequested(int)), this,SLOT(onMainTabTabCloseRequested(int)));
	connect(ui->m_lpMdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(onMdiAreaSubWindowActivated(QMdiSubWindow*)));

	connect(ui->m_lpOutlineList, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(onOutlineDoubleClicked(QModelIndex)));
	connect(ui->m_lpCharacterList, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(onCharacterDoubleClicked(QModelIndex)));
}

void cMainWindow::createFileActions()
{
	QAction*	lpAction;
	QToolBar*	lpToolBar		= addToolBar(tr("File Actions"));
	QMenu*		lpMenu			= menuBar()->addMenu(tr("&File"));

	const QIcon	newIcon			= QIcon::fromTheme("document-new", QIcon(":/images/mac/filenew.png"));
	lpAction					= lpMenu->addAction(newIcon, tr("&New"), this, &cMainWindow::onFileNew);
	lpToolBar->addAction(lpAction);
	lpAction->setPriority(QAction::LowPriority);
	lpAction->setShortcut(QKeySequence::New);

	const QIcon	openIcon		= QIcon::fromTheme("document-open", QIcon(":/images/mac/fileopen.png"));
	lpAction					= lpMenu->addAction(openIcon, tr("&Open..."), this, &cMainWindow::onFileOpen);
	lpAction->setShortcut(QKeySequence::Open);
	lpToolBar->addAction(lpAction);

	lpMenu->addSeparator();

	const QIcon	saveIcon		= QIcon::fromTheme("document-save", QIcon(":/images/mac/filesave.png"));
	m_lpActionSave				= lpMenu->addAction(saveIcon, tr("&Save"), this, &cMainWindow::onFileSave);
	m_lpActionSave->setShortcut(QKeySequence::Save);
	m_lpActionSave->setEnabled(false);
	lpToolBar->addAction(m_lpActionSave);

	lpAction					= lpMenu->addAction(tr("Save &As..."), this, &cMainWindow::onFileSaveAs);
	lpAction->setPriority(QAction::LowPriority);
	lpMenu->addSeparator();

#ifndef QT_NO_PRINTER
	const QIcon	printIcon		= QIcon::fromTheme("document-print", QIcon(":/images/mac/fileprint.png"));
	lpAction					= lpMenu->addAction(printIcon, tr("&Print..."), this, &cMainWindow::onFilePrint);
	lpAction->setPriority(QAction::LowPriority);
	lpAction->setShortcut(QKeySequence::Print);
	lpToolBar->addAction(lpAction);

	const QIcon	filePrintIcon	= QIcon::fromTheme("fileprint", QIcon(":/images/mac/fileprint.png"));
	lpMenu->addAction(filePrintIcon, tr("Print Preview..."), this, &cMainWindow::onFilePrintPreview);

	const QIcon	exportPdfIcon	= QIcon::fromTheme("exportpdf", QIcon(":/images/mac/exportpdf.png"));
	lpAction					= lpMenu->addAction(exportPdfIcon, tr("&Export PDF..."), this, &cMainWindow::onFilePrintPdf);
	lpAction->setPriority(QAction::LowPriority);
	lpAction->setShortcut(Qt::CTRL + Qt::Key_D);
	lpToolBar->addAction(lpAction);

	lpMenu->addSeparator();
#endif

	lpAction					= lpMenu->addAction(tr("&Quit"), this, &QWidget::close);
	lpAction->setShortcut(Qt::CTRL + Qt::Key_Q);
}

void cMainWindow::createEditActions()
{
	QToolBar*	lpToolBar	= addToolBar(tr("Edit Actions"));
	QMenu*		lpMenu		= menuBar()->addMenu(tr("&Edit"));

	const QIcon	undoIcon	= QIcon::fromTheme("edit-undo", QIcon(":/images/mac/editundo.png"));
//	m_lpActionUndo			= lpMenu->addAction(undoIcon, tr("&Undo"), textEdit, &QTextEdit::undo);
	m_lpActionUndo			= lpMenu->addAction(undoIcon, tr("&Undo"), this, &cMainWindow::onSpecialUndo);
	m_lpActionUndo->setShortcut(QKeySequence::Undo);
	lpToolBar->addAction(m_lpActionUndo);

	const QIcon redoIcon	= QIcon::fromTheme("edit-redo", QIcon(":/images/mac/editredo.png"));
//	m_lpActionRedo			= lpMenu->addAction(redoIcon, tr("&Redo"), textEdit, &QTextEdit::redo);
	m_lpActionRedo			= lpMenu->addAction(redoIcon, tr("&Redo"), this, &cMainWindow::onSpecialRedo);
	m_lpActionRedo->setPriority(QAction::LowPriority);
	m_lpActionRedo->setShortcut(QKeySequence::Redo);
	lpToolBar->addAction(m_lpActionRedo);
	lpMenu->addSeparator();

#ifndef QT_NO_CLIPBOARD
	const QIcon	cutIcon		= QIcon::fromTheme("edit-cut", QIcon(":/images/mac/editcut.png"));
//	m_lpActionCut			= lpMenu->addAction(cutIcon, tr("Cu&t"), textEdit, &QTextEdit::cut);
	m_lpActionCut			= lpMenu->addAction(cutIcon, tr("Cu&t"), this, &cMainWindow::onSpecialCut);
	m_lpActionCut->setPriority(QAction::LowPriority);
	m_lpActionCut->setShortcut(QKeySequence::Cut);
	lpToolBar->addAction(m_lpActionCut);

	const QIcon	copyIcon	= QIcon::fromTheme("edit-copy", QIcon(":/images/mac/editcopy.png"));
//	m_lpActionCopy			= lpMenu->addAction(copyIcon, tr("&Copy"), textEdit, &QTextEdit::copy);
	m_lpActionCopy			= lpMenu->addAction(copyIcon, tr("&Copy"), this, &cMainWindow::onSpecialCopy);
	m_lpActionCopy->setPriority(QAction::LowPriority);
	m_lpActionCopy->setShortcut(QKeySequence::Copy);
	lpToolBar->addAction(m_lpActionCopy);

	const QIcon	pasteIcon	= QIcon::fromTheme("edit-paste", QIcon(":/images/mac/editpaste.png"));
//	m_lpActionPaste			= lpMenu->addAction(pasteIcon, tr("&Paste"), textEdit, &QTextEdit::paste);
	m_lpActionPaste			= lpMenu->addAction(pasteIcon, tr("&Paste"), this, &cMainWindow::onSpecialPaste);
	m_lpActionPaste->setPriority(QAction::LowPriority);
	m_lpActionPaste->setShortcut(QKeySequence::Paste);
	lpToolBar->addAction(m_lpActionPaste);
	if(const QMimeData*	md	= QApplication::clipboard()->mimeData())
		m_lpActionPaste->setEnabled(md->hasText());
#endif
}

void cMainWindow::createTextActions()
{
	QToolBar*	lpToolBar	= addToolBar(tr("Format Actions"));
	QMenu*		lpMenu		= menuBar()->addMenu(tr("F&ormat"));

	const QIcon boldIcon	= QIcon::fromTheme("format-text-bold", QIcon(":/images/mac/textbold.png"));
	m_lpActionTextBold		= lpMenu->addAction(boldIcon, tr("&Bold"), this, &cMainWindow::onTextBold);
	m_lpActionTextBold->setShortcut(Qt::CTRL + Qt::Key_B);
	m_lpActionTextBold->setPriority(QAction::LowPriority);
	QFont	bold;
	bold.setBold(true);
	m_lpActionTextBold->setFont(bold);
	lpToolBar->addAction(m_lpActionTextBold);
	m_lpActionTextBold->setCheckable(true);

	const QIcon	italicIcon	= QIcon::fromTheme("format-text-italic", QIcon(":/images/mac/textitalic.png"));
	m_lpActionTextItalic	= lpMenu->addAction(italicIcon, tr("&Italic"), this, &cMainWindow::onTextItalic);
	m_lpActionTextItalic->setPriority(QAction::LowPriority);
	m_lpActionTextItalic->setShortcut(Qt::CTRL + Qt::Key_I);
	QFont	italic;
	italic.setItalic(true);
	m_lpActionTextItalic->setFont(italic);
	lpToolBar->addAction(m_lpActionTextItalic);
	m_lpActionTextItalic->setCheckable(true);

	const QIcon	underlineIcon	= QIcon::fromTheme("format-text-underline", QIcon(":/images/mac/textunder.png"));
	m_lpActionTextUnderline = lpMenu->addAction(underlineIcon, tr("&Underline"), this, &cMainWindow::onTextUnderline);
	m_lpActionTextUnderline->setShortcut(Qt::CTRL + Qt::Key_U);
	m_lpActionTextUnderline->setPriority(QAction::LowPriority);
	QFont underline;
	underline.setUnderline(true);
	m_lpActionTextUnderline->setFont(underline);
	lpToolBar->addAction(m_lpActionTextUnderline);
	m_lpActionTextUnderline->setCheckable(true);

	lpMenu->addSeparator();

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
	QActionGroup*	alignGroup	= new QActionGroup(this);
	connect(alignGroup, &QActionGroup::triggered, this, &cMainWindow::onTextAlign);

	if(QApplication::isLeftToRight())
	{
		alignGroup->addAction(m_lpActionAlignLeft);
		alignGroup->addAction(m_lpActionAlignCenter);
		alignGroup->addAction(m_lpActionAlignRight);
	}
	else
	{
		alignGroup->addAction(m_lpActionAlignRight);
		alignGroup->addAction(m_lpActionAlignCenter);
		alignGroup->addAction(m_lpActionAlignLeft);
	}
	alignGroup->addAction(m_lpActionAlignJustify);

	lpToolBar->addActions(alignGroup->actions());
	lpMenu->addActions(alignGroup->actions());

	lpMenu->addSeparator();

	QPixmap pix(16, 16);
	pix.fill(Qt::black);
	m_lpActionTextColor = lpMenu->addAction(pix, tr("&Color..."), this, &cMainWindow::onTextColor);
	lpToolBar->addAction(m_lpActionTextColor);

	lpToolBar = addToolBar(tr("Format Actions"));
	lpToolBar->setAllowedAreas(Qt::TopToolBarArea | Qt::BottomToolBarArea);
	addToolBarBreak(Qt::TopToolBarArea);
	addToolBar(lpToolBar);

	m_lpComboStyle	= new QComboBox(lpToolBar);
	lpToolBar->addWidget(m_lpComboStyle);
	m_lpComboStyle->addItem("Standard");
	m_lpComboStyle->addItem("Bullet List (Disc)");
	m_lpComboStyle->addItem("Bullet List (Circle)");
	m_lpComboStyle->addItem("Bullet List (Square)");
	m_lpComboStyle->addItem("Ordered List (Decimal)");
	m_lpComboStyle->addItem("Ordered List (Alpha lower)");
	m_lpComboStyle->addItem("Ordered List (Alpha upper)");
	m_lpComboStyle->addItem("Ordered List (Roman lower)");
	m_lpComboStyle->addItem("Ordered List (Roman upper)");

	connect(m_lpComboStyle, QOverload<int>::of(&QComboBox::activated), this, &cMainWindow::onTextStyle);

	m_lpComboFont	= new QFontComboBox(lpToolBar);
	lpToolBar->addWidget(m_lpComboFont);
	connect(m_lpComboFont, QOverload<const QString &>::of(&QComboBox::activated), this, &cMainWindow::onTextFamily);

	m_lpComboSize	= new QComboBox(lpToolBar);
	m_lpComboSize->setObjectName("comboSize");
	lpToolBar->addWidget(m_lpComboSize);
	m_lpComboSize->setEditable(true);

	const QList<int> standardSizes	= QFontDatabase::standardSizes();
	foreach(int size, standardSizes)
		m_lpComboSize->addItem(QString::number(size));
	m_lpComboSize->setCurrentIndex(standardSizes.indexOf(QApplication::font().pointSize()));

	connect(m_lpComboSize, QOverload<const QString &>::of(&QComboBox::activated), this, &cMainWindow::onTextSize);
}

void cMainWindow::updateWindowTitle()
{
	if(!m_lpStoryBook)
	{
		setWindowTitle("qtStoryWriter");
		return;
	}

	QString	szTitle		= m_lpStoryBook->title();
	QString	szAuthor	= m_lpStoryBook->author();

	if(szAuthor.isEmpty())
		setWindowTitle(QString("\"%1\" - qtStoryWriter").arg(szTitle));
	else
		setWindowTitle(QString("\"%1\" by %2 - qtStoryWriter").arg(szTitle).arg(szAuthor));
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

void cMainWindow::onOutlineDoubleClicked(const QModelIndex& index)
{
	QStandardItem*	lpItem		= m_lpOutlineModel->itemFromIndex(index);
	cPart*			lpPart		= qvariant_cast<cPart*>(lpItem->data());
	cChapter*		lpChapter	= qvariant_cast<cChapter*>(lpItem->data());
	cScene*			lpScene		= qvariant_cast<cScene*>(lpItem->data());

	if(lpPart)
		showPartWindow(lpPart);
	else if(lpChapter)
		showChapterWindow(lpChapter);
	else if(lpScene)
		showSceneWindow(lpScene);
	else
		QMessageBox::information(this, "DoubleClicked", "outline");
}

void cMainWindow::onCharacterDoubleClicked(const QModelIndex& index)
{
	QStandardItem*	lpItem		= m_lpCharacterModel->itemFromIndex(index);
	cCharacter*		lpCharacter	= qvariant_cast<cCharacter*>(lpItem->data());

	showCharacterWindow(lpCharacter);
}

void cMainWindow::showPartWindow(cPart* lpPart)
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

	lpPartWindow->show();
}

void cMainWindow::showChapterWindow(cChapter* lpChapter)
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

	lpChapterWindow->show();
}

void cMainWindow::showSceneWindow(cScene* lpScene)
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
	lpSceneWindow->setScene(lpScene);
	cWidget*			lpWidget1			= new cWidget(lpSceneWindow);
	lpWidget1->setWindow(ui->m_lpMdiArea->addSubWindow(lpSceneWindow));
	ui->m_lpMainTab->addTab((QWidget*)lpWidget1, lpSceneWindow->windowTitle());

	lpSceneWindow->show();
}

void cMainWindow::showCharacterWindow(cCharacter* lpCharacter)
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

	lpCharacterWindow->show();
}

void cMainWindow::onFileNew()
{
}

void cMainWindow::onFileOpen()
{
}

bool cMainWindow::onFileSave()
{
	return(true);
}

bool cMainWindow::onFileSaveAs()
{
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

void cMainWindow::onTextBold()
{
}

void cMainWindow::onTextItalic()
{
}

void cMainWindow::onTextUnderline()
{
}

void cMainWindow::onTextAlign(QAction *a)
{
}

void cMainWindow::onTextFamily(const QString &f)
{
}

void cMainWindow::onTextSize(const QString &p)
{
}

void cMainWindow::onTextStyle(int styleIndex)
{
}

void cMainWindow::onTextColor()
{
}

void cMainWindow::onSpecialUndo()
{
}

void cMainWindow::onSpecialRedo()
{
}

void cMainWindow::onSpecialCut()
{
}

void cMainWindow::onSpecialCopy()
{
}

void cMainWindow::onSpecialPaste()
{
}
