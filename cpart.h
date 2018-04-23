#ifndef CPART_H
#define CPART_H


#include "ctextdocument.h"

#include <QMetaType>
#include <QList>
#include <QString>
#include <QObject>


class cPart : public QObject
{
	Q_OBJECT
public:
	explicit cPart(qint32 iID = -1, QObject *parent = nullptr);

	void			setID(const qint32& iID);
	qint32			id();

	void			setName(const QString& szName);
	QString			name();

	void			setSortOrder(const qint32& iSortOrder);
	qint32			sortOrder();

	void			setDescription(cTextDocument* lpDescription);
	cTextDocument*	description();

	void			setText(cTextDocument* lpText);
	cTextDocument*	text();

private:
	qint32			m_iID;
	QString			m_szName;
	qint32			m_iSortOrder;
	cTextDocument*	m_lpDescription;
	cTextDocument*	m_lpText;
};

Q_DECLARE_METATYPE(cPart*)

class cPartList : public QList<cPart*>
{
public:
	bool			load();
	bool			save();

	cPart*			add(const qint32& iID);
	cPart*			find(const qint32& iID);
};

#endif // CPART_H
