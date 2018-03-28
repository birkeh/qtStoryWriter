#include "cdocumentwriter.h"
#include "ctextdocument.h"

#include <QFileInfo>

#include <QDebug>


cDocumentWriter::cDocumentWriter(const QString &szFileName, bool bZip) :
	m_bZip(bZip),
	m_szFileName(szFileName),
	m_lpDocument(0)
{
	QFileInfo	fileInfo(szFileName);
	m_szPath	= fileInfo.absolutePath();
}

cDocumentWriter::~cDocumentWriter()
{
	close();
}

bool cDocumentWriter::open()
{
	if(m_szFileName.isEmpty())
		return(false);

	if(m_bZip)
	{
		m_zip.setZipName(m_szFileName);
		m_zip.open(QuaZip::mdCreate);

		QuaZipNewInfo	info("document.xml");
		m_zipFile.setZip(&m_zip);

		if(!m_zipFile.open(QIODevice::WriteOnly, info))
		{
			m_zip.close();
			return(false);
		}

		setDevice(&m_zipFile);
	}
	else
	{
		m_file.setFileName(m_szFileName);
		if(!m_file.open(QIODevice::WriteOnly | QFile::Text))
			return(false);

		setDevice(&m_file);
	}

	setAutoFormatting(true);
	setAutoFormattingIndent(-1);
	writeStartDocument();
	writeStartElement("document");

	return(true);
}

bool cDocumentWriter::close()
{
	if(m_bZip)
	{
		if(m_zipFile.isOpen())
		{
			writeEndElement();
			writeEndDocument();
			m_zipFile.close();
		}
	}
	else
	{
		if(m_file.isOpen())
		{
			writeEndElement();
			writeEndDocument();
			m_file.close();
		}
	}

	return(true);
}

bool cDocumentWriter::writeDocument(cTextDocument *lpDocument)
{
	m_lpDocument	= lpDocument;

	QList<QPair<int, QTextBlockFormat>>	textBlockFormats;
	QTextBlock							textBlock				= lpDocument->firstBlock();

	while(textBlock.isValid())
	{
		int	x;
		for(x = 0;x < textBlockFormats.count();x++)
		{
			if(textBlockFormats[x].first == textBlock.blockFormatIndex())
				break;
		}
		if(x >= textBlockFormats.count())
			textBlockFormats.append(QPair<int, QTextBlockFormat>(textBlock.blockFormatIndex(), textBlock.blockFormat()));

		textBlock	= textBlock.next();
	}

	writeStartElement("documentSettings");
		writeAttribute("documentMargin", QString::number(lpDocument->documentMargin()));
		writeAttribute("indentWidth", QString::number(lpDocument->indentWidth()));
		writeAttribute("textWidth", QString::number(lpDocument->textWidth()));
		writeAttribute("useDesignMetrics", lpDocument->useDesignMetrics() == true ? "true" : "false");

		writeStartElement("metaInformation");
			writeAttribute("documentTitle", lpDocument->metaInformation(QTextDocument::DocumentTitle));
			writeAttribute("documentUrl", lpDocument->metaInformation(QTextDocument::DocumentUrl));
		writeEndElement();

		writeStartElement("baseUrl");
			writeAttribute("authority", lpDocument->baseUrl().authority());
			writeAttribute("fragment", lpDocument->baseUrl().fragment());
			writeAttribute("host", lpDocument->baseUrl().host());
			writeAttribute("password", lpDocument->baseUrl().password());
			writeAttribute("path", lpDocument->baseUrl().path());
			writeAttribute("port", QString::number(lpDocument->baseUrl().port()));
			writeAttribute("query", lpDocument->baseUrl().query());
			writeAttribute("scheme", lpDocument->baseUrl().scheme());
			writeAttribute("url", lpDocument->baseUrl().url());
			writeAttribute("userInfo", lpDocument->baseUrl().userInfo());
			writeAttribute("userName", lpDocument->baseUrl().userName());
		writeEndElement();

		writeStartElement("pageSize");
			writeAttribute("width", QString::number(lpDocument->pageSize().width()));
			writeAttribute("height", QString::number(lpDocument->pageSize().height()));
		writeEndElement();
	writeEndElement();

	writeStartElement("defaults");
		writeAttribute("defaultCursorMoveStyle", QString::number(lpDocument->defaultCursorMoveStyle()));
		writeAttribute("defaultStyleSheet", lpDocument->defaultStyleSheet());

		writeStartElement("defaultFont");
		writeFont(lpDocument->defaultFont());
		writeEndElement();

		writeStartElement("defaultTextOption");
		writeTextOption(lpDocument->defaultTextOption());
		writeEndElement();
	writeEndElement();

	writeFormats(lpDocument->allFormats());
	writeTextBlockFormats(textBlockFormats);

	textBlock				= lpDocument->firstBlock();
	writeTextBlocks(textBlock);

	return(true);
}

