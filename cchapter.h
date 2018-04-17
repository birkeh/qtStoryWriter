#ifndef CCHAPTER_H
#define CCHAPTER_H


#include "cpart.h"

#include <QMetaType>
#include <QList>
#include <QString>


class cChapter
{
public:
	cChapter(qint32 iID = -1);

	void			setID(const qint32& iID);
	qint32			id();

	void			setPart(cPart *lpPart);
	cPart*			part();

	void			setName(const QString& szName);
	QString			name();

	void			setSortOrder(const qint32& iSortOrder);
	qint32			sortOrder();

	void			setDescription(const QString& szDescription);
	QString			description();

	void			setFile(const QString& szFile);
	QString			file();

private:
	qint32			m_iID;
	cPart*			m_lpPart;
	QString			m_szName;
	qint32			m_iSortOrder;
	QString			m_szDescription;
	QString			m_szFile;
};

Q_DECLARE_METATYPE(cChapter*)

class cChapterList : public QList<cChapter*>
{
public:
	bool			load(cPartList *lpPartList);
	bool			save();

	cChapter*		add(const qint32& iID);
	cChapter*		find(const qint32& iID);
};

#endif // CCHAPTER_H
