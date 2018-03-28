#include "cdocumentreader.h"
#include "ctextdocument.h"

#include "common.h"

#include <JlCompress.h>

#include <QString>
#include <QUrl>

#include <QTextList>

#include <QDomNode>
#include <QDomNamedNodeMap>

cDocumentReader::cDocumentReader(const QString &szFileName, bool bZip) :
	m_bFirstBlock(true),
	m_bZip(bZip),
	m_szFileName(szFileName)
{
}

cDocumentReader::~cDocumentReader()
{
	close();
}

bool cDocumentReader::open()
{
	if(m_bZip)
	{
		m_zip.setZipName(m_szFileName);

		if(!m_zip.open(QuaZip::mdUnzip))
			return(false);

		m_zip.setCurrentFile("document.xml");
		m_zipFile.setZip(&m_zip);

		if(!m_zipFile.open(QIODevice::ReadOnly))
		{
			m_zip.close();
			return(false);
		}
	}
	else
	{
		m_file.setFileName(m_szFileName);

		if(!m_file.open(QIODevice::ReadOnly))
			return(false);
	}

	return(true);
}

bool cDocumentReader::close()
{
	if(m_bZip)
	{
		if(m_zip.isOpen())
		{
			if(m_zipFile.isOpen())
				m_zipFile.close();
			m_zip.close();
		}
	}
	else
	{
		if(m_file.isOpen())
			m_file.close();
	}

	return(true);
}

cTextDocument* cDocumentReader::readDocument()
{
	if(!open())
		return(0);

	cTextDocument*		lpDocument;
	QDomDocument		doc;
	QString				errorStr;
	int					errorLine;
	int					errorColumn;

	if(m_bZip)
	{
		if(!doc.setContent(&m_zipFile, false, &errorStr, &errorLine, &errorColumn))
			return(0);
	}
	else
	{
		if(!doc.setContent(&m_file, false, &errorStr, &errorLine, &errorColumn))
			return(0);
	}

	QDomElement				root	= doc.documentElement();
	if(root.tagName().compare("document", Qt::CaseInsensitive))
		return(0);

	lpDocument						= new cTextDocument;
	QDomNode				child	= root.firstChild();
	QVector<cTextFormat>	allFormats;

	QTextCursor				cursor(lpDocument);

	while(!child.isNull())
	{
		if(!child.toElement().tagName().compare("documentSettings", Qt::CaseInsensitive))
			parseSettings(child.toElement(), lpDocument);
		else if(!child.toElement().tagName().compare("defaults", Qt::CaseInsensitive))
			parseDefaults(child.toElement(), lpDocument);
		else if(!child.toElement().tagName().compare("allFormats", Qt::CaseInsensitive))
			allFormats	= parseAllFormats(child.toElement());
		else if(!child.toElement().tagName().compare("textBlockFormats", Qt::CaseInsensitive))
		{
			// SHOULD BE COVERED BY TEXTBLOCKS
		}
		else if(!child.toElement().tagName().compare("textBlocks", Qt::CaseInsensitive))
		{
			QDomNode				block	= child.firstChild();

			while(!block.isNull())
			{
				if(!block.toElement().tagName().compare("textBlock", Qt::CaseInsensitive))
					parseTextBlock(block.toElement(), &cursor, allFormats);
				else
					myDebug << "readDocument: unknown element: " << child.toElement().tagName();

				block	= block.nextSibling();
			}
		}
		else
			myDebug << "readDocument: unknown element: " << child.toElement().tagName();

		child	= child.nextSibling();
	}

	close();

	return(lpDocument);
}

void cDocumentReader::parseSettings(const QDomElement &element, cTextDocument* lpDocument)
{
	QDomNamedNodeMap	attributes	= element.attributes();
	for(int x = 0;x < attributes.count();x++)
	{
		QDomNode	node	= attributes.item(x);

		if(!node.toAttr().name().compare("documentMargin", Qt::CaseInsensitive))
			lpDocument->setDocumentMargin(node.toAttr().nodeValue().toDouble());
		else if(!node.toAttr().name().compare("indentWidth", Qt::CaseInsensitive))
			lpDocument->setIndentWidth(node.toAttr().nodeValue().toDouble());
		else if(!node.toAttr().name().compare("textWidth", Qt::CaseInsensitive))
			lpDocument->setTextWidth(node.toAttr().nodeValue().toDouble());
		else if(!node.toAttr().name().compare("useDesignMetrics", Qt::CaseInsensitive))
			lpDocument->setUseDesignMetrics(node.toAttr().nodeValue().compare("true", Qt::CaseInsensitive) == 0 ? true : false);
		else
			myDebug << "parseSettings: unknown attribute: " << node.toAttr().name();
	}

	QDomNode			child		= element.firstChild();

	while(!child.isNull())
	{
		if(!child.toElement().tagName().compare("metaInformation", Qt::CaseInsensitive))
		{
			attributes	= child.toElement().attributes();
			for(int x = 0;x < attributes.count();x++)
			{
				QDomNode	node	= attributes.item(x);
				if(!node.toAttr().name().compare("documentTitle", Qt::CaseInsensitive))
					lpDocument->setMetaInformation(QTextDocument::DocumentTitle, node.toAttr().nodeValue());
				else if(!node.toAttr().name().compare("documentUrl", Qt::CaseInsensitive))
					lpDocument->setMetaInformation(QTextDocument::DocumentUrl, node.toAttr().nodeValue());
				else
					myDebug << "parseSettings: unknown attribute: " << node.toAttr().name();
			}
		}
		else if(!child.toElement().tagName().compare("baseUrl", Qt::CaseInsensitive))
		{
			attributes	= child.toElement().attributes();
			QString	authority;
			QString	fragment;
			QString	host;
			QString	password;
			QString	path;
			int		port;
			QString	query;
			QString	scheme;
			QString	urlName;
			QString	userInfo;
			QString	userName;

			for(int x = 0;x < attributes.count();x++)
			{
				QDomNode	node	= attributes.item(x);
				if(!node.toAttr().name().compare("authority", Qt::CaseInsensitive))
					authority	= node.toAttr().nodeValue();
				else if(!node.toAttr().name().compare("fragment", Qt::CaseInsensitive))
					fragment	= node.toAttr().nodeValue();
				else if(!node.toAttr().name().compare("host", Qt::CaseInsensitive))
					host		= node.toAttr().nodeValue();
				else if(!node.toAttr().name().compare("password", Qt::CaseInsensitive))
					password	= node.toAttr().nodeValue();
				else if(!node.toAttr().name().compare("path", Qt::CaseInsensitive))
					path		= node.toAttr().nodeValue();
				else if(!node.toAttr().name().compare("port", Qt::CaseInsensitive))
					port		= node.toAttr().nodeValue().toInt();
				else if(!node.toAttr().name().compare("query", Qt::CaseInsensitive))
					query		= node.toAttr().nodeValue();
				else if(!node.toAttr().name().compare("scheme", Qt::CaseInsensitive))
					scheme		= node.toAttr().nodeValue();
				else if(!node.toAttr().name().compare("url", Qt::CaseInsensitive))
					urlName		= node.toAttr().nodeValue();
				else if(!node.toAttr().name().compare("userInfo", Qt::CaseInsensitive))
					userInfo	= node.toAttr().nodeValue();
				else if(!node.toAttr().name().compare("userName", Qt::CaseInsensitive))
					userName	=node.toAttr().nodeValue();
				else
					myDebug << "parseSettings: unknown attribute: " << node.toAttr().name();
			}

			if(!urlName.isEmpty())
			{
				QUrl	url(urlName);
				url.setAuthority(authority);
				url.setFragment(fragment);
				url.setHost(host);
				url.setPassword(password);
				url.setPath(path);
				url.setPort(port);
				url.setQuery(query);
				url.setScheme(scheme);
				url.setUserInfo(userInfo);
				url.setUserName(userName);

				if(url.isValid())
					lpDocument->setBaseUrl(url);
			}
		}
		else if(!child.toElement().tagName().compare("pageSize", Qt::CaseInsensitive))
		{
			attributes	= child.toElement().attributes();
			QSizeF	size;

			for(int x = 0;x < attributes.count();x++)
			{
				QDomNode	node	= attributes.item(x);
				if(!node.toAttr().name().compare("width", Qt::CaseInsensitive))
					size.setWidth(node.toAttr().nodeValue().toDouble());
				else if(!node.toAttr().name().compare("height", Qt::CaseInsensitive))
					size.setHeight(node.toAttr().nodeValue().toDouble());
			}
			if(size.isValid())
				lpDocument->setPageSize(size);
		}
		else
			myDebug << "parseSettings: unknown element: " << child.toElement().tagName();

		child	= child.nextSibling();
	}
}

void cDocumentReader::parseDefaults(const QDomElement &element, cTextDocument* lpDocument)
{
	QDomNamedNodeMap	attributes	= element.attributes();
	for(int x = 0;x < attributes.count();x++)
	{
		QDomNode	node	= attributes.item(x);

		if(!node.toAttr().name().compare("defaultCursorMoveStyle", Qt::CaseInsensitive))
			lpDocument->setDefaultCursorMoveStyle((Qt::CursorMoveStyle)node.toAttr().nodeValue().toInt());
		else if(!node.toAttr().name().compare("defaultStyleSheet", Qt::CaseInsensitive))
			lpDocument->setDefaultStyleSheet(node.toAttr().nodeValue());
		else
			myDebug << "parseDefaults: unknown attribute: " << node.toAttr().name();
	}

	QDomNode			child		= element.firstChild();

	while(!child.isNull())
	{
		if(!child.toElement().tagName().compare("defaultFont", Qt::CaseInsensitive))
			lpDocument->setDefaultFont(parseFont(child.toElement()));
		else if(!child.toElement().tagName().compare("defaultTextOption", Qt::CaseInsensitive))
			lpDocument->setDefaultTextOption(parseDefaultTextOption(child.toElement()));
		else
			myDebug << "parseDefaults: unknown element: " << child.toElement().tagName();

		child	= child.nextSibling();
	}
}

