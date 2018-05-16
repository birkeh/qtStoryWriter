/*!
 \file ctextdocument.h

*/

#ifndef CTEXTDOCUMENT_H
#define CTEXTDOCUMENT_H


#include <QObject>
#include <QTextDocument>

QT_BEGIN_NAMESPACE
class QAction;
class QComboBox;
class QFontComboBox;
class QTextEdit;
class QTextCharFormat;
class QMenu;
class QPrinter;
QT_END_NAMESPACE


/*!
 \brief

 \class cTextDocument ctextdocument.h "ctextdocument.h"
*/
class cTextDocument : public QTextDocument
{
public:
	/*!
	 \brief

	 \fn cTextDocument
	 \param parent
	*/
	cTextDocument(QObject *parent = Q_NULLPTR);
	/*!
	 \brief

	 \fn cTextDocument
	 \param text
	 \param parent
	*/
	cTextDocument(const QString &text, QObject *parent = Q_NULLPTR);

	/*!
	 \brief

	 \fn save
	 \return bool
	*/
	bool			save();
	/*!
	 \brief

	 \fn saveAs
	 \param szFileName
	 \return bool
	*/
	bool			saveAs(const QString& szFileName);

	/*!
	 \brief

	 \fn printPreview
	 \param lpPrinter
	*/
	void			printPreview(QPrinter* lpPrinter);
private:
	QString			m_szFileName; /*!< TODO: describe */

	/*!
	 \brief

	 \fn init
	*/
	void			init();
	/*!
	 \brief

	 \fn saveDocument
	 \return bool
	*/
	bool			saveDocument();
private slots:
};

#endif // CTEXTDOCUMENT_H
