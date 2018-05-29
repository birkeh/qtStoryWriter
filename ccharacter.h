/*!
 \file ccharacter.h

*/

#ifndef CCHARACTER_H
#define CCHARACTER_H


#include "ctextdocument.h"
#include "cimage.h"

#include <QMetaType>
#include <QList>
#include <QString>
#include <QDateTime>
#include <QColor>
#include <QObject>

#include <QStandardItem>


/*!
 \brief

 \class cCharacter ccharacter.h "ccharacter.h"
*/
class cCharacter : public QObject
{
	Q_OBJECT
public:
	/*!
	 \brief

	 \enum GENDER
	*/
	enum GENDER
	{
		GENDER_undefined	= 0, /*!< TODO: describe */
		GENDER_male			= 1, /*!< TODO: describe */
		GENDER_female		= 2, /*!< TODO: describe */
	};

	/*!
	 \brief

	 \fn cCharacter
	 \param iID
	 \param parent
	*/
	explicit cCharacter(qint32 iID = -1, QObject *parent = nullptr);

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

	 \fn setMainCharacter
	 \param bMainCharacter
	*/
	void							setMainCharacter(bool bMainCharacter);
	/*!
	 \brief

	 \fn mainCharacter
	 \return bool
	*/
	bool							mainCharacter();

	/*!
	 \brief

	 \fn setCreature
	 \param szCreature
	*/
	void							setCreature(const QString& szCreature);
	/*!
	 \brief

	 \fn creature
	 \return QString
	*/
	QString							creature();

	/*!
	 \brief

	 \fn setGender
	 \param gender
	*/
	void							setGender(GENDER gender);
	/*!
	 \brief

	 \fn gender
	 \return GENDER
	*/
	GENDER							gender();
	/*!
	 \brief

	 \fn genderText
	 \return QString
	*/
	QString							genderText();
	/*!
	 \brief

	 \fn genderText
	 \param gender
	 \return QString
	*/
	QString							genderText(GENDER gender) const;

	/*!
	 \brief

	 \fn setTitle
	 \param szTitle
	*/
	void							setTitle(const QString& szTitle);
	/*!
	 \brief

	 \fn title
	 \return QString
	*/
	QString							title();

	/*!
	 \brief

	 \fn setFirstName
	 \param szFirstName
	*/
	void							setFirstName(const QString& szFirstName);
	/*!
	 \brief

	 \fn firstName
	 \return QString
	*/
	QString							firstName();

	/*!
	 \brief

	 \fn setMiddleName
	 \param szMiddleName
	*/
	void							setMiddleName(const QString& szMiddleName);
	/*!
	 \brief

	 \fn middleName
	 \return QString
	*/
	QString							middleName();

	/*!
	 \brief

	 \fn setLastName
	 \param szLastName
	*/
	void							setLastName(const QString& szLastName);
	/*!
	 \brief

	 \fn lastName
	 \return QString
	*/
	QString							lastName();

	/*!
	 \brief

	 \fn name
	 \return QString
	*/
	QString							name();

	/*!
	 \brief

	 \fn setNickName
	 \param szNickName
	*/
	void							setNickName(const QString& szNickName);
	/*!
	 \brief

	 \fn nickName
	 \return QString
	*/
	QString							nickName();

	/*!
	 \brief

	 \fn setHeight
	 \param dHeight
	*/
	void							setHeight(qreal dHeight);
	/*!
	 \brief

	 \fn height
	 \return qreal
	*/
	qreal							height();

	/*!
	 \brief

	 \fn setWeight
	 \param dWeight
	*/
	void							setWeight(qreal dWeight);
	/*!
	 \brief

	 \fn weight
	 \return qreal
	*/
	qreal							weight();

	/*!
	 \brief

	 \fn setAge
	 \param dAge
	*/
	void							setAge(qreal dAge);
	/*!
	 \brief

	 \fn age
	 \return qreal
	*/
	qreal							age();

	/*!
	 \brief

	 \fn setDateOfBirth
	 \param dateOfBirth
	*/
	void							setDateOfBirth(const QDate& dateOfBirth);
	/*!
	 \brief

	 \fn dateOfBirth
	 \return QDate
	*/
	QDate							dateOfBirth();

	/*!
	 \brief

	 \fn setPlaceOfBirth
	 \param szPlaceOfBirth
	*/
	void							setPlaceOfBirth(const QString& szPlaceOfBirth);
	/*!
	 \brief

	 \fn placeOfBirth
	 \return QString
	*/
	QString							placeOfBirth();

	/*!
	 \brief

	 \fn setDateOfDeath
	 \param dateOfDeath
	*/
	void							setDateOfDeath(const QDate& dateOfDeath);
	/*!
	 \brief

	 \fn dateOfDeath
	 \return QDate
	*/
	QDate							dateOfDeath();

	/*!
	 \brief

	 \fn setPlaceOfDeath
	 \param szPlaceOfDeath
	*/
	void							setPlaceOfDeath(const QString& szPlaceOfDeath);
	/*!
	 \brief

	 \fn placeOfDeath
	 \return QString
	*/
	QString							placeOfDeath();

	/*!
	 \brief

	 \fn setHairColor
	 \param szHairColor
	*/
	void							setHairColor(const QString& szHairColor);
	/*!
	 \brief

	 \fn hairColor
	 \return QString
	*/
	QString							hairColor();

	/*!
	 \brief

	 \fn setHairCut
	 \param szHairCut
	*/
	void							setHairCut(const QString& szHairCut);
	/*!
	 \brief

	 \fn hairCut
	 \return QString
	*/
	QString							hairCut();

