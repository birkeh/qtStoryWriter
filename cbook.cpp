#include "cbook.h"
#include "common.h"

#include <QSqlQuery>
#include <QSqlError>

#include <QString>
#include <QVariant>


cBook::cBook(const QString &szTitle, QObject *parent) :
	QObject(parent),
	m_szTitle(szTitle),
	m_szSubtitle(""),
	m_szShortDescription(""),
	m_szDescription(""),
	m_szAuthor(""),
	m_startedAt(QDateTime(QDate(1, 1, 1))),
	m_finishedAt(QDateTime(QDate(1, 1, 1))),
	m_targetDate(QDateTime(QDate(1, 1, 1)))
{
}

bool cBook::load()
{
	QSqlQuery	query;

	query.prepare("SELECT title, subTitle, shortDescription, description, author, startedAt, finishedAt, targetDate FROM book;");
	if(!query.exec())
	{
		myDebug << query.lastError().text();
		return(false);
	}

	query.first();

	setTitle(query.value("title").toString());
	setSubTitle(query.value("subtitle").toString());
	setShortDescription(query.value("shortDescription").toString());
	setDescription(query.value("description").toString());
	setAuthor(query.value("author").toString());
	setStartedAt(query.value("startedAt").toDateTime());
	setFinishedAt(query.value("finishedAt").toDateTime());
	setTargetDate(query.value("targetDate").toDateTime());

	return(true);
}

bool cBook::save()
{
	QSqlQuery	query;

	query.prepare("SELECT COUNT(1) CNT FROM book;");
	if(!query.exec())
	{
		myDebug << query.lastError().text();
		return(false);
	}

	query.first();

	if(query.value("CNT").toInt() == 1)
		query.prepare("UPDATE book SET title = :title, subTitle = :subTitle, shortDescription = :shortDescription, description = :description, author = :author, startedAt = :startedAt, finishedAt = :finishedAt, targetDate = :targetDate;");
	else
		query.prepare("INSERT INTO book (title, subTitle, shortDesctiption, description, author, startedAt, finishedAt, targetDate) VALUES (:title, :subTitle, :shortDesctiption, :description, :author, :startedAt, :finishedAt, :targetDate);");

	query.bindValue(":title", title());
	query.bindValue(":subTitle", subTitle());
	query.bindValue(":shortDescription", shortDescription());
	query.bindValue(":description", description());
	query.bindValue(":author", author());
	query.bindValue(":startedAt", startedAt());
	query.bindValue(":finishedAt", finishedAt());
	query.bindValue(":targetDate", targetDate());

	if(!query.exec())
	{
		myDebug << query.lastError().text();
		return(false);
	}

	return(true);
}

void cBook::setTitle(const QString& szTitle)
{
	m_szTitle	= szTitle;
}

QString cBook::title()
{
	return(m_szTitle);
}

void cBook::setSubTitle(const QString& szSubTitle)
{
	m_szSubtitle	= szSubTitle;
}

QString cBook::subTitle()
{
	return(m_szSubtitle);
}

void cBook::setShortDescription(const QString& szShortDescription)
{
	m_szShortDescription	= szShortDescription;
}

QString cBook::shortDescription()
{
	return(m_szShortDescription);
}

void cBook::setDescription(const QString& szDescription)
{
	m_szDescription	= szDescription;
}

QString cBook::description()
{
	return(m_szDescription);
}

void cBook::setAuthor(const QString& szAuthor)
{
	m_szAuthor	= szAuthor;
}

QString cBook::author()
{
	return(m_szAuthor);
}

void cBook::setStartedAt(const QDateTime& startedAt)
{
	m_startedAt	= startedAt;
}

QDateTime cBook::startedAt()
{
	return(m_startedAt);
}

void cBook::setFinishedAt(const QDateTime& finishedAt)
{
	m_finishedAt	= finishedAt;

}
QDateTime cBook::finishedAt()
{
	return(m_finishedAt);
}

void cBook::setTargetDate(const QDateTime& targetDate)
{
	m_targetDate	= targetDate;
}

QDateTime cBook::targetDate()
{
	return(m_targetDate);
}
