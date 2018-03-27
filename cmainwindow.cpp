#include "cmainwindow.h"
#include "ui_cmainwindow.h"

#include "ctextdocument.h"
#include "cdocumentreader.h"

#include <QTextDocument>
#include <QTextBlockFormat>
#include <QTextCharFormat>

#include <QTextDocumentWriter>
#include <QByteArray>
#include <QTextCodec>
#include <QFile>


cTextDocument*	g_lpInputDocument	= 0;
cTextDocument*	g_lpOutputDocument	= 0;


QTextBlockFormat createTextBlockFormat(Qt::Alignment alignment, qreal leftMargin, qreal topMargin, qreal rightMargin, qreal bottomMargin, int indent, qreal lineHeight, int lineHeightType,
										bool nonBreakableLines, QTextBlockFormat::PageBreakFlags pageBreakPolicy, const QList<QTextOption::Tab>& tabPositions, qreal textIndent,
										QBrush background, QBrush foreground, Qt::LayoutDirection layoutDirection, int objectIndex, int objectType /* property*/)
{
	QTextBlockFormat	format;

	format.setAlignment(alignment);
	format.setLeftMargin(leftMargin);
	format.setTopMargin(topMargin);
	format.setRightMargin(rightMargin);
	format.setBottomMargin(bottomMargin);
	format.setIndent(indent);
	format.setLineHeight(lineHeight, lineHeightType);
	format.setNonBreakableLines(nonBreakableLines);
	format.setPageBreakPolicy(pageBreakPolicy);
	format.setTabPositions(tabPositions);
	format.setTextIndent(textIndent);

	format.setBackground(background);
	format.setForeground(foreground);
	format.setLayoutDirection(layoutDirection);
	format.setObjectIndex(objectIndex);
	format.setObjectType(objectType);
	//property

	return(format);
}

QTextCharFormat createTextCharFormat(bool anchor, const QString& anchorHref, const QStringList& anchorNames, const QFont& font, QTextCharFormat::FontPropertiesInheritanceBehavior behavior,
									 const QPen& textOutline, const QString& toolTip, const QColor& underlineColor, QTextCharFormat::UnderlineStyle underlineStyle, QTextCharFormat::VerticalAlignment verticalAlignment,
									 QBrush background, QBrush foreground, Qt::LayoutDirection layoutDirection, int objectIndex, int objectType /* property*/)
{
	QTextCharFormat		format;

	format.setAnchor(anchor);
	format.setAnchorHref(anchorHref);
	format.setAnchorNames(anchorNames);
	format.setFont(font, behavior);
	format.setTextOutline(textOutline);
	format.setToolTip(toolTip);
	format.setUnderlineColor(underlineColor);
	format.setUnderlineStyle(underlineStyle);
	format.setVerticalAlignment(verticalAlignment);

	format.setBackground(background);
	format.setForeground(foreground);
	format.setLayoutDirection(layoutDirection);
	format.setObjectIndex(objectIndex);
	format.setObjectType(objectType);
	//property

	return(format);
}

void readWriteTest1()
{
	if(!QFile::exists(":/example.html"))
		return;
	QFile file(":/example.html");

	if(!file.open(QFile::ReadOnly))
		return;

	QByteArray	data	= file.readAll();
	QTextCodec*	codec	= Qt::codecForHtml(data);
	QString		str		= codec->toUnicode(data);
	if(Qt::mightBeRichText(str))
	{
		g_lpInputDocument->setHtml(str);
	}
	else
	{
		str = QString::fromLocal8Bit(data);
		g_lpInputDocument->setPlainText(str);
	}

	file.close();
}

