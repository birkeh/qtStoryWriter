#ifndef CDOCUMENTWRITER_H
#define CDOCUMENTWRITER_H


#include <QXmlStreamWriter>

#include <QFile>
#include <QString>

#include <QColor>
#include <QGradient>
#include <QPen>
#include <QBrush>
#include <QVector>
#include <QPair>

#include <QTextBlock>
#include <QTextBlockFormat>
#include <QTextCharFormat>
#include <QTextFormat>


class cTextDocument;


class cDocumentWriter : public QXmlStreamWriter
{
public:
	enum WritePart
	{
		WriteAll		= 3,
		WriteAttribute	= 1,
		WriteElements	= 2,
	};

	cDocumentWriter(const QString& szFileName);
	~cDocumentWriter();

	bool			open();
	bool			close();

	bool			writeDocument(cTextDocument* lpDocument);

private:
	QString			m_szFileName;
	QFile			m_file;

	void			writeTextBlockFormats(const QList<QPair<int, QTextBlockFormat>> textBlockFormats);
	void			writeTextBlocks(QTextBlock& textBlock);
	void			writeColor(QColor color);
	void			writeGradient(const QGradient* lpGradient);
	void			writePen(const QPen& pen);
	void			writeBrush(const QBrush& brush);
	void			writeFormat(const QTextFormat& textFormat, int id = -1);
	void			writeFont(const QFont& font);

	void			writeTextBlock(const QTextBlock& textBlock);

	void			writeFormats(const QVector<QTextFormat> formats);

	void			writeTextFormat(QTextFormat* lpTextFormat, int id = -1, WritePart part = WriteAll);
	void			writeTextBlockFormat(QTextBlockFormat* lpTextBlockFormat, int id = -1, WritePart part = WriteAll);
	void			writeTextCharFormat(QTextCharFormat* lpTextCharFormat, int id = -1, WritePart part = WriteAll);
	void			writeTextFrameFormat(QTextFrameFormat* lpTextFrameFormat, int id = -1, WritePart part = WriteAll);
	void			writeTextImageFormat(QTextImageFormat* lpTextImageFormat, int id = -1, WritePart part = WriteAll);
	void			writeTextListFormat(QTextListFormat* lpTextListFormat, int id = -1, WritePart part = WriteAll);
	void			writeTextTableCellFormat(QTextTableCellFormat* lpTextTableCellFormat, int id = -1, WritePart part = WriteAll);
	void			writeTextTableFormat(QTextTableFormat* lpTextTableFormat, int id = -1, WritePart part = WriteAll);

	void			writeTextOption(const QTextOption &textOption);

	void			writeTabPositions(const QList<QTextOption::Tab> tabs);
};

#endif // CDOCUMENTWRITER_H
