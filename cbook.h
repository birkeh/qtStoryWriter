/*!
 \file cbook.h

*/

#ifndef CBOOK_H
#define CBOOK_H


#include "ctextdocument.h"

#include <QMetaType>
#include <QString>
#include <QDateTime>
#include <QObject>


/*!
 \brief

 \class cBook cbook.h "cbook.h"
*/
class cBook : public QObject
{
	Q_OBJECT
public:
	/*!
	 \brief constructor of cBook

	 \fn cBook
	 \param szTitle title of the book
	 \param parent parent object
	*/
	explicit cBook(const QString& szTitle = "", QObject *parent = nullptr);

	/*!
	 \brief

	 \fn load
	 \return bool
	*/
	bool			load();
	/*!
	 \brief

	 \fn save
	 \return bool
	*/
	bool			save();

	/*!
	 \brief

	 \fn setTitle
	 \param szTitle
	*/
	void			setTitle(const QString& szTitle);
	/*!
	 \brief

	 \fn title
	 \return QString
	*/
	QString			title();

	/*!
	 \brief

	 \fn setSubTitle
	 \param szSubTitle
	*/
	void			setSubTitle(const QString& szSubTitle);
	/*!
	 \brief

	 \fn subTitle
	 \return QString
	*/
	QString			subTitle();

	/*!
	 \brief

	 \fn setShortDescription
	 \param lpShortDescription
	*/
	void			setShortDescription(cTextDocument* lpShortDescription);
	/*!
	 \brief

	 \fn shortDescription
	 \return cTextDocument
	*/
	cTextDocument*	shortDescription();

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

	/*!
	 \brief

	 \fn setAuthor
	 \param szAuthor
	*/
	void			setAuthor(const QString& szAuthor);
	/*!
	 \brief

	 \fn author
	 \return QString
	*/
	QString			author();

	/*!
	 \brief

	 \fn setStartedAt
	 \param startedAt
	*/
	void			setStartedAt(const QDateTime& startedAt);
	/*!
	 \brief

	 \fn startedAt
	 \return QDateTime
	*/
	QDateTime		startedAt();

	/*!
	 \brief

	 \fn setFinishedAt
	 \param finishedAt
	*/
	void			setFinishedAt(const QDateTime& finishedAt);
	/*!
	 \brief

	 \fn finishedAt
	 \return QDateTime
	*/
	QDateTime		finishedAt();

	/*!
	 \brief

	 \fn setTargetDate
	 \param targetDate
	*/
	void			setTargetDate(const QDateTime& targetDate);
	/*!
	 \brief

	 \fn targetDate
	 \return QDateTime
	*/
	QDateTime		targetDate();
private:
	QString			m_szTitle; /*!< TODO: describe */
	QString			m_szSubtitle; /*!< TODO: describe */
	cTextDocument*	m_lpShortDescription; /*!< TODO: describe */
	cTextDocument*	m_lpDescription; /*!< TODO: describe */
	QString			m_szAuthor; /*!< TODO: describe */
	QDateTime		m_startedAt; /*!< TODO: describe */
	QDateTime		m_finishedAt; /*!< TODO: describe */
	QDateTime		m_targetDate; /*!< TODO: describe */
};

Q_DECLARE_METATYPE(cBook*)

#endif // CBOOK_H
