/*!
 \file cimagewidget.h

*/

#ifndef CIMAGEWIDGET_H
#define CIMAGEWIDGET_H


#include "ctextdocument.h"
#include <QWidget>
#include <QPixmap>


namespace Ui {
class cImageWidget;
}

/*!
 \brief

 \class cImageWidget cimagewidget.h "cimagewidget.h"
*/
class cImageWidget : public QWidget
{
	Q_OBJECT

public:
	/*!
	 \brief

	 \fn cImageWidget
	 \param parent
	*/
	explicit cImageWidget(QWidget *parent = 0);
	/*!
	 \brief

	 \fn ~cImageWidget
	*/
	~cImageWidget();

	/*!
	 \brief

	 \fn setValues
	 \param szName
	 \param szType
	 \param lpDocument
	 \param pixmap
	*/
	void				setValues(const QString& szName, const QString& szType, cTextDocument* lpDocument, const QPixmap& pixmap);
private:
	Ui::cImageWidget*	ui; /*!< TODO: describe */
};

#endif // CIMAGEWIDGET_H
