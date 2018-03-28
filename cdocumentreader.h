#ifndef CDOCUMENTREADER_H
#define CDOCUMENTREADER_H


#include <QXmlStreamReader>

#include <QFile>
#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>

#include <QFont>
#include <QTextOption>
#include <QTextFormat>
#include <QBrush>
#include <QColor>

#include <QTextTableCellFormat>
#include <QTextTableFormat>
#include <QTextImageFormat>
#include <QTextFrameFormat>
#include <QTextListFormat>
#include <QTextBlockFormat>
#include <QTextCharFormat>
#include <QTextLayout>
#include <QTextBlock>
#include <QTextCursor>

#include <JlCompress.h>


class cTextDocument;

class cTextFormat
{
public:
	enum TextFormatType
	{
		TextFormatTypeUnknown	= 0,
		TextFormatTypeTableCell	= 1,
		TextFormatTypeTable		= 2,
		TextFormatTypeImage		= 3,
		TextFormatTypeFrame		= 4,
		TextFormatTypeList		= 5,
		TextFormatTypeBlock		= 6,
		TextFormatTypeChar		= 7,
	};

	cTextFormat(TextFormatType type = TextFormatTypeUnknown) : m_type(type) {}
	cTextFormat(const QString& szType) : m_type(TextFormatTypeUnknown)
	{
		if(szType.compare("tableCellFormat", Qt::CaseInsensitive))
			m_type			= TextFormatTypeTableCell;
		else if(szType.compare("tableFormat", Qt::CaseInsensitive))
			m_type			= TextFormatTypeTable;
		else if(szType.compare("imageFormat", Qt::CaseInsensitive))
			m_type			= TextFormatTypeImage;
		else if(szType.compare("frameFormat", Qt::CaseInsensitive))
			m_type			= TextFormatTypeFrame;
		else if(szType.compare("listFormat", Qt::CaseInsensitive))
			m_type			= TextFormatTypeList;
		else if(szType.compare("blockFormat", Qt::CaseInsensitive))
			m_type			= TextFormatTypeBlock;
		else if(szType.compare("charFormat", Qt::CaseInsensitive))
			m_type			= TextFormatTypeChar;
	}

	void					setTableCellFormat(const QTextTableCellFormat& format)
	{
		tableCellFormat		= format;
		m_type				= TextFormatTypeTableCell;
	}
	void					setTableFormat(const QTextTableFormat& format)
	{
		tableFormat			= format;
		m_type				= TextFormatTypeTable;
	}
	void					setImageFormat(const QTextImageFormat& format)
	{
		imageFormat			= format;
		m_type				= TextFormatTypeImage;
	}
	void					setFrameFormat(const QTextFrameFormat& format)
	{
		frameFormat			= format;
		m_type				= TextFormatTypeFrame;
	}
	void					setListFormat(const QTextListFormat& format)
	{
		listFormat			= format;
		m_type				= TextFormatTypeList;
	}
	void					setBlockFormat(const QTextBlockFormat& format)
	{
		blockFormat			= format;
		m_type				= TextFormatTypeBlock;
	}
	void					setCharFormat(const QTextCharFormat& format)
	{
		charFormat			= format;
		m_type				= TextFormatTypeChar;
	}

	bool					isValid()
	{
		switch(m_type)
		{
		case TextFormatTypeTableCell:
			return(tableCellFormat.isValid());
		case TextFormatTypeTable:
			return(tableFormat.isValid());
		case TextFormatTypeImage:
			return(imageFormat.isValid());
		case TextFormatTypeFrame:
			return(frameFormat.isValid());
		case TextFormatTypeList:
			return(listFormat.isValid());
		case TextFormatTypeBlock:
			return(blockFormat.isValid());
		case TextFormatTypeChar:
			return(charFormat.isValid());
		case TextFormatTypeUnknown:
			return(false);
		}
		return(false);
	}

	void					setLayoutDirection(Qt::LayoutDirection layoutDirection)
	{
		switch(m_type)
		{
		case TextFormatTypeTableCell:
			tableCellFormat.setLayoutDirection(layoutDirection);
			break;
		case TextFormatTypeTable:
			tableFormat.setLayoutDirection(layoutDirection);
			break;
		case TextFormatTypeImage:
			imageFormat.setLayoutDirection(layoutDirection);
			break;
		case TextFormatTypeFrame:
			frameFormat.setLayoutDirection(layoutDirection);
			break;
		case TextFormatTypeList:
			listFormat.setLayoutDirection(layoutDirection);
			break;
		case TextFormatTypeBlock:
			blockFormat.setLayoutDirection(layoutDirection);
			break;
		case TextFormatTypeChar:
			charFormat.setLayoutDirection(layoutDirection);
			break;
		case TextFormatTypeUnknown:
			break;
		}
	}

	QTextTableCellFormat	tableCellFormat;
	QTextTableFormat		tableFormat;
	QTextImageFormat		imageFormat;
	QTextFrameFormat		frameFormat;
	QTextListFormat			listFormat;
	QTextBlockFormat		blockFormat;
	QTextCharFormat			charFormat;
	TextFormatType			m_type;
};

class cDocumentReader : public QXmlStreamReader
{
public:
	cDocumentReader(const QString& szFileName, bool bZip = true);
	~cDocumentReader();

	bool								open();
	bool								close();

	cTextDocument*						readDocument();
private:
	bool								m_bFirstBlock;
	bool								m_bZip;
	QString								m_szFileName;
	QFile								m_file;
	QuaZip								m_zip;
	QuaZipFile							m_zipFile;

	QMap<int, QTextList*>				m_textLists;

	void								parseSettings(const QDomElement& element, cTextDocument* lpDocument);
	void								parseDefaults(const QDomElement& element, cTextDocument* lpDocument);
	void								parseTextBlock(const QDomElement& element, QTextCursor *lpCursor, const QVector<cTextFormat>& allFormats);

	QVector<QTextLayout::FormatRange>	parseTextFormats(const QDomElement& element);
	QTextLayout::FormatRange			parseRange(const QDomElement& element);
	QFont								parseFont(const QDomElement& element);
	QTextOption							parseDefaultTextOption(const QDomElement& element);
	QList<QTextOption::Tab>				parseTabPositions(const QDomElement& element);
	QVector<cTextFormat> parseAllFormats(const QDomElement& element);
	cTextFormat parseFormat(const QDomElement& element);
	QPen								parsePen(const QDomElement& element);
	QBrush								parseBrush(const QDomElement& element);
	QColor								parseColor(const QDomElement& element);

	QTextTableCellFormat				parseTextTableCellFormat(const QDomElement& element);
	QTextTableFormat					parseTextTableFormat(const QDomElement& element);
	QTextImageFormat					parseTextImageFormat(const QDomElement& element);
	QTextFrameFormat					parseTextFrameFormat(const QDomElement& element);
	QTextListFormat						parseTextListFormat(const QDomElement& element);
	QTextBlockFormat					parseTextBlockFormat(const QDomElement& element);
	QTextCharFormat						parseTextCharFormat(const QDomElement& element);
};

#endif // CDOCUMENTREADER_H
