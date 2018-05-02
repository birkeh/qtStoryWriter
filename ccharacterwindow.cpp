#include "ccharacterwindow.h"
#include "ui_ccharacterwindow.h"

#include "cimagewidget.h"

#include <QStandardItem>


cCharacterWindow::cCharacterWindow(QWidget *parent) :
	cMDISubWindow(parent),
	ui(new Ui::cCharacterWindow),
	m_lpCharacter(0)
{
	ui->setupUi(this);
	ui->m_lpTab->setCurrentIndex(0);
}

cCharacterWindow::~cCharacterWindow()
{
	delete ui;
}

void cCharacterWindow::setCharacter(cCharacter* lpCharacter)
{
	m_lpCharacter		= lpCharacter;

	ui->m_lpFirstName->setText(lpCharacter->firstName());
	ui->m_lpMiddleName->setText(lpCharacter->middleName());
	ui->m_lpLastName->setText(lpCharacter->lastName());
	ui->m_lpMainCharacter->setChecked(lpCharacter->mainCharacter());
	ui->m_lpCreature->setText(lpCharacter->creature());
	ui->m_lpTitle->setText(lpCharacter->title());
	switch(lpCharacter->gender())
	{
	case cCharacter::GENDER_female:
		ui->m_lpFemale->setChecked(true);
		break;
	case cCharacter::GENDER_male:
		ui->m_lpMale->setChecked(true);
		break;
	case cCharacter::GENDER_undefined:
		ui->m_lpOther->setChecked(true);
		break;
	}
	ui->m_lpDayOfBirth->setDate(lpCharacter->dateOfBirth());
	ui->m_lpDayOfDeath->setDate(lpCharacter->dateOfDeath());
	ui->m_lpPlaceOfBirth->setText(lpCharacter->placeOfBirth());
	ui->m_lpPlaceOfDeath->setText(lpCharacter->placeOfDeath());
	ui->m_lpHeight->setValue(lpCharacter->height());
	ui->m_lpWeight->setValue(lpCharacter->weight());
	ui->m_lpFigure->setText(lpCharacter->figure());
	ui->m_lpNature->setText(lpCharacter->nature());
	ui->m_lpSkin->setText(lpCharacter->skin());
	ui->m_lpHairColor->setText(lpCharacter->hairColor());
	ui->m_lpHairCut->setText(lpCharacter->hairCut());
	ui->m_lpHairLength->setText(lpCharacter->hairLength());
	ui->m_lpSchool->setText(lpCharacter->school());
	ui->m_lpspokenLanguages->setText(lpCharacter->spokenLanguages());
	ui->m_lpJob->setHtml(lpCharacter->job());
	ui->m_lpDescription->setDocument(lpCharacter->description());

	QList<cImage*>	images	= lpCharacter->images();
	for(int x = 0;x < images.count();x++)
	{
		cImage*			lpImage			= images[x];
		QPixmap			pixmap			= lpImage->load();
		cImageWidget*	lpImageWidget	= new cImageWidget;

		lpImageWidget->setValues(lpImage->name(), lpImage->type(), lpImage->description(), pixmap);
		ui->m_lpLayout->addWidget(lpImageWidget);
	}

	QSpacerItem*	lpSpacer		= new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
	ui->m_lpLayout->addItem(lpSpacer);

	setWindowTitle(tr("[character] - ") + lpCharacter->name());
}

cCharacter* cCharacterWindow::character()
{
	return(m_lpCharacter);
}
