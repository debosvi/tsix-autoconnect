
#ifndef DBLOCKER_H
#define DBLOCKER_H

#include <QObject>

class QLockFile;

class DbLocker : public QObject {
	Q_OBJECT
	
public:
	DbLocker(const QString& dirpath);
	~DbLocker();
	
	void lock();
	void unlock();
	bool isLocked() const;
	
public Q_SLOTS:
    void onExit();
	
private:
	QLockFile* _lf;
};

#endif // DBLOCKER_H
