#ifndef COBJECTSELECTDIALOG_H
#define COBJECTSELECTDIALOG_H


#include "cobject.h"

#include <QList>
#include <QStandardItemModel>
#include <QDialog>


namespace Ui {
class cObjectSelectDialog;
}

/*!
 \brief

 \class cObjectSelectDialog cobjectselectdialog.h "cobjectselectdialog.h"
*/
class cObjectSelectDialog : public QDialog
{
	Q_OBJECT

public:
	/*!
	 \brief

	 \fn cObjectSelectDialog
	 \param parent
	*/
	explicit cObjectSelectDialog(QWidget *parent = 0);
	/*!
	 \brief

	 \fn ~cObjectSelectDialog
	*/
	~cObjectSelectDialog();

	/*!
	 \brief

	 \fn setObjectList
	 \param lpObjectList
	 \param objectDescriptionList
	*/
	void						setObjectList(cObjectList* lpObjectList, QList<cObjectDescription *> objectDescriptionList);
	/*!
	 \brief

	 \fn selected
	 \return cObject
	*/
	cObject*					selected();

private:
	Ui::cObjectSelectDialog*	ui;						/*!< TODO: describe */
	QStandardItemModel*			m_lpObjectListModel;	/*!< TODO: describe */

private slots:
	/*!
	 \brief

	 \fn onObjectDoubleClicked
	 \param index
	*/
	void						onObjectDoubleClicked(const QModelIndex& index);
};

#endif // COBJECTSELECTDIALOG_H