void cDocumentWriter::writeTextBlockFormats(const QList<QPair<int, QTextBlockFormat>> textBlockFormats)
{
	writeStartElement("textBlockFormats");
	for(int x = 0;x < textBlockFormats.count();x++)
	{
		writeStartElement("format");
			writeFormat(textBlockFormats[x].second, textBlockFormats[x].first);
		writeEndElement();
	}
	writeEndElement();
}

void cDocumentWriter::writeTextBlocks(QTextBlock& textBlock)
{
	writeStartElement("textBlocks");
	while(textBlock.isValid())
	{
		writeStartElement("textBlock");
			writeTextBlock(textBlock);
		writeEndElement();
		textBlock	= textBlock.next();
	}
	writeEndElement();
}

#include <QTextList>
#include <QTextTable>

void cDocumentWriter::writeTextBlock(const QTextBlock& textBlock)
{
	QTextCursor	cursor(textBlock);
	QTextList*	lpTextList	= cursor.currentList();
	QTextTable*	lpTextTable	= cursor.currentTable();

	writeAttribute("blockFormatIndex", QString::number(textBlock.blockFormatIndex()));
	writeAttribute("charFormatIndex", QString::number(textBlock.charFormatIndex()));
	writeAttribute("listFormatIndex", QString::number(lpTextList == 0 ? -1 : lpTextList->formatIndex()));
	writeAttribute("tableFormatIndex", QString::number(lpTextTable == 0 ? -1 : lpTextTable->formatIndex()));

	QVector<QTextLayout::FormatRange>	textFormats	= textBlock.textFormats();
	writeStartElement("textFormats");
		for(int x = 0;x < textFormats.count();x++)
		{
			QTextLayout::FormatRange	range	= textFormats[x];
			QTextCharFormat				format	= range.format;
			writeStartElement("range");
			writeAttribute("start", QString::number(range.start));
			writeAttribute("length", QString::number(range.length));
			writeTextCharFormat((QTextCharFormat*)&format, -1, WriteAttribute);
			writeTextFormat((QTextFormat*)&format, -1, WriteAll);
			writeTextCharFormat((QTextCharFormat*)&format, -1, WriteElements);
			writeEndElement();
		}
	writeEndElement();

	writeTextElement("text", textBlock.text());
}

void cDocumentWriter::writeColor(QColor color)
{
	writeAttribute("alpha", QString::number(color.alpha()));
	writeAttribute("r", QString::number(color.red()));
	writeAttribute("g", QString::number(color.green()));
	writeAttribute("b", QString::number(color.blue()));
}

void cDocumentWriter::writeGradient(const QGradient* lpGradient)
{
	writeAttribute("type", QString::number(lpGradient->type()));
	writeTextElement("spread", QString::number(lpGradient->spread()));

	for(int x = 0;x < lpGradient->stops().count();x++)
	{
		writeStartElement("stop");
			writeAttribute("pos", QString::number(lpGradient->stops()[x].first));

			writeStartElement("color");
				writeColor(lpGradient->stops()[x].second);
			writeEndElement();

		writeEndElement();
	}
}

