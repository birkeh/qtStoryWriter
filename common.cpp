/*!
 \file common.cpp

*/

#include "common.h"

#include <QBuffer>
#include <QSettings>
#include <QCoreApplication>
#include <QDir>
#include <QMap>


QString uncompressText(const QByteArray& compressed)
{
	if(compressed.isNull() || compressed.isEmpty())
		return("");
	return(qUncompress(compressed));
}

QByteArray compressText(const QString& uncompressed)
{
	if(uncompressed.isNull() || uncompressed.isEmpty())
		return(QByteArray());
	return(qCompress(uncompressed.toUtf8()));
}

QPixmap blob2Image(const QByteArray& ba)
{
	QPixmap		image;

	if(!ba.isEmpty())
	{
		if(!image.loadFromData(ba))
			myDebug << "image load error.";
	}

	return(image);
}

QByteArray image2Blob(const QPixmap &image)
{
	QByteArray	ba;
	QBuffer		buffer(&ba);
	buffer.open(QIODevice::WriteOnly);
	image.save(&buffer, "JPG");
	buffer.close();

	return(ba);
}

cTextDocument*	blob2TextDocument(const QByteArray& ba)
{
	cTextDocument*	lpTextDocument	= new cTextDocument;
	if(ba.isEmpty())
	{
		lpTextDocument->setHtml("");
		return(lpTextDocument);
	}

	lpTextDocument->setHtml(uncompressText(ba));
	return(lpTextDocument);
}

QByteArray textDocument2Blob(cTextDocument* lpTextDocument)
{
	QByteArray	ba;

	if(!lpTextDocument)
		return(ba);

	ba	= compressText(lpTextDocument->toHtml());

	return(ba);
}

QString	 localePath()
{
	QSettings	settings;
	QString		szAppPath	= QCoreApplication::applicationDirPath();
	QString		szPath		= settings.value("file/locale", QString("%1%2locale").arg(szAppPath).arg(QDir::separator())).toString();
	return(szPath);
}

QString paperName(QPagedPaintDevice::PageSize paperSize)
{
	QMap<QPagedPaintDevice::PageSize, QString>	list	= paperList();
	return(list.value(paperSize));
}

QPagedPaintDevice::PageSize paperKey(const QString& szPaperSize)
{
	QMap<QPagedPaintDevice::PageSize, QString>	list	= paperList();
	return(list.key(szPaperSize));
}

