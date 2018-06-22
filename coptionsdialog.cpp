#include "coptionsdialog.h"
#include "ui_coptionsdialog.h"


cOptionsDialog::cOptionsDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::cOptionsDialog)
{
	ui->setupUi(this);

	m_lpCategoryModel	= new QStandardItemModel(0, 1);
	ui->m_lpCategoryList->setModel(m_lpCategoryModel);

	QIcon			icon(":/category/category_core.png");
	QStandardItem*	lpItem	= new QStandardItem(icon, tr("General"));
	m_lpCategoryModel->appendRow(lpItem);

	ui->m_lpCategoryList->resizeColumnToContents(0);
}

cOptionsDialog::~cOptionsDialog()
{
	delete ui;
}
