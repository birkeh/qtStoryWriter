/*!
 \file crecherche.h

*/

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


/*!
 \brief

 \class cRecherche crecherche.h "crecherche.h"
*/
class cRecherche : public QObject
{
	Q_OBJECT
public:
	/*!
	 \brief

	 \fn cRecherche
	 \param iID
	 \param parent
	*/
	explicit cRecherche(qint32 iID = -1, QObject *parent = nullptr);

	/*!
	 \brief

	 \fn setID
	 \param iID
	*/
	void							setID(const qint32& iID);
	/*!
	 \brief

	 \fn id
	 \return qint32
	*/
	qint32							id();

	/*!
	 \brief

	 \fn setName
	 \param szName
	*/
	void							setName(const QString& szName);
	/*!
	 \brief

	 \fn name
	 \return QString
	*/
	QString							name();

	/*!
	 \brief

	 \fn setLink
	 \param szLink
	*/
	void							setLink(const QString& szLink);
	/*!
	 \brief

	 \fn link
	 \return QString
	*/
	QString							link();

	/*!
	 \brief

	 \fn setDescription
	 \param lpDescription
	*/
	void							setDescription(cTextDocument* lpDescription);
	/*!
	 \brief

	 \fn description
	 \return cTextDocument
	*/
	cTextDocument*					description();

	/*!
	 \brief

	 \fn addImage
	 \param lpImage
	 \param lpDescription
	*/
	void							addImage(cImage* lpImage, cTextDocument* lpDescription);
	/*!
	 \brief

	 \fn addCharacter
	 \param lpCharacter
	 \param lpDescription
	*/
	void							addCharacter(cCharacter* lpCharacter, cTextDocument* lpDescription);
	/*!
	 \brief

	 \fn addObject
	 \param lpObject
	 \param lpDescription
	*/
	void							addObject(cObject* lpObject, cTextDocument* lpDescription);
	/*!
	 \brief

	 \fn addPlace
	 \param lpPlace
	 \param lpDescription
	*/
	void							addPlace(cPlace* lpPlace, cTextDocument* lpDescription);

	/*!
	 \brief

	 \fn images
	 \return QList<cImageDescription *>
	*/
	QList<cImageDescription*>		images();
	/*!
	 \brief

	 \fn characterList
	 \return QList<cCharacterDescription *>
	*/
	QList<cCharacterDescription*>	characterList();
	/*!
	 \brief

	 \fn objectList
	 \return QList<cObjectDescription *>
	*/
	QList<cObjectDescription*>		objectList();
	/*!
	 \brief

	 \fn placeList
	 \return QList<cPlaceDescription *>
	*/
	QList<cPlaceDescription*>		placeList();

private:
	qint32							m_iID;				/*!< TODO: describe */
	QString							m_szName;			/*!< TODO: describe */
	QString							m_szLink;			/*!< TODO: describe */
	cTextDocument*					m_lpDescription;	/*!< TODO: describe */
	QList<cImageDescription*>		m_imageList;		/*!< TODO: describe */
	QList<cCharacterDescription*>	m_characterList;	/*!< TODO: describe */
	QList<cObjectDescription*>		m_objectList;		/*!< TODO: describe */
	QList<cPlaceDescription*>		m_placeList;		/*!< TODO: describe */

signals:

public slots:
};

Q_DECLARE_METATYPE(cRecherche*)

/*!
 \brief

 \class cRechercheList crecherche.h "crecherche.h"
*/
class cRechercheList : public QList<cRecherche*>
{
public:
	/*!
	 \brief

	 \fn load
	 \param lpImageList
	 \param lpCharacterList
	 \param lpObjectList
	 \param lpPlaceList
	 \return bool
	*/
	bool				load(cImageList* lpImageList, cCharacterList* lpCharacterList, cObjectList* lpObjectList, cPlaceList* lpPlaceList);
	/*!
	 \brief

	 \fn save
	 \return bool
	*/
	bool				save();

	/*!
	 \brief

	 \fn add
	 \param iID
	 \return cRecherche
	*/
	cRecherche*			add(const qint32& iID);
	/*!
	 \brief

	 \fn find
	 \param iID
	 \return cRecherche
	*/
	cRecherche*			find(const qint32& iID);

	/*!
	 \brief

	 \fn find
	 \param lpCharacter
	 \return QList<cCharacter *>
	*/
	QList<cRecherche *> find(cCharacter* lpCharacter);
};

#endif // CRECHERCHE_H
