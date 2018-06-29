#ifndef COPTIONSDIALOG_H
#define COPTIONSDIALOG_H


#include <QDialog>
#include <QAbstractButton>

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


	/*!
	 \brief

	 \fn retranslateUI
	*/
	void				retranslateUI();

private slots:
	/*!
	 \brief

	 \fn onLanguageIndexChanged
	 \param index
	*/
	void				onLanguageIndexChanged(int index);

	/*!
	 \brief

	 \fn onButtonClicked
	 \param button
	*/
	void				onButtonClicked(QAbstractButton* button);
signals:
	/*!
	 \brief

	 \fn onLanguageChanged
	*/
	void				onLanguageChanged();

private:
	Ui::cOptionsDialog*	ui;					/*!< TODO: describe */
	QStandardItemModel*	m_lpCategoryModel;	/*!< TODO: describe */
	QStandardItem*		m_lpGeneralItem;	/*!< TODO: describe */
};

#endif // COPTIONSDIALOG_H