QFont cDocumentReader::parseFont(const QDomElement& element)
{
	QDomNamedNodeMap			attributes			= element.attributes();

	bool						bold;
	QFont::Capitalization		capitalization;
	QString						family;
	bool						fixedPitch;
	QFont::HintingPreference	hintingPreference;
	bool						italic;
	bool						kerning;
	qreal						letterSpacing;
	QFont::SpacingType			letterSpacingType;
	int							overline;
	int							pixelSize;
	int							pointSize;
	qreal						pointSizeF;
	int							stretch;
	bool						strikeOut;
	QFont::Style				style;
	QFont::StyleHint			styleHint;
	QString						styleName;
	QFont::StyleStrategy		styleStrategy;
	bool						underline;
	int							weight;
	qreal						wordSpacing;


	for(int x = 0;x < attributes.count();x++)
	{
		QDomNode	node	= attributes.item(x);

		if(!node.toAttr().name().compare("bold", Qt::CaseInsensitive))
			bold						= node.toAttr().nodeValue().compare("true", Qt::CaseInsensitive) == 0 ? true : false;
		else if(!node.toAttr().name().compare("capitalization", Qt::CaseInsensitive))
			capitalization				= (QFont::Capitalization)node.toAttr().nodeValue().toInt();
		else if(!node.toAttr().name().compare("family", Qt::CaseInsensitive))
			family						= node.toAttr().nodeValue();
		else if(!node.toAttr().name().compare("fixedPitch", Qt::CaseInsensitive))
			fixedPitch					= node.toAttr().nodeValue().compare("true", Qt::CaseInsensitive) == 0 ? true : false;
		else if(!node.toAttr().name().compare("hintingPreference", Qt::CaseInsensitive))
			hintingPreference			= (QFont::HintingPreference)node.toAttr().nodeValue().toInt();
		else if(!node.toAttr().name().compare("italic", Qt::CaseInsensitive))
			italic						= node.toAttr().nodeValue().compare("true", Qt::CaseInsensitive) == 0 ? true : false;
		else if(!node.toAttr().name().compare("kerning", Qt::CaseInsensitive))
			kerning						= node.toAttr().nodeValue().compare("true", Qt::CaseInsensitive) == 0 ? true : false;
		else if(!node.toAttr().name().compare("letterSpacing", Qt::CaseInsensitive))
			letterSpacing				= node.toAttr().nodeValue().toDouble();
		else if(!node.toAttr().name().compare("letterSpacingType", Qt::CaseInsensitive))
			letterSpacingType			= (QFont::SpacingType)node.toAttr().nodeValue().toInt();
		else if(!node.toAttr().name().compare("overline", Qt::CaseInsensitive))
			overline					= node.toAttr().nodeValue().toInt();
		else if(!node.toAttr().name().compare("pixelSize", Qt::CaseInsensitive))
			pixelSize					= node.toAttr().nodeValue().toInt();
		else if(!node.toAttr().name().compare("pointSize", Qt::CaseInsensitive))
			pointSize					= node.toAttr().nodeValue().toInt();
		else if(!node.toAttr().name().compare("pointSizeF", Qt::CaseInsensitive))
			pointSizeF					= node.toAttr().nodeValue().toDouble();
		else if(!node.toAttr().name().compare("stretch", Qt::CaseInsensitive))
			stretch						= node.toAttr().nodeValue().toInt();
		else if(!node.toAttr().name().compare("strikeOut", Qt::CaseInsensitive))
			strikeOut					= node.toAttr().nodeValue().compare("true", Qt::CaseInsensitive) == 0 ? true : false;
		else if(!node.toAttr().name().compare("style", Qt::CaseInsensitive))
			style						= (QFont::Style)node.toAttr().nodeValue().toInt();
		else if(!node.toAttr().name().compare("styleHint", Qt::CaseInsensitive))
			styleHint					= (QFont::StyleHint)node.toAttr().nodeValue().toInt();
		else if(!node.toAttr().name().compare("styleName", Qt::CaseInsensitive))
			styleName					= node.toAttr().nodeValue();
		else if(!node.toAttr().name().compare("styleStrategy", Qt::CaseInsensitive))
			styleStrategy				= (QFont::StyleStrategy)node.toAttr().nodeValue().toInt();
		else if(!node.toAttr().name().compare("underline", Qt::CaseInsensitive))
			underline					= node.toAttr().nodeValue().compare("true", Qt::CaseInsensitive) == 0 ? true : false;
		else if(!node.toAttr().name().compare("weight", Qt::CaseInsensitive))
			weight						= node.toAttr().nodeValue().toInt();
		else if(!node.toAttr().name().compare("wordSpacing", Qt::CaseInsensitive))
			wordSpacing					= node.toAttr().nodeValue().toDouble();
		else
			myDebug << "parseFont: unknown attribute: " << node.toAttr().name();
	}

	QFont	font(family);
	font.setBold(bold);
	font.setCapitalization(capitalization);
	font.setFixedPitch(fixedPitch);
	font.setHintingPreference(hintingPreference);
	font.setItalic(italic);
	font.setKerning(kerning);
	font.setLetterSpacing(letterSpacingType, letterSpacing);
	font.setOverline(overline);
	if(pointSizeF > 0)
		font.setPointSizeF(pointSizeF);
	else if(pointSize > 0)
		font.setPointSize(pointSize);
	else if(pixelSize > 0)
		font.setPixelSize(pixelSize);
	font.setStretch(stretch);
	font.setStretch(strikeOut);
	font.setStyle(style);
	font.setStyleHint(styleHint);
	font.setStyleName(styleName);
	font.setStyleStrategy(styleStrategy);
	font.setUnderline(underline);
	font.setWeight(weight);
	font.setWordSpacing(wordSpacing);

	return(font);
}

QTextOption cDocumentReader::parseDefaultTextOption(const QDomElement& element)
{
	QTextOption	textOption;

	QDomNamedNodeMap	attributes	= element.attributes();
	for(int x = 0;x < attributes.count();x++)
	{
		QDomNode	node	= attributes.item(x);

		if(!node.toAttr().name().compare("alignment", Qt::CaseInsensitive))
			textOption.setAlignment((Qt::AlignmentFlag)node.toAttr().nodeValue().toInt());
		else if(!node.toAttr().name().compare("flags", Qt::CaseInsensitive))
			textOption.setFlags((QTextOption::Flag)node.toAttr().nodeValue().toInt());
		else if(!node.toAttr().name().compare("tabStopDistance", Qt::CaseInsensitive))
			textOption.setTabStopDistance(node.toAttr().nodeValue().toDouble());
		else if(!node.toAttr().name().compare("textDirection", Qt::CaseInsensitive))
			textOption.setTextDirection((Qt::LayoutDirection)node.toAttr().nodeValue().toInt());
		else if(!node.toAttr().name().compare("useDesignMetrics", Qt::CaseInsensitive))
			textOption.setUseDesignMetrics(node.toAttr().nodeValue().compare("true", Qt::CaseInsensitive) == 0 ? true : false);
		else if(!node.toAttr().name().compare("wrapMode", Qt::CaseInsensitive))
			textOption.setWrapMode((QTextOption::WrapMode)node.toAttr().nodeValue().toInt());
		else
			myDebug << "parseDefaultTextOption: unknown attribute: " << node.toAttr().name();
	}

	QList<qreal>			tabArray;
	QList<QTextOption::Tab>	tabs;
	QDomNode				child		= element.firstChild();

	while(!child.isNull())
	{
		if(!child.toElement().tagName().compare("tabArray", Qt::CaseInsensitive))
		{
			QDomNode	tab			= child.toElement().firstChild();

			while(!tab.isNull())
			{
				if(!tab.toElement().tagName().compare("tab", Qt::CaseInsensitive))
					tabArray.append(tab.toElement().nodeValue().toDouble());

				tab	= tab.nextSibling();
			}
		}
		else if(!child.toElement().tagName().compare("tabs", Qt::CaseInsensitive))
			tabs	= parseTabPositions(child.toElement());
		else
			myDebug << "parseDefaultTextOption: unknown element: " << child.toElement().tagName();

		child	= child.nextSibling();
	}

	if(!tabArray.isEmpty())
		textOption.setTabArray(tabArray);
	if(!tabs.isEmpty())
		textOption.setTabs(tabs);

	return(textOption);
}

QList<QTextOption::Tab> cDocumentReader::parseTabPositions(const QDomElement& element)
{
	QList<QTextOption::Tab>	tabs;
	QDomNode				child		= element.firstChild();

	while(!child.isNull())
	{
		if(!child.toElement().tagName().compare("tabPosition", Qt::CaseInsensitive))
		{
			QTextOption::Tab	tab;
			QDomNamedNodeMap	attributes	= element.attributes();
			for(int x = 0;x < attributes.count();x++)
			{
				QDomNode	node	= attributes.item(x);

				if(!node.toAttr().name().compare("delimiter", Qt::CaseInsensitive))
					tab.delimiter	= node.toAttr().nodeValue().at(0);
				else if(!node.toAttr().name().compare("position", Qt::CaseInsensitive))
					tab.position	= node.toAttr().nodeValue().toDouble();
				else if(!node.toAttr().name().compare("type", Qt::CaseInsensitive))
					tab.type		= (QTextOption::TabType)node.toAttr().nodeValue().toInt();
			}
			tabs.append(tab);
		}
		else
			myDebug << "parseTabPositions: unknown element: " << child.toElement().tagName();

		child	= child.nextSibling();
	}

	return(tabs);
}

