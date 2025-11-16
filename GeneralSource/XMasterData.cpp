/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XMasterData.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XTypeDef.h"
#include <QSqlQuery>
#include <QBuffer>
#include <QPainter>
#include <QImage>
#include <QSqlRecord>
#include "XDataInLayer.h"
#include "Regulus64Version.h"
#include "XDataInLayerCommander.h" 
#include "XDataInLayerCmdLocal.h"
#include "XGeneralFunc.h"
#include "XAlgorithmBase.h"
#include "XDatabaseLoader.h"
#include "XLightInterfaceDLL.h"
#include "XLightClass.h"
#include "XOutlineOffset.h"
#include "XDisplayImagePacket.h"
#include "XGUIInterfaceDLL.h"
#include "XGUI.h"
#include <omp.h>
#include "XTransFile.h"
#include "XGeneralStocker.h"
#include "XResultAnalizer.h"
#include "XDataInLayerToDisplayImage.h"
#include "Regulus64System.h"
#include "XMasterData.h"

bool	LayersBase::GetDulicatedData(int32 masterCode ,IntList &MachineList)
{
	QDir dirPath(GetParamGlobal()->ImageFilePath);
	QStringList filters;
	filters << QString("Image")+QString::number(masterCode)+QString("-*.img");
	dirPath.setNameFilters(filters);
	QFileInfoList lstFiles = dirPath.entryInfoList();

	for(int i=0;i<lstFiles.size();i++){
		QFileInfo fFile = lstFiles[i];
		QString	BaseName=fFile.baseName();
		int	d=BaseName.indexOf("Mac");
		QString	s=BaseName.mid(d+3);
		QString	Num=s.section('.',0,0);
		bool	ok;
		int	Mac=Num.toInt(&ok);
		if(ok==false){
			continue;
		}
		if(MachineList.IsInclude(Mac)==false){
			MachineList.Add(Mac);
		}
	}
	return true;
}
int		LayersBase::SQLCreateNewMasterRelation(const QString &RelationNumber
											,  const QString &RelationName 
											,  const QString &Remark 
											,  int RelationType
											,  int32 ThresholdLevelID)
{
	int RetRelationCode=0;
	if(GetDatabaseLoader()){
		QByteArray	DummyCommonData;
		if(GetDatabaseLoader()->G_CreateNewMasterRelation(GetDatabase() ,RetRelationCode
										,RelationNumber
										,RelationName
										,Remark
										,RelationType
										,DummyCommonData
										,ThresholdLevelID)==false){
			return -1;
		}
		return RetRelationCode;
	}
	return -1;
}

bool	LayersBase::SQLSetRelationOnMasterData(int masterCode ,int RelationCode ,int RelationID)
{
	if(GetDatabaseLoader()){
		return GetDatabaseLoader()->G_SetRelationOnMasterData(GetDatabase() ,masterCode ,RelationCode ,RelationID);
	}
	return false;
}

int		LayersBase::SQLSearchMasterCode(int RelationCode ,RelationMasterList MasterListDim[] ,int MaxListCount)
{
	if(GetDatabaseLoader()){
		return GetDatabaseLoader()->G_SearchMasterCode(GetDatabase() ,RelationCode ,MasterListDim ,MaxListCount);
	}
	return false;
}

int		LayersBase::SQLGetRelationCode(int MasterCode)
{
	if(GetDatabaseLoader()){
		return GetDatabaseLoader()->G_GetRelationCode(GetDatabase() ,MasterCode);
	}
	return false;
}

int	LayersBase::SQLSaveNewMasterData(const QString &_MasterName 
									,const QString &_Remark 
									,int32 _CategoryID
									,const QString &ImagePath
									,QString &ErrorMessageOfFalse)
{
	MasterName	=_MasterName;
	Remark		=_Remark;
	CategoryID	=_CategoryID;
	SetMaxProcessing(1);
	GetLayersBase()->LockForLoadSave();
	if(GetDatabaseLoader()){
		bool	NewOK=false;
		for(int i=0;i<10;i++){
			MasterCode=GetDatabaseLoader()->G_SQLSaveNewMasterData(GetDatabase() ,this);
			if(MasterCode!=0){
				NewOK=true;
				break;
			}
			GSleep(10000);
		}
		if(NewOK==false){
			GetLayersBase()->UnlockForLoadSave();
			GSleep(1000);
			ErrorMessageOfFalse="Can not create new master data in Database";
			return 0;
		}
	}
	RegTime	=XDateTime::currentDateTime();

	StepProcessing(-1);
	GetLayersBase()->UnlockForLoadSave();

	MachineIDFromMaster	=MachineID;
	SQLUpdateMasterData(GetMachineID(),ImagePath,true,ErrorMessageOfFalse);
	return MasterCode;
}
QString	LayersBase::CreateGUIContentFileName(int32 masterCode ,int _MachineID,const QString &ImagePath
											,int ShadowLevel, int ShadowNumber)
{
	QString Sep=/**/"";
	QString s = ImagePath.right(1);
	if(s!=::GetSeparator() && s!=QString("\\")){
		Sep= GetSeparator();
	}
	if(ShadowLevel==0 && ShadowNumber==0){
		QString	Ret=ImagePath+Sep
					+QString(DefGUIPath)+QString::number(masterCode)+QString("-")
					+QString("Mac")+QString::number(_MachineID)
					+QString(".blb");
		return Ret;
	}
	else{
		QString	Ret=ImagePath+Sep
					+QString(DefGUIPath)+QString::number(masterCode)+QString("-")
					+QString("Mac")+QString::number(_MachineID)+QString("-")
					+QString("SLv")+QString::number(ShadowLevel)+QString("-")
					+QString("Snb")+QString::number(ShadowNumber)
					+QString(".blb");
		return Ret;
	}
}
bool	LayersBase::SaveGUIContent(const QString &GUIContentFileName)
{
	if(GetParamGlobal()->ImageFileCachePort==0){
		QFile	GUIContentFile(GUIContentFileName);
		if(GUIContentFile.open(QIODevice::WriteOnly)==false){
			return false;
		}
		return SaveGUIContent(GUIContentFile);
	}
	else{
		TrFile	GUIContentFile(GUIContentFileName,GetParamGlobal()->TransDatabaseIP
												 ,GetParamGlobal()->ImageFileCachePort);
		if(GUIContentFile.open(QIODevice::WriteOnly)==false){
			return false;
		}
		return SaveGUIContent(GUIContentFile);
	}
}

bool	LayersBase::SaveGUIContent(QIODevice &GUIContentFile)
{
	int32	GUICount=0;
	for(GUIInstancePack *c=GetEntryPoint()->GetGUIInstancePack();c!=NULL;c=c->GetNext()){
		for(GUIItemInstance *d=c->NPListPack<GUIItemInstance>::GetFirst();d!=NULL;d=d->GetNext()){
			GUIFormBase	*h=d->GetForm();
			if(h!=NULL && h->GetGuiDLLPoint()!=NULL){
				GUICount++;
			}
		}
	}
	int32	GUIVer=1;

	if(::Save(&GUIContentFile,GUIVer)==false){
		return false;
	}
	if(::Save(&GUIContentFile,GUICount)==false){
		return false;
	}

	for(GUIInstancePack *c=GetEntryPoint()->GetGUIInstancePack();c!=NULL;c=c->GetNext()){
		for(GUIItemInstance *d=c->NPListPack<GUIItemInstance>::GetFirst();d!=NULL;d=d->GetNext()){
			GUIFormBase	*h=d->GetForm();
			if(h!=NULL && h->GetGuiDLLPoint()!=NULL){
				if(::Save(&GUIContentFile,h->GetGuiDLLPoint()->RootName)==false){
					return false;
				}
				if(::Save(&GUIContentFile,h->GetGuiDLLPoint()->Name)==false){
					return false;
				}
				if(::Save(&GUIContentFile,h->GetName())==false){
					return false;
				}
				QBuffer	GUIBuff;
				QByteArray	GUIArray;
				GUIBuff.open(QIODevice::WriteOnly);
				if(h->SaveContent(&GUIBuff)==true){
					GUIArray=GUIBuff.buffer();
				}
				if(::Save(&GUIContentFile,GUIArray)==false){
					return false;
				}
			}
		}
	}
	return true;
}

bool	LayersBase::SQLUpdateMasterData(int _MachineID
										,const QString &ImagePath
										,bool ForceSave 
										,QString &ErrorMessageOfFalse
										,bool UpdateGeneralSetting)
{
	SetMaxProcessing(2);
	QBuffer GeneralBuff;
	QBuffer	SettingBuff;
	QBuffer TopViewBuff;
	QBuffer LightBuff;
	QBuffer GeneralStockerBuff;
	QBuffer ResultAnalizerBuff;

	GetLayersBase()->LockForLoadSave();
	if(SQLUpdateMasterDataHeader(GeneralBuff 
								 ,SettingBuff 
								 ,TopViewBuff 
								 ,LightBuff
								 ,GeneralStockerBuff
								 ,ResultAnalizerBuff
								 ,UpdateGeneralSetting
								 ,ErrorMessageOfFalse)==false){
		GetLayersBase()->UnlockForLoadSave();
		return false;
	}
	SelectedImagePath=ImagePath;
	StepProcessing(-1);
	bool	ret=false;
	if(GetDatabaseLoader()){

		ret=GetDatabaseLoader()->G_SQLUpdateMasterData(GetDatabase() ,this ,GetParamGlobal()
								,GeneralBuff ,SettingBuff ,LightBuff 
								,GeneralStockerBuff,ResultAnalizerBuff,TopViewBuff);

		QString	GUIContentFileName=CreateGUIContentFileName(MasterCode,_MachineID ,ImagePath);
		if(SaveGUIContent(GUIContentFileName)==false){
			GSleep(GetParamGlobal()->WaitingMilisecForRetryLoading);
			if(SaveGUIContent(GUIContentFileName)==false){
				GSleep(GetParamGlobal()->WaitingMilisecForRetryLoading*1.5);
				if(SaveGUIContent(GUIContentFileName)==false){
					GSleep(GetParamGlobal()->WaitingMilisecForRetryLoading*2);
					GetLayersBase()->UnlockForLoadSave();
					ErrorMessageOfFalse=QString("Can not save file : ")+GUIContentFileName;
					return false;
				}
			}
		}
		SaveShadowChildrenGUIContent(_MachineID,ImagePath);
	}
	GetLayersBase()->UnlockForLoadSave();

	StepProcessing(-1);
	if(ret==true){
		GetErrorContainer()->RemoveAll();
		for(int page=0;page<GetPageNumb();page++){
			int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
			CmdReqSaveMasterForPage	P(this,"ANY","ANY",MasterCode,globalPage);
			P.MachineID=_MachineID;
			P.ImagePath=ImagePath;
			P.ForceSave=ForceSave;
			P.Send(NULL,page,0);
		}
		GetLayersBase()->WaitAllAcknowledged(60*10);

		ErrorCodeList	*e=GetErrorContainer()->GetLast();
		if(e!=NULL){
			ErrorMessageOfFalse=e->GetMessageStr();
			ret=false;
		}
	}
	else{
		ErrorMessageOfFalse="Fail to update MasterData in database";
	}
	SetEdited(false);
	return ret;
}