void readWriteTest2()
{
	QTextCursor		cursor(g_lpInputDocument);

	// TEXT BLOCK FORMAT
	Qt::Alignment										alignment			= Qt::AlignCenter;
	qreal												leftMargin			= 0;
	qreal												topMargin			= 0;
	qreal												rightMargin			= 0;
	qreal												bottomMargin		= 0;
	int													indent				= 0;
	qreal												lineHeight			= 1;
	int													lineHeightType		= QTextBlockFormat::SingleHeight;	// QTextBlockFormat::SingleHeight		0		This is the default line height: single spacing.
																												// QTextBlockFormat::ProportionalHeight	1		This sets the spacing proportional to the line (in percentage). For example, set to 200 for double spacing.
																												// QTextBlockFormat::FixedHeight		2		This sets the line height to a fixed line height (in pixels).
																												// QTextBlockFormat::MinimumHeight		3		This sets the minimum line height (in pixels).
																												// QTextBlockFormat::LineDistanceHeight	4		This adds the specified height between lines (in pixels).
	bool												nonBreakableLines	= false;
	QTextBlockFormat::PageBreakFlags					pageBreakPolicy		= QTextFormat::PageBreak_Auto;		// QTextFormat::PageBreak_Auto			0		The page break is determined automatically depending on the available space on the current page
																												// QTextFormat::PageBreak_AlwaysBefore	0x001	The page is always broken before the paragraph/table
																												// QTextFormat::PageBreak_AlwaysAfter	0x010	A new page is always started after the paragraph/table
	const QList<QTextOption::Tab>						tabPositions;
	qreal												textIndent			= 0;
	QBrush												background			= QBrush(QColor("lightGray"));
	QBrush												foreground			= QBrush(QColor("black"));
	Qt::LayoutDirection									layoutDirection		= Qt::LeftToRight;					// Qt::LeftToRight						0		Left-to-right layout.
																												// Qt::RightToLeft						1		Right-to-left layout.
																												// Qt::LayoutDirectionAuto				2		Automatic layout.
	int													objectIndex			= 0;
	int													objectType			= QTextFormat::NoObject;			// QTextFormat::NoObject				0
																												// QTextFormat::ImageObject				1
																												// QTextFormat::TableObject				2
																												// QTextFormat::TableCellObject			3
																												// QTextFormat::UserObject				0x1000	The first object that can be used for application-specific purposes.
	//property


	// TEXT CHAR FORMAT
	bool												anchor				= false;
	QString												anchorHref			= "";
	QStringList											anchorNames;
	QFont												font				= QFont("Arial");
	QTextCharFormat::FontPropertiesInheritanceBehavior	behavior			= QTextCharFormat::FontPropertiesAll;// QTextCharFormat::FontPropertiesSpecifiedOnly	0	If a property is not explicitly set, do not change the text format's property value.
																												// QTextCharFormat::FontPropertiesAll			1	If a property is not explicitly set, override the text format's property with a default value.
	QPen												textOutline			= QPen(QColor("blue"));
	QString												toolTip				= "toolTip";
	QColor												underlineColor		= QColor("yellow");
	QTextCharFormat::UnderlineStyle						underlineStyle		= QTextCharFormat::NoUnderline;		// QTextCharFormat::NoUnderline			0	Text is draw without any underlining decoration.
																												// QTextCharFormat::SingleUnderline		1	A line is drawn using Qt::SolidLine.
																												// QTextCharFormat::DashUnderline		2	Dashes are drawn using Qt::DashLine.
																												// QTextCharFormat::DotLine				3	Dots are drawn using Qt::DotLine;
																												// QTextCharFormat::DashDotLine			4	Dashs and dots are drawn using Qt::DashDotLine.
																												// QTextCharFormat::DashDotDotLine		5	Underlines draw drawn using Qt::DashDotDotLine.
																												// QTextCharFormat::WaveUnderline		6	The text is underlined using a wave shaped line.
																												// QTextCharFormat::SpellCheckUnderline	7	The underline is drawn depending on the SpellCheckUnderlineStyle theme hint of QPlatformTheme. By default this is mapped to WaveUnderline, on macOS it is mapped to DotLine.
	QTextCharFormat::VerticalAlignment					verticalAlignment	= QTextCharFormat::AlignNormal;		// QTextCharFormat::AlignNormal			0	Adjacent characters are positioned in the standard way for text in the writing system in use.
																												// QTextCharFormat::AlignSuperScript	1	Characters are placed above the base line for normal text.
																												// QTextCharFormat::AlignSubScript		2	Characters are placed below the base line for normal text.
																												// QTextCharFormat::AlignMiddle			3	The center of the object is vertically aligned with the base line. Currently, this is only implemented for inline objects.
																												// QTextCharFormat::AlignBottom			5	The bottom edge of the object is vertically aligned with the base line.
																												// QTextCharFormat::AlignTop			4	The top edge of the object is vertically aligned with the base line.
																												// QTextCharFormat::AlignBaseline		6	The base lines of the characters are aligned.
	QBrush												background1			= QBrush(QColor("red"));
	QBrush												foreground1			= QBrush(QColor("green"));
	Qt::LayoutDirection									layoutDirection1	= Qt::LeftToRight;					// Qt::LeftToRight						0		Left-to-right layout.
																												// Qt::RightToLeft						1		Right-to-left layout.
																												// Qt::LayoutDirectionAuto				2		Automatic layout.
	int													objectIndex1		= 0;
	int													objectType1			= QTextFormat::NoObject;			// QTextFormat::NoObject				0
																												// QTextFormat::ImageObject				1
																												// QTextFormat::TableObject				2
																												// QTextFormat::TableCellObject			3
																												// QTextFormat::UserObject				0x1000	The first object that can be used for application-specific purposes.
	//property

	QTextBlockFormat	blockFormat1	= createTextBlockFormat(alignment, leftMargin, topMargin, rightMargin, bottomMargin, indent, lineHeight, lineHeightType, nonBreakableLines, pageBreakPolicy, tabPositions, textIndent, background, foreground, layoutDirection, objectIndex, objectType);
	QTextCharFormat		charFormat1		= createTextCharFormat(anchor, anchorHref, anchorNames, font, behavior, textOutline, toolTip, underlineColor, underlineStyle, verticalAlignment, background1, foreground1, layoutDirection1, objectIndex1, objectType1); // property);

	cursor.setBlockFormat(blockFormat1);
	cursor.setBlockCharFormat(charFormat1);

	cursor.insertText("TestText");
}

