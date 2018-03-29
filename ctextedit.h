#ifndef CTEXTEDIT_H
#define CTEXTEDIT_H


#include <QTextEdit>


class cTextEdit : public QTextEdit
{
public:
	cTextEdit(QWidget* parent = Q_NULLPTR);
	cTextEdit(const QString& text, QWidget* parent = Q_NULLPTR);

	bool		canInsertFromMimeData(const QMimeData* source) const;
	void		insertFromMimeData(const QMimeData* source);

private:
	void		dropImage(const QUrl& url, const QImage& image);
	void		dropTextFile(const QUrl& url);
};

#endif // CTEXTEDIT_H
