/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XLogOut.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XTypeDef.h"
#include "XLogOut.h"
#include <QCoreApplication>
#include "XDateTime.h"
#include <QString>
#include <QFileInfo>
#include <QAbstractButton>
#include <QDir>
#include <QTreeWidgetItem>
#include <QListWidgetItem>
#include <QTableWidgetItem>
#include <QTreeWidget>
#include <QListWidget>
#include <QTableWidget>
#include <QLineEdit>
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "XCriticalFunc.h"
#include "XGUIFormBase.h"
#include "XStatusController.h"

LogOutPacket::LogOutPacket(int lineNo ,const char *funcName)
{
	LineNo=lineNo;
	DT	=XDateTime::currentDateTime();
	strncpy(FuncName,funcName,sizeof(FuncName));
	FuncName[sizeof(FuncName)-1]=0;

	EnableArg1=false;
	EnableArg2=false;
	EnableArg3=false;
	EnableArg4=false;

	EnableRet1=false;
	EnableRet2=false;
}

bool	LogOutPacket::Write(FILE *file,DWORD LastCTime)
{
	fprintf(file,"%d/%d/%d %d:%d:%d %u Dif:%u Line=%d %s ",DT.year(),DT.month(),DT.day(),DT.hour(),DT.minute(),DT.second()
												,(int)CTime,(int)(CTime-LastCTime)
												,LineNo,FuncName);
	if(EnableArg1==true){
		fprintf(file,"IN:%I64d ",Arg1);
	}
	if(EnableArg2==true){
		fprintf(file,"IN:%I64d ",Arg2);
	}
	if(EnableArg3==true){
		fprintf(file,"IN:%s ",Arg3);
	}
	if(EnableArg4==true){
		fprintf(file,"IN:%s ",Arg4);
	}

	if(EnableRet1==true){
		if(Ret1==true){
			fprintf(file,"Ret:true ");
		}
		else{
			fprintf(file,"Ret:false ");
		}
	}
	if(EnableRet2==true){
		fprintf(file,"Ret:%I64d ",Ret2);
	}
	fprintf(file,"\n");
	return true;
}

//===============================================================

void LogOutThread::run ()
{
	DWORD	LastCTime;
	while(QCoreApplication::closingDown ()==false){
		LogOutPacket *L=PickTopLog();
		if(L!=NULL){
			QFileInfo	Info(FileName);
			if(Info.isRelative()==true){
				Info.makeAbsolute();
			}
			ForceDirectories(Info.path());
			XDateTime	Now=XDateTime::currentDateTime ();
			QString	FName=Info.path()+GetSeparator()+Info.completeBaseName()
								+Now.toString("_yyMMdd")+QString(".")+Info.suffix();
		
			char	LogFileName[1024];
			::QString2Char(FName,LogFileName,sizeof(LogFileName));

			FILE	*file=fopen(LogFileName,"a+t");
			if(file!=NULL){
				L->Write(file,LastCTime);
				fclose(file);
			}
			else{
				msleep(100);
			}
			LastCTime=L->CTime;
			delete	L;
		}
		else{
			msleep(100);
		}
	}
}

void	LogOutThread::AddLog(LogOutPacket *data)
{
	MutexLogOut.lock();
	data->CTime=::GetComputerMiliSec();
	LogOutData.AppendList(data);
	MutexLogOut.unlock();
}
LogOutPacket *LogOutThread::PickTopLog(void)
{
	MutexLogOut.lock();
	LogOutPacket *Ret=LogOutData.GetFirst();
	if(Ret!=NULL){
		LogOutData.RemoveList(Ret);
	}
	MutexLogOut.unlock();
	return Ret;
}

//===============================================================
LogOutClass::LogOutClass(const char *filename)
{
	if(filename!=NULL){
		strcpy(FileName,filename);
	}
	LThread=NULL;
}
LogOutClass::~LogOutClass(void)
{
	if(LThread!=NULL){
		delete	LThread;
	}
	LThread=NULL;
}

void	LogOutClass::Initial(char *filename)
{
	if(filename!=NULL){
		strcpy(FileName,filename);
	}
	if(LThread==NULL){
		LThread=new LogOutThread();
		LThread->FileName=FileName;
		LThread->start();
	}
}

void	LogOutClass::PutLog(int LineNo,const char *FuncName)
{
	if(LThread!=NULL){
		LogOutPacket	*c=new LogOutPacket(LineNo,FuncName);
		LThread->AddLog(c);
	}
}
	
