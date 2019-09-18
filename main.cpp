/*!
 \file main.cpp

*/

#include "cmainwindow.h"
#include <QApplication>
#include <QSettings>

#include <QPixmap>
#include <QThread>

#include <QTranslator>
#include <QLocale>
#include <QSettings>

#include <QDir>

#include <QTimer>

#include "csplashscreen.h"


#define SHOW_SPLASH
#define DO_DEB

void debugOut(const QString& message)
{
#ifdef DO_DEB
	QFile		file("c:\\temp\\log.log");
	file.open(QFile::WriteOnly | QFile::Text | QFile::Append);
	QTextStream	out(&file);
	out << message;
	out << "\n";
	file.flush();
	file.close();
#endif
}

int main(int argc, char *argv[])
{
	for(int x = 0;x < argc;x++)
		debugOut(argv[x]);

	debugOut("1");
	QApplication	a(argc, argv);
	debugOut("2");

	a.setApplicationVersion(APP_VERSION);
	a.setApplicationDisplayName("storyWriter");
	a.setOrganizationName("WIN-DESIGN");
	a.setOrganizationDomain("windesign.at");
	a.setApplicationName("storyWriter");
	debugOut("3");

	QSettings		settings;
	QTranslator*	lpTranslator	= new QTranslator;
	QString			szLanguage	= settings.value("main/language").toString();
	debugOut("4");

	if(!szLanguage.compare("%SYSTEM%"))
	{
		QStringList	languageList	= QLocale::system().uiLanguages();
		if(languageList.count())
			szLanguage	= languageList[0];
	}
	debugOut("5");

	if(!szLanguage.isEmpty())
	{
		if(lpTranslator->load(QString("storyWriter_%1").arg(szLanguage), ":/locale"))
			a.installTranslator(lpTranslator);
	}
	debugOut("6");

#ifdef SHOW_SPLASH
	QPixmap			pixmap(":/images/splash.png");
#else
	QPixmap			pixmap(":/images/splashEmpty.png");
#endif
//	int				id			= QFontDatabase::addApplicationFont(":/fonts/Stingray.otf");
//	int				id			= QFontDatabase::addApplicationFont(":/fonts/Luna.ttf");
//	int				id			= QFontDatabase::addApplicationFont(":/fonts/Tomatoes.ttf");
//	int				id			= QFontDatabase::addApplicationFont(":/fonts/BiggerLove.ttf");
	int				id			= QFontDatabase::addApplicationFont(":/fonts/Tahu!.ttf");
	QString			family		= QFontDatabase::applicationFontFamilies(id).at(0);
	QFont			splashFont(family);
	splashFont.setPixelSize(24);
	debugOut("7");

	cSplashScreen*	lpSplash	= new cSplashScreen(pixmap, splashFont);
	debugOut("8");

#ifdef SHOW_SPLASH
	lpSplash->setMessageRect(QRect(0, 110, 480, 209));
#else
	lpSplash->setMessageRect(QRect(0, 110, 480, 209));
#endif
	debugOut("9");

	lpSplash->show();
	a.processEvents();
	debugOut("10");

	lpSplash->showStatusMessage(QObject::tr("<center>initializing...</denter>"));
	debugOut("11");

	cMainWindow w(lpSplash, lpTranslator);
	debugOut("12");

	QTimer::singleShot(0, &w, SLOT(onInitialize()));
	debugOut("12a");

	if(settings.value("main/maximized").toBool())
		w.showMaximized();
	else
		w.show();
	debugOut("13");

	lpSplash->finish(&w);
	delete lpSplash;
	debugOut("14");

	return a.exec();
}
