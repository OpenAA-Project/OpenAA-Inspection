/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\AutoSaveImage\XAutoSaveImage.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include <QFileInfo>
#include <QDir>
#include "XAutoSaveImage.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"
#include "XGeneralStocker.h"
#include "PanelSaveImage.h";
#include "XForWindows.h"
#include "XLotInformation.h"


//===========================================

AutoSaveThread::AutoSaveThread(QObject * parent )
:QThread(parent)
{	
	Layer		=0;
	Base		=NULL;
	InspectionID=0;
	ClusterID	=0;
	LocalPageNo	=0;
	GlobalPageNo=0;

	SavedImage	=NULL;
	CompressBuff1=new BYTE[CompressBuffSize];
	CompressBuff2=new BYTE[CompressBuffSize];
	StartMode=false;	
}

AutoSaveThread::~AutoSaveThread(void)
{
	delete	[]CompressBuff1;
	delete	[]CompressBuff2;
	CompressBuff1=NULL;
	CompressBuff2=NULL;
	delete	SavedImage;
	SavedImage=NULL;
}

void	AutoSaveThread::Initial(int n ,AutoSaveImageInLayer *layer,AutoSaveImageBase *base)
{
	Base  = base;
	Layer = layer;
	//connect(this,SIGNAL(finished()),this,SLOT(SlotFinished()));
	RootPath=GetRootPath(n);
}

QString	AutoSaveThread::GetRootPath(int n)
{
	QString	Ret;
	switch(n%10){
		case 0:	Ret=Base->SavedFolder1;	break;
		case 1:	Ret=Base->SavedFolder2;	break;
		case 2:	Ret=Base->SavedFolder3;	break;
		case 3:	Ret=Base->SavedFolder4;	break;
		case 4:	Ret=Base->SavedFolder5;	break;
		case 5:	Ret=Base->SavedFolder6;	break;
		case 6:	Ret=Base->SavedFolder7;	break;
		case 7:	Ret=Base->SavedFolder8;	break;
		case 8:	Ret=Base->SavedFolder9;	break;
		case 9:	Ret=Base->SavedFolder10;	break;
	}
	return Ret;
}

bool	AutoSaveThread::SaveLayerTarget(void)
{
	ForceDirectories( FolderName );
	if(Layer->SaveLayerTarget(SavedImage, FolderName + "/" + FileName
				,CompressBuff1,CompressBuff2)==false){
		Base->GetLayersBase()->SendErrorToMaster(1 , "Error Save image" ,ErrorCodeList::_Important);
	}

	return true;
}

bool	AutoSaveThread::LoadLayerTarget(QString FileName)
{
	/*
	ImageBuffer *p = &SavedImage;
	Layer->LoadLayerTarget(&p, FileName);	//このLoad,Save二つの関数は互換性確保のため　不要なら消す
	*/
	return true;
}


bool	AutoSaveThread::CopyFromTarget(void)
{
	return CopyFrom(Layer->GetDataInLayer()->GetTargetBuff());
}
bool	AutoSaveThread::CopyFromMaster(void)
{
	return CopyFrom(Layer->GetDataInLayer()->GetMasterBuff());
}

struct	FoundFile
{
	QString		FileName;
	XDateTime	FileStamp;
};



