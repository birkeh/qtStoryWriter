#ifndef CDATETIMEEDIT_H
#define CDATETIMEEDIT_H


#include <QDateTimeEdit>
#include <QMetaType>


class cDateTimeEdit : public QDateTimeEdit
{
	Q_OBJECT

public:
	cDateTimeEdit(QWidget* parent = Q_NULLPTR);

signals:
	void		gotFocus(cDateTimeEdit* lpDateTimeEdit);
	void		lostFocus(cDateTimeEdit* lpDateTimeEdit);

protected:
	void		focusInEvent(QFocusEvent *event);
	void		focusOutEvent(QFocusEvent *event);
};

Q_DECLARE_METATYPE(cDateTimeEdit*)

#endif // CDATETIMEEDIT_H
