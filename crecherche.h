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
	void				setID(const qint32& iID);
	/*!
	 \brief

	 \fn id
	 \return qint32
	*/
	qint32				id();

	/*!
	 \brief

	 \fn setName
	 \param szName
	*/
	void				setName(const QString& szName);
	/*!
	 \brief

	 \fn name
	 \return QString
	*/
	QString				name();

	/*!
	 \brief

	 \fn setLink
	 \param szLink
	*/
	void				setLink(const QString& szLink);
	/*!
	 \brief

	 \fn link
	 \return QString
	*/
	QString				link();

	/*!
	 \brief

	 \fn setDescription
	 \param lpDescription
	*/
	void				setDescription(cTextDocument* lpDescription);
	/*!
	 \brief

	 \fn description
	 \return cTextDocument
	*/
	cTextDocument*		description();

	/*!
	 \brief

	 \fn addImage
	 \param lpImage
	*/
	void				addImage(cImage* lpImage);
	/*!
	 \brief

	 \fn addCharacter
	 \param lpCharacter
	*/
	void				addCharacter(cCharacter* lpCharacter);
	/*!
	 \brief

	 \fn addObject
	 \param lpObject
	*/
	void				addObject(cObject* lpObject);
	/*!
	 \brief

	 \fn addPlace
	 \param lpPlace
	*/
	void				addPlace(cPlace* lpPlace);

	/*!
	 \brief

	 \fn images
	 \return QList<cImage *>
	*/
	QList<cImage*>		images();
	/*!
	 \brief

	 \fn characterList
	 \return QList<cCharacter *>
	*/
	QList<cCharacter*>	characterList();
	/*!
	 \brief

	 \fn objectList
	 \return QList<cObject *>
	*/
	QList<cObject*>		objectList();
	/*!
	 \brief

	 \fn placeList
	 \return QList<cPlace *>
	*/
	QList<cPlace*>		placeList();

private:
	qint32				m_iID; /*!< TODO: describe */
	QString				m_szName; /*!< TODO: describe */
	QString				m_szLink; /*!< TODO: describe */
	cTextDocument*		m_lpDescription; /*!< TODO: describe */
	QList<cImage*>		m_imageList; /*!< TODO: describe */
	QList<cCharacter*>	m_characterList; /*!< TODO: describe */
	QList<cObject*>		m_objectList; /*!< TODO: describe */
	QList<cPlace*>		m_placeList; /*!< TODO: describe */

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
};

#endif // CRECHERCHE_H