bool	LayersBase::SQLUpdateMasterDataHeader(QBuffer &GeneralBuff ,QBuffer	&SettingBuff ,QBuffer &TopViewBuff 
											,QBuffer &LightBuff ,QBuffer &GeneralStockerBuff,QBuffer &ResultAnalizerBuff
											,bool UpdateGeneralSetting
											,QString &ErrorMessageOfFalse)
{
	LastEditTime	=XDateTime::currentDateTime();

	if(UpdateGeneralSetting==true){
		GeneralBuff.open(QIODevice::ReadWrite);
		//Save(&GeneralBuff);
		GeneralBuff.seek(0);

		SettingBuff.open(QIODevice::ReadWrite);
		GetParamGlobal()->SaveParam(&SettingBuff);
		//GetParamComm()	->SaveParam(&SettingBuff);
	}
	struct	PropertyGeneralStocker	Prop;
	Prop.SaveInMasterData	=true;
	Prop.SynchronizeToSlave	=false;

	GeneralStockerBuff.open(QIODevice::ReadWrite);
	if(GetGeneralStocker()!=NULL){
		GetGeneralStocker()->Save(&GeneralStockerBuff,Prop);
	}
	ResultAnalizerBuff.open(QIODevice::ReadWrite);
	if(GetResultAnalizerItemBaseContainer()!=NULL){
		GetResultAnalizerItemBaseContainer()->Save(&ResultAnalizerBuff);
	}
		
	SettingBuff.seek(0);

	LightBuff.open(QIODevice::ReadWrite);
	if(GetLightBase()!=NULL){
		if(GetLightBase()->IsEmptyLight()==false){
			GetLightBase()->Save(&LightBuff);
			LightBuff.seek(0);
		}
		else{
			LightBuff.setData(LightDataFromMasterData);
			LightBuff.seek(0);
		}
	}


	int	TopViewSizeX=256;
	int	TopViewSizeY=256;
	if(IsValidData()==false){
		ErrorMessageOfFalse="DataHeader is invalid to write";
		return false;
	}

	GUICmdSendBmpForTopView	**BmpReceiver=new GUICmdSendBmpForTopView*[GetPageNumb()];
	GUICmdReqBmpForTopView	**BmpRequester=new GUICmdReqBmpForTopView*[GetPageNumb()];
	int	globalX1;
	int	globalY1;
	int	globalX2;
	int	globalY2;
	GetArea(globalX1,globalY1 ,globalX2,globalY2);
	double	Zx=(double)TopViewSizeX/(double)globalX2;
	double	Zy=(double)TopViewSizeY/(double)globalY2;
	double	ZoomRate=(Zx<Zy)?Zx:Zy;
	int	N=0;
	for(int page=0;page<GetPageNumb();page++){
		int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
		BmpReceiver[N]=new GUICmdSendBmpForTopView(this,"ANY","ANY" ,globalPage);
		BmpRequester[N]=new GUICmdReqBmpForTopView(this,"ANY","ANY",globalPage);
		if(GetParamGlobal()->AllocateMasterBuff==false){
			BmpRequester[N]->Data.DType=DisplayImage::__Target;
			BmpRequester[N]->Data.MasterNo	=0;
		}

		DataInPage *P=GetPageData(page);
		int	Dx1	=P->GetOutlineOffset()->x;
		int	Dy1	=P->GetOutlineOffset()->y;
		int	Dx2	=P->GetOutlineOffset()->x+P->GetDotPerLine();
		int	Dy2	=P->GetOutlineOffset()->x+P->GetMaxLines();
		int	Gx1=Dx1*ZoomRate;
		int	Gy1=Dy1*ZoomRate;
		int	Gx2=Dx2*ZoomRate;
		int	Gy2=Dy2*ZoomRate;
		BmpRequester[N]->Data.ZoomRate=ZoomRate;
		BmpRequester[N]->Data.Yz	  =1.0;
		BmpRequester[N]->Data.MovX		=0;
		BmpRequester[N]->Data.MovY		=0;
		BmpRequester[N]->Data.GlobalPage=globalPage;
		if(Gx1<0){
			Gx1=0;
		}
		if(Gy1<0){
			Gy1=0;
		}
		if(Gx2>TopViewSizeX){
			Gx2=TopViewSizeX;
		}
		if(Gy2>TopViewSizeY){
			Gy2=TopViewSizeY;
		}
		BmpRequester[N]->Data.Gx1		=Gx1;
		BmpRequester[N]->Data.Gy1		=Gy1;
		BmpRequester[N]->Data.Gx2		=Gx2;
		BmpRequester[N]->Data.Gy2		=Gy2;
		Dx1=Gx1/ZoomRate;
		Dy1=Gy1/ZoomRate;
		Dx2=Gx2/ZoomRate;
		Dy2=Gy2/ZoomRate;
		BmpRequester[N]->Data.Dx1	=Dx1-P->GetOutlineOffset()->x;
		BmpRequester[N]->Data.Dy1	=Dy1-P->GetOutlineOffset()->y;
		BmpRequester[N]->Data.Dx2	=Dx2-P->GetOutlineOffset()->x;
		BmpRequester[N]->Data.Dy2	=Dy2-P->GetOutlineOffset()->y;
		for(int layer=0;layer<GetLayerNumb(page);layer++){
			BmpRequester[N]->LayerList.Add(layer);
		}
		N++;
	}
	for(int n=0;n<N;n++){
		BmpRequester[n]->Send(BmpRequester[n]->Data.GlobalPage,0,*BmpReceiver[n]);
	}
	TopView.fill(0);
	QPainter	*Pnt=new QPainter(&TopView);
	for(int n=0;n<N;n++){
		if(BmpReceiver[n]->IData!=NULL){
			Pnt->drawImage(BmpRequester[n]->Data.Gx1 ,BmpRequester[n]->Data.Gy1
						 ,*(const QImage *)BmpReceiver[n]->IData);
		}
	}
	for(int i=0;i<N;i++){
		delete	BmpRequester[i];
		delete	BmpReceiver[i];
	}
	delete	[]BmpRequester;
	delete	[]BmpReceiver;

	TopViewBuff.open(QIODevice::ReadWrite);
	TopView.save(&TopViewBuff,"PNG");
	delete	Pnt;

	return true;
}

bool	LayersBase::InitialParamFromDatabase(int masterCode)
{
	if(GetDatabaseLoader()){
		QBuffer	SettingBuff;
		bool	ret=GetDatabaseLoader()->G_SQLLoadMasterSetting(GetDatabase() ,masterCode ,SettingBuff);
		if (ret == false) {
			return false;
		}
		SettingBuff.open(QIODevice::ReadWrite);
		if(GetParamGlobal()	->LoadParam(&SettingBuff,ParamEnableInTransfer | ParamEnableInLoadOnMaster | ParamEnableInLoadOnSlave)==false){
			return false;
		}
		//if(GetParamCommData()	->LoadParam(&SettingBuff,ParamEnableInTransfer | ParamEnableInLoadOnMaster | ParamEnableInLoadOnSlave)==false)
		//	return false;
	}
	return true;
}

bool	LayersBase::LoadGUIContent(const QString &GUIContentFileName)
{
	if(GetParamGlobal()->ImageFileCachePort==0){
		QFile	GUIContentFile(GUIContentFileName);
		if(GUIContentFile.open(QIODevice::ReadOnly)==true){
			return LoadGUIContent(GUIContentFile);
		}
	}
	else{
		TrFile	GUIContentFile(GUIContentFileName,GetParamGlobal()->TransDatabaseIP
												 ,GetParamGlobal()->ImageFileCachePort);
		if(GUIContentFile.open(QIODevice::ReadOnly)==true){
			return LoadGUIContent(GUIContentFile);
		}
	}
	return false;
}
bool	LayersBase::LoadGUIContent(QIODevice &GUIContentFile)
{
	int32	GUIVer;
	if(::Load(&GUIContentFile,GUIVer)==false){
		return false;
	}
	int32	GUICount=0;
	if(::Load(&GUIContentFile,GUICount)==false){
		return false;
	}
	for(int i=0;i<GUICount;i++){
		QString	SRoot;
		QString	SName;
		QString	InstName;

		if(::Load(&GUIContentFile,SRoot)==false){
			break;
			//return false;
		}
		if(::Load(&GUIContentFile,SName)==false){
			break;
			//return false;
		}
		if(::Load(&GUIContentFile,InstName)==false){
			break;
			//return false;
		}
		QByteArray	GUIArray;
		if(::Load(&GUIContentFile,GUIArray)==false){
			break;
			//return false;
		}

		GUIFormBase	*h=FindByName(SRoot,SName,InstName);
		if(h!=NULL){
			QBuffer	GUIBuff(&GUIArray);
			GUIBuff.open(QIODevice::ReadOnly);
			h->LoadContent(&GUIBuff);
		}
	}
	return true;
}

