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

QString paperName(QPageSize::PageSizeId paperSize)
{
	QMap<QPageSize::PageSizeId, QString>	list	= paperList();
	return(list.value(paperSize));
}

QPageSize::PageSizeId paperKey(const QString& szPaperSize)
{
	QMap<QPageSize::PageSizeId, QString>	list	= paperList();
	return(list.key(szPaperSize));
}

QMap<QPageSize::PageSizeId, QString> paperList()
{
	QMap<QPageSize::PageSizeId, QString>	list;

	list.insert(QPageSize::A0, QObject::tr("A0"));
	list.insert(QPageSize::A1, QObject::tr("A1"));
	list.insert(QPageSize::A2, QObject::tr("A2"));
	list.insert(QPageSize::A3, QObject::tr("A3"));
	list.insert(QPageSize::A4, QObject::tr("A4"));
	list.insert(QPageSize::A5, QObject::tr("A5"));
	list.insert(QPageSize::A6, QObject::tr("A6"));
	list.insert(QPageSize::A7, QObject::tr("A7"));
	list.insert(QPageSize::A8, QObject::tr("A8"));
	list.insert(QPageSize::A9, QObject::tr("A9"));
	list.insert(QPageSize::B0, QObject::tr("B0"));
	list.insert(QPageSize::B1, QObject::tr("B1"));
	list.insert(QPageSize::B2, QObject::tr("B2"));
	list.insert(QPageSize::B3, QObject::tr("B3"));
	list.insert(QPageSize::B4, QObject::tr("B4"));
	list.insert(QPageSize::B5, QObject::tr("B5"));
	list.insert(QPageSize::B6, QObject::tr("B6"));
	list.insert(QPageSize::B7, QObject::tr("B7"));
	list.insert(QPageSize::B8, QObject::tr("B8"));
	list.insert(QPageSize::B9, QObject::tr("B9"));
	list.insert(QPageSize::B10, QObject::tr("B10"));
	list.insert(QPageSize::C5E, QObject::tr("C5E"));
	list.insert(QPageSize::Comm10E, QObject::tr("Comm10E"));
	list.insert(QPageSize::DLE, QObject::tr("DLE"));
	list.insert(QPageSize::Executive, QObject::tr("Executive"));
	list.insert(QPageSize::Folio, QObject::tr("Folio"));
	list.insert(QPageSize::Ledger, QObject::tr("Ledger"));
	list.insert(QPageSize::Legal, QObject::tr("Legal"));
	list.insert(QPageSize::Letter, QObject::tr("Letter"));
	list.insert(QPageSize::Tabloid, QObject::tr("Tabloid"));
	list.insert(QPageSize::Custom, QObject::tr("Custom"));
	list.insert(QPageSize::A10, QObject::tr("A10"));
	list.insert(QPageSize::A3Extra, QObject::tr("A3Extra"));
	list.insert(QPageSize::A4Extra, QObject::tr("A4Extra"));
	list.insert(QPageSize::A4Plus, QObject::tr("A4Plus"));
	list.insert(QPageSize::A4Small, QObject::tr("A4Small"));
	list.insert(QPageSize::A5Extra, QObject::tr("A5Extra"));
	list.insert(QPageSize::B5Extra, QObject::tr("B5Extra"));
	list.insert(QPageSize::JisB0, QObject::tr("JisB0"));
	list.insert(QPageSize::JisB1, QObject::tr("JisB1"));
	list.insert(QPageSize::JisB2, QObject::tr("JisB2"));
	list.insert(QPageSize::JisB3, QObject::tr("JisB3"));
	list.insert(QPageSize::JisB4, QObject::tr("JisB4"));
	list.insert(QPageSize::JisB5, QObject::tr("JisB5"));
	list.insert(QPageSize::JisB6, QObject::tr("JisB6"));
	list.insert(QPageSize::JisB7, QObject::tr("JisB7"));
	list.insert(QPageSize::JisB8, QObject::tr("JisB8"));
	list.insert(QPageSize::JisB9, QObject::tr("JisB9"));
	list.insert(QPageSize::JisB10, QObject::tr("JisB10"));
	list.insert(QPageSize::AnsiA, QObject::tr("Letter"));
	list.insert(QPageSize::AnsiB, QObject::tr("Ledger"));
	list.insert(QPageSize::AnsiC, QObject::tr("AnsiC"));
	list.insert(QPageSize::AnsiD, QObject::tr("AnsiD"));
	list.insert(QPageSize::AnsiE, QObject::tr("AnsiE"));
	list.insert(QPageSize::LegalExtra, QObject::tr("LegalExtra"));
	list.insert(QPageSize::LetterExtra, QObject::tr("LetterExtra"));
	list.insert(QPageSize::LetterPlus, QObject::tr("LetterPlus"));
	list.insert(QPageSize::LetterSmall, QObject::tr("LetterSmall"));
	list.insert(QPageSize::TabloidExtra, QObject::tr("TabloidExtra"));
	list.insert(QPageSize::ArchA, QObject::tr("ArchA"));
	list.insert(QPageSize::ArchB, QObject::tr("ArchB"));
	list.insert(QPageSize::ArchC, QObject::tr("ArchC"));
	list.insert(QPageSize::ArchD, QObject::tr("ArchD"));
	list.insert(QPageSize::ArchE, QObject::tr("ArchE"));
	list.insert(QPageSize::Imperial7x9, QObject::tr("Imperial7x9"));
	list.insert(QPageSize::Imperial8x10, QObject::tr("Imperial8x10"));
	list.insert(QPageSize::Imperial9x11, QObject::tr("Imperial9x11"));
	list.insert(QPageSize::Imperial9x12, QObject::tr("Imperial9x12"));
	list.insert(QPageSize::Imperial10x11, QObject::tr("Imperial10x11"));
	list.insert(QPageSize::Imperial10x13, QObject::tr("Imperial10x13"));
	list.insert(QPageSize::Imperial10x14, QObject::tr("Imperial10x14"));
	list.insert(QPageSize::Imperial12x11, QObject::tr("Imperial12x11"));
	list.insert(QPageSize::Imperial15x11, QObject::tr("Imperial15x11"));
	list.insert(QPageSize::ExecutiveStandard, QObject::tr("ExecutiveStandard"));
	list.insert(QPageSize::Note, QObject::tr("Note"));
	list.insert(QPageSize::Quarto, QObject::tr("Quarto"));
	list.insert(QPageSize::Statement, QObject::tr("Statement"));
	list.insert(QPageSize::SuperA, QObject::tr("SuperA"));
	list.insert(QPageSize::SuperB, QObject::tr("SuperB"));
	list.insert(QPageSize::Postcard, QObject::tr("Postcard"));
	list.insert(QPageSize::DoublePostcard, QObject::tr("DoublePostcard"));
	list.insert(QPageSize::Prc16K, QObject::tr("Prc16K"));
	list.insert(QPageSize::Prc32K, QObject::tr("Prc32K"));
	list.insert(QPageSize::Prc32KBig, QObject::tr("Prc32KBig"));
	list.insert(QPageSize::FanFoldUS, QObject::tr("FanFoldUS"));
	list.insert(QPageSize::FanFoldGerman, QObject::tr("FanFoldGerman"));
	list.insert(QPageSize::FanFoldGermanLegal, QObject::tr("FanFoldGermanLegal"));
	list.insert(QPageSize::EnvelopeB4, QObject::tr("EnvelopeB4"));
	list.insert(QPageSize::EnvelopeB5, QObject::tr("EnvelopeB5"));
	list.insert(QPageSize::EnvelopeB6, QObject::tr("EnvelopeB6"));
	list.insert(QPageSize::EnvelopeC0, QObject::tr("EnvelopeC0"));
	list.insert(QPageSize::EnvelopeC1, QObject::tr("EnvelopeC1"));
	list.insert(QPageSize::EnvelopeC2, QObject::tr("EnvelopeC2"));
	list.insert(QPageSize::EnvelopeC3, QObject::tr("EnvelopeC3"));
	list.insert(QPageSize::EnvelopeC4, QObject::tr("EnvelopeC4"));
	list.insert(QPageSize::EnvelopeC5, QObject::tr("EnvelopeC5"));
	list.insert(QPageSize::EnvelopeC6, QObject::tr("EnvelopeC6"));
	list.insert(QPageSize::EnvelopeC65, QObject::tr("EnvelopeC65"));
	list.insert(QPageSize::EnvelopeC7, QObject::tr("EnvelopeC7"));
	list.insert(QPageSize::EnvelopeDL, QObject::tr("EnvelopeDL"));
	list.insert(QPageSize::Envelope9, QObject::tr("Envelope9"));
	list.insert(QPageSize::Envelope10, QObject::tr("Envelope10"));
	list.insert(QPageSize::Envelope11, QObject::tr("Envelope11"));
	list.insert(QPageSize::Envelope12, QObject::tr("Envelope12"));
	list.insert(QPageSize::Envelope14, QObject::tr("Envelope14"));
	list.insert(QPageSize::EnvelopeMonarch, QObject::tr("EnvelopeMonarch"));
	list.insert(QPageSize::EnvelopePersonal, QObject::tr("EnvelopePersonal"));
	list.insert(QPageSize::EnvelopeChou3, QObject::tr("EnvelopeChou3"));
	list.insert(QPageSize::EnvelopeChou4, QObject::tr("EnvelopeChou4"));
	list.insert(QPageSize::EnvelopeInvite, QObject::tr("EnvelopeInvite"));
	list.insert(QPageSize::EnvelopeItalian, QObject::tr("EnvelopeItalian"));
	list.insert(QPageSize::EnvelopeKaku2, QObject::tr("EnvelopeKaku2"));
	list.insert(QPageSize::EnvelopeKaku3, QObject::tr("EnvelopeKaku3"));
	list.insert(QPageSize::EnvelopePrc1, QObject::tr("EnvelopePrc1"));
	list.insert(QPageSize::EnvelopePrc2, QObject::tr("EnvelopePrc2"));
	list.insert(QPageSize::EnvelopePrc3, QObject::tr("EnvelopePrc3"));
	list.insert(QPageSize::EnvelopePrc4, QObject::tr("EnvelopePrc4"));
	list.insert(QPageSize::EnvelopePrc5, QObject::tr("EnvelopePrc5"));
	list.insert(QPageSize::EnvelopePrc6, QObject::tr("EnvelopePrc6"));
	list.insert(QPageSize::EnvelopePrc7, QObject::tr("EnvelopePrc7"));
	list.insert(QPageSize::EnvelopePrc8, QObject::tr("EnvelopePrc8"));
	list.insert(QPageSize::EnvelopePrc9, QObject::tr("EnvelopePrc9"));
	list.insert(QPageSize::EnvelopePrc10, QObject::tr("EnvelopePrc10"));
	list.insert(QPageSize::EnvelopeYou4, QObject::tr("EnvelopeYou4"));

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
