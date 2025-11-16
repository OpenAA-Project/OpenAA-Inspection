#include "ThreadLogger.h"
#include "XCommandServer.h"
#include "XGeneralFunc.h"
#include <QDir>
#include <QFile>

LogLeaf::LogLeaf(ThreadLogger *parent)
{
	Parent	=parent;
	OpeCode	=-1;
	Result	=true;
}

bool	LogLeaf::WriteLog(void)
{
	QString	FileName=GetFileName();
	QFile	File(FileName);
	if(File.open(QIODevice::Append)==true){
		QTextStream out(&File);
		out<<CurrentTime.toString("yy/MM/dd hh:mm:ss");
		if(OpeCode>=0){
			out<<"    OpeCode: ";
			out<<OpeCode;
		}
		out<<"    Result: ";
		out<<((Result==true)?QString("Success"):QString("Fail"));
		out<<"\n";
		for(int i=0;i<Messages.count();i++){
			out<<Messages[i]<<"\n";
		}
		out<<"\n";
		return true;
	}
	return false;
}

void	LogLeaf::SetLog(int _OpeCode ,QStringList &Msg,bool _Result)
{
	CurrentTime	=XDateTime::currentDateTime();
	OpeCode		=_OpeCode;
	Messages	=Msg;
	Result		=_Result;
}

QString	LogLeaf::GetFileName(void)
{
	QString	LogOutPath=Parent->GetParent()->LogOutPath;

	QDir	Dir(LogOutPath);
	QStringList	NameFilter;
	NameFilter.append("*");
	QStringList	DirList=Dir.entryList(NameFilter,QDir::Dirs | QDir::NoDotAndDotDot,QDir::Name);
	while(DirList.count()>Parent->GetParent()->LoggedDays){
		QString	FolderName=DirList[0];
		DirList.removeAt(0);
		QStringList	FileFilter;
		FileFilter.append("*.log");
		QDir	FileDir(LogOutPath+::GetSeparator()+FolderName);
		QStringList	FileList=FileDir.entryList(FileFilter,QDir::Files,QDir::Name);
		for(int i=0;i<FileList.count();i++){
			QString	FileName=LogOutPath+::GetSeparator()+FolderName+::GetSeparator()+FileList[i];
			QFile::remove (FileName);
		}
		QDir	RmDir;
		Dir.rmdir(FolderName);
	}
	QString	CFolderName=CurrentTime.toString("yyMMdd");
	Dir.mkdir(CFolderName);
	QString	FileName=CurrentTime.toString("hhmm")+QString(".log");
	::ForceDirectories(LogOutPath+::GetSeparator()+CFolderName);
	return LogOutPath+::GetSeparator()+CFolderName+::GetSeparator()+FileName;
}

//===============================================================

ThreadLogger::ThreadLogger(XMLServerComm * parent)
	:QThread(parent)
{
	Parent	=parent;
	CloseMode=false;
}

	
void ThreadLogger::run()
{
	LogLeaf	*a;
	while(CloseMode==false){
		msleep(100);
		for(;;){
			LogMutex.lock();
			a=LogQueue.GetFirst();
			if(a!=NULL){
				LogQueue.RemoveList(a);
			}
			LogMutex.unlock();
			if(a==NULL){
				break;
			}
			a->WriteLog();
			delete	a;
		}
	}
}

void	ThreadLogger::Close(void)
{
	CloseMode=true;
}

void	ThreadLogger::AddLog(int OpeCode ,QStringList &Msg,bool Result)
{
	if(Parent->LogOut==true){
		LogLeaf	*a=new LogLeaf(this);
		a->SetLog(OpeCode,Msg,Result);
		LogMutex.lock();
		LogQueue.AppendList(a);
		LogMutex.unlock();
	}
}
