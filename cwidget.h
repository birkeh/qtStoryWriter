#ifndef CWIDGET_H
#define CWIDGET_H


#include "cpropertieswindow.h"
#include "cpartwindow.h"
#include "cchapterwindow.h"
#include "cscenewindow.h"
#include "ccharacterwindow.h"
#include "cobjectwindow.h"
#include "cplacewindow.h"
#include "crecherchewindow.h"

#include <QWidget>
#include <QMdiSubWindow>


/*!
 \brief

 \class cWidget cwidget.h "cwidget.h"
*/
class cWidget : public QWidget
{
	Q_OBJECT
public:
	/*!
	 \brief

	 \enum TYPE
	*/
	enum TYPE
	{
		TYPE_unknown	= 0, /*!< TODO: describe */
		TYPE_part		= 1, /*!< TODO: describe */
		TYPE_chapter	= 2, /*!< TODO: describe */
		TYPE_scene		= 3, /*!< TODO: describe */
		TYPE_character	= 4, /*!< TODO: describe */
		TYPE_object		= 5, /*!< TODO: describe */
		TYPE_place		= 6, /*!< TODO: describe */
		TYPE_recherche	= 7, /*!< TODO: describe */
		TYPE_properties	= 8, /*!< TODO: describe */
	};

	/*!
	 \brief

	 \fn cWidget
	 \param parent
	*/
	explicit			cWidget(cPropertiesWindow* parent);

	/*!
	 \brief

	 \fn cWidget
	 \param parent
	*/
	explicit			cWidget(cPartWindow* parent);
	/*!
	 \brief

	 \fn cWidget
	 \param parent
	*/
	explicit			cWidget(cChapterWindow* parent);
	/*!
	 \brief

	 \fn cWidget
	 \param parent
	*/
	explicit			cWidget(cSceneWindow* parent);
	/*!
	 \brief

	 \fn cWidget
	 \param parent
	*/
	explicit			cWidget(cCharacterWindow* parent);
	/*!
	 \brief

	 \fn cWidget
	 \param parent
	*/
	explicit			cWidget(cObjectWindow* parent);
	/*!
	 \brief

	 \fn cWidget
	 \param parent
	*/
	explicit			cWidget(cPlaceWindow* parent);
	/*!
	 \brief

	 \fn cWidget
	 \param parent
	*/
	explicit			cWidget(cRechercheWindow* parent);
	/*!
	 \brief

	 \fn cWidget
	 \param parent
	*/
	explicit			cWidget(QWidget* parent);

	/*!
	 \brief

	 \fn retranslateUI
	*/
	void				retranslateUI();

	/*!
	 \brief

	 \fn widget
	 \return QWidget
	*/
	QWidget*			widget();

	/*!
	 \brief

	 \fn setWindow
	 \param lpWindow
	*/
	void				setWindow(QMdiSubWindow* lpWindow);
	/*!
	 \brief

	 \fn window
	 \return QMdiSubWindow
	*/
	QMdiSubWindow*		window();
	/*!
	 \brief

	 \fn type
	 \return TYPE
	*/
	TYPE				type();
signals:

public slots:

private:
	TYPE				m_type; /*!< TODO: describe */
	QWidget*			m_lpWidget; /*!< TODO: describe */
	QMdiSubWindow*		m_lpWindow; /*!< TODO: describe */
};

#endif // CWIDGET_H
