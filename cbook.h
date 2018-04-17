#ifndef CBOOK_H
#define CBOOK_H


#include <QString>
#include <QDateTime>


class cBook
{
public:
	cBook(const QString& szTitle = "");

	bool		load();
	bool		save();

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

	void		setStartedAt(const QDateTime& startedAt);
	QDateTime	startedAt();

	void		setFinishedAt(const QDateTime& finishedAt);
	QDateTime	finishedAt();

	void		setTargetDate(const QDateTime& targetDate);
	QDateTime	targetDate();
private:
	QString		m_szTitle;
	QString		m_szSubtitle;
	QString		m_szShortDescription;
	QString		m_szDescription;
	QString		m_szAuthor;
	QDateTime	m_startedAt;
	QDateTime	m_finishedAt;
	QDateTime	m_targetDate;
};

#endif // CBOOK_H
