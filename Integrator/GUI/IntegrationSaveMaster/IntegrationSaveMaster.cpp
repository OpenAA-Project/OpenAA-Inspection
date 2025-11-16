#include "IntegrationSaveMasterResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\IntegrationSaveMaster\IntegrationSaveMaster.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "IntegrationSaveMaster.h"
#include "XGeneralFunc.h"
#include <QFileDialog>
#include "XMacroFunction.h"
#include "SaveMasterDialog.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMessageBox>
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "XDatabaseLoader.h"
#include "XMacroFunction.h"
#include "IntegrationNewMaster.h"
#include "ButtonSaveMasterData.h"
#include "ButtonUpdateMasterData.h"
#include "swap.h"

static	const	char	*sRoot=/**/"Integration";
static	const	char	*sName=/**/"SaveMaster";


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to save master data");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	(*Base)	=new IntegrationCmdSaveMaster(Base,sRoot,sName);
	(*Base)	=new IntegrationAckSaveMaster(Base,sRoot,sName);
	//(*Base)=new GUICmdReqSaveBmpJpg(Base,QString(sRoot),QString(sName));
	(*Base)	=new IntegrationReqSaveMasterReturn(Base,sRoot,sName);
	(*Base)	=new IntegrationAckSaveMasterReturn(Base,sRoot,sName);

	return true;
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new IntegrationSaveMaster(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<5)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((IntegrationSaveMaster *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((IntegrationSaveMaster *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((IntegrationSaveMaster *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((IntegrationSaveMaster *)Instance)->CFont;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/IntegrationSaveMaster.png")));
}

static	bool	MacroSaveDialog			(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroCreateNewDialog	(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroUpdateWithoutDialog(GUIFormBase *Instance ,QStringList &Args);

DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"SaveDialog";
		Functions[ret].Explain.append(/**/"Open saving dialog");
		Functions[ret].ArgName.append(/**/"Copy image to target (true/false)");
		Functions[ret].DLL_ExcuteMacro	=MacroSaveDialog;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"CreateMasterDialog";
		Functions[ret].Explain.append(/**/"Create new dialog");
		Functions[ret].DLL_ExcuteMacro	=MacroCreateNewDialog;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"UpdateWithoutDialog";
		Functions[ret].Explain.append(/**/"Update master without dialog");
		Functions[ret].DLL_ExcuteMacro	=MacroUpdateWithoutDialog;
		ret++;
	}
	return ret;
}

static bool	MacroSaveDialog(GUIFormBase *Instance ,QStringList &Args)
{
	IntegrationSaveMaster	*V=dynamic_cast<IntegrationSaveMaster *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<1){
		return false;
	}
	bool	ModeCopyImage=true;
	if(Args[0].toLower()==/**/"true"){
		ModeCopyImage=true;
	}
	else{
		ModeCopyImage=false;
	}

	V->OpenDialog(ModeCopyImage);

	return true;
}

static bool	MacroCreateNewDialog(GUIFormBase *Instance ,QStringList &Args)
{
	IntegrationSaveMaster	*V=dynamic_cast<IntegrationSaveMaster *>(Instance);
	if(V==NULL){
		return false;
	}

	V->CreateNewDialog();

	return true;
}
static bool	MacroUpdateWithoutDialog(GUIFormBase *Instance ,QStringList &Args)
{
	IntegrationSaveMaster	*V=dynamic_cast<IntegrationSaveMaster *>(Instance);
	if(V==NULL){
		return false;
	}

	V->UpdateWithoutDialog();

	return true;
}
//==================================================================================================
IntegrationSaveMaster::IntegrationSaveMaster(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.setObjectName(/**/"IntegrationSaveMasterBtn");
	Button.move(0,0);
	Msg=/**/"Save master data";
	LastOpenedFileName	=/**/"IntegratorLastOpenedID.dat";
	LastAcsendantOrder	=false;
	LastOrderMode		=0;

	Button.setStyleSheet(/**/"QToolButton {"
						/**/"	border-style: outset;"
						/**/"	border-width: 1px;"
						/**/"	border-radius: 25px;"
						/**/"	border-color: gray;"
						/**/"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));"
						/**/"}"
						/**/"QToolButton:pressed { 	"
						/**/"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));"
						/**/"}"
						);

	resize(80,25);
	connect(&Button,SIGNAL(clicked()), this ,SLOT(SlotClicked()));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

void	IntegrationSaveMaster::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	IntegrationSaveMaster::ResizeAction()
{
	Button.setGeometry(0,0,width(),height());
}

void	IntegrationSaveMaster::OpenDialog(bool ModeCopyImage)
{
	SaveWithDialog(ModeCopyImage);
}

void	IntegrationSaveMaster::SlotClicked ()
{
//	if(GetLayersBase()->GetIntegrationBasePointer()->NowOnUsing()==false){
		SaveWithDialog(false);
//	}
}

void	IntegrationSaveMaster::UpdateWithoutDialog(void)
{
	QString RetRelationNumber	;
	QString RetRelationName	;
	QString RetRemark		;
	int		RetRelationType	;
	QByteArray	CommonByteArray;
	int32	ThresholdLevelID;
	if(GetLayersBase()->GetDatabaseLoader()->G_GetMasterRelation(GetLayersBase()->GetDatabase() 
									,GetLayersBase()->GetIntegrationBasePointer()->GetMasterRelationCode()
									,RetRelationNumber
									,RetRelationName
									,RetRemark
									,RetRelationType
									,CommonByteArray
									,ThresholdLevelID)==true){

		IntegrationCommonData	CommonData(CommonByteArray);

		GetLayersBase()->ShowProcessingForm(LangSolver.GetString(IntegrationSaveMaster_LS,LID_0)/*"繝槭せ繧ｿ繝ｼ繝��繧ｿ荳頑嶌縺肴峩譁ｰ荳ｭ"*/);

		int	N=GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveCount();
		for(int SlaveNo=0;SlaveNo<N;SlaveNo++){
			EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
			if(m->IsDependent()==false){
				IntegrationCmdSaveMaster	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
				IntegrationAckSaveMaster	ACmd(GetLayersBase(),sRoot,sName,SlaveNo);
				RCmd.MasterCode		=m->GetMasterCode();
				RCmd.ResultName		=RetRelationName;
				RCmd.ResultRemark	=RetRemark;
				RCmd.RelationCode	=GetLayersBase()->GetIntegrationBasePointer()->GetMasterRelationCode();
				RCmd.CommonData		=CommonData;
				RCmd.ModeCopyImage	=false;
				if(RCmd.Send(SlaveNo,0,ACmd)==true){
					EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
					if(m!=NULL){
						m->SetMasterCode(ACmd.MasterCode);
						m->SetMasterName(RetRelationName);
					}
				}
			}
			GSleep(2000);
		}
		//int	YLen=GetParamGlobal()->TransformUnitDistanceToPixel(0,(CommonData.CommonSizeY+CommonData.AddedY));
		//int	DotPerLine=GetParamGlobal()->DotPerLine;
		//GetLayersBase()->GetIntegrationBasePointer()->ReallocXYPixels(DotPerLine ,YLen);

		for(int SlaveNo=0;SlaveNo<N;SlaveNo++){
			EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
			if(m!=NULL){
				for(int page=0;page<m->GetPageNumb();page++){
					int	YLen=GetParamGlobal()->TransformUnitDistanceToPixel(page,0,CommonData.CommonSizeY+CommonData.AddedY);
					int	XLen=m->GetDotPerLine(0,page);
					m->ReallocXYPixels(page,XLen ,YLen);
				}
			}
		}



		for(EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
			m->ReleaseImageBuffer();
			bool	OKSlaveInfo=false;
			for(int i=0;i<10;i++){
				if(m->RequireSlaveInfo()==true){
					OKSlaveInfo=true;
					break;
				}
				GSleep(2000);
			}
			if(OKSlaveInfo==true){
				m->RequireMasterImage(GetParamGlobal()->MixMasterForIntegration);
			}
		}
		CmdUpdatedMasterImage	ICmd;
		BroadcastSpecifiedDirectly(&ICmd);
		CreateUpdateMasterSpecifiedBroadcaster	LSCmd;
		BroadcastSpecifiedDirectly(&LSCmd);
			
		GetLayersBase()->GetIntegrationBasePointer()->UpdateLastLoadedTimeMasterRelation();

		GetLayersBase()->CloseProcessingForm();
	}
}
void	IntegrationSaveMaster::CreateNewDialog(void)
{
	SaveWithDialog(false,true,false);
}
void	IntegrationSaveMaster::SaveWithDialog(bool ModeCopyImage ,bool ModeNew ,bool ModeUpdate)
{
	SaveMasterDialog	D(GetLayersBase() ,this,ModeNew ,ModeUpdate);
	int	Ret=D.exec();
	if(Ret==1){
		GetLayersBase()->ShowProcessingForm(LangSolver.GetString(IntegrationSaveMaster_LS,LID_6)/*"繝槭せ繧ｿ繝ｼ繝��繧ｿ譁ｰ隕丈ｿ晏ｭ倅ｸｭ"*/);
		int		RetRelationCode;

		IntegrationNewMaster	*f=(IntegrationNewMaster *)GetLayersBase()->FindByName(/**/"Integration",/**/"NewMaster",/**/"");
		if(f!=NULL){
			D.CommonData.AddedX	=f->AddedMMX;
			D.CommonData.AddedY	=f->AddedMMY;
			D.CommonData.AddedZ	=f->AddedMMZ;
		}
		QByteArray	CommonByteAray;
		QBuffer	CommonBuff;
		CommonBuff.open(QIODevice::WriteOnly);
		D.CommonData.Save(&CommonBuff);
		GetLayersBase()->GetMainWidget()->SaveAll(&CommonBuff);
		CommonByteAray=CommonBuff.buffer();
		int32 ThresholdLevelID=GetLayersBase()->GetIntegrationBasePointer()->GetThresholdLevelID();
		
		GetLayersBase()->LockForLoadSave();
		bool Ret=GetLayersBase()->GetDatabaseLoader()->G_CreateNewMasterRelation(*GetLayersBase()->GetDataBase()
										,RetRelationCode
										,D.ResultNumber
										,D.ResultName
										,D.ResultRemark
										,0
										,CommonByteAray
										,ThresholdLevelID);
		GetLayersBase()->UnlockForLoadSave();
		if(Ret==false){
			GetLayersBase()->CloseProcessingForm();
			QMessageBox::critical(NULL,LangSolver.GetString(IntegrationSaveMaster_LS,LID_7)/*"Error"*/,LangSolver.GetString(IntegrationSaveMaster_LS,LID_8)/*"Can not create new relation for masterdata"*/);
			return;
		}

		GetLayersBase()->GetIntegrationBasePointer()->MasterRelationCode=RetRelationCode;

		for(EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
			if(m->IsDependent()==false){
				int	SlaveNo=m->GetIntegrationSlaveNo();
				IntegrationCmdSaveMaster	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
				IntegrationAckSaveMaster	ACmd(GetLayersBase(),sRoot,sName,SlaveNo);
				RCmd.RelationCode	=RetRelationCode;
				RCmd.MasterCode		=-1;
				RCmd.ResultName		=D.ResultName;
				RCmd.ResultRemark	=D.ResultRemark;
				RCmd.CommonData		=D.CommonData;
				RCmd.ModeCopyImage	=ModeCopyImage;
				m->SetMasterName(D.ResultName);
				//if(RCmd.Send(SlaveNo,0,ACmd)==true){
				//	m->MasterCode	=ACmd.MasterCode;
				//	m->MasterName	=D.ResultName;
				//}
				RCmd.Send(NULL,SlaveNo,0);
			}
		}
		//int	YLen=GetParamGlobal()->TransformUnitDistanceToPixel(0,(D.CommonData.CommonSizeY+D.CommonData.AddedY));
		//int	DotPerLine=GetParamGlobal()->DotPerLine;
		//GetLayersBase()->GetIntegrationBasePointer()->ReallocXYPixels(DotPerLine ,YLen);
		for(EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
			if(m->IsDependent()==false){
				for(int page=0;page<m->GetPageNumb();page++){
					int	YLen=GetParamGlobal()->TransformUnitDistanceToPixel(page,0,(D.CommonData.CommonSizeY+D.CommonData.AddedY));
					int	XLen=m->GetDotPerLine(0,page);
					m->ReallocXYPixels(page,XLen ,YLen);
				}
			}
		}

		bool	NowOnIdle;
		do{
			NowOnIdle=true;
			for(EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
				int	SlaveNo=m->GetIntegrationSlaveNo();
				if(GetLayersBase()->GetIntegrationBasePointer()->CheckOnProcessing(SlaveNo)==false){
					NowOnIdle=false;
				}
			}
		}while(NowOnIdle==false);

		for(EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
			if(m->IsDependent()==false){
				int	SlaveNo=m->GetIntegrationSlaveNo();
				IntegrationReqSaveMasterReturn	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
				IntegrationAckSaveMasterReturn	ACmd(GetLayersBase(),sRoot,sName,SlaveNo);
				if(RCmd.Send(SlaveNo,0,ACmd)==true){
					if(ACmd.ExeReturn==false){
						GetLayersBase()->CloseProcessingForm();
						QMessageBox::critical(NULL,QString(LangSolver.GetString(IntegrationSaveMaster_LS,LID_9)/*"Error Slave:"*/)+QString::number(SlaveNo)
											  ,ACmd.ErrorMessageOfFalse);
						return;
					}
				}
			}
		}

		for(EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
			m->ReleaseImageBuffer();
			bool	OKSlaveInfo=false;
			for(int i=0;i<10;i++){
				if(m->RequireSlaveInfo()==true){
					OKSlaveInfo=true;
					break;
				}
				GSleep(2000);
			}
			if(OKSlaveInfo==true){
				m->RequireMasterImage(GetParamGlobal()->MixMasterForIntegration);
			}
		}
				
		{
			QFile	File(LastOpenedFileName);
			if(File.open(QIODevice::ReadWrite)==true){
				::Load(&File,LastOpenedID);
				::Load(&File,LastAcsendantOrder);
				::Load(&File,LastOrderMode);

				File.seek(0);
				LastOpenedID		=RetRelationCode;
				::Save(&File,LastOpenedID);
				::Save(&File,LastAcsendantOrder);
				::Save(&File,LastOrderMode);
			}
		}
		GetLayersBase()->GetIntegrationBasePointer()->LoadLotData();
		CmdUpdatedMasterImage	ICmd;
		BroadcastSpecifiedDirectly(&ICmd);
		
		CreateUpdateMasterSpecifiedBroadcaster	LSCmd;
		BroadcastSpecifiedDirectly(&LSCmd);

		BroadcastBuildForShow();
		GetLayersBase()->GetIntegrationBasePointer()->UpdateLastLoadedTimeMasterRelation();


		GetLayersBase()->CloseProcessingForm();
	}
	else if(Ret==2){
		GetLayersBase()->ShowProcessingForm(LangSolver.GetString(IntegrationSaveMaster_LS,LID_10)/*"繝槭せ繧ｿ繝ｼ繝��繧ｿ荳頑嶌縺肴峩譁ｰ荳ｭ"*/);

		IntegrationNewMaster	*f=(IntegrationNewMaster *)GetLayersBase()->FindByName(/**/"Integration",/**/"NewMaster",/**/"");
		if(f!=NULL){
			D.CommonData.AddedX	=f->AddedMMX;
			D.CommonData.AddedY	=f->AddedMMY;
			D.CommonData.AddedZ	=f->AddedMMZ;
		}

		QByteArray	CommonByteAray;
		QBuffer	CommonBuff;
		CommonBuff.open(QIODevice::WriteOnly);
		D.CommonData.Save(&CommonBuff);
		GetLayersBase()->GetMainWidget()->SaveAll(&CommonBuff);

		CommonByteAray=CommonBuff.buffer();
		int32 ThresholdLevelID=GetLayersBase()->GetIntegrationBasePointer()->GetThresholdLevelID();

		GetLayersBase()->LockForLoadSave();
		bool Ret=GetLayersBase()->GetDatabaseLoader()->G_UpdateMasterRelation(*GetLayersBase()->GetDataBase()
										,GetLayersBase()->GetIntegrationBasePointer()->GetMasterRelationCode()
										,D.ResultNumber
										,D.ResultName
										,D.ResultRemark
										,0
										,CommonByteAray
										,ThresholdLevelID);
		GetLayersBase()->UnlockForLoadSave();
		if(Ret==false){
			GetLayersBase()->CloseProcessingForm();
			QMessageBox::critical(NULL,LangSolver.GetString(IntegrationSaveMaster_LS,LID_11)/*"Error"*/,LangSolver.GetString(IntegrationSaveMaster_LS,LID_12)/*"Can not update relation for masterdata"*/);
			return;
		}

		int	N=GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveCount();
		for(int SlaveNo=0;SlaveNo<N;SlaveNo++){
			EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
			if(m!=NULL && m->IsDependent()==false){
				IntegrationCmdSaveMaster	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
				IntegrationAckSaveMaster	ACmd(GetLayersBase(),sRoot,sName,SlaveNo);
				RCmd.MasterCode		=m->GetMasterCode();
				RCmd.ResultName		=D.ResultName;
				RCmd.ResultRemark	=D.ResultRemark;
				RCmd.RelationCode	=GetLayersBase()->GetIntegrationBasePointer()->GetMasterRelationCode();
				RCmd.CommonData		=D.CommonData;
				RCmd.ModeCopyImage	=false;
				m->SetMasterName(D.ResultName);

				//if(RCmd.Send(SlaveNo,0,ACmd)==true){
				//	EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
				//	if(m!=NULL){
				//		m->MasterCode	=ACmd.MasterCode;
				//		m->MasterName	=D.ResultName;
				//	}
				//}
				RCmd.Send(NULL,SlaveNo,0);
			}
		}
		//int	YLen=GetParamGlobal()->TransformUnitDistanceToPixel(0,(D.CommonData.CommonSizeY+D.CommonData.AddedY));
		//int	DotPerLine=GetParamGlobal()->DotPerLine;
		//GetLayersBase()->GetIntegrationBasePointer()->ReallocXYPixels(DotPerLine,YLen);
		for(EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
			if(m->IsDependent()==false){
				for(int page=0;page<m->GetPageNumb();page++){
					int	YLen=GetParamGlobal()->TransformUnitDistanceToPixel(page,0,(D.CommonData.CommonSizeY+D.CommonData.AddedY));
					int	XLen=m->GetDotPerLine(0,page);
					m->ReallocXYPixels(page,XLen ,YLen);
				}
			}
		}

		bool	NowOnIdle;
		do{
			NowOnIdle=true;
			for(EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
				int	SlaveNo=m->GetIntegrationSlaveNo();
				if(GetLayersBase()->GetIntegrationBasePointer()->CheckOnProcessing(SlaveNo)==false){
					NowOnIdle=false;
				}
			}
		}while(NowOnIdle==false);

		for(EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
			if(m->IsDependent()==false){
				int	SlaveNo=m->GetIntegrationSlaveNo();
				IntegrationReqSaveMasterReturn	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
				IntegrationAckSaveMasterReturn	ACmd(GetLayersBase(),sRoot,sName,SlaveNo);
				if(RCmd.Send(SlaveNo,0,ACmd)==true){
					if(ACmd.ExeReturn==false){
						GetLayersBase()->CloseProcessingForm();
						QMessageBox::critical(NULL,QString(LangSolver.GetString(IntegrationSaveMaster_LS,LID_13)/*"Error Slave:"*/)+QString::number(SlaveNo)
											  ,ACmd.ErrorMessageOfFalse);
						return;
					}
				}
			}
		}

		for(EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
			m->ReleaseImageBuffer();
			bool	OKSlaveInfo=false;
			for(int i=0;i<10;i++){
				if(m->RequireSlaveInfo()==true){
					OKSlaveInfo=true;
					break;
				}
				GSleep(2000);
			}
			if(OKSlaveInfo==true){
				m->RequireMasterImage(GetParamGlobal()->MixMasterForIntegration);
			}
		}
		{
			QFile	File(LastOpenedFileName);
			if(File.open(QIODevice::ReadWrite)==true){
				::Load(&File,LastOpenedID);
				::Load(&File,LastAcsendantOrder);
				::Load(&File,LastOrderMode);

				File.seek(0);
				LastOpenedID		=GetLayersBase()->GetIntegrationBasePointer()->GetMasterRelationCode();
				::Save(&File,LastOpenedID);
				::Save(&File,LastAcsendantOrder);
				::Save(&File,LastOrderMode);
			}
		}

		CmdUpdatedMasterImage	ICmd;
		BroadcastSpecifiedDirectly(&ICmd);
		CreateUpdateMasterSpecifiedBroadcaster	LSCmd;
		BroadcastSpecifiedDirectly(&LSCmd);
		GetLayersBase()->GetIntegrationBasePointer()->UpdateLastLoadedTimeMasterRelation();

		GetLayersBase()->CloseProcessingForm();
	}
}
bool	IntegrationSaveMaster::CheckDupInMaster( const QString &ResultName
												,const QString &ResultNumber
												,const QString &ResultRemark
												,bool NewMode)
{
	IntList		RelationMasterCodes;
	if(GetLayersBase()->GetDatabaseLoader()->G_FindMasterRelation(GetLayersBase()->GetDatabase()
																,ResultName
																,ResultNumber
																,ResultRemark
																,RelationMasterCodes)==false){
		return false;
	}
	if(NewMode==false){
		int	RelationCode=GetLayersBase()->GetIntegrationBasePointer()->GetMasterRelationCode();
		if(RelationCode>0){
			if(RelationMasterCodes.GetCount()!=0 
			&& RelationMasterCodes.IsInclude(RelationCode)==false){
				return false;
			}
		}
		else{
			if(RelationMasterCodes.GetCount()!=0){
				return false;
			}
		}
	}
	else{
		if(RelationMasterCodes.GetCount()!=0){
			return false;
		}
	}
	return true;
}

//================================================================================================
IntegrationCmdSaveMaster::IntegrationCmdSaveMaster(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdSaveMaster::Load(QIODevice *f)
{
	if(::Load(f,RelationCode	)==false)
		return false;
	if(::Load(f,MasterCode	)==false)
		return false;
	if(::Load(f,ResultName	)==false)
		return false;
	if(::Load(f,ResultRemark)==false)
		return false;
	if(CommonData.Load(f)==false)
		return false;
	if(::Load(f,ModeCopyImage)==false)
		return false;
	return true;
}
bool	IntegrationCmdSaveMaster::Save(QIODevice *f)
{
	if(::Save(f,RelationCode	)==false)
		return false;
	if(::Save(f,MasterCode	)==false)
		return false;
	if(::Save(f,ResultName	)==false)
		return false;
	if(::Save(f,ResultRemark)==false)
		return false;
	if(CommonData.Save(f)==false)
		return false;
	if(::Save(f,ModeCopyImage)==false)
		return false;
	return true;
}
void	IntegrationCmdSaveMaster::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(MasterCode<0){
		//int	Length=GetParamGlobal()->TransformUnitDistanceToPixel(0,(CommonData.CommonSizeY+CommonData.AddedY));
		//int	DotPerLine	=GetParamGlobal()->DotPerLine;
		//int	MaxLines	=GetParamGlobal()->MaxLines;
		//GetLayersBase()->ReallocXYPixels(DotPerLine,max(Length,MaxLines));
	}
	GetLayersBase()->WriteAllSettingFiles();
	bool ExeReturn=true;
	IntegrationSaveMaster	*MForm=(IntegrationSaveMaster *)GetLayersBase()->FindByName(sRoot,sName,/**/"");
	if(MForm!=NULL){
		MForm->ErrorMessageOfFalse.clear();
	}

	if(MasterCode<0){
		if(ModeCopyImage==true){
			GUIFormBase	*g=GetLayersBase()->FindByName(/**/"Inspection",/**/"DisplayMasterImage",/**/"");
			if(g!=NULL){
				QStringList Args;
				bool tExeReturn;
				g->ExecuteMacro(/**/"CopyTargetImageToMaster", Args, tExeReturn);
			}
		}
		GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Button",/**/"SaveMasterData",/**/"");
		if(f!=NULL){
			QStringList Args;
			Args.append(ResultName);
			Args.append(ResultRemark);
			Args.append(/**/"TRUE");	//Silent mode
			f->ExecuteMacro(/**/"SaveMaster", Args, ExeReturn);
		}
		if(ExeReturn==false){
			ButtonSaveMasterData	*GForm=dynamic_cast<ButtonSaveMasterData *>(f);
			if(GForm!=NULL && MForm!=NULL){
				MForm->ErrorMessageOfFalse=GForm->ErrorMessageOfFalse;
			}
		}
		if(MForm!=NULL){
			MForm->ExeReturn=ExeReturn;
		}
	}
	else{
		GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Button",/**/"UpdateMasterData",/**/"");
		if(f!=NULL){
			QStringList Args;
			Args.append(ResultName);
			Args.append(ResultRemark);
			Args.append(/**/"TRUE");	//Silent mode
			f->ExecuteMacro(/**/"UpdateMaster", Args, ExeReturn);
		}
		if(ExeReturn==false){
			ButtonUpdateMasterData	*GForm=dynamic_cast<ButtonUpdateMasterData *>(f);
			if(GForm!=NULL && MForm!=NULL){
				MForm->ErrorMessageOfFalse=GForm->ErrorMessageOfFalse;
			}
		}
		if(MForm!=NULL){
			MForm->ExeReturn=ExeReturn;
		}
	}
	int	SlaveNo=0;
	if(GetLayersBase()->GetIntegrationBasePointer()!=NULL
	&& GetLayersBase()->GetIntegrationBasePointer()->GetParamIntegrationMaster()!=NULL){
		SlaveNo=GetLayersBase()->GetIntegrationBasePointer()->GetParamIntegrationMaster()->OwnSlaveNo;
	}

	GetLayersBase()->LockForLoadSave();
	GetLayersBase()->GetDatabaseLoader()->G_SetRelationOnMasterData(*GetLayersBase()->GetDataBase()
																,GetLayersBase()->GetMasterCode()
																,RelationCode
																,SlaveNo);
	GetLayersBase()->UnlockForLoadSave();
}

IntegrationAckSaveMaster::IntegrationAckSaveMaster(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationAckSaveMaster::Load(QIODevice *f)
{
	if(::Load(f,MasterCode)==false)
		return false;
	return true;
}
bool	IntegrationAckSaveMaster::Save(QIODevice *f)
{
	if(::Save(f,MasterCode)==false)
		return false;
	return true;
}

//===========================================================================
IntegrationReqSaveMasterReturn::IntegrationReqSaveMasterReturn(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
void	IntegrationReqSaveMasterReturn::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	IntegrationAckSaveMasterReturn	*SendBack=GetSendBackIntegration(IntegrationAckSaveMasterReturn,GetLayersBase(),EmitterRoot,EmitterName ,slaveNo);

	IntegrationSaveMaster	*MForm=(IntegrationSaveMaster *)GetLayersBase()->FindByName(sRoot,sName,/**/"");
	if(MForm!=NULL){
		SendBack->ExeReturn			 =MForm->ExeReturn;
		SendBack->ErrorMessageOfFalse=MForm->ErrorMessageOfFalse;
	}
	SendBack->Send(this ,slaveNo,0);
	CloseSendBackIntegration(SendBack);
}

IntegrationAckSaveMasterReturn::IntegrationAckSaveMasterReturn(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}

bool	IntegrationAckSaveMasterReturn::Load(QIODevice *f)
{
	if(::Load(f,ExeReturn)==false)
		return false;
	if(::Load(f,ErrorMessageOfFalse)==false)
		return false;
	return true;
}
bool	IntegrationAckSaveMasterReturn::Save(QIODevice *f)
{
	if(::Save(f,ExeReturn)==false)
		return false;
	if(::Save(f,ErrorMessageOfFalse)==false)
		return false;
	return true;
}

