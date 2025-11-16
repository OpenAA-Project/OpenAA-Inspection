#include "XMaintainer.h"
#include "XGeneralFunc.h"
#include <QDateTime>
#include "Maintainer.h"
#include "XForWindows.h"

QString	GetDriveName(const QString &PathName)
{
	QDir	D(PathName);
	QString	AbsPath=D.absolutePath();
	QStringList	List=AbsPath.split(/**/':');
	if(List.count()>=2){
		return List[0];
	}
	return /**/"";
}

MaintainerSetting::MaintainerSetting(void)
{
	UseDaysToKeepTerm	=true;
	UseMonthsToKeepTerm	=false;
	TermDaysToKeep		=90;
	TermMonthsToKeep	=3;
	PrioritySpace		=false;
	SpaceGBRemaining	=2;
	CheckingHour		=0;
	CheckingMinute		=0;
}

bool	MaintainerSetting::Save(QIODevice *f)
{
	int32	Ver=2;

	if(::Save(f,Ver					)==false)	return false;
	if(::Save(f,UseDaysToKeepTerm	)==false)	return false;
	if(::Save(f,UseMonthsToKeepTerm	)==false)	return false;
	if(::Save(f,TermDaysToKeep		)==false)	return false;
	if(::Save(f,TermMonthsToKeep	)==false)	return false;
	if(::Save(f,PrioritySpace		)==false)	return false;
	if(::Save(f,SpaceGBRemaining	)==false)	return false;
	if(::Save(f,FileNames			)==false)	return false;
	if(::Save(f,FolderNames			)==false)	return false;
	if(::Save(f,CheckingHour		)==false)	return false;
	if(::Save(f,CheckingMinute		)==false)	return false;
	if(::Save(f,DestinationPath		)==false)	return false;
	return true;
}
bool	MaintainerSetting::Load(QIODevice *f)
{
	int32	Ver;
	if(::Load(f,Ver					)==false)	return false;
	if(::Load(f,UseDaysToKeepTerm	)==false)	return false;
	if(::Load(f,UseMonthsToKeepTerm	)==false)	return false;
	if(::Load(f,TermDaysToKeep		)==false)	return false;
	if(::Load(f,TermMonthsToKeep	)==false)	return false;
	if(::Load(f,PrioritySpace		)==false)	return false;
	if(::Load(f,SpaceGBRemaining	)==false)	return false;
	if(::Load(f,FileNames			)==false)	return false;
	if(::Load(f,FolderNames			)==false)	return false;
	if(::Load(f,CheckingHour		)==false)	return false;
	if(::Load(f,CheckingMinute		)==false)	return false;
	if(Ver>=2){
		if(::Save(f,DestinationPath	)==false)	return false;
	}
	return true;
}
bool	MaintainerSetting::IsOlder(const QDateTime &FileStamp , const QDateTime &CurrentTime)
{
	if(UseDaysToKeepTerm==true){
		if(FileStamp.daysTo(CurrentTime)>TermDaysToKeep){
			return true;
		}
	}
	else
	if(UseMonthsToKeepTerm==true){
		int	year=CurrentTime.date().year();
		int	month=CurrentTime.date().month();
		int	day	=CurrentTime.date().day();
		month-=TermMonthsToKeep;
		while(month<1){
			year--;
			month+=12;
		}
		QDateTime	tm(QDate(year,month,day),CurrentTime.time());
		if(FileStamp<tm){
			return true;
		}
	}
	return false;
}

//=====================================================================================
MFileList::MFileList(const QFileInfo &Info)
{
	AbsFileName	=Info.absoluteFilePath();
	FileSize	=Info.size();
	TimeStamp	=Info.lastModified();
}
int	MFileList::Compare(MFileList &src)
{
	if(TimeStamp<src.TimeStamp)
		return -1;
	if(TimeStamp>src.TimeStamp)
		return 1;
	return 0;
}
//=====================================================================================