	/*!
	 \brief

	 \fn setHairLength
	 \param szHairLength
	*/
	void							setHairLength(const QString& szHairLength);
	/*!
	 \brief

	 \fn hairLength
	 \return QString
	*/
	QString							hairLength();

	/*!
	 \brief

	 \fn setFigure
	 \param szFigure
	*/
	void							setFigure(const QString& szFigure);
	/*!
	 \brief

	 \fn figure
	 \return QString
	*/
	QString							figure();

	/*!
	 \brief

	 \fn setNature
	 \param szNature
	*/
	void							setNature(const QString& szNature);
	/*!
	 \brief

	 \fn nature
	 \return QString
	*/
	QString							nature();

	/*!
	 \brief

	 \fn setSpokenLanguages
	 \param szSpokenLanguages
	*/
	void							setSpokenLanguages(const QString& szSpokenLanguages);
	/*!
	 \brief

	 \fn spokenLanguages
	 \return QString
	*/
	QString							spokenLanguages();

	/*!
	 \brief

	 \fn setSkin
	 \param szSkin
	*/
	void							setSkin(const QString& szSkin);
	/*!
	 \brief

	 \fn skin
	 \return QString
	*/
	QString							skin();

	/*!
	 \brief

	 \fn setSchool
	 \param szSchool
	*/
	void							setSchool(const QString& szSchool);
	/*!
	 \brief

	 \fn school
	 \return QString
	*/
	QString							school();

	/*!
	 \brief

	 \fn setJob
	 \param szJob
	*/
	void							setJob(const QString& szJob);
	/*!
	 \brief

	 \fn job
	 \return QString
	*/
	QString							job();

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
	*/
	void							addImage(cImage* lpImage, cTextDocument* lpDescription);
	/*!
	 \brief

	 \fn images
	 \return QList<cImage *>
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
	qint32							m_id;					/*!< TODO: describe */
	bool							m_bMainCharacter;		/*!< TODO: describe */
	QString							m_szCreature;			/*!< TODO: describe */
	GENDER							m_gender;				/*!< TODO: describe */
	QString							m_szTitle;				/*!< TODO: describe */
	QString							m_szFirstName;			/*!< TODO: describe */
	QString							m_szMiddleName;			/*!< TODO: describe */
	QString							m_szLastName;			/*!< TODO: describe */
	QString							m_szNickName;			/*!< TODO: describe */
	qreal							m_dHeight;				/*!< TODO: describe */
	qreal							m_dWeight;				/*!< TODO: describe */
	qreal							m_dAge;					/*!< TODO: describe */
	QDate							m_dateOfBirth;			/*!< TODO: describe */
	QString							m_szPlaceOfBirth;		/*!< TODO: describe */
	QDate							m_dateOfDeath;			/*!< TODO: describe */
	QString							m_szPlaceOfDeath;		/*!< TODO: describe */
	QString							m_szHairColor;			/*!< TODO: describe */
	QString							m_szHairCut;			/*!< TODO: describe */
	QString							m_szHairLength;			/*!< TODO: describe */
	QString							m_szFigure;				/*!< TODO: describe */
	QString							m_szNature;				/*!< TODO: describe */
	QString							m_szSpokenLanguages;	/*!< TODO: describe */
	QString							m_szSkin;				/*!< TODO: describe */
	QString							m_szSchool;				/*!< TODO: describe */
	QString							m_szJob;				/*!< TODO: describe */
	cTextDocument*					m_lpDescription;		/*!< TODO: describe */
	QList<cImageDescription*>		m_imageList;			/*!< TODO: describe */
	QList<QStandardItem*>			m_itemList;				/*!< TODO: describe */
	bool							m_bDeleted;				/*!< TODO: describe */
signals:

public slots:
};

/*!
 \brief

 \class cCharacterDescription ccharacter.h "ccharacter.h"
*/
class cCharacterDescription : public QObject
{
	Q_OBJECT
public:
	cCharacterDescription(cCharacter* lpCharacter, cTextDocument* lpDescription, QObject* parent = nullptr);

	/*!
	 \brief

	 \fn setCharacter
	 \param lpCharacter
	*/
	void			setCharacter(cCharacter* lpCharacter);
	/*!
	 \brief

	 \fn character
	 \return cCharacter
	*/
	cCharacter*		character();

	/*!
	 \brief

	 \fn setDescription
	 \param lpDescription
	*/
	void			setDescription(cTextDocument* lpDescription);
	/*!
	 \brief

	 \fn description
	 \return cTextDocument
	*/
	cTextDocument*	description();
private:
	cCharacter*		m_lpCharacter;		/*!< TODO: describe */
	cTextDocument*	m_lpDescription;	/*!< TODO: describe */
};

Q_DECLARE_METATYPE(cCharacter*)

/*!
 \brief

 \class cCharacterList ccharacter.h "ccharacter.h"
*/
class cCharacterList : public QList<cCharacter*>
{
public:
	/*!
	 \brief

	 \fn load
	 \param lpImageList
	 \return bool
	*/
	bool			load(cImageList* lpImageList);
	/*!
	 \brief

	 \fn save
	 \return bool
	*/
	bool			save();

	/*!
	 \brief

	 \fn add
	 \param iID
	 \return cCharacter
	*/
	cCharacter*		add(const qint32& iID);
	/*!
	 \brief

	 \fn find
	 \param iID
	 \return cCharacter
	*/
	cCharacter*		find(const qint32& iID);
};

#endif // CCHARACTER_H
