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
 \brief The cStoryBook class provides basic values of a book project.

With the constructor, the title of the book may be set.

	cBook* lpBook = new cBook("My title");

If the database has already been loaded, the book class may be initialized like this:

	cBook* lpBook = new cBook;
	lpBook->load();

This class should always be initialized by cStoryBook.

 \class cBook cbook.h "cbook.h"
*/
class cBook : public QObject
{
	Q_OBJECT
public:
	/*!
	 \brief Creates a new cBook with the given <i>title</i> and <i>parent</i> to hold basic book project values. Use load() to load the values from the database.

	 \fn cBook
	 \param szTitle title of the book
	 \param parent parent object
	*/
	explicit cBook(const QString& szTitle = "", QObject *parent = nullptr);

	/*!
	 \brief Load the main book values from the database.

	 \fn load
	 \return true on success, otherwise false
	*/
	bool			load();
	/*!
	 \brief Save the main book values to the database.

	 \fn save
	 \return true on success, otherwise false
	*/
	bool			save();

	/*!
	 \brief Set the title of the book.

	 \fn setTitle
	 \param szTitle Title of the book
	*/
	void			setTitle(const QString& szTitle);
	/*!
	 \brief Return the title of the book.

	 \fn title
	 \return title of the book
	*/
	QString			title();

	/*!
	 \brief Set the subtitle of the book.

	 \fn setSubTitle
	 \param szSubTitle subtitle of the book
	*/
	void			setSubTitle(const QString& szSubTitle);
	/*!
	 \brief Return the subtitle of the book.

	 \fn subTitle
	 \return subtitle of the book
	*/
	QString			subTitle();

	/*!
	 \brief Set the short description of the book. The text may be formatted.

	 \fn setShortDescription
	 \param lpShortDescription pointer to a cTextDocument containing the short description
	*/
	void			setShortDescription(cTextDocument* lpShortDescription);
	/*!
	 \brief Return the short description of the book.

	 \fn shortDescription
	 \return short description of the book as a cTextDocument
	*/
	cTextDocument*	shortDescription();

	/*!
	 \brief Set the description of the book. The text may be formatted.

	 \fn setDescription
	 \param lpDescription pointer to a cTextDocument containing the description
	*/
	void			setDescription(cTextDocument* lpDescription);
	/*!
	 \brief Return the description of the book.

	 \fn description
	 \return description of the book as a cTextDocument
	*/
	cTextDocument*	description();

	/*!
	 \brief Set the author of the book.

	 \fn setAuthor
	 \param name of the author
	*/
	void			setAuthor(const QString& szAuthor);
	/*!
	 \brief Return the author of the book.

	 \fn author
	 \return name of the author
	*/
	QString			author();

	/*!
	 \brief Set the date and time when the document has been started.

	 \fn setStartedAt
	 \param date and time when the document has been started
	*/
	void			setStartedAt(const QDateTime& startedAt);
	/*!
	 \brief Return the date and time when the document has been started.

	 \fn startedAt
	 \return date and time when the document has been started
	*/
	QDateTime		startedAt();

	/*!
	 \brief Set the date and time when the document has been finished.

	 \fn setFinishedAt
	 \param date and time when the document has been finished
	*/
	void			setFinishedAt(const QDateTime& finishedAt);
	/*!
	 \brief Return the date and time when the document has been finished.

	 \fn finishedAt
	 \return date and time when the document has been finished
	*/
	QDateTime		finishedAt();

	/*!
	 \brief Set the date and time when the document should be finished.

	 \fn setTargetDate
	 \param date and time when the document should be finished
	*/
	void			setTargetDate(const QDateTime& targetDate);
	/*!
	 \brief Return the date and time when the document should be finished.

	 \fn targetDate
	 \return date and time when the document should be finished
	*/
	QDateTime		targetDate();
private:
	QString			m_szTitle;				/*!< This property holds the title of the document.<br>The default value is empty. <br><b>Access functions:</b><br><table><tr><td>QString</td><td><b>title</b>()</td></tr><tr><td>void</td><td><b>setTitle</b>(const QString& szTitle)</td></tr></table> */
	QString			m_szSubtitle;			/*!< subtitle of the document */
	cTextDocument*	m_lpShortDescription;	/*!< short description of the document. The text may be formatted */
	cTextDocument*	m_lpDescription;		/*!< description of the document. The text may be formatted */
	QString			m_szAuthor;				/*!< name of the author of the document */
	QDateTime		m_startedAt;			/*!< date and time when the document has been startd */
	QDateTime		m_finishedAt;			/*!< date and time when the document has been finished */
	QDateTime		m_targetDate;			/*!< date and time when the document should be finished */
};

Q_DECLARE_METATYPE(cBook*)

#endif // CBOOK_H
