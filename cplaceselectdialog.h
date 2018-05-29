#ifndef CPLACESELECTDIALOG_H
#define CPLACESELECTDIALOG_H


#include "cplace.h"

#include <QList>
#include <QStandardItemModel>
#include <QDialog>


namespace Ui {
class cPlaceSelectDialog;
}

/*!
 \brief

 \class cPlaceSelectDialog cplaceselectdialog.h "cplaceselectdialog.h"
*/
class cPlaceSelectDialog : public QDialog
{
	Q_OBJECT

public:
	/*!
	 \brief

	 \fn cPlaceSelectDialog
	 \param parent
	*/
	explicit cPlaceSelectDialog(QWidget *parent = 0);
	/*!
	 \brief

	 \fn ~cPlaceSelectDialog
	*/
	~cPlaceSelectDialog();

	/*!
	 \brief

	 \fn setPlaceList
	 \param lpPlaceList
	 \param placeDescriptionList
	*/
	void						setPlaceList(cPlaceList* lpPlaceList, QList<cPlaceDescription *> placeDescriptionList);
	/*!
	 \brief

	 \fn selected
	 \return cPlace
	*/
	cPlace*						selected();

private:
	Ui::cPlaceSelectDialog*		ui;					/*!< TODO: describe */
	QStandardItemModel*			m_lpPlaceListModel;	/*!< TODO: describe */

private slots:
	/*!
	 \brief

	 \fn onPlaceDoubleClicked
	 \param index
	*/
	void						onPlaceDoubleClicked(const QModelIndex& index);
};

#endif // CPLACESELECTDIALOG_H
