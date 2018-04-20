#include "ccharacter.h"

#include "common.h"

#include <QSqlQuery>
#include <QSqlError>


cCharacter::cCharacter(qint32 iID, QObject *parent) :
	QObject(parent),
	m_id(iID),
	m_bMainCharacter(false),
	m_szCreature(QString("")),
	m_gender(GENDER::GENDER_undefined),
	m_szTitle(QString("")),
	m_szFirstName(QString("")),
	m_szMiddleName(QString("")),
	m_szLastName(QString("")),
	m_szNickName(QString("")),
	m_dHeight(-1),
	m_dWeight(-1),
	m_dAge(-1),
	m_dateOfBirth(QDate(1, 1, 1)),
	m_szPlaceOfBirth(QString("")),
	m_dateOfDeath(QDate(1, 1, 1)),
	m_szPlaceOfDeath(QString("")),
	m_szHairColor(QString("")),
	m_szHairCut(QString("")),
	m_szHairLength(QString("")),
	m_szFigure(QString("")),
	m_szNature(QString("")),
	m_szSpokenLanguages(QString("")),
	m_szSkin(QString("")),
	m_szSchool(QString("")),
	m_szJob(QString("")),
	m_szDescription(QString(""))
{
}

void cCharacter::setID(const qint32& iID)
{
	m_id	= iID;
}

qint32 cCharacter::id()
{
	return(m_id);
}

void cCharacter::setMainCharacter(bool bMainCharacter)
{
	m_bMainCharacter	= bMainCharacter;
}

bool cCharacter::mainCharacter()
{
	return(m_bMainCharacter);
}

void cCharacter::setCreature(const QString& szCreature)
{
	m_szCreature	= szCreature;
}

QString cCharacter::creature()
{
	return(m_szCreature);
}

void cCharacter::setGender(GENDER gender)
{
	m_gender	= gender;
}

cCharacter::GENDER cCharacter::gender()
{
	return(m_gender);
}

void cCharacter::setTitle(const QString& szTitle)
{
	m_szTitle	= szTitle;
}

QString cCharacter::title()
{
	return(m_szTitle);
}

void cCharacter::setFirstName(const QString& szFirstName)
{
	m_szFirstName	= szFirstName;
}

QString cCharacter::firstName()
{
	return(m_szFirstName);
}

void cCharacter::setMiddleName(const QString& szMiddleName)
{
	m_szMiddleName	= szMiddleName;
}

QString cCharacter::middleName()
{
	return(m_szMiddleName);
}

void cCharacter::setLastName(const QString& szLastName)
{
	m_szLastName	= szLastName;
}

QString cCharacter::lastName()
{
	return(m_szLastName);
}

void cCharacter::setNickName(const QString& szNickName)
{
	m_szNickName	= szNickName;
}

QString cCharacter::nickName()
{
	return(m_szNickName);
}

QString cCharacter::name()
{
	QString	szName("");

	if(!m_szFirstName.isEmpty())
		szName.append(m_szFirstName);

	if(!m_szMiddleName.isEmpty())
	{
		if(!szName.isEmpty())
			szName.append(" ");
		szName.append(m_szMiddleName);
	}

	if(!m_szLastName.isEmpty())
	{
		if(!szName.isEmpty())
			szName.append(" ");
		szName.append(m_szLastName);
	}
	return(szName);
}

void cCharacter::setHeight(qreal dHeight)
{
	m_dHeight	= dHeight;
}

qreal cCharacter::height()
{
	return(m_dHeight);
}

void cCharacter::setWeight(qreal dWeight)
{
	m_dWeight	= dWeight;
}

qreal cCharacter::weight()
{
	return(m_dWeight);
}

void cCharacter::setAge(qreal dAge)
{
	m_dAge	= dAge;
}

qreal cCharacter::age()
{
	return(m_dAge);
}

void cCharacter::setDateOfBirth(const QDate& dateOfBirth)
{
	m_dateOfBirth	= dateOfBirth;
}

QDate cCharacter::dateOfBirth()
{
	return(m_dateOfBirth);
}

void cCharacter::setPlaceOfBirth(const QString& szPlaceOfBirth)
{
	m_szPlaceOfBirth	= szPlaceOfBirth;
}

QString cCharacter::placeOfBirth()
{
	return(m_szPlaceOfBirth);
}

void cCharacter::setDateOfDeath(const QDate& dateOfDeath)
{
	m_dateOfDeath	= dateOfDeath;
}

QDate cCharacter::dateOfDeath()
{
	return(m_dateOfDeath);
}

void cCharacter::setPlaceOfDeath(const QString& szPlaceOfDeath)
{
	m_szPlaceOfDeath	= szPlaceOfDeath;
}

