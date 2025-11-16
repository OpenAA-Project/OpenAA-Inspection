/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonSaveMasterData\ButtonSaveMasterData.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ButtonSaveMasterData.h"
#include "XGeneralDialog.h"
#include "SaveMasterDataWindow.h"
#include "ButtonSaveMasterDataResource.h"
#include "XGeneralFunc.h"
#include "XMacroFunction.h"
#include <QMessageBox>

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"SaveMasterData";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show the window to save master data");
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
	return(new ButtonSaveMasterData(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<6)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((ButtonSaveMasterData *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonSaveMasterData *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonSaveMasterData *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonSaveMasterData *)Instance)->CFont;
	Data[4].Type				 =/**/"bool";
	Data[4].VariableNameWithRoute=/**/"ModeCheckDupName";
	Data[4].Pointer				 =&((ButtonSaveMasterData *)Instance)->ModeCheckDupName;
	Data[5].Type				 =/**/"bool";
	Data[5].VariableNameWithRoute=/**/"ExecuteInitialAfterSaving";
	Data[5].Pointer				 =&((ButtonSaveMasterData *)Instance)->ExecuteInitialAfterSaving;

	return(6);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonSaveNewMasterData.png")));
}

static	bool	MacroSaveMaster(GUIFormBase *Instance ,QStringList &Args)
{
	ButtonSaveMasterData	*V=dynamic_cast<ButtonSaveMasterData *>(Instance);
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

	return V->CommandSaveMaster(tMasterName,tRemark,SilentMode);
}
static	bool	MacroSearchMasterIDByName(GUIFormBase *Instance ,QStringList &Args)
{
	ButtonSaveMasterData	*V=dynamic_cast<ButtonSaveMasterData *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<1){
		return false;
	}
	QString	tMasterName	=Args[0];
	int	MasterID=V->CommandSearchMaster(tMasterName);
	Args.append(QString::number(MasterID));

	return true;
}