QVector<cTextFormat> cDocumentReader::parseAllFormats(const QDomElement& element)
{
	QVector<cTextFormat>	allFormats;
	QDomNode				child		= element.firstChild();

	while(!child.isNull())
	{
		if(!child.toElement().tagName().compare("format", Qt::CaseInsensitive))
		{
			cTextFormat	format	= parseFormat(child.toElement());
			if(format.isValid())
				allFormats.append(format);
		}
		else
			myDebug << "parseAllFormats: unknown element: " << child.toElement().tagName();

		child	= child.nextSibling();
	}

	return(allFormats);
}

cTextFormat cDocumentReader::parseFormat(const QDomElement& element)
{
	QString					typeText;
	Qt::LayoutDirection		layoutDirection;
	//UNUSED
	int						id;
	int						type;

	QDomNamedNodeMap		attributes	= element.attributes();
	for(int x = 0;x < attributes.count();x++)
	{
		QDomNode	node	= attributes.item(x);

		if(!node.toAttr().name().compare("id", Qt::CaseInsensitive))
			id						= node.toAttr().nodeValue().toInt();
		else if(!node.toAttr().name().compare("type", Qt::CaseInsensitive))
			type					= node.toAttr().nodeValue().toInt();
		else if(!node.toAttr().name().compare("typeText", Qt::CaseInsensitive))
			typeText				= node.toAttr().nodeValue();
		else if(!node.toAttr().name().compare("layoutDirection", Qt::CaseInsensitive))
			layoutDirection			= (Qt::LayoutDirection)node.toAttr().nodeValue().toInt();
		//else
		//	myDebug << "parseFormat: unknown attribute: " << node.toAttr().name();
	}

	//UNUSED
	id			= id;
	type		= type;

	cTextFormat				format(typeText);

	if(!typeText.compare("tableCellFormat", Qt::CaseInsensitive))
		format.tableCellFormat	= parseTextTableCellFormat(element);
	else if(!typeText.compare("tableFormat", Qt::CaseInsensitive))
		format.tableFormat		= parseTextTableFormat(element);
	else if(!typeText.compare("imageFormat", Qt::CaseInsensitive))
		format.imageFormat		= parseTextImageFormat(element);
	else if(!typeText.compare("frameFormat", Qt::CaseInsensitive))
		format.frameFormat		= parseTextFrameFormat(element);
	else if(!typeText.compare("listFormat", Qt::CaseInsensitive))
		format.listFormat		= parseTextListFormat(element);
	else if(!typeText.compare("blockFormat", Qt::CaseInsensitive))
		format.blockFormat		= parseTextBlockFormat(element);
	else if(!typeText.compare("charFormat", Qt::CaseInsensitive))
		format.charFormat		= parseTextCharFormat(element);
	format.setLayoutDirection(layoutDirection);

	return(format);
}

QPen cDocumentReader::parsePen(const QDomElement& element)
{
	QDomNamedNodeMap		attributes	= element.attributes();
	Qt::PenCapStyle			capStyle;
	qreal					dashOffset;
	bool					isCosmetic;
	Qt::PenJoinStyle		joinStyle;
	qreal					miterLimit;
	Qt::PenStyle			style;
	int						width;
	qreal					widthF;
	QBrush					brush;
	QColor					color;
	QVector<qreal>			dashPattern;

	for(int x = 0;x < attributes.count();x++)
	{
		QDomNode	node	= attributes.item(x);

		if(!node.toAttr().name().compare("capStyle", Qt::CaseInsensitive))
			capStyle	= (Qt::PenCapStyle)node.toAttr().nodeValue().toInt();
		else if(!node.toAttr().name().compare("dashOffset", Qt::CaseInsensitive))
			dashOffset	= node.toAttr().nodeValue().toDouble();
		else if(!node.toAttr().name().compare("isCosmetic", Qt::CaseInsensitive))
			isCosmetic	= node.toAttr().nodeValue().compare("true", Qt::CaseInsensitive) == 0 ? true : false;
		else if(!node.toAttr().name().compare("joinStyle", Qt::CaseInsensitive))
			joinStyle	= (Qt::PenJoinStyle)node.toAttr().nodeValue().toInt();
		else if(!node.toAttr().name().compare("miterLimit", Qt::CaseInsensitive))
			miterLimit	= node.toAttr().nodeValue().toDouble();
		else if(!node.toAttr().name().compare("style", Qt::CaseInsensitive))
			style		= (Qt::PenStyle)node.toAttr().nodeValue().toInt();
		else if(!node.toAttr().name().compare("width", Qt::CaseInsensitive))
			width		= node.toAttr().nodeValue().toInt();
		else if(!node.toAttr().name().compare("widthF", Qt::CaseInsensitive))
			widthF		= node.toAttr().nodeValue().toDouble();
		else
			myDebug << "parsePen: unknown attribute: " << node.toAttr().name();
	}

	QDomNode				child		= element.firstChild();

	while(!child.isNull())
	{
		if(!child.toElement().tagName().compare("brush", Qt::CaseInsensitive))
			brush	= parseBrush(child.toElement());
		else if(!child.toElement().tagName().compare("color", Qt::CaseInsensitive))
			color	= parseColor(child.toElement());
		else if(!child.toElement().tagName().compare("dashPattern", Qt::CaseInsensitive))
		{
			QDomNode		pattern	= child.toElement().firstChild();

			while(!pattern.isNull())
			{
				if(!pattern.toElement().tagName().compare("pattern", Qt::CaseInsensitive))
					dashPattern.append(pattern.toElement().nodeValue().toDouble());
				else
					qDebug() << " parsePen: unknown element: " << pattern.toElement().tagName();

				pattern	= pattern.nextSibling();
			}
		}
		else
			myDebug << " parsePen: unknown element: " << child.toElement().tagName();

		child	= child.nextSibling();
	}

	QPen	pen(color);

	pen.setBrush(brush);
	if(widthF > 0)
		pen.setWidthF(widthF);
	else
		pen.setWidth(width);
	pen.setCapStyle(capStyle);
	pen.setDashOffset(dashOffset);
	pen.setCosmetic(isCosmetic);
	pen.setJoinStyle(joinStyle);
	pen.setMiterLimit(miterLimit);
	pen.setStyle(style);
	if(dashPattern.count())
		pen.setDashPattern(dashPattern);

	return(pen);
}

QBrush cDocumentReader::parseBrush(const QDomElement& element)
{
	QDomNamedNodeMap		attributes	= element.attributes();
	Qt::BrushStyle			style;

	for(int x = 0;x < attributes.count();x++)
	{
		QDomNode	node	= attributes.item(x);

		if(!node.toAttr().name().compare("style", Qt::CaseInsensitive))
			style	= (Qt::BrushStyle)node.toAttr().nodeValue().toInt();
		else
			myDebug << " parseBrush: unknown attribute: " << node.toAttr().name();
	}

	QDomNode				child		= element.firstChild();
	QColor					color;

	while(!child.isNull())
	{
		if(!child.toElement().tagName().compare("color", Qt::CaseInsensitive))
			color	= parseColor(child.toElement());
		else
			myDebug << " parseBrush: unknown element: " << child.toElement().tagName();

		child	= child.nextSibling();
	}

	return(QBrush(color, style));
}

QColor cDocumentReader::parseColor(const QDomElement& element)
{
	QDomNamedNodeMap		attributes	= element.attributes();
	int						alpha;
	int						r;
	int						g;
	int						b;

	for(int x = 0;x < attributes.count();x++)
	{
		QDomNode	node	= attributes.item(x);

		if(!node.toAttr().name().compare("alpha", Qt::CaseInsensitive))
			alpha	= node.toAttr().nodeValue().toInt();
		else if(!node.toAttr().name().compare("r", Qt::CaseInsensitive))
			r		= node.toAttr().nodeValue().toInt();
		else if(!node.toAttr().name().compare("g", Qt::CaseInsensitive))
			g		= node.toAttr().nodeValue().toInt();
		else if(!node.toAttr().name().compare("b", Qt::CaseInsensitive))
			b		= node.toAttr().nodeValue().toInt();
		else
			myDebug << " parseColor: unknown attribute: " << node.toAttr().name();
	}

	return(QColor(r, g, b, alpha));
}

