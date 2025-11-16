#include "ReportDisk.h"
#include <QFileInfo>
#include <QString>
#include <QDir>
#include "XCSV.h"
#include "XForWindows.h"
#include "XGeneralFunc.h"

ThreadDiskChecker::ThreadDiskChecker(ReportDisk *parent)
:QThread(parent)
{
	Parent		=parent;
	CloseMode	=false;
	ModeForce	=false;
}

void ThreadDiskChecker::run()
{
	bool	Disk1Alerted=false;
	bool	Disk2Alerted=false;
	bool	Disk3Alerted=false;
	bool	Disk4Alerted=false;
	int		LoopCounter=0;
	for(;;){
		msleep(10000);

		int64 FreeSpace1;
		int64 FreeSpace2;
		int64 FreeSpace3;
		int64 FreeSpace4;

		if(CheckDisk(DiskPath1,AlertSpace1,FreeSpace1)==false){
			if(Disk1Alerted==false){
				ErrorOut(DiskPath1);
				Disk1Alerted=true;
			}
		}
		else{
			Disk1Alerted=false;
		}

		if(CheckDisk(DiskPath2,AlertSpace2,FreeSpace2)==false){
			if(Disk2Alerted==false){
				ErrorOut(DiskPath2);
				Disk2Alerted=true;
			}
		}
		else{
			Disk2Alerted=false;
		}

		if(CheckDisk(DiskPath3,AlertSpace3,FreeSpace3)==false){
			if(Disk3Alerted==false){
				ErrorOut(DiskPath3);
				Disk3Alerted=true;
			}
		}
		else{
			Disk3Alerted=false;
		}

		if(CheckDisk(DiskPath4,AlertSpace4,FreeSpace4)==false){
			if(Disk4Alerted==false){
				ErrorOut(DiskPath4);
				Disk4Alerted=true;
			}
		}
		else{
			Disk4Alerted=false;
		}

		if((LoopCounter%4)==0 && DiskPath1!=/**/""){
			ReportOut(DiskPath1,FreeSpace1);
		}
		if((LoopCounter%4)==1 && DiskPath2!=/**/""){
			ReportOut(DiskPath2,FreeSpace2);
		}
		if((LoopCounter%4)==2 && DiskPath3!=/**/""){
			ReportOut(DiskPath3,FreeSpace3);
		}
		if((LoopCounter%4)==3 && DiskPath4!=/**/""){
			ReportOut(DiskPath4,FreeSpace4);
		}

		if((LoopCounter%60)==40 && DiskPath1!=/**/""){
			if(AutoMode==true){
				ScanDisk(DiskPath1);
			}
		}
		if((LoopCounter%60)==41 && DiskPath2!=/**/""){
			if(AutoMode==true){
				ScanDisk(DiskPath2);
			}
		}
		if((LoopCounter%60)==42 && DiskPath3!=/**/""){
			if(AutoMode==true){
				ScanDisk(DiskPath3);
			}
		}
		if((LoopCounter%60)==43 && DiskPath4!=/**/""){
			if(AutoMode==true){
				ScanDisk(DiskPath4);
			}
		}
		if(ModeForce==true){
			if(AutoMode==true){
				if(DiskPath1!=/**/""){
					ScanDisk(DiskPath1);
				}
				if(DiskPath2!=/**/""){
					ScanDisk(DiskPath2);
				}
				if(DiskPath3!=/**/""){
					ScanDisk(DiskPath3);
				}
				if(DiskPath4!=/**/""){
					ScanDisk(DiskPath4);
				}
			}
			ModeForce=false;
		}
		LoopCounter++;
		if(CloseMode==true){
			return;
		}
	}
}

bool	ThreadDiskChecker::CheckDisk(QString Drive, int AlertSpace,int64 &FreeSpace)
{
	char	DriveBuff[256];

	QString2Char(Drive,DriveBuff ,sizeof(DriveBuff));

	FreeSpace=MtGetDiskFreeSpace(DriveBuff);
	if(FreeSpace<0)
		return true;
	if(FreeSpace<((int64)AlertSpace)*((int64)1024)){
		return false;
	}
	return true;
}


void	ThreadDiskChecker::ErrorOut(QString DiskPath)
{
	QString	Msg=ComputerName + QString(": ディスク (")+DiskPath+QString(")の容量不足");
	Parent->MClient.Send(2,0,Msg);
}

void	ThreadDiskChecker::ReportOut(QString DiskPath,int64 FreeSpace)
{
	//QString	CName;
	//MtGetComputerName(CName);

	QString	Msg=ComputerName+QString("(")+DiskPath+QString(")+空き容量=");
	if(FreeSpace>1024*1024*1024){
		double	m=((double)FreeSpace)/(1024.0*1024.0*1024.0);
		Msg=Msg+QString::number(m,'f',2)+QString("GB");
	}
	else if(FreeSpace>1024*1024){
		double	m=((double)FreeSpace)/(1024.0*1024.0);
		Msg=Msg+QString::number(m,'f',2)+QString("MB");
	}
	else if(FreeSpace>1024){
		double	m=((double)FreeSpace)/(1024.0);
		Msg=Msg+QString::number(m,'f',2)+QString("KB");
	}
	else{
		Msg=Msg+QString::number((int)FreeSpace)+QString("B");
	}

	Parent->MClient.Send(4,0,Msg);
}

bool ThreadDiskChecker::SaveSetting(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false)
		return false;
	if(::Save(f,AutoMode)==false)
		return false;
	if(::Save(f,PassedTime)==false)
		return false;
	if(::Save(f,RemoveMode)==false)
		return false;
	if(::Save(f,Destinations)==false)
		return false;
	return true;
}

bool ThreadDiskChecker::LoadSetting(QIODevice *f)
{
	int32	Ver=1;

	if(::Load(f,Ver)==false)
		return false;
	if(::Load(f,AutoMode)==false)
		return false;
	if(::Load(f,PassedTime)==false)
		return false;
	if(::Load(f,RemoveMode)==false)
		return false;
	if(::Load(f,Destinations)==false)
		return false;
	return true;
}

bool	ThreadDiskChecker::ScanDisk(QString &Path)
{
	QDir	Dir(Path);
	int64		PassedSec=PassedTime.to64();
	XDateTime	Now=XDateTime::currentDateTime();

	QStringList	List;
	List.append("*.*");

	QFileInfoList	FInfo=Dir.entryInfoList(List,QDir::Files);
	for(int i=0;i<FInfo.count();i++){
		int	d=PassedTime.secsTo(FInfo[i].lastModified ());
		if(d<0){
			QString	FileName =FInfo[i].absoluteFilePath();
			if(RemoveMode==true){
				QFile::remove(FileName);
			}
			else{
				bool	Success=false;
				for(int i=0;i<Destinations.count();i++){
					QString	DestFileName=Destinations[i]+GetSeparator()+FInfo[i].fileName();
					if(::MTCopyFile(FileName,DestFileName,false)==true){
						Success=true;
						break;
					}
				}
				if(Success==true){
					QFile::remove(FileName);
				}
			}
		}
	}
	QStringList	ListSubFolder;
	ListSubFolder.append("*");

	QFileInfoList	SubFolders=Dir.entryInfoList(ListSubFolder,QDir::Dirs | QDir::NoDotAndDotDot);
	for(int i=0;i<SubFolders.count();i++){
		QString	LPath=SubFolders[i].absoluteFilePath();
		ScanDisk(LPath);
	}

	return true;
}