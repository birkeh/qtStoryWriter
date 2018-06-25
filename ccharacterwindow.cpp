/*!
 \file ccharacterwindow.cpp

*/

#include "ccharacterwindow.h"
#include "ui_ccharacterwindow.h"

#include "cimagewidget.h"

#include "cmainwindow.h"

#include "common.h"

#include <QStandardItem>


cCharacterWindow::cCharacterWindow(QWidget *parent) :
	cMDISubWindow(parent),
	ui(new Ui::cCharacterWindow),
	m_lpMainWindow((cMainWindow*)parent),
	m_lpCharacter(0)
{
	ui->setupUi(this);
	ui->m_lpTab->setCurrentIndex(0);

	connect(ui->m_lpFirstName,			&cLineEdit::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onLineEditGotFocus);
	connect(ui->m_lpFirstName,			&cLineEdit::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onLineEditLostFocus);

	connect(ui->m_lpMiddleName,			&cLineEdit::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onLineEditGotFocus);
	connect(ui->m_lpMiddleName,			&cLineEdit::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onLineEditLostFocus);

	connect(ui->m_lpLastName,			&cLineEdit::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onLineEditGotFocus);
	connect(ui->m_lpLastName,			&cLineEdit::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onLineEditLostFocus);

	connect(ui->m_lpNickName,			&cLineEdit::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onLineEditGotFocus);
	connect(ui->m_lpNickName,			&cLineEdit::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onLineEditLostFocus);

	connect(ui->m_lpMainCharacter,		&cCheckBox::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxGotFocus);
	connect(ui->m_lpMainCharacter,		&cCheckBox::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxLostFocus);

	connect(ui->m_lpCreature,			&cLineEdit::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onLineEditGotFocus);
	connect(ui->m_lpCreature,			&cLineEdit::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onLineEditLostFocus);

	connect(ui->m_lpTitle,				&cLineEdit::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onLineEditGotFocus);
	connect(ui->m_lpTitle,				&cLineEdit::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onLineEditLostFocus);

	connect(ui->m_lpMale,				&cRadioButton::gotFocus,	(cMainWindow*)parent,	&cMainWindow::onRadioButtonGotFocus);
	connect(ui->m_lpMale,				&cRadioButton::lostFocus,	(cMainWindow*)parent,	&cMainWindow::onRadioButtonLostFocus);

	connect(ui->m_lpFemale,				&cRadioButton::gotFocus,	(cMainWindow*)parent,	&cMainWindow::onRadioButtonGotFocus);
	connect(ui->m_lpFemale,				&cRadioButton::lostFocus,	(cMainWindow*)parent,	&cMainWindow::onRadioButtonLostFocus);

	connect(ui->m_lpOther,				&cRadioButton::gotFocus,	(cMainWindow*)parent,	&cMainWindow::onRadioButtonGotFocus);
	connect(ui->m_lpOther,				&cRadioButton::lostFocus,	(cMainWindow*)parent,	&cMainWindow::onRadioButtonLostFocus);

	connect(ui->m_lpDayOfBirth,			&cDateEdit::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onDateEditGotFocus);
	connect(ui->m_lpDayOfBirth,			&cDateEdit::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onDateEditLostFocus);

	connect(ui->m_lpDayOfDeath,			&cDateEdit::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onDateEditGotFocus);
	connect(ui->m_lpDayOfDeath,			&cDateEdit::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onDateEditLostFocus);

	connect(ui->m_lpPlaceOfBirth,		&cLineEdit::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onLineEditGotFocus);
	connect(ui->m_lpPlaceOfBirth,		&cLineEdit::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onLineEditLostFocus);

	connect(ui->m_lpPlaceOfDeath,		&cLineEdit::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onLineEditGotFocus);
	connect(ui->m_lpPlaceOfDeath,		&cLineEdit::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onLineEditLostFocus);

	connect(ui->m_lpHeight,				&cDoubleSpinBox::gotFocus,	(cMainWindow*)parent,	&cMainWindow::onDoubleSpinBoxGotFocus);
	connect(ui->m_lpHeight,				&cDoubleSpinBox::lostFocus,	(cMainWindow*)parent,	&cMainWindow::onDoubleSpinBoxLostFocus);

	connect(ui->m_lpWeight,				&cDoubleSpinBox::gotFocus,	(cMainWindow*)parent,	&cMainWindow::onDoubleSpinBoxGotFocus);
	connect(ui->m_lpWeight,				&cDoubleSpinBox::lostFocus,	(cMainWindow*)parent,	&cMainWindow::onDoubleSpinBoxLostFocus);

	connect(ui->m_lpFigure,				&cLineEdit::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onLineEditGotFocus);
	connect(ui->m_lpFigure,				&cLineEdit::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onLineEditLostFocus);

	connect(ui->m_lpSkin,				&cLineEdit::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onLineEditGotFocus);
	connect(ui->m_lpSkin,				&cLineEdit::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onLineEditLostFocus);

	connect(ui->m_lpNature,				&cLineEdit::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onLineEditGotFocus);
	connect(ui->m_lpNature,				&cLineEdit::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onLineEditLostFocus);

	connect(ui->m_lpHairColor,			&cLineEdit::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onLineEditGotFocus);
	connect(ui->m_lpHairColor,			&cLineEdit::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onLineEditLostFocus);

	connect(ui->m_lpHairCut,			&cLineEdit::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onLineEditGotFocus);
	connect(ui->m_lpHairCut,			&cLineEdit::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onLineEditLostFocus);

	connect(ui->m_lpHairLength,			&cLineEdit::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onLineEditGotFocus);
	connect(ui->m_lpHairLength,			&cLineEdit::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onLineEditLostFocus);

	connect(ui->m_lpSchool,				&cTextEdit::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onTextEditGotFocus);
	connect(ui->m_lpSchool,				&cTextEdit::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onTextEditLostFocus);

	connect(ui->m_lpSpokenLanguages,	&cTextEdit::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onTextEditGotFocus);
	connect(ui->m_lpSpokenLanguages,	&cTextEdit::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onTextEditLostFocus);

	connect(ui->m_lpJob,				&cTextEdit::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onTextEditGotFocus);
	connect(ui->m_lpJob,				&cTextEdit::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onTextEditLostFocus);

	connect(ui->m_lpDescription,		&cTextEdit::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onTextEditGotFocus);
	connect(ui->m_lpDescription,		&cTextEdit::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onTextEditLostFocus);
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
	ui->m_lpNickName->setText(lpCharacter->nickName());
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
		cImage*				lpImage				= images[x];
		QPixmap				pixmap				= lpImage->image();
		cImageWidget*		lpImageWidget		= new cImageWidget;

		lpImageWidget->setValues(lpImage->name(), lpImage->description(), pixmap);
		ui->m_lpLayout->addWidget(lpImageWidget);
	}

	QSpacerItem*	lpSpacer		= new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
	ui->m_lpLayout->addItem(lpSpacer);

	setWindowTitle(windowTitle() + lpCharacter->name());

	connect(ui->m_lpFirstName,			&cLineEdit::textChanged,								this,	&cCharacterWindow::onFirstNameChanged);
	connect(ui->m_lpMiddleName,			&cLineEdit::textChanged,								this,	&cCharacterWindow::onMiddleNameChanged);
	connect(ui->m_lpLastName,			&cLineEdit::textChanged,								this,	&cCharacterWindow::onLastNameChanged);
	connect(ui->m_lpNickName,			&cLineEdit::textChanged,								this,	&cCharacterWindow::onNickNameChanged);
	connect(ui->m_lpMainCharacter,		&cCheckBox::clicked,									this,	&cCharacterWindow::onMainCharacterClicked);
	connect(ui->m_lpCreature,			&cLineEdit::textChanged,								this,	&cCharacterWindow::onCreatureChanged);
	connect(ui->m_lpMale,				&cCheckBox::clicked,									this,	&cCharacterWindow::onGenderMaleClicked);
	connect(ui->m_lpFemale,				&cCheckBox::clicked,									this,	&cCharacterWindow::onGenderFemaleClicked);
	connect(ui->m_lpOther,				&cCheckBox::clicked,									this,	&cCharacterWindow::onGenderOtherClicked);
	connect(ui->m_lpTitle,				&cLineEdit::textChanged,								this,	&cCharacterWindow::onTitleChanged);
	connect(ui->m_lpDayOfBirth,			&cDateEdit::dateChanged,								this,	&cCharacterWindow::onDateOfBirthChanged);
	connect(ui->m_lpDayOfDeath,			&cDateEdit::dateChanged,								this,	&cCharacterWindow::onDateOfDeathChanged);
	connect(ui->m_lpPlaceOfBirth,		&cLineEdit::textChanged,								this,	&cCharacterWindow::onPlaceOfBirthChanged);
	connect(ui->m_lpPlaceOfDeath,		&cLineEdit::textChanged,								this,	&cCharacterWindow::onPlaceOfDeathChanged);
	connect(ui->m_lpHeight,				QOverload<double>::of(&cDoubleSpinBox::valueChanged),	this,	&cCharacterWindow::onHeightChanged);
	connect(ui->m_lpWeight,				QOverload<double>::of(&cDoubleSpinBox::valueChanged),	this,	&cCharacterWindow::onWeightChanged);
	connect(ui->m_lpFigure,				&cLineEdit::textChanged,								this,	&cCharacterWindow::onFigureChanged);
	connect(ui->m_lpSkin,				&cLineEdit::textChanged,								this,	&cCharacterWindow::onSkinChanged);
	connect(ui->m_lpNature,				&cLineEdit::textChanged,								this,	&cCharacterWindow::onNatureChanged);
	connect(ui->m_lpHairColor,			&cLineEdit::textChanged,								this,	&cCharacterWindow::onHairColorChanged);
	connect(ui->m_lpHairCut,			&cLineEdit::textChanged,								this,	&cCharacterWindow::onHairCutChanged);
	connect(ui->m_lpHairLength,			&cLineEdit::textChanged,								this,	&cCharacterWindow::onHairLengthChanged);
	connect(ui->m_lpSchool,				&cTextEdit::textChanged,								this,	&cCharacterWindow::onSchoolChanged);
	connect(ui->m_lpSpokenLanguages,	&cTextEdit::textChanged,								this,	&cCharacterWindow::onSpokenLanguagesChanged);
	connect(ui->m_lpJob,				&cTextEdit::textChanged,								this,	&cCharacterWindow::onJobChanged);
	connect(ui->m_lpDescription,		&cTextEdit::textChanged,								this,	&cCharacterWindow::onDescriptionChanged);
}