MaintainThread::MaintainThread(Maintainer *p,QObject * parent)
	:QThread(parent),Parent(p)
{
	Terminated		=false;
	WaitingMilisec	=1000;
}
void MaintainThread::run ()
{
	while(Terminated==false){
		QDateTime	Now=QDateTime::currentDateTime();
		if((Now.time().hour()==Parent->DeleteData.CheckingHour
		&& Now.time().minute()==Parent->DeleteData.CheckingMinute)
		|| Parent->ModeExecuteNow==true){
			Parent->ModeExecuteNow	=false;
			NPListPack<MFileList>	AliveFiles;
			QStringList				DriveNames;

			for(int i=0;i<Parent->DeleteData.FileNames.count();i++){
				QString	FileName=Parent->DeleteData.FileNames[i];
				QFileInfo	FInfo(FileName);
				QString	tPath=FInfo.path();
				QDir	CD(tPath);
				QStringList	Filter;
				Filter.append(FInfo.fileName());
				QFileInfoList TInfo=CD.entryInfoList (Filter,QDir::NoDotAndDotDot | QDir::Files);
				Parent->Step();
				msleep(1000);

				for(int j=0;j<TInfo.count();j++){
					QString	s=TInfo[j].absoluteFilePath();
					QString	Drive=GetDriveName(s);
					if(DriveNames.contains(Drive)==false){
						DriveNames.append(Drive);
					}
					if(Parent->DeleteData.IsOlder(TInfo[j].lastModified (),Now)==true){
						if(QFile::remove(s)==true){
							Parent->DoneRemoveFile(s);
						}
						msleep(WaitingMilisec);
					}
					else{
						MFileList	*a=new MFileList(TInfo[j]);
						AliveFiles.AppendList(a);
					}
					if(Terminated==true){
						return;
					}
					Parent->Step();
				}
			}
			for(int i=0;i<Parent->DeleteData.FolderNames.count();i++){
				QString	FolderName=Parent->DeleteData.FolderNames[i];
				QFileInfo	FInfo(FolderName);
				QString	Drive=GetDriveName(FInfo.absoluteFilePath());
				if(DriveNames.contains(Drive)==false){
					DriveNames.append(Drive);
				}
				QString	tPath=FInfo.path();
				QDir	CD(tPath);
				QStringList	Filter;
				QString	tFileName=FInfo.fileName();
				Filter.append(tFileName);
				QFileInfoList TInfo=CD.entryInfoList (Filter,QDir::NoDotAndDotDot | QDir::Dirs);
				msleep(WaitingMilisec);

				for(int j=0;j<TInfo.count();j++){
					QString	s=TInfo[j].absoluteFilePath();
					if(RemoveAllFilesAndFolder(s,Now,AliveFiles)==false){
						QString	pth=TInfo[j].filePath();
						CD.rmdir(pth);
						Parent->DoneRemoveDir(pth);
						msleep(WaitingMilisec);
					}
					if(Terminated==true){
						return;
					}
					Parent->Step();
				}
			}
			int64	Space=0;
			for(int i=0;i<DriveNames.count();i++){
				char	DriveStr[100];
				::QString2Char(DriveNames[i] ,DriveStr,sizeof(DriveStr)-1);
				strcat(DriveStr,/**/":");
				Space+=MtGetDiskFreeSpace(DriveStr);
				msleep(WaitingMilisec);
				if(Terminated==true){
					return;
				}
			}
			if(Space<((int64)Parent->DeleteData.SpaceGBRemaining)*((int64)1000000000)){
				if(Parent->DeleteData.PrioritySpace==true){
					AliveFiles.Sort();
					for(MFileList *a=AliveFiles.GetFirst();a!=NULL;a=a->GetNext()){
						if(QFile::remove(a->AbsFileName)==true){
							Parent->DoneRemoveFile(a->AbsFileName);
							Space+=a->FileSize;
							if(Space>((int64)Parent->DeleteData.SpaceGBRemaining)*((int64)1000000000)){
								break;
							}
							if(Terminated==true){
								return;
							}
							Parent->Step();
						}
					}
				}
			}
		}
		if(Now.time().hour()	==Parent->BackupData.CheckingHour
		&& Now.time().minute()	==Parent->BackupData.CheckingMinute
		&& Parent->BackupData.DestinationPath.isEmpty()==false){
			NPListPack<MFileList>	AliveFiles;
			QStringList				DriveNames;

			for(int i=0;i<Parent->BackupData.FileNames.count();i++){
				QString	FileName=Parent->BackupData.FileNames[i];
				QFileInfo	FInfo(FileName);
				QString	tPath=FInfo.path();
				QDir	CD(tPath);
				QStringList	Filter;
				Filter.append(FInfo.fileName());
				QFileInfoList TInfo=CD.entryInfoList (Filter,QDir::NoDotAndDotDot | QDir::Files);
				Parent->Step();
				msleep(1000);

				for(int j=0;j<TInfo.count();j++){
					QString	s=TInfo[j].absoluteFilePath();
					QString	Drive=GetDriveName(s);
					if(DriveNames.contains(Drive)==false){
						DriveNames.append(Drive);
					}
					if(Parent->BackupData.IsOlder(TInfo[j].lastModified (),Now)==true){
						QString	fname=TInfo[j].fileName();
						QString	DestName=Parent->BackupData.DestinationPath+::GetSeparator()+fname;
						if(QFile::copy ( s, DestName )==true){
							if(QFile::remove(s)==true){
								Parent->DoneBackupFile(s);
							}
						}
						msleep(WaitingMilisec);
					}
					else{
						MFileList	*a=new MFileList(TInfo[j]);
						AliveFiles.AppendList(a);
					}
					if(Terminated==true){
						return;
					}
					Parent->Step();
				}
			}
			for(int i=0;i<Parent->BackupData.FolderNames.count();i++){
				QString	FolderName=Parent->BackupData.FolderNames[i];
				QFileInfo	FInfo(FolderName);
				QString	Drive=GetDriveName(FInfo.absoluteFilePath());
				if(DriveNames.contains(Drive)==false){
					DriveNames.append(Drive);
				}
				QString	tPath=FInfo.path();
				QDir	CD(tPath);
				QStringList	Filter;
				QString	tFileName=FInfo.fileName();
				Filter.append(tFileName);
				QFileInfoList TInfo=CD.entryInfoList (Filter,QDir::NoDotAndDotDot | QDir::Dirs);
				msleep(WaitingMilisec);

				for(int j=0;j<TInfo.count();j++){
					QString	s=TInfo[j].absoluteFilePath();
					if(BackupAllFilesAndFolder(s,Now,AliveFiles)==false){
						QString	pth=TInfo[j].filePath();
						CD.rmdir(pth);
						Parent->DoneRemoveDir(pth);
						msleep(WaitingMilisec);
					}
					if(Terminated==true){
						return;
					}
					Parent->Step();
				}
			}
			int64	Space=0;
			for(int i=0;i<DriveNames.count();i++){
				char	DriveStr[100];
				::QString2Char(DriveNames[i] ,DriveStr,sizeof(DriveStr)-1);
				strcat(DriveStr,/**/":");
				Space+=MtGetDiskFreeSpace(DriveStr);
				msleep(WaitingMilisec);
				if(Terminated==true){
					return;
				}
			}
			if(Space<((int64)Parent->BackupData.SpaceGBRemaining)*((int64)1000000000)){
				if(Parent->BackupData.PrioritySpace==true){
					AliveFiles.Sort();
					for(MFileList *a=AliveFiles.GetFirst();a!=NULL;a=a->GetNext()){
						if(QFile::remove(a->AbsFileName)==true){
							Parent->DoneRemoveFile(a->AbsFileName);
							msleep(WaitingMilisec);
							Space+=a->FileSize;
							if(Space>((int64)Parent->BackupData.SpaceGBRemaining)*((int64)1000000000)){
								break;
							}
							if(Terminated==true){
								return;
							}
							Parent->Step();
						}
					}
				}
			}
		}
		msleep(2000);
	}
}