QMap<QPagedPaintDevice::PageSize, QString> paperList()
{
	QMap<QPagedPaintDevice::PageSize, QString>	list;

	list.insert(QPagedPaintDevice::A0, QObject::tr("A0"));
	list.insert(QPagedPaintDevice::A1, QObject::tr("A1"));
	list.insert(QPagedPaintDevice::A2, QObject::tr("A2"));
	list.insert(QPagedPaintDevice::A3, QObject::tr("A3"));
	list.insert(QPagedPaintDevice::A4, QObject::tr("A4"));
	list.insert(QPagedPaintDevice::A5, QObject::tr("A5"));
	list.insert(QPagedPaintDevice::A6, QObject::tr("A6"));
	list.insert(QPagedPaintDevice::A7, QObject::tr("A7"));
	list.insert(QPagedPaintDevice::A8, QObject::tr("A8"));
	list.insert(QPagedPaintDevice::A9, QObject::tr("A9"));
	list.insert(QPagedPaintDevice::B0, QObject::tr("B0"));
	list.insert(QPagedPaintDevice::B1, QObject::tr("B1"));
	list.insert(QPagedPaintDevice::B2, QObject::tr("B2"));
	list.insert(QPagedPaintDevice::B3, QObject::tr("B3"));
	list.insert(QPagedPaintDevice::B4, QObject::tr("B4"));
	list.insert(QPagedPaintDevice::B5, QObject::tr("B5"));
	list.insert(QPagedPaintDevice::B6, QObject::tr("B6"));
	list.insert(QPagedPaintDevice::B7, QObject::tr("B7"));
	list.insert(QPagedPaintDevice::B8, QObject::tr("B8"));
	list.insert(QPagedPaintDevice::B9, QObject::tr("B9"));
	list.insert(QPagedPaintDevice::B10, QObject::tr("B10"));
	list.insert(QPagedPaintDevice::C5E, QObject::tr("C5E"));
	list.insert(QPagedPaintDevice::Comm10E, QObject::tr("Comm10E"));
	list.insert(QPagedPaintDevice::DLE, QObject::tr("DLE"));
	list.insert(QPagedPaintDevice::Executive, QObject::tr("Executive"));
	list.insert(QPagedPaintDevice::Folio, QObject::tr("Folio"));
	list.insert(QPagedPaintDevice::Ledger, QObject::tr("Ledger"));
	list.insert(QPagedPaintDevice::Legal, QObject::tr("Legal"));
	list.insert(QPagedPaintDevice::Letter, QObject::tr("Letter"));
	list.insert(QPagedPaintDevice::Tabloid, QObject::tr("Tabloid"));
	list.insert(QPagedPaintDevice::Custom, QObject::tr("Custom"));
	list.insert(QPagedPaintDevice::A10, QObject::tr("A10"));
	list.insert(QPagedPaintDevice::A3Extra, QObject::tr("A3Extra"));
	list.insert(QPagedPaintDevice::A4Extra, QObject::tr("A4Extra"));
	list.insert(QPagedPaintDevice::A4Plus, QObject::tr("A4Plus"));
	list.insert(QPagedPaintDevice::A4Small, QObject::tr("A4Small"));
	list.insert(QPagedPaintDevice::A5Extra, QObject::tr("A5Extra"));
	list.insert(QPagedPaintDevice::B5Extra, QObject::tr("B5Extra"));
	list.insert(QPagedPaintDevice::JisB0, QObject::tr("JisB0"));
	list.insert(QPagedPaintDevice::JisB1, QObject::tr("JisB1"));
	list.insert(QPagedPaintDevice::JisB2, QObject::tr("JisB2"));
	list.insert(QPagedPaintDevice::JisB3, QObject::tr("JisB3"));
	list.insert(QPagedPaintDevice::JisB4, QObject::tr("JisB4"));
	list.insert(QPagedPaintDevice::JisB5, QObject::tr("JisB5"));
	list.insert(QPagedPaintDevice::JisB6, QObject::tr("JisB6"));
	list.insert(QPagedPaintDevice::JisB7, QObject::tr("JisB7"));
	list.insert(QPagedPaintDevice::JisB8, QObject::tr("JisB8"));
	list.insert(QPagedPaintDevice::JisB9, QObject::tr("JisB9"));
	list.insert(QPagedPaintDevice::JisB10, QObject::tr("JisB10"));
	list.insert(QPagedPaintDevice::AnsiA, QObject::tr("Letter"));
	list.insert(QPagedPaintDevice::AnsiB, QObject::tr("Ledger"));
	list.insert(QPagedPaintDevice::AnsiC, QObject::tr("AnsiC"));
	list.insert(QPagedPaintDevice::AnsiD, QObject::tr("AnsiD"));
	list.insert(QPagedPaintDevice::AnsiE, QObject::tr("AnsiE"));
	list.insert(QPagedPaintDevice::LegalExtra, QObject::tr("LegalExtra"));
	list.insert(QPagedPaintDevice::LetterExtra, QObject::tr("LetterExtra"));
	list.insert(QPagedPaintDevice::LetterPlus, QObject::tr("LetterPlus"));
	list.insert(QPagedPaintDevice::LetterSmall, QObject::tr("LetterSmall"));
	list.insert(QPagedPaintDevice::TabloidExtra, QObject::tr("TabloidExtra"));
	list.insert(QPagedPaintDevice::ArchA, QObject::tr("ArchA"));
	list.insert(QPagedPaintDevice::ArchB, QObject::tr("ArchB"));
	list.insert(QPagedPaintDevice::ArchC, QObject::tr("ArchC"));
	list.insert(QPagedPaintDevice::ArchD, QObject::tr("ArchD"));
	list.insert(QPagedPaintDevice::ArchE, QObject::tr("ArchE"));
	list.insert(QPagedPaintDevice::Imperial7x9, QObject::tr("Imperial7x9"));
	list.insert(QPagedPaintDevice::Imperial8x10, QObject::tr("Imperial8x10"));
	list.insert(QPagedPaintDevice::Imperial9x11, QObject::tr("Imperial9x11"));
	list.insert(QPagedPaintDevice::Imperial9x12, QObject::tr("Imperial9x12"));
	list.insert(QPagedPaintDevice::Imperial10x11, QObject::tr("Imperial10x11"));
	list.insert(QPagedPaintDevice::Imperial10x13, QObject::tr("Imperial10x13"));
	list.insert(QPagedPaintDevice::Imperial10x14, QObject::tr("Imperial10x14"));
	list.insert(QPagedPaintDevice::Imperial12x11, QObject::tr("Imperial12x11"));
	list.insert(QPagedPaintDevice::Imperial15x11, QObject::tr("Imperial15x11"));
	list.insert(QPagedPaintDevice::ExecutiveStandard, QObject::tr("ExecutiveStandard"));
	list.insert(QPagedPaintDevice::Note, QObject::tr("Note"));
	list.insert(QPagedPaintDevice::Quarto, QObject::tr("Quarto"));
	list.insert(QPagedPaintDevice::Statement, QObject::tr("Statement"));
	list.insert(QPagedPaintDevice::SuperA, QObject::tr("SuperA"));
	list.insert(QPagedPaintDevice::SuperB, QObject::tr("SuperB"));
	list.insert(QPagedPaintDevice::Postcard, QObject::tr("Postcard"));
	list.insert(QPagedPaintDevice::DoublePostcard, QObject::tr("DoublePostcard"));
	list.insert(QPagedPaintDevice::Prc16K, QObject::tr("Prc16K"));
	list.insert(QPagedPaintDevice::Prc32K, QObject::tr("Prc32K"));
	list.insert(QPagedPaintDevice::Prc32KBig, QObject::tr("Prc32KBig"));
	list.insert(QPagedPaintDevice::FanFoldUS, QObject::tr("FanFoldUS"));
	list.insert(QPagedPaintDevice::FanFoldGerman, QObject::tr("FanFoldGerman"));
	list.insert(QPagedPaintDevice::FanFoldGermanLegal, QObject::tr("FanFoldGermanLegal"));
	list.insert(QPagedPaintDevice::EnvelopeB4, QObject::tr("EnvelopeB4"));
	list.insert(QPagedPaintDevice::EnvelopeB5, QObject::tr("EnvelopeB5"));
	list.insert(QPagedPaintDevice::EnvelopeB6, QObject::tr("EnvelopeB6"));
	list.insert(QPagedPaintDevice::EnvelopeC0, QObject::tr("EnvelopeC0"));
	list.insert(QPagedPaintDevice::EnvelopeC1, QObject::tr("EnvelopeC1"));
	list.insert(QPagedPaintDevice::EnvelopeC2, QObject::tr("EnvelopeC2"));
	list.insert(QPagedPaintDevice::EnvelopeC3, QObject::tr("EnvelopeC3"));
	list.insert(QPagedPaintDevice::EnvelopeC4, QObject::tr("EnvelopeC4"));
	list.insert(QPagedPaintDevice::EnvelopeC5, QObject::tr("EnvelopeC5"));
	list.insert(QPagedPaintDevice::EnvelopeC6, QObject::tr("EnvelopeC6"));
	list.insert(QPagedPaintDevice::EnvelopeC65, QObject::tr("EnvelopeC65"));
	list.insert(QPagedPaintDevice::EnvelopeC7, QObject::tr("EnvelopeC7"));
	list.insert(QPagedPaintDevice::EnvelopeDL, QObject::tr("EnvelopeDL"));
	list.insert(QPagedPaintDevice::Envelope9, QObject::tr("Envelope9"));
	list.insert(QPagedPaintDevice::Envelope10, QObject::tr("Envelope10"));
	list.insert(QPagedPaintDevice::Envelope11, QObject::tr("Envelope11"));
	list.insert(QPagedPaintDevice::Envelope12, QObject::tr("Envelope12"));
	list.insert(QPagedPaintDevice::Envelope14, QObject::tr("Envelope14"));
	list.insert(QPagedPaintDevice::EnvelopeMonarch, QObject::tr("EnvelopeMonarch"));
	list.insert(QPagedPaintDevice::EnvelopePersonal, QObject::tr("EnvelopePersonal"));
	list.insert(QPagedPaintDevice::EnvelopeChou3, QObject::tr("EnvelopeChou3"));
	list.insert(QPagedPaintDevice::EnvelopeChou4, QObject::tr("EnvelopeChou4"));
	list.insert(QPagedPaintDevice::EnvelopeInvite, QObject::tr("EnvelopeInvite"));
	list.insert(QPagedPaintDevice::EnvelopeItalian, QObject::tr("EnvelopeItalian"));
	list.insert(QPagedPaintDevice::EnvelopeKaku2, QObject::tr("EnvelopeKaku2"));
	list.insert(QPagedPaintDevice::EnvelopeKaku3, QObject::tr("EnvelopeKaku3"));
	list.insert(QPagedPaintDevice::EnvelopePrc1, QObject::tr("EnvelopePrc1"));
	list.insert(QPagedPaintDevice::EnvelopePrc2, QObject::tr("EnvelopePrc2"));
	list.insert(QPagedPaintDevice::EnvelopePrc3, QObject::tr("EnvelopePrc3"));
	list.insert(QPagedPaintDevice::EnvelopePrc4, QObject::tr("EnvelopePrc4"));
	list.insert(QPagedPaintDevice::EnvelopePrc5, QObject::tr("EnvelopePrc5"));
	list.insert(QPagedPaintDevice::EnvelopePrc6, QObject::tr("EnvelopePrc6"));
	list.insert(QPagedPaintDevice::EnvelopePrc7, QObject::tr("EnvelopePrc7"));
	list.insert(QPagedPaintDevice::EnvelopePrc8, QObject::tr("EnvelopePrc8"));
	list.insert(QPagedPaintDevice::EnvelopePrc9, QObject::tr("EnvelopePrc9"));
	list.insert(QPagedPaintDevice::EnvelopePrc10, QObject::tr("EnvelopePrc10"));
	list.insert(QPagedPaintDevice::EnvelopeYou4, QObject::tr("EnvelopeYou4"));

	return(list);
}

QString unitName(QPageLayout::Unit unit)
{
	QMap<QPageLayout::Unit, QString>	list	= unitList();
	return(list.value(unit));
}

QPageLayout::Unit unitKey(const QString& szUnit)
{
	QMap<QPageLayout::Unit, QString>	list	= unitList();
	return(list.key(szUnit));
}

QMap<QPageLayout::Unit, QString> unitList()
{
	QMap<QPageLayout::Unit, QString>	list;

	list.insert(QPageLayout::Millimeter, QObject::tr("Millimeter"));
	list.insert(QPageLayout::Point, QObject::tr("Point"));
	list.insert(QPageLayout::Inch, QObject::tr("Inch"));
	list.insert(QPageLayout::Pica, QObject::tr("Pica"));
	list.insert(QPageLayout::Didot, QObject::tr("Didot"));
	list.insert(QPageLayout::Cicero, QObject::tr("Cicero"));

	return(list);
}
