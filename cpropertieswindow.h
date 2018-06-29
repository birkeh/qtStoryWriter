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
	/*!
	 \brief

	 \fn onTitleFontChanged
	 \param text
	*/
	void					onTitleFontChanged(const QString &text);
	/*!
	 \brief

	 \fn onTitleFontSizeChanged
	 \param text
	*/
	void					onTitleFontSizeChanged(const QString &text);
	/*!
	 \brief

	 \fn onTitleBoldChanged
	 \param checked
	*/
	void					onTitleBoldChanged(bool checked);
	/*!
	 \brief

	 \fn onTitleItalicChanged
	 \param checked
	*/
	void					onTitleItalicChanged(bool checked);
	/*!
	 \brief

	 \fn onTitleUnderlineChanged
	 \param checked
	*/
	void					onTitleUnderlineChanged(bool checked);
	/*!
	 \brief

	 \fn onTitleLeftChanged
	 \param checked
	*/
	void					onTitleLeftChanged(bool checked);
	/*!
	 \brief

	 \fn onTitleCenterChanged
	 \param checked
	*/
	void					onTitleCenterChanged(bool checked);
	/*!
	 \brief

	 \fn onTitleRightChanged
	 \param checked
	*/
	void					onTitleRightChanged(bool checked);
	/*!
	 \brief

	 \fn onPrintSubtitleChanged
	 \param checked
	*/
	void					onPrintSubtitleChanged(bool checked);
	/*!
	 \brief

	 \fn onSubtitleFontChanged
	 \param text
	*/
	void					onSubtitleFontChanged(const QString &text);
	/*!
	 \brief

	 \fn onSubtitleFontSizeChanged
	 \param text
	*/
	void					onSubtitleFontSizeChanged(const QString &text);
	/*!
	 \brief

	 \fn onSubtitleBoldChanged
	 \param checked
	*/
	void					onSubtitleBoldChanged(bool checked);
	/*!
	 \brief

	 \fn onSubtitleItalicChanged
	 \param checked
	*/
	void					onSubtitleItalicChanged(bool checked);
	/*!
	 \brief

	 \fn onSubtitleUnderlineChanged
	 \param checked
	*/
	void					onSubtitleUnderlineChanged(bool checked);
	/*!
	 \brief

	 \fn onSubtitleLeftChanged
	 \param checked
	*/
	void					onSubtitleLeftChanged(bool checked);
	/*!
	 \brief

	 \fn onSubtitleCenterChanged
	 \param checked
	*/
	void					onSubtitleCenterChanged(bool checked);
	/*!
	 \brief

	 \fn onSubtitleRightChanged
	 \param checked
	*/
	void					onSubtitleRightChanged(bool checked);
	/*!
	 \brief

	 \fn onPrintShortDescriptionChanged
	 \param checked
	*/
	void					onPrintShortDescriptionChanged(bool checked);
	/*!
	 \brief

	 \fn onPrintDescriptionChanged
	 \param checked
	*/
	void					onPrintDescriptionChanged(bool checked);
	/*!
	 \brief

	 \fn onPrintAuthorChanged
	 \param checked
	*/
	void					onPrintAuthorChanged(bool checked);
	/*!
	 \brief

	 \fn onAuthorFontChanged
	 \param text
	*/
	void					onAuthorFontChanged(const QString &text);
	/*!
	 \brief

	 \fn onAuthorFontSizeChanged
	 \param text
	*/
	void					onAuthorFontSizeChanged(const QString &text);
	/*!
	 \brief

	 \fn onAuthorBoldChanged
	 \param checked
	*/
	void					onAuthorBoldChanged(bool checked);
	/*!
	 \brief

	 \fn onAuthorItalicChanged
	 \param checked
	*/
	void					onAuthorItalicChanged(bool checked);
	/*!
	 \brief

	 \fn onAuthorUnderlineChanged
	 \param checked
	*/
	void					onAuthorUnderlineChanged(bool checked);
	/*!
	 \brief

	 \fn onAuthorLeftChanged
	 \param checked
	*/
	void					onAuthorLeftChanged(bool checked);
	/*!
	 \brief

	 \fn onAuthorCenterChanged
	 \param checked
	*/
	void					onAuthorCenterChanged(bool checked);
	/*!
	 \brief

	 \fn onAuthorRightChanged
	 \param checked
	*/
	void					onAuthorRightChanged(bool checked);
	/*!
	 \brief

	 \fn onPrintPartNameChanged
	 \param checked
	*/
	void					onPrintPartNameChanged(bool checked);
	/*!
	 \brief

	 \fn onPartNameFontChanged
	 \param text
	*/
	void					onPartNameFontChanged(const QString &text);
	/*!
	 \brief

	 \fn onPartNameFontSizeChanged
	 \param text
	*/
	void					onPartNameFontSizeChanged(const QString &text);
	/*!
	 \brief

	 \fn onPartNameBoldChanged
	 \param checked
	*/
	void					onPartNameBoldChanged(bool checked);
	/*!
	 \brief

	 \fn onPartNameItalicChanged
	 \param checked
	*/
	void					onPartNameItalicChanged(bool checked);
	/*!
	 \brief

	 \fn onPartNameUnderlineChanged
	 \param checked
	*/
	void					onPartNameUnderlineChanged(bool checked);
	/*!
	 \brief

	 \fn onPartNameLeftChanged
	 \param checked
	*/
	void					onPartNameLeftChanged(bool checked);
	/*!
	 \brief

	 \fn onPartNameCenterChanged
	 \param checked
	*/
	void					onPartNameCenterChanged(bool checked);
	/*!
	 \brief

	 \fn onPartNameRightChanged
	 \param checked
	*/
	void					onPartNameRightChanged(bool checked);
	/*!
	 \brief

	 \fn onPrintPartDescriptionChanged
	 \param checked
	*/
	void					onPrintPartDescriptionChanged(bool checked);
	/*!
	 \brief

	 \fn onPrintPartTextChanged
	 \param checked
	*/
	void					onPrintPartTextChanged(bool checked);
	/*!
	 \brief

	 \fn onPrintChapterNameChanged
	 \param checked
	*/
	void					onPrintChapterNameChanged(bool checked);
	/*!
	 \brief

	 \fn onChapterNameFontChanged
	 \param text
	*/
	void					onChapterNameFontChanged(const QString &text);
	/*!
	 \brief

	 \fn onChapterNameFontSizeChanged
	 \param text
	*/
	void					onChapterNameFontSizeChanged(const QString &text);
	/*!
	 \brief

	 \fn onChapterNameBoldChanged
	 \param checked
	*/
	void					onChapterNameBoldChanged(bool checked);
	/*!
	 \brief

	 \fn onChapterNameItalicChanged
	 \param checked
	*/
	void					onChapterNameItalicChanged(bool checked);
	/*!
	 \brief

	 \fn onChapterNameUnderlineChanged
	 \param checked
	*/
	void					onChapterNameUnderlineChanged(bool checked);
	/*!
	 \brief

	 \fn onChapterNameLeftChanged
	 \param checked
	*/
	void					onChapterNameLeftChanged(bool checked);
	/*!
	 \brief

	 \fn onChapterNameCenterChanged
	 \param checked
	*/
	void					onChapterNameCenterChanged(bool checked);
	/*!
	 \brief

	 \fn onChapterNameRightChanged
	 \param checked
	*/
	void					onChapterNameRightChanged(bool checked);
	/*!
	 \brief

	 \fn onPrintChapterDescriptionChanged
	 \param checked
	*/
	void					onPrintChapterDescriptionChanged(bool checked);
	/*!
	 \brief

	 \fn onPrintChapterTextChanged
	 \param checked
	*/
	void					onPrintChapterTextChanged(bool checked);
	/*!
	 \brief

	 \fn onPrintSceneNameChanged
	 \param checked
	*/
	void					onPrintSceneNameChanged(bool checked);
	/*!
	 \brief

	 \fn onSceneNameFontChanged
	 \param text
	*/
	void					onSceneNameFontChanged(const QString &text);
	/*!
	 \brief

	 \fn onSceneNameFontSizeChanged
	 \param text
	*/
	void					onSceneNameFontSizeChanged(const QString &text);
	/*!
	 \brief

	 \fn onSceneNameBoldChanged
	 \param checked
	*/
	void					onSceneNameBoldChanged(bool checked);
	/*!
	 \brief

	 \fn onSceneNameItalicChanged
	 \param checked
	*/
	void					onSceneNameItalicChanged(bool checked);
	/*!
	 \brief

	 \fn onSceneNameUnderlineChanged
	 \param checked
	*/
	void					onSceneNameUnderlineChanged(bool checked);
	/*!
	 \brief

	 \fn onSceneNameLeftChanged
	 \param checked
	*/
	void					onSceneNameLeftChanged(bool checked);
	/*!
	 \brief

	 \fn onSceneNameCenterChanged
	 \param checked
	*/
	void					onSceneNameCenterChanged(bool checked);
	/*!
	 \brief

	 \fn onSceneNameRightChanged
	 \param checked
	*/
	void					onSceneNameRightChanged(bool checked);
	/*!
	 \brief

	 \fn onPrintSceneDescriptionChanged
	 \param checked
	*/
	void					onPrintSceneDescriptionChanged(bool checked);
	/*!
	 \brief

	 \fn onPrintSceneTextChanged
	 \param checked
	*/
	void					onPrintSceneTextChanged(bool checked);
	/*!
	 \brief

	 \fn onPaperSizeChanged
	 \param text
	*/
	void					onPaperSizeChanged(const QString &text);
	/*!
	 \brief

	 \fn onOrientationPortraitChanged
	 \param checked
	*/
	void					onOrientationPortraitChanged(bool checked);
	/*!
	 \brief

	 \fn onOrientationLandscapeChanged
	 \param checked
	*/
	void					onOrientationLandscapeChanged(bool checked);
	/*!
	 \brief

	 \fn onUnitChanged
	 \param text
	*/
	void					onUnitChanged(const QString &text);
	/*!
	 \brief

	 \fn onMarginLeftChanged
	 \param d
	*/
	void					onMarginLeftChanged(double d);
	/*!
	 \brief

	 \fn onMarginRightChanged
	 \param d
	*/
	void					onMarginRightChanged(double d);
	/*!
	 \brief

	 \fn onMarginTopChanged
	 \param d
	*/
	void					onMarginTopChanged(double d);
	/*!
	 \brief

	 \fn onMarginBottomChanged
	 \param d
	*/
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

	void					enablePrintTitle(bool enable);
};

#endif // CPROPERTIESWINDOW_H