void	LogOutClass::PutLogA1(int LineNo,const char *FuncName,int64 arg)
{
	if(LThread!=NULL){
		LogOutPacket	*c=new LogOutPacket(LineNo,FuncName);
		c->Arg1=arg;
		c->EnableArg1=true;
		LThread->AddLog(c);
	}
}
void	LogOutClass::PutLogA1(int LineNo,const char *FuncName,char *arg)
{
	if(LThread!=NULL){
		LogOutPacket	*c=new LogOutPacket(LineNo,FuncName);
		strncpy(c->Arg3,arg,sizeof(c->Arg3)-2);
		c->Arg3[sizeof(c->Arg3)-2]=0;
		c->Arg3[sizeof(c->Arg3)-1]=0;
		c->EnableArg3=true;
		LThread->AddLog(c);
	}
}
	
void	LogOutClass::PutLogR(int LineNo,const char *FuncName,bool retcode)
{
	if(LThread!=NULL){
		LogOutPacket	*c=new LogOutPacket(LineNo,FuncName);
		c->Ret1=retcode;
		c->EnableRet1=true;
		LThread->AddLog(c);
	}
}
void	LogOutClass::PutLogR(int LineNo,const char *FuncName,int64 retcode)
{
	if(LThread!=NULL){
		LogOutPacket	*c=new LogOutPacket(LineNo,FuncName);
		c->Ret2=retcode;
		c->EnableRet2=true;
		LThread->AddLog(c);
	}
}

void	LogOutClass::PutLogA1R(int LineNo,const char *FuncName,int64 arg,bool retcode)
{
	if(LThread!=NULL){
		LogOutPacket	*c=new LogOutPacket(LineNo,FuncName);
		c->Arg1=arg;
		c->EnableArg1=true;
		c->Ret1=retcode;
		c->EnableRet1=true;
		LThread->AddLog(c);
	}
}
void	LogOutClass::PutLogA1R(int LineNo,const char *FuncName,char *arg,bool retcode)
{
	if(LThread!=NULL){
		LogOutPacket	*c=new LogOutPacket(LineNo,FuncName);
		strncpy(c->Arg3,arg,sizeof(c->Arg3)-2);
		c->Arg3[sizeof(c->Arg3)-2]=0;
		c->Arg3[sizeof(c->Arg3)-1]=0;
		c->EnableArg3=true;
		c->Ret1=retcode;
		c->EnableRet1=true;
		LThread->AddLog(c);
	}
}
void	LogOutClass::PutLogA1R(int LineNo,const char *FuncName,int64 arg,int64 retcode)
{
	if(LThread!=NULL){
		LogOutPacket	*c=new LogOutPacket(LineNo,FuncName);
		c->Arg1=arg;
		c->EnableArg1=true;
		c->Ret2=retcode;
		c->EnableRet2=true;
		LThread->AddLog(c);
	}
}
void	LogOutClass::PutLogA1R(int LineNo,const char *FuncName,char *arg,int64 retcode)
{
	if(LThread!=NULL){
		LogOutPacket	*c=new LogOutPacket(LineNo,FuncName);
		strncpy(c->Arg3,arg,sizeof(c->Arg3)-2);
		c->Arg3[sizeof(c->Arg3)-2]=0;
		c->Arg3[sizeof(c->Arg3)-1]=0;
		c->EnableArg3=true;
		c->Ret2=retcode;
		c->EnableRet2=true;
		LThread->AddLog(c);
	}
}