void cDocumentWriter::writePen(const QPen& pen)
{
	writeAttribute("capStyle", QString::number(pen.capStyle()));
	writeAttribute("dashOffset", QString::number(pen.dashOffset()));
	writeAttribute("isCosmetic", pen.isCosmetic() == true ? "true" : "false");
	writeAttribute("joinStyle", QString::number(pen.joinStyle()));
	writeAttribute("miterLimit", QString::number(pen.miterLimit()));
	writeAttribute("style", QString::number(pen.style()));
	writeAttribute("width", QString::number(pen.width()));
	writeAttribute("widthF", QString::number(pen.widthF()));

	writeStartElement("brush");
		writeBrush(pen.brush());
	writeEndElement();

	writeStartElement("color");
		writeColor(pen.color());
	writeEndElement();

	if(pen.dashPattern().count())
	{
		writeStartElement("dashPattern");
		for(int x = 0;x < pen.dashPattern().count();x++)
			writeTextElement("pattern", QString::number(pen.dashPattern()[x]));
		writeEndElement();
	}
}

void cDocumentWriter::writeBrush(const QBrush& brush)
{
	writeAttribute("style", QString::number(brush.style()));

	writeStartElement("color");
		writeColor(brush.color());
	writeEndElement();

	if(brush.gradient())
	{
		writeStartElement("gradient");
			writeGradient(brush.gradient());
		writeEndElement();
	}

	//matrix
	//texture oder textureImage
}

void cDocumentWriter::writeFont(const QFont& font)
{
	writeAttribute("bold", font.bold() == true ? "true" : "false");
	writeAttribute("capitalization", QString::number(font.capitalization()));
//	writeAttribute("defaultFamily", font.defaultFamily());
//	writeAttribute("exactMatch", font.exactMatch() == true ? "true" : "false");
	writeAttribute("family", font.family());
	writeAttribute("fixedPitch", font.fixedPitch() == true ? "true" : "false");
	writeAttribute("hintingPreference", QString::number(font.hintingPreference()));
	writeAttribute("italic", font.italic() == true ? "true" : "false");
	writeAttribute("kerning", font.kerning() == true ? "true" : "false");
	writeAttribute("letterSpacing", QString::number(font.letterSpacing()));
	writeAttribute("letterSpacingType", QString::number(font.letterSpacingType()));
	writeAttribute("overline", QString::number(font.overline()));
	writeAttribute("pixelSize", QString::number(font.pixelSize()));
	writeAttribute("pointSize", QString::number(font.pointSize()));
	writeAttribute("pointSizeF", QString::number(font.pointSizeF()));
	writeAttribute("stretch", QString::number(font.stretch()));
	writeAttribute("strikeOut", font.strikeOut() == true ? "true" : "false");
	writeAttribute("style", QString::number(font.style()));
	writeAttribute("styleHint", QString::number(font.styleHint()));
	writeAttribute("styleName", font.styleName());
	writeAttribute("styleStrategy", QString::number(font.styleStrategy()));
	writeAttribute("underline", font.underline() == true ? "true" : "false");
	writeAttribute("weight", QString::number(font.weight()));
	writeAttribute("wordSpacing", QString::number(font.wordSpacing()));
}

