/*
 * Copyright (C) 2023
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

#include "XCopyMultiple.h"
#include "XGeneralFunc.h"
#include "XForWindows.h"



CopyMultipleData::FoundFileClass::FoundFileClass(CopyMultipleData	*parent)
{
	int	NLen=parent->GetDestCount();
	CopiedState=new State[NLen];
	for(int i=0;i<NLen;i++){
		CopiedState[i]=_NotYet;
	}
}

CopyMultipleData::FoundFileClass::~FoundFileClass(void)
{
	delete	[]CopiedState;
	CopiedState=NULL;
}

//-------------------------------------------------
CopyMultipleData::~CopyMultipleData(void)
{
	if(ThreadCopyDim!=NULL){
		delete	[]ThreadCopyDim;
	}
	ThreadCopyDim=NULL;
}
int		CopyMultipleData::GetDestCount(void)
{
	for(int i=Destinations.count()-1;i>=0;i++){
		if(Destinations[i].isEmpty()==false){
			return i+1;
		}
	}
	return 0;
}

bool	CopyMultipleData::SaveFilter(QIODevice *f)
{
	if(::Save(f,SearchFilter)==false)
		return false;
	if(::Save(f,ExcludedFilter)==false)
		return false;
	return true;
}

bool	CopyMultipleData::LoadFilter(QIODevice *f)
{
	if(::Load(f,SearchFilter)==false)
		return false;
	if(::Load(f,ExcludedFilter)==false)
		return false;
	return true;
}

bool	CopyMultipleData::Save(QIODevice *f)
{
	if(::Save(f,SourcePath)==false)
		return false;
	if(SaveFilter(f)==false)
		return false;
	if(::Save(f,Destinations)==false)
		return false;
	return true;
}

bool	CopyMultipleData::Load(QIODevice *f)
{
	if(::Load(f,SourcePath)==false)
		return false;
	if(LoadFilter(f)==false)
		return false;
	if(::Load(f,Destinations)==false)
		return false;
	return true;
}

void	CopyMultipleData::MakeFoundList(void)
{
	SourceFiles.RemoveAll();
	MakeFoundList(SourcePath);
}

void	CopyMultipleData::MakeFoundList(const QString &pathname)
{
	QDir	Dir(pathname);
	QFileInfoList	SInfo=Dir.entryInfoList(SearchFilter  ,QDir::NoDotAndDotDot | QDir::Files);
	QFileInfoList	EInfo;
	if(ExcludedFilter.count()!=0){
		EInfo=Dir.entryInfoList(ExcludedFilter,QDir::NoDotAndDotDot | QDir::Files);
	}

	for(int i=0;i<SInfo.count();i++){
		bool	Eliminated=false;
		QString	LFileName=SInfo[i].absoluteFilePath();
		for(int j=0;j<EInfo.count();j++){
			if(LFileName==EInfo[j].absoluteFilePath()){
				Eliminated=true;
				break;
			}
		}
		if(Eliminated==false){
			FoundFileClass	*c=new FoundFileClass(this);
			c->FoundFile=LFileName;
			SourceFiles.AppendList(c);
		}
	}
	QFileInfoList	DInfo=Dir.entryInfoList(QDir::NoDotAndDotDot |QDir::AllDirs);
	for(int i=0;i<DInfo.count();i++){
		QString	s=DInfo[i].absoluteFilePath();
		MakeFoundList(s);
	}
}
void	CopyMultipleData::StartCopy(QWidget *parent)
{
	TerminateCopy=false;
	if(ThreadCopyDim!=NULL){
		delete	[]ThreadCopyDim;
	}
	int	N=GetDestCount();
	ThreadCopyDim=new ThreadCopy*[N];
	for(int i=0;i<N;i++){
		QString	dName=Destinations[i];
		ThreadCopyDim[i]=new ThreadCopy(this,dName,i,parent);
		connect(ThreadCopyDim[i],SIGNAL(finished()),this,SLOT(FinishedThreadCopy()),Qt::QueuedConnection);
	}
	for(int i=0;i<N;i++){
		ThreadCopyDim[i]->start();
	}
}

void	CopyMultipleData::FinishedThreadCopy()
{
	int	N=GetDestCount();
	if(ThreadCopyDim!=NULL){
		for(int i=0;i<N;i++){
			if(ThreadCopyDim[i]!=NULL){
				return;
			}
		}
	}
	emit	SignalFinishCopy();
}





//=============================================================================

ThreadCopy::ThreadCopy(CopyMultipleData *_DataParent 
				,const QString &_DestPath ,int DestN
				,QObject *parent)
:QThread(parent)
{
	DataParent	=_DataParent;
	DestPath	=_DestPath;
	DestNumber	=DestN;
}


void ThreadCopy::run ()
{
	for(CopyMultipleData::FoundFileClass *c=DataParent->SourceFiles.GetFirst();c!=NULL;c=c->GetNext()){
		if(DataParent->TerminateCopy==true){
			break;
		}
		QFileInfo	Info(c->FoundFile);
		QString		NewFileName;
		//QString		NewFileName=DestPath;
		//if(DestPath.right(1)!=::GetSeparator()){
		//	NewFileName=NewFileName+::GetSeparator();
		//}
		QString OldPath=DataParent->SourcePath;
		OldPath.replace("\\","/");
		QString OldName=Info.filePath();
		NewFileName=OldName.replace(OldPath,DestPath);
		OldName.remove(Info.fileName());
		QDir Dir;
		if(Dir.cd(OldName)==false)
			if((Dir.mkdir(OldName)==false))
				makeDirectory(OldName ,OldPath);
		if(MTCopyFile(c->FoundFile, NewFileName,false)==true){
		//if(QFile::copy ( c->FoundFile, NewFileName)==true){
			c->CopiedState[DestNumber]=CopyMultipleData::FoundFileClass::_Copied;
		}
		else{
			c->CopiedState[DestNumber]=CopyMultipleData::FoundFileClass::_NotCopied;
		}
	}
	DataParent->ThreadCopyDim[DestNumber]=NULL;
	deleteLater();
}

bool ThreadCopy::makeDirectory(QString pathname, QString oldpath)
{
	bool r = true;
	int nPathNameLen = pathname.length();
	int nPos = nPathNameLen - oldpath.length();
	QString strPathName = pathname;

	while(nPos-- > 0)
	{
		int nLen = nPathNameLen - nPos;
		if(strPathName[nLen] == '/'){
			QString strDir = strPathName.left(nLen);
			QDir dir;
			if(dir.mkdir(strDir)) r=false;
		}
	}
	return r;
}