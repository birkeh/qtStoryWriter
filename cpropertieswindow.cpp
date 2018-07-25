#include "cpropertieswindow.h"
#include "ui_cpropertieswindow.h"

#include "cmainwindow.h"

#include "common.h"


cPropertiesWindow::cPropertiesWindow(QWidget *parent) :
	cMDISubWindow(parent),
	ui(new Ui::cPropertiesWindow),
	m_lpMainWindow((cMainWindow*)parent),
	m_lpStoryBook(0)
{
	ui->setupUi(this);
	ui->m_lpTab->setCurrentIndex(0);

	QMap<QPagedPaintDevice::PageSize, QString>				paperLst	= paperList();
	QMap<QPagedPaintDevice::PageSize, QString>::iterator	i;

	for(i = paperLst.begin();i != paperLst.end();i++)
		ui->m_lpPaperSize->addItem(i.value(), QVariant::fromValue((int)i.key()));

	QMap<QPageLayout::Unit, QString>						unitLst		= unitList();
	QMap<QPageLayout::Unit, QString>::iterator				iUnit;

	for(iUnit = unitLst.begin();iUnit != unitLst.end();iUnit++)
		ui->m_lpUnit->addItem(iUnit.value(), QVariant::fromValue((int)iUnit.key()));

	fillFontSize(ui->m_lpAuthorFontSize);
	fillFontSize(ui->m_lpChapterNameFontSize);
	fillFontSize(ui->m_lpPartNameFontSize);
	fillFontSize(ui->m_lpSceneNameFontSize);
	fillFontSize(ui->m_lpSubtitleFontSize);
	fillFontSize(ui->m_lpTitleFontSize);

	connect(ui->m_lpTitle,						&cLineEdit::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onLineEditGotFocus);
	connect(ui->m_lpTitle,						&cLineEdit::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onLineEditLostFocus);

	connect(ui->m_lpSubTitle,					&cLineEdit::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onLineEditGotFocus);
	connect(ui->m_lpSubTitle,					&cLineEdit::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onLineEditLostFocus);

	connect(ui->m_lpAuthor,						&cLineEdit::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onLineEditGotFocus);
	connect(ui->m_lpAuthor,						&cLineEdit::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onLineEditLostFocus);

	connect(ui->m_lpStartedAt,					&cDateTimeEdit::gotFocus,	(cMainWindow*)parent,	&cMainWindow::onDateTimeEditGotFocus);
	connect(ui->m_lpStartedAt,					&cDateTimeEdit::lostFocus,	(cMainWindow*)parent,	&cMainWindow::onDateTimeEditLostFocus);

	connect(ui->m_lpFinishedAt,					&cDateTimeEdit::gotFocus,	(cMainWindow*)parent,	&cMainWindow::onDateTimeEditGotFocus);
	connect(ui->m_lpFinishedAt,					&cDateTimeEdit::lostFocus,	(cMainWindow*)parent,	&cMainWindow::onDateTimeEditLostFocus);

	connect(ui->m_lpTargetDate,					&cDateTimeEdit::gotFocus,	(cMainWindow*)parent,	&cMainWindow::onDateTimeEditGotFocus);
	connect(ui->m_lpTargetDate,					&cDateTimeEdit::lostFocus,	(cMainWindow*)parent,	&cMainWindow::onDateTimeEditLostFocus);

	connect(ui->m_lpShortDescription,			&cTextEdit::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onTextEditGotFocus);
	connect(ui->m_lpShortDescription,			&cTextEdit::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onTextEditLostFocus);

	connect(ui->m_lpDescription,				&cTextEdit::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onTextEditGotFocus);
	connect(ui->m_lpDescription,				&cTextEdit::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onTextEditLostFocus);

	connect(ui->m_lpPrintTitle,					&cCheckBox::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxGotFocus);
	connect(ui->m_lpPrintTitle,					&cCheckBox::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxLostFocus);

	connect(ui->m_lpTitleFont,					&cFontComboBox::gotFocus,	(cMainWindow*)parent,	&cMainWindow::onFontComboBoxGotFocus);
	connect(ui->m_lpTitleFont,					&cFontComboBox::lostFocus,	(cMainWindow*)parent,	&cMainWindow::onFontComboBoxLostFocus);

	connect(ui->m_lpTitleFontSize,				&cComboBox::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onComboBoxGotFocus);
	connect(ui->m_lpTitleFontSize,				&cComboBox::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onComboBoxLostFocus);

	connect(ui->m_lpTitleBold,					&cCheckBox::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxGotFocus);
	connect(ui->m_lpTitleBold,					&cCheckBox::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxLostFocus);

	connect(ui->m_lpTitleItalic,				&cCheckBox::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxGotFocus);
	connect(ui->m_lpTitleItalic,				&cCheckBox::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxLostFocus);

	connect(ui->m_lpTitleUnderline,				&cCheckBox::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxGotFocus);
	connect(ui->m_lpTitleUnderline,				&cCheckBox::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxLostFocus);

	connect(ui->m_lpTitleLeft,					&cRadioButton::gotFocus,	(cMainWindow*)parent,	&cMainWindow::onRadioButtonGotFocus);
	connect(ui->m_lpTitleLeft,					&cRadioButton::lostFocus,	(cMainWindow*)parent,	&cMainWindow::onRadioButtonLostFocus);

	connect(ui->m_lpTitleCenter,				&cRadioButton::gotFocus,	(cMainWindow*)parent,	&cMainWindow::onRadioButtonGotFocus);
	connect(ui->m_lpTitleCenter,				&cRadioButton::lostFocus,	(cMainWindow*)parent,	&cMainWindow::onRadioButtonLostFocus);

	connect(ui->m_lpTitleRight,					&cRadioButton::gotFocus,	(cMainWindow*)parent,	&cMainWindow::onRadioButtonGotFocus);
	connect(ui->m_lpTitleRight,					&cRadioButton::lostFocus,	(cMainWindow*)parent,	&cMainWindow::onRadioButtonLostFocus);

	connect(ui->m_lpPrintSubtitle,				&cCheckBox::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxGotFocus);
	connect(ui->m_lpPrintSubtitle,				&cCheckBox::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxLostFocus);

	connect(ui->m_lpSubtitleFont,				&cFontComboBox::gotFocus,	(cMainWindow*)parent,	&cMainWindow::onFontComboBoxGotFocus);
	connect(ui->m_lpSubtitleFont,				&cFontComboBox::lostFocus,	(cMainWindow*)parent,	&cMainWindow::onFontComboBoxLostFocus);

	connect(ui->m_lpSubtitleFontSize,			&cComboBox::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onComboBoxGotFocus);
	connect(ui->m_lpSubtitleFontSize,			&cComboBox::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onComboBoxLostFocus);

	connect(ui->m_lpSubtitleBold,				&cCheckBox::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxGotFocus);
	connect(ui->m_lpSubtitleBold,				&cCheckBox::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxLostFocus);

	connect(ui->m_lpSubtitleItalic,				&cCheckBox::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxGotFocus);
	connect(ui->m_lpSubtitleItalic,				&cCheckBox::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxLostFocus);

	connect(ui->m_lpSubtitleUnderline,			&cCheckBox::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxGotFocus);
	connect(ui->m_lpSubtitleUnderline,			&cCheckBox::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxLostFocus);

	connect(ui->m_lpSubtitleLeft,				&cRadioButton::gotFocus,	(cMainWindow*)parent,	&cMainWindow::onRadioButtonGotFocus);
	connect(ui->m_lpSubtitleLeft,				&cRadioButton::lostFocus,	(cMainWindow*)parent,	&cMainWindow::onRadioButtonLostFocus);

	connect(ui->m_lpSubtitleCenter,				&cRadioButton::gotFocus,	(cMainWindow*)parent,	&cMainWindow::onRadioButtonGotFocus);
	connect(ui->m_lpSubtitleCenter,				&cRadioButton::lostFocus,	(cMainWindow*)parent,	&cMainWindow::onRadioButtonLostFocus);

	connect(ui->m_lpSubtitleRight,				&cRadioButton::gotFocus,	(cMainWindow*)parent,	&cMainWindow::onRadioButtonGotFocus);
	connect(ui->m_lpSubtitleRight,				&cRadioButton::lostFocus,	(cMainWindow*)parent,	&cMainWindow::onRadioButtonLostFocus);

	connect(ui->m_lpPrintShortDescription,		&cCheckBox::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxGotFocus);
	connect(ui->m_lpPrintShortDescription,		&cCheckBox::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxLostFocus);

	connect(ui->m_lpPrintDescription,			&cCheckBox::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxGotFocus);
	connect(ui->m_lpPrintDescription,			&cCheckBox::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxLostFocus);

	connect(ui->m_lpPrintAuthor,				&cCheckBox::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxGotFocus);
	connect(ui->m_lpPrintAuthor,				&cCheckBox::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxLostFocus);

	connect(ui->m_lpAuthorFont,					&cFontComboBox::gotFocus,	(cMainWindow*)parent,	&cMainWindow::onFontComboBoxGotFocus);
	connect(ui->m_lpAuthorFont,					&cFontComboBox::lostFocus,	(cMainWindow*)parent,	&cMainWindow::onFontComboBoxLostFocus);

	connect(ui->m_lpAuthorFontSize,				&cComboBox::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onComboBoxGotFocus);
	connect(ui->m_lpAuthorFontSize,				&cComboBox::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onComboBoxLostFocus);

	connect(ui->m_lpAuthorBold,					&cCheckBox::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxGotFocus);
	connect(ui->m_lpAuthorBold,					&cCheckBox::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxLostFocus);

	connect(ui->m_lpAuthorItalic,				&cCheckBox::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxGotFocus);
	connect(ui->m_lpAuthorItalic,				&cCheckBox::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxLostFocus);

	connect(ui->m_lpAuthorUnderline,			&cCheckBox::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxGotFocus);
	connect(ui->m_lpAuthorUnderline,			&cCheckBox::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxLostFocus);

	connect(ui->m_lpAuthorLeft,					&cRadioButton::gotFocus,	(cMainWindow*)parent,	&cMainWindow::onRadioButtonGotFocus);
	connect(ui->m_lpAuthorLeft,					&cRadioButton::lostFocus,	(cMainWindow*)parent,	&cMainWindow::onRadioButtonLostFocus);

	connect(ui->m_lpAuthorCenter,				&cRadioButton::gotFocus,	(cMainWindow*)parent,	&cMainWindow::onRadioButtonGotFocus);
	connect(ui->m_lpAuthorCenter,				&cRadioButton::lostFocus,	(cMainWindow*)parent,	&cMainWindow::onRadioButtonLostFocus);

	connect(ui->m_lpAuthorRight,				&cRadioButton::gotFocus,	(cMainWindow*)parent,	&cMainWindow::onRadioButtonGotFocus);
	connect(ui->m_lpAuthorRight,				&cRadioButton::lostFocus,	(cMainWindow*)parent,	&cMainWindow::onRadioButtonLostFocus);

	connect(ui->m_lpPrintPartName,				&cCheckBox::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxGotFocus);
	connect(ui->m_lpPrintPartName,				&cCheckBox::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxLostFocus);

	connect(ui->m_lpPartNameFont,				&cFontComboBox::gotFocus,	(cMainWindow*)parent,	&cMainWindow::onFontComboBoxGotFocus);
	connect(ui->m_lpPartNameFont,				&cFontComboBox::lostFocus,	(cMainWindow*)parent,	&cMainWindow::onFontComboBoxLostFocus);

	connect(ui->m_lpPartNameFontSize,			&cComboBox::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onComboBoxGotFocus);
	connect(ui->m_lpPartNameFontSize,			&cComboBox::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onComboBoxLostFocus);

	connect(ui->m_lpPartNameBold,				&cCheckBox::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxGotFocus);
	connect(ui->m_lpPartNameBold,				&cCheckBox::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxLostFocus);

	connect(ui->m_lpPartNameItalic,				&cCheckBox::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxGotFocus);
	connect(ui->m_lpPartNameItalic,				&cCheckBox::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxLostFocus);

	connect(ui->m_lpPartNameUnderline,			&cCheckBox::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxGotFocus);
	connect(ui->m_lpPartNameUnderline,			&cCheckBox::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxLostFocus);

	connect(ui->m_lpPartNameLeft,				&cRadioButton::gotFocus,	(cMainWindow*)parent,	&cMainWindow::onRadioButtonGotFocus);
	connect(ui->m_lpPartNameLeft,				&cRadioButton::lostFocus,	(cMainWindow*)parent,	&cMainWindow::onRadioButtonLostFocus);

	connect(ui->m_lpPartNameCenter,				&cRadioButton::gotFocus,	(cMainWindow*)parent,	&cMainWindow::onRadioButtonGotFocus);
	connect(ui->m_lpPartNameCenter,				&cRadioButton::lostFocus,	(cMainWindow*)parent,	&cMainWindow::onRadioButtonLostFocus);

	connect(ui->m_lpPartNameRight,				&cRadioButton::gotFocus,	(cMainWindow*)parent,	&cMainWindow::onRadioButtonGotFocus);
	connect(ui->m_lpPartNameRight,				&cRadioButton::lostFocus,	(cMainWindow*)parent,	&cMainWindow::onRadioButtonLostFocus);

	connect(ui->m_lpPrintPartDescription,		&cCheckBox::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxGotFocus);
	connect(ui->m_lpPrintPartDescription,		&cCheckBox::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxLostFocus);

	connect(ui->m_lpPrintPartText,				&cCheckBox::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxGotFocus);
	connect(ui->m_lpPrintPartText,				&cCheckBox::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxLostFocus);

	connect(ui->m_lpPrintChapterName,			&cCheckBox::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxGotFocus);
	connect(ui->m_lpPrintChapterName,			&cCheckBox::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxLostFocus);

	connect(ui->m_lpChapterNameFont,			&cFontComboBox::gotFocus,	(cMainWindow*)parent,	&cMainWindow::onFontComboBoxGotFocus);
	connect(ui->m_lpChapterNameFont,			&cFontComboBox::lostFocus,	(cMainWindow*)parent,	&cMainWindow::onFontComboBoxLostFocus);

	connect(ui->m_lpChapterNameFontSize,		&cComboBox::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onComboBoxGotFocus);
	connect(ui->m_lpChapterNameFontSize,		&cComboBox::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onComboBoxLostFocus);

	connect(ui->m_lpChapterNameBold,			&cCheckBox::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxGotFocus);
	connect(ui->m_lpChapterNameBold,			&cCheckBox::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxLostFocus);

	connect(ui->m_lpChapterNameItalic,			&cCheckBox::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxGotFocus);
	connect(ui->m_lpChapterNameItalic,			&cCheckBox::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxLostFocus);

	connect(ui->m_lpChapterNameUnderline,		&cCheckBox::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxGotFocus);
	connect(ui->m_lpChapterNameUnderline,		&cCheckBox::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxLostFocus);

	connect(ui->m_lpChapterNameLeft,			&cRadioButton::gotFocus,	(cMainWindow*)parent,	&cMainWindow::onRadioButtonGotFocus);
	connect(ui->m_lpChapterNameLeft,			&cRadioButton::lostFocus,	(cMainWindow*)parent,	&cMainWindow::onRadioButtonLostFocus);

	connect(ui->m_lpChapterNameCenter,			&cRadioButton::gotFocus,	(cMainWindow*)parent,	&cMainWindow::onRadioButtonGotFocus);
	connect(ui->m_lpChapterNameCenter,			&cRadioButton::lostFocus,	(cMainWindow*)parent,	&cMainWindow::onRadioButtonLostFocus);

	connect(ui->m_lpChapterNameRight,			&cRadioButton::gotFocus,	(cMainWindow*)parent,	&cMainWindow::onRadioButtonGotFocus);
	connect(ui->m_lpChapterNameRight,			&cRadioButton::lostFocus,	(cMainWindow*)parent,	&cMainWindow::onRadioButtonLostFocus);

	connect(ui->m_lpPrintChapterDescription,	&cCheckBox::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxGotFocus);
	connect(ui->m_lpPrintChapterDescription,	&cCheckBox::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxLostFocus);

	connect(ui->m_lpPrintChapterText,			&cCheckBox::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxGotFocus);
	connect(ui->m_lpPrintChapterText,			&cCheckBox::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxLostFocus);

	connect(ui->m_lpPrintSceneName,				&cCheckBox::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxGotFocus);
	connect(ui->m_lpPrintSceneName,				&cCheckBox::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxLostFocus);

	connect(ui->m_lpSceneNameFont,				&cFontComboBox::gotFocus,	(cMainWindow*)parent,	&cMainWindow::onFontComboBoxGotFocus);
	connect(ui->m_lpSceneNameFont,				&cFontComboBox::lostFocus,	(cMainWindow*)parent,	&cMainWindow::onFontComboBoxLostFocus);

	connect(ui->m_lpSceneNameFontSize,			&cComboBox::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onComboBoxGotFocus);
	connect(ui->m_lpSceneNameFontSize,			&cComboBox::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onComboBoxLostFocus);

	connect(ui->m_lpSceneNameBold,				&cCheckBox::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxGotFocus);
	connect(ui->m_lpSceneNameBold,				&cCheckBox::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxLostFocus);

	connect(ui->m_lpSceneNameItalic,			&cCheckBox::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxGotFocus);
	connect(ui->m_lpSceneNameItalic,			&cCheckBox::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxLostFocus);

	connect(ui->m_lpSceneNameUnderline,			&cCheckBox::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxGotFocus);
	connect(ui->m_lpSceneNameUnderline,			&cCheckBox::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxLostFocus);

	connect(ui->m_lpSceneNameLeft,				&cRadioButton::gotFocus,	(cMainWindow*)parent,	&cMainWindow::onRadioButtonGotFocus);
	connect(ui->m_lpSceneNameLeft,				&cRadioButton::lostFocus,	(cMainWindow*)parent,	&cMainWindow::onRadioButtonLostFocus);

	connect(ui->m_lpSceneNameCenter,			&cRadioButton::gotFocus,	(cMainWindow*)parent,	&cMainWindow::onRadioButtonGotFocus);
	connect(ui->m_lpSceneNameCenter,			&cRadioButton::lostFocus,	(cMainWindow*)parent,	&cMainWindow::onRadioButtonLostFocus);

	connect(ui->m_lpSceneNameRight,				&cRadioButton::gotFocus,	(cMainWindow*)parent,	&cMainWindow::onRadioButtonGotFocus);
	connect(ui->m_lpSceneNameRight,				&cRadioButton::lostFocus,	(cMainWindow*)parent,	&cMainWindow::onRadioButtonLostFocus);

	connect(ui->m_lpPrintSceneDescription,		&cCheckBox::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxGotFocus);
	connect(ui->m_lpPrintSceneDescription,		&cCheckBox::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxLostFocus);

	connect(ui->m_lpPrintSceneText,				&cCheckBox::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxGotFocus);
	connect(ui->m_lpPrintSceneText,				&cCheckBox::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onCheckBoxLostFocus);

	connect(ui->m_lpPaperSize,					&cComboBox::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onComboBoxGotFocus);
	connect(ui->m_lpPaperSize,					&cComboBox::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onComboBoxLostFocus);

	connect(ui->m_lpOrientationPortrait,		&cRadioButton::gotFocus,	(cMainWindow*)parent,	&cMainWindow::onRadioButtonGotFocus);
	connect(ui->m_lpOrientationPortrait,		&cRadioButton::lostFocus,	(cMainWindow*)parent,	&cMainWindow::onRadioButtonLostFocus);

	connect(ui->m_lpOrientationLandscape,		&cRadioButton::gotFocus,	(cMainWindow*)parent,	&cMainWindow::onRadioButtonGotFocus);
	connect(ui->m_lpOrientationLandscape,		&cRadioButton::lostFocus,	(cMainWindow*)parent,	&cMainWindow::onRadioButtonLostFocus);

	connect(ui->m_lpUnit,						&cComboBox::gotFocus,		(cMainWindow*)parent,	&cMainWindow::onComboBoxGotFocus);
	connect(ui->m_lpUnit,						&cComboBox::lostFocus,		(cMainWindow*)parent,	&cMainWindow::onComboBoxLostFocus);

	connect(ui->m_lpMarginLeft,					&cDoubleSpinBox::gotFocus,	(cMainWindow*)parent,	&cMainWindow::onDoubleSpinBoxGotFocus);
	connect(ui->m_lpMarginLeft,					&cDoubleSpinBox::lostFocus,	(cMainWindow*)parent,	&cMainWindow::onDoubleSpinBoxLostFocus);

	connect(ui->m_lpMarginRight,				&cDoubleSpinBox::gotFocus,	(cMainWindow*)parent,	&cMainWindow::onDoubleSpinBoxGotFocus);
	connect(ui->m_lpMarginRight,				&cDoubleSpinBox::lostFocus,	(cMainWindow*)parent,	&cMainWindow::onDoubleSpinBoxLostFocus);

	connect(ui->m_lpMarginTop,					&cDoubleSpinBox::gotFocus,	(cMainWindow*)parent,	&cMainWindow::onDoubleSpinBoxGotFocus);
	connect(ui->m_lpMarginTop,					&cDoubleSpinBox::lostFocus,	(cMainWindow*)parent,	&cMainWindow::onDoubleSpinBoxLostFocus);

	connect(ui->m_lpMarginBottom,				&cDoubleSpinBox::gotFocus,	(cMainWindow*)parent,	&cMainWindow::onDoubleSpinBoxGotFocus);
	connect(ui->m_lpMarginBottom,				&cDoubleSpinBox::lostFocus,	(cMainWindow*)parent,	&cMainWindow::onDoubleSpinBoxLostFocus);
}