bool	LayersBase::SQLLoadMasterData(int masterCode
									 ,int _MachineID
									 ,bool ModeLoadMasterImage 
									 ,bool &CriticalErrorOccured
									 ,QString &ErrorMessageOfFalse)
{
	SetMaxProcessing(3+3);

	CriticalErrorOccured=false;
	QBuffer	GeneralBuff;
	QBuffer	SettingBuff;
	QBuffer	LightBuff;
	QBuffer	GeneralStockerBuff;
	QBuffer	ResultAnalizerBuff;
	bool	ret=false;
	int		iMachineID=-1;
	int32	iLibFolderID;
	int32 	iThresholdLevelID		=ThresholdLevelID;
	int32 	iThresholdLevelParentID	=ThresholdLevelParentID;
	QString		GUIContentFileName;

	ClearBufferInfo();
	if(GetDatabaseLoader()){
		ret=GetDatabaseLoader()->G_SQLLoadMasterData(GetDatabase() ,this,masterCode ,GeneralBuff ,SettingBuff ,LightBuff,GeneralStockerBuff,ResultAnalizerBuff
									,MasterCode ,MachineIDFromMaster
									,RegTime
									,MasterName ,Remark
									,Version
									,LastEditTime
									,CategoryID
									,MasterType
									,TopView
									,iLibFolderID
									,iThresholdLevelID
									,iThresholdLevelParentID);
		if(ret==false){
			ErrorMessageOfFalse="Can not load MasterData from database";
			return false;
		}
		ThresholdLevelParentID	=iThresholdLevelParentID;
		ThresholdLevelID		=iThresholdLevelID;

		SetLibFolderID(iLibFolderID);
		
		iMachineID=_MachineID;
		if(iMachineID<0){
			iMachineID=MachineIDFromMaster;
		}
		
		QStringList	ImagePathes=GetParamGlobal()->ImageFilePath.split(QChar(';'));
		QString		ImagePath;
		bool		FoundGUIContentFileName=false;
		for(int h=0;h<ImagePathes.count();h++){
			ImagePath=ImagePathes[h];
			GUIContentFileName=CreateGUIContentFileName(MasterCode,GetMachineID(),ImagePath);
			if(QFile::exists(GUIContentFileName)==true){
				FoundGUIContentFileName=true;
				break;
			}
		}
		if(FoundGUIContentFileName==false){
			if(ImagePathes.count()==0)
				ImagePath=/**/"";
			else
				ImagePath=ImagePathes[0];
			GUIContentFileName=CreateGUIContentFileName(MasterCode,iMachineID,ImagePath);
		}
		SelectedImagePath=ImagePath;
	}
	StepProcessing(-1);

	if(ret==true){
		GeneralBuff.open(QIODevice::ReadWrite);
		//if(Load(&GeneralBuff)==false){
		//	return false;
		//}
		LoadedVersion=Version;
		Version=RegulusVersion;
		GetParamGlobal()->Push();	//for GetParamGlobal()->IsChangedCritically
		int	OldDotPerLine	=GetDotPerLine(-1);
		int	OldMaxLines		=GetMaxLines(-1);
		int	OldPhaseNumb	=GetPhaseNumb();
		int	OldPageNumb		=GetPageNumb();
		int	OldLayerNumb	=GetMaxLayerNumb();
		int	OldAllocatedCountMasterBuff	=GetParamGlobal()->AllocatedCountMasterBuff;

		StepProcessing(-1);
		SettingBuff.open(QIODevice::ReadWrite);
		if(GetParamGlobal()	->LoadParam(&SettingBuff,ParamEnableInLoadOnMaster)==false){
			SettingBuff.seek(0);
			if(GetParamGlobal()	->LoadParam(&SettingBuff)==false){
				ErrorMessageOfFalse="Can not load SettingParam from database";
				return false;
			}
		}
		//if(GetParamCommData()	->LoadParam(&SettingBuff,ParamEnableInLoadOnMaster)==false)
		//	return false;

		GeneralStockerBuff.open(QIODevice::ReadWrite);
		struct	PropertyGeneralStocker	Prop;
		Prop.SaveInMasterData	=true;
		Prop.SynchronizeToSlave	=false;
		if(GetGeneralStocker()!=NULL){
			if(GetGeneralStocker()->Load(&GeneralStockerBuff,Prop)==false){
				//return false;
			}
		}
		ResultAnalizerBuff.open(QIODevice::ReadWrite);
		if(GetResultAnalizerItemBaseContainer()!=NULL){
			if(GetResultAnalizerItemBaseContainer()->Load(&ResultAnalizerBuff)==false){
				//return false;
			}
		}
		CopyShadowMasterToChildren();
		
		if(GetParamGlobal()->IsChangedCritically("AllocatedCountMasterBuff")==true
		|| GetParamGlobal()->IsChangedCritically("PhaseNumb")==true
		|| GetParamGlobal()->IsChangedCritically("DotPerLine")==true
		|| GetParamGlobal()->IsChangedCritically("MaxLines")==true
		|| GetParamGlobal()->IsChangedCritically("LayerNumb")==true
		|| GetParamGlobal()->IsChangedCritically("PageNumb")==true){
			int	iAllocatedCountMasterBuff	=GetParamGlobal()->AllocatedCountMasterBuff;
			int	iPhaseNumb	=GetParamGlobal()->PhaseNumb;
			int	iDotPerLine	=GetParamGlobal()->DotPerLine;
			int	iMaxLines	=GetParamGlobal()->MaxLines;
			int	iLayerNumb	=GetParamGlobal()->LayerNumb;
			int	iPageNumb	=GetParamGlobal()->PageNumb;
			//GetParamGlobal()->Pop();

			GetParamGlobal()->AllocatedCountMasterBuff	=OldAllocatedCountMasterBuff;
			GetParamGlobal()->PhaseNumb	=OldPhaseNumb	;
			GetParamGlobal()->DotPerLine=OldDotPerLine	;
			GetParamGlobal()->MaxLines	=OldMaxLines	;
			GetParamGlobal()->LayerNumb	=OldLayerNumb	;
			GetParamGlobal()->PageNumb	=OldPageNumb	;

			if(iPhaseNumb!=GetPhaseNumb() || iPageNumb!=GetPageNumb() || iLayerNumb!=GetMaxLayerNumb()){
				Reallocate(iPhaseNumb , iPageNumb ,iLayerNumb);
			}
			if(iDotPerLine!=GetDotPerLine(-1) || iMaxLines!=GetMaxLines(-1)){
				ReallocXYPixels(iDotPerLine,iMaxLines);
			}
			if(iAllocatedCountMasterBuff!=GetParamGlobal()->AllocatedCountMasterBuff){
				GetLayersBase()->ReallocateMasterCount(iAllocatedCountMasterBuff);
			}
		}

		StepProcessing(-1);
		int	PageCount=GetParamGlobal()->PageNumb;
		//if(GetParamComm()->GetConnectedPCNumb()>0){
			for(int page=0;page<PageCount;page++){
				int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
				CmdReqLoadMasterForPage	P(this,"ANY","ANY",MasterCode,globalPage);
				P.MachineID=iMachineID;
				P.ModeLoadMasterImage=ModeLoadMasterImage;
				P.Send(NULL,page,0);
				//_CrtCheckMemory();
			}
		//}
		//_CrtCheckMemory();

		if(GetLightBase()!=NULL){
			if(GetLightBase()->IsEmptyLight()==false){
				LightBuff.open(QIODevice::ReadWrite);
				if(GetLightBase()->Load(&LightBuff)==true){
					if(GetLightBase()->GetFirst()!=NULL){
						GetLightBase()->SetPattern(0);
						GSleep(2000);
						if(GetParamGlobal()->InitialLightON==true){
							GetLightBase()->LightOn();
						}
						else{
							GetLightBase()->LightOff();
						}
					}
				}
			}
			else{
				LightDataFromMasterData=LightBuff.buffer();
			}
		}
		if(GetParamGlobal()->RetryLoadIfFails==true){
			for(int h=0;h<GetParamGlobal()->CountToRetryLoading;h++){
				if(LoadGUIContent(GUIContentFileName)==true){
					break;
				}
				GSleep(GetParamGlobal()->WaitingMilisecForRetryLoading);
			}
		}
		else{
			LoadGUIContent(GUIContentFileName);
		}
		LoadShadowChildrenGUIContent(iMachineID);

		for(int page=0;page<PageCount;page++){
			int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
			GUICmdSendResultAnalizerData	P(this,"ANY","ANY",globalPage);
			P.Data=ResultAnalizerBuff.buffer();
			P.Send(NULL,page,0);
			//_CrtCheckMemory();
		}
		InitialExecuter();
		InitializeToStart();
		//_CrtCheckMemory();
	}
	return ret;
}

bool	LayersBase::SQLLoadMasterDataIn1Phase(int masterCode,int _MachineID,int DestPhase
											 ,bool ModeLoadMasterImage ,bool &CriticalErrorOccured
											,QString &ErrorMessageOfFalse)
{
	SetMaxProcessing(3+3);

	CriticalErrorOccured=false;
	QBuffer	GeneralBuff;
	QBuffer	SettingBuff;
	QBuffer	LightBuff;
	QBuffer	GeneralStockerBuff;
	QBuffer	ResultAnalizerBuff;
	int32	iMasterCode;
	int32	iMachineID;
	int32	iVersion;
	XDateTime	iRegTime;
	XDateTime	iLastEditTime;
	QString	iMasterName ,iRemark;
	bool	ret=false;
	int32	iCategoryID;
	short	iMasterType;
	QImage	iTopView;
	int32	iLibFolderID;
	int32 	iThresholdLevelID		=ThresholdLevelID;
	int32 	iThresholdLevelParentID	=ThresholdLevelParentID;

	if(GetDatabaseLoader()){
		ret=GetDatabaseLoader()->G_SQLLoadMasterData(GetDatabase() ,this,masterCode ,GeneralBuff ,SettingBuff ,LightBuff,GeneralStockerBuff,ResultAnalizerBuff
									,iMasterCode ,iMachineID
									,iRegTime
									,iMasterName ,iRemark
									,iVersion
									,iLastEditTime
									,iCategoryID
									,iMasterType
									,iTopView
									,iLibFolderID
									,iThresholdLevelID
									,iThresholdLevelParentID);
		if(ret==false){
			ErrorMessageOfFalse="Can not load MasterData from database";
			return false;
		}
		ThresholdLevelParentID	=iThresholdLevelParentID;
		ThresholdLevelID		=iThresholdLevelID;
		SetLibFolderID(iLibFolderID);
		
		QStringList	ImagePathes=GetParamGlobal()->ImageFilePath.split(QChar(';'));
		QString		ImagePath;
		QString		GUIContentFileName;
		bool		FoundGUIContentFileName=false;
		for(int h=0;h<ImagePathes.count();h++){
			ImagePath=ImagePathes[h];
			GUIContentFileName=CreateGUIContentFileName(iMasterCode,iMachineID,ImagePath);
			if(QFile::exists(GUIContentFileName)==true){
				FoundGUIContentFileName=true;
				break;
			}
		}
		if(FoundGUIContentFileName==false){
			if(ImagePathes.count()==0)
				ImagePath=/**/"";
			else
				ImagePath=ImagePathes[0];
			GUIContentFileName=CreateGUIContentFileName(iMasterCode,iMachineID,ImagePath);
		}
		SelectedImagePath=ImagePath;

		if(DestPhase==0){
			if(GetParamGlobal()->RetryLoadIfFails==true){
				for(int h=0;h<GetParamGlobal()->CountToRetryLoading;h++){
					if(LoadGUIContent(GUIContentFileName)==true){
						break;
					}
					GSleep(GetParamGlobal()->WaitingMilisecForRetryLoading);
				}
			}
			else{
				LoadGUIContent(GUIContentFileName);
			}
		}
		LoadShadowChildrenGUIContent(iMachineID);
	}
	StepProcessing(-1);

	if(ret==true){
		GeneralBuff.open(QIODevice::ReadWrite);
		//if(Load(&GeneralBuff)==false){
		//	return false;
		//}
		if(DestPhase==0){
			LoadedVersion=iVersion;
			Version=RegulusVersion;
		}
		GetParamGlobal()->Push();	//for GetParamGlobal()->IsChangedCritically
		int	OldDotPerLine	=GetDotPerLine(-1);
		int	OldMaxLines		=GetMaxLines(-1);
		int	OldPhaseNumb	=GetPhaseNumb();
		int	OldPageNumb		=GetPageNumb();
		int	OldLayerNumb	=GetMaxLayerNumb();
		int	OldAllocatedCountMasterBuff	=GetParamGlobal()->AllocatedCountMasterBuff;

		StepProcessing(-1);

		if(DestPhase==0){
			SettingBuff.open(QIODevice::ReadWrite);
			if(GetParamGlobal()	->LoadParam(&SettingBuff,ParamEnableInLoadOnMaster)==false){
				ErrorMessageOfFalse="Can not load ParamSetting from database";
				return false;
			}
		}
		//if(GetParamCommData()	->LoadParam(&SettingBuff,ParamEnableInLoadOnMaster)==false)
		//	return false;

		GeneralStockerBuff.open(QIODevice::ReadWrite);
		struct	PropertyGeneralStocker	Prop;
		Prop.SaveInMasterData	=true;
		Prop.SynchronizeToSlave	=false;
		if(GetGeneralStocker()!=NULL){
			if(DestPhase==0){
				if(GetGeneralStocker()->Load(&GeneralStockerBuff,Prop)==false){
					 //return false;
				}
			}
		}
		ResultAnalizerBuff.open(QIODevice::ReadWrite);
		if(GetResultAnalizerItemBaseContainer()!=NULL){
			if(GetResultAnalizerItemBaseContainer()->Load(&ResultAnalizerBuff)==false){
				//return false;
			}
		}
		CopyShadowMasterToChildren();

		if(DestPhase==0){
			if(GetParamGlobal()->IsChangedCritically("AllocatedCountMasterBuff")==true
			|| GetParamGlobal()->IsChangedCritically("DotPerLine")==true
			|| GetParamGlobal()->IsChangedCritically("MaxLines")==true
			|| GetParamGlobal()->IsChangedCritically("LayerNumb")==true
			|| GetParamGlobal()->IsChangedCritically("PageNumb")==true){
				int	iAllocatedCountMasterBuff=GetParamGlobal()->AllocatedCountMasterBuff;
				int	iDotPerLine	=GetParamGlobal()->DotPerLine;
				int	iMaxLines	=GetParamGlobal()->MaxLines;
				int	iLayerNumb	=GetParamGlobal()->LayerNumb;
				int	iPageNumb	=GetParamGlobal()->PageNumb;
				//GetParamGlobal()->Pop();
				GetParamGlobal()->AllocatedCountMasterBuff	=OldAllocatedCountMasterBuff;
				GetParamGlobal()->PhaseNumb	=OldPhaseNumb	;
				GetParamGlobal()->DotPerLine=OldDotPerLine	;
				GetParamGlobal()->MaxLines	=OldMaxLines	;
				GetParamGlobal()->LayerNumb	=OldLayerNumb	;
				GetParamGlobal()->PageNumb	=OldPageNumb	;

				if(iPageNumb!=GetPageNumb() || iLayerNumb!=GetMaxLayerNumb()){
					Reallocate(GetPhaseNumb() , iPageNumb ,iLayerNumb);
				}
				if(iDotPerLine!=GetDotPerLine(-1) || iMaxLines!=GetMaxLines(-1)){
					ReallocXYPixels(iDotPerLine,iMaxLines);
				}
				if(iAllocatedCountMasterBuff!=GetParamGlobal()->AllocatedCountMasterBuff){
					GetLayersBase()->ReallocateMasterCount(iAllocatedCountMasterBuff);
				}
			}
		}

		StepProcessing(-1);
		int	PageCount=GetParamGlobal()->PageNumb;
		//if(GetParamComm()->GetConnectedPCNumb()>0){
			for(int page=0;page<PageCount;page++){
				int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
				CmdReqLoadMasterForPagePhase	P(this,"ANY","ANY",iMasterCode,globalPage);
				P.MachineID=iMachineID;
				P.ModeLoadMasterImage=ModeLoadMasterImage;
				P.DestPhase	=DestPhase;
				P.Send(NULL,page,0);
				//_CrtCheckMemory();
			}
		//}
		//_CrtCheckMemory();

		if(GetLightBase()!=NULL && DestPhase==0){
			if(GetLightBase()->IsEmptyLight()==false){
				LightBuff.open(QIODevice::ReadWrite);
				if(GetLightBase()->Load(&LightBuff)==true){
					if(GetLightBase()->GetFirst()!=NULL){
						GetLightBase()->SetPattern(0);
						GSleep(2000);
						if(GetParamGlobal()->InitialLightON==true){
							GetLightBase()->LightOn();
						}
						else{
							GetLightBase()->LightOff();
						}
					}
				}
			}
			else{
				LightDataFromMasterData=LightBuff.buffer();
			}
		}
		if(DestPhase==0){
			for(int page=0;page<PageCount;page++){
				int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
				GUICmdSendResultAnalizerData	P(this,"ANY","ANY",globalPage);
				P.Data=ResultAnalizerBuff.buffer();
				P.Send(NULL,page,0);
				//_CrtCheckMemory();
			}
		}
		//_CrtCheckMemory();
	}
	return ret;
}

