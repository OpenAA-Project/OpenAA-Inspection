/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XLogOut.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#if	!defined(XLOGOUT_H)
#define	XLOGOUT_H

#include <QThread>
#include "XDateTime.h"
#include <QMutex>
#include "NList.h"
#include <stdio.h>
#include <QDate>
#include <QEvent>
#include "XTypeDef.h"
#include "XServiceForLayers.h"

class	LogOutPacket : public NPList<LogOutPacket>
{
public:
	int			LineNo;
	XDateTime	DT;
	char		FuncName[64];
	struct{
		bool	EnableArg1:1;
		bool	EnableArg2:1;
		bool	EnableArg3:1;
		bool	EnableArg4:1;
	};
	int64		Arg1;
	int64		Arg2;
	char		Arg3[64];
	char		Arg4[64];
	struct{
		bool	EnableRet1:1;
		bool	EnableRet2:1;
	};
	union{
		bool		Ret1;
		int64		Ret2;
	};
	DWORD		CTime;

	LogOutPacket(int lineNo ,const char *funcName);

	bool	Write(FILE *file ,DWORD LastCTime);
};


class	LogOutThread : public QThread
{
	NPListPack<LogOutPacket>	LogOutData;
	QMutex						MutexLogOut;
public:
	char	*FileName;

	LogOutThread(void){	FileName=NULL;	}

	virtual void run ();

	void	AddLog(LogOutPacket *data);
	LogOutPacket *PickTopLog(void);

};



class	LogOutClass
{
	char	FileName[256];
	LogOutThread	*LThread;
public:

	LogOutClass(const char *filename="LogFile.txt");
	~LogOutClass(void);

	void	Initial(char *filename=NULL);

	void	PutLog(int lineNo ,const char *FuncName);
	
	void	PutLogA1(int lineNo ,const char *FuncName,int64 arg);
	void	PutLogA1(int lineNo ,const char *FuncName,char *arg);
	
	void	PutLogR(int lineNo ,const char *FuncName,bool retcode);
	void	PutLogR(int lineNo ,const char *FuncName,int64 retcode);

	void	PutLogA1R(int lineNo ,const char *FuncName,int64 arg,bool retcode);
	void	PutLogA1R(int lineNo ,const char *FuncName,char *arg,bool retcode);
	void	PutLogA1R(int lineNo ,const char *FuncName,int64 arg,int64 retcode);
	void	PutLogA1R(int lineNo ,const char *FuncName,char *arg,int64 retcode);

	void	PutLogA2(int lineNo ,const char *FuncName,int64 arg1,int64 arg2);
	void	PutLogA2(int lineNo ,const char *FuncName,char *arg1,int64 arg2);
	void	PutLogA2(int lineNo ,const char *FuncName,int64 arg1,char *arg2);
	void	PutLogA2(int lineNo ,const char *FuncName,char *arg1,char *arg2);

	void	PutLogA2R(int lineNo ,const char *FuncName,int64 arg1,int64 arg2,bool retcode);
	void	PutLogA2R(int lineNo ,const char *FuncName,char *arg1,int64 arg2,bool retcode);
	void	PutLogA2R(int lineNo ,const char *FuncName,int64 arg1,char *arg2,bool retcode);
	void	PutLogA2R(int lineNo ,const char *FuncName,char *arg1,char *arg2,bool retcode);
	void	PutLogA2R(int lineNo ,const char *FuncName,int64 arg1,int64 arg2,int64 retcode);
	void	PutLogA2R(int lineNo ,const char *FuncName,char *arg1,int64 arg2,int64 retcode);
	void	PutLogA2R(int lineNo ,const char *FuncName,int64 arg1,char *arg2,int64 retcode);
	void	PutLogA2R(int lineNo ,const char *FuncName,char *arg1,char *arg2,int64 retcode);
};

//==================================================================================

class	OperationLoggerFilter : public QObject,public ServiceForLayers,public NPList<OperationLoggerFilter>
{
	Q_OBJECT
		
	QObject	*TargetObj;
public:
	OperationLoggerFilter(LayersBase *base, QObject *targetObj, QObject * parent = 0 );
	~OperationLoggerFilter(void);

	void	Release(void);
protected:
	bool eventFilter(QObject *obj, QEvent *event);

	void	MakeStringList(QObject *obj, QString &WhereIsObj ,QStringList &WhereIsObjList);

private slots:
	void	SlotDestroyed();
};

class	OperationLogger : public ServiceForLayers
{
	QDate	CNow;
	QString	ProgramName;
	NPListPack<OperationLoggerFilter>	OperationLoggerFilterContainer;

public:
	OperationLogger(LayersBase *base);
	~OperationLogger(void);

	const QString	&GetProgramName(void)	{	return ProgramName;		}

	void	PutLogStart				(const QString &Program);
	void	PutLogClose				(void);
	void	PutLogKeyInput			(const QString &WhereIsObj ,const QString &str);
	void	PutLogMouseDown			(const QString &WhereIsObj ,const QString &ObjTitle,int x ,int y);
	void	PutLogMouseRelease		(const QString &WhereIsObj ,const QString &ObjTitle,int x ,int y);
	void	PutLogPushButton		(const QString &WhereIsObj ,const QString &ObjTitle);
	void	PutLogClickGrid			(const QString &WhereIsObj ,const QString &ObjTitle,int x ,int y);
	void	PutLogDoubleClick		(const QString &WhereIsObj ,const QString &ObjTitle,int x ,int y);

	void	Install(QObject *window);
	void	Uninstall(void);

private:
	void	PutLog(const QString &WhereIsObj ,const QString &ActionMsg,const QString &Msg);
	void	RemoveLogFolder(const QString &FolderName);
	void	CheckLogFolder(void);
};

#endif