void cDocumentWriter::writeFormat(const QTextFormat& textFormat, int id)
{
	writeAttribute("type", QString::number(textFormat.type()));

	if(textFormat.isTableCellFormat())
	{
		writeAttribute("typeText", "tableCellFormat");
		writeTextTableCellFormat((QTextTableCellFormat*)&textFormat, id, WriteAttribute);
		writeTextCharFormat((QTextCharFormat*)&textFormat, id, WriteAttribute);
		writeTextFormat((QTextFormat*)&textFormat, id, WriteAll);
		writeTextTableCellFormat((QTextTableCellFormat*)&textFormat, id, WriteElements);
		writeTextCharFormat((QTextCharFormat*)&textFormat, id, WriteElements);
	}
	else if(textFormat.isTableFormat())
	{
		writeAttribute("typeText", "tableFormat");
		writeTextTableFormat((QTextTableFormat*)&textFormat, id, WriteAttribute);
		writeTextFrameFormat((QTextFrameFormat*)&textFormat, id, WriteAttribute);
		writeTextFormat((QTextFormat*)&textFormat, id, WriteAll);
		writeTextTableFormat((QTextTableFormat*)&textFormat, id, WriteElements);
		writeTextFrameFormat((QTextFrameFormat*)&textFormat, id, WriteElements);
	}
	else if(textFormat.isImageFormat())
	{
		writeAttribute("typeText", "imageFormat");
		writeTextImageFormat((QTextImageFormat*)&textFormat, id, WriteAttribute);
		writeTextCharFormat((QTextCharFormat*)&textFormat, id, WriteAttribute);
		writeTextFormat((QTextFormat*)&textFormat, id, WriteAll);
		writeTextImageFormat((QTextImageFormat*)&textFormat, id, WriteElements);
		writeTextCharFormat((QTextCharFormat*)&textFormat, id, WriteElements);
	}
	else if(textFormat.isFrameFormat())
	{
		writeAttribute("typeText", "frameFormat");
		writeTextFrameFormat((QTextFrameFormat*)&textFormat, id, WriteAttribute);
		writeTextFormat((QTextFormat*)&textFormat, id, WriteAll);
		writeTextFrameFormat((QTextFrameFormat*)&textFormat, id, WriteElements);
	}
	else if(textFormat.isListFormat())
	{
		writeAttribute("typeText", "listFormat");
		writeTextListFormat((QTextListFormat*)&textFormat, id, WriteAttribute);
		writeTextFormat((QTextFormat*)&textFormat, id, WriteAll);
		writeTextListFormat((QTextListFormat*)&textFormat, id, WriteElements);
	}
	else if(textFormat.isBlockFormat())
	{
		writeAttribute("typeText", "blockFormat");
		writeTextBlockFormat((QTextBlockFormat*)&textFormat, id, WriteAttribute);
		writeTextFormat((QTextFormat*)&textFormat, id, WriteAll);
		writeTextBlockFormat((QTextBlockFormat*)&textFormat, id, WriteElements);
	}
	else if(textFormat.isCharFormat())
	{
		writeAttribute("typeText", "charFormat");
		writeTextCharFormat((QTextCharFormat*)&textFormat, id, WriteAttribute);
		writeTextFormat((QTextFormat*)&textFormat, id, WriteAll);
		writeTextCharFormat((QTextCharFormat*)&textFormat, id, WriteElements);
	}
}

void cDocumentWriter::writeTextFormat(QTextFormat* lpTextFormat, int /*id*/, WritePart part)
{
	if(lpTextFormat->isValid())
	{
		if(part & WriteAttribute)
		{
			writeAttribute("layoutDirection", QString::number(lpTextFormat->layoutDirection()));
		}

		if(part & WriteElements)
		{
			writeStartElement("background");
				writeBrush(lpTextFormat->background());
			writeEndElement();

			writeStartElement("foreground");
				writeBrush(lpTextFormat->foreground());
			writeEndElement();

			writeStartElement("properties");
				QMap<int, QVariant>			properties = lpTextFormat->properties();
				QMapIterator<int, QVariant> property(properties);

				while(property.hasNext())
				{
					property.next();

					writeStartElement("property");
						writeAttribute("key", QString::number(property.key()));
						writeAttribute("type", QString::number(property.value().type()));
						writeTextElement("value", property.value().toString());
					writeEndElement();
				}
			writeEndElement();
		}
	}
}

