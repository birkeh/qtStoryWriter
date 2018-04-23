#ifndef COBJECT_H
#define COBJECT_H


#include "ctextdocument.h"

#include <QMetaType>
#include <QList>
#include <QString>
#include <QObject>


class cObject : public QObject
{
	Q_OBJECT
public:
	explicit cObject(qint32 iID = -1, QObject *parent = nullptr);

	void			setID(const qint32& iID);
	qint32			id();

	void			setName(const QString& szName);
	QString			name();

	void			setType(const QString& szType);
	QString			type();

	void			setDescription(cTextDocument* lpDescription);
	cTextDocument*	description();

private:
	qint32			m_iID;
	QString			m_szName;
	QString			m_szType;
	cTextDocument*	m_lpDescription;

signals:

public slots:
};

Q_DECLARE_METATYPE(cObject*)

class cObjectList : public QList<cObject*>
{
public:
	bool			load();
	bool			save();

	cObject*		add(const qint32& iID);
	cObject*		find(const qint32& iID);
};

#endif // COBJECT_H