cPropertiesWindow::~cPropertiesWindow()
{
	delete ui;
}

void setAlign(ALIGN align, cRadioButton* lpLeft, cRadioButton* lpCenter, cRadioButton* lpRight)
{
	switch(align)
	{
	case ALIGN_left:
		lpLeft->setChecked(true);
		break;
	case ALIGN_center:
		lpCenter->setChecked(true);
		break;
	case ALIGN_right:
		lpRight->setChecked(true);
		break;
	case ALIGN_block:
		break;
	}
}

void cPropertiesWindow::setBook(cStoryBook *lpStoryBook)
{
	m_lpStoryBook	= lpStoryBook;

	ui->m_lpTitle->setText(lpStoryBook->book()->title());
	ui->m_lpSubTitle->setText(lpStoryBook->book()->subTitle());
	ui->m_lpAuthor->setText(lpStoryBook->book()->author());
	ui->m_lpStartedAt->setDateTime(lpStoryBook->book()->startedAt());
	ui->m_lpFinishedAt->setDateTime(lpStoryBook->book()->finishedAt());
	ui->m_lpTargetDate->setDateTime(lpStoryBook->book()->targetDate());
	ui->m_lpShortDescription->setDocument(lpStoryBook->book()->shortDescription());
	ui->m_lpDescription->setDocument(lpStoryBook->book()->description());

	ui->m_lpPrintTitle->setChecked(lpStoryBook->printTitle());
	ui->m_lpTitleFont->setCurrentText(lpStoryBook->titleFont());
	ui->m_lpTitleFontSize->setCurrentText(QString("%1").arg(lpStoryBook->titleFontSize()));
	ui->m_lpTitleBold->setChecked(lpStoryBook->titleBold());
	ui->m_lpTitleItalic->setChecked(lpStoryBook->titleItalic());
	ui->m_lpTitleUnderline->setChecked(lpStoryBook->titleUnderline());
	setAlign(lpStoryBook->titleAlign(), ui->m_lpTitleLeft, ui->m_lpTitleCenter, ui->m_lpTitleRight);
	ui->m_lpPrintSubtitle->setChecked(lpStoryBook->printSubTitle());
	ui->m_lpSubtitleFont->setCurrentText(lpStoryBook->subtitleFont());
	ui->m_lpSubtitleFontSize->setCurrentText(QString("%1").arg(lpStoryBook->subtitleFontSize()));
	ui->m_lpSubtitleBold->setChecked(lpStoryBook->subtitleBold());
	ui->m_lpSubtitleItalic->setChecked(lpStoryBook->subtitleItalic());
	ui->m_lpSubtitleUnderline->setChecked(lpStoryBook->subtitleUnderline());
	setAlign(lpStoryBook->subtitleAlign(), ui->m_lpSubtitleLeft, ui->m_lpSubtitleCenter, ui->m_lpSubtitleRight);
	ui->m_lpPrintShortDescription->setChecked(lpStoryBook->printShortDescription());
	ui->m_lpPrintDescription->setChecked(lpStoryBook->printDescription());
	ui->m_lpPrintAuthor->setChecked(lpStoryBook->printAuthor());
	ui->m_lpAuthorFont->setCurrentText(lpStoryBook->authorFont());
	ui->m_lpAuthorFontSize->setCurrentText(QString("%1").arg(lpStoryBook->authorFontSize()));
	ui->m_lpAuthorBold->setChecked(lpStoryBook->authorBold());
	ui->m_lpAuthorItalic->setChecked(lpStoryBook->authorItalic());
	ui->m_lpAuthorUnderline->setChecked(lpStoryBook->authorUnderline());
	setAlign(lpStoryBook->authorAlign(), ui->m_lpAuthorLeft, ui->m_lpAuthorCenter, ui->m_lpAuthorRight);
	ui->m_lpPrintPartName->setChecked(lpStoryBook->printPartName());
	ui->m_lpPartNameFont->setCurrentText(lpStoryBook->partFont());
	ui->m_lpPartNameFontSize->setCurrentText(QString("%1").arg(lpStoryBook->partFontSize()));
	ui->m_lpPartNameBold->setChecked(lpStoryBook->partBold());
	ui->m_lpPartNameItalic->setChecked(lpStoryBook->partItalic());
	ui->m_lpPartNameUnderline->setChecked(lpStoryBook->partUnderline());
	setAlign(lpStoryBook->partAlign(), ui->m_lpPartNameLeft, ui->m_lpPartNameCenter, ui->m_lpPartNameRight);
	ui->m_lpPrintPartDescription->setChecked(lpStoryBook->printPartDescription());
	ui->m_lpPrintPartText->setChecked(lpStoryBook->printPartText());
	ui->m_lpPrintChapterName->setChecked(lpStoryBook->printChapterName());
	ui->m_lpChapterNameFont->setCurrentText(lpStoryBook->chapterFont());
	ui->m_lpChapterNameFontSize->setCurrentText(QString("%1").arg(lpStoryBook->chapterFontSize()));
	ui->m_lpChapterNameBold->setChecked(lpStoryBook->chapterBold());
	ui->m_lpChapterNameItalic->setChecked(lpStoryBook->chapterItalic());
	ui->m_lpChapterNameUnderline->setChecked(lpStoryBook->chapterUnderline());
	setAlign(lpStoryBook->chapterAlign(), ui->m_lpChapterNameLeft, ui->m_lpChapterNameCenter, ui->m_lpChapterNameRight);
	ui->m_lpPrintChapterDescription->setChecked(lpStoryBook->printChapterDescription());
	ui->m_lpPrintChapterText->setChecked(lpStoryBook->printChapterText());
	ui->m_lpPrintSceneName->setChecked(lpStoryBook->printSceneName());
	ui->m_lpSceneNameFont->setCurrentText(lpStoryBook->sceneFont());
	ui->m_lpSceneNameFontSize->setCurrentText(QString("%1").arg(lpStoryBook->sceneFontSize()));
	ui->m_lpSceneNameBold->setChecked(lpStoryBook->sceneBold());
	ui->m_lpSceneNameItalic->setChecked(lpStoryBook->sceneItalic());
	ui->m_lpSceneNameUnderline->setChecked(lpStoryBook->sceneUnderline());
	setAlign(lpStoryBook->sceneAlign(), ui->m_lpSceneNameLeft, ui->m_lpSceneNameCenter, ui->m_lpSceneNameRight);
	ui->m_lpPrintSceneDescription->setChecked(lpStoryBook->printSceneDescription());
	ui->m_lpPrintSceneText->setChecked(lpStoryBook->printSceneText());
	ui->m_lpPaperSize->setCurrentText(paperName(lpStoryBook->paperSize()));
	ui->m_lpOrientationPortrait->setChecked(lpStoryBook->paperOrientation() == QPrinter::Portrait);
	ui->m_lpOrientationLandscape->setChecked(lpStoryBook->paperOrientation() == QPrinter::Landscape);
	ui->m_lpUnit->setCurrentText(QString("%1").arg(lpStoryBook->unit()));
	ui->m_lpMarginLeft->setValue(lpStoryBook->leftMargin());
	ui->m_lpMarginRight->setValue(lpStoryBook->rightMargin());
	ui->m_lpMarginTop->setValue(lpStoryBook->topMargin());
	ui->m_lpMarginBottom->setValue(lpStoryBook->bottomMargin());

	enablePrintTitle(lpStoryBook->printTitle());
	enablePrintSubtitle(lpStoryBook->printSubTitle());
	enablePrintShortDescription(lpStoryBook->printShortDescription());
	enablePrintDescription(lpStoryBook->printDescription());
	enablePrintAuthor(lpStoryBook->printAuthor());
	enablePrintPartName(lpStoryBook->printPartName());
	enablePrintPartDescription(lpStoryBook->printPartDescription());
	enablePrintPartText(lpStoryBook->printPartText());
	enablePrintChapterName(lpStoryBook->printChapterName());
	enablePrintChapterDescription(lpStoryBook->printChapterDescription());
	enablePrintChapterText(lpStoryBook->printChapterText());
	enablePrintSceneName(lpStoryBook->printSceneName());
	enablePrintSceneDescription(lpStoryBook->printSceneDescription());
	enablePrintSceneText(lpStoryBook->printSceneText());

	connect(ui->m_lpTitle,						&cLineEdit::textChanged,								this,	&cPropertiesWindow::onTitleChanged);
	connect(ui->m_lpSubTitle,					&cLineEdit::textChanged,								this,	&cPropertiesWindow::onSubTitleChanged);
	connect(ui->m_lpAuthor,						&cLineEdit::textChanged,								this,	&cPropertiesWindow::onAuthorChanged);
	connect(ui->m_lpStartedAt,					&cDateTimeEdit::dateTimeChanged,						this,	&cPropertiesWindow::onStartedAtChanged);
	connect(ui->m_lpFinishedAt,					&cDateTimeEdit::dateTimeChanged,						this,	&cPropertiesWindow::onFinishedAtChanged);
	connect(ui->m_lpTargetDate,					&cDateTimeEdit::dateTimeChanged,						this,	&cPropertiesWindow::onTargetDateChanged);
	connect(ui->m_lpShortDescription,			&cTextEdit::textChanged,								this,	&cPropertiesWindow::onShortDescriptionChanged);
	connect(ui->m_lpDescription,				&cTextEdit::textChanged,								this,	&cPropertiesWindow::onDescriptionChanged);

	connect(ui->m_lpPrintTitle,					&cCheckBox::clicked,									this, &cPropertiesWindow::onPrintTitleChanged);
	connect(ui->m_lpTitleFont,					&cFontComboBox::currentTextChanged,						this, &cPropertiesWindow::onTitleFontChanged);
	connect(ui->m_lpTitleFontSize,				&cComboBox::currentTextChanged,							this, &cPropertiesWindow::onTitleFontSizeChanged);
	connect(ui->m_lpTitleBold,					&cCheckBox::clicked,									this, &cPropertiesWindow::onTitleBoldChanged);
	connect(ui->m_lpTitleItalic,				&cCheckBox::clicked,									this, &cPropertiesWindow::onTitleItalicChanged);
	connect(ui->m_lpTitleUnderline,				&cCheckBox::clicked,									this, &cPropertiesWindow::onTitleUnderlineChanged);
	connect(ui->m_lpTitleLeft,					&cRadioButton::clicked,									this, &cPropertiesWindow::onTitleLeftChanged);
	connect(ui->m_lpTitleCenter,				&cRadioButton::clicked,									this, &cPropertiesWindow::onTitleCenterChanged);
	connect(ui->m_lpTitleRight,					&cRadioButton::clicked,									this, &cPropertiesWindow::onTitleRightChanged);
	connect(ui->m_lpPrintSubtitle,				&cCheckBox::clicked,									this, &cPropertiesWindow::onPrintSubtitleChanged);
	connect(ui->m_lpSubtitleFont,				&cFontComboBox::currentTextChanged,						this, &cPropertiesWindow::onSubtitleFontChanged);
	connect(ui->m_lpSubtitleFontSize,			&cComboBox::currentTextChanged,							this, &cPropertiesWindow::onSubtitleFontSizeChanged);
	connect(ui->m_lpSubtitleBold,				&cCheckBox::clicked,									this, &cPropertiesWindow::onSubtitleBoldChanged);
	connect(ui->m_lpSubtitleItalic,				&cCheckBox::clicked,									this, &cPropertiesWindow::onSubtitleItalicChanged);
	connect(ui->m_lpSubtitleUnderline,			&cCheckBox::clicked,									this, &cPropertiesWindow::onSubtitleUnderlineChanged);
	connect(ui->m_lpSubtitleLeft,				&cRadioButton::clicked,									this, &cPropertiesWindow::onSubtitleLeftChanged);
	connect(ui->m_lpSubtitleCenter,				&cRadioButton::clicked,									this, &cPropertiesWindow::onSubtitleCenterChanged);
	connect(ui->m_lpSubtitleRight,				&cRadioButton::clicked,									this, &cPropertiesWindow::onSubtitleRightChanged);
	connect(ui->m_lpPrintShortDescription,		&cCheckBox::clicked,									this, &cPropertiesWindow::onPrintShortDescriptionChanged);
	connect(ui->m_lpPrintDescription,			&cCheckBox::clicked,									this, &cPropertiesWindow::onPrintDescriptionChanged);
	connect(ui->m_lpPrintAuthor,				&cCheckBox::clicked,									this, &cPropertiesWindow::onPrintAuthorChanged);
	connect(ui->m_lpAuthorFont,					&cFontComboBox::currentTextChanged,						this, &cPropertiesWindow::onAuthorFontChanged);
	connect(ui->m_lpAuthorFontSize,				&cComboBox::currentTextChanged,							this, &cPropertiesWindow::onAuthorFontSizeChanged);
	connect(ui->m_lpAuthorBold,					&cCheckBox::clicked,									this, &cPropertiesWindow::onAuthorBoldChanged);
	connect(ui->m_lpAuthorItalic,				&cCheckBox::clicked,									this, &cPropertiesWindow::onAuthorItalicChanged);
	connect(ui->m_lpAuthorUnderline,			&cCheckBox::clicked,									this, &cPropertiesWindow::onAuthorUnderlineChanged);
	connect(ui->m_lpAuthorLeft,					&cRadioButton::clicked,									this, &cPropertiesWindow::onAuthorLeftChanged);
	connect(ui->m_lpAuthorCenter,				&cRadioButton::clicked,									this, &cPropertiesWindow::onAuthorCenterChanged);
	connect(ui->m_lpAuthorRight,				&cRadioButton::clicked,									this, &cPropertiesWindow::onAuthorRightChanged);
	connect(ui->m_lpPrintPartName,				&cCheckBox::clicked,									this, &cPropertiesWindow::onPrintPartNameChanged);
	connect(ui->m_lpPartNameFont,				&cFontComboBox::currentTextChanged,						this, &cPropertiesWindow::onPartNameFontChanged);
	connect(ui->m_lpPartNameFontSize,			&cComboBox::currentTextChanged,							this, &cPropertiesWindow::onPartNameFontSizeChanged);
	connect(ui->m_lpPartNameBold,				&cCheckBox::clicked,									this, &cPropertiesWindow::onPartNameBoldChanged);
	connect(ui->m_lpPartNameItalic,				&cCheckBox::clicked,									this, &cPropertiesWindow::onPartNameItalicChanged);
	connect(ui->m_lpPartNameUnderline,			&cCheckBox::clicked,									this, &cPropertiesWindow::onPartNameUnderlineChanged);
	connect(ui->m_lpPartNameLeft,				&cRadioButton::clicked,									this, &cPropertiesWindow::onPartNameLeftChanged);
	connect(ui->m_lpPartNameCenter,				&cRadioButton::clicked,									this, &cPropertiesWindow::onPartNameCenterChanged);
	connect(ui->m_lpPartNameRight,				&cRadioButton::clicked,									this, &cPropertiesWindow::onPartNameRightChanged);
	connect(ui->m_lpPrintPartDescription,		&cCheckBox::clicked,									this, &cPropertiesWindow::onPrintPartDescriptionChanged);
	connect(ui->m_lpPrintPartText,				&cCheckBox::clicked,									this, &cPropertiesWindow::onPrintPartTextChanged);
	connect(ui->m_lpPrintChapterName,			&cCheckBox::clicked,									this, &cPropertiesWindow::onPrintChapterNameChanged);
	connect(ui->m_lpChapterNameFont,			&cFontComboBox::currentTextChanged,						this, &cPropertiesWindow::onChapterNameFontChanged);
	connect(ui->m_lpChapterNameFontSize,		&cComboBox::currentTextChanged,							this, &cPropertiesWindow::onChapterNameFontSizeChanged);
	connect(ui->m_lpChapterNameBold,			&cCheckBox::clicked,									this, &cPropertiesWindow::onChapterNameBoldChanged);
	connect(ui->m_lpChapterNameItalic,			&cCheckBox::clicked,									this, &cPropertiesWindow::onChapterNameItalicChanged);
	connect(ui->m_lpChapterNameUnderline,		&cCheckBox::clicked,									this, &cPropertiesWindow::onChapterNameUnderlineChanged);
	connect(ui->m_lpChapterNameLeft,			&cRadioButton::clicked,									this, &cPropertiesWindow::onChapterNameLeftChanged);
	connect(ui->m_lpChapterNameCenter,			&cRadioButton::clicked,									this, &cPropertiesWindow::onChapterNameCenterChanged);
	connect(ui->m_lpChapterNameRight,			&cRadioButton::clicked,									this, &cPropertiesWindow::onChapterNameRightChanged);
	connect(ui->m_lpPrintChapterDescription,	&cCheckBox::clicked,									this, &cPropertiesWindow::onPrintChapterDescriptionChanged);
	connect(ui->m_lpPrintChapterText,			&cCheckBox::clicked,									this, &cPropertiesWindow::onPrintChapterTextChanged);
	connect(ui->m_lpPrintSceneName,				&cCheckBox::clicked,									this, &cPropertiesWindow::onPrintSceneNameChanged);
	connect(ui->m_lpSceneNameFont,				&cFontComboBox::currentTextChanged,						this, &cPropertiesWindow::onSceneNameFontChanged);
	connect(ui->m_lpSceneNameFontSize,			&cComboBox::currentTextChanged,							this, &cPropertiesWindow::onSceneNameFontSizeChanged);
	connect(ui->m_lpSceneNameBold,				&cCheckBox::clicked,									this, &cPropertiesWindow::onSceneNameBoldChanged);
	connect(ui->m_lpSceneNameItalic,			&cCheckBox::clicked,									this, &cPropertiesWindow::onSceneNameItalicChanged);
	connect(ui->m_lpSceneNameUnderline,			&cCheckBox::clicked,									this, &cPropertiesWindow::onSceneNameUnderlineChanged);
	connect(ui->m_lpSceneNameLeft,				&cRadioButton::clicked,									this, &cPropertiesWindow::onSceneNameLeftChanged);
	connect(ui->m_lpSceneNameCenter,			&cRadioButton::clicked,									this, &cPropertiesWindow::onSceneNameCenterChanged);
	connect(ui->m_lpSceneNameRight,				&cRadioButton::clicked,									this, &cPropertiesWindow::onSceneNameRightChanged);
	connect(ui->m_lpPrintSceneDescription,		&cCheckBox::clicked,									this, &cPropertiesWindow::onPrintSceneDescriptionChanged);
	connect(ui->m_lpPrintSceneText,				&cCheckBox::clicked,									this, &cPropertiesWindow::onPrintSceneTextChanged);
	connect(ui->m_lpPaperSize,					&cComboBox::currentTextChanged,							this, &cPropertiesWindow::onPaperSizeChanged);
	connect(ui->m_lpOrientationPortrait,		&cRadioButton::clicked,									this, &cPropertiesWindow::onOrientationPortraitChanged);
	connect(ui->m_lpOrientationLandscape,		&cRadioButton::clicked,									this, &cPropertiesWindow::onOrientationLandscapeChanged);
	connect(ui->m_lpUnit,						&cComboBox::currentTextChanged,							this, &cPropertiesWindow::onUnitChanged);
	connect(ui->m_lpMarginLeft,					QOverload<double>::of(&cDoubleSpinBox::valueChanged),	this, &cPropertiesWindow::onMarginLeftChanged);
	connect(ui->m_lpMarginRight,				QOverload<double>::of(&cDoubleSpinBox::valueChanged),	this, &cPropertiesWindow::onMarginRightChanged);
	connect(ui->m_lpMarginTop,					QOverload<double>::of(&cDoubleSpinBox::valueChanged),	this, &cPropertiesWindow::onMarginTopChanged);
	connect(ui->m_lpMarginBottom,				QOverload<double>::of(&cDoubleSpinBox::valueChanged),	this, &cPropertiesWindow::onMarginBottomChanged);
}