void	LogOutClass::PutLogA2(int LineNo,const char *FuncName,int64 arg1,int64 arg2)
{
	if(LThread!=NULL){
		LogOutPacket	*c=new LogOutPacket(LineNo,FuncName);
		c->Arg1=arg1;
		c->EnableArg1=true;
		c->Arg2=arg2;
		c->EnableArg2=true;
		LThread->AddLog(c);
	}
}
void	LogOutClass::PutLogA2(int LineNo,const char *FuncName,char *arg1,int64 arg2)
{
	if(LThread!=NULL){
		LogOutPacket	*c=new LogOutPacket(LineNo,FuncName);
		c->Arg2=arg2;
		c->EnableArg2=true;
		strncpy(c->Arg3,arg1,sizeof(c->Arg3)-2);
		c->Arg3[sizeof(c->Arg3)-2]=0;
		c->Arg3[sizeof(c->Arg3)-1]=0;
		c->EnableArg3=true;
		LThread->AddLog(c);
	}
}
void	LogOutClass::PutLogA2(int LineNo,const char *FuncName,int64 arg1,char *arg2)
{
	PutLogA2(LineNo,FuncName,arg2,arg1);
}
void	LogOutClass::PutLogA2(int LineNo,const char *FuncName,char *arg1,char *arg2)
{
	if(LThread!=NULL){
		LogOutPacket	*c=new LogOutPacket(LineNo,FuncName);
		strncpy(c->Arg3,arg1,sizeof(c->Arg3)-2);
		c->Arg3[sizeof(c->Arg3)-2]=0;
		c->Arg3[sizeof(c->Arg3)-1]=0;
		c->EnableArg3=true;
		strncpy(c->Arg4,arg2,sizeof(c->Arg4)-2);
		c->Arg3[sizeof(c->Arg4)-2]=0;
		c->Arg3[sizeof(c->Arg4)-1]=0;
		c->EnableArg4=true;
		LThread->AddLog(c);
	}
}

void	LogOutClass::PutLogA2R(int LineNo,const char *FuncName,int64 arg1,int64 arg2,bool retcode)
{
	if(LThread!=NULL){
		LogOutPacket	*c=new LogOutPacket(LineNo,FuncName);
		c->Arg1=arg1;
		c->EnableArg1=true;
		c->Arg2=arg2;
		c->EnableArg2=true;
		c->Ret1=retcode;
		c->EnableRet1=true;
		LThread->AddLog(c);
	}
}
void	LogOutClass::PutLogA2R(int LineNo,const char *FuncName,char *arg1,int64 arg2,bool retcode)
{
	if(LThread!=NULL){
		LogOutPacket	*c=new LogOutPacket(LineNo,FuncName);
		c->Arg2=arg2;
		c->EnableArg2=true;
		strncpy(c->Arg3,arg1,sizeof(c->Arg3)-2);
		c->Arg3[sizeof(c->Arg3)-2]=0;
		c->Arg3[sizeof(c->Arg3)-1]=0;
		c->EnableArg3=true;
		c->Ret1=retcode;
		c->EnableRet1=true;
		LThread->AddLog(c);
	}
}
void	LogOutClass::PutLogA2R(int LineNo,const char *FuncName,int64 arg1,char *arg2,bool retcode)
{
	PutLogA2R(LineNo,FuncName,arg2,arg1,retcode);
}
void	LogOutClass::PutLogA2R(int LineNo,const char *FuncName,char *arg1,char *arg2,bool retcode)
{
	if(LThread!=NULL){
		LogOutPacket	*c=new LogOutPacket(LineNo,FuncName);
		strncpy(c->Arg3,arg1,sizeof(c->Arg3)-2);
		c->Arg3[sizeof(c->Arg3)-2]=0;
		c->Arg3[sizeof(c->Arg3)-1]=0;
		c->EnableArg3=true;
		strncpy(c->Arg4,arg2,sizeof(c->Arg4)-2);
		c->Arg3[sizeof(c->Arg4)-2]=0;
		c->Arg3[sizeof(c->Arg4)-1]=0;
		c->EnableArg4=true;
		c->Ret1=retcode;
		c->EnableRet1=true;
		LThread->AddLog(c);
	}
}
void	LogOutClass::PutLogA2R(int LineNo,const char *FuncName,int64 arg1,int64 arg2,int64 retcode)
{
	if(LThread!=NULL){
		LogOutPacket	*c=new LogOutPacket(LineNo,FuncName);
		c->Arg1=arg1;
		c->EnableArg1=true;
		c->Arg2=arg2;
		c->EnableArg2=true;
		c->Ret2=retcode;
		c->EnableRet2=true;
		LThread->AddLog(c);
	}
}
void	LogOutClass::PutLogA2R(int LineNo,const char *FuncName,char *arg1,int64 arg2,int64 retcode)
{
	if(LThread!=NULL){
		LogOutPacket	*c=new LogOutPacket(LineNo,FuncName);
		c->Arg2=arg2;
		c->EnableArg2=true;
		strncpy(c->Arg3,arg1,sizeof(c->Arg3)-2);
		c->Arg3[sizeof(c->Arg3)-2]=0;
		c->Arg3[sizeof(c->Arg3)-1]=0;
		c->EnableArg3=true;
		c->Ret2=retcode;
		c->EnableRet2=true;
		LThread->AddLog(c);
	}
}
void	LogOutClass::PutLogA2R(int LineNo,const char *FuncName,int64 arg1,char *arg2,int64 retcode)
{
	PutLogA2R(LineNo,FuncName,arg2,arg1,retcode);
}
void	LogOutClass::PutLogA2R(int LineNo,const char *FuncName,char *arg1,char *arg2,int64 retcode)
{
	if(LThread!=NULL){
		LogOutPacket	*c=new LogOutPacket(LineNo,FuncName);
		strncpy(c->Arg3,arg1,sizeof(c->Arg3)-2);
		c->Arg3[sizeof(c->Arg3)-2]=0;
		c->Arg3[sizeof(c->Arg3)-1]=0;
		c->EnableArg3=true;
		strncpy(c->Arg4,arg2,sizeof(c->Arg4)-2);
		c->Arg3[sizeof(c->Arg4)-2]=0;
		c->Arg3[sizeof(c->Arg4)-1]=0;
		c->EnableArg4=true;
		c->Ret2=retcode;
		c->EnableRet2=true;
		LThread->AddLog(c);
	}
}