QTextTableCellFormat cDocumentReader::parseTextTableCellFormat(const QDomElement& element)
{
	int									leftPadding;
	int									topPadding;
	int									rightPadding;
	int									bottomPadding;
	Qt::LayoutDirection					layoutDirection;

	QString								anchorHref;
	bool								isAnchor;
	QString								toolTip;
	QTextImageFormat::VerticalAlignment	verticalAlignment;

	QBrush								background;
	QBrush								foreground;
	QPen								textOutline;
	QStringList							anchorNames;
	QMap<int, QVariant>					properties;
	QFont								font;
	QColor								underlineColor;

	//UNUSED
	int									id;
	int									type;
	QString								typeText;

	QDomNamedNodeMap		attributes	= element.attributes();
	for(int x = 0;x < attributes.count();x++)
	{
		QDomNode	node	= attributes.item(x);

		if(!node.toAttr().name().compare("id", Qt::CaseInsensitive))
			id						= node.toAttr().nodeValue().toInt();
		else if(!node.toAttr().name().compare("type", Qt::CaseInsensitive))
			type					= node.toAttr().nodeValue().toInt();
		else if(!node.toAttr().name().compare("typeText", Qt::CaseInsensitive))
			typeText				= node.toAttr().nodeValue();
		else if(!node.toAttr().name().compare("anchorHref", Qt::CaseInsensitive))
			anchorHref				= node.toAttr().nodeValue();
		else if(!node.toAttr().name().compare("isAnchor", Qt::CaseInsensitive))
			isAnchor				= node.toAttr().nodeValue().compare("true", Qt::CaseInsensitive) == 0 ? true : false;
		else if(!node.toAttr().name().compare("toolTip", Qt::CaseInsensitive))
			toolTip					= node.toAttr().nodeValue();
		else if(!node.toAttr().name().compare("verticalAlignment", Qt::CaseInsensitive))
			verticalAlignment		= (QTextImageFormat::VerticalAlignment)node.toAttr().nodeValue().toInt();
		else if(!node.toAttr().name().compare("leftPadding", Qt::CaseInsensitive))
			leftPadding		= node.toAttr().nodeValue().toInt();
		else if(!node.toAttr().name().compare("topPadding", Qt::CaseInsensitive))
			topPadding		= node.toAttr().nodeValue().toInt();
		else if(!node.toAttr().name().compare("rightPadding", Qt::CaseInsensitive))
			rightPadding	= node.toAttr().nodeValue().toInt();
		else if(!node.toAttr().name().compare("bottomPadding", Qt::CaseInsensitive))
			bottomPadding	= node.toAttr().nodeValue().toInt();
		else if(!node.toAttr().name().compare("layoutDirection", Qt::CaseInsensitive))
			layoutDirection	= (Qt::LayoutDirection)node.toAttr().nodeValue().toInt();
		else
			myDebug << " parseTextTableCellFormat: unknown attribute: " << node.toAttr().name();
	}

	//UNUSED
	id			= id;
	type		= type;
	typeText	= typeText;

	QDomNode				child		= element.firstChild();

	while(!child.isNull())
	{
		if(!child.toElement().tagName().compare("background", Qt::CaseInsensitive))
			background	= parseBrush(child.toElement());
		else if(!child.toElement().tagName().compare("foreground", Qt::CaseInsensitive))
			foreground	= parseBrush(child.toElement());
		else if(!child.toElement().tagName().compare("properties", Qt::CaseInsensitive))
		{
			int				key;
			QVariant::Type	type;
			QString			value;

			QDomNode		property	= child.toElement().firstChild();

			while(!property.isNull())
			{
				if(!property.toElement().tagName().compare("key", Qt::CaseInsensitive))
					key		= property.toElement().toElement().nodeValue().toInt();
				else if(!property.toElement().tagName().compare("type", Qt::CaseInsensitive))
					type	= (QVariant::Type)property.toElement().nodeValue().toInt();
				else if(!property.toElement().tagName().compare("value", Qt::CaseInsensitive))
					value	= property.toElement().nodeValue();

				QVariant	propertyValue(value);
				propertyValue.convert(type);
				properties.insert(key, propertyValue);

				property	= property.nextSibling();
			}
		}
		else if(!child.toElement().tagName().compare("textOutline", Qt::CaseInsensitive))
			textOutline	= parsePen(child.toElement());
		else if(!child.toElement().tagName().compare("anchorNames", Qt::CaseInsensitive))
		{

			QDomNode		anchors		= child.toElement().firstChild();

			while(!anchors.isNull())
			{
				if(!child.toElement().tagName().compare("anchor", Qt::CaseInsensitive))
					anchorNames.append(child.toElement().nodeValue());

				anchors	= anchors.nextSibling();
			}
		}
		else if(!child.toElement().tagName().compare("font", Qt::CaseInsensitive))
			font			= parseFont(child.toElement());
		else if(!child.toElement().tagName().compare("underlineColor", Qt::CaseInsensitive))
			underlineColor	= parseColor(child.toElement());
		else
			myDebug << " parseTextTableCellFormat: unknown element: " << child.toElement().tagName();

		child	= child.nextSibling();
	}

	QTextTableCellFormat	format;

	format.setAnchorHref(anchorHref);
	format.setAnchor(isAnchor);
	format.setToolTip(toolTip);
	format.setVerticalAlignment(verticalAlignment);
	format.setLeftPadding(leftPadding);
	format.setTopPadding(topPadding);
	format.setRightPadding(rightPadding);
	format.setBottomPadding(bottomPadding);
	format.setLayoutDirection(layoutDirection);
	format.setBackground(background);
	format.setForeground(foreground);
	format.setTextOutline(textOutline);
	format.setAnchorNames(anchorNames);

	QMapIterator<int, QVariant> property(properties);
	while(property.hasNext())
	{
		property.next();
		format.setProperty(property.key(), property.value());
	}

	format.setFont(font);
	format.setUnderlineColor(underlineColor);

	return(format);
}

QTextTableFormat cDocumentReader::parseTextTableFormat(const QDomElement& element)
{
	Qt::AlignmentFlag					alignment;
	int									cellPadding;
	int									cellSpacing;
	int									columns;
	int									headerRowCount;
	qreal								border;
	QTextTableFormat::BorderStyle		borderStyle;
	qreal								margin;
	qreal								leftMargin;
	qreal								topMargin;
	qreal								rightMargin;
	qreal								bottomMargin;
	qreal								width;
	qreal								height;
	qreal								padding;
	QTextTableFormat::PageBreakFlags	pageBreakPolicy;
	QTextTableFormat::Position			position;
	Qt::LayoutDirection					layoutDirection;
	QVector<QTextLength>				columnWidthContraints;
	QBrush								borderBrush;
	QBrush								background;
	QBrush								foreground;
	QMap<int, QVariant>					properties;

	//UNUSED
	int									id;
	int									type;
	QString								typeText;

	QDomNamedNodeMap		attributes	= element.attributes();
	for(int x = 0;x < attributes.count();x++)
	{
		QDomNode	node	= attributes.item(x);

		if(!node.toAttr().name().compare("id", Qt::CaseInsensitive))
			id						= node.toAttr().nodeValue().toInt();
		else if(!node.toAttr().name().compare("type", Qt::CaseInsensitive))
			type					= node.toAttr().nodeValue().toInt();
		else if(!node.toAttr().name().compare("typeText", Qt::CaseInsensitive))
			typeText				= node.toAttr().nodeValue();
		else if(!node.toAttr().name().compare("alignment", Qt::CaseInsensitive))
			alignment		= (Qt::AlignmentFlag)node.toAttr().nodeValue().toInt();
		else if(!node.toAttr().name().compare("cellPadding", Qt::CaseInsensitive))
			cellPadding		= node.toAttr().nodeValue().toInt();
		else if(!node.toAttr().name().compare("cellSpacing", Qt::CaseInsensitive))
			cellSpacing		= node.toAttr().nodeValue().toInt();
		else if(!node.toAttr().name().compare("columns", Qt::CaseInsensitive))
			columns			= node.toAttr().nodeValue().toInt();
		else if(!node.toAttr().name().compare("headerRowCount", Qt::CaseInsensitive))
			headerRowCount	= node.toAttr().nodeValue().toInt();
		else if(!node.toAttr().name().compare("border", Qt::CaseInsensitive))
			border			= node.toAttr().nodeValue().toDouble();
		else if(!node.toAttr().name().compare("borderStyle", Qt::CaseInsensitive))
			borderStyle		= (QTextTableFormat::BorderStyle)node.toAttr().nodeValue().toInt();
		else if(!node.toAttr().name().compare("margin", Qt::CaseInsensitive))
			margin			= node.toAttr().nodeValue().toDouble();
		else if(!node.toAttr().name().compare("leftMargin", Qt::CaseInsensitive))
			leftMargin		= node.toAttr().nodeValue().toDouble();
		else if(!node.toAttr().name().compare("topMargin", Qt::CaseInsensitive))
			topMargin		= node.toAttr().nodeValue().toDouble();
		else if(!node.toAttr().name().compare("rightMargin", Qt::CaseInsensitive))
			rightMargin		= node.toAttr().nodeValue().toDouble();
		else if(!node.toAttr().name().compare("bottomMargin", Qt::CaseInsensitive))
			bottomMargin	= node.toAttr().nodeValue().toDouble();
		else if(!node.toAttr().name().compare("width", Qt::CaseInsensitive))
			width			= node.toAttr().nodeValue().toDouble();
		else if(!node.toAttr().name().compare("height", Qt::CaseInsensitive))
			height			= node.toAttr().nodeValue().toDouble();
		else if(!node.toAttr().name().compare("padding", Qt::CaseInsensitive))
			padding			= node.toAttr().nodeValue().toDouble();
		else if(!node.toAttr().name().compare("pageBreakPolicy", Qt::CaseInsensitive))
			pageBreakPolicy	= (QTextTableFormat::PageBreakFlags)node.toAttr().nodeValue().toInt();
		else if(!node.toAttr().name().compare("position", Qt::CaseInsensitive))
			position		= (QTextTableFormat::Position)node.toAttr().nodeValue().toInt();
		else if(!node.toAttr().name().compare("layoutDirection", Qt::CaseInsensitive))
			layoutDirection	= (Qt::LayoutDirection)node.toAttr().nodeValue().toInt();
		else
			myDebug << " parseTextTableFormat: unknown attribute: " << node.toAttr().name();
	}

	//UNUSED
	id			= id;
	type		= type;
	typeText	= typeText;

	QDomNode				child		= element.firstChild();

	while(!child.isNull())
	{
		if(!child.toElement().tagName().compare("columnWidthConstraints", Qt::CaseInsensitive))
		{
			QDomNode		constraints	= child.toElement().firstChild();
			while(!constraints.isNull())
			{
				if(!constraints.toElement().tagName().compare("columnWidthConstraint", Qt::CaseInsensitive))
				{
					qreal				rawValue;
					QTextLength::Type	type;
					QDomNamedNodeMap	constraint	= constraints.attributes();

					for(int x = 0;x < constraint.count();x++)
					{
						QDomNode	node	= constraint.item(x);

						if(!node.toAttr().name().compare("rawValue", Qt::CaseInsensitive))
							rawValue	= node.toAttr().nodeValue().toDouble();
						else if(!node.toAttr().name().compare("type", Qt::CaseInsensitive))
							type		= (QTextLength::Type)node.toAttr().nodeValue().toInt();
					}

					columnWidthContraints.append(QTextLength(type, rawValue));
				}
				else
					myDebug << " parseTextTableFormat: unknown element: " << child.toElement().tagName();

				constraints	= constraints.nextSibling();
			}
		}
		else if(!child.toElement().tagName().compare("borderBrush", Qt::CaseInsensitive))
			borderBrush	= parseBrush(child.toElement());
		else if(!child.toElement().tagName().compare("background", Qt::CaseInsensitive))
			background	= parseBrush(child.toElement());
		else if(!child.toElement().tagName().compare("foreground", Qt::CaseInsensitive))
			foreground	= parseBrush(child.toElement());
		else if(!child.toElement().tagName().compare("properties", Qt::CaseInsensitive))
		{
			int				key;
			QVariant::Type	type;
			QString			value;

			QDomNode		property	= child.toElement().firstChild();

			while(!property.isNull())
			{
				if(!property.toElement().tagName().compare("key", Qt::CaseInsensitive))
					key		= property.toElement().toElement().nodeValue().toInt();
				else if(!property.toElement().tagName().compare("type", Qt::CaseInsensitive))
					type	= (QVariant::Type)property.toElement().nodeValue().toInt();
				else if(!property.toElement().tagName().compare("value", Qt::CaseInsensitive))
					value	= property.toElement().nodeValue();

				QVariant	propertyValue(value);
				propertyValue.convert(type);
				properties.insert(key, propertyValue);

				property	= property.nextSibling();
			}
		}
		else
			myDebug << " parseTextTableFormat: unknown element: " << child.toElement().tagName();

		child	= child.nextSibling();
	}

	QTextTableFormat	format;

	format.setAlignment(alignment);
	format.setCellPadding(cellPadding);
	format.setCellSpacing(cellSpacing);
	format.setColumns(columns);
	format.setHeaderRowCount(headerRowCount);
	format.setBorder(border);
	format.setBorderStyle(borderStyle);
	format.setMargin(margin);
	format.setLeftMargin(leftMargin);
	format.setTopMargin(topMargin);
	format.setRightMargin(rightMargin);
	format.setBottomMargin(bottomMargin);
	format.setWidth(width);
	format.setHeight(height);
	format.setPadding(padding);
	format.setPageBreakPolicy(pageBreakPolicy);
	format.setPosition(position);
	format.setLayoutDirection(layoutDirection);
	format.setColumnWidthConstraints(columnWidthContraints);
	format.setBorderBrush(borderBrush);
	format.setBackground(background);
	format.setForeground(foreground);

	QMapIterator<int, QVariant> property(properties);
	while(property.hasNext())
	{
		property.next();
		format.setProperty(property.key(), property.value());
	}

	return(format);
}