bool	LayersBase::SQLUpdateAlgorithmOnly(AlgorithmBase *Algo)
{
	for(int page=0;page<GetPageNumb();page++){
		AlgorithmInPageRoot		*Ap=Algo->GetPageData(page);
		if(Ap==NULL){
			return false;
		}
		if(GetPageData(page)->SQLUpdateAlgorithmOnly(Ap)==false){
			return false;
		}
	}
	return true;
}

QString	DataInPage::CreateMasterImageFileName(int32 masterCode ,int _MachineID ,const QString &ImagePath
											,int ShadowLevel ,int ShadowNumber)
{
	int	Phase=GetPhaseCode();
	QString Sep=/**/"";
	QString s = ImagePath.right(1);
	if(s!=::GetSeparator() && s!=QString("\\")){
		Sep= GetSeparator();
	}
	QString	Ret;
	if(ShadowLevel==0 && ShadowNumber<=0){
		if(Phase==0){
			Ret =ImagePath+Sep
				+QString("Image")+QString::number(masterCode)+QString("-")
				+QString("Page")+QString::number(GetLayersBase()->GetGlobalPageFromLocal(GetPage()))+QString("-")
				+QString("Mac")+QString::number(_MachineID)
				+QString(".img");
		}
		else{
			Ret =ImagePath+Sep
				+QString("Image")+QString::number(masterCode)+QString("-")
				+QString("Phase")+QString::number(Phase)+QString("-")
				+QString("Page")+QString::number(GetLayersBase()->GetGlobalPageFromLocal(GetPage()))+QString("-")
				+QString("Mac")+QString::number(_MachineID)
				+QString(".img");
		}
	}
	else{
		if(Phase==0){
			Ret =ImagePath+Sep
				+QString("Image")+QString::number(masterCode)+QString("-")
				+QString("Page")+QString::number(GetLayersBase()->GetGlobalPageFromLocal(GetPage()))+QString("-")
				+QString("Mac")+QString::number(_MachineID)+QString("-")
				+QString("SLv")+QString::number(ShadowLevel)+QString("-")
				+QString("Snb")+QString::number(ShadowNumber)
				+QString(".img");
		}
		else{
			Ret =ImagePath+Sep
				+QString("Image")+QString::number(masterCode)+QString("-")
				+QString("Phase")+QString::number(Phase)+QString("-")
				+QString("Page")+QString::number(GetLayersBase()->GetGlobalPageFromLocal(GetPage()))+QString("-")
				+QString("Mac")+QString::number(_MachineID)+QString("-")
				+QString("SLv")+QString::number(ShadowLevel)+QString("-")
				+QString("Snb")+QString::number(ShadowNumber)
				+QString(".img");
		}
	}
	return Ret;
}

QString	DataInPage::CreateLogicFileName(int32 masterCode ,LogicDLL *abase,int _MachineID ,const QString &ImagePath
										,int ShadowLevel ,int ShadowNumber)
{
	int	Phase=GetPhaseCode();
	QString Sep=/**/"";
	QString s = ImagePath.right(1);
	if(s!=::GetSeparator() && s!=QString("\\")){
		Sep= GetSeparator();
	}
	QString	Ret;
	if(ShadowLevel==0 && ShadowNumber<=0){
		if(Phase==0){
			Ret =ImagePath+Sep
				+abase->GetBlobName()+QString("-")
				+QString::number(masterCode)+QString("-")
				+QString("Page")+QString::number(GetLayersBase()->GetGlobalPageFromLocal(GetPage()))+QString("-")
				+QString("Mac")+QString::number(_MachineID)
				+QString(".blb");
		}
		else{
			Ret =ImagePath+Sep
				+abase->GetBlobName()+QString("-")
				+QString::number(masterCode)+QString("-")
				+QString("Phase")+QString::number(Phase)+QString("-")
				+QString("Page")+QString::number(GetLayersBase()->GetGlobalPageFromLocal(GetPage()))+QString("-")
				+QString("Mac")+QString::number(_MachineID)
				+QString(".blb");
		}
	}
	else{
		if(Phase==0){
			Ret =ImagePath+Sep
				+abase->GetBlobName()+QString("-")
				+QString::number(masterCode)+QString("-")
				+QString("Page")+QString::number(GetLayersBase()->GetGlobalPageFromLocal(GetPage()))+QString("-")
				+QString("Mac")+QString::number(_MachineID)+QString("-")
				+QString("SLv")+QString::number(ShadowLevel)+QString("-")
				+QString("Snb")+QString::number(ShadowNumber)
				+QString(".blb");
		}
		else{
			Ret =ImagePath+Sep
				+abase->GetBlobName()+QString("-")
				+QString::number(masterCode)+QString("-")
				+QString("Phase")+QString::number(Phase)+QString("-")
				+QString("Page")+QString::number(GetLayersBase()->GetGlobalPageFromLocal(GetPage()))+QString("-")
				+QString("Mac")+QString::number(_MachineID)+QString("-")
				+QString("SLv")+QString::number(ShadowLevel)+QString("-")
				+QString("Snb")+QString::number(ShadowNumber)
				+QString(".blb");
		}
	}
	return Ret;

}

bool	DataInPage::SaveMasterImageFile(const QString &ImageFileName ,bool ForceSave)
{
	if(GetParamGlobal()->ImageFileCachePort==0){
		QFile	ImageFile(ImageFileName);
		if(ImageFile.open(QIODevice::ReadWrite)==false){
			return false;
		}
		if(SaveMasterImageFile(ImageFile,ForceSave)==false){
			return false;
		}
	}
	else{
		TrFile	ImageFile(ImageFileName ,GetParamGlobal()->TransDatabaseIP
										,GetParamGlobal()->ImageFileCachePort);
		if(ImageFile.open(QIODevice::ReadWrite)==false){
			return false;
		}
		if(SaveMasterImageFile(ImageFile,ForceSave)==false){
			return false;
		}
	}
	return true;
}

bool	DataInPage::SaveMasterImageFile(QIODevice &ImageFile ,bool ForceSave)
{
	bool	MasterChanged=false;
	int	CountMasterBuff=0;
	IntList	IndexBuffer;
	for(int i=0;i<GetCountAllMasterBuff();i++){
		BufferInfoList	*B=GetLayersBase()->GetBufferInfo(i);
		if(B!=NULL && B->OriginCode<=0){
			CountMasterBuff++;
			IndexBuffer.Add(i);
		}
	}

	for(int LNumb=0;LNumb<GetLayerNumb();LNumb++){
		DataInLayer	*L=GetLayerData(LNumb);
		for(IntClass *v=IndexBuffer.GetFirst();v!=NULL;v=v->GetNext()){
			int	MasterNo=v->GetValue();
			if(L->GetMasterBuff(MasterNo).IsChanged()==true){
				MasterChanged=true;
				break;
			}
		}
		if(GetParamGlobal()->AllocateBackGroundBuff==true){
			for(int i=0;i<GetParamGlobal()->AllocatedCountBackGroundBuff;i++){
				if(L->GetBackGroundBuff(i).IsChanged()==true){
					MasterChanged=true;
					break;
				}
			}
		}
		if(GetParamGlobal()->AllocBitBuffer==true){
			if(L->GetBitBuff().IsChanged()==true){
				if(GetParamGlobal()->NoLoadSaveMasterImage==false){
					MasterChanged=true;
					break;
				}
			}
		}
	}

	if(MasterChanged==true || ForceSave==true){
		for(int LNumb=0;LNumb<GetLayerNumb();LNumb++){
			GetLayersBase()->StepProcessing(GetPage());

			DataInLayer	*L=GetLayerData(LNumb);
			if(GetParamGlobal()->NoLoadSaveMasterImage==false){
				for(IntClass *v=IndexBuffer.GetFirst();v!=NULL;v=v->GetNext()){
					int	MasterNo=v->GetValue();
					if(L->GetMasterBuff(MasterNo).Save(&ImageFile)==false){
						return false;
					}
				}
				GetParamGlobal()->IsLoadedMasterImageSuccessful=true;

				if(GetParamGlobal()->AllocateBackGroundBuff==true){
					for(int i=0;i<GetParamGlobal()->AllocatedCountBackGroundBuff;i++){
						if(L->GetBackGroundBuff(i).Save(&ImageFile)==false){
							return false;
						}
					}
				}

				ImageBuffer	Dummy;
				if(Dummy.Save(&ImageFile)==false){
					return false;
				}
				if(Dummy.Save(&ImageFile)==false){
					return false;
				}
			}
			for(IntClass *v=IndexBuffer.GetFirst();v!=NULL;v=v->GetNext()){
				int	MasterNo=v->GetValue();
				L->GetMasterBuff(MasterNo).SetChanged(false);
			}
		}
		bool	AllocBit;
		if(GetParamGlobal()->AllocBitBuffer==true){
			AllocBit=true;
			if(::Save(&ImageFile,AllocBit)==false)
				return false;

			for(int LNumb=0;LNumb<GetLayerNumb();LNumb++){
				DataInLayer	*L=GetLayerData(LNumb);
				if(L->GetBitBuff().IsChanged()==true){
					if(GetParamGlobal()->NoLoadSaveMasterImage==false){
						if(L->GetBitBuff().Save(&ImageFile)==false){
							return false;
						}
					}
				}
			}
		}
		else{
			AllocBit=false;
			if(::Save(&ImageFile,AllocBit)==false)
				return false;
		}
	}
	//bool	AllocMaster2=false;
	//if(::Save(&ImageFile,AllocMaster2)==false){
	//	return false;
	//}

	return true;
}


