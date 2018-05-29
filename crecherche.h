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

#include <QStandardItem>


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

	 \fn removeCharacter
	 \param lpCharacter
	*/
	void							removeCharacter(cCharacterDescription* lpCharacter);
	/*!
	 \brief

	 \fn characterList
	 \return QList<cCharacter *>
	*/
	QList<cCharacterDescription*>	characterList();

	/*!
	 \brief

	 \fn addObject
	 \param lpObject
	 \param lpDescription
	*/
	void							addObject(cObject* lpObject, cTextDocument* lpDescription);
	/*!
	 \brief

	 \fn removeObject
	 \param lpObject
	*/
	void							removeObject(cObjectDescription* lpObject);
	/*!
	 \brief

	 \fn objectList
	 \return QList<cObject *>
	*/
	QList<cObjectDescription*>		objectList();

	/*!
	 \brief

	 \fn addPlace
	 \param lpPlace
	 \param lpDescription
	*/
	void							addPlace(cPlace* lpPlace, cTextDocument* lpDescription);
	/*!
	 \brief

	 \fn removePlace
	 \param lpPlace
	*/
	void							removePlace(cPlaceDescription* lpPlace);
	/*!
	 \brief

	 \fn placeList
	 \return QList<cPlace *>
	*/
	QList<cPlaceDescription*>		placeList();

	/*!
	 \brief

	 \fn images
	 \return QList<cImageDescription *>
	*/
	QList<cImageDescription*>		images();

	/*!
	 \brief

	 \fn setItem
	 \param itemList
	*/
	void							setItem(QList<QStandardItem*> itemList);
	/*!
	 \brief

	 \fn item
	 \return QList<QStandardItem*>
	*/
	QList<QStandardItem*>			item();

	/*!
	 \brief

	 \fn setDeleted
	 \param bDeleted
	*/
	void							setDeleted(bool bDeleted);
	/*!
	 \brief

	 \fn deleted
	 \return bool
	*/
	bool							deleted();

private:
	qint32							m_iID;				/*!< TODO: describe */
	QString							m_szName;			/*!< TODO: describe */
	QString							m_szLink;			/*!< TODO: describe */
	cTextDocument*					m_lpDescription;	/*!< TODO: describe */
	QList<cImageDescription*>		m_imageList;		/*!< TODO: describe */
	QList<cCharacterDescription*>	m_characterList;	/*!< TODO: describe */
	QList<cObjectDescription*>		m_objectList;		/*!< TODO: describe */
	QList<cPlaceDescription*>		m_placeList;		/*!< TODO: describe */
	QList<QStandardItem*>			m_itemList;			/*!< TODO: describe */
	bool							m_bDeleted;			/*!< TODO: describe */

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

	/*!
	 \brief

	 \fn find
	 \param lpPlace
	 \return QList<cScene *>
	*/
	QList<cRecherche *>		find(cPlace* lpPlace);

	/*!
	 \brief

	 \fn find
	 \param lpObject
	 \return QList<cScene *>
	*/
	QList<cRecherche *>		find(cObject* lpObject);
};

#endif // CRECHERCHE_H