QString cCharacter::placeOfDeath()
{
	return(m_szPlaceOfDeath);
}

void cCharacter::setHairColor(const QString& szHairColor)
{
	m_szHairColor	= szHairColor;
}

QString cCharacter::hairColor()
{
	return(m_szHairColor);
}

void cCharacter::setHairCut(const QString& szHairCut)
{
	m_szHairCut	= szHairCut;
}

QString cCharacter::hairCut()
{
	return(m_szHairCut);
}

void cCharacter::setHairLength(const QString& szHairLength)
{
	m_szHairLength	= szHairLength;
}

QString cCharacter::hairLength()
{
	return(m_szHairLength);
}

void cCharacter::setFigure(const QString& szFigure)
{
	m_szFigure	= szFigure;
}

QString cCharacter::figure()
{
	return(m_szFigure);
}

void cCharacter::setNature(const QString& szNature)
{
	m_szNature	= szNature;
}

QString cCharacter::nature()
{
	return(m_szNature);
}

void cCharacter::setSpokenLanguages(const QString& szSpokenLanguages)
{
	m_szSpokenLanguages	= szSpokenLanguages;
}

QString cCharacter::spokenLanguages()
{
	return(m_szSpokenLanguages);
}

void cCharacter::setSkin(const QString& szSkin)
{
	m_szSkin	= szSkin;
}

QString cCharacter::skin()
{
	return(m_szSkin);
}

void cCharacter::setSchool(const QString& szSchool)
{
	m_szSchool	= szSchool;
}

QString	 cCharacter::school()
{
	return(m_szSchool);
}

void cCharacter::setJob(const QString& szJob)
{
	m_szJob	= szJob;
}

QString cCharacter::job()
{
	return(m_szJob);
}

void cCharacter::setDescription(const QString& szDescription)
{
	m_szDescription	= szDescription;
}

QString cCharacter::description()
{
	return(m_szDescription);
}

cCharacter* cCharacterList::add(const qint32& iID)
{
	cCharacter*	lpCharacter	= find(iID);

	if(!lpCharacter)
	{
		lpCharacter	= new cCharacter(iID);
		append(lpCharacter);
	}

	return(lpCharacter);
}

cCharacter* cCharacterList::find(const qint32& iID)
{
	for(int x = 0;x < count();x++)
	{
		if(at(x)->id() == iID)
			return(at(x));
	}

	return(0);
}

bool cCharacterList::load()
{
	QSqlQuery	query;

	query.prepare("SELECT id, mainCharacter, gender, title, firstName, middleName, lastName, height, weight, dateOfBirth, placeOfBirth, dateOfDeath, placeOfDeath, hairColor, hairCut, hairLength, figure, nature, spokenLanguages, skin, school, job, description FROM character ORDER BY mainCharacter DESC, lastName, middleName, firstName;");
	if(!query.exec())
	{
		myDebug << query.lastError().text();
		return(false);
	}

	while(query.next())
	{
		cCharacter*	lpCharacter	= add(query.value("id").toInt());

		lpCharacter->setMainCharacter(query.value("mainCharacter").toBool());
		lpCharacter->setGender((cCharacter::GENDER)query.value("gender").toInt());
		lpCharacter->setTitle(query.value("title").toString());
		lpCharacter->setFirstName(query.value("firstName").toString());
		lpCharacter->setMiddleName(query.value("middleName").toString());
		lpCharacter->setLastName(query.value("lastName").toString());
		lpCharacter->setHeight(query.value("height").toDouble());
		lpCharacter->setWeight(query.value("weight").toDouble());
		lpCharacter->setDateOfBirth(query.value("dateOfBirth").toDate());
		lpCharacter->setPlaceOfBirth(query.value("placeOfBirth").toString());
		lpCharacter->setDateOfDeath(query.value("dateOfDeath").toDate());
		lpCharacter->setPlaceOfDeath(query.value("placeOfBirth").toString());
		lpCharacter->setHairColor(query.value("hairColor").toString());
		lpCharacter->setHairCut(query.value("hairCut").toString());
		lpCharacter->setHairLength(query.value("hairLength").toString());
		lpCharacter->setFigure(query.value("figure").toString());
		lpCharacter->setNature(query.value("nature").toString());
		lpCharacter->setSpokenLanguages(query.value("spokenLanguages").toString());
		lpCharacter->setSkin(query.value("skin").toString());
		lpCharacter->setSchool(query.value("school").toString());
		lpCharacter->setJob(query.value("job").toString());
		lpCharacter->setDescription(query.value("description").toString());
	}

	return(true);
}

bool cCharacterList::save()
{
	return(true);
}