void cDocumentWriter::writeFormats(const QVector<QTextFormat> formats)
{
	writeStartElement("allFormats");
		for(int x = 0;x < formats.count();x++)
		{
			writeStartElement("format");
				writeAttribute("id", QString::number(x));
				writeFormat(formats[x]);
			writeEndElement();
		}
	writeEndElement();
}

void cDocumentWriter::writeTabPositions(const QList<QTextOption::Tab> tabs)
{
	for(int x = 0;x < tabs.count();x++)
	{
		QTextOption::Tab	tab	= tabs[x];
		writeStartElement("tabPosition");
			writeAttribute("delimiter", tab.delimiter);
			writeAttribute("position", QString::number(tab.position));
			writeAttribute("type", QString::number(tab.type));
		writeEndElement();
	}
}

void cDocumentWriter::writeTextBlockFormat(QTextBlockFormat* lpTextBlockFormat, int id, WritePart part)
{
	if(part & WriteAttribute && id != -1)
		writeAttribute("id", QString::number(id));

	if(lpTextBlockFormat->isValid())
	{
		if(part & WriteAttribute)
		{
			writeAttribute("alignment", QString::number(lpTextBlockFormat->alignment()));
			writeAttribute("topMargin", QString::number(lpTextBlockFormat->topMargin()));
			writeAttribute("leftMargin", QString::number(lpTextBlockFormat->leftMargin()));
			writeAttribute("bottomMargin", QString::number(lpTextBlockFormat->bottomMargin()));
			writeAttribute("rightMargin", QString::number(lpTextBlockFormat->rightMargin()));
			writeAttribute("indent", QString::number(lpTextBlockFormat->indent()));
			writeAttribute("lineHeight", QString::number(lpTextBlockFormat->lineHeight()));
			writeAttribute("lineHeightType", QString::number(lpTextBlockFormat->lineHeightType()));
			writeAttribute("nonBreakableLines", lpTextBlockFormat->nonBreakableLines() == true ? "true" : "false");
			writeAttribute("pageBreakPolicy", QString::number(lpTextBlockFormat->pageBreakPolicy()));
			writeAttribute("textIndent", QString::number(lpTextBlockFormat->textIndent()));
		}

		if(part & WriteElements)
		{
			writeStartElement("tabPositions");
				writeTabPositions(lpTextBlockFormat->tabPositions());
			writeEndElement();
		}
	}
}

void cDocumentWriter::writeTextCharFormat(QTextCharFormat* lpTextCharFormat, int id, WritePart part)
{
	if(part & WriteAttribute && id != -1)
		writeAttribute("id", QString::number(id));

	if(lpTextCharFormat->isValid())
	{
		if(part & WriteAttribute)
		{
			writeAttribute("anchorHref", lpTextCharFormat->anchorHref());
//			writeAttribute("fontCapitalization", QString::number(lpTextCharFormat->fontCapitalization()));
//			writeAttribute("fontFamily", lpTextCharFormat->fontFamily());
//			writeAttribute("fontFixedPitch", lpTextCharFormat->fontFixedPitch() == true ? "true" : "false");
//			writeAttribute("fontHintingPreference", QString::number(lpTextCharFormat->fontHintingPreference()));
//			writeAttribute("fontItalic", lpTextCharFormat->fontItalic() == true ? "true" : "false");
//			writeAttribute("fontKerning", lpTextCharFormat->fontKerning() == true ? "true" : "false");
//			writeAttribute("fontLetterSpacing", QString::number(lpTextCharFormat->fontLetterSpacing()));
//			writeAttribute("fontLetterSpacingType", QString::number(lpTextCharFormat->fontLetterSpacingType()));
//			writeAttribute("fontOverline", QString::number(lpTextCharFormat->fontOverline()));
//			writeAttribute("fontPointSize", QString::number(lpTextCharFormat->fontPointSize()));
//			writeAttribute("fontStretch", QString::number(lpTextCharFormat->fontStretch()));
//			writeAttribute("fontStrikeOut", lpTextCharFormat->fontStrikeOut() == true ? "true" : "false");
//			writeAttribute("fontStyleHint", QString::number(lpTextCharFormat->fontStyleHint()));
//			writeAttribute("fontStyleStrategy", QString::number(lpTextCharFormat->fontStyleStrategy()));
//			writeAttribute("fontUnderline", lpTextCharFormat->fontUnderline() == true ? "true" : "false");
//			writeAttribute("fontWeight", QString::number(lpTextCharFormat->fontWeight()));
//			writeAttribute("fontWordSpacing", QString::number(lpTextCharFormat->fontWordSpacing()));
			writeAttribute("isAnchor", lpTextCharFormat->isAnchor() == true ? "true" : "false");
			writeAttribute("toolTip", lpTextCharFormat->toolTip());
			writeAttribute("verticalAlignment", QString::number(lpTextCharFormat->verticalAlignment()));
		}

		if(part & WriteElements)
		{
			writeStartElement("textOutline");
				writePen(lpTextCharFormat->textOutline());
			writeEndElement();

			writeStartElement("anchorNames");
				for(int x = 0;x < lpTextCharFormat->anchorNames().count();x++)
					writeTextElement("anchor", lpTextCharFormat->anchorNames()[x]);
			writeEndElement();

			writeStartElement("font");
				writeFont(lpTextCharFormat->font());
			writeEndElement();

			writeStartElement("underlineColor");
				writeColor(lpTextCharFormat->underlineColor());
			writeEndElement();
		}
	}
}

