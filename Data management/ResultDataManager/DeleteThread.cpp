#include "DeleteThread.h"

#include <QFile>
#include <QTime>
#include <QDir>

#include "XDirectoryAPI.h"

DeleteThread::DeleteThread(QObject *parent)
	:QThread(parent),m_stop(false),m_pause(false),m_deleteAtFlush(true),m_deleteFilePathes(QStringList())
	,m_checkDelEmpDirectories(),m_mutex(),m_mutexEmpDir()
{
}

DeleteThread::~DeleteThread()
{
	stop();
	while(isFinished()==false){
		msleep(1);
	}
	if(deleteAtFlush()==true && remainFileCount()>0){// 残り削除フラグが立っているとき
		// 残りを実行
		start();
		msleep(1);
		if(isRunning()==true){
			while(remainFileCount()!=0){
				msleep(1);
			}
		}
	}

	msleep(100);

	emptyDirRemove();
}

void DeleteThread::emptyDirRemove()
{
	QMutexLocker locker( &m_mutexEmpDir );
	// ディレクトリのチェックおよび削除
	for(int i=0; i<m_checkDelEmpDirectories.count(); i++){
		if(IsEmptyDirectory(m_checkDelEmpDirectories[i])==true){
			RemoveDirectoryApi(m_checkDelEmpDirectories[i]);
		}
	}

	m_checkDelEmpDirectories.clear();
}

void DeleteThread::run(void)
{
	m_stop = false;
	m_pause = false;
	while(m_stop==false){
		// 待機
		msleep(10);

		QStringList filePath;
		{// ミューテックス保護域ここから
			QMutexLocker locker( &m_mutex );

			if(m_pause==true){
				continue;
			}

			// １つでもストックされているかを確認する
			if(m_deleteFilePathes.isEmpty()==true){// 一つもない場合
				emptyDirRemove();
				continue;
			}
		
			// ストックを取得
			filePath = m_deleteFilePathes;
			m_deleteFilePathes.clear();
		}// ミューテックス保護域ここまで

		//QStringList checkDir;

		for(int i=0; i<filePath.count(); i++){
			QString fileDirPath = QFileInfo(filePath[i]).absolutePath();
			deleteFile(filePath[i]);
			//if(deleteFile(filePath[i])==true && checkDir.contains(fileDirPath)==false){
			//	checkDir.append(fileDirPath);
			//}
		}

		//msleep(100);

		//for(int i=0; i<checkDir.count(); i++){
		//	QDir dir;
		//	dir.remove(checkDir[i]);
		//}
	}
}

bool DeleteThread::deleteFile(const QString &filePath)
{
	static QTime time;
	if(time.isNull()==true){
		time.start();
	}

	// 削除
	if(DeleteFileApi(filePath)==true){
		QString fileDirectory = QFileInfo(filePath).absolutePath();
		QDir dir(fileDirectory);
		QString dirName = dir.dirName();
		dir.cdUp();

		QFile file(filePath);
		while(file.exists()==true)
			;

		{
		QMutexLocker locker( &m_mutexEmpDir );
		if(m_checkDelEmpDirectories.contains(fileDirectory)==false){
			m_checkDelEmpDirectories.append(fileDirectory);
		}
		}

		if(time.elapsed()>100){
			time.restart();
			emit deletedFile(QDir::fromNativeSeparators(filePath));// 削除シグナル送信
		}
		return true;
	}else{
		return false;
	}
}

void DeleteThread::addDelFile(const QString &filePath)
{
	QMutexLocker locker( &m_mutex );
	m_deleteFilePathes << filePath;
}

void DeleteThread::addDelFile(const QStringList &filePathes)
{
	QMutexLocker locker( &m_mutex );
	m_deleteFilePathes << filePathes;
}

void DeleteThread::stop()
{
	QMutexLocker locker( &m_mutex );
	m_stop = true;
}

void DeleteThread::pause(bool p)
{
	QMutexLocker locker( &m_mutex );
	m_pause = p;
}

qint64 DeleteThread::remainFileCount() const
{
	QMutexLocker locker( &m_mutex );
	return m_deleteFilePathes.count();
}

QStringList DeleteThread::remainFiles() const
{
	QMutexLocker locker( &m_mutex );
	return m_deleteFilePathes;
}

void DeleteThread::setDeleteAtFlush(bool flush)
{
	QMutexLocker locker( &m_mutex );
	m_deleteAtFlush = flush;
}

bool DeleteThread::deleteAtFlush() const
{
	QMutexLocker locker( &m_mutex );
	return m_deleteAtFlush;
}
