#include "cobjectselectdialog.h"
#include "ui_cobjectselectdialog.h"


cObjectSelectDialog::cObjectSelectDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::cObjectSelectDialog)
{
	ui->setupUi(this);

	m_lpObjectListModel	= new QStandardItemModel(0, 1);
	ui->m_lpObjectList->setModel(m_lpObjectListModel);

	connect(ui->m_lpObjectList, &QTreeView::doubleClicked, this, &cObjectSelectDialog::onObjectDoubleClicked);
}

cObjectSelectDialog::~cObjectSelectDialog()
{
	delete ui;
}

void cObjectSelectDialog::setObjectList(cObjectList* lpObjectList, QList<cObjectDescription *> objectDescriptionList)
{
	QStandardItemModel*				lpModel					= m_lpObjectListModel;

	lpModel->clear();

	QStringList						headerLabels	= QStringList() << tr("name") << tr("type");
	m_lpObjectListModel->setHorizontalHeaderLabels(headerLabels);

	for(int x = 0;x < lpObjectList->count();x++)
	{
		bool					bFound		= false;
		cObject*				lpObject	= lpObjectList->at(x);

		for(int y = 0;y < objectDescriptionList.count();y++)
		{
			if(lpObject == objectDescriptionList.at(y)->object())
			{
				bFound	= true;
				break;
			}
		}

		if(bFound)
			continue;

		QList<QStandardItem*>	lpItems;

		lpItems.append(new QStandardItem(lpObject->name()));
		lpItems.append(new QStandardItem(lpObject->type()));

		for(int i = 0;i < headerLabels.count();i++)
		{
			lpItems[i]->setData(QVariant::fromValue(lpObject));

			if(lpObject->description())
				lpItems[i]->setToolTip(lpObject->description()->toPlainText());
		}

		m_lpObjectListModel->appendRow(lpItems);
	}

	ui->m_lpObjectList->header()->setStretchLastSection(true);

	ui->m_lpObjectList->expandAll();

	for(int i = 0;i < headerLabels.count();i++)
		ui->m_lpObjectList->resizeColumnToContents(i);

	ui->m_lpObjectList->setCurrentIndex(m_lpObjectListModel->index(0, 0));
}

void cObjectSelectDialog::onObjectDoubleClicked(const QModelIndex& /*index*/)
{
	this->accept();
}

cObject* cObjectSelectDialog::selected()
{
	if(!ui->m_lpObjectList->currentIndex().isValid())
		return(0);

	QStandardItem*	lpItem	= m_lpObjectListModel->itemFromIndex(ui->m_lpObjectList->currentIndex());
	if(!lpItem)
		return(0);

	return(qvariant_cast<cObject*>(lpItem->data()));
}