bool	DataInPage::SaveLogicFile(const QString &LogicFileName
								, AlgorithmBase	*base
								,AlgorithmInPageInOnePhase *pbase
								, AlgorithmInPageRoot *ap)
{
	if(base->GetEnableToSave()==true){
		if(GetParamGlobal()->ImageFileCachePort==0){
			QFile	LogicFile(LogicFileName);
			if(LogicFile.open(QIODevice::ReadWrite)==true){
				base->SaveOnlyBase(&LogicFile);
				if(pbase->SaveOnly(&LogicFile)==false){
					return false;
				}
				if(ap->Save(&LogicFile)==false){
					return false;
				}
			}
			else{
				return false;
			}
		}
		else{
			TrFile	LogicFile(LogicFileName ,GetParamGlobal()->TransDatabaseIP
											,GetParamGlobal()->ImageFileCachePort);
			if(LogicFile.open(QIODevice::ReadWrite)==true){
				base->SaveOnlyBase(&LogicFile);
				if(pbase->SaveOnly(&LogicFile)==false){
					return false;
				}
				if(ap->Save(&LogicFile)==false){
					return false;
				}
			}
			else{
				return false;
			}
		}
	}
	return true;
}
bool	DataInPage::SQLSavePage(int32 masterCode, int32 machineID, QString &ErrorMsg ,const QString &ImagePath ,bool ForceSave)
{
	GetLayersBase()->AddMaxProcessing(GetPage(),3+GetLayerNumb());
	GetLayersBase()->SetSelectedImagePath(ImagePath);

	int	ShadowLevel	=GetLayersBase()->GetShadowLevel();
	int	ShadowNumber=GetLayersBase()->GetShadowNumber();

	GetParamGlobal()->InitializeNetworkDrive();
	QBuffer	GeneralBuff;
	GeneralBuff.open(QIODevice::ReadWrite);
	//if(GetLayersBase()->Save(&GeneralBuff)==false){
	//	ErrorMsg="Error of Saving LayersBase data";
	//	return false;
	//}

	QBuffer	SettingBuff;
	SettingBuff.open(QIODevice::ReadWrite);
	if(GetParamGlobal()->SaveParam(&SettingBuff)==false){
		ErrorMsg="Error of Saving ParamGlobal";
		return false;
	}
	if(GetParamComm()	->SaveParam(&SettingBuff)==false){
		ErrorMsg="Error of Saving ParamComm";
		return false;
	}
	GetLayersBase()->SaveShadowParamInChildren(&SettingBuff);

	GetLayersBase()->LockForLoadSave();
	GetLayersBase()->StepProcessing(GetPage());
	if(Parent->GetDatabaseLoader()){
		if(Parent->GetDatabaseLoader()->G_SQLSavePageNoImage(Parent->GetDatabase(),this,masterCode
							,GetParamGlobal(),GetParamComm()
							,GeneralBuff ,SettingBuff)==false){
			ErrorMsg="Can not save MasterCode record in Database(MasterPage)";
			GetLayersBase()->UnlockForLoadSave();
			return false;
		}
	}

	GetLayersBase()->StepProcessing(GetPage());

	QString	ImageFileName=CreateMasterImageFileName(masterCode,machineID,ImagePath
													,ShadowLevel,ShadowNumber);
	if(SaveMasterImageFile(ImageFileName,ForceSave)==false){
		if(GetParamGlobal()->RetryLoadIfFails==true){
			GSleep(GetParamGlobal()->WaitingMilisecForRetryLoading+GetPage()*500);
			if(SaveMasterImageFile(ImageFileName,ForceSave)==false){
				GSleep(GetParamGlobal()->WaitingMilisecForRetryLoading*1.5+GetPage()*10000);
				if(SaveMasterImageFile(ImageFileName,ForceSave)==false){
					GSleep(GetParamGlobal()->WaitingMilisecForRetryLoading*2+GetPage()*20000);
					if(SaveMasterImageFile(ImageFileName,ForceSave)==false){
						ErrorMsg="Error of Saving MasterImage";
						GetLayersBase()->UnlockForLoadSave();
						return false;
					}
				}
			}
		}
	}
	if(GetLayersBase()->SaveShadowMasterImageFileInChildren(masterCode, machineID,ImagePath,ForceSave
												,GetPhaseCode(),GetPage())==false){
		GetLayersBase()->UnlockForLoadSave();
		ErrorMsg="Error of Saving Shadow-MasterImage";
		return false;
	}

	GetLayersBase()->StepProcessing(GetPage());

	LogicDLL *p;
	AlgorithmBase	*base;
	AlgorithmInPageRoot	*ap;
	if(GetLayersBase()->GetVersion()>=11){
		for(p=GetLayersBase()->GetLogicDLLBase()->GetFirst();p!=NULL;p=p->GetNext()){
			if(p->GetBlobName().isEmpty()==true){
				continue;
			}
			base=GetLayersBase()->GetAlgorithmBase(p->GetDLLRoot(),p->GetDLLName());
			if(base==NULL){
				continue;
			}
			AlgorithmInPageInOnePhase	*pbase=base->GetPageDataPhase(GetPhaseCode());
			ap=pbase->GetPageData(GetPage());
			if(ap==NULL){
				continue;
			}

			if(base->GetModeLoadSaveInPlayer()==true || (base->GetModeLoadSaveInPlayer()==false && GetLayersBase()->GetModeInspectionPlayer()==false)){
				QString	LogicFileName=CreateLogicFileName(masterCode,p,machineID,ImagePath
															,ShadowLevel,ShadowNumber);
				if(SaveLogicFile(LogicFileName ,base ,pbase,ap)==false){
					if(GetParamGlobal()->RetryLoadIfFails==true){
						GSleep(GetParamGlobal()->WaitingMilisecForRetryLoading);
						if(SaveLogicFile(LogicFileName ,base ,pbase,ap)==false){
							GSleep(GetParamGlobal()->WaitingMilisecForRetryLoading*1.5);
							if(SaveLogicFile(LogicFileName ,base ,pbase,ap)==false){
								GSleep(GetParamGlobal()->WaitingMilisecForRetryLoading*2);
								if(SaveLogicFile(LogicFileName ,base ,pbase,ap)==false){
									ErrorMsg=QString("Error of Saving Algorithm ")+p->GetDLLRoot() +QString(":")+ p->GetDLLName();
									continue;
								}
							}
						}
					}
				}
			}
		}
	}
	if(GetLayersBase()->SaveShadowLogicFileInChildren(masterCode, machineID,ImagePath
													,GetPhaseCode(),GetPage())==false){
		GetLayersBase()->UnlockForLoadSave();
		ErrorMsg=QString("Can not save Shadow-LogicFile");
		return false;
	}

	SaveLearningDefault(ImagePath);
	GetLayersBase()->UnlockForLoadSave();

	SetEdited(false);
	GetLayersBase()->SendAckToMaster(GetPage());
	return true;
}


bool	DataInPage::SQLUpdateAlgorithmOnly(AlgorithmInPageRoot *AlgoPage)
{
	AlgorithmBase	*ABase=AlgoPage->GetParentBase();
	LogicDLL *p=ABase->GetLogicDLL();
	if(p==NULL){
		return false;
	}
	LayersBase	*LBase=GetLayersBase();
	int	ShadowLevel	=LBase->GetShadowLevel();
	int	ShadowNumber=LBase->GetShadowNumber();

	QStringList	ImagePathes=GetParamGlobal()->ImageFilePath.split(QChar(';'));
	QString		ImagePath;
	QString		LogicFileName;
	bool		FoundLogicFileName=false;
	for(int h=0;h<ImagePathes.count();h++){
		ImagePath=ImagePathes[h];
		LogicFileName=CreateLogicFileName(LBase->GetMasterCode(),p,LBase->GetMachineID(),ImagePath
											,ShadowLevel,ShadowNumber);
		if(QFile::exists(LogicFileName)==true){
			FoundLogicFileName=true;
			break;
		}
	}
	if(FoundLogicFileName==true){
		QFile	LogicFile(LogicFileName);
		LogicFile.open(QIODevice::ReadWrite);
		ABase->SaveOnlyBase(&LogicFile);
		if(AlgoPage->Save(&LogicFile)==false){
			return false;
		}
	}
	else{
		return false;
	}
	return true;
}

QString	DataInPage::GetImageFile(int32 masterCode, int machineID)
{
	LayersBase	*LBase=GetLayersBase();
	int	ShadowLevel	=LBase->GetShadowLevel();
	int	ShadowNumber=LBase->GetShadowNumber();

	QStringList	ImagePathes=GetParamGlobal()->ImageFilePath.split(QChar(';'));
	QString		ImagePath;
	QString		ImageFileName;
	bool		FoundImageFileName=false;
	for(int h=0;h<ImagePathes.count();h++){
		ImagePath=ImagePathes[h];
		ImageFileName=CreateMasterImageFileName(masterCode,machineID,ImagePath
												,ShadowLevel,ShadowNumber);
		if(QFile::exists(ImageFileName)==true){
			Parent->SetMachineIDFromMaster(machineID);
			FoundImageFileName=true;
			break;
		}
	}
	if(FoundImageFileName==false){
		if(ImagePathes.count()==0)
			ImagePath=/**/"";
		else
			ImagePath=ImagePathes[0];
		ImageFileName=CreateMasterImageFileName(masterCode,Parent->GetMachineIDFromMaster(),ImagePath
												,ShadowLevel,ShadowNumber);
	}
	return ImageFileName;
}

QString	DataInPage::GetLogicFileName(int masterCode ,LogicDLL *p ,int machineID ,QString ImagePath)
{
	QString	LogicFileName;
	
	LayersBase	*LBase=GetLayersBase();
	int	ShadowLevel	=LBase->GetShadowLevel();
	int	ShadowNumber=LBase->GetShadowNumber();
	LogicFileName=CreateLogicFileName(masterCode,p,machineID,ImagePath
										,ShadowLevel,ShadowNumber);
	if(QFile::exists(LogicFileName)==true){
		LogicFileName=CreateLogicFileName(masterCode,p,Parent->GetMachineID(),ImagePath
											,ShadowLevel,ShadowNumber);
		if(QFile::exists(LogicFileName)==false){
			LogicFileName=CreateLogicFileName(masterCode,p,Parent->GetMachineIDFromMaster(),ImagePath
												,ShadowLevel,ShadowNumber);
			if(QFile::exists(LogicFileName)==false){
				return /**/"";
			}
		}
	}
	return LogicFileName;
}