#include <QTextList>

void readWriteTest3()
{
	QTextCursor		cursor(g_lpInputDocument);

	QTextListFormat*	lpFormat		= new QTextListFormat;
	QString				numberSuffix	= lpFormat->numberSuffix();

	lpFormat->setNumberSuffix(".");
	numberSuffix	= lpFormat->numberSuffix();

	delete lpFormat;

	QTextList*	list1;
	QTextList*	list2;
	QTextList*	list3;
	QTextBlock	textBlock;

	QTextListFormat	format1;
	QTextListFormat	format2;
	QTextListFormat	format3;
	format1.setStyle(QTextListFormat::ListDecimal);
	format1.setIndent(1);
	format2.setStyle(QTextListFormat::ListLowerAlpha);
	format2.setIndent(2);
	format3.setStyle(QTextListFormat::ListUpperAlpha);
	format3.setIndent(3);

	list1	= cursor.insertList(format1);
							textBlock	= cursor.block();	cursor.insertText("Introduction");				list1->add(textBlock);
	cursor.insertBlock();	textBlock	= cursor.block();	cursor.insertText("Tools");						list1->add(textBlock);

	list2	= cursor.insertList(format2);
							textBlock	= cursor.block();	cursor.insertText("Assistant");					list2->add(textBlock);
	cursor.insertBlock();	textBlock	= cursor.block();	cursor.insertText("Designer");					list2->add(textBlock);

	list3	= cursor.insertList(format3);
							textBlock	= cursor.block();	cursor.insertText("Form Editor");				list3->add(textBlock);
	cursor.insertBlock();	textBlock	= cursor.block();	cursor.insertText("Component Architecture");	list3->add(textBlock);

	cursor.insertBlock();	textBlock	= cursor.block();	cursor.insertText("Qt Linguist");				list2->add(textBlock);
}

cMainWindow::cMainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::cMainWindow)
{
	ui->setupUi(this);
	ui->m_lpTabWidget->setCurrentIndex(0);

	g_lpInputDocument		= new cTextDocument(ui->m_lpInput);
	g_lpOutputDocument		= new cTextDocument(ui->m_lpOutput);

	ui->m_lpInput->setDocument(g_lpInputDocument);

	readWriteTest1();
//	readWriteTest2();
//	readWriteTest3();
}

cMainWindow::~cMainWindow()
{
	delete ui;

	if(g_lpInputDocument)
		delete g_lpInputDocument;

	if(g_lpOutputDocument)
		delete g_lpOutputDocument;
}

void cMainWindow::on_actionTest1_triggered()
{
	QTextBlockFormat	blockFormatStyle;
	blockFormatStyle.setBackground(QColor("red"));

	QTextCursor			cursor(g_lpInputDocument);
	cursor.setBlockFormat(blockFormatStyle);

	QTextCharFormat		charFormatStyle;

}

void cMainWindow::on_actionSave_triggered()
{
	g_lpInputDocument->saveAs("C:/Temp/documentText.xml");

	cDocumentReader	reader("C:/Temp/documentText.xml");
	reader.open();
	g_lpOutputDocument	= reader.readDocument();
	reader.close();

	ui->m_lpOutput->setDocument(g_lpOutputDocument);
}
