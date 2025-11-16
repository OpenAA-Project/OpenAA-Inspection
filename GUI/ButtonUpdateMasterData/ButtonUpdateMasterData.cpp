/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonUpdateMasterData\ButtonUpdateMasterData.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ButtonUpdateMasterDataResource.h"
#include "ButtonUpdateMasterData.h"
#include "XGeneralDialog.h"
#include "UpdateMasterDataWindow.h"
#include "XGeneralFunc.h"
#include "XFileRegistry.h"
#include "XMacroFunction.h"
#include <QMessageBox>

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"UpdateMasterData";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show the window to Update master data");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonUpdateMasterData(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<4)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((ButtonUpdateMasterData *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonUpdateMasterData *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonUpdateMasterData *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonUpdateMasterData *)Instance)->CFont;
	Data[4].Type				 =/**/"bool";
	Data[4].VariableNameWithRoute=/**/"UpdateGeneralSetting";
	Data[4].Pointer				 =&((ButtonUpdateMasterData *)Instance)->UpdateGeneralSetting;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonUpdateMasterData.png")));
}

static	bool	MacroUpdateMaster(GUIFormBase *Instance ,QStringList &Args)
{
	ButtonUpdateMasterData	*V=dynamic_cast<ButtonUpdateMasterData *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<2){
		return false;
	}
	QString	tMasterName	=Args[0];
	QString	tRemark		=Args[1];
	bool	SilentMode=false;
	if(Args.count()>=3){
		if(Args[2].toUpper()==QString("TRUE")){
			SilentMode=true;
		}
	}
	return V->CommandUpdateMaster(tMasterName,tRemark,SilentMode);
}

static	bool	MacroOpenUpdateDialog(GUIFormBase *Instance ,QStringList &Args)
{
	ButtonUpdateMasterData	*V=dynamic_cast<ButtonUpdateMasterData *>(Instance);
	if(V==NULL){
		return false;
	}
	V->SlotClicked(true);

	return true;
}

DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"UpdateMaster";
		Functions[ret].Explain.append(/**/"Update master data");
		Functions[ret].ArgName.append(/**/"Master name without duplication");
		Functions[ret].ArgName.append(/**/"Remark");
		Functions[ret].ArgName.append(/**/"Silent mode TRUE/false (Optional)");
		Functions[ret].DLL_ExcuteMacro	=MacroUpdateMaster;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"OpenUpdateDialog";
		Functions[ret].Explain.append(/**/"Open dialog to update master data");
		Functions[ret].DLL_ExcuteMacro	=MacroOpenUpdateDialog;
		ret++;
	}

	return ret;
}
//==================================================================================================
ButtonUpdateMasterData::ButtonUpdateMasterData(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.setObjectName(/**/"ButtonUpdateMasterDataBtn");
	Button.move(0,0);
	Msg=/**/"Update MasterData";
	resize(60,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
	UpdateGeneralSetting=true;
}

ButtonUpdateMasterData::~ButtonUpdateMasterData(void)
{
}

void	ButtonUpdateMasterData::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
	if(GetLayersBase()->GetInsideLearningEditor()==true){
		Button.setEnabled(false);
	}
}

void	ButtonUpdateMasterData::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonUpdateMasterData::SlotClicked (bool checked)
{
	if(GetLayersBase()->GetShadowLevel()>0){
		return;
	}
	GeneralDialog	D(GetLayersBase(),new UpdateMasterDataWindow(GetLayersBase(),sRoot,sName
																	,UpdateGeneralSetting,this),this);
	D.exec();
	BroadcastDirectly(GUIFormBase::_BC_BuildForShow ,GetLayersBase()->GetCurrentInspectIDForDisplay());
}
bool	ButtonUpdateMasterData::CommandUpdateMaster(QString &tMasterName,QString &tRemark,bool SilentMode)
{
	UpdateMasterDataWindow	*Cli=new UpdateMasterDataWindow(GetLayersBase(),sRoot,sName
															,UpdateGeneralSetting,this);
	bool	Ret;
	ErrorMessageOfFalse.clear();
	if(SilentMode==false){
		Ret=Cli->ExecuteUpdate(tMasterName,tRemark);
	}
	else{
		Ret=Cli->ExecuteUpdateSilent(tMasterName,tRemark,ErrorMessageOfFalse);
	}
	delete	Cli;
	BroadcastDirectly(GUIFormBase::_BC_BuildForShow ,GetLayersBase()->GetCurrentInspectIDForDisplay());
	return Ret;
}
void	ButtonUpdateMasterData::GetMenuInfo(MenuInfoContainer &Info)
{
	MenuInfoList	*p=new MenuInfoList(1,LangSolver.GetString(ButtonUpdateMasterData_LS,LID_9)/*"FILE"*/
										,LangSolver.GetString(ButtonUpdateMasterData_LS,LID_10)/*"Overwrite MasterData"*/
										,this);
	p->SetMenuNumber(1020);
	Info.AppendList(p);
}
void	ButtonUpdateMasterData::ExecuteMenu(int ID)
{
	if(ID==1){
		SlotClicked(true);
	}
}

void	ButtonUpdateMasterData::RxSync(QByteArray &f)
{
	QBuffer	Buff(&f);
	Buff.open(QIODevice::ReadWrite);
	int	RelationCode;
	QString	iMasterName;
	QString	iRemark;
	//int	SelectedCategoryID;

	::Load(&Buff,RelationCode);
	::Load(&Buff,iMasterName);
	::Load(&Buff,iRemark);
	QString	ImagePath;
	::Load(&Buff,ImagePath);

	GetLayersBase()->SetMasterName(iMasterName);
	GetLayersBase()->SetRemark(iRemark);

	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(ButtonUpdateMasterData_LS,LID_0)/*"Update master data in received Sync"*/);

	bool	EditMaltipleMachine=GetLayersBase()->GetFRegistry()->LoadRegBool(/**/"EditMaltipleMachine",0);
	int	SelectedMachineID=GetLayersBase()->GetMachineID();
	if(EditMaltipleMachine==true){
		SelectedMachineID=GetLayersBase()->GetMachineIDFromMaster();
	}

	CreateUpdateMasterPreSpecifiedBroadcaster	SData1;
	BroadcastSpecifiedDirectly(&SData1);
	QString ErrorMessageOfFalse;
	if(GetLayersBase()->GetMasterCode()>=0){
		if(GetLayersBase()->SQLUpdateMasterData(SelectedMachineID,ImagePath,false,ErrorMessageOfFalse)==false){
			QMessageBox::critical(NULL,"Update Error",ErrorMessageOfFalse);
		}
		GetLayersBase()->WaitAllAcknowledged(60*10);
	}
	
	GetLayersBase()->CloseProcessingForm();

	if(GetLayersBase()->GetMasterCode()>=0 && RelationCode>=0){
		GetLayersBase()->SQLSetRelationOnMasterData(GetLayersBase()->GetMasterCode()
												,RelationCode ,GetLayersBase()->GetMachineID());
	}
				
	CreateUpdateMasterSpecifiedBroadcaster	SData2;
	BroadcastSpecifiedDirectly(&SData2);

}