#include "ctextdocument.h"
#include "cdocumentwriter.h"

#include <QVector>

#include <QTextCursor>
#include <QTextBlock>
#include <QTextBlockFormat>
#include <QTextFormat>
#include <QTextOption>

#include <QAbstractTextDocumentLayout>

#include <QUrl>

#include <QFile>
#include <QByteArray>
#include <QTextCodec>
#include <QList>
#include <QSizeF>

#include <QDebug>


#if defined(QT_PRINTSUPPORT_LIB)
	#include <QtPrintSupport/qtprintsupportglobal.h>
	#if QT_CONFIG(printer)
		#if QT_CONFIG(printdialog)
			#include <QPrintDialog>
		#endif
		#include <QPrinter>
		#if QT_CONFIG(printpreviewdialog)
			#include <QPrintPreviewDialog>
		#endif
	#endif
#endif


cTextDocument::cTextDocument(QObject *parent) :
	QTextDocument(parent)
{
	init();
}

cTextDocument::cTextDocument(const QString &text, QObject *parent) :
	QTextDocument(text, parent),
	m_szFileName(QString())
{
	init();
}

void cTextDocument::init()
{
	setPageSize((QSizeF(210, 297)));
/*
	QTextCursor* myCursor = new QTextCursor(this);

	QTextBlockFormat format;
	format.setBackground(Qt::red);
	myCursor->setBlockFormat(format);

	myCursor->insertText("the ");

	format.setBackground(Qt::green);
	myCursor->insertBlock(format);
	myCursor->insertText("fish ");

	format.setBackground(Qt::yellow);
	myCursor->insertBlock(format);
	myCursor->insertText("are ");

	format.setBackground(Qt::red);
	myCursor->insertBlock(format);
	myCursor->insertText("coming!");

	format.setBackground(Qt::green);
	myCursor->insertBlock(format);
	myCursor->insertText(QString("%1 blocks").arg(this->blockCount()));
*/
}

bool cTextDocument::save()
{
	if(!m_szFileName.isEmpty())
		return(saveDocument());
	return(false);
}

bool cTextDocument::saveAs(const QString& szFileName)
{
	m_szFileName	= szFileName;
	return(saveDocument());
}

bool cTextDocument::saveDocument()
{
	cDocumentWriter	docWriter(m_szFileName);
	if(!docWriter.open())
		return(false);

	docWriter.writeDocument(this);

	docWriter.close();
	return(true);
}

void cTextDocument::printPreview(QPrinter* lpPrinter)
{
#ifdef QT_NO_PRINTER
	Q_UNUSED(lpPrinter);
#else
	lpPrinter->setPageSizeMM(QSizeF(210, 297));
	print(lpPrinter);
#endif
}
