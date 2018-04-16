#ifndef CBOOK_H
#define CBOOK_H


#include <QString>
#include <QDate>


class cBook
{
public:
	cBook(const QString& szTitle = "");

	void		setTitle(const QString& szTitle);
	QString		title();

	void		setSubTitle(const QString& szSubTitle);
	QString		subTitle();

	void		setShortDescription(const QString& szShortDescription);
	QString		shortDescription();

	void		setDescription(const QString& szDescription);
	QString		description();

	void		setAuthor(const QString& szAuthor);
	QString		author();

	void		setStartedAt(const QDate& startedAt);
	QDate		startedAt();

	void		setFinishedAt(const QDate& finishedAt);
	QDate		finishedAt();

	void		setTargetDate(const QDate& targetDate);
	QDate		targetDate();
private:
	QString		m_szTitle;
	QString		m_szSubtitle;
	QString		m_szShortDescription;
	QString		m_szDescription;
	QString		m_szAuthor;
	QDate		m_startedAt;
	QDate		m_finishedAt;
	QDate		m_targetDate;
};

#endif // CBOOK_H
