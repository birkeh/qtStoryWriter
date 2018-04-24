#ifndef CCHAPTER_H
#define CCHAPTER_H


#include "cpart.h"
#include "ctextdocument.h"
				  

#include <QMetaType>
#include <QList>
#include <QString>
#include <QObject>


class cChapter : public QObject
{
	Q_OBJECT
public:
	explicit cChapter(qint32 iID = -1, QObject *parent = nullptr);

	void				setID(const qint32& iID);
	qint32				id();

	void				setPart(cPart *lpPart);
	cPart*				part();

	void				setName(const QString& szName);
	QString				name();

	void				setSortOrder(const qint32& iSortOrder);
	qint32				sortOrder();

	void				setDescription(cTextDocument* lpDescription);
	cTextDocument*		description();

	void				setText(cTextDocument* lpText);
	cTextDocument*		text();

private:
	qint32				m_iID;
	cPart*				m_lpPart;
	QString				m_szName;
	qint32				m_iSortOrder;
	cTextDocument*		m_lpDescription;
	cTextDocument*		m_lpText;
};

Q_DECLARE_METATYPE(cChapter*)

class cChapterList : public QList<cChapter*>
{
public:
	bool				load(cPartList *lpPartList);
	bool				save();

	cChapter*			add(const qint32& iID);
	cChapter*			find(const qint32& iID);

	QList<cChapter*>	find(cPart* lpPart);
};

#endif // CCHAPTER_H
