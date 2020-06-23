
#include <QCoreApplication>
#include <QLockFile>
#include <QDebug>

#include "DbLocker.h"

DbLocker::DbLocker(const QString& dirpath) {
	QString lockfile_path = dirpath + "/lockfile";
	_lf = new QLockFile(lockfile_path);	
}

DbLocker::~DbLocker() {
	unlock();
}

void DbLocker::lock() {
	int b=_lf->tryLock();
	if(b) {
		qInfo() << "lock acquired!";
	}
	else {
		qInfo() << "lock refused!";
		qint64 pid;
		QString hostname;
		QString appname;
		if(_lf->getLockInfo(&pid, &hostname, &appname)) {
			qInfo() << "Lock acquired by application: " << appname;
		}
		else {
			qCritical() << "Unable to retrieve lock information";
		}		
	}
}

void DbLocker::unlock() {
	_lf->unlock();	
}

bool DbLocker::isLocked() const {
	return _lf->isLocked();
}

void DbLocker::onExit() {
	unlock();
}