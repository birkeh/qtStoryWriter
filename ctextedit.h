/*!
 \file ctextedit.h

*/

#ifndef CTEXTEDIT_H
#define CTEXTEDIT_H


#include <QTextEdit>
#include <QMetaType>


class cMainWindow;

/*!
 \brief

 \class cTextEdit ctextedit.h "ctextedit.h"
*/
class cTextEdit : public QTextEdit
{
	Q_OBJECT

public:
	/*!
	 \brief

	 \fn cTextEdit
	 \param parent
	*/
	cTextEdit(QWidget* parent = Q_NULLPTR);
	/*!
	 \brief

	 \fn cTextEdit
	 \param text
	 \param parent
	*/
	cTextEdit(const QString& text, QWidget* parent = Q_NULLPTR);

	/*!
	 \brief

	 \fn canInsertFromMimeData
	 \param source
	 \return bool
	*/
	bool			canInsertFromMimeData(const QMimeData* source) const;
	/*!
	 \brief

	 \fn insertFromMimeData
	 \param source
	*/
	void			insertFromMimeData(const QMimeData* source);

signals:
	/*!
	 \brief

	 \fn gotFocus
	 \param lpTextEdit
	*/
	void			gotFocus(cTextEdit* lpTextEdit);
	/*!
	 \brief

	 \fn lostFocus
	 \param lpTextEdit
	*/
	void			lostFocus(cTextEdit* lpTextEdit);

	/*!
	 \brief

	 \fn fontChanged
	 \param font
	*/
	void			fontChanged(const QFont& font);
	/*!
	 \brief

	 \fn colorChanged
	 \param color
	*/
	void			colorChanged(const QColor& color);
	/*!
	 \brief

	 \fn alignmentChanged
	 \param alignment
	*/
	void			alignmentChanged(const Qt::Alignment& alignment);

public slots:
	/*!
	 \brief

	 \fn onTextBold
	 \param isChecked
	*/
	void			onTextBold(bool isChecked);
	/*!
	 \brief

	 \fn onTextUnderline
	 \param isChecked
	*/
	void			onTextUnderline(bool isChecked);
	/*!
	 \brief

	 \fn onTextItalic
	 \param isChecked
	*/
	void			onTextItalic(bool isChecked);

	/*!
	 \brief

	 \fn onTextAlign
	 \param a
	*/
	void			onTextAlign(QAction *a);

	/*!
	 \brief

	 \fn onTextFamily
	 \param f
	*/
	void			onTextFamily(const QString &f);
	/*!
	 \brief

	 \fn onTextSize
	 \param p
	*/
	void			onTextSize(const QString &p);
	/*!
	 \brief

	 \fn onTextStyle
	 \param styleIndex
	*/
	void			onTextStyle(int styleIndex);

	/*!
	 \brief

	 \fn onTextColor
	*/
	void			onTextColor();

	/*!
	 \brief

	 \fn onCurrentCharFormatChanged
	 \param format
	*/
	void			onCurrentCharFormatChanged(const QTextCharFormat &format);
	/*!
	 \brief

	 \fn onCursorPositionChanged
	*/
	void			onCursorPositionChanged();

private:
	cMainWindow*	m_lpMainWindow; /*!< TODO: describe */

	/*!
	 \brief

	 \fn dropImage
	 \param url
	 \param image
	*/
	void			dropImage(const QUrl& url, const QImage& image);
	/*!
	 \brief

	 \fn dropTextFile
	 \param url
	*/
	void			dropTextFile(const QUrl& url);

	/*!
	 \brief

	 \fn mergeFormatOnWordOrSelection
	 \param format
	*/
	void			mergeFormatOnWordOrSelection(const QTextCharFormat& format);

protected:
	/*!
	 \brief

	 \fn focusInEvent
	 \param event
	*/
	void			focusInEvent(QFocusEvent *event);
	/*!
	 \brief

	 \fn focusOutEvent
	 \param event
	*/
	void			focusOutEvent(QFocusEvent *event);
};

Q_DECLARE_METATYPE(cTextEdit*)

#endif // CTEXTEDIT_H
