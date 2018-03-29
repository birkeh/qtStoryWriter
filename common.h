#ifndef COMMON_H
#define COMMON_H


#include <QDebug>

#ifdef _MSC_VER
	#define myDebug qDebug()
#else
#define myDebug qDebug() << __FILE__ << "(" << __LINE__ << ") - " << __PRETTY_FUNCTION__ << ":"
#endif

#endif // COMMON_H
