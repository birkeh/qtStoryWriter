#ifndef CBOOK_H
#define CBOOK_H


#include "ctextdocument.h"

#include <QMetaType>
#include <QString>
#include <QDateTime>
#include <QObject>


class cBook : public QObject
{
	Q_OBJECT
public:
	explicit cBook(const QString& szTitle = "", QObject *parent = nullptr);

	bool			load();
	bool			save();

	void			setTitle(const QString& szTitle);
	QString			title();

	void			setSubTitle(const QString& szSubTitle);
	QString			subTitle();

	void			setShortDescription(cTextDocument* lpShortDescription);
	cTextDocument*	shortDescription();

	void			setDescription(cTextDocument* lpDescription);
	cTextDocument*	description();

	void			setAuthor(const QString& szAuthor);
	QString			author();

	void			setStartedAt(const QDateTime& startedAt);
	QDateTime		startedAt();

	void			setFinishedAt(const QDateTime& finishedAt);
	QDateTime		finishedAt();

	void			setTargetDate(const QDateTime& targetDate);
	QDateTime		targetDate();
private:
	QString			m_szTitle;
	QString			m_szSubtitle;
	cTextDocument*	m_lpShortDescription;
	cTextDocument*	m_lpDescription;
	QString			m_szAuthor;
	QDateTime		m_startedAt;
	QDateTime		m_finishedAt;
	QDateTime		m_targetDate;
};

Q_DECLARE_METATYPE(cBook*)

#endif // CBOOK_H
