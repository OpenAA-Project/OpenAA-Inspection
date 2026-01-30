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

#if	!defined(XCopyMultiple_h)
#define	XCopyMultiple_h

#include <QStringList>
#include "NList.h"
#include <QThread>
#include <QIODevice>
#include <QObject>
#include <QWidget>

class	ThreadCopy;

class	CopyMultipleData : public QObject
{
	Q_OBJECT
public:
	QString			SourcePath;
	QStringList		SearchFilter;
	QStringList		ExcludedFilter;

	QStringList		Destinations;

	class	FoundFileClass : public NPList<FoundFileClass>
	{
	public:
		CopyMultipleData	*Parent;

		QString		FoundFile;

		enum	State
		{
			_NotYet		=0
			,_Copied	=1
			,_NotCopied	=2
		}*CopiedState;

		FoundFileClass(CopyMultipleData	*parent);
		~FoundFileClass(void);
	};
	NPListPack<FoundFileClass>	SourceFiles;	//�������ꂽ�t�@�C��

	volatile	bool	TerminateCopy;
	ThreadCopy	**ThreadCopyDim;

	CopyMultipleData(void){	ThreadCopyDim=NULL;		TerminateCopy=false;	}
	~CopyMultipleData(void);

	int		GetDestCount(void);

	bool	SaveFilter(QIODevice *f);
	bool	LoadFilter(QIODevice *f);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	MakeFoundList(void);
	void	MakeFoundList(const QString &pathname);

	void	StartCopy(QWidget *parent);

signals:
	void	SignalFinishCopy();
private slots:
	void	FinishedThreadCopy();
};

class	ThreadCopy : public QThread
{
	CopyMultipleData	*DataParent;
	QString				DestPath;
	int					DestNumber;
public:
	ThreadCopy(CopyMultipleData *_DataParent 
				,const QString &_DestPath,int DestN
				,QObject *parent);

	virtual void run ();
	bool makeDirectory(QString pathname,QString oldname);
};

#endif