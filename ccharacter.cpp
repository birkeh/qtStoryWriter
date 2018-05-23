/*!
 \file ccharacter.cpp

*/

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
	m_lpDescription(0),
	m_bDeleted(false)
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

QString cCharacter::genderText()
{
	return(genderText(m_gender));
}

QString cCharacter::genderText(GENDER gender) const
{
	switch(gender)
	{
	case GENDER::GENDER_female:
		return(tr("female"));
	case GENDER::GENDER_male:
		return(tr("male"));
	case GENDER::GENDER_undefined:
		return(tr("undefined"));
	}
	return(tr("undefined"));
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

void cCharacter::setDescription(cTextDocument* lpDescription)
{
	m_lpDescription	= lpDescription;
}

cTextDocument* cCharacter::description()
{
	return(m_lpDescription);
}


void cCharacter::setDeleted(bool bDeleted)
{
	m_bDeleted	= bDeleted;
}

bool cCharacter::deleted()
{
	return(m_bDeleted);
}

void cCharacter::addImage(cImage* lpImage, cTextDocument* lpDescription)
{
	m_imageList.append(new cImageDescription(lpImage, lpDescription));
}

QList<cImageDescription *> cCharacter::images()
{
	return(m_imageList);
}

cCharacterDescription::cCharacterDescription(cCharacter* lpCharacter, cTextDocument* lpDescription, QObject* parent) :
	QObject(parent)
{
	setCharacter(lpCharacter);
	setDescription(lpDescription);
}

void cCharacterDescription::setCharacter(cCharacter* lpCharacter)
{
	m_lpCharacter	= lpCharacter;
}

cCharacter* cCharacterDescription::character()
{
	return(m_lpCharacter);
}

void cCharacterDescription::setDescription(cTextDocument* lpDescription)
{
	m_lpDescription	= lpDescription;
}

cTextDocument* cCharacterDescription::description()
{
	return(m_lpDescription);
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
	if(iID == -1)
		return(0);

	for(int x = 0;x < count();x++)
	{
		if(at(x)->id() == iID)
			return(at(x));
	}

	return(0);
}

bool cCharacterList::load(cImageList *lpImageList)
{
	QSqlQuery	query;

	query.prepare("SELECT id, mainCharacter, creature, gender, title, firstName, middleName, lastName, nickName, height, weight, dateOfBirth, placeOfBirth, dateOfDeath, placeOfDeath, hairColor, hairCut, hairLength, figure, nature, spokenLanguages, skin, school, job, description FROM character ORDER BY mainCharacter DESC, lastName, middleName, firstName;");
	if(!query.exec())
	{
		myDebug << query.lastError().text();
		return(false);
	}

	while(query.next())
	{
		cCharacter*	lpCharacter	= add(query.value("id").toInt());

		lpCharacter->setMainCharacter(query.value("mainCharacter").toBool());
		lpCharacter->setCreature(query.value("creature").toString());
		lpCharacter->setGender((cCharacter::GENDER)query.value("gender").toInt());
		lpCharacter->setTitle(query.value("title").toString());
		lpCharacter->setFirstName(query.value("firstName").toString());
		lpCharacter->setMiddleName(query.value("middleName").toString());
		lpCharacter->setLastName(query.value("lastName").toString());
		lpCharacter->setNickName(query.value("nickName").toString());
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
		lpCharacter->setDescription(blob2TextDocument(query.value("description").toByteArray()));
	}

	query.prepare("SELECT characterID, imageID, description FROM characterImage;");
	if(!query.exec())
	{
		myDebug << query.lastError().text();
		return(false);
	}

	while(query.next())
	{
		cCharacter*	lpCharacter	= find(query.value("characterID").toInt());
		if(lpCharacter)
		{
			cImage*	lpImage		= lpImageList->find(query.value("imageID").toInt());
			if(lpImage)
				lpCharacter->addImage(lpImage, blob2TextDocument(query.value("description").toByteArray()));
		}
	}

	return(true);
}

bool cCharacterList::save()
{
	QSqlQuery	queryUpdate;
	QSqlQuery	queryInsert;
	QSqlQuery	querySelect;
	QSqlQuery	queryDelete;

	queryUpdate.prepare("UPDATE character SET mainCharacter=:mainCharacter, creature=:creature, gender=:gender, title=:title, firstName=:firstName, middleName=:middleName, lastName=:lastName, nickName=:nickName, height=:height, weight=:weight, dateOfBirth=:dateOfBirth, dateOfDeath=:dateOfDeath, placeOfBirth=:placeOfBirth, placeOfDeath=:placeOfDeath, hairColor=:hairColor, hairCut=:hairCut, hairLength=:hairLength, figure=:figure, nature=:nature, spokenLanguages=:spokenLanguages, skin=:skin, school=:school, job=:job, description=:description WHERE id=:id;");
	queryInsert.prepare("INSERT INTO character (mainCharacter, creature, gender, title, firstName, middleName, lastName, nickName, height, weight, dateOfBirth, dateOfDeath, placeOfBirth, placeOfDeath, hairColor, hairCut, hairLength, figure, nature, spokenLanguages, skin, school, job, description) VALUES (:mainCharacter, :creature, :gender, :title, :firstName, :middleName, :lastName, :nickName, :height, :weight,:dateOfBirth, :dateOfDeath, :placeOfBirth, :placeOfDeath, :hairColor, :hairCut, :hairLength, :figure, :nature, :spokenLanguages, :skin, :school, :job, :description);");
	querySelect.prepare("SELECT id FROM character WHERE _rowid_=(SELECT MAX(_rowid_) FROM character);");
	queryDelete.prepare("DELETE FROM character WHERE id=:id;");

	QSqlQuery	imageDelete;
	QSqlQuery	imageAdd;

	imageDelete.prepare("DELETE FROM characterImage WHERE characterID=:characterID;");
	imageAdd.prepare("INSERT INTO characterImage (characterID, imageID, description) VALUES (:characterID, :imageID, :description);");

	for(int x = 0;x < count();x++)
	{
		cCharacter*	lpCharacter	= at(x);

		if(lpCharacter->deleted())
		{
			queryDelete.bindValue(":id", lpCharacter->id());

			if(!queryDelete.exec())
			{
				myDebug << queryDelete.lastError().text();
				return(false);
			}
			this->removeOne(lpCharacter);
		}
		else if(lpCharacter->id() != -1)
		{
			queryUpdate.bindValue(":id", lpCharacter->id());
			queryUpdate.bindValue(":mainCharacter", lpCharacter->mainCharacter());
			queryUpdate.bindValue(":creature", lpCharacter->creature());
			queryUpdate.bindValue(":gender", lpCharacter->gender());
			queryUpdate.bindValue(":title", lpCharacter->title());
			queryUpdate.bindValue(":firstName", lpCharacter->firstName());
			queryUpdate.bindValue(":middleName", lpCharacter->middleName());
			queryUpdate.bindValue(":lastName", lpCharacter->lastName());
			queryUpdate.bindValue(":nickName", lpCharacter->nickName());
			queryUpdate.bindValue(":height", lpCharacter->height());
			queryUpdate.bindValue(":weight", lpCharacter->weight());
			queryUpdate.bindValue(":dateOfBirth", lpCharacter->dateOfBirth());
			queryUpdate.bindValue(":dateOfDeath", lpCharacter->dateOfDeath());
			queryUpdate.bindValue(":placeOfBirth", lpCharacter->placeOfBirth());
			queryUpdate.bindValue(":placeOfDeath", lpCharacter->placeOfDeath());
			queryUpdate.bindValue(":hairColor", lpCharacter->hairColor());
			queryUpdate.bindValue(":hairCut", lpCharacter->hairCut());
			queryUpdate.bindValue(":hairLength", lpCharacter->hairLength());
			queryUpdate.bindValue(":figure", lpCharacter->figure());
			queryUpdate.bindValue(":nature", lpCharacter->nature());
			queryUpdate.bindValue(":spokenLanguages", lpCharacter->spokenLanguages());
			queryUpdate.bindValue(":skin", lpCharacter->skin());
			queryUpdate.bindValue(":school", lpCharacter->school());
			queryUpdate.bindValue(":job", lpCharacter->job());
			queryUpdate.bindValue(":description",  textDocument2Blob(lpCharacter->description()));

			if(!queryUpdate.exec())
			{
				myDebug << queryUpdate.lastError().text();
				return(false);
			}
		}
		else
		{
			queryInsert.bindValue(":mainCharacter", lpCharacter->mainCharacter());
			queryInsert.bindValue(":creature", lpCharacter->creature());
			queryInsert.bindValue(":gender", lpCharacter->gender());
			queryInsert.bindValue(":title", lpCharacter->title());
			queryInsert.bindValue(":firstName", lpCharacter->firstName());
			queryInsert.bindValue(":middleName", lpCharacter->middleName());
			queryInsert.bindValue(":lastName", lpCharacter->lastName());
			queryInsert.bindValue(":nickName", lpCharacter->nickName());
			queryInsert.bindValue(":height", lpCharacter->height());
			queryInsert.bindValue(":weight", lpCharacter->weight());
			queryInsert.bindValue(":dateOfBirth", lpCharacter->dateOfBirth());
			queryInsert.bindValue(":dateOfDeath", lpCharacter->dateOfDeath());
			queryInsert.bindValue(":placeOfBirth", lpCharacter->placeOfBirth());
			queryInsert.bindValue(":placeOfDeath", lpCharacter->placeOfDeath());
			queryInsert.bindValue(":hairColor", lpCharacter->hairColor());
			queryInsert.bindValue(":hairCut", lpCharacter->hairCut());
			queryInsert.bindValue(":hairLength", lpCharacter->hairLength());
			queryInsert.bindValue(":figure", lpCharacter->figure());
			queryInsert.bindValue(":nature", lpCharacter->nature());
			queryInsert.bindValue(":spokenLanguages", lpCharacter->spokenLanguages());
			queryInsert.bindValue(":skin", lpCharacter->skin());
			queryInsert.bindValue(":school", lpCharacter->school());
			queryInsert.bindValue(":job", lpCharacter->job());
			queryInsert.bindValue(":description",  textDocument2Blob(lpCharacter->description()));

			if(!queryInsert.exec())
			{
				myDebug << queryInsert.lastError().text();
				return(false);
			}

			if(!querySelect.exec())
			{
				myDebug << querySelect.lastError().text();
				return(false);
			}
			querySelect.next();
			lpCharacter->setID(querySelect.value("id").toInt());
		}

		imageDelete.bindValue(":characterID", lpCharacter->id());
		if(!imageDelete.exec())
		{
			myDebug << imageDelete.lastError().text();
			return(false);
		}

		QList<cImageDescription*>	images	= lpCharacter->images();

		for(int x = 0;x < images.count();x++)
		{
			cImageDescription*	lpImage	= images.at(x);

			imageAdd.bindValue(":characterID", lpCharacter->id());
			imageAdd.bindValue(":imageID", lpImage->image()->id());
			imageAdd.bindValue(":description", textDocument2Blob(lpImage->description()));
			if(!imageAdd.exec())
			{
				myDebug << imageAdd.lastError().text();
				return(false);
			}
		}
	}

	return(true);
}
