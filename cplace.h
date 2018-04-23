#ifndef CPLACE_H
#define CPLACE_H


#include "ctextdocument.h"

#include <QMetaType>
#include <QList>
#include <QString>
#include <QObject>


class cPlace : public QObject
{
	Q_OBJECT
public:
	explicit cPlace(qint32 iID = -1, QObject *parent = nullptr);

	void			setID(const qint32& iID);
	qint32			id();

	void			setName(const QString& szName);
	QString			name();

	void			setLocation(const QString& szLocation);
	QString			location();

	void			setType(const QString& szType);
	QString			type();

	void			setDescription(cTextDocument* lpDescription);
	cTextDocument*	description();

private:
	qint32			m_iID;
	QString			m_szName;
	QString			m_szLocation;
	QString			m_szType;
	cTextDocument*	m_lpDescription;

signals:

public slots:
};

Q_DECLARE_METATYPE(cPlace*)

class cPlaceList : public QList<cPlace*>
{
public:
	bool			load();
	bool			save();

	cPlace*			add(const qint32& iID);
	cPlace*			find(const qint32& iID);
};

#endif // CPLACE_H
