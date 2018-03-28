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


class cTextDocument : public QTextDocument
{
public:
	cTextDocument(QObject *parent = Q_NULLPTR);
	cTextDocument(const QString &text, QObject *parent = Q_NULLPTR);

	bool			save(bool bZip = true);
	bool			saveAs(const QString& szFileName, bool bZip = true);

	void			printPreview(QPrinter* lpPrinter);
private:
	QString			m_szFileName;

	void			init();
	bool			saveDocument(bool bZip = true);
private slots:
};

#endif // CTEXTDOCUMENT_H