//=======================================================================================

OperationLoggerFilter::OperationLoggerFilter(LayersBase *base, QObject *targetObj, QObject * parent)
	:QObject(parent),ServiceForLayers(base),TargetObj(targetObj)
{
	connect(targetObj,SIGNAL(destroyed()),this,SLOT(SlotDestroyed()));
}

OperationLoggerFilter::~OperationLoggerFilter(void)
{
	Release();
}

void	OperationLoggerFilter::Release(void)
{
	if(TargetObj!=NULL){
		TargetObj->removeEventFilter(this);
		TargetObj=NULL;
		disconnect(this,SLOT(SlotDestroyed()));
	}
}

void	OperationLoggerFilter::SlotDestroyed()
{
	if(TargetObj!=NULL){
		TargetObj->removeEventFilter(this);
		TargetObj=NULL;
	}
}

void	OperationLoggerFilter::MakeStringList(QObject *obj, QString &WhereIsObj ,QStringList &WhereIsObjList)
{
	for(QObject *b=obj;b!=NULL;b=b->parent()){
		WhereIsObjList.append(b->objectName());
	}
	for(int i=WhereIsObjList.count()-1;i>=0;i--){
		WhereIsObj=WhereIsObj+WhereIsObjList[i]+::GetSeparator();
	}
}

