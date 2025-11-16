#include "ButtonSelectLotResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonSelectLot\ButtonSelectLot.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ButtonSelectLot.h"
#include "XExecuteInspectBase.h"
#include "XGeneralFunc.h"
#include "SelectLotForm.h"
#include "XGeneralDialog.h"
#include "XResultDLLManager.h"
#include "XSequenceLocal.h"
#include "XFileRegistry.h"
#include "XLotInformation.h"



char	*sRoot=/**/"Button";
char	*sName=/**/"SelectLot";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button for select-lot dialog");
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdSelectLot(Base ,sRoot,sName ,-1);

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonSelectLot(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	return(0);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonSelectLot.png")));
}

//==================================================================================================


ButtonSelectLot::ButtonSelectLot(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent),Button(parent,false)
{
	//言語対応
	FileRegistry	*FRegistry=new FileRegistry(/**/"./MachineInfo.dat");
	int	LanguageCode=FRegistry->LoadRegInt(/**/"Language",0);

	QString ImageBmpFile[5]={
		/**/":Resources/SelectLotImage.bmp",	//日本語
		/**/":Resources/SelectLotImage-en.bmp",	//English
		/**/":Resources/SelectLotImage-en.bmp",	//簡体中文
		/**/":Resources/SelectLotImage-en.bmp",	//繁体中文
		/**/":Resources/SelectLotImage-en.bmp"	//Korean
	};
	Button.setImageBmp(QImage(ImageBmpFile[LanguageCode]));

	Button.setParent(this);
	Button.move(0,0);
	Button.setObjectName(/**/"ButtonSelectLot");
	resize(176,74);
	connect(&Button,SIGNAL(SignalClicked(bool)),this,SLOT(SlotClicked(bool)));
	connect(this,	SIGNAL(SignalResize()),		this,SLOT(ResizeAction()));
	LoadLastID=true;
	GetParamGUI()->SetParam(&LoadLastID, /**/"ButtonSelectLot",/**/"LoadLastID"	,LangSolver.GetString(ButtonSelectLot_LS,LID_0)/*"True if loading last ID"*/);
}

ButtonSelectLot::~ButtonSelectLot(void)
{
}

void	ButtonSelectLot::Prepare(void)
{
	ResizeAction();
}

void	ButtonSelectLot::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonSelectLot::SlotClicked (bool checked)
{
	SelectLotForm	*SelectLot=new SelectLotForm(GetLayersBase(),this,this,GetMaxLines());
	LogoInQWidget(GetLayersBase(),SelectLot,sRoot ,sName);
//	GeneralDialog	D(GetLayersBase(),SelectLot,this);
	GeneralDialog	D(GetLayersBase(),SelectLot,0);
	D.exec();
	if(SelectLot->RetMode==true){
		GetLayersBase()->RemoveStockedResult();

		GetLayersBase()->GetLot(0)->SetLotAutoCount	(SelectLot->SelectedLotAutoCount);
		GetLayersBase()->GetLot(0)->SetLotID			(SelectLot->SelectedLotID);
		GetLayersBase()->GetLot(0)->SetLotName		(SelectLot->SelectedLotName);
		GetLayersBase()->ClearInspectID();
		int64 InspectionID=0;
		if(LoadLastID==true){
			if(GetLayersBase()->GetResultDLLBase()->GetLastInspectionID(GetLayersBase()->GetMasterCode(),SelectLot->SelectedLotID,InspectionID)==true)
				InspectionID++;
		}
		GetLayersBase()->SetCurrentInspectID(InspectionID);

		GetLayersBase()->SetForceChangedInspectID();
		GetLayersBase()->GetResultHistryData()->Reset();

		BroadcastDirectly(_BC_BuildForShow ,GetLayersBase()->GetCurrentInspectIDForDisplay());

		//今回検査ID(S102)にも検査IDをセットする
		if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
			SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
			if(Param!=NULL){
				Param->InspectionID=InspectionID;
			}
		}
		for(int page=0;page<GetPageNumb();page++){
			GUICmdSelectLot	RCmd(GetLayersBase(),sRoot,sName ,page);
			RCmd.LotAutoCount	=SelectLot->SelectedLotAutoCount;
			RCmd.LotID			=SelectLot->SelectedLotID;
			RCmd.LotName		=SelectLot->SelectedLotName;
			RCmd.Send(NULL,page,0);
		}
		GetLayersBase()->GetResultDLLBase()->OutputInLotChangedCommon();
		GetLayersBase()->ClearCurrentStrategicNumberForCalc();
	}
}
void	ButtonSelectLot::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdSelectLot	*CmdSelectLotVar=dynamic_cast<CmdSelectLot *>(packet);
	if(CmdSelectLotVar!=NULL){
		SlotClicked (true);
	}
}



GUICmdSelectLot::GUICmdSelectLot(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSelectLot::Load(QIODevice *f)
{
	if(::Load(f,LotAutoCount)==false)
		return false;
	if(::Load(f,LotID)==false)
		return false;
	if(::Load(f,LotName)==false)
		return false;
	return true;
}
bool	GUICmdSelectLot::Save(QIODevice *f)
{
	if(::Save(f,LotAutoCount)==false)
		return false;
	if(::Save(f,LotID)==false)
		return false;
	if(::Save(f,LotName)==false)
		return false;
	return true;
}
void	GUICmdSelectLot::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(GetLayersBase()->GetEntryPoint()->IsMasterPC()==false){
		GetLayersBase()->GetLot(0)->SetLotAutoCount	(LotAutoCount);
		GetLayersBase()->GetLot(0)->SetLotID			(LotID);
		GetLayersBase()->GetLot(0)->SetLotName		(LotName);
	}
}

