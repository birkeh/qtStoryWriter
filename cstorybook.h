#ifndef CSTORYBOOK_H
#define CSTORYBOOK_H


#include "cbook.h"

#include <QString>

#include <QSqlDatabase>


class cStoryBook
{
public:
	cStoryBook(const QString& szProjectPath);
	~cStoryBook();

	bool			openDatabase();
	bool			verify();
private:
	QString			m_szProjectPath;
	bool			m_bIsOpen;
	QSqlDatabase	m_db;
	cBook			m_book;

	bool			createDatabase();
	bool			updateDatabase();
	bool			createTable(const QString& szSQL);

	bool			loadBook();
};

#endif // CSTORYBOOK_H
