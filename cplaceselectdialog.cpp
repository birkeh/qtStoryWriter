#include "cplaceselectdialog.h"
#include "ui_cplaceselectdialog.h"


cPlaceSelectDialog::cPlaceSelectDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::cPlaceSelectDialog)
{
	ui->setupUi(this);

	m_lpPlaceListModel	= new QStandardItemModel(0, 1);
	ui->m_lpPlaceList->setModel(m_lpPlaceListModel);

	connect(ui->m_lpPlaceList, &QTreeView::doubleClicked, this, &cPlaceSelectDialog::onPlaceDoubleClicked);
}

cPlaceSelectDialog::~cPlaceSelectDialog()
{
	delete ui;
}

void cPlaceSelectDialog::setPlaceList(cPlaceList* lpPlaceList, QList<cPlaceDescription *> placeDescriptionList)
{
	QStandardItemModel*				lpModel					= m_lpPlaceListModel;

	lpModel->clear();

	QStringList						headerLabels	= QStringList() << tr("name") << tr("location") << tr("type");
	m_lpPlaceListModel->setHorizontalHeaderLabels(headerLabels);

	for(int x = 0;x < lpPlaceList->count();x++)
	{
		bool					bFound		= false;
		cPlace*					lpPlace		= lpPlaceList->at(x);

		for(int y = 0;y < placeDescriptionList.count();y++)
		{
			if(lpPlace == placeDescriptionList.at(y)->place())
			{
				bFound	= true;
				break;
			}
		}

		if(bFound)
			continue;

		QList<QStandardItem*>	lpItems;

		lpItems.append(new QStandardItem(lpPlace->name()));
		lpItems.append(new QStandardItem(lpPlace->location()));
		lpItems.append(new QStandardItem(lpPlace->type()));

		for(int i = 0;i < headerLabels.count();i++)
		{
			lpItems[i]->setData(QVariant::fromValue(lpPlace));

			if(lpPlace->description())
				lpItems[i]->setToolTip(lpPlace->description()->toPlainText());
		}

		m_lpPlaceListModel->appendRow(lpItems);
	}

	ui->m_lpPlaceList->header()->setStretchLastSection(true);

	ui->m_lpPlaceList->expandAll();

	for(int i = 0;i < headerLabels.count();i++)
		ui->m_lpPlaceList->resizeColumnToContents(i);

	ui->m_lpPlaceList->setCurrentIndex(m_lpPlaceListModel->index(0, 0));
}

void cPlaceSelectDialog::onPlaceDoubleClicked(const QModelIndex& /*index*/)
{
	this->accept();
}

cPlace* cPlaceSelectDialog::selected()
{
	if(!ui->m_lpPlaceList->currentIndex().isValid())
		return(0);

	QStandardItem*	lpItem	= m_lpPlaceListModel->itemFromIndex(ui->m_lpPlaceList->currentIndex());
	if(!lpItem)
		return(0);

	return(qvariant_cast<cPlace*>(lpItem->data()));
}