bool	MaintainThread::RemoveAllFilesAndFolder(const QString &Path ,const QDateTime &CurrentTime,NPListPack<MFileList> &AliveFiles)
{
	bool	KeepFile=false;
	QDir	CD(Path);
	QStringList	Filter;
	Filter.append(/**/"*.*");
	QFileInfoList TInfo=CD.entryInfoList (Filter,QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
	msleep(WaitingMilisec);
	Parent->SetMaxStep("Deleting"
						,Path,TInfo.count());

	for(int i=0;i<TInfo.count();i++){
		while(Parent->NowOnShowing==false){
			msleep(10);
		}
		if(TInfo[i].isDir()==true){
			QString	s=TInfo[i].absoluteFilePath();
			if(RemoveAllFilesAndFolder(s,CurrentTime,AliveFiles)==false){
				QString	p=TInfo[i].filePath();
				CD.rmdir(p);
				Parent->DoneRemoveDir(p);
				msleep(WaitingMilisec);
			}
			Parent->Step();
		}
		else{
			if(Parent->DeleteData.IsOlder(TInfo[i].lastModified (),CurrentTime)==true){
				QString	s=TInfo[i].absoluteFilePath();
				if(QFile::remove(s)==true){
					Parent->DoneRemoveFile(s);
				}
				msleep(1);
			}
			else{
				MFileList	*a=new MFileList(TInfo[i]);
				AliveFiles.AppendList(a);
				KeepFile=true;
			}
			Parent->Step();
		}
		if(Terminated==true){
			return true;
		}
	}
	return KeepFile;
}

bool	MaintainThread::BackupAllFilesAndFolder(const QString &Path ,const QDateTime &CurrentTime,NPListPack<MFileList> &AliveFiles)
{
	bool	KeepFile=false;
	QDir	CD(Path);
	QStringList	Filter;
	Filter.append(/**/"*.*");
	QFileInfoList TInfo=CD.entryInfoList (Filter,QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
	msleep(WaitingMilisec);
	Parent->SetMaxStep("Backup"
						,Path,TInfo.count());

	for(int i=0;i<TInfo.count();i++){
		while(Parent->NowOnShowing==false){
			msleep(10);
		}
		if(TInfo[i].isDir()==true){
			QString	s=TInfo[i].absoluteFilePath();
			if(RemoveAllFilesAndFolder(s,CurrentTime,AliveFiles)==false){
				QString	p=TInfo[i].filePath();
				CD.rmdir(p);
				Parent->DoneRemoveDir(p);
				msleep(WaitingMilisec);
			}
			Parent->Step();
		}
		else{
			if(Parent->DeleteData.IsOlder(TInfo[i].lastModified (),CurrentTime)==true){
				QString	s=TInfo[i].absoluteFilePath();
				QString	fname=TInfo[i].fileName();
				QString	DestName=Parent->BackupData.DestinationPath+::GetSeparator()+fname;
				if(QFile::copy ( s, DestName )==true){
					if(QFile::remove(s)==true){
						Parent->DoneBackupFile(s);
					}
				}
				msleep(1);
			}
			else{
				MFileList	*a=new MFileList(TInfo[i]);
				AliveFiles.AppendList(a);
				KeepFile=true;
			}
			Parent->Step();
		}
		if(Terminated==true){
			return true;
		}
	}
	return KeepFile;
}