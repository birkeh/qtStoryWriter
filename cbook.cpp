#include "cbook.h"


cBook::cBook(const QString &szTitle) :
	m_szTitle(szTitle),
	m_szSubtitle(""),
	m_szShortDescription(""),
	m_szDescription(""),
	m_szAuthor(""),
	m_startedAt(QDate(1, 1, 1)),
	m_finishedAt(QDate(1, 1, 1)),
	m_targetDate(QDate(1, 1, 1))
{
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

void cBook::setStartedAt(const QDate& startedAt)
{
	m_startedAt	= startedAt;
}

QDate cBook::startedAt()
{
	return(m_startedAt);
}

void cBook::setFinishedAt(const QDate& finishedAt)
{
	m_finishedAt	= finishedAt;

}
QDate cBook::finishedAt()
{
	return(m_finishedAt);
}

void cBook::setTargetDate(const QDate& targetDate)
{
	m_targetDate	= targetDate;
}

QDate cBook::targetDate()
{
	return(m_targetDate);
}
