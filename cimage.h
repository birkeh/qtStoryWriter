#ifndef CIMAGE_H
#define CIMAGE_H


#include "ctextdocument.h"

#include <QMetaType>
#include <QList>
#include <QString>
#include <QPixmap>


class cImage : public QObject
{
	Q_OBJECT
public:
	cImage(qint32 iID = -1, QObject* parent = nullptr);

	void			setID(const qint32& iID);
	qint32			id();

	void			setName(const QString& szName);
	QString			name();

	void			setType(const QString& szType);
	QString			type();

	void			setDescription(cTextDocument* lpDescription);
	cTextDocument*	description();

	QPixmap			load();

private:
	qint32			m_iID;
	QString			m_szName;
	QString			m_szType;
	cTextDocument*	m_lpDescription;
};

Q_DECLARE_METATYPE(cImage*)

class cImageList : public QList<cImage*>
{
public:
	bool			load();
	bool			save();

	cImage*			add(const qint32& iID);
	cImage*			find(const qint32& iID);
};

#endif // CIMAGE_H