cStoryBook* cPropertiesWindow::book()
{
	return(m_lpStoryBook);
}

void cPropertiesWindow::retranslateUI()
{
	ui->retranslateUi(this);
}

void cPropertiesWindow::onTitleChanged(const QString& szName)
{
	m_lpStoryBook->book()->setTitle(szName);
	m_lpMainWindow->somethingChanged();
	m_lpMainWindow->updateWindowTitle();
}

void cPropertiesWindow::onSubTitleChanged(const QString& szName)
{
	m_lpStoryBook->book()->setSubTitle(szName);
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onShortDescriptionChanged()
{
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onAuthorChanged(const QString& szName)
{
	m_lpStoryBook->book()->setAuthor(szName);
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onStartedAtChanged(const QDateTime& dateTime)
{
	m_lpStoryBook->book()->setStartedAt(dateTime);
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onFinishedAtChanged(const QDateTime& dateTime)
{
	m_lpStoryBook->book()->setFinishedAt(dateTime);
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onTargetDateChanged(const QDateTime& dateTime)
{
	m_lpStoryBook->book()->setTargetDate(dateTime);
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onDescriptionChanged()
{
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::fillFontSize(QComboBox* lpComboBox)
{
	lpComboBox->setEditable(true);

	const QList<int> standardSizes	= QFontDatabase::standardSizes();
	foreach(int size, standardSizes)
		lpComboBox->addItem(QString::number(size));
}

void cPropertiesWindow::onPrintTitleChanged(bool checked)
{
	m_lpStoryBook->setPrintTitle(checked);
	enablePrintTitle(checked);

	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onTitleFontChanged(const QString &text)
{
	m_lpStoryBook->setTitleFont(text);
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onTitleFontSizeChanged(const QString &text)
{
	m_lpStoryBook->setTitleFontSize(text.toInt());
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onTitleBoldChanged(bool checked)
{
	m_lpStoryBook->setTitleBold(checked);
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onTitleItalicChanged(bool checked)
{
	m_lpStoryBook->setTitleItalic(checked);
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onTitleUnderlineChanged(bool checked)
{
	m_lpStoryBook->setTitleUnderline(checked);
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onTitleLeftChanged(bool checked)
{
	if(checked)
		m_lpStoryBook->setTitleAlign(ALIGN_left);
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onTitleCenterChanged(bool checked)
{
	if(checked)
		m_lpStoryBook->setTitleAlign(ALIGN_center);
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onTitleRightChanged(bool checked)
{
	if(checked)
	m_lpStoryBook->setTitleAlign(ALIGN_right);
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onPrintSubtitleChanged(bool checked)
{
	m_lpStoryBook->setPrintSubTitle(checked);
	enablePrintSubtitle(checked);

	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onSubtitleFontChanged(const QString &text)
{
	m_lpStoryBook->setSubtitleFont(text);
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onSubtitleFontSizeChanged(const QString &text)
{
	m_lpStoryBook->setSubtitleFontSize(text.toInt());
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onSubtitleBoldChanged(bool checked)
{
	m_lpStoryBook->setSubtitleBold(checked);
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onSubtitleItalicChanged(bool checked)
{
	m_lpStoryBook->setSubtitleItalic(checked);
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onSubtitleUnderlineChanged(bool checked)
{
	m_lpStoryBook->setSubtitleUnderline(checked);
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onSubtitleLeftChanged(bool checked)
{
	if(checked)
		m_lpStoryBook->setSubtitleAlign(ALIGN_left);
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onSubtitleCenterChanged(bool checked)
{
	if(checked)
		m_lpStoryBook->setSubtitleAlign(ALIGN_center);
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onSubtitleRightChanged(bool checked)
{
	if(checked)
		m_lpStoryBook->setSubtitleAlign(ALIGN_right);
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onPrintShortDescriptionChanged(bool checked)
{
	m_lpStoryBook->setPrintShortDescription(checked);
	enablePrintShortDescription(checked);

	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onPrintDescriptionChanged(bool checked)
{
	m_lpStoryBook->setPrintDescription(checked);
	enablePrintDescription(checked);

	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onPrintAuthorChanged(bool checked)
{
	m_lpStoryBook->setPrintAuthor(checked);
	enablePrintAuthor(checked);

	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onAuthorFontChanged(const QString &text)
{
	m_lpStoryBook->setAuthorFont(text);
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onAuthorFontSizeChanged(const QString &text)
{
	m_lpStoryBook->setAuthorFontSize(text.toInt());
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onAuthorBoldChanged(bool checked)
{
	m_lpStoryBook->setAuthorBold(checked);
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onAuthorItalicChanged(bool checked)
{
	m_lpStoryBook->setAuthorItalic(checked);
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onAuthorUnderlineChanged(bool checked)
{
	m_lpStoryBook->setAuthorUnderline(checked);
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onAuthorLeftChanged(bool checked)
{
	if(checked)
		m_lpStoryBook->setAuthorAlign(ALIGN_left);
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onAuthorCenterChanged(bool checked)
{
	if(checked)
		m_lpStoryBook->setAuthorAlign(ALIGN_center);
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onAuthorRightChanged(bool checked)
{
	if(checked)
		m_lpStoryBook->setAuthorAlign(ALIGN_right);
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onPrintPartNameChanged(bool checked)
{
	m_lpStoryBook->setPrintPartName(checked);
	enablePrintPartName(checked);

	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onPartNameFontChanged(const QString &text)
{
	m_lpStoryBook->setPartFont(text);
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onPartNameFontSizeChanged(const QString &text)
{
	m_lpStoryBook->setPartFontSize(text.toInt());
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onPartNameBoldChanged(bool checked)
{
	m_lpStoryBook->setPartBold(checked);
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onPartNameItalicChanged(bool checked)
{
	m_lpStoryBook->setPartItalic(checked);
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onPartNameUnderlineChanged(bool checked)
{
	m_lpStoryBook->setPartUnderline(checked);
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onPartNameLeftChanged(bool checked)
{
	if(checked)
		m_lpStoryBook->setPartAlign(ALIGN_left);
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onPartNameCenterChanged(bool checked)
{
	if(checked)
		m_lpStoryBook->setPartAlign(ALIGN_center);
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onPartNameRightChanged(bool checked)
{
	if(checked)
		m_lpStoryBook->setPartAlign(ALIGN_right);
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onPrintPartDescriptionChanged(bool checked)
{
	m_lpStoryBook->setPrintPartDescription(checked);
	enablePrintPartDescription(checked);

	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onPrintPartTextChanged(bool checked)
{
	m_lpStoryBook->setPrintPartText(checked);
	enablePrintPartText(checked);

	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onPrintChapterNameChanged(bool checked)
{
	m_lpStoryBook->setPrintChapterName(checked);
	enablePrintChapterName(checked);

	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onChapterNameFontChanged(const QString &text)
{
	m_lpStoryBook->setChapterFont(text);
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onChapterNameFontSizeChanged(const QString &text)
{
	m_lpStoryBook->setChapterFontSize(text.toInt());
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onChapterNameBoldChanged(bool checked)
{
	m_lpStoryBook->setChapterBold(checked);
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onChapterNameItalicChanged(bool checked)
{
	m_lpStoryBook->setChapterItalic(checked);
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onChapterNameUnderlineChanged(bool checked)
{
	m_lpStoryBook->setChapterUnderline(checked);
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onChapterNameLeftChanged(bool checked)
{
	if(checked)
		m_lpStoryBook->setChapterAlign(ALIGN_left);
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onChapterNameCenterChanged(bool checked)
{
	if(checked)
		m_lpStoryBook->setChapterAlign(ALIGN_center);
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onChapterNameRightChanged(bool checked)
{
	if(checked)
		m_lpStoryBook->setChapterAlign(ALIGN_right);
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onPrintChapterDescriptionChanged(bool checked)
{
	m_lpStoryBook->setPrintChapterDescription(checked);
	enablePrintChapterDescription(checked);

	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onPrintChapterTextChanged(bool checked)
{
	m_lpStoryBook->setPrintChapterText(checked);
	enablePrintChapterText(checked);

	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onPrintSceneNameChanged(bool checked)
{
	m_lpStoryBook->setPrintSceneName(checked);
	enablePrintSceneName(checked);

	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onSceneNameFontChanged(const QString &text)
{
	m_lpStoryBook->setSceneFont(text);
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onSceneNameFontSizeChanged(const QString &text)
{
	m_lpStoryBook->setSceneFontSize(text.toInt());
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onSceneNameBoldChanged(bool checked)
{
	m_lpStoryBook->setSceneBold(checked);
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onSceneNameItalicChanged(bool checked)
{
	m_lpStoryBook->setSceneItalic(checked);
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onSceneNameUnderlineChanged(bool checked)
{
	m_lpStoryBook->setSceneUnderline(checked);
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onSceneNameLeftChanged(bool checked)
{
	if(checked)
		m_lpStoryBook->setSceneAlign(ALIGN_left);
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onSceneNameCenterChanged(bool checked)
{
	if(checked)
		m_lpStoryBook->setSceneAlign(ALIGN_center);
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onSceneNameRightChanged(bool checked)
{
	if(checked)
		m_lpStoryBook->setSceneAlign(ALIGN_right);
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onPrintSceneDescriptionChanged(bool checked)
{
	m_lpStoryBook->setPrintSceneDescription(checked);
	enablePrintSceneDescription(checked);

	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onPrintSceneTextChanged(bool checked)
{
	m_lpStoryBook->setPrintSceneText(checked);
	enablePrintSceneText(checked);

	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onPaperSizeChanged(const QString &text)
{
	m_lpStoryBook->setPaperSize(paperKey(text));
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onOrientationPortraitChanged(bool checked)
{
	if(checked)
		m_lpStoryBook->setPaperOrientation(QPrinter::Portrait);
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onOrientationLandscapeChanged(bool checked)
{
	if(checked)
		m_lpStoryBook->setPaperOrientation(QPrinter::Landscape);
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onUnitChanged(const QString &text)
{
	m_lpStoryBook->setUnit(unitKey(text));
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onMarginLeftChanged(double d)
{
	m_lpStoryBook->setLeftMargin(d);
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onMarginRightChanged(double d)
{
	m_lpStoryBook->setRightMargin(d);
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onMarginTopChanged(double d)
{
	m_lpStoryBook->setTopMargin(d);
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::onMarginBottomChanged(double d)
{
	m_lpStoryBook->setBottomMargin(d);
	m_lpMainWindow->somethingChanged();
}

void cPropertiesWindow::enablePrintTitle(bool enable)
{
	ui->m_lpTitleFont->setEnabled(enable);
	ui->m_lpTitleFontSize->setEnabled(enable);
	ui->m_lpTitleBold->setEnabled(enable);
	ui->m_lpTitleItalic->setEnabled(enable);
	ui->m_lpTitleUnderline->setEnabled(enable);
	ui->m_lpTitleLeft->setEnabled(enable);
	ui->m_lpTitleCenter->setEnabled(enable);
	ui->m_lpTitleRight->setEnabled(enable);
}

void cPropertiesWindow::enablePrintSubtitle(bool enable)
{
	ui->m_lpSubtitleFont->setEnabled(enable);
	ui->m_lpSubtitleFontSize->setEnabled(enable);
	ui->m_lpSubtitleBold->setEnabled(enable);
	ui->m_lpSubtitleItalic->setEnabled(enable);
	ui->m_lpSubtitleUnderline->setEnabled(enable);
	ui->m_lpSubtitleLeft->setEnabled(enable);
	ui->m_lpSubtitleCenter->setEnabled(enable);
	ui->m_lpSubtitleRight->setEnabled(enable);
}

void cPropertiesWindow::enablePrintShortDescription(bool /*enable*/)
{
}

void cPropertiesWindow::enablePrintDescription(bool /*enable*/)
{
}

void cPropertiesWindow::enablePrintAuthor(bool enable)
{
	ui->m_lpAuthorFont->setEnabled(enable);
	ui->m_lpAuthorFontSize->setEnabled(enable);
	ui->m_lpAuthorBold->setEnabled(enable);
	ui->m_lpAuthorItalic->setEnabled(enable);
	ui->m_lpAuthorUnderline->setEnabled(enable);
	ui->m_lpAuthorLeft->setEnabled(enable);
	ui->m_lpAuthorCenter->setEnabled(enable);
	ui->m_lpAuthorRight->setEnabled(enable);
}

void cPropertiesWindow::enablePrintPartName(bool enable)
{
	ui->m_lpPartNameFont->setEnabled(enable);
	ui->m_lpPartNameFontSize->setEnabled(enable);
	ui->m_lpPartNameBold->setEnabled(enable);
	ui->m_lpPartNameItalic->setEnabled(enable);
	ui->m_lpPartNameUnderline->setEnabled(enable);
	ui->m_lpPartNameLeft->setEnabled(enable);
	ui->m_lpPartNameCenter->setEnabled(enable);
	ui->m_lpPartNameRight->setEnabled(enable);
}

void cPropertiesWindow::enablePrintPartDescription(bool /*enable*/)
{
}

void cPropertiesWindow::enablePrintPartText(bool /*enable*/)
{
}

void cPropertiesWindow::enablePrintChapterName(bool enable)
{
	ui->m_lpChapterNameFont->setEnabled(enable);
	ui->m_lpChapterNameFontSize->setEnabled(enable);
	ui->m_lpChapterNameBold->setEnabled(enable);
	ui->m_lpChapterNameItalic->setEnabled(enable);
	ui->m_lpChapterNameUnderline->setEnabled(enable);
	ui->m_lpChapterNameLeft->setEnabled(enable);
	ui->m_lpChapterNameCenter->setEnabled(enable);
	ui->m_lpChapterNameRight->setEnabled(enable);
}

void cPropertiesWindow::enablePrintChapterDescription(bool /*enable*/)
{
}

void cPropertiesWindow::enablePrintChapterText(bool /*enable*/)
{
}

void cPropertiesWindow::enablePrintSceneName(bool enable)
{
	ui->m_lpSceneNameFont->setEnabled(enable);
	ui->m_lpSceneNameFontSize->setEnabled(enable);
	ui->m_lpSceneNameBold->setEnabled(enable);
	ui->m_lpSceneNameItalic->setEnabled(enable);
	ui->m_lpSceneNameUnderline->setEnabled(enable);
	ui->m_lpSceneNameLeft->setEnabled(enable);
	ui->m_lpSceneNameCenter->setEnabled(enable);
	ui->m_lpSceneNameRight->setEnabled(enable);
}

void cPropertiesWindow::enablePrintSceneDescription(bool /*enable*/)
{
}

void cPropertiesWindow::enablePrintSceneText(bool /*enable*/)
{
}
