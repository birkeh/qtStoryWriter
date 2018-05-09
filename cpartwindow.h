#ifndef CPARTWINDOW_H
#define CPARTWINDOW_H


#include "cpart.h"
#include "cchapter.h"

#include "cmdisubwindow.h"
#include "cmainwindow.h"

#include <QWidget>
#include <QStandardItemModel>


namespace Ui {
class cPartWindow;
}

/*!
 \brief

 \class cPartWindow cpartwindow.h "cpartwindow.h"
*/
class cPartWindow : public cMDISubWindow
{
	Q_OBJECT

public:
	/*!
	 \brief

	 \fn cPartWindow
	 \param parent
	*/
	explicit cPartWindow(QWidget *parent = 0);
	/*!
	 \brief

	 \fn ~cPartWindow
	*/
	~cPartWindow();

	/*!
	 \brief

	 \fn setPart
	 \param lpPart
	 \param lpChapterList
	*/
	void					setPart(cPart* lpPart, cChapterList* lpChapterList);
	/*!
	 \brief

	 \fn part
	 \return cPart
	*/
	cPart*					part();

private slots:
	/*!
	 \brief

	 \fn onChapterDoubleClicked
	 \param index
	*/
	void					onChapterDoubleClicked(const QModelIndex& index);

	void					onNameChanged(const QString& szName);
	/*!
	 \brief

	 \fn onDescriptionChanged
	*/
	void					onDescriptionChanged();
	/*!
	 \brief

	 \fn onTextChanged
	*/
	void					onTextChanged();

signals:
	/*!
	 \brief

	 \fn showChapterWindow
	 \param lpChapter
	*/
	void					showChapterWindow(cChapter* lpChapter);

private:
	Ui::cPartWindow*		ui; /*!< TODO: describe */
	cMainWindow*			m_lpMainWindow; /*!< TODO: describe */
	cPart*					m_lpPart; /*!< TODO: describe */
	cChapterList*			m_lpChapterList; /*!< TODO: describe */
	QStandardItemModel*		m_lpChapterModel; /*!< TODO: describe */
};

#endif // CPARTWINDOW_H
