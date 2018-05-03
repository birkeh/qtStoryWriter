#ifndef CTEXTEDIT_H
#define CTEXTEDIT_H


#include <QTextEdit>
#include <QMetaType>


class cMainWindow;

class cTextEdit : public QTextEdit
{
	Q_OBJECT

public:
	cTextEdit(QWidget* parent = Q_NULLPTR);
	cTextEdit(const QString& text, QWidget* parent = Q_NULLPTR);

	bool			canInsertFromMimeData(const QMimeData* source) const;
	void			insertFromMimeData(const QMimeData* source);

signals:
	void			gotFocus(cTextEdit* lpTextEdit);
	void			lostFocus(cTextEdit* lpTextEdit);

	void			fontChanged(const QFont& font);
	void			colorChanged(const QColor& color);
	void			alignmentChanged(const Qt::Alignment& alignment);

public slots:
	void			onTextBold(bool isChecked);
	void			onTextUnderline(bool isChecked);
	void			onTextItalic(bool isChecked);

	void			onTextAlign(QAction *a);

	void			onTextFamily(const QString &f);
	void			onTextSize(const QString &p);
	void			onTextStyle(int styleIndex);

	void			onTextColor();

	void			onCurrentCharFormatChanged(const QTextCharFormat &format);
	void			onCursorPositionChanged();

private:
	cMainWindow*	m_lpMainWindow;

	void			dropImage(const QUrl& url, const QImage& image);
	void			dropTextFile(const QUrl& url);

	void			mergeFormatOnWordOrSelection(const QTextCharFormat& format);

protected:
	void			focusInEvent(QFocusEvent *event);
	void			focusOutEvent(QFocusEvent *event);
};

Q_DECLARE_METATYPE(cTextEdit*)

#endif // CTEXTEDIT_H
