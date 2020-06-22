#include <QCoreApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>

// #include <QHostInfo>
#include <QtGlobal>
#include <QLockFile>
#include <QDebug>

int main(int argc, char **argv) {
    QCoreApplication app(argc, argv);
    
	app.setOrganizationName("Akka CDS Thalès SIX");
	
	QString sysUsername = qgetenv("USER");
	if (sysUsername.isEmpty()) sysUsername = qgetenv("USERNAME");

    app.setApplicationName("Test Application for locking file (" + sysUsername + ")");
    app.setApplicationVersion(QT_VERSION_STR);
    
	QCommandLineParser parser;
    
	parser.setApplicationDescription(QCoreApplication::applicationName());
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("file", "The file to open.");
    parser.process(app);
	
	QString lockfile_path = app.applicationDirPath() + "/lockfile";
	qInfo() << "Lock file path: " << lockfile_path;
	
	QLockFile lf(lockfile_path);
	
	int b=lf.tryLock();
	if(b) {
		qInfo() << "lock acquired!";
	}
	else {
		qInfo() << "lock refused!";
		qint64 pid;
		QString hostname;
		QString appname;
		if(lf.getLockInfo(&pid, &hostname, &appname)) {
			qInfo() << "Lock acquired by application: " << appname;
		}
		else {
			qCritical() << "Unable to retrieve lock information";
		}		
	}

    return app.exec();
}