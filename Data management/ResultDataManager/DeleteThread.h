/*
 * Copyright (C) 2012
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
	void setDeleteAtFlush(bool flush);// �f�X�g���N�^�Ŏc���Ă����t�@�C�����폜����

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