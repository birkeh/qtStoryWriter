#ifndef CCHARACTERSELECTDIALOG_H
#define CCHARACTERSELECTDIALOG_H


#include "ccharacter.h"

#include <QList>
#include <QStandardItemModel>
#include <QDialog>


namespace Ui {
class cCharacterSelectDialog;
}

/*!
 \brief

 \class cCharacterSelectDialog ccharacterselectdialog.h "ccharacterselectdialog.h"
*/
class cCharacterSelectDialog : public QDialog
{
	Q_OBJECT

public:
	/*!
	 \brief

	 \fn cCharacterSelectDialog
	 \param parent
	*/
	explicit cCharacterSelectDialog(QWidget *parent = 0);
	/*!
	 \brief

	 \fn ~cCharacterSelectDialog
	*/
	~cCharacterSelectDialog();

	/*!
	 \brief

	 \fn setCharacterList
	 \param lpCharacterList
	 \param characterDescriptionList
	*/
	void						setCharacterList(cCharacterList* lpCharacterList, QList<cCharacterDescription *> characterDescriptionList);
	/*!
	 \brief

	 \fn selected
	 \return cCharacter
	*/
	cCharacter*					selected();
private:
	Ui::cCharacterSelectDialog*	ui;						/*!< TODO: describe */
	QStandardItemModel*			m_lpCharacterListModel;	/*!< TODO: describe */

private slots:
	/*!
	 \brief

	 \fn onCharacterDoubleClicked
	 \param index
	*/
	void						onCharacterDoubleClicked(const QModelIndex& index);
};

#endif // CCHARACTERSELECTDIALOG_H
