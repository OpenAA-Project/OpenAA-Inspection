/*
 * Copyright (C) 2022
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

#if	!defined(XMaintainer_h)
#define	XMaintainer_h

#include <QStringList>
#include <QIODevice>
#include <QThread>
#include <QDateTime>
#include <QFileInfo>
#include "XTypeDef.h"
#include "NList.h"

class Maintainer;

class	MaintainerSetting
{
public:
	QStringList		FileNames;
	QStringList		FolderNames;
	bool			UseDaysToKeepTerm;
	bool			UseMonthsToKeepTerm;
	int32			TermDaysToKeep;
	int32			TermMonthsToKeep;
	bool			PrioritySpace;
	int32			SpaceGBRemaining;
	int32			CheckingHour	;
	int32			CheckingMinute	;
	QString			DestinationPath	;

	MaintainerSetting(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	bool	IsOlder(const QDateTime &FileStamp , const QDateTime &CurrentTime);
};

class	MFileList : public NPList<MFileList>
{
public:
	QString	AbsFileName;
	int64	FileSize;
	QDateTime	TimeStamp;

	MFileList(const QFileInfo &Info);
	virtual	int	Compare(MFileList &src)	override;
};




class	MaintainThread : public QThread
{
	Maintainer	*Parent;
public:
	int		WaitingMilisec;
	volatile	bool	Terminated;

	MaintainThread(Maintainer *p,QObject * parent);

	virtual	void run ();
private:
	bool	RemoveAllFilesAndFolder(const QString &Path ,const QDateTime &CurrentTime ,NPListPack<MFileList> &AliveFiles);
	bool	BackupAllFilesAndFolder(const QString &Path ,const QDateTime &CurrentTime ,NPListPack<MFileList> &AliveFiles);
};


#endif