QTextImageFormat cDocumentReader::parseTextImageFormat(const QDomElement& element)
{
	QString								name;
	qreal								height;
	qreal								width;
	QString								anchorHref;
	bool								isAnchor;
	QString								toolTip;
	QTextImageFormat::VerticalAlignment	verticalAlignment;
	QBrush								background;
	QBrush								foreground;
	QPen								textOutline;
	QStringList							anchorNames;
	QMap<int, QVariant>					properties;
	QFont								font;
	QColor								underlineColor;
	Qt::LayoutDirection					layoutDirection;

	//UNUSED
	int									id;
	int									type;
	QString								typeText;

	QDomNamedNodeMap		attributes	= element.attributes();
	for(int x = 0;x < attributes.count();x++)
	{
		QDomNode	node	= attributes.item(x);

		if(!node.toAttr().name().compare("id", Qt::CaseInsensitive))
			id						= node.toAttr().nodeValue().toInt();
		else if(!node.toAttr().name().compare("type", Qt::CaseInsensitive))
			type					= node.toAttr().nodeValue().toInt();
		else if(!node.toAttr().name().compare("typeText", Qt::CaseInsensitive))
			typeText				= node.toAttr().nodeValue();
		else if(!node.toAttr().name().compare("anchorHref", Qt::CaseInsensitive))
			anchorHref				= node.toAttr().nodeValue();
		else if(!node.toAttr().name().compare("height", Qt::CaseInsensitive))
			height					= node.toAttr().nodeValue().toDouble();
		else if(!node.toAttr().name().compare("width", Qt::CaseInsensitive))
			width					= node.toAttr().nodeValue().toDouble();
		else if(!node.toAttr().name().compare("name", Qt::CaseInsensitive))
			name					= node.toAttr().nodeValue();
		else if(!node.toAttr().name().compare("isAnchor", Qt::CaseInsensitive))
			isAnchor				= node.toAttr().nodeValue().compare("true", Qt::CaseInsensitive) == 0 ? true : false;
		else if(!node.toAttr().name().compare("toolTip", Qt::CaseInsensitive))
			toolTip					= node.toAttr().nodeValue();
		else if(!node.toAttr().name().compare("verticalAlignment", Qt::CaseInsensitive))
			verticalAlignment		= (QTextImageFormat::VerticalAlignment)node.toAttr().nodeValue().toInt();
		else if(!node.toAttr().name().compare("layoutDirection", Qt::CaseInsensitive))
			layoutDirection			= (Qt::LayoutDirection)node.toAttr().nodeValue().toInt();
		else
			myDebug << " parseTextImageFormat: unknown attribute: " << node.toAttr().name();
	}

	//UNUSED
	id			= id;
	type		= type;
	typeText	= typeText;

	QDomNode				child		= element.firstChild();

	while(!child.isNull())
	{
		if(!child.toElement().tagName().compare("background", Qt::CaseInsensitive))
			background	= parseBrush(child.toElement());
		else if(!child.toElement().tagName().compare("foreground", Qt::CaseInsensitive))
			foreground	= parseBrush(child.toElement());
		else if(!child.toElement().tagName().compare("properties", Qt::CaseInsensitive))
		{
			int				key;
			QVariant::Type	type;
			QString			value;

			QDomNode		property	= child.toElement().firstChild();

			while(!property.isNull())
			{
				if(!property.toElement().tagName().compare("key", Qt::CaseInsensitive))
					key		= property.toElement().toElement().nodeValue().toInt();
				else if(!property.toElement().tagName().compare("type", Qt::CaseInsensitive))
					type	= (QVariant::Type)property.toElement().nodeValue().toInt();
				else if(!property.toElement().tagName().compare("value", Qt::CaseInsensitive))
					value	= property.toElement().nodeValue();

				QVariant	propertyValue(value);
				propertyValue.convert(type);
				properties.insert(key, propertyValue);

				property	= property.nextSibling();
			}
		}
		else if(!child.toElement().tagName().compare("textOutline", Qt::CaseInsensitive))
			textOutline	= parsePen(child.toElement());
		else if(!child.toElement().tagName().compare("anchorNames", Qt::CaseInsensitive))
		{

			QDomNode		anchors		= child.toElement().firstChild();

			while(!anchors.isNull())
			{
				if(!child.toElement().tagName().compare("anchor", Qt::CaseInsensitive))
					anchorNames.append(child.toElement().nodeValue());

				anchors	= anchors.nextSibling();
			}
		}
		else if(!child.toElement().tagName().compare("font", Qt::CaseInsensitive))
			font			= parseFont(child.toElement());
		else if(!child.toElement().tagName().compare("underlineColor", Qt::CaseInsensitive))
			underlineColor	= parseColor(child.toElement());
		else
			myDebug << " parseTextTableCellFormat: unknown element: " << child.toElement().tagName();
		child	= child.nextSibling();
	}

	QTextImageFormat	format;

	format.setName(name);
	format.setHeight(height);
	format.setWidth(width);
	format.setAnchorHref(anchorHref);
	format.setFont(font);
	format.setAnchor(isAnchor);
	format.setToolTip(toolTip);
	format.setVerticalAlignment(verticalAlignment);
	format.setBackground(background);
	format.setForeground(foreground);
	format.setTextOutline(textOutline);
	format.setAnchorNames(anchorNames);
	format.setLayoutDirection(layoutDirection);

	QMapIterator<int, QVariant> property(properties);
	while(property.hasNext())
	{
		property.next();
		format.setProperty(property.key(), property.value());
	}

	format.setUnderlineColor(underlineColor);

	return(format);
}

QTextFrameFormat cDocumentReader::parseTextFrameFormat(const QDomElement& element)
{
	qreal								border;
	QTextTableFormat::BorderStyle		borderStyle;
	qreal								margin;
	qreal								leftMargin;
	qreal								topMargin;
	qreal								rightMargin;
	qreal								bottomMargin;
	qreal								width;
	qreal								height;
	qreal								padding;
	QTextTableFormat::PageBreakFlags	pageBreakPolicy;
	QTextTableFormat::Position			position;
	QBrush								background;
	QBrush								foreground;
	QBrush								borderBrush;
	QMap<int, QVariant>					properties;
	Qt::LayoutDirection					layoutDirection;

	//UNUSED
	int									id;
	int									type;
	QString								typeText;

	QDomNamedNodeMap		attributes	= element.attributes();
	for(int x = 0;x < attributes.count();x++)
	{
		QDomNode	node	= attributes.item(x);

		if(!node.toAttr().name().compare("id", Qt::CaseInsensitive))
			id						= node.toAttr().nodeValue().toInt();
		else if(!node.toAttr().name().compare("type", Qt::CaseInsensitive))
			type					= node.toAttr().nodeValue().toInt();
		else if(!node.toAttr().name().compare("typeText", Qt::CaseInsensitive))
			typeText				= node.toAttr().nodeValue();
		else if(!node.toAttr().name().compare("border", Qt::CaseInsensitive))
			border			= node.toAttr().nodeValue().toDouble();
		else if(!node.toAttr().name().compare("borderStyle", Qt::CaseInsensitive))
			borderStyle		= (QTextTableFormat::BorderStyle)node.toAttr().nodeValue().toInt();
		else if(!node.toAttr().name().compare("margin", Qt::CaseInsensitive))
			margin			= node.toAttr().nodeValue().toDouble();
		else if(!node.toAttr().name().compare("leftMargin", Qt::CaseInsensitive))
			leftMargin		= node.toAttr().nodeValue().toDouble();
		else if(!node.toAttr().name().compare("topMargin", Qt::CaseInsensitive))
			topMargin		= node.toAttr().nodeValue().toDouble();
		else if(!node.toAttr().name().compare("rightMargin", Qt::CaseInsensitive))
			rightMargin		= node.toAttr().nodeValue().toDouble();
		else if(!node.toAttr().name().compare("bottomMargin", Qt::CaseInsensitive))
			bottomMargin	= node.toAttr().nodeValue().toDouble();
		else if(!node.toAttr().name().compare("width", Qt::CaseInsensitive))
			width			= node.toAttr().nodeValue().toDouble();
		else if(!node.toAttr().name().compare("height", Qt::CaseInsensitive))
			height			= node.toAttr().nodeValue().toDouble();
		else if(!node.toAttr().name().compare("padding", Qt::CaseInsensitive))
			padding			= node.toAttr().nodeValue().toDouble();
		else if(!node.toAttr().name().compare("pageBreakPolicy", Qt::CaseInsensitive))
			pageBreakPolicy	= (QTextTableFormat::PageBreakFlags)node.toAttr().nodeValue().toInt();
		else if(!node.toAttr().name().compare("position", Qt::CaseInsensitive))
			position		= (QTextTableFormat::Position)node.toAttr().nodeValue().toInt();
		else if(!node.toAttr().name().compare("layoutDirection", Qt::CaseInsensitive))
			layoutDirection	= (Qt::LayoutDirection)node.toAttr().nodeValue().toInt();
		else
			myDebug << " parseTextTableFormat: unknown attribute: " << node.toAttr().name();
	}

	//UNUSED
	id			= id;
	type		= type;
	typeText	= typeText;

	QDomNode				child		= element.firstChild();

	while(!child.isNull())
	{
		if(!child.toElement().tagName().compare("background", Qt::CaseInsensitive))
			background	= parseBrush(child.toElement());
		else if(!child.toElement().tagName().compare("foreground", Qt::CaseInsensitive))
			foreground	= parseBrush(child.toElement());
		else if(!child.toElement().tagName().compare("borderBrush", Qt::CaseInsensitive))
			borderBrush	= parseBrush(child.toElement());
		else if(!child.toElement().tagName().compare("properties", Qt::CaseInsensitive))
		{
			int				key;
			QVariant::Type	type;
			QString			value;

			QDomNode		property	= child.toElement().firstChild();

			while(!property.isNull())
			{
				if(!property.toElement().tagName().compare("key", Qt::CaseInsensitive))
					key		= property.toElement().toElement().nodeValue().toInt();
				else if(!property.toElement().tagName().compare("type", Qt::CaseInsensitive))
					type	= (QVariant::Type)property.toElement().nodeValue().toInt();
				else if(!property.toElement().tagName().compare("value", Qt::CaseInsensitive))
					value	= property.toElement().nodeValue();

				QVariant	propertyValue(value);
				propertyValue.convert(type);
				properties.insert(key, propertyValue);

				property	= property.nextSibling();
			}
		}
		else
			myDebug << " parseTextFrameFormat: unknown element: " << child.toElement().tagName();

		child	= child.nextSibling();
	}

	QTextFrameFormat	format;

	format.setBorder(border);
	format.setBorderStyle(borderStyle);
	format.setMargin(margin);
	format.setLeftMargin(leftMargin);
	format.setTopMargin(topMargin);
	format.setRightMargin(rightMargin);
	format.setBottomMargin(bottomMargin);
	format.setWidth(width);
	format.setHeight(height);
	format.setPadding(padding);
	format.setPageBreakPolicy(pageBreakPolicy);
	format.setPosition(position);
	format.setLayoutDirection(layoutDirection);
	format.setBackground(background);
	format.setForeground(foreground);
	format.setBorderBrush(borderBrush);

	QMapIterator<int, QVariant> property(properties);
	while(property.hasNext())
	{
		property.next();
		format.setProperty(property.key(), property.value());
	}

	return(format);
}

QTextListFormat cDocumentReader::parseTextListFormat(const QDomElement& element)
{
	int									indent;
	QString								numberPrefix;
	QString								numberSuffix;
	QTextListFormat::Style				style;
	Qt::LayoutDirection					layoutDirection;
	QBrush								background;
	QBrush								foreground;
	QMap<int, QVariant>					properties;

	//UNUSED
	int									id;
	int									type;
	QString								typeText;

	QDomNamedNodeMap		attributes	= element.attributes();
	for(int x = 0;x < attributes.count();x++)
	{
		QDomNode	node	= attributes.item(x);

		if(!node.toAttr().name().compare("id", Qt::CaseInsensitive))
			id						= node.toAttr().nodeValue().toInt();
		else if(!node.toAttr().name().compare("type", Qt::CaseInsensitive))
			type					= node.toAttr().nodeValue().toInt();
		else if(!node.toAttr().name().compare("typeText", Qt::CaseInsensitive))
			typeText				= node.toAttr().nodeValue();
		else if(!node.toAttr().name().compare("indent", Qt::CaseInsensitive))
			indent			= node.toAttr().nodeValue().toDouble();
		else if(!node.toAttr().name().compare("numberPrefix", Qt::CaseInsensitive))
			numberPrefix	= node.toAttr().nodeValue();
		else if(!node.toAttr().name().compare("numberSuffix", Qt::CaseInsensitive))
			numberSuffix	= node.toAttr().nodeValue();
		else if(!node.toAttr().name().compare("style", Qt::CaseInsensitive))
			style			= (QTextListFormat::Style)node.toAttr().nodeValue().toInt();
		else if(!node.toAttr().name().compare("layoutDirection", Qt::CaseInsensitive))
			layoutDirection		= (Qt::LayoutDirection)node.toAttr().nodeValue().toInt();
		else
			myDebug << " parseTextListFormat: unknown attribute: " << node.toAttr().name();
	}

	//UNUSED
	id			= id;
	type		= type;
	typeText	= typeText;

	QDomNode				child		= element.firstChild();

	while(!child.isNull())
	{
		if(!child.toElement().tagName().compare("background", Qt::CaseInsensitive))
			background	= parseBrush(child.toElement());
		else if(!child.toElement().tagName().compare("foreground", Qt::CaseInsensitive))
			foreground	= parseBrush(child.toElement());
		else if(!child.toElement().tagName().compare("properties", Qt::CaseInsensitive))
		{
			int				key;
			QVariant::Type	type;
			QString			value;

			QDomNode		property	= child.toElement().firstChild();

			while(!property.isNull())
			{
				if(!property.toElement().tagName().compare("key", Qt::CaseInsensitive))
					key		= property.toElement().toElement().nodeValue().toInt();
				else if(!property.toElement().tagName().compare("type", Qt::CaseInsensitive))
					type	= (QVariant::Type)property.toElement().nodeValue().toInt();
				else if(!property.toElement().tagName().compare("value", Qt::CaseInsensitive))
					value	= property.toElement().nodeValue();

				QVariant	propertyValue(value);
				propertyValue.convert(type);
				properties.insert(key, propertyValue);

				property	= property.nextSibling();
			}
		}
		else
			myDebug << " parseTextListFormat: unknown element: " << child.toElement().tagName();

		child	= child.nextSibling();
	}

	QTextListFormat	format;

	format.setIndent(indent);
	format.setNumberPrefix(numberPrefix);
	format.setNumberSuffix(numberSuffix);
	format.setStyle(style);
	format.setLayoutDirection(layoutDirection);
	format.setBackground(background);
	format.setForeground(foreground);

	QMapIterator<int, QVariant> property(properties);
	while(property.hasNext())
	{
		property.next();
		format.setProperty(property.key(), property.value());
	}

	return(format);
}

