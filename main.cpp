/*!
 \file main.cpp

*/

#include "cmainwindow.h"
#include <QApplication>
#include <QSettings>

#include <QPixmap>
#include <QThread>

#include "csplashscreen.h"

#define SHOW_SPLASH

int main(int argc, char *argv[])
{
	QApplication	a(argc, argv);

#ifdef SHOW_SPLASH
	QPixmap			pixmap(":/images/splash.png");
#else
	QPixmap			pixmap(":/images/splashEmpty.png");
#endif
	cSplashScreen*	lpSplash	= new cSplashScreen(pixmap);
//	int				id			= QFontDatabase::addApplicationFont(":/fonts/Stingray.otf");
//	int				id			= QFontDatabase::addApplicationFont(":/fonts/Luna.ttf");
//	int				id			= QFontDatabase::addApplicationFont(":/fonts/Tomatoes.ttf");
//	int				id			= QFontDatabase::addApplicationFont(":/fonts/BiggerLove.ttf");
	int				id			= QFontDatabase::addApplicationFont(":/fonts/Tahu!.ttf");
	QString			family		= QFontDatabase::applicationFontFamilies(id).at(0);
	QFont			splashFont(family);

#ifdef SHOW_SPLASH
	lpSplash->setMessageRect(QRect(0, 110, 480, 209), Qt::AlignHCenter);
#else
	lpSplash->setMessageRect(QRect(0, 20, 480, 299), Qt::AlignHCenter);
#endif

	splashFont.setPixelSize(18);
	lpSplash->setFont(splashFont);
	lpSplash->setStatusMessageColor(Qt::darkGray);

	lpSplash->show();
	a.processEvents();

	lpSplash->showStatusMessage(QObject::tr("initializing..."));

	QCoreApplication::setOrganizationName("WIN-DESIGN");
	QCoreApplication::setOrganizationDomain("windesign.at");
	QCoreApplication::setApplicationName("storyWriter");

	QSettings	settings;

	cMainWindow w(lpSplash);

	if(settings.value("main/maximized").toBool())
		w.showMaximized();
	else
		w.show();

	lpSplash->finish(&w);
	delete lpSplash;

	return a.exec();
}
