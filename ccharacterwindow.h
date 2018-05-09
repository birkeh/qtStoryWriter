#ifndef CCHARACTERWINDOW_H
#define CCHARACTERWINDOW_H


#include "ccharacter.h"

#include "cmdisubwindow.h"
#include "cmainwindow.h"

#include <QWidget>
#include <QStandardItemModel>


namespace Ui {
class cCharacterWindow;
}

/*!
 \brief

 \class cCharacterWindow ccharacterwindow.h "ccharacterwindow.h"
*/
class cCharacterWindow : public cMDISubWindow
{
	Q_OBJECT

public:
	/*!
	 \brief

	 \fn cCharacterWindow
	 \param parent
	*/
	explicit cCharacterWindow(QWidget *parent = 0);
	/*!
	 \brief

	 \fn ~cCharacterWindow
	*/
	~cCharacterWindow();

	/*!
	 \brief

	 \fn setCharacter
	 \param lpCharacter
	*/
	void					setCharacter(cCharacter* lpCharacter);
	/*!
	 \brief

	 \fn character
	 \return cCharacter
	*/
	cCharacter*				character();

private slots:
	/*!
	 \brief

	 \fn onFirstNameChanged
	 \param szText
	*/
	void					onFirstNameChanged(const QString& szText);
	/*!
	 \brief

	 \fn onMiddleNameChanged
	 \param szText
	*/
	void					onMiddleNameChanged(const QString& szText);
	/*!
	 \brief

	 \fn onLastNameChanged
	 \param szText
	*/
	void					onLastNameChanged(const QString& szText);
	/*!
	 \brief

	 \fn onMainCharacterClicked
	 \param bChecked
	*/
	void					onMainCharacterClicked(bool bChecked);
	/*!
	 \brief

	 \fn onCreatureChanged
	 \param szText
	*/
	void					onCreatureChanged(const QString& szText);
	/*!
	 \brief

	 \fn onGenderMaleClicked
	 \param bChecked
	*/
	void					onGenderMaleClicked(bool bChecked);
	/*!
	 \brief

	 \fn onGenderFemaleClicked
	 \param bChecked
	*/
	void					onGenderFemaleClicked(bool bChecked);
	/*!
	 \brief

	 \fn onGenderOtherClicked
	 \param bChecked
	*/
	void					onGenderOtherClicked(bool bChecked);
	/*!
	 \brief

	 \fn onTitleChanged
	 \param szText
	*/
	void					onTitleChanged(const QString& szText);
	/*!
	 \brief

	 \fn onDateOfBirthChanged
	 \param date
	*/
	void					onDateOfBirthChanged(const QDate& date);
	/*!
	 \brief

	 \fn onDateOfDeathChanged
	 \param date
	*/
	void					onDateOfDeathChanged(const QDate& date);
	/*!
	 \brief

	 \fn onPlaceOfBirthChanged
	 \param szText
	*/
	void					onPlaceOfBirthChanged(const QString& szText);
	/*!
	 \brief

	 \fn onPlaceOfDeathChanged
	 \param szText
	*/
	void					onPlaceOfDeathChanged(const QString& szText);
	/*!
	 \brief

	 \fn onHeightChanged
	 \param d
	*/
	void					onHeightChanged(double d);
	/*!
	 \brief

	 \fn onWeightChanged
	 \param d
	*/
	void					onWeightChanged(double d);
	/*!
	 \brief

	 \fn onFigureChanged
	 \param szText
	*/
	void					onFigureChanged(const QString& szText);
	/*!
	 \brief

	 \fn onSkinChanged
	 \param szText
	*/
	void					onSkinChanged(const QString& szText);
	/*!
	 \brief

	 \fn onNatureChanged
	 \param szText
	*/
	void					onNatureChanged(const QString& szText);
	/*!
	 \brief

	 \fn onHairColorChanged
	 \param szText
	*/
	void					onHairColorChanged(const QString& szText);
	/*!
	 \brief

	 \fn onHairCutChanged
	 \param szText
	*/
	void					onHairCutChanged(const QString& szText);
	/*!
	 \brief

	 \fn onHairLengthChanged
	 \param szText
	*/
	void					onHairLengthChanged(const QString& szText);
	/*!
	 \brief

	 \fn onSchoolChanged
	*/
	void					onSchoolChanged();
	/*!
	 \brief

	 \fn onSpokenLanguagesChanged
	*/
	void					onSpokenLanguagesChanged();
	/*!
	 \brief

	 \fn onJobChanged
	*/
	void					onJobChanged();
	/*!
	 \brief

	 \fn onDescriptionChanged
	*/
	void					onDescriptionChanged();

private:
	Ui::cCharacterWindow*	ui; /*!< TODO: describe */
	cMainWindow*			m_lpMainWindow; /*!< TODO: describe */
	cCharacter*				m_lpCharacter; /*!< TODO: describe */
};

#endif // CCHARACTERWINDOW_H