QTextBlockFormat cDocumentReader::parseTextBlockFormat(const QDomElement& element)
{
	Qt::AlignmentFlag					alignment;
	qreal								leftMargin;
	qreal								topMargin;
	qreal								rightMargin;
	qreal								bottomMargin;
	int									indent;
	int									lineHeight;
	int									lineHeightType;
	bool								nonBreakableLines;
	QTextTableFormat::PageBreakFlags	pageBreakPolicy;
	int									textIndent;
	Qt::LayoutDirection					layoutDirection;
	QList<QTextOption::Tab>				tabs;
	QBrush								background;
	QBrush								foreground;
	QMap<int, QVariant>					properties;

	//UNUSED
	int									id;
	int									type;
	QString								typeText;

	QDomNamedNodeMap		attributes	= element.attributes();
	for(int x = 0;x < attributes.count();x++)
	{
		QDomNode	node	= attributes.item(x);

		if(!node.toAttr().name().compare("id", Qt::CaseInsensitive))
			id						= node.toAttr().nodeValue().toInt();
		else if(!node.toAttr().name().compare("type", Qt::CaseInsensitive))
			type					= node.toAttr().nodeValue().toInt();
		else if(!node.toAttr().name().compare("typeText", Qt::CaseInsensitive))
			typeText				= node.toAttr().nodeValue();
		else if(!node.toAttr().name().compare("alignment", Qt::CaseInsensitive))
			alignment			= (Qt::AlignmentFlag)node.toAttr().nodeValue().toInt();
		else if(!node.toAttr().name().compare("leftMargin", Qt::CaseInsensitive))
			leftMargin			= node.toAttr().nodeValue().toDouble();
		else if(!node.toAttr().name().compare("topMargin", Qt::CaseInsensitive))
			topMargin			= node.toAttr().nodeValue().toDouble();
		else if(!node.toAttr().name().compare("rightMargin", Qt::CaseInsensitive))
			rightMargin			= node.toAttr().nodeValue().toDouble();
		else if(!node.toAttr().name().compare("bottomMargin", Qt::CaseInsensitive))
			bottomMargin		= node.toAttr().nodeValue().toDouble();
		else if(!node.toAttr().name().compare("indent", Qt::CaseInsensitive))
			indent				= node.toAttr().nodeValue().toDouble();
		else if(!node.toAttr().name().compare("lineHeight", Qt::CaseInsensitive))
			lineHeight			= node.toAttr().nodeValue().toDouble();
		else if(!node.toAttr().name().compare("lineHeightType", Qt::CaseInsensitive))
			lineHeightType		= node.toAttr().nodeValue().toDouble();
		else if(!node.toAttr().name().compare("nonBreakableLines", Qt::CaseInsensitive))
			nonBreakableLines	= node.toAttr().nodeValue().compare("true", Qt::CaseInsensitive) == 0 ? true : false;
		else if(!node.toAttr().name().compare("pageBreakPolicy", Qt::CaseInsensitive))
			pageBreakPolicy		= (QTextTableFormat::PageBreakFlags)node.toAttr().nodeValue().toInt();
		else if(!node.toAttr().name().compare("textIndent", Qt::CaseInsensitive))
			textIndent			= node.toAttr().nodeValue().toDouble();
		else if(!node.toAttr().name().compare("layoutDirection", Qt::CaseInsensitive))
			layoutDirection		= (Qt::LayoutDirection)node.toAttr().nodeValue().toInt();
		else
			myDebug << " parseTextBlockFormat: unknown attribute: " << node.toAttr().name();
	}

	//UNUSED
	id			= id;
	type		= type;
	typeText	= typeText;

	QDomNode				child		= element.firstChild();

	while(!child.isNull())
	{
		if(!child.toElement().tagName().compare("background", Qt::CaseInsensitive))
			background	= parseBrush(child.toElement());
		else if(!child.toElement().tagName().compare("foreground", Qt::CaseInsensitive))
			foreground	= parseBrush(child.toElement());
		else if(!child.toElement().tagName().compare("properties", Qt::CaseInsensitive))
		{
			int				key;
			QVariant::Type	type;
			QString			value;

			QDomNode		property	= child.toElement().firstChild();

			while(!property.isNull())
			{
				if(!property.toElement().tagName().compare("key", Qt::CaseInsensitive))
					key		= property.toElement().toElement().nodeValue().toInt();
				else if(!property.toElement().tagName().compare("type", Qt::CaseInsensitive))
					type	= (QVariant::Type)property.toElement().nodeValue().toInt();
				else if(!property.toElement().tagName().compare("value", Qt::CaseInsensitive))
					value	= property.toElement().nodeValue();

				QVariant	propertyValue(value);
				propertyValue.convert(type);
				properties.insert(key, propertyValue);

				property	= property.nextSibling();
			}
		}
		else if(!child.toElement().tagName().compare("tabPositions", Qt::CaseInsensitive))
			tabs	= parseTabPositions(child.toElement());
		else
			myDebug << " parseTextBlockFormat: unknown element: " << child.toElement().tagName();

		child	= child.nextSibling();
	}

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
	format.setTextIndent(textIndent);
	format.setTabPositions(tabs);
	format.setLayoutDirection(layoutDirection);

	background.setColor(QColor((int)(255*0.827451), (int)(255*0.827451), (int)(255*0.827451), (int)(255*1)));
	format.setBackground(background);
	format.setForeground(foreground);

	QMapIterator<int, QVariant> property(properties);
	while(property.hasNext())
	{
		property.next();
		format.setProperty(property.key(), property.value());
	}

	return(format);
}

QTextCharFormat cDocumentReader::parseTextCharFormat(const QDomElement& element)
{
	QString								anchorHref;
	bool								isAnchor;
	QString								toolTip;
	QTextImageFormat::VerticalAlignment	verticalAlignment;
	QPen								textOutline;
	QStringList							anchorNames;
	QFont								font;
	QColor								underlineColor;
	QBrush								background;
	QBrush								foreground;
	QMap<int, QVariant>					properties;
	Qt::LayoutDirection					layoutDirection;

	//UNUSED
	int									id;
	int									type;
	QString								typeText;

	QDomNamedNodeMap		attributes	= element.attributes();
	for(int x = 0;x < attributes.count();x++)
	{
		QDomNode	node	= attributes.item(x);

		if(!node.toAttr().name().compare("id", Qt::CaseInsensitive))
			id						= node.toAttr().nodeValue().toInt();
		else if(!node.toAttr().name().compare("type", Qt::CaseInsensitive))
			type					= node.toAttr().nodeValue().toInt();
		else if(!node.toAttr().name().compare("typeText", Qt::CaseInsensitive))
			typeText				= node.toAttr().nodeValue();
		else if(!node.toAttr().name().compare("anchorHref", Qt::CaseInsensitive))
			anchorHref				= node.toAttr().nodeValue();
		else if(!node.toAttr().name().compare("type", Qt::CaseInsensitive))
			anchorHref				= node.toAttr().nodeValue();
		else if(!node.toAttr().name().compare("isAnchor", Qt::CaseInsensitive))
			isAnchor				= node.toAttr().nodeValue().compare("true", Qt::CaseInsensitive) == 0 ? true : false;
		else if(!node.toAttr().name().compare("toolTip", Qt::CaseInsensitive))
			toolTip					= node.toAttr().nodeValue();
		else if(!node.toAttr().name().compare("verticalAlignment", Qt::CaseInsensitive))
			verticalAlignment		= (QTextImageFormat::VerticalAlignment)node.toAttr().nodeValue().toInt();
		else if(!node.toAttr().name().compare("layoutDirection", Qt::CaseInsensitive))
			layoutDirection		= (Qt::LayoutDirection)node.toAttr().nodeValue().toInt();
		else
			myDebug << " parseTextCharFormat: unknown attribute: " << node.toAttr().name();
	}

	//UNUSED
	id			= id;
	type		= type;
	typeText	= typeText;

	QDomNode				child		= element.firstChild();

	while(!child.isNull())
	{
		if(!child.toElement().tagName().compare("background", Qt::CaseInsensitive))
			background	= parseBrush(child.toElement());
		else if(!child.toElement().tagName().compare("foreground", Qt::CaseInsensitive))
			foreground	= parseBrush(child.toElement());
		else if(!child.toElement().tagName().compare("properties", Qt::CaseInsensitive))
		{
			int				key;
			QVariant::Type	type;
			QString			value;

			QDomNode		property	= child.toElement().firstChild();

			while(!property.isNull())
			{
				if(!property.toElement().tagName().compare("key", Qt::CaseInsensitive))
					key		= property.toElement().toElement().nodeValue().toInt();
				else if(!property.toElement().tagName().compare("type", Qt::CaseInsensitive))
					type	= (QVariant::Type)property.toElement().nodeValue().toInt();
				else if(!property.toElement().tagName().compare("value", Qt::CaseInsensitive))
					value	= property.toElement().nodeValue();

				QVariant	propertyValue(value);
				propertyValue.convert(type);
				properties.insert(key, propertyValue);

				property	= property.nextSibling();
			}
		}
		else if(!child.toElement().tagName().compare("textOutline", Qt::CaseInsensitive))
			textOutline	= parsePen(child.toElement());
		else if(!child.toElement().tagName().compare("anchorNames", Qt::CaseInsensitive))
		{

			QDomNode		anchors		= child.toElement().firstChild();

			while(!anchors.isNull())
			{
				if(!child.toElement().tagName().compare("anchor", Qt::CaseInsensitive))
					anchorNames.append(child.toElement().nodeValue());

				anchors	= anchors.nextSibling();
			}
		}
		else if(!child.toElement().tagName().compare("font", Qt::CaseInsensitive))
			font			= parseFont(child.toElement());
		else if(!child.toElement().tagName().compare("underlineColor", Qt::CaseInsensitive))
			underlineColor	= parseColor(child.toElement());
		else
			myDebug << " parseTextCharFormat: unknown element: " << child.toElement().tagName();

		child	= child.nextSibling();
	}

	QTextCharFormat	format;

	format.setAnchorHref(anchorHref);
	format.setFont(font);
	format.setAnchor(isAnchor);
	format.setToolTip(toolTip);
	format.setVerticalAlignment(verticalAlignment);
	format.setBackground(background);
	format.setForeground(foreground);
	format.setTextOutline(textOutline);
	format.setAnchorNames(anchorNames);
	format.setLayoutDirection(layoutDirection);

	QMapIterator<int, QVariant> property(properties);
	while(property.hasNext())
	{
		property.next();
		format.setProperty(property.key(), property.value());
	}

	format.setUnderlineColor(underlineColor);

	return(format);
}