cCharacter* cCharacterWindow::character()
{
	return(m_lpCharacter);
}

void cCharacterWindow::retranslateUI()
{
	ui->retranslateUi(this);
	setWindowTitle(windowTitle() + m_lpCharacter->name());
}

void cCharacterWindow::onFirstNameChanged(const QString& szText)
{
	m_lpCharacter->setFirstName(szText);

	nameChanged();

	m_lpMainWindow->somethingChanged();
}

void cCharacterWindow::onMiddleNameChanged(const QString& szText)
{
	m_lpCharacter->setMiddleName(szText);

	nameChanged();

	m_lpMainWindow->somethingChanged();
}

void cCharacterWindow::onLastNameChanged(const QString& szText)
{
	m_lpCharacter->setLastName(szText);

	nameChanged();

	m_lpMainWindow->somethingChanged();
}

void cCharacterWindow::nameChanged()
{
	QList<QStandardItem*>	items	= m_lpCharacter->item();

	if(items.count())
		items[0]->setText(m_lpCharacter->name());
}

void cCharacterWindow::onNickNameChanged(const QString& szText)
{
	m_lpCharacter->setNickName(szText);
	m_lpMainWindow->somethingChanged();
}

void cCharacterWindow::onMainCharacterClicked(bool bChecked)
{
	m_lpCharacter->setMainCharacter(bChecked);

	QList<QStandardItem*>	items	= m_lpCharacter->item();

	if(items.count())
	{
		QFont				font	= items[0]->font();

		if(bChecked)
		{
			font.setBold(true);
			font.setItalic(false);
		}
		else
		{
			font.setBold(false);
			font.setItalic(true);
		}

		for(int x = 0;x < items.count();x++)
			items[x]->setFont(font);
	}

	m_lpMainWindow->somethingChanged();
}

