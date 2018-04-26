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


class cCharacter : public QObject
{
	Q_OBJECT
public:
	enum GENDER
	{
		GENDER_undefined	= 0,
		GENDER_male			= 1,
		GENDER_female		= 2,
	};

	explicit cCharacter(qint32 iID = -1, QObject *parent = nullptr);

	void			setID(const qint32& iID);
	qint32			id();

	void			setMainCharacter(bool bMainCharacter);
	bool			mainCharacter();

	void			setCreature(const QString& szCreature);
	QString			creature();

	void			setGender(GENDER gender);
	GENDER			gender();
	QString			genderText();
	QString			genderText(GENDER gender) const;

	void			setTitle(const QString& szTitle);
	QString			title();

	void			setFirstName(const QString& szFirstName);
	QString			firstName();

	void			setMiddleName(const QString& szMiddleName);
	QString			middleName();

	void			setLastName(const QString& szLastName);
	QString			lastName();

	QString			name();

	void			setNickName(const QString& szNickName);
	QString			nickName();

	void			setHeight(qreal dHeight);
	qreal			height();

	void			setWeight(qreal dWeight);
	qreal			weight();

	void			setAge(qreal dAge);
	qreal			age();

	void			setDateOfBirth(const QDate& dateOfBirth);
	QDate			dateOfBirth();

	void			setPlaceOfBirth(const QString& szPlaceOfBirth);
	QString			placeOfBirth();

	void			setDateOfDeath(const QDate& dateOfDeath);
	QDate			dateOfDeath();

	void			setPlaceOfDeath(const QString& szPlaceOfDeath);
	QString			placeOfDeath();

	void			setHairColor(const QString& szHairColor);
	QString			hairColor();

	void			setHairCut(const QString& szHairCut);
	QString			hairCut();

	void			setHairLength(const QString& szHairLength);
	QString			hairLength();

	void			setFigure(const QString& szFigure);
	QString			figure();

	void			setNature(const QString& szNature);
	QString			nature();

	void			setSpokenLanguages(const QString& szSpokenLanguages);
	QString			spokenLanguages();

	void			setSkin(const QString& szSkin);
	QString			skin();

	void			setSchool(const QString& szSchool);
	QString			school();

	void			setJob(const QString& szJob);
	QString			job();

	void			setDescription(cTextDocument* lpDescription);
	cTextDocument*	description();

	void			addImage(cImage* lpImage);
	QList<cImage*>	images();
private:
	qint32			m_id;
	bool			m_bMainCharacter;
	QString			m_szCreature;
	GENDER			m_gender;
	QString			m_szTitle;
	QString			m_szFirstName;
	QString			m_szMiddleName;
	QString			m_szLastName;
	QString			m_szNickName;
	qreal			m_dHeight;
	qreal			m_dWeight;
	qreal			m_dAge;
	QDate			m_dateOfBirth;
	QString			m_szPlaceOfBirth;
	QDate			m_dateOfDeath;
	QString			m_szPlaceOfDeath;
	QString			m_szHairColor;
	QString			m_szHairCut;
	QString			m_szHairLength;
	QString			m_szFigure;
	QString			m_szNature;
	QString			m_szSpokenLanguages;
	QString			m_szSkin;
	QString			m_szSchool;
	QString			m_szJob;
	cTextDocument*	m_lpDescription;
	QList<cImage*>	m_imageList;
signals:

public slots:
};

Q_DECLARE_METATYPE(cCharacter*)

class cCharacterList : public QList<cCharacter*>
{
public:
	bool			load(cImageList* lpImageList);
	bool			save();

	cCharacter*		add(const qint32& iID);
	cCharacter*		find(const qint32& iID);
};

#endif // CCHARACTER_H
