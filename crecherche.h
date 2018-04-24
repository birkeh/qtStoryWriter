#ifndef CRECHERCHE_H
#define CRECHERCHE_H


#include "ctextdocument.h"
#include "cimage.h"
#include "ccharacter.h"
#include "cobject.h"
#include "cplace.h"

#include <QMetaType>
#include <QList>
#include <QString>
#include <QObject>


class cRecherche : public QObject
{
	Q_OBJECT
public:
	explicit cRecherche(qint32 iID = -1, QObject *parent = nullptr);

	void				setID(const qint32& iID);
	qint32				id();

	void				setName(const QString& szName);
	QString				name();

	void				setLink(const QString& szLink);
	QString				link();

	void				setDescription(cTextDocument* lpDescription);
	cTextDocument*		description();

	void				addImage(cImage* lpImage);
	void				addCharacter(cCharacter* lpCharacter);
	void				addObject(cObject* lpObject);
	void				addPlace(cPlace* lpPlace);

private:
	qint32				m_iID;
	QString				m_szName;
	QString				m_szLink;
	cTextDocument*		m_lpDescription;
	QList<cImage*>		m_imageList;
	QList<cCharacter*>	m_characterList;
	QList<cObject*>		m_objectList;
	QList<cPlace*>		m_placeList;

signals:

public slots:
};

Q_DECLARE_METATYPE(cRecherche*)

class cRechercheList : public QList<cRecherche*>
{
public:
	bool				load(cImageList* lpImageList, cCharacterList* lpCharacterList, cObjectList* lpObjectList, cPlaceList* lpPlaceList);
	bool				save();

	cRecherche*			add(const qint32& iID);
	cRecherche*			find(const qint32& iID);
};

#endif // CRECHERCHE_H
