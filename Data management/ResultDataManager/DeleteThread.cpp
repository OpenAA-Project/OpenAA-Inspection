/*
 * Copyright (C) 2021
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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
	if(deleteAtFlush()==true && remainFileCount()>0){// �c���폜�t���O�������Ă����Ƃ�
		// �c�������s
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
	// �f�B���N�g���̃`�F�b�N�����э폜
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
		// �ҋ@
		msleep(10);

		QStringList filePath;
		{// �~���[�e�b�N�X�ی��悱������
			QMutexLocker locker( &m_mutex );

			if(m_pause==true){
				continue;
			}

			// �P�ł��X�g�b�N�����Ă��邩���m�F����
			if(m_deleteFilePathes.isEmpty()==true){// �����Ȃ��ꍇ
				emptyDirRemove();
				continue;
			}
		
			// �X�g�b�N���擾
			filePath = m_deleteFilePathes;
			m_deleteFilePathes.clear();
		}// �~���[�e�b�N�X�ی��悱���܂�

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

	// �폜
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
			emit deletedFile(QDir::fromNativeSeparators(filePath));// �폜�V�O�i�����M
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