static	bool	MacroOpenSaveDialog(GUIFormBase *Instance ,QStringList &Args)
{
	ButtonSaveMasterData	*V=dynamic_cast<ButtonSaveMasterData *>(Instance);
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
		Functions[ret].FuncName	=/**/"SaveMaster";
		Functions[ret].Explain.append(/**/"Save master data");
		Functions[ret].ArgName.append(/**/"Master name without duplication");
		Functions[ret].ArgName.append(/**/"Remark");
		Functions[ret].ArgName.append(/**/"Silent mode TRUE/false (Optional)");
		Functions[ret].DLL_ExcuteMacro	=MacroSaveMaster;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"SearchMasterIDByName";
		Functions[ret].Explain.append(/**/"Search MasterID by MasterName");
		Functions[ret].ArgName.append(/**/"Master name");
		Functions[ret].ArgName.append(/**/"Return value of MasterID");
		Functions[ret].DLL_ExcuteMacro	=MacroSearchMasterIDByName;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"OpenSaveDialog";
		Functions[ret].Explain.append(/**/"Open dialog to save master data");
		Functions[ret].DLL_ExcuteMacro	=MacroOpenSaveDialog;
		ret++;
	}

	return ret;
}
//==================================================================================================
ButtonSaveMasterData::ButtonSaveMasterData(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.setObjectName(/**/"ButtonSaveMasterDataBtn");
	Button.move(0,0);
	Msg=/**/"Save MasterData";
	ModeCheckDupName	=true;
	ExecuteInitialAfterSaving	=false;

	resize(60,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonSaveMasterData::~ButtonSaveMasterData(void)
{
}

void	ButtonSaveMasterData::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
	if(GetLayersBase()->GetInsideLearningEditor()==true){
		Button.setEnabled(false);
	}
}

void	ButtonSaveMasterData::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonSaveMasterData::SlotClicked (bool checked)
{
	if(GetLayersBase()->GetShadowLevel()>0){
		return;
	}
	SaveMasterDataWindow	*Cli=new SaveMasterDataWindow(GetLayersBase(),QString(sRoot),QString(sName),this);
	GeneralDialog	D(GetLayersBase(),Cli,this);
	D.exec();
	BroadcastDirectly(GUIFormBase::_BC_BuildForShow ,GetLayersBase()->GetCurrentInspectIDForDisplay());

	if(ExecuteInitialAfterSaving==true){
		GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Button",/**/"CalcFinalization",/**/"");
		if(f!=NULL){
			QStringList Args;
			bool ExeReturn;
			f->ExecuteMacro(/**/"Execute", Args, ExeReturn);
		}
	}
}
bool	ButtonSaveMasterData::CommandSaveMaster(QString &tMasterName,QString &tRemark ,bool SilentMode)
{
	SaveMasterDataWindow	*Cli=new SaveMasterDataWindow(GetLayersBase(),QString(sRoot),QString(sName),this);
	bool	Ret;
	ErrorMessageOfFalse.clear();
	if(SilentMode==false){
		Ret=Cli->ExecuteSave(tMasterName,tRemark);
	}
	else{
		Ret=Cli->ExecuteSaveSilent(tMasterName,tRemark,ErrorMessageOfFalse);
	}
	delete	Cli;
	BroadcastDirectly(GUIFormBase::_BC_BuildForShow ,GetLayersBase()->GetCurrentInspectIDForDisplay());

	if(ExecuteInitialAfterSaving==true){
		GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Button",/**/"CalcFinalization",/**/"");
		if(f!=NULL){
			QStringList Args;
			bool ExeReturn;
			f->ExecuteMacro(/**/"Execute", Args, ExeReturn);
		}
	}
	return Ret;
}
int		ButtonSaveMasterData::CommandSearchMaster	(QString &tMasterName)
{
	SaveMasterDataWindow	*Cli=new SaveMasterDataWindow(GetLayersBase(),QString(sRoot),QString(sName),this);
	int	MasterID=Cli->ExecuteSearch(tMasterName);
	delete	Cli;
	return MasterID;
}
void	ButtonSaveMasterData::GetMenuInfo(MenuInfoContainer &Info)
{
	MenuInfoList	*p=new MenuInfoList(1,LangSolver.GetString(ButtonSaveMasterData_LS,LID_7)/*"FILE"*/
										,LangSolver.GetString(ButtonSaveMasterData_LS,LID_8)/*"Save MasterData"*/
										,this);
	p->SetMenuNumber(1010);
	Info.AppendList(p);
}
void	ButtonSaveMasterData::ExecuteMenu(int ID)
{
	if(ID==1){
		SlotClicked(true);
	}
}
void	ButtonSaveMasterData::RxSync(QByteArray &f)
{
	QBuffer	Buff(&f);
	Buff.open(QIODevice::ReadWrite);
	int	RelationCode;
	QString	iMasterName;
	QString	iRemark;
	int	SelectedCategoryID;

	::Load(&Buff,RelationCode);
	::Load(&Buff,iMasterName);
	::Load(&Buff,iRemark);
	::Load(&Buff,SelectedCategoryID);
	QString	ImagePath;
	::Load(&Buff,ImagePath);


	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(ButtonSaveMasterData_LS,LID_0)/*"Saving master data in received Sync"*/);

	CreateNewMasterPreSpecifiedBroadcaster	SData1;
	BroadcastSpecifiedDirectly(&SData1);

	GetLayersBase()->SetEdited(true);
	QString ErrorMessageOfFalse;
	if(GetLayersBase()->SQLSaveNewMasterData(iMasterName
										 ,iRemark 
										 ,SelectedCategoryID
										 ,ImagePath
										,ErrorMessageOfFalse)==false){
		QMessageBox::critical(NULL,"Save Error",ErrorMessageOfFalse);
	}
	
	GetLayersBase()->WaitAllAcknowledged(60*10);

	GetLayersBase()->SQLSetRelationOnMasterData(GetLayersBase()->GetMasterCode()
												,RelationCode ,GetLayersBase()->GetMachineID());
	GetLayersBase()->SetEdited(false);
	BroadcastDirectly(_BC_BuildForShow,GetLayersBase()->GetCurrentInspectIDForDisplay());

	CreateNewMasterSpecifiedBroadcaster	SData2;
	BroadcastSpecifiedDirectly(&SData2);

	GetLayersBase()->CloseProcessingForm();

	if(ExecuteInitialAfterSaving==true){
		GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Button",/**/"CalcFinalization",/**/"");
		if(f!=NULL){
			QStringList Args;
			bool ExeReturn;
			f->ExecuteMacro(/**/"Execute", Args, ExeReturn);
		}
	}
}