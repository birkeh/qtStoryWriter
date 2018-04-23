#ifndef CRECHERCHE_H
#define CRECHERCHE_H


#include "ctextdocument.h"

#include <QMetaType>
#include <QList>
#include <QString>
#include <QObject>


class cRecherche : public QObject
{
	Q_OBJECT
public:
	explicit cRecherche(qint32 iID = -1, QObject *parent = nullptr);

	void			setID(const qint32& iID);
	qint32			id();

	void			setName(const QString& szName);
	QString			name();

	void			setLink(const QString& szLink);
	QString			link();

	void			setDescription(cTextDocument* lpDescription);
	cTextDocument*	description();

private:
	qint32			m_iID;
	QString			m_szName;
	QString			m_szLink;
	cTextDocument*	m_lpDescription;

signals:

public slots:
};

Q_DECLARE_METATYPE(cRecherche*)

class cRechercheList : public QList<cRecherche*>
{
public:
	bool			load();
	bool			save();

	cRecherche*		add(const qint32& iID);
	cRecherche*		find(const qint32& iID);
};

#endif // CRECHERCHE_H
