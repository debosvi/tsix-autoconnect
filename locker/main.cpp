#include <QCoreApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>

#include <QtGlobal>
#include <QLockFile>
#include <QDebug>

#include "SignalHandler.h"
#include "DbLocker.h"

int main(int argc, char **argv) {
    QCoreApplication app(argc, argv);
	SignalHandler sig_handler;
	
	QObject::connect(&sig_handler, SIGNAL(s_term()), &app, SLOT(quit()));
	QObject::connect(&sig_handler, SIGNAL(s_close()), &app, SLOT(quit()));
	QObject::connect(&sig_handler, SIGNAL(s_int()), &app, SLOT(quit()));
	
	QString sysUsername = qgetenv("USER");
	if (sysUsername.isEmpty()) sysUsername = qgetenv("USERNAME");
    
	app.setOrganizationName("Akka CDS Thalès SIX");
    app.setApplicationName("Test Application for locking file (" + sysUsername + ")");
    app.setApplicationVersion(QT_VERSION_STR);
    
	QCommandLineParser parser;
    
	parser.setApplicationDescription(QCoreApplication::applicationName());
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("file", "The file to open.");
    parser.process(app);
	
	DbLocker locker(app.applicationDirPath());
	
	QObject::connect(&app, SIGNAL(aboutToQuit()), &locker, SLOT(onExit()));
	
	locker.lock();

    return app.exec();
}