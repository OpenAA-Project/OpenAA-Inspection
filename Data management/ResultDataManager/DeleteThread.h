#pragma once

#include <QThread>
#include <QStringList>
#include <QMutex>

class DeleteThread : public QThread
{
	Q_OBJECT
public:
	DeleteThread(QObject *parent=NULL);
	~DeleteThread();

protected:
	void run(void);

public:
	void addDelFile(const QString &filePath);
	void addDelFile(const QStringList &filePathes);

public:
	void stop();
	void pause(bool p=true);
	qint64 remainFileCount() const;
	QStringList remainFiles() const;
	void setDeleteAtFlush(bool flush);// デストラクタで残っているファイルを削除する

	bool deleteAtFlush() const;

private:
	bool deleteFile(const QString &filePath);
	void emptyDirRemove();

signals:
	void deletedFile(const QString &filePath);

private:
	volatile bool m_stop;
	volatile bool m_pause;
	volatile bool m_deleteAtFlush;
	QStringList m_deleteFilePathes;
	QStringList m_checkDelEmpDirectories;
	mutable QMutex m_mutex;
	mutable QMutex m_mutexEmpDir;
};