#include "coptionsdialog.h"
#include "ui_coptionsdialog.h"

#include "common.h"

#include <QStringList>
#include <QDir>
#include <QLocale>
#include <QSettings>
#include <QPushButton>


cOptionsDialog::cOptionsDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::cOptionsDialog)
{
	ui->setupUi(this);

	ui->m_lpButtonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
	ui->m_lpButtonBox->button(QDialogButtonBox::Apply)->setEnabled(false);

	m_lpCategoryModel	= new QStandardItemModel(0, 1);
	ui->m_lpCategoryList->setModel(m_lpCategoryModel);

	QIcon			icon(":/category/category_core.png");
	QStandardItem*	lpItem	= new QStandardItem(icon, tr("General"));
	m_lpCategoryModel->appendRow(lpItem);

	ui->m_lpCategoryList->resizeColumnToContents(0);

	QSettings		settings;
	QString			szCur	= settings.value("main/language", "%SYSTEM%").toString();

	ui->m_lpLanguage->addItem("AUTO", QString("SYSTEM"));
	if(!szCur.compare("%SYSTEM%", Qt::CaseInsensitive))
		ui->m_lpLanguage->setCurrentIndex(0);

	QString			szLanguage	= QLocale::languageToString(QLocale("en").language());
	ui->m_lpLanguage->addItem(szLanguage, QString("en"));
	if(!szCur.compare("en", Qt::CaseInsensitive))
		ui->m_lpLanguage->setCurrentIndex(1);

	QString			szPath		= localePath();
	QStringList		localeList	= QDir(":/locale").entryList(QStringList() << "storyWriter*.qm");

	for(int z = 0;z < localeList.count();z++)
	{
		QString		szLocale	= localeList[z];
		szLocale.truncate(szLocale.lastIndexOf("."));
		szLocale.remove(0, szLocale.indexOf('_') + 1);
		szLanguage	= QLocale::languageToString(QLocale(szLocale).language());

		ui->m_lpLanguage->addItem(szLanguage, szLocale);
		if(!szCur.compare(szLocale, Qt::CaseInsensitive))
			ui->m_lpLanguage->setCurrentIndex(z+2);
	}

	connect(ui->m_lpLanguage,	QOverload<int>::of(&QComboBox::currentIndexChanged),	this,	&cOptionsDialog::onLanguageIndexChanged);
	connect(ui->m_lpButtonBox,	QDialogButtonBox::clicked,								this,	&cOptionsDialog::onButtonClicked);
}

cOptionsDialog::~cOptionsDialog()
{
	delete ui;
}

void cOptionsDialog::onLanguageIndexChanged(int /*index*/)
{
	QString		szLanguage	= ui->m_lpLanguage->currentData().toString();
	QSettings	settings;

	if(szLanguage == "SYSTEM")
		szLanguage	= "%SYSTEM%";

	if(settings.value("main/language").toString().compare(szLanguage, Qt::CaseInsensitive))
	{
		ui->m_lpButtonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
		ui->m_lpButtonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
	}
	else
	{
		ui->m_lpButtonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
		ui->m_lpButtonBox->button(QDialogButtonBox::Apply)->setEnabled(false);
	}
}

void cOptionsDialog::onButtonClicked(QAbstractButton* button)
{
	QString		szLanguage	= ui->m_lpLanguage->currentData().toString();
	QSettings	settings;

	if(szLanguage == "SYSTEM")
		szLanguage	= "%SYSTEM%";

	settings.setValue("main/language", szLanguage);

	if(button == ui->m_lpButtonBox->button(QDialogButtonBox::Ok))
	{
		ui->m_lpButtonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
		ui->m_lpButtonBox->button(QDialogButtonBox::Apply)->setEnabled(false);
		onLanguageChanged();
		ui->retranslateUi(this);
	}
	else if(button == ui->m_lpButtonBox->button(QDialogButtonBox::Apply))
	{
		ui->m_lpButtonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
		ui->m_lpButtonBox->button(QDialogButtonBox::Apply)->setEnabled(false);
		onLanguageChanged();
		ui->retranslateUi(this);
	}
}
