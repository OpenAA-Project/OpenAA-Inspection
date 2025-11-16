#include "SaveTargetInNGResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\SaveTargetInNG\SaveTargetInNG.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "SaveTargetInNG.h"
#include "SaveImageTargetButton.h"
#include "InputPathListDialog.h"
#include <QVariant>
#include "XDataInLayer.h"
#include "XGeneralStocker.h"

static	const	char	*sRoot=/**/"Button";
static	const	char	*sName=/**/"SaveTargetInNG";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to draw all controls again");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdReqOkNG	(Base,sRoot,sName);
	(*Base)=new GUICmdSendOkNG(Base,sRoot,sName);
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
	return(new SaveTargetInNG(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<11)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((SaveTargetInNG *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((SaveTargetInNG *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((SaveTargetInNG *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((SaveTargetInNG *)Instance)->CFont;
	Data[4].Type				 =/**/"bool";
	Data[4].VariableNameWithRoute=/**/"BootupON";
	Data[4].Pointer				 =&((SaveTargetInNG *)Instance)->BootupON;
	Data[5].Type				 =/**/"bool";
	Data[5].VariableNameWithRoute=/**/"UseCamImage";
	Data[5].Pointer				 =&((SaveTargetInNG *)Instance)->UseCamImage;
	Data[6].Type				 =/**/"bool";
	Data[6].VariableNameWithRoute=/**/"CheckDisk";
	Data[6].Pointer				 =&((SaveTargetInNG *)Instance)->CheckDisk;
	Data[7].Type				 =/**/"QStringList";
	Data[7].VariableNameWithRoute=/**/"SaveFolderList";
	Data[7].Pointer				 =&((SaveTargetInNG *)Instance)->SaveFolderList;
	Data[8].Type				 =/**/"bool";
	Data[8].VariableNameWithRoute=/**/"UseGeneralStockerToGetPath";
	Data[8].Pointer				 =&((SaveTargetInNG *)Instance)->UseGeneralStockerToGetPath;
	Data[9].Type				 =/**/"int32";
	Data[9].VariableNameWithRoute=/**/"DiskSpaceToCheck";
	Data[9].Pointer				 =&((SaveTargetInNG *)Instance)->DiskSpaceToCheck;
	Data[10].Type				 =/**/"int32";
	Data[10].VariableNameWithRoute=/**/"UseLayer";
	Data[10].Pointer				 =&((SaveTargetInNG *)Instance)->UseLayer;
	return(11);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/SaveTargetInNG.png")));
}

//==================================================================================================
SaveTargetInNG::SaveTargetInNG(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent),Button(false,this)
{
	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"Save Target";
	resize(80,25);
	LastInspectionID=-1;
	SavedFolder	=LangSolver.GetString(SaveTargetInNG_LS,LID_0)/*"D:\\LogImage"*/;
	OnlyNG		=true;
	BootupON	=false;
	UseCamImage	=true;
	CheckDisk	=false;
	UseGeneralStockerToGetPath	=false;
	SaveForm	=NULL;
	UseLayer	=-1;

	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));

	GetParamGUI()->SetParam(&SavedFolder, /**/"SaveTargetInNG",/**/"SavedFolder"		
							,LangSolver.GetString(SaveTargetInNG_LS,LID_1)/*"PIX data folder to be saved"*/		);
	GetParamGUI()->SetParam(&OnlyNG		, /**/"SaveTargetInNG",/**/"OnlyNG"		
							,LangSolver.GetString(SaveTargetInNG_LS,LID_2)/*"Save image of only NG result"*/		);
}

SaveTargetInNG::~SaveTargetInNG(void)
{
}

void	SaveTargetInNG::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
	Button.setChecked(BootupON);
}

void	SaveTargetInNG::ResizeAction()
{
	Button.resize(width(),height());
}

void	SaveTargetInNG::ShowInPlayer(int64 shownInspectionID)
{
	if(SaveForm==NULL){
		SaveForm=GetLayersBase()->FindByName(/**/"Inspection",/**/"SaveImageTargetButton",/**/"");
	}
	ResultInspection	*R=GetLayersBase()->GetBufferedResult(shownInspectionID);
	if(R!=NULL && Button.isChecked()==true){

		//if(LastInspectionID!=shownInspectionID){
			bool3	ShouldWrite=false3;
			for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
				int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
				GUICmdReqOkNG		CmdReq(GetLayersBase(),sRoot,sName,GlobalPage);
				CmdReq.ShownInspectionID=shownInspectionID;
				GUICmdSendOkNG		CmdAck(GetLayersBase(),sRoot,sName,GlobalPage);
				if(CmdReq.Send(GlobalPage ,0,CmdAck)==true){
					if(CmdAck.ResultOk==none3){
						ShouldWrite=none3;
					}
					if(CmdAck.ResultOk==false3 && ShouldWrite==false3){
						ShouldWrite=true3;
					}
				}
			}
			QString	tSavedFolder	=SavedFolder;
			QString	tSavedFileName;
			if(UseGeneralStockerToGetPath==true){
				QList<QVariant> Arguments;
				QList<QVariant> ReturnedValues;
				Arguments << DiskSpaceToCheck;
				if( true==(GetLayersBase()->GetGeneralStocker()->GetData("GetFolder", ReturnedValues, Arguments)) ){
					if(ReturnedValues.count()>=1)
						tSavedFolder	=ReturnedValues[0].toString();
					if(ReturnedValues.count()>=2)
						tSavedFileName	=ReturnedValues[1].toString();
				}
			}
			if(tSavedFileName.isEmpty()==true){
				tSavedFileName=QDateTime::currentDateTime().toString(/**/"yyMMdd-hhmmss");
			}
			if(OnlyNG==true && ShouldWrite==true3){
				ForceDirectories(tSavedFolder);
				CmdReqSaveImage	Cmd(GetLayersBase());
				if(UseCamImage==true && GetParamGlobal()->AllocCamTargetBuffer==true){
					Cmd.UsageImageMode=CmdReqSaveImage::_SaveCamImage;
				}
				Cmd.FileName=tSavedFolder+GetSeparator()+tSavedFileName
											+ QString(/**/"-NG.pix");
				Cmd.UseLayer	=UseLayer;
				if(SaveForm!=NULL){
					R->AddRemark(Cmd.FileName);
					if(UseGeneralStockerToGetPath==true){
						QList<QVariant> Arguments;
						QList<QVariant> ReturnedValues;
						GetLayersBase()->GetGeneralStocker()->GetData("PermitToWriteResult", ReturnedValues, Arguments);
					}
					SaveForm->TransmitDirectly(&Cmd);
				}
			}
			else if(OnlyNG==false && (ShouldWrite==true3 || ShouldWrite==false3)){
				ForceDirectories(tSavedFolder);
				CmdReqSaveImage	Cmd(GetLayersBase());
				if(UseCamImage==true && GetParamGlobal()->AllocCamTargetBuffer==true){
					Cmd.UsageImageMode=CmdReqSaveImage::_SaveCamImage;
				}
				if(ShouldWrite==true3)
					Cmd.FileName=tSavedFolder+GetSeparator()+tSavedFileName + QString(/**/"-NG.pix");
				else
					Cmd.FileName=tSavedFolder+GetSeparator()+tSavedFileName + QString(/**/"-OK.pix");
				Cmd.UseLayer	=UseLayer;
				if(SaveForm!=NULL){
					R->AddRemark(Cmd.FileName);
					if(UseGeneralStockerToGetPath==true){
						QList<QVariant> Arguments;
						QList<QVariant> ReturnedValues;
						GetLayersBase()->GetGeneralStocker()->GetData("PermitToWriteResult", ReturnedValues, Arguments);
					}
					SaveForm->TransmitDirectly(&Cmd);
				}
			}
		//}
	}
	LastInspectionID=shownInspectionID;
}


//=====================================================================================
GUICmdReqOkNG::GUICmdReqOkNG(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqOkNG::Load(QIODevice *f)
{
	if(::Load(f,ShownInspectionID)==false)
		return false;
	return true;
}
bool	GUICmdReqOkNG::Save(QIODevice *f)
{
	if(::Save(f,ShownInspectionID)==false)
		return false;
	return true;
}

void	GUICmdReqOkNG::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendOkNG	*SendBack=GetSendBack(GUICmdSendOkNG,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	ResultInspection	*R=GetLayersBase()->GetBufferedResult(ShownInspectionID);
	if(R!=NULL){
		R->GatherResult(localPage,SendBack->ResultOk,SendBack->ResultMaxError,SendBack->ResultTimeOut);
		SendBack->CriticalError	=R->GetCriticalError();
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendOkNG::GUICmdSendOkNG(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	CriticalError	=ResultInspection::_NoError;
	ResultOk		=true3;
	ResultTimeOut	=false;
	ResultMaxError	=false;
}

bool	GUICmdSendOkNG::Load(QIODevice *f)
{
	WORD	iCriticalError;
	if(::Load(f,iCriticalError)==false)
		return false;
	CriticalError=(ResultInspection::CriticalErrorMode)iCriticalError;

	if(::Load(f,ResultOk)==false)
		return false;
	if(::Load(f,ResultTimeOut )==false)
		return false;
	if(::Load(f,ResultMaxError)==false)
		return false;
	return true;
}
bool	GUICmdSendOkNG::Save(QIODevice *f)
{
	WORD	iCriticalError=(WORD)CriticalError;
	if(::Save(f,iCriticalError)==false)
		return false;

	if(::Save(f,ResultOk)==false)
		return false;
	if(::Save(f,ResultTimeOut )==false)
		return false;
	if(::Save(f,ResultMaxError)==false)
		return false;
	return true;
}

void	GUICmdSendOkNG::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}