bool OperationLoggerFilter::eventFilter(QObject *obj, QEvent *event)
{
	int	type=event->type();
	if(type==QEvent::Close){
		obj->removeEventFilter(this);
		TargetObj=NULL;
	}
	QAbstractButton	*Button=dynamic_cast<QAbstractButton *>(obj);
	if(Button!=NULL){
		if(type==QEvent::KeyPress || type==QEvent::MouseButtonRelease){
			QString	ObjTitle=Button->text();
			QStringList	WhereIsObjList;
			QString	WhereIsObj;
			MakeStringList(obj, WhereIsObj ,WhereIsObjList);
			GetLayersBase()->GetOperationLoggerData()->PutLogPushButton(WhereIsObj,ObjTitle);
			return false;
		}
	}
	QLineEdit	*LEdit=dynamic_cast<QLineEdit *>(obj);
	if(LEdit!=NULL){
		if(type==QEvent::KeyPress){
			QString	ObjTitle=LEdit->text();
			QStringList	WhereIsObjList;
			QString	WhereIsObj;
			MakeStringList(obj, WhereIsObj ,WhereIsObjList);
			GetLayersBase()->GetOperationLoggerData()->PutLogKeyInput(WhereIsObj,ObjTitle);
			return false;
		}
	}
	QTableWidgetItem	*TableWidgetItem=dynamic_cast<QTableWidgetItem *>(obj);
	if(TableWidgetItem!=NULL){
		if(type==QEvent::MouseButtonDblClick){
			QStringList	WhereIsObjList;
			QString	WhereIsObj;
			MakeStringList(obj, WhereIsObj ,WhereIsObjList);
			GetLayersBase()->GetOperationLoggerData()->PutLogDoubleClick(WhereIsObj,TableWidgetItem->text(),TableWidgetItem->column(),TableWidgetItem->row());
			return false;
		}
		else if(type==QEvent::MouseButtonPress){
			QStringList	WhereIsObjList;
			QString	WhereIsObj;
			MakeStringList(obj, WhereIsObj ,WhereIsObjList);
			GetLayersBase()->GetOperationLoggerData()->PutLogClickGrid(WhereIsObj,TableWidgetItem->text(),TableWidgetItem->column(),TableWidgetItem->row());
			return false;
		}		
	}
	QListWidgetItem	*ListWidgetItem=dynamic_cast<QListWidgetItem *>(obj);
	if(ListWidgetItem!=NULL){
		QListWidget *L=ListWidgetItem->listWidget ();
		if(L!=NULL){
			if(type==QEvent::MouseButtonDblClick){
				QStringList	WhereIsObjList;
				QString	WhereIsObj;
				MakeStringList(obj, WhereIsObj ,WhereIsObjList);
				GetLayersBase()->GetOperationLoggerData()->PutLogDoubleClick(WhereIsObj,ListWidgetItem->text(),0,L->currentRow());
				return false;
			}
			else if(type==QEvent::MouseButtonPress){
				QStringList	WhereIsObjList;
				QString	WhereIsObj;
				MakeStringList(obj, WhereIsObj ,WhereIsObjList);
				GetLayersBase()->GetOperationLoggerData()->PutLogClickGrid(WhereIsObj,ListWidgetItem->text(),0,L->currentRow());
				return false;
			}
		}
	}
	QTreeWidgetItem	*TreeWidgetItem=dynamic_cast<QTreeWidgetItem *>(obj);
	if(TreeWidgetItem!=NULL){
		if(type==QEvent::MouseButtonDblClick){
			QStringList	WhereIsObjList;
			QString	WhereIsObj;
			MakeStringList(obj, WhereIsObj ,WhereIsObjList);
			GetLayersBase()->GetOperationLoggerData()->PutLogDoubleClick(WhereIsObj,TreeWidgetItem->text(0),0,0);
			return false;
		}
		else if(type==QEvent::MouseButtonPress){
			QStringList	WhereIsObjList;
			QString	WhereIsObj;
			MakeStringList(obj, WhereIsObj ,WhereIsObjList);
			GetLayersBase()->GetOperationLoggerData()->PutLogClickGrid(WhereIsObj,TreeWidgetItem->text(0),0,0);
			return false;
		}
	}
	QWidget	*w=dynamic_cast<QWidget	*>(obj);
	if(w!=NULL){
		QMouseEvent	*mv=dynamic_cast<QMouseEvent *>(event);
		if(mv!=NULL && type==QEvent::MouseButtonPress){
			QString	WName=typeid(w).name();
			QStringList	WhereIsObjList;
			QString	WhereIsObj;
			MakeStringList(obj, WhereIsObj ,WhereIsObjList);
			GetLayersBase()->GetOperationLoggerData()->PutLogMouseDown(WhereIsObj,WName,mv->x(),mv->y());
			return false;
		}
		if(mv!=NULL && type==QEvent::MouseButtonRelease){
			QString	WName=typeid(w).name();
			QStringList	WhereIsObjList;
			QString	WhereIsObj;
			MakeStringList(obj, WhereIsObj ,WhereIsObjList);
			GetLayersBase()->GetOperationLoggerData()->PutLogMouseRelease(WhereIsObj,WName,mv->x(),mv->y());
			return false;
		}
	}
	return false;
}


OperationLogger::OperationLogger(LayersBase *base)
	:ServiceForLayers(base)
{
	CheckLogFolder();
}
OperationLogger::~OperationLogger(void)
{
	Uninstall();
}

void	OperationLogger::PutLogStart			(const QString &Program)
{
	Install(GetLayersBase()->GetMainWidget());

	ProgramName	=Program;
	PutLog(/**/"Top","Start program",Program);
}
void	OperationLogger::PutLogClose			(void)
{
	PutLog(/**/"Top","Close program",ProgramName);
}
void	OperationLogger::PutLogKeyInput			(const QString &WhereIsObj ,const QString &str)
{
	PutLog(WhereIsObj,/**/"KeyInput",str);
}
void	OperationLogger::PutLogMouseDown		(const QString &WhereIsObj ,const QString &ObjTitle,int x ,int y)
{
	QString	Str=ObjTitle + QString(/**/" : X=")+QString::number(x)+QString(/**/",Y=")+QString::number(y);
	PutLog(WhereIsObj,/**/"MouseDown",Str);
}