bool	DataInPage::SQLLoadPage(int32 masterCode, int machineID 
								,bool ModeLoadMasterImage 
								,QString &ErrorMsg,LoadedInfoContainerInPhase &LInfo)
{
	QBuffer		GeneralBuff;
	QBuffer		SettingBuff;
	QBuffer		ImageBuff;
	bool	ret=false;
	QString	LogicFileName;
	
	int32 _MachineID;
	XDateTime	_RegTime;
	QString		_MasterName;
	QString		_Remark;
	int32		_Version;
	XDateTime	_LastEditTime;
	int32		_CategoryID;
	int16		_MasterType;
	int32		iLibFolderID;
	int32 		iThresholdLevelID;
	int32 		iThresholdLevelParentID;

	int	ShadowLevel	=Parent->GetShadowLevel();
	int	ShadowNumber=Parent->GetShadowNumber();
	//Parent->SetMachineID(machineID);

	if(Parent->GetDatabaseLoader()){
		if(Parent->GetDatabaseLoader()->G_SQLGetMasterInfo(Parent->GetDatabase() ,masterCode
											,_MachineID
											,_RegTime
											,_MasterName ,_Remark
											,_Version
											,_LastEditTime
											,_CategoryID
											,_MasterType
											,iLibFolderID
											,iThresholdLevelID
											,iThresholdLevelParentID)==true){
			Parent->SetMachineIDFromMaster(_MachineID);
			GetLayersBase()->SetLibFolderID(iLibFolderID);
		}
		GetParamGlobal()->InitializeNetworkDrive();

		QStringList	ImagePathes=GetParamGlobal()->ImageFilePath.split(QChar(';'));
		QString		ImagePath;
		QString		ImageFileName;
		bool		FoundImageFileName=false;
		for(int h=0;h<ImagePathes.count();h++){
			ImagePath=ImagePathes[h];
			ImageFileName=CreateMasterImageFileName(masterCode,machineID,ImagePath
													,ShadowLevel,ShadowNumber);
			if(QFile::exists(ImageFileName)==true){
				Parent->SetMachineIDFromMaster(machineID);
				FoundImageFileName=true;
				break;
			}
		}
		if(FoundImageFileName==false){
			if(ImagePathes.count()==0)
				ImagePath=/**/"";
			else
				ImagePath=ImagePathes[0];
			ImageFileName=CreateMasterImageFileName(masterCode,Parent->GetMachineIDFromMaster(),ImagePath
													,ShadowLevel,ShadowNumber);
		}
		GetLayersBase()->SetSelectedImagePath(ImagePath);

		GetParamGlobal()->Push();	//for GetParamGlobal()->IsChangedCritically
		//_CrtCheckMemory();

		QByteArray *LogicDLLBuff=new QByteArray[GetLayersBase()->GetLogicDLLBase()->GetNumber()];
		bool *ValidLogicDLLBuff	=new bool[GetLayersBase()->GetLogicDLLBase()->GetNumber()];


		GetLayersBase()->AddMaxProcessing(GetPage(),3+GetLayerNumb());
		int iVersion;
		for(int i=0;i<5;i++){
			ret=Parent->GetDatabaseLoader()->G_SQLLoadPageNoImage(Parent->GetDatabase(),this,masterCode
							,GetParamGlobal(),GetParamComm()
							,GeneralBuff ,SettingBuff
							,LogicDLLBuff,ValidLogicDLLBuff
							,iVersion);
			if(ret==true){
				break;
			}
			//Wait for Retry
			GSleep(GetParamGlobal()->WaitingMilisecForRetryLoading+GetPage()*500);
		}
		GetLayersBase()->StepProcessing(GetPage());
		if(ret==true){

			GeneralBuff.open(QIODevice::ReadWrite);
			//if(GetLayersBase()->Load(&GeneralBuff)==false){
			//	ErrorMsg="Error of loading LayersBase data";
			//	ret=false;
			//	goto	QEnd;
			//}

			GetLayersBase()->StepProcessing(GetPage());
			
			SettingBuff.open(QIODevice::ReadWrite);
			if(GetLayersBase()->GetEntryPoint()->IsMasterPC()==false){
				if(GetParamGlobal()	->LoadParam(&SettingBuff,ParamEnableInLoadOnSlave)==false){
					ErrorMsg="Error of loading ParamGlobal data";
					return false;
				}
				//if(GetParamCommData()	->LoadParam(&SettingBuff,ParamEnableInLoadOnSlave)==false)
				//	return false;
				GetLayersBase()->LoadShadowParamInChildren(&SettingBuff);
			}
			if(GetParamGlobal()->IsChangedCritically("AllocatedCountMasterBuff")==true){
				GetLayersBase()->ReallocateMasterCount(GetParamGlobal()->AllocatedCountMasterBuff);
			}

			if(GetParamGlobal()->IsChangedCritically("DotPerLine")==true
			|| GetParamGlobal()->IsChangedCritically("MaxLines")==true
			|| GetParamGlobal()->IsChangedCritically("LayerNumb")==true
			|| GetParamGlobal()->IsChangedCritically("PageNumb")==true){
				Initial();
				for(LogicDLL *p=GetLayersBase()->GetLogicDLLBase()->GetFirst();p!=NULL;p=p->GetNext()){
					AlgorithmBase	*base=p->GetInstance();
					if(base==NULL){
						continue;
					}
					base->SizeChanged();
				}
			}
			
			if(ModeLoadMasterImage==true){
				if(GetParamGlobal()->RetryLoadIfFails==true){
					bool	FlagLoaded=false;
					for(int h=0;h<GetParamGlobal()->CountToRetryLoading;h++){
						if(LoadMasterImageFile(ImageFileName)==true){
							FlagLoaded=true;
							break;
						}
						GSleep(GetParamGlobal()->WaitingMilisecForRetryLoading);
					}
					if(FlagLoaded==false){
						ErrorMsg="Error of loading MasterImage Data";
						ret=false;
						goto	QEnd;
					}					
				}
				else{
					if(LoadMasterImageFile(ImageFileName)==false){
						ErrorMsg="Error of loading MasterImage Data";
						ret=false;
						goto	QEnd;
					}
				}
				GetLayersBase()->LoadShadowMasterImageFileInChildren(masterCode, machineID
											,ImagePath
											,GetPhaseCode(),GetPage());
			}
			if(iVersion<=10){
				int	n=0;
				for(LogicDLL *p=GetLayersBase()->GetLogicDLLBase()->GetFirst();p!=NULL;p=p->GetNext(),n++){
					if(ValidLogicDLLBuff[n]==true){
						LoadedInfoList	*Fo=new LoadedInfoList();
						Fo->AlgoRoot	=p->GetDLLRoot();
						Fo->AlgoName	=p->GetDLLName();
						LInfo.AppendList(Fo);

						AlgorithmBase	*base=GetLayersBase()->GetAlgorithmBase(p->GetDLLRoot(),p->GetDLLName());
						if(base==NULL){
							Fo->Error=LoadedInfoList::_Error;
							continue;
						}
						AlgorithmInPageRoot	*ap=base->GetPageData(GetPage());
						if(ap==NULL){
							Fo->Error=LoadedInfoList::_Error;
							continue;
						}
						QBuffer	Buff(&LogicDLLBuff[n]);
						if(Buff.open(QIODevice::ReadWrite)==true){
							if(Buff.size()!=0){
								if(base->LoadOnlyBase(&Buff)==false){
									Fo->Error=LoadedInfoList::_Error;
									continue;
								}
								if(ap->Load(&Buff)==false){
									Fo->Error=LoadedInfoList::_Error;
									continue;
									}
								Fo->Error=LoadedInfoList::_Success;
								Fo->ItemCount=ap->GetItemCount();
							}
							//_CrtCheckMemory();
						}
						else{
							Fo->Error=LoadedInfoList::_NoFile;
						}
					}
				}
			}
			else{
				for(LogicDLL *p=GetLayersBase()->GetLogicDLLBase()->GetFirst();p!=NULL;p=p->GetNext()){
					AlgorithmBase	*base=GetLayersBase()->GetAlgorithmBase(p->GetDLLRoot(),p->GetDLLName());
					if(base==NULL){
						continue;
					}
					AlgorithmInPageInOnePhase	*pbase=base->GetPageDataPhase(GetPhaseCode());
					AlgorithmInPageRoot	*ap=pbase->GetPageData(GetPage());
					if(ap==NULL){
						continue;
					}

					if(GetParamGlobal()->RetryLoadIfFails==true){
						for(int h=0;h<GetParamGlobal()->CountToRetryLoading;h++){
							LogicFileName=GetLogicFileName(masterCode ,p ,machineID ,ImagePath);
							if(LogicFileName.isEmpty()==false){
								break;
							}
							GSleep(GetParamGlobal()->WaitingMilisecForRetryLoading);
						}
					}
					else{
						LogicFileName=GetLogicFileName(masterCode ,p ,machineID ,ImagePath);
					}


					LoadedInfoList	*Fo=new LoadedInfoList();
					Fo->AlgoRoot	=p->GetDLLRoot();
					Fo->AlgoName	=p->GetDLLName();
					Fo->FileName	=LogicFileName;
					LInfo.AppendList(Fo);
					
					Fo->Error=LoadedInfoList::_Success;
					if(base->GetModeLoadSaveInPlayer()==true || (base->GetModeLoadSaveInPlayer()==false && GetLayersBase()->GetModeInspectionPlayer()==false)){
						if(GetParamGlobal()->RetryLoadIfFails==true){
							for(int h=0;h<GetParamGlobal()->CountToRetryLoading;h++){
								if(LoadLogicFile(LogicFileName ,base ,pbase,ap,_Version)==true){
									break;
								}
								GSleep(GetParamGlobal()->WaitingMilisecForRetryLoading);
								Fo->Error=LoadedInfoList::_Error;
							}
						}
						else{
							if(LoadLogicFile(LogicFileName ,base ,pbase,ap,_Version)==false)
								Fo->Error=LoadedInfoList::_Error;
						}
					}

					//_CrtCheckMemory();
					Fo->ItemCount=ap->GetItemCount();
				}
			}
			GetLayersBase()->LoadShadowLogicFileInChildren(masterCode,machineID,_Version
											,ImagePath
											,GetPhaseCode(),GetPage());

			for(int LNumb=0;LNumb<GetLayerNumb();LNumb++){
				DataInLayer	*L=GetLayerData(LNumb);
				L->GetMasterBuff().EmitDataChanged();
				L->GetMasterBuff().SetChanged(false);
			}
			GetLayersBase()->ShadowSetMasterImageChanged(false,GetPhaseCode(),GetPage());

			GetLayersBase()->StepProcessing(GetPage());
			LInfo.SuccessForImage=true;
		}
		else{
			ErrorMsg="Can\'t find MasterCode record in Database(MasterPage)";
		}

	QEnd:;
		LoadLearningDefault();
		delete	[]LogicDLLBuff		;
		delete	[]ValidLogicDLLBuff	;
		//_CrtCheckMemory();
		return ret;
	}
	return true;
}


bool	DataInPage::LoadLogicFile(const QString &LogicFileName
								, AlgorithmBase	*base
								, AlgorithmInPageInOnePhase *pbase
								, AlgorithmInPageRoot *ap
								, int DataVersion)
{
	if(GetParamGlobal()->ImageFileCachePort==0){
		QFile	LogicFile(LogicFileName);
		if(LogicFile.open(QIODevice::ReadOnly)==true){
			if(LogicFile.size()!=0){
				if(base->LoadOnlyBase(&LogicFile)==false){
					return false;
				}
				if(DataVersion>=13){
					if(pbase->LoadOnly(&LogicFile)==false){
						return false;
					}
				}
				if(ap->Load(&LogicFile)==false){
					return false;
				}
				ap->SetChanged(false);
			}
			return true;
		}
	}
	else{
		TrFile	LogicFile(LogicFileName ,GetParamGlobal()->TransDatabaseIP
										,GetParamGlobal()->ImageFileCachePort);
		if(LogicFile.open(QIODevice::ReadOnly)==true){
			if(LogicFile.size()!=0){
				if(base->LoadOnlyBase(&LogicFile)==false){
					return false;
				}
				if(DataVersion>=13){
					if(pbase->LoadOnly(&LogicFile)==false){
						return false;
					}
				}
				if(ap->Load(&LogicFile)==false){
					return false;
				}
				ap->SetChanged(false);
			}
			return true;
		}
	}
	return false;
}

bool	DataInPage::LoadMasterImageFile(const QString &ImageFileName)
{
	if(GetParamGlobal()->ImageFileCachePort==0){
		QFile	ImageFile(ImageFileName);
		if(ImageFile.open(QIODevice::ReadOnly)==false){
			return false;
		}
		if(LoadMasterImageFile(ImageFile)==false){
			return false;
		}
	}
	else{
		TrFile	ImageFile(ImageFileName ,GetParamGlobal()->TransDatabaseIP
										,GetParamGlobal()->ImageFileCachePort);
		if(ImageFile.open(QIODevice::ReadOnly)==false){
			return false;
		}
		if(LoadMasterImageFile(ImageFile)==false){
			return false;
		}
	}
	return true;
}

bool	DataInPage::LoadMasterImageFile(QIODevice &ImageFile)
{
	int	CountMasterBuff=GetCountAllMasterBuff();
	for(int LNumb=0;LNumb<GetLayerNumb();LNumb++){
		GetLayersBase()->StepProcessing(GetPage());
		DataInLayer	*L=GetLayerData(LNumb);
		if(GetParamGlobal()->NoLoadSaveMasterImage==false){
			//if(L->GetMasterBuff().IsNull()==true){
			//	return true;
			//}
			for(int i=0;i<CountMasterBuff;i++){
				ImageBuffer	&M=L->GetMasterBuff(i);
				if(M.Load(&ImageFile,false)==false){
					return false;
				}
				if(M.IsNull()==false){
					M.SetChanged(false);
				}
			}
			if(GetParamGlobal()->AllocateBackGroundBuff==true){
				for(int i=0;i<GetParamGlobal()->AllocatedCountBackGroundBuff;i++){
					ImageBuffer	&M=L->GetBackGroundBuff(i);
					if(M.Load(&ImageFile,false)==false){
						return false;
					}
					if(M.IsNull()==false){
						M.SetChanged(false);
					}
				}
			}
			ImageBuffer	Dummy;
			if(Dummy.Load(&ImageFile)==false){
				return false;
			}
			if(Dummy.Load(&ImageFile)==false){
				return false;
			}
			GetParamGlobal()->IsLoadedMasterImageSuccessful=true;
		}
		else{
			L->GetMasterBuff().SetChanged(false);
			GetParamGlobal()->IsLoadedMasterImageSuccessful=false;
		}
	}
	bool	AllocBit;
	if(::Load(&ImageFile,AllocBit)==true){
		if(AllocBit==true){
			for(int LNumb=0;LNumb<GetLayerNumb();LNumb++){
				DataInLayer	*L=GetLayerData(LNumb);
				if(L->GetBitBuff().Load(&ImageFile)==false){
					return false;
				}
			}
		}
	}
	bool	AllocMaster2;
	if(::Load(&ImageFile,AllocMaster2)==true){
	}

	return true;
}

void	LayersBase::SQLSetWorker(int workerID)
{
	QString	Name;
	bool	ret=false;
	if(GetDatabaseLoader()){
		ret=GetDatabaseLoader()->G_SQLLoadWorker(GetDatabase() ,workerID,Name);
	}
	if(ret==true){
		WorkerID	=workerID;
		WorkerName	=Name;
	}
}

bool	LayersBase::SaveOutlineOffsetForDatabase(void)
{
	if(GetParamComm()->Mastered==true){
		for(int phase=0;phase<GetPhaseNumb();phase++){
			PageDataInOnePhase	*Ph=GetPageDataPhase(phase);
			for(int page=0;page<Ph->GetAllocatedPageNumb();page++){
				OutlineOffsetInPage Data;
				Data.Dx=Ph->GetPageData(page)->GetOutlineOffset()->x;
				Data.Dy=Ph->GetPageData(page)->GetOutlineOffset()->y;
				GetOutlineOffsetWriter()->SetData(phase,page ,Data);
			}
		}
		if(GetDatabaseLoader()){
			if(IsDatabaseOk()==true){
				return GetDatabaseLoader()->G_SQLSaveOutlineOfset(GetDatabase() ,MachineID ,GetOutlineOffsetWriter());
			}
		}
		return false;
	}
	return true;
}
	
bool	LayersBase::LoadOutlineOffsetForDatabase(void)
{
	if(GetParamComm()->Mastered==true){
		bool	Ret=false;
		if(GetDatabaseLoader() && IsDatabaseOk()==true){
			Ret=GetDatabaseLoader()->G_SQLLoadOutlineOfset(GetDatabase() ,MachineID ,GetOutlineOffsetWriter());
			if(Ret==true){
				for(int phase=0;phase<GetPhaseNumb();phase++){
					PageDataInOnePhase	*Ph=GetPageDataPhase(phase);
					for(int page=0;page<GetPageNumb();page++){
						OutlineOffsetInPage Data;
						Data=GetOutlineOffsetWriter()->GetData(phase,page);
						int	X=Data.Dx;
						int	Y=Data.Dy;
						ConvertToLocal(X,Y);
						Ph->GetPageData(page)->GetOutlineOffset()->x=X;
						Ph->GetPageData(page)->GetOutlineOffset()->y=Y;
					}
				}
			}
		}
		return Ret;
	}
	else{
		bool	Ret=false;
		if(GetDatabaseLoader()){
			Ret=GetDatabaseLoader()->G_SQLLoadOutlineOfset(GetDatabase() ,MachineID ,GetOutlineOffsetWriter());
			if(Ret==true){
				for(int phase=0;phase<GetPhaseNumb();phase++){
					PageDataInOnePhase	*Ph=GetPageDataPhase(phase);
					for(int page=0;page<GetPageNumb();page++){
						OutlineOffsetInPage Data;
						Data=GetOutlineOffsetWriter()->GetData(phase,GetGlobalPageFromLocal(page));
						int	X=Data.Dx;
						int	Y=Data.Dy;
						ConvertToLocal(X,Y);
						Ph->GetPageData(page)->GetOutlineOffset()->x=X;
						Ph->GetPageData(page)->GetOutlineOffset()->y=Y;
					}
				}
			}
		}
		return Ret;
	}
}

bool	LayersBase::LoadMasterImageInMasterData(int masterCode,int _MachineID  ,int LocalPage ,QString &ErrorMsg)
{
	DataInPage	*Pg=GetPageData(LocalPage);
	QStringList	ImagePathes=GetParamGlobal()->ImageFilePath.split(QChar(';'));
	QString		ImagePath;
	QString		ImageFileName;
	int	ShadowLevel	=GetShadowLevel();
	int	ShadowNumber=GetShadowNumber();

	bool		FoundImageFileName=false;
	for(int h=0;h<ImagePathes.count();h++){
		ImagePath=ImagePathes[h];
		ImageFileName=Pg->CreateMasterImageFileName(masterCode,_MachineID,ImagePath
													,ShadowLevel,ShadowNumber);
		if(QFile::exists(ImageFileName)==true){
			FoundImageFileName=true;
			break;
		}
	}
	if(FoundImageFileName==false){
		if(ImagePathes.count()==0)
			ImagePath=/**/"";
		else
			ImagePath=ImagePathes[0];
		ImageFileName=Pg->CreateMasterImageFileName(masterCode,GetMachineIDFromMaster(),ImagePath
													,ShadowLevel,ShadowNumber);
	}
	if(Pg->LoadMasterImageFile(ImageFileName)==false){
		ErrorMsg="Error of loading MasterImage Data";
		return false;
	}
	return true;
}

bool	LayersBase::SaveMasterImageInMasterData(int masterCode,int _MachineID  ,int LocalPage ,bool ForceSave ,QString &ErrorMsg)
{
	DataInPage	*Pg=GetPageData(LocalPage);
	QStringList	ImagePathes=GetParamGlobal()->ImageFilePath.split(QChar(';'));
	QString		ImagePath;
	QString		ImageFileName;
	int	ShadowLevel	=GetShadowLevel();
	int	ShadowNumber=GetShadowNumber();

	bool		FoundImageFileName=false;
	for(int h=0;h<ImagePathes.count();h++){
		ImagePath=ImagePathes[h];
		ImageFileName=Pg->CreateMasterImageFileName(masterCode,_MachineID,ImagePath
													,ShadowLevel,ShadowNumber);
		if(QFile::exists(ImageFileName)==true){
			FoundImageFileName=true;
			break;
		}
	}
	if(FoundImageFileName==false){
		if(ImagePathes.count()==0)
			ImagePath=/**/"";
		else
			ImagePath=ImagePathes[0];
		ImageFileName=Pg->CreateMasterImageFileName(masterCode,GetMachineIDFromMaster(),ImagePath
													,ShadowLevel,ShadowNumber);
	}
	if(Pg->SaveMasterImageFile(ImageFileName,ForceSave)==false){
		ErrorMsg="Error of saving MasterImage Data";
		return false;
	}
	if(SaveShadowMasterImageFileInChildren(masterCode, GetMachineIDFromMaster(),ImagePath,ForceSave
												,0,LocalPage)==false){
		return false;
	}

	return true;
}

bool	LayersBase::LoadAlgorithmDataInMasterData(int masterCode,int _MachineID
											,AlgorithmInPageRoot *APage
											,QString &ErrorMsg)
{	
	int32		_tMachineID;
	XDateTime	_tRegTime;
	QString		_tMasterName;
	QString		_tRemark;
	int32		_tVersion;
	XDateTime	_tLastEditTime;
	int32		_tCategoryID;
	int16		_tMasterType;
	int32		iLibFolderID;
	int32 		iThresholdLevelID;
	int32 		iThresholdLevelParentID;

	//Parent->SetMachineID(machineID);
	if(GetDatabaseLoader()){
		if(GetDatabaseLoader()->G_SQLGetMasterInfo(GetDatabase() ,masterCode
											,_tMachineID
											,_tRegTime
											,_tMasterName ,_tRemark
											,_tVersion
											,_tLastEditTime
											,_tCategoryID
											,_tMasterType
											,iLibFolderID
											,iThresholdLevelID
											,iThresholdLevelParentID)==true){
			QString	LogicFileName;
			QString	ImagePath;
			QStringList	ImagePathes=GetParamGlobal()->ImageFilePath.split(QChar(';'));
			AlgorithmBase				*ABase	=APage->GetParentBase();
			AlgorithmInPageInOnePhase	*pbase	=APage->GetParentPhase();
			DataInPage					*Pg		=APage->GetDataInPage();
			LogicDLL	*p=ABase->GetLogicDLL();
			for(int g=0;g<ImagePathes.count();g++){
				ImagePath=ImagePathes[g];
				for(int h=0;h<GetParamGlobal()->CountToRetryLoading;h++){
					LogicFileName=Pg->GetLogicFileName(masterCode ,p ,_MachineID ,ImagePath);
					if(LogicFileName.isEmpty()==false){
						break;
					}
					GSleep(GetParamGlobal()->WaitingMilisecForRetryLoading);
				}

				if(GetParamGlobal()->RetryLoadIfFails==true){
					for(int h=0;h<GetParamGlobal()->CountToRetryLoading;h++){
						if(Pg->LoadLogicFile(LogicFileName ,ABase ,pbase,APage,_tVersion)==true){
							return true;
						}
						GSleep(GetParamGlobal()->WaitingMilisecForRetryLoading);
					}
				}
			}
			return true;
		}
	}
	ErrorMsg="Error of loading algorithm data";
	return false;
}

bool	LayersBase::SaveAlgorithmDataInMasterData(int masterCode,int _MachineID
											,AlgorithmInPageRoot *APage
											,QString &ErrorMsg)
{
	QString	LogicFileName;
	QString	ImagePath;
	AlgorithmBase				*ABase	=APage->GetParentBase();
	AlgorithmInPageInOnePhase	*pbase	=APage->GetParentPhase();

	QStringList	ImagePathes=GetParamGlobal()->ImageFilePath.split(QChar(';'));
	DataInPage	*Pg=APage->GetDataInPage();
	LogicDLL	*p=ABase->GetLogicDLL();
	for(int g=0;g<ImagePathes.count();g++){
		ImagePath=ImagePathes[g];
		for(int h=0;h<GetParamGlobal()->CountToRetryLoading;h++){
			LogicFileName=Pg->GetLogicFileName(masterCode ,p ,_MachineID ,ImagePath);
			if(LogicFileName.isEmpty()==false){
				break;
			}
			GSleep(GetParamGlobal()->WaitingMilisecForRetryLoading);
		}

		if(GetParamGlobal()->RetryLoadIfFails==true){
			for(int h=0;h<GetParamGlobal()->CountToRetryLoading;h++){
				if(Pg->SaveLogicFile(LogicFileName ,ABase ,pbase,APage)==true){
					return true;
				}
				GSleep(GetParamGlobal()->WaitingMilisecForRetryLoading);
			}
		}
	}
	ErrorMsg="Error of saving algorithm data";
	return false;
}

//=====================================================================================
CmdReqSaveMasterForPage::CmdReqSaveMasterForPage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int masterCode ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	MasterCode=masterCode;
}

bool	CmdReqSaveMasterForPage::Load(QIODevice *f)
{
	if(::Load(f,MasterCode)==false){
		return false;
	}
	if(::Load(f,MachineID)==false){
		return false;
	}
	if(::Load(f,ImagePath)==false){
		return false;
	}
	if(::Load(f,ForceSave)==false){
		return false;
	}
	return true;
}
bool	CmdReqSaveMasterForPage::Save(QIODevice *f)
{
	if(::Save(f,MasterCode)==false){
		return false;
	}
	if(::Save(f,MachineID)==false){
		return false;
	}
	if(::Save(f,ImagePath)==false){
		return false;
	}
	if(::Save(f,ForceSave)==false){
		return false;
	}
	return true;
}

void	CmdReqSaveMasterForPage::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	for(int phase=0;phase<GetPhaseNumb();phase++){
		PageDataInOnePhase	*Ph=GetLayersBase()->GetPageDataPhase(phase);
		DataInPage *P=Ph->GetPageData(localPage);
		QString	ErrorMsg;
		if(P->SQLSavePage(MasterCode,MachineID,ErrorMsg,ImagePath,ForceSave)==false){
			GetLayersBase()->SendErrorAckToMaster(localPage,0
						,ErrorMsg
						,ErrorCodeList::_Critical);
		}
	}
	SendAck(localPage);
}


//====================================================================================
CmdReqLoadMasterForPage::CmdReqLoadMasterForPage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int masterCode ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ModeLoadMasterImage	=true;
	MasterCode=masterCode;
}
bool	CmdReqLoadMasterForPage::Load(QIODevice *f)
{
	if(::Load(f,MasterCode)==false){
		return false;
	}
	if(::Load(f,MachineID)==false){
		return false;
	}	
	if(::Load(f,ModeLoadMasterImage)==false){
		return false;
	}
	return true;
}
bool	CmdReqLoadMasterForPage::Save(QIODevice *f)
{
	if(::Save(f,MasterCode)==false){
		return false;
	}
	if(::Save(f,MachineID)==false){
		return false;
	}
	if(::Save(f,ModeLoadMasterImage)==false){
		return false;
	}
	return true;
}

void	CmdReqLoadMasterForPage::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	bool	Ret=true;
	QString	ErrorMsg;
	LoadedInfoContainer	LInfoAll;
	for(int phase=0;phase<GetPhaseNumb();phase++){
		LoadedInfoContainerInPhaseList	*LInfo=new LoadedInfoContainerInPhaseList();
		LInfoAll.AppendList(LInfo);
		LInfo->Phase=phase;

		PageDataInOnePhase	*Ph=GetLayersBase()->GetPageDataPhase(phase);
		DataInPage *P=Ph->GetPageData(localPage);
		if(P->SQLLoadPage(MasterCode,MachineID,ModeLoadMasterImage,ErrorMsg,*LInfo)==true){
			if(GetLayersBase()->GetParamComm()->Mastered==false){
				GetLayersBase()->SetMasterCode(MasterCode);
				if(GetLayersBase()->GetDatabaseLoader()){
					QBuffer GeneralBuff;
					QBuffer	SettingBuff;
					QBuffer LightBuff;
					QBuffer GeneralStockerBuff;
					QBuffer ResultAnalizerBuff;
					int32	_MasterCode;
					int32	_MachineID;
					XDateTime RegTime;
					QString MasterName;
					QString Remark;
					int32	Version;
					XDateTime LastEditTime;
					int32	CategoryID;
					int16	MasterType;
					QImage	TopView;
					int32	iLibFolderID;
					int32 	iThresholdLevelID;
					int32 	iThresholdLevelParentID;

					if(GetLayersBase()->GetDatabaseLoader()->G_SQLLoadMasterData(*GetLayersBase()->GetDataBase()
											,GetLayersBase(),MasterCode
											,GeneralBuff ,SettingBuff
											,LightBuff
											,GeneralStockerBuff
											,ResultAnalizerBuff
											,_MasterCode ,_MachineID
											,RegTime
											,MasterName ,Remark
											,Version
											,LastEditTime
											,CategoryID
											,MasterType
											,TopView
											,iLibFolderID
											,iThresholdLevelID
											,iThresholdLevelParentID)==true){
						if(phase==0){
							GetLayersBase()->SetMasterName	(MasterName);
							GetLayersBase()->SetRemark		(Remark);
							GetLayersBase()->SetMasterType	(MasterType);
							GetLayersBase()->SetMachineIDFromMaster(MachineID);
							GetLayersBase()->SetLibFolderID	(iLibFolderID);
							GetLayersBase()->SetThresholdLevel(iThresholdLevelID);
						}
					}
				}
			}
			if(GetParamComm()->Mastered==false){
				ExecuteInitialAfterEditInfo EInfo;
				GetLayersBase()->MakeExecuteInitialAfterEditInfo(EInfo);
				GetLayersBase()->ExecuteInitialAfterEdit(EInfo,GetLayersBase()->GetEntryPoint());
			}
			//_CrtCheckMemory();
		}
		else{
			Ret=false;
		}
	}
	if(Ret==true){
		//GetLayersBase()->SendAckToMaster(localPage);
		int	gpage=GetLayersBase()->GetGlobalPageFromLocal(localPage);
		CmdAckLoadMasterForPage	Cmd(GetLayersBase(),"ANY","ANY",0);
		Cmd.LInfo=LInfoAll;
		Cmd.SendFromSlaveToMaster(gpage ,0);
		GetLayersBase()->SetAckFlag(localPage,1);
	}
	else{
		GetLayersBase()->SendErrorAckToMaster(localPage,0
						,ErrorMsg
						,ErrorCodeList::_Critical,1);
	}
}

CmdAckLoadMasterForPage::CmdAckLoadMasterForPage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	CmdAckLoadMasterForPage::Load(QIODevice *f)
{
	if(LInfo.Load(f)==false){
		return false;
	}
	return true;
}
bool	CmdAckLoadMasterForPage::Save(QIODevice *f)
{
	if(LInfo.Save(f)==false){
		return false;
	}
	return true;
}

void	CmdAckLoadMasterForPage::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->SetAckFlag(localPage,1);
	for(LoadedInfoContainerInPhaseList *p=LInfo.GetFirst();p!=NULL;p=p->GetNext()){
		PageDataInOnePhase	*Ph=GetLayersBase()->GetPageDataPhase(p->Phase);
		if(Ph!=NULL){
			DataInPage *P=Ph->GetPageData(localPage);
			if(P!=NULL){
				P->SetResultLoaded(*p);
			}
		}
	}
}

//====================================================================================
CmdReqLoadMasterForPagePhase::CmdReqLoadMasterForPagePhase(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int masterCode ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ModeLoadMasterImage	=true;
	MasterCode=masterCode;
	DestPhase	=-1;
}
bool	CmdReqLoadMasterForPagePhase::Load(QIODevice *f)
{
	if(::Load(f,MasterCode)==false){
		return false;
	}
	if(::Load(f,MachineID)==false){
		return false;
	}	
	if(::Load(f,ModeLoadMasterImage)==false){
		return false;
	}
	if(::Load(f,DestPhase)==false){
		return false;
	}
	return true;
}
bool	CmdReqLoadMasterForPagePhase::Save(QIODevice *f)
{
	if(::Save(f,MasterCode)==false){
		return false;
	}
	if(::Save(f,MachineID)==false){
		return false;
	}
	if(::Save(f,ModeLoadMasterImage)==false){
		return false;
	}
	if(::Save(f,DestPhase)==false){
		return false;
	}
	return true;
}

void	CmdReqLoadMasterForPagePhase::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	bool	Ret=true;
	QString	ErrorMsg;
	LoadedInfoContainer	LInfoAll;
	
	LoadedInfoContainerInPhaseList	*LInfo=new LoadedInfoContainerInPhaseList();
	LInfoAll.AppendList(LInfo);
	LInfo->Phase=DestPhase;

	PageDataInOnePhase	*Ph=GetLayersBase()->GetPageDataPhase(DestPhase);
	DataInPage *P=Ph->GetPageData(localPage);
	if(P->SQLLoadPage(MasterCode,MachineID,ModeLoadMasterImage,ErrorMsg,*LInfo)==true){
		if(GetLayersBase()->GetParamComm()->Mastered==false){
			GetLayersBase()->SetMasterCode(MasterCode);
			if(GetLayersBase()->GetDatabaseLoader()){
				QBuffer GeneralBuff;
				QBuffer	SettingBuff;
				QBuffer LightBuff;
				QBuffer GeneralStockerBuff;
				QBuffer ResultAnalizerBuff;
				int32	_MasterCode;
				int32	_MachineID;
				XDateTime RegTime;
				QString MasterName;
				QString Remark;
				int32	Version;
				XDateTime LastEditTime;
				int32	CategoryID;
				int16	MasterType;
				QImage	TopView;
				int32	iLibFolderID;
				int32 	iThresholdLevelID;
				int32 	iThresholdLevelParentID;

				if(GetLayersBase()->GetDatabaseLoader()->G_SQLLoadMasterData(*GetLayersBase()->GetDataBase()
										,GetLayersBase(),MasterCode
										,GeneralBuff ,SettingBuff
										,LightBuff
										,GeneralStockerBuff
										,ResultAnalizerBuff
										,_MasterCode ,_MachineID
										,RegTime
										,MasterName ,Remark
										,Version
										,LastEditTime
										,CategoryID
										,MasterType
										,TopView
										,iLibFolderID
										,iThresholdLevelID
										,iThresholdLevelParentID)==true){
					if(DestPhase==0){
						GetLayersBase()->SetMasterName	(MasterName);
						GetLayersBase()->SetRemark		(Remark);
						GetLayersBase()->SetMasterType	(MasterType);
						GetLayersBase()->SetMachineIDFromMaster(MachineID);
						GetLayersBase()->SetLibFolderID	(iLibFolderID);
						GetLayersBase()->SetThresholdLevel(iThresholdLevelID);
					}
				}
			}
		}
		if(GetParamComm()->Mastered==false){
			ExecuteInitialAfterEditInfo EInfo;
			GetLayersBase()->MakeExecuteInitialAfterEditInfo(EInfo);
			GetLayersBase()->ExecuteInitialAfterEdit(EInfo,GetLayersBase()->GetEntryPoint());
		}
		//_CrtCheckMemory();
	}
	else{
		Ret=false;
	}
	
	if(Ret==true){
		//GetLayersBase()->SendAckToMaster(localPage);
		int	gpage=GetLayersBase()->GetGlobalPageFromLocal(localPage);
		CmdAckLoadMasterForPage	Cmd(GetLayersBase(),"ANY","ANY",0);
		Cmd.LInfo=LInfoAll;
		Cmd.SendFromSlaveToMaster(gpage ,0);
		GetLayersBase()->SetAckFlag(localPage,1);
	}
	else{
		GetLayersBase()->SendErrorAckToMaster(localPage,0
						,ErrorMsg
						,ErrorCodeList::_Critical,1);
	}
}
