/*!
 \file ctextedit.cpp

*/

#include "common.h"

#include "ctextedit.h"

#include "cmainwindow.h"

#include <QMimeData>
#include <QFileInfo>
#include <QFile>
#include <QImageReader>

#include <QFocusEvent>
#include <QApplication>

#include <QTextList>
#include <QColorDialog>


cTextEdit::cTextEdit(QWidget* parent) :
	QTextEdit(parent)
{
	connect(this, &cTextEdit::currentCharFormatChanged, this, &cTextEdit::onCurrentCharFormatChanged);
	connect(this, &cTextEdit::cursorPositionChanged, this, &cTextEdit::onCursorPositionChanged);

	foreach(QWidget *w, qApp->topLevelWidgets())
	{
		m_lpMainWindow = qobject_cast<cMainWindow*>(w);
		if(m_lpMainWindow)
			return;
	}
	m_lpMainWindow	= 0;
}

cTextEdit::cTextEdit(const QString& text, QWidget* parent) :
	QTextEdit(text, parent)
{
}

bool cTextEdit::canInsertFromMimeData(const QMimeData* source) const
{
	return source->hasImage() || source->hasUrls() || QTextEdit::canInsertFromMimeData(source);
}

void cTextEdit::insertFromMimeData(const QMimeData* source)
{
	if(source->hasImage())
	{
		static int i = 1;
		QUrl url(QString("dropped_image_%1").arg(i++));
		dropImage(url, qvariant_cast<QImage>(source->imageData()));
	}
	else if(source->hasUrls())
	{
		foreach(QUrl url, source->urls())
		{
			QFileInfo info(url.toLocalFile());
			if(QImageReader::supportedImageFormats().contains(info.suffix().toLower().toLatin1()))
				dropImage(url, QImage(info.filePath()));
			else
				dropTextFile(url);
		}
	}
	else
	{
		QTextEdit::insertFromMimeData(source);
	}
}

void cTextEdit::dropImage(const QUrl& url, const QImage& image)
{
	if(!image.isNull())
	{
		document()->addResource(QTextDocument::ImageResource, url, image);
		textCursor().insertImage(url.toString());
	}
}

void cTextEdit::dropTextFile(const QUrl& url)
{
	QFile file(url.toLocalFile());
	if(file.open(QIODevice::ReadOnly | QIODevice::Text))
		textCursor().insertText(file.readAll());
}

void cTextEdit::focusInEvent(QFocusEvent* event)
{
	gotFocus(this);
	QTextEdit::focusInEvent(event);
}

void cTextEdit::focusOutEvent(QFocusEvent* event)
{
	lostFocus(this);
	QTextEdit::focusOutEvent(event);
}

void cTextEdit::onCurrentCharFormatChanged(const QTextCharFormat &format)
{
	fontChanged(format.font());
	colorChanged(format.foreground().color());
}

void cTextEdit::onCursorPositionChanged()
{
	alignmentChanged(alignment());
}

void cTextEdit::onTextBold(bool isChecked)
{
	QTextCharFormat fmt;
	fmt.setFontWeight(isChecked ? QFont::Bold : QFont::Normal);
	mergeFormatOnWordOrSelection(fmt);
}

void cTextEdit::onTextUnderline(bool isChecked)
{
	QTextCharFormat fmt;
	fmt.setFontUnderline(isChecked);
	mergeFormatOnWordOrSelection(fmt);
}

void cTextEdit::onTextItalic(bool isChecked)
{
	QTextCharFormat fmt;
	fmt.setFontItalic(isChecked);
	mergeFormatOnWordOrSelection(fmt);
}

void cTextEdit::onTextAlign(QAction *a)
{
	if(!m_lpMainWindow)
		return;

	if(a == m_lpMainWindow->actionAlignLeft())
		setAlignment(Qt::AlignLeft | Qt::AlignAbsolute);
	else if(a == m_lpMainWindow->actionAlignCenter())
		setAlignment(Qt::AlignHCenter);
	else if(a == m_lpMainWindow->actionAlignRight())
		setAlignment(Qt::AlignRight | Qt::AlignAbsolute);
	else if(a == m_lpMainWindow->actionAlignJustify())
		setAlignment(Qt::AlignJustify);
}

void cTextEdit::onTextFamily(const QString &f)
{
	QTextCharFormat	fmt;
	fmt.setFontFamilies(QStringList() << f);
	mergeFormatOnWordOrSelection(fmt);
}

void cTextEdit::onTextSize(const QString &p)
{
	qreal pointSize = p.toFloat();
	if(p.toFloat() > 0)
	{
		QTextCharFormat	fmt;
		fmt.setFontPointSize(pointSize);
		mergeFormatOnWordOrSelection(fmt);
	}
}

void cTextEdit::onTextColor()
{
	QColor col = QColorDialog::getColor(textColor(), this);
	if(!col.isValid())
		return;
	QTextCharFormat fmt;
	fmt.setForeground(col);
	mergeFormatOnWordOrSelection(fmt);
//	colorChanged(col);
}

void cTextEdit::onTextStyle(int styleIndex)
{
	QTextCursor	cursor	= textCursor();

	if(styleIndex != 0)
	{
		QTextListFormat::Style style = QTextListFormat::ListDisc;

		switch(styleIndex)
		{
		default:
		case 1:
			style = QTextListFormat::ListDisc;
			break;
		case 2:
			style = QTextListFormat::ListCircle;
			break;
		case 3:
			style = QTextListFormat::ListSquare;
			break;
		case 4:
			style = QTextListFormat::ListDecimal;
			break;
		case 5:
			style = QTextListFormat::ListLowerAlpha;
			break;
		case 6:
			style = QTextListFormat::ListUpperAlpha;
			break;
		case 7:
			style = QTextListFormat::ListLowerRoman;
			break;
		case 8:
			style = QTextListFormat::ListUpperRoman;
			break;
		}

		cursor.beginEditBlock();

		QTextBlockFormat	blockFmt	= cursor.blockFormat();
		QTextListFormat		listFmt;

		if(cursor.currentList())
		{
			listFmt = cursor.currentList()->format();
		}
		else
		{
			listFmt.setIndent(blockFmt.indent() + 1);
			blockFmt.setIndent(0);
			cursor.setBlockFormat(blockFmt);
		}

		listFmt.setStyle(style);

		cursor.createList(listFmt);

		cursor.endEditBlock();
	}
	else
	{
		QTextBlockFormat bfmt;
		bfmt.setObjectIndex(-1);
		cursor.mergeBlockFormat(bfmt);
	}
}

void cTextEdit::mergeFormatOnWordOrSelection(const QTextCharFormat &format)
{
	QTextCursor cursor = textCursor();
	if(!cursor.hasSelection())
		cursor.select(QTextCursor::WordUnderCursor);
	cursor.mergeCharFormat(format);
	mergeCurrentCharFormat(format);
}