void cDocumentReader::parseTextBlock(const QDomElement& element, QTextCursor* lpCursor, const QVector<cTextFormat> &allFormats)
{
	int									blockFormatIndex;
	int									charFormatIndex;
	int									listFormatIndex;
	int									tableFormatIndex;
	QVector<QTextLayout::FormatRange>	textFormats;
	QString								text;

	QDomNamedNodeMap		attributes	= element.attributes();
	for(int x = 0;x < attributes.count();x++)
	{
		QDomNode	node	= attributes.item(x);

		if(!node.toAttr().name().compare("blockFormatIndex", Qt::CaseInsensitive))
			blockFormatIndex		= node.toAttr().nodeValue().toInt();
		else if(!node.toAttr().name().compare("charFormatIndex", Qt::CaseInsensitive))
			charFormatIndex			= node.toAttr().nodeValue().toInt();
		else if(!node.toAttr().name().compare("listFormatIndex", Qt::CaseInsensitive))
			listFormatIndex			= node.toAttr().nodeValue().toInt();
		else if(!node.toAttr().name().compare("tableFormatIndex", Qt::CaseInsensitive))
			tableFormatIndex		= node.toAttr().nodeValue().toInt();
		else
			myDebug << " parseTextBlock: unknown attribute: " << node.toAttr().name();
	}

	QDomNode				child		= element.firstChild();

	while(!child.isNull())
	{
		if(!child.toElement().tagName().compare("textFormats", Qt::CaseInsensitive))
			textFormats	= parseTextFormats(child.toElement());
		else if(!child.toElement().tagName().compare("text", Qt::CaseInsensitive))
			text		= child.toElement().text();
		else
			myDebug << " parseTextBlock: unknown element: " << child.toElement().tagName();

		child	= child.nextSibling();
	}

	int								indent;

	if(m_bFirstBlock)
	{
		m_bFirstBlock	= false;
		lpCursor->setBlockFormat(allFormats[blockFormatIndex].blockFormat);
		lpCursor->setCharFormat(allFormats[charFormatIndex].charFormat);
		lpCursor->setBlockCharFormat(allFormats[charFormatIndex].charFormat);
	}
	else
	{
		if(listFormatIndex != -1)
		{
			indent	= allFormats[listFormatIndex].listFormat.indent();

			if(!m_textLists.value(indent))
			{
				m_textLists.insert(allFormats[listFormatIndex].listFormat.indent(), lpCursor->insertList(allFormats[listFormatIndex].listFormat));
				lpCursor->setBlockFormat(allFormats[blockFormatIndex].blockFormat);
				lpCursor->setCharFormat(allFormats[charFormatIndex].charFormat);
				lpCursor->setBlockCharFormat(allFormats[charFormatIndex].charFormat);
			}
			else
			{
				lpCursor->insertBlock();
				lpCursor->setBlockFormat(allFormats[blockFormatIndex].blockFormat);
				lpCursor->setCharFormat(allFormats[charFormatIndex].charFormat);
				lpCursor->setBlockCharFormat(allFormats[charFormatIndex].charFormat);
			}

			QTextBlock	block	= lpCursor->block();
			QTextList*	list	= m_textLists.value(indent);
			list->add(block);
		}
//		else if(tableFormatIndex != -1)
//			lpCursor->insertTable(allFormats[tableFormatIndex].tableFormat);
		else
		{
			m_textLists.clear();
			lpCursor->insertBlock();
			lpCursor->setBlockFormat(allFormats[blockFormatIndex].blockFormat);
			lpCursor->setCharFormat(allFormats[charFormatIndex].charFormat);
			lpCursor->setBlockCharFormat(allFormats[charFormatIndex].charFormat);
		}
	}

	for(int x = 0;x < textFormats.count();x++)
	{
		QTextLayout::FormatRange	textFormat	= textFormats[x];
		int							start		= textFormat.start;
		int							length		= textFormat.length;
		QTextCharFormat				format		= textFormat.format;
		QString						textPart	= text.mid(start, length);
		lpCursor->insertText(textPart, format);
	}
}

QVector<QTextLayout::FormatRange> cDocumentReader::parseTextFormats(const QDomElement& element)
{
	QDomNode							child		= element.firstChild();
	QVector<QTextLayout::FormatRange>	formats;

	while(!child.isNull())
	{
		if(!child.toElement().tagName().compare("range", Qt::CaseInsensitive))
		{
			QTextLayout::FormatRange	range	= parseRange(child.toElement());
			formats.append(range);
		}
		else
			myDebug << " parseTextFormats: unknown element: " << child.toElement().tagName();

		child	= child.nextSibling();
	}

	return(formats);
}

QTextLayout::FormatRange cDocumentReader::parseRange(const QDomElement& element)
{
	int									start;
	int									length;
	QString								anchorHref;
	bool								isAnchor;
	QString								toolTip;
	QTextImageFormat::VerticalAlignment	verticalAlignment;
	Qt::LayoutDirection					layoutDirection;

	QBrush								background;
	QBrush								foreground;
	QPen								textOutline;
	QStringList							anchorNames;
	QMap<int, QVariant>					properties;
	QFont								font;
	QColor								underlineColor;

	QDomNamedNodeMap		attributes	= element.attributes();
	for(int x = 0;x < attributes.count();x++)
	{
		QDomNode	node	= attributes.item(x);

		if(!node.toAttr().name().compare("start", Qt::CaseInsensitive))
			start					= node.toAttr().nodeValue().toInt();
		else if(!node.toAttr().name().compare("length", Qt::CaseInsensitive))
			length					= node.toAttr().nodeValue().toInt();
		else if(!node.toAttr().name().compare("anchorHref", Qt::CaseInsensitive))
			anchorHref				= node.toAttr().nodeValue();
		else if(!node.toAttr().name().compare("isAnchor", Qt::CaseInsensitive))
			isAnchor				= node.toAttr().nodeValue().compare("true", Qt::CaseInsensitive) == 0 ? true : false;
		else if(!node.toAttr().name().compare("toolTip", Qt::CaseInsensitive))
			toolTip					= node.toAttr().nodeValue();
		else if(!node.toAttr().name().compare("verticalAlignment", Qt::CaseInsensitive))
			verticalAlignment		= (QTextImageFormat::VerticalAlignment)node.toAttr().nodeValue().toInt();
		else if(!node.toAttr().name().compare("layoutDirection", Qt::CaseInsensitive))
			layoutDirection	= (Qt::LayoutDirection)node.toAttr().nodeValue().toInt();
		else
			myDebug << " parseRange: unknown attribute: " << node.toAttr().name();
	}

	QDomNode				child		= element.firstChild();

	while(!child.isNull())
	{
		if(!child.toElement().tagName().compare("background", Qt::CaseInsensitive))
			background	= parseBrush(child.toElement());
		else if(!child.toElement().tagName().compare("foreground", Qt::CaseInsensitive))
			foreground	= parseBrush(child.toElement());
		else if(!child.toElement().tagName().compare("properties", Qt::CaseInsensitive))
		{
			int				key;
			QVariant::Type	type;
			QString			value;

			QDomNode		property	= child.toElement().firstChild();

			while(!property.isNull())
			{
				if(!property.toElement().tagName().compare("key", Qt::CaseInsensitive))
					key		= property.toElement().toElement().nodeValue().toInt();
				else if(!property.toElement().tagName().compare("type", Qt::CaseInsensitive))
					type	= (QVariant::Type)property.toElement().nodeValue().toInt();
				else if(!property.toElement().tagName().compare("value", Qt::CaseInsensitive))
					value	= property.toElement().nodeValue();

				QVariant	propertyValue(value);
				propertyValue.convert(type);
				properties.insert(key, propertyValue);

				property	= property.nextSibling();
			}
		}
		else if(!child.toElement().tagName().compare("textOutline", Qt::CaseInsensitive))
			textOutline	= parsePen(child.toElement());
		else if(!child.toElement().tagName().compare("anchorNames", Qt::CaseInsensitive))
		{

			QDomNode		anchors		= child.toElement().firstChild();

			while(!anchors.isNull())
			{
				if(!child.toElement().tagName().compare("anchor", Qt::CaseInsensitive))
					anchorNames.append(child.toElement().nodeValue());

				anchors	= anchors.nextSibling();
			}
		}
		else if(!child.toElement().tagName().compare("font", Qt::CaseInsensitive))
			font			= parseFont(child.toElement());
		else if(!child.toElement().tagName().compare("underlineColor", Qt::CaseInsensitive))
			underlineColor	= parseColor(child.toElement());
		else
			myDebug << " parseTextCharFormat: unknown element: " << child.toElement().tagName();

		child	= child.nextSibling();
	}

	QTextCharFormat						format;

	format.setAnchorHref(anchorHref);
	format.setFont(font);
	format.setAnchor(isAnchor);
	format.setToolTip(toolTip);
	format.setVerticalAlignment(verticalAlignment);
	format.setBackground(background);
	format.setForeground(foreground);
	format.setTextOutline(textOutline);
	format.setAnchorNames(anchorNames);
	format.setLayoutDirection(layoutDirection);

	QMapIterator<int, QVariant> property(properties);
	while(property.hasNext())
	{
		property.next();
		format.setProperty(property.key(), property.value());
	}

	format.setUnderlineColor(underlineColor);

	QTextLayout::FormatRange			range;

	range.start							= start;
	range.length						= length;
	range.format						= format;

	return(range);
}
