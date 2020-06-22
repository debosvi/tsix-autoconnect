#include <QCoreApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>

#include <QLockFile>
#include <QDir>
#include <QTextStream>
#include <QDebug>

QTextStream& qStdErr()
{
    static QTextStream ts( stdout );
    return ts;
}

int main(int argc, char **argv) {
    QCoreApplication app(argc, argv);
    
	app.setOrganizationName("Akka CDS Thalès SIX");
    app.setApplicationName("Test Application for locking file");
    app.setApplicationVersion(QT_VERSION_STR);
    
	QCommandLineParser parser;
    
	parser.setApplicationDescription(QCoreApplication::applicationName());
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("file", "The file to open.");
    parser.process(app);
	
	QString lockfile_path = app.applicationDirPath() + "/lockfile";
	qDebug() << "Lock file path: " << lockfile_path;
	
	QLockFile lf(lockfile_path);
	
	int b=lf.tryLock();
	if(b)
		qDebug() << "lock acquired!";
	else
		qDebug() << "lock refused!";

    return app.exec();
}