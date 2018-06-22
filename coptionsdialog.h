#ifndef COPTIONSDIALOG_H
#define COPTIONSDIALOG_H


#include <QDialog>

#include <QStandardItemModel>


namespace Ui {
class cOptionsDialog;
}

/*!
 \brief

 \class cOptionsDialog coptionsdialog.h "coptionsdialog.h"
*/
class cOptionsDialog : public QDialog
{
	Q_OBJECT

public:
	/*!
	 \brief

	 \fn cOptionsDialog
	 \param parent
	*/
	explicit cOptionsDialog(QWidget *parent = 0);
	/*!
	 \brief

	 \fn ~cOptionsDialog
	*/
	~cOptionsDialog();

private:
	Ui::cOptionsDialog*	ui;					/*!< TODO: describe */
	QStandardItemModel*	m_lpCategoryModel;	/*!< TODO: describe */
};

#endif // COPTIONSDIALOG_H
