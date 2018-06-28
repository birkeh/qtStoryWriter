#ifndef CPROPERTIESWINDOW_H
#define CPROPERTIESWINDOW_H


#include "cstorybook.h"

#include "cmdisubwindow.h"
#include "cmainwindow.h"


#include <QWidget>


namespace Ui {
class cPropertiesWindow;
}

/*!
 \brief

 \class cPropertiesWindow cpropertieswindow.h "cpropertieswindow.h"
*/
class cPropertiesWindow : public cMDISubWindow
{
	Q_OBJECT

public:
	/*!
	 \brief

	 \fn cPropertiesWindow
	 \param parent
	*/
	explicit cPropertiesWindow(QWidget *parent = 0);
	/*!
	 \brief

	 \fn ~cPropertiesWindow
	*/
	~cPropertiesWindow();

	/*!
	 \brief

	 \fn setBook
	 \param lpBook
	*/
	void					setBook(cStoryBook* lpStoryBook);
	/*!
	 \brief

	 \fn book
	 \return cStoryBook
	*/
	cStoryBook *book();

	/*!
	 \brief

	 \fn retranslateUI
	*/
	void					retranslateUI();

private slots:
	/*!
	 \brief

	 \fn onTitleChanged
	 \param szName
	*/
	void					onTitleChanged(const QString& szName);
	/*!
	 \brief

	 \fn onSubTitleChanged
	 \param szName
	*/
	void					onSubTitleChanged(const QString& szName);
	/*!
	 \brief

	 \fn onAuthorChanged
	 \param szName
	*/
	void					onAuthorChanged(const QString& szName);
	/*!
	 \brief

	 \fn onShortDescriptionChanged
	*/
	void					onShortDescriptionChanged();
	/*!
	 \brief

	 \fn onDescriptionChanged
	*/
	void					onDescriptionChanged();
	/*!
	 \brief

	 \fn onStartedAtChanged
	 \param dateTime
	*/
	void					onStartedAtChanged(const QDateTime& dateTime);
	/*!
	 \brief

	 \fn onFinishedAtChanged
	 \param dateTime
	*/
	void					onFinishedAtChanged(const QDateTime& dateTime);
	/*!
	 \brief

	 \fn onTargetDateChanged
	 \param dateTime
	*/
	void					onTargetDateChanged(const QDateTime& dateTime);

	void					onPrintTitleChanged(bool checked);
	void					onTitleFontChanged(const QString &text);
	void					onTitleFontSizeChanged(const QString &text);
	void					onTitleBoldChanged(bool checked);
	void					onTitleItalicChanged(bool checked);
	void					onTitleUnderlineChanged(bool checked);
	void					onTitleLeftChanged(bool checked);
	void					onTitleCenterChanged(bool checked);
	void					onTitleRightChanged(bool checked);
	void					onPrintSubtitleChanged(bool checked);
	void					onSubtitleFontChanged(const QString &text);
	void					onSubtitleFontSizeChanged(const QString &text);
	void					onSubtitleBoldChanged(bool checked);
	void					onSubtitleItalicChanged(bool checked);
	void					onSubtitleUnderlineChanged(bool checked);
	void					onSubtitleLeftChanged(bool checked);
	void					onSubtitleCenterChanged(bool checked);
	void					onSubtitleRightChanged(bool checked);
	void					onPrintShortDescriptionChanged(bool checked);
	void					onPrintDescriptionChanged(bool checked);
	void					onPrintAuthorChanged(bool checked);
	void					onAuthorFontChanged(const QString &text);
	void					onAuthorFontSizeChanged(const QString &text);
	void					onAuthorBoldChanged(bool checked);
	void					onAuthorItalicChanged(bool checked);
	void					onAuthorUnderlineChanged(bool checked);
	void					onAuthorLeftChanged(bool checked);
	void					onAuthorCenterChanged(bool checked);
	void					onAuthorRightChanged(bool checked);
	void					onPrintPartNameChanged(bool checked);
	void					onPartNameFontChanged(const QString &text);
	void					onPartNameFontSizeChanged(const QString &text);
	void					onPartNameBoldChanged(bool checked);
	void					onPartNameItalicChanged(bool checked);
	void					onPartNameUnderlineChanged(bool checked);
	void					onPartNameLeftChanged(bool checked);
	void					onPartNameCenterChanged(bool checked);
	void					onPartNameRightChanged(bool checked);
	void					onPrintPartDescriptionChanged(bool checked);
	void					onPrintPartTextChanged(bool checked);
	void					onPrintChapterNameChanged(bool checked);
	void					onChapterNameFontChanged(const QString &text);
	void					onChapterNameFontSizeChanged(const QString &text);
	void					onChapterNameBoldChanged(bool checked);
	void					onChapterNameItalicChanged(bool checked);
	void					onChapterNameUnderlineChanged(bool checked);
	void					onChapterNameLeftChanged(bool checked);
	void					onChapterNameCenterChanged(bool checked);
	void					onChapterNameRightChanged(bool checked);
	void					onPrintChapterDescriptionChanged(bool checked);
	void					onPrintChapterTextChanged(bool checked);
	void					onPrintSceneNameChanged(bool checked);
	void					onSceneNameFontChanged(const QString &text);
	void					onSceneNameFontSizeChanged(const QString &text);
	void					onSceneNameBoldChanged(bool checked);
	void					onSceneNameItalicChanged(bool checked);
	void					onSceneNameUnderlineChanged(bool checked);
	void					onSceneNameLeftChanged(bool checked);
	void					onSceneNameCenterChanged(bool checked);
	void					onSceneNameRightChanged(bool checked);
	void					onPrintSceneDescriptionChanged(bool checked);
	void					onPrintSceneTextChanged(bool checked);
	void					onPaperSizeChanged(const QString &text);
	void					onOrientationPortraitChanged(bool checked);
	void					onOrientationLandscapeChanged(bool checked);
	void					onUnitChanged(const QString &text);
	void					onMarginLeftChanged(double d);
	void					onMarginRightChanged(double d);
	void					onMarginTopChanged(double d);
	void					onMarginBottomChanged(double d);

private:
	Ui::cPropertiesWindow*	ui;				/*!< TODO: describe */
	cMainWindow*			m_lpMainWindow;	/*!< TODO: describe */
	cStoryBook*				m_lpStoryBook;	/*!< TODO: describe */

	/*!
	 \brief

	 \fn fillFontSize
	 \param lpComboBox
	*/
	void					fillFontSize(QComboBox* lpComboBox);
};

#endif // CPROPERTIESWINDOW_H
