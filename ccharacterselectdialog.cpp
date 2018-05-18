#include "ccharacterselectdialog.h"
#include "ui_ccharacterselectdialog.h"


cCharacterSelectDialog::cCharacterSelectDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::cCharacterSelectDialog)
{
	ui->setupUi(this);

	m_lpCharacterListModel	= new QStandardItemModel(0, 1);
	ui->m_lpCharacterList->setModel(m_lpCharacterListModel);

	connect(ui->m_lpCharacterList, &QTreeView::doubleClicked, this, &cCharacterSelectDialog::onCharacterDoubleClicked);
}

cCharacterSelectDialog::~cCharacterSelectDialog()
{
	delete ui;
}

void cCharacterSelectDialog::setCharacterList(cCharacterList* lpCharacterList, QList<cCharacterDescription *> characterDescriptionList)
{
	QStandardItemModel*				lpModel					= m_lpCharacterListModel;
	QStandardItem*					lpRootItem				= lpModel->invisibleRootItem();
	QFont							fontMainCharacter		= lpRootItem->font();
	QFont							fontNonMainCharacter	= lpRootItem->font();

	lpModel->clear();

	QStringList						headerLabels	= QStringList() << tr("name") << tr("creature") << tr("gender");
	m_lpCharacterListModel->setHorizontalHeaderLabels(headerLabels);

	fontMainCharacter.setBold(true);
	fontNonMainCharacter.setItalic(true);

	for(int x = 0;x < lpCharacterList->count();x++)
	{
		bool					bFound		= false;
		cCharacter*				lpCharacter	= lpCharacterList->at(x);

		for(int y = 0;y < characterDescriptionList.count();y++)
		{
			if(lpCharacter == characterDescriptionList.at(y)->character())
			{
				bFound	= true;
				break;
			}
		}

		if(bFound)
			continue;

		QList<QStandardItem*>	lpItems;

		lpItems.append(new QStandardItem(lpCharacter->name()));
		lpItems.append(new QStandardItem(lpCharacter->creature()));
		lpItems.append(new QStandardItem(lpCharacter->genderText()));

		for(int i = 0;i < headerLabels.count();i++)
		{
			lpItems[i]->setData(QVariant::fromValue(lpCharacter));
			if(lpCharacter->mainCharacter())
				lpItems[i]->setFont(fontMainCharacter);
			else
				lpItems[i]->setFont(fontNonMainCharacter);

			if(lpCharacter->description())
				lpItems[i]->setToolTip(lpCharacter->description()->toPlainText());
		}

		m_lpCharacterListModel->appendRow(lpItems);
	}

	ui->m_lpCharacterList->header()->setStretchLastSection(true);

	ui->m_lpCharacterList->expandAll();

	for(int i = 0;i < headerLabels.count();i++)
		ui->m_lpCharacterList->resizeColumnToContents(i);

	ui->m_lpCharacterList->setCurrentIndex(m_lpCharacterListModel->index(0, 0));
}

void cCharacterSelectDialog::onCharacterDoubleClicked(const QModelIndex& /*index*/)
{
	this->accept();
}

cCharacter* cCharacterSelectDialog::selected()
{
	if(!ui->m_lpCharacterList->currentIndex().isValid())
		return(0);

	QStandardItem*	lpItem	= m_lpCharacterListModel->itemFromIndex(ui->m_lpCharacterList->currentIndex());
	if(!lpItem)
		return(0);

	return(qvariant_cast<cCharacter*>(lpItem->data()));
}