void	OperationLogger::PutLogMouseRelease		(const QString &WhereIsObj ,const QString &ObjTitle,int x ,int y)
{
	QString	Str=ObjTitle + QString(/**/" : X=")+QString::number(x)+QString(/**/",Y=")+QString::number(y);
	PutLog(WhereIsObj,/**/"MouseRelease",Str);
}
void	OperationLogger::PutLogPushButton		(const QString &WhereIsObj ,const QString &ObjTitle)
{
	PutLog(WhereIsObj,/**/"PushButton",ObjTitle);
}

void	OperationLogger::PutLogClickGrid		(const QString &WhereIsObj ,const QString &ObjTitle,int x ,int y)
{
	QString	Str=ObjTitle + QString(/**/" : X=")+QString::number(x)+QString(/**/",Y=")+QString::number(y);
	PutLog(WhereIsObj,/**/"ClickGrid",Str);
}
void	OperationLogger::PutLogDoubleClick		(const QString &WhereIsObj ,const QString &ObjTitle,int x ,int y)
{
	QString	Str=ObjTitle + QString(/**/" : X=")+QString::number(x)+QString(/**/",Y=")+QString::number(y);
	PutLog(WhereIsObj,/**/"DoubleClick",Str);
}

const	QString	DateFormat=/**/"yyyy-MM-dd";

void	OperationLogger::PutLog(const QString &WhereIsObj ,const QString &ActionMsg,const QString &Msg)
{
	QDir::setCurrent(GetLayersBase()->GetUserPath());
	QDate	Now=QDate::currentDate();
	if(CNow.isNull()==true || Now!=CNow){
		CheckLogFolder();
	}
	QTime	Time=QTime::currentTime();
	int	CurrentHour=Time.hour();
	QString	PathFilePath=GetParamGlobal()->OperationLogFolder+GetSeparator()+QString(/**/"Log")+ProgramName+QString(/**/"#")+Now.toString(DateFormat);
	QString	PathFileName=PathFilePath
						+GetSeparator()
						+QString(/**/"LogHour-")+QString::number(CurrentHour)+QString(/**/".txt");
	ForceDirectories(PathFilePath);

	QFile	File(PathFileName);
	if(File.open(QIODevice::Append)==true){
		QTextStream	Txt(&File);
		Txt<<Time.toString() +QString(/**/"  ")+WhereIsObj +QString(/**/" Act:")+ActionMsg +QString(/**/" :")+Msg +	QString(/**/"\r\n");
		File.flush();
	}
}
void	OperationLogger::CheckLogFolder(void)
{
	QDate	Now=QDate::currentDate();
	CNow=Now;
	QStringList	List;
	List.append(/**/"Log*");
	QDir	dir(GetParamGlobal()->OperationLogFolder);
	QFileInfoList	DirInfo=dir.entryInfoList(List,QDir::Dirs | QDir::NoDotAndDotDot);
	for(int i=0;i<DirInfo.count();i++){
		QString	FolderName=DirInfo[i].baseName();
		QStringList	FList=FolderName.split('#');
		if(FList.count()>=2){
			QString	DateStr=FList[1];
			QDate	D=QDate::fromString(DateStr,DateFormat);
			int	days=D.daysTo(Now);
			if(days>GetParamGlobal()->OperationLogDaysToKeep){
				RemoveLogFolder(GetParamGlobal()->OperationLogFolder+GetSeparator()+FolderName);
			}
		}
	}
}
void	OperationLogger::RemoveLogFolder(const QString &FolderName)
{
	QStringList	List;
	List.append(/**/"*.*");
	QDir	dir(FolderName);
	QFileInfoList	FileInfo=dir.entryInfoList(List,QDir::Files | QDir::NoDotAndDotDot);
	for(int i=0;i<FileInfo.count();i++){
		dir.remove(FileInfo[i].fileName());
	}
	dir.rmdir(FolderName);
}


void	OperationLogger::Install(QObject *window)
{
	if(window!=NULL){
		for(int i=0;i<window->children().count();i++){
			QObject	*obj=window->children()[i];
			OperationLoggerFilter	*filter=new OperationLoggerFilter(GetLayersBase(),obj);
			obj->installEventFilter(filter);
			OperationLoggerFilterContainer.AppendList(filter);
			Install(obj);
		}
	}
}

void	OperationLogger::Uninstall(void)
{
	OperationLoggerFilterContainer.RemoveAll();
}