bool	AutoSaveThread::CopyFrom(ImageBuffer &ImageBuff)
{
	QList<QVariant> Arguments;
	QList<QVariant> ReturnedValues;
	InspectionID  = Layer->GetLayersBase()->GetCurrentInspectIDForExecute();
	//LotID=Layer->GetLayersBase()->GetLotID();
	ClusterID  = Layer->GetLayersBase()->GetLotBase()->GetClusterID();
	LocalPageNo   = Layer->GetPage();
	GlobalPageNo  = Layer->GetLayersBase()->GetGlobalPageFromLocal(LocalPageNo);

	//FolderName = RootPath + ::GetSeparator() + Layer->MakeDirPath(RootPath, FolderName, LocalPageNo);
	//FileName = Layer->MakeFileName();
	DataInPage	*P=Layer->GetLayersBase()->GetPageData(LocalPageNo);

	bool	Flag=false;
	for(int i=0;i<10;i++){		
		FolderName = GetRootPath(i);
		FileName = FolderName +QDir::separator()+Layer->MakeFileName();
		QFileInfo	FInfo(FileName);
		FolderName	=FInfo.path();
		FileName	=FInfo.fileName();
		if(FolderName.mid(1,1)==QString(":")){
			char	buff[10];
			QString2Char(FolderName.mid(0,2),buff,10);
			int64	Len=MtGetDiskFreeSpace(buff);
			int64	ReqSize=((int64)P->GetDotPerLine()*(int64)P->GetMaxLines()*(int64)Base->GetLayerNumb(LocalPageNo)+100)*(int64)Base->GetPageNumb();
			if(Len>=ReqSize){
				Flag=true;
				break;
			}
		}
	}
	if(Flag==false)
		return false;

	AutoSaveImageBase	*ABase=(AutoSaveImageBase *)Layer->GetParentBase();
	if(ABase->MaxCountToSave>0){
		QStringList	FileList;
		for(int i=0;i<10;i++){		
			QString	iFolderName = GetRootPath(i);
			if(iFolderName.isEmpty()==false){
				QStringList	List=FindFiles(iFolderName,QString("*.piy"));
				FileList.append(List);
			}
		}
		if(ABase->StandardFolder==true){
			struct	FoundFile	*FoundFileDim=new struct FoundFile[FileList.count()];
			int	N=0;
			for(int i=0;i<FileList.count();i++){
				QFileInfo	FInfo(FileList[i]);
				QString		BaseName=FInfo.baseName();
				bool	ok;
				int	page =BaseName.mid(5,2).toInt(&ok);	if(ok==false)	continue;
				int	layer=BaseName.mid(8,2).toInt(&ok);	if(ok==false)	continue;
				if(Layer->GetLayer()==layer && ABase->GetLayersBase()->GetGlobalPageFromLocal(Layer->GetPage())==page){
					FoundFileDim[N].FileName=FileList[i];
					FoundFileDim[N].FileStamp=FInfo.lastModified();
					N++;
				}
			}
			int	NowN=N;
			while(NowN>ABase->MaxCountToSave){
				XDateTime	Oldest;
				int			Found=-1;
				for(int i=0;i<N;i++){
					if(FoundFileDim[i].FileName.isEmpty()==false){
						if(Found==-1){
							Oldest=FoundFileDim[i].FileStamp;
							Found=i;
						}
						else{
							if(Oldest>FoundFileDim[i].FileStamp){
								Oldest=FoundFileDim[i].FileStamp;
								Found=i;
							}
						}
					}
				}
				QFile	RFile(FoundFileDim[Found].FileName);
				RFile.remove();
				FoundFileDim[Found].FileName.clear();
				NowN--;
			}
			delete	[]FoundFileDim;
		}
	}


	int32 PartialDot = ((AutoSaveImageBase *)Layer->GetParentBase())->PartialDot;
	if(SavedImage==NULL){
		SavedImage=new ImageBuffer();
	}
	SavedImage->Set(0, 0, (P->GetDotPerLine()+PartialDot)/(PartialDot+1), (P->GetMaxLines()+PartialDot)/(PartialDot+1));

	if(PartialDot==0){
		*SavedImage=ImageBuff;
	}
	else{
		int	NYLen=Layer->GetMaxLines  ()/(PartialDot+1);
		int	NXLen=Layer->GetDotPerLine()/(PartialDot+1);
		for(int y=0;y<NYLen;y++){
			BYTE	*Src=ImageBuff.GetY(y*(PartialDot+1));
			BYTE	*Dst=SavedImage->GetY(y);
			int	Px=0;
			for(int x=0;x<NXLen;x++){
				Dst[x]=Src[Px];
				Px+=PartialDot+1;
			}
		}
	}
	return true;
}

void	AutoSaveThread::CopyToTarget(void)
{
	//Layer->GetDataInLayer()->GetTargetBuff()=*SavedImage;
}

void AutoSaveThread::run()
{
	for(;;){
		if(StartMode==true){
			SaveLayerTarget();
			StartMode=false;
		}
		msleep(200);
		if(Base->GetLayersBase()->GetOnTerminating()==true){
			break;
		}
	}
}

void AutoSaveThread::SlotFinished()
{
}