void cCharacterWindow::onCreatureChanged(const QString& szText)
{
	m_lpCharacter->setCreature(szText);

	QList<QStandardItem*>	items	= m_lpCharacter->item();

	if(items.count() >= 2)
		items[1]->setText(szText);

	m_lpMainWindow->somethingChanged();
}

void cCharacterWindow::onGenderMaleClicked(bool /*bChecked*/)
{
	if(ui->m_lpMale->isChecked())
		m_lpCharacter->setGender(cCharacter::GENDER_male);
	else if(ui->m_lpFemale->isChecked())
		m_lpCharacter->setGender(cCharacter::GENDER_female);
	else
		m_lpCharacter->setGender(cCharacter::GENDER_undefined);

	genderChanged();

	m_lpMainWindow->somethingChanged();
}

void cCharacterWindow::onGenderFemaleClicked(bool /*bChecked*/)
{
	if(ui->m_lpMale->isChecked())
		m_lpCharacter->setGender(cCharacter::GENDER_male);
	else if(ui->m_lpFemale->isChecked())
		m_lpCharacter->setGender(cCharacter::GENDER_female);
	else
		m_lpCharacter->setGender(cCharacter::GENDER_undefined);

	genderChanged();

	m_lpMainWindow->somethingChanged();
}

void cCharacterWindow::onGenderOtherClicked(bool /*bChecked*/)
{
	if(ui->m_lpMale->isChecked())
		m_lpCharacter->setGender(cCharacter::GENDER_male);
	else if(ui->m_lpFemale->isChecked())
		m_lpCharacter->setGender(cCharacter::GENDER_female);
	else
		m_lpCharacter->setGender(cCharacter::GENDER_undefined);

	genderChanged();

	m_lpMainWindow->somethingChanged();
}

void cCharacterWindow::genderChanged()
{
	QList<QStandardItem*>	items	= m_lpCharacter->item();

	if(items.count() >= 3)
		items[2]->setText(m_lpCharacter->genderText());
}

void cCharacterWindow::onTitleChanged(const QString& szText)
{
	m_lpCharacter->setTitle(szText);
	m_lpMainWindow->somethingChanged();
}

void cCharacterWindow::onDateOfBirthChanged(const QDate& date)
{
	m_lpCharacter->setDateOfBirth(date);
	m_lpMainWindow->somethingChanged();
}

void cCharacterWindow::onDateOfDeathChanged(const QDate& date)
{
	m_lpCharacter->setDateOfDeath(date);
	m_lpMainWindow->somethingChanged();
}

void cCharacterWindow::onPlaceOfBirthChanged(const QString& szText)
{
	m_lpCharacter->setPlaceOfBirth(szText);
	m_lpMainWindow->somethingChanged();
}

void cCharacterWindow::onPlaceOfDeathChanged(const QString& szText)
{
	m_lpCharacter->setPlaceOfDeath(szText);
	m_lpMainWindow->somethingChanged();
}

void cCharacterWindow::onHeightChanged(double d)
{
	m_lpCharacter->setHeight(d);
	m_lpMainWindow->somethingChanged();
}

void cCharacterWindow::onWeightChanged(double d)
{
	m_lpCharacter->setWeight(d);
	m_lpMainWindow->somethingChanged();
}

void cCharacterWindow::onFigureChanged(const QString& szText)
{
	m_lpCharacter->setFigure(szText);
	m_lpMainWindow->somethingChanged();
}

void cCharacterWindow::onSkinChanged(const QString& szText)
{
	m_lpCharacter->setSkin(szText);
	m_lpMainWindow->somethingChanged();
}

void cCharacterWindow::onNatureChanged(const QString& szText)
{
	m_lpCharacter->setNature(szText);
	m_lpMainWindow->somethingChanged();
}

void cCharacterWindow::onHairColorChanged(const QString& szText)
{
	m_lpCharacter->setHairColor(szText);
	m_lpMainWindow->somethingChanged();
}

void cCharacterWindow::onHairCutChanged(const QString& szText)
{
	m_lpCharacter->setHairCut(szText);
	m_lpMainWindow->somethingChanged();
}

void cCharacterWindow::onHairLengthChanged(const QString& szText)
{
	m_lpCharacter->setHairLength(szText);
	m_lpMainWindow->somethingChanged();
}

void cCharacterWindow::onSchoolChanged()
{
	m_lpMainWindow->somethingChanged();
}

void cCharacterWindow::onSpokenLanguagesChanged()
{
	m_lpMainWindow->somethingChanged();
}

void cCharacterWindow::onJobChanged()
{
	m_lpMainWindow->somethingChanged();
}

void cCharacterWindow::onDescriptionChanged()
{
	m_lpMainWindow->somethingChanged();
}