void cDocumentWriter::writeTextFrameFormat(QTextFrameFormat* lpTextFrameFormat, int id, WritePart part)
{
	if(part & WriteAttribute && id != -1)
		writeAttribute("id", QString::number(id));

	if(lpTextFrameFormat->isValid())
	{
		if(part & WriteAttribute)
		{
			writeAttribute("border", QString::number(lpTextFrameFormat->border()));
			writeAttribute("borderStyle", QString::number(lpTextFrameFormat->borderStyle()));
			writeAttribute("margin", QString::number(lpTextFrameFormat->margin()));
			writeAttribute("leftMargin", QString::number(lpTextFrameFormat->leftMargin()));
			writeAttribute("topMargin", QString::number(lpTextFrameFormat->topMargin()));
			writeAttribute("rightMargin", QString::number(lpTextFrameFormat->rightMargin()));
			writeAttribute("bottomMargin", QString::number(lpTextFrameFormat->bottomMargin()));
			writeAttribute("width", QString::number(lpTextFrameFormat->width().rawValue()));
			writeAttribute("height", QString::number(lpTextFrameFormat->height().rawValue()));
			writeAttribute("padding", QString::number(lpTextFrameFormat->padding()));
			writeAttribute("pageBreakPolicy", QString::number(lpTextFrameFormat->pageBreakPolicy()));
			writeAttribute("position", QString::number(lpTextFrameFormat->position()));
		}

		if(part & WriteElements)
		{
			writeStartElement("borderBrush");
				writeBrush(lpTextFrameFormat->borderBrush());
			writeEndElement();
		}
	}
}

void cDocumentWriter::writeTextImageFormat(QTextImageFormat* lpTextImageFormat, int id, WritePart part)
{
	if(part & WriteAttribute && id != -1)
		writeAttribute("id", QString::number(id));

	if(lpTextImageFormat->isValid())
	{
		if(part & WriteAttribute)
		{
			writeAttribute("name", lpTextImageFormat->name());
			writeAttribute("height", QString::number(lpTextImageFormat->height()));
			writeAttribute("width", QString::number(lpTextImageFormat->width()));
		}

		if(m_lpDocument)
		{
			QPixmap		pixmap		= m_lpDocument->resource(2, lpTextImageFormat->name()).value<QPixmap>();
			if(!pixmap.isNull())
			{
				QString	name		= lpTextImageFormat->name();
				if(name.left(1) == ':')
					name	= name.mid(1);
				if(name.left(1) == '/')
					name	= name.mid(1);

				name	= m_szPath + "/" + name;
				QString	path	= name.left(name.lastIndexOf("/"));

				QDir	dir;
				dir.mkpath(path);
				pixmap.save(name);
			}

		}
	}
}

