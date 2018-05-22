/*!
 \file main.cpp

*/

#include "cmainwindow.h"
#include <QApplication>
#include <QSettings>

#include <QPixmap>
#include <QThread>

#include "csplashscreen.h"


int main(int argc, char *argv[])
{
	QApplication	a(argc, argv);
	QPixmap			pixmap(":/images/splash.png");
	cSplashScreen*	lpSplash	= new cSplashScreen(pixmap.scaled(480, 289));
//	int				id			= QFontDatabase::addApplicationFont(":/fonts/Stingray.otf");
	int				id			= QFontDatabase::addApplicationFont(":/fonts/BiggerLove.ttf");
//	int				id			= QFontDatabase::addApplicationFont(":/fonts/Luna.ttf");
//	int				id			= QFontDatabase::addApplicationFont(":/fonts/Tomatoes.ttf");
	QString			family		= QFontDatabase::applicationFontFamilies(id).at(0);
	QFont			splashFont(family);

	lpSplash->setMessageRect(QRect(0, 50, 480, 189), Qt::AlignHCenter);

	splashFont.setPixelSize(18);
	lpSplash->setFont(splashFont);
	lpSplash->setStatusMessageColor(Qt::white);

	lpSplash->show();
	a.processEvents();

	lpSplash->showStatusMessage(QObject::tr("initializing..."));

	QCoreApplication::setOrganizationName("WIN-DESIGN");
	QCoreApplication::setOrganizationDomain("windesign.at");
	QCoreApplication::setApplicationName("qtStoryWriter");

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
