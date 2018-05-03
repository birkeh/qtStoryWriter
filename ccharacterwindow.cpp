#include "ccharacterwindow.h"
#include "ui_ccharacterwindow.h"

#include "cimagewidget.h"

#include "cmainwindow.h"

#include <QStandardItem>


cCharacterWindow::cCharacterWindow(QWidget *parent) :
	cMDISubWindow(parent),
	ui(new Ui::cCharacterWindow),
	m_lpCharacter(0)
{
	ui->setupUi(this);
	ui->m_lpTab->setCurrentIndex(0);

	connect(ui->m_lpFirstName, SIGNAL(gotFocus(cLineEdit*)), (cMainWindow*)parent, SLOT(onLineEditGotFocus(cLineEdit*)));
	connect(ui->m_lpFirstName, SIGNAL(lostFocus(cLineEdit*)), (cMainWindow*)parent, SLOT(onLineEditLostFocus(cLineEdit*)));

	connect(ui->m_lpMiddleName, SIGNAL(gotFocus(cLineEdit*)), (cMainWindow*)parent, SLOT(onLineEditGotFocus(cLineEdit*)));
	connect(ui->m_lpMiddleName, SIGNAL(lostFocus(cLineEdit*)), (cMainWindow*)parent, SLOT(onLineEditLostFocus(cLineEdit*)));

	connect(ui->m_lpLastName, SIGNAL(gotFocus(cLineEdit*)), (cMainWindow*)parent, SLOT(onLineEditGotFocus(cLineEdit*)));
	connect(ui->m_lpLastName, SIGNAL(lostFocus(cLineEdit*)), (cMainWindow*)parent, SLOT(onLineEditLostFocus(cLineEdit*)));

	connect(ui->m_lpMainCharacter, SIGNAL(gotFocus(cCheckBox*)), (cMainWindow*)parent, SLOT(onCheckBoxGotFocus(cCheckBox*)));
	connect(ui->m_lpMainCharacter, SIGNAL(lostFocus(cCheckBox*)), (cMainWindow*)parent, SLOT(onCheckBoxLostFocus(cCheckBox*)));

	connect(ui->m_lpCreature, SIGNAL(gotFocus(cLineEdit*)), (cMainWindow*)parent, SLOT(onLineEditGotFocus(cLineEdit*)));
	connect(ui->m_lpCreature, SIGNAL(lostFocus(cLineEdit*)), (cMainWindow*)parent, SLOT(onLineEditLostFocus(cLineEdit*)));

	connect(ui->m_lpTitle, SIGNAL(gotFocus(cLineEdit*)), (cMainWindow*)parent, SLOT(onLineEditGotFocus(cLineEdit*)));
	connect(ui->m_lpTitle, SIGNAL(lostFocus(cLineEdit*)), (cMainWindow*)parent, SLOT(onLineEditLostFocus(cLineEdit*)));

	connect(ui->m_lpMale, SIGNAL(gotFocus(cRadioButton*)), (cMainWindow*)parent, SLOT(onRadioButtonGotFocus(cRadioButton*)));
	connect(ui->m_lpMale, SIGNAL(lostFocus(cRadioButton*)), (cMainWindow*)parent, SLOT(onRadioButtonLostFocus(cRadioButton*)));

	connect(ui->m_lpFemale, SIGNAL(gotFocus(cRadioButton*)), (cMainWindow*)parent, SLOT(onRadioButtonGotFocus(cRadioButton*)));
	connect(ui->m_lpFemale, SIGNAL(lostFocus(cRadioButton*)), (cMainWindow*)parent, SLOT(onRadioButtonLostFocus(cRadioButton*)));

	connect(ui->m_lpOther, SIGNAL(gotFocus(cRadioButton*)), (cMainWindow*)parent, SLOT(onRadioButtonGotFocus(cRadioButton*)));
	connect(ui->m_lpOther, SIGNAL(lostFocus(cRadioButton*)), (cMainWindow*)parent, SLOT(onRadioButtonLostFocus(cRadioButton*)));

	connect(ui->m_lpDayOfBirth, SIGNAL(gotFocus(cDateEdit*)), (cMainWindow*)parent, SLOT(onDateEditGotFocus(cDateEdit*)));
	connect(ui->m_lpDayOfBirth, SIGNAL(lostFocus(cDateEdit*)), (cMainWindow*)parent, SLOT(onDateEditLostFocus(cDateEdit*)));

	connect(ui->m_lpDayOfDeath, SIGNAL(gotFocus(cDateEdit*)), (cMainWindow*)parent, SLOT(onDateEditGotFocus(cDateEdit*)));
	connect(ui->m_lpDayOfDeath, SIGNAL(lostFocus(cDateEdit*)), (cMainWindow*)parent, SLOT(onDateEditLostFocus(cDateEdit*)));

	connect(ui->m_lpPlaceOfBirth, SIGNAL(gotFocus(cLineEdit*)), (cMainWindow*)parent, SLOT(onLineEditGotFocus(cLineEdit*)));
	connect(ui->m_lpPlaceOfBirth, SIGNAL(lostFocus(cLineEdit*)), (cMainWindow*)parent, SLOT(onLineEditLostFocus(cLineEdit*)));

	connect(ui->m_lpPlaceOfDeath, SIGNAL(gotFocus(cLineEdit*)), (cMainWindow*)parent, SLOT(onLineEditGotFocus(cLineEdit*)));
	connect(ui->m_lpPlaceOfDeath, SIGNAL(lostFocus(cLineEdit*)), (cMainWindow*)parent, SLOT(onLineEditLostFocus(cLineEdit*)));

	connect(ui->m_lpHeight, SIGNAL(gotFocus(cDoubleSpinBox*)), (cMainWindow*)parent, SLOT(onDoubleSpinBoxGotFocus(cDoubleSpinBox*)));
	connect(ui->m_lpHeight, SIGNAL(lostFocus(cDoubleSpinBox*)), (cMainWindow*)parent, SLOT(onDoubleSpinBoxLostFocus(cDoubleSpinBox*)));

	connect(ui->m_lpWeight, SIGNAL(gotFocus(cDoubleSpinBox*)), (cMainWindow*)parent, SLOT(onDoubleSpinBoxGotFocus(cDoubleSpinBox*)));
	connect(ui->m_lpWeight, SIGNAL(lostFocus(cDoubleSpinBox*)), (cMainWindow*)parent, SLOT(onDoubleSpinBoxLostFocus(cDoubleSpinBox*)));

	connect(ui->m_lpFigure, SIGNAL(gotFocus(cLineEdit*)), (cMainWindow*)parent, SLOT(onLineEditGotFocus(cLineEdit*)));
	connect(ui->m_lpFigure, SIGNAL(lostFocus(cLineEdit*)), (cMainWindow*)parent, SLOT(onLineEditLostFocus(cLineEdit*)));

	connect(ui->m_lpSkin, SIGNAL(gotFocus(cLineEdit*)), (cMainWindow*)parent, SLOT(onLineEditGotFocus(cLineEdit*)));
	connect(ui->m_lpSkin, SIGNAL(lostFocus(cLineEdit*)), (cMainWindow*)parent, SLOT(onLineEditLostFocus(cLineEdit*)));

	connect(ui->m_lpNature, SIGNAL(gotFocus(cLineEdit*)), (cMainWindow*)parent, SLOT(onLineEditGotFocus(cLineEdit*)));
	connect(ui->m_lpNature, SIGNAL(lostFocus(cLineEdit*)), (cMainWindow*)parent, SLOT(onLineEditLostFocus(cLineEdit*)));

	connect(ui->m_lpHairColor, SIGNAL(gotFocus(cLineEdit*)), (cMainWindow*)parent, SLOT(onLineEditGotFocus(cLineEdit*)));
	connect(ui->m_lpHairColor, SIGNAL(lostFocus(cLineEdit*)), (cMainWindow*)parent, SLOT(onLineEditLostFocus(cLineEdit*)));

	connect(ui->m_lpHairCut, SIGNAL(gotFocus(cLineEdit*)), (cMainWindow*)parent, SLOT(onLineEditGotFocus(cLineEdit*)));
	connect(ui->m_lpHairCut, SIGNAL(lostFocus(cLineEdit*)), (cMainWindow*)parent, SLOT(onLineEditLostFocus(cLineEdit*)));

	connect(ui->m_lpHairLength, SIGNAL(gotFocus(cLineEdit*)), (cMainWindow*)parent, SLOT(onLineEditGotFocus(cLineEdit*)));
	connect(ui->m_lpHairLength, SIGNAL(lostFocus(cLineEdit*)), (cMainWindow*)parent, SLOT(onLineEditLostFocus(cLineEdit*)));

	connect(ui->m_lpSchool, SIGNAL(gotFocus(cTextEdit*)), (cMainWindow*)parent, SLOT(onTextEditGotFocus(cTextEdit*)));
	connect(ui->m_lpSchool, SIGNAL(lostFocus(cTextEdit*)), (cMainWindow*)parent, SLOT(onTextEditLostFocus(cTextEdit*)));

	connect(ui->m_lpSpokenLanguages, SIGNAL(gotFocus(cTextEdit*)), (cMainWindow*)parent, SLOT(onTextEditGotFocus(cTextEdit*)));
	connect(ui->m_lpSpokenLanguages, SIGNAL(lostFocus(cTextEdit*)), (cMainWindow*)parent, SLOT(onTextEditLostFocus(cTextEdit*)));

	connect(ui->m_lpJob, SIGNAL(gotFocus(cTextEdit*)), (cMainWindow*)parent, SLOT(onTextEditGotFocus(cTextEdit*)));
	connect(ui->m_lpJob, SIGNAL(lostFocus(cTextEdit*)), (cMainWindow*)parent, SLOT(onTextEditLostFocus(cTextEdit*)));

	connect(ui->m_lpDescription, SIGNAL(gotFocus(cTextEdit*)), (cMainWindow*)parent, SLOT(onTextEditGotFocus(cTextEdit*)));
	connect(ui->m_lpDescription, SIGNAL(lostFocus(cTextEdit*)), (cMainWindow*)parent, SLOT(onTextEditLostFocus(cTextEdit*)));
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
	ui->m_lpSpokenLanguages->setText(lpCharacter->spokenLanguages());
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