void cDocumentWriter::writeTextListFormat(QTextListFormat* lpTextListFormat, int id, WritePart part)
{
	if(part & WriteAttribute && id != -1)
		writeAttribute("id", QString::number(id));

	if(lpTextListFormat->isValid())
	{
		if(part & WriteAttribute)
		{
			writeAttribute("indent", QString::number(lpTextListFormat->indent()));
			writeAttribute("numberPrefix", lpTextListFormat->numberPrefix());
			writeAttribute("numberSuffix", lpTextListFormat->numberSuffix());
			writeAttribute("style", QString::number(lpTextListFormat->style()));
		}
	}
}

void cDocumentWriter::writeTextTableCellFormat(QTextTableCellFormat* lpTextTableCellFormat, int id, WritePart part)
{
	if(part & WriteAttribute && id != -1)
		writeAttribute("id", QString::number(id));

	if(lpTextTableCellFormat->isValid())
	{
		if(part & WriteAttribute)
		{
			writeAttribute("leftPadding", QString::number(lpTextTableCellFormat->leftPadding()));
			writeAttribute("topPadding", QString::number(lpTextTableCellFormat->topPadding()));
			writeAttribute("rightPadding", QString::number(lpTextTableCellFormat->rightPadding()));
			writeAttribute("bottomPadding", QString::number(lpTextTableCellFormat->bottomPadding()));
		}
	}
}

void cDocumentWriter::writeTextTableFormat(QTextTableFormat* lpTextTableFormat, int id, WritePart part)
{
	if(part & WriteAttribute && id != -1)
		writeAttribute("id", QString::number(id));

	if(lpTextTableFormat->isValid())
	{
		if(part & WriteAttribute)
		{
			writeAttribute("alignment", QString::number(lpTextTableFormat->alignment()));
			writeAttribute("cellPadding", QString::number(lpTextTableFormat->cellPadding()));
			writeAttribute("cellSpacing", QString::number(lpTextTableFormat->cellSpacing()));
			writeAttribute("columns", QString::number(lpTextTableFormat->columns()));
			writeAttribute("headerRowCount", QString::number(lpTextTableFormat->headerRowCount()));
		}

		if(part & WriteElements)
		{
			if(lpTextTableFormat->columnWidthConstraints().count())
			{
				writeStartElement("columnWidthConstraints");
				for(int x = 0;x < lpTextTableFormat->columnWidthConstraints().count();x++)
				{
					writeStartElement("columnWidthConstraint");
						writeAttribute("rawValue", QString::number(lpTextTableFormat->columnWidthConstraints()[x].rawValue()));
						writeAttribute("type", QString::number(lpTextTableFormat->columnWidthConstraints()[x].type()));
					writeEndElement();
				}
				writeEndElement();
			}
		}
	}
}

void cDocumentWriter::writeTextOption(const QTextOption& textOption)
{
	writeAttribute("alignment", QString::number(textOption.alignment()));
	writeAttribute("flags", QString::number(textOption.flags()));
	writeAttribute("tabStopDistance", QString::number(textOption.tabStopDistance()));
	writeAttribute("textDirection", QString::number(textOption.textDirection()));
	writeAttribute("useDesignMetrics", textOption.useDesignMetrics() == true ? "true" : "false");
	writeAttribute("wrapMode", QString::number(textOption.wrapMode()));

	writeStartElement("tabArray");
	for(int x = 0;x < textOption.tabArray().count();x++)
		writeTextElement("tab", QString::number(textOption.tabArray()[x]));
	writeEndElement();

	writeStartElement("tabs");
		writeTabPositions(textOption.tabs());
	writeEndElement();
}
