#include "common.h"

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

cTextDocument*	blob2TextDocument(const QByteArray& ba)
{
	cTextDocument*	lpTextDocument	= new cTextDocument;
	if(ba.isEmpty())
		return(lpTextDocument);

	lpTextDocument->setHtml(uncompressText(ba));
	return(lpTextDocument);
}
