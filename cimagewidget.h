#ifndef CIMAGEWIDGET_H
#define CIMAGEWIDGET_H


#include "ctextdocument.h"
#include <QWidget>
#include <QPixmap>


namespace Ui {
class cImageWidget;
}

class cImageWidget : public QWidget
{
	Q_OBJECT

public:
	explicit cImageWidget(QWidget *parent = 0);
	~cImageWidget();

	void				setValues(const QString& szName, const QString& szType, cTextDocument* lpDocument, const QPixmap& pixmap);
private:
	Ui::cImageWidget*	ui;
};

#endif // CIMAGEWIDGET_H
