/*
 * Copyright (C) 2025
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

//#include "EasyLevelAllocationResource.h"
#include "EasyShowNGMessageForDataValidation.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "XGeneralFunc.h"
#include "XGUIDLL.h"
#include "XCheckDataValidation.h"
#include "ShowNGMessageForm.h"
#include "XParamIntegrationMaster.h"

//extern	LangSolverNew	LangCGSolver;

const	char	*sRoot=/**/"KidaPrint";
const	char	*sName=/**/"EasyShowNGMessageForDataValidation";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show NG message for DataValidation");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	(*Base)	=new IntegrationCmdShowNGMessage	(Base,sRoot,sName,-1);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new EasyShowNGMessageForDataValidation(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<4)
		return(-1);
	Data[0].Type				 =/**/"bool";
	Data[0].VariableNameWithRoute=/**/"ModeShowNGMessage";
	Data[0].Pointer				 =&((EasyShowNGMessageForDataValidation *)Instance)->ModeShowNGMessage;

	return(1);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/EasyShowNGMessageForDataValidation.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"CheckDataValidation"));
}

//=========================================================================================

EasyShowNGMessageForDataValidation::EasyShowNGMessageForDataValidation(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	resize(60,25);
	ModeShowNGMessage=true;
	NGMessageWindow	=NULL;

	connect(this,SIGNAL(SignalNGMessage(int,int,int,const QString &))
			,this,SLOT(SlotNGMessage(int,int,int,const QString &))
			,Qt::QueuedConnection);
}

EasyShowNGMessageForDataValidation::~EasyShowNGMessageForDataValidation(void)
{
}
CheckDataValidationBase	*EasyShowNGMessageForDataValidation::GetCheckDataValidationBase(void)
{
    return (CheckDataValidationBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"CheckDataValidation");
}
void	EasyShowNGMessageForDataValidation::ReadyParam(void)
{
	CheckDataValidationBase	*ABase=GetCheckDataValidationBase();
	if(ABase!=NULL){
		for(int phase=0;phase<GetPhaseNumb();phase++){
			AlgorithmInPageInOnePhase	*Ah=ABase->GetPageDataPhase(phase);
			for(int page=0;page<GetPageNumb();page++){
				CheckDataValidationInPage	*Ap=dynamic_cast<CheckDataValidationInPage *>(Ah->GetPageData(page));
				connect(Ap,SIGNAL(SignalNGOccurs(int,int)),this,SLOT(SlotShowNGMessage(int,int)),Qt::QueuedConnection);
			}
		}
	}
}

void    EasyShowNGMessageForDataValidation::SlotShowNGMessage(int phase ,int page)
{
	if(ModeShowNGMessage==true){
		CheckDataValidationBase	*ABase=GetCheckDataValidationBase();
		if(ABase!=NULL){
			AlgorithmInPageInOnePhase	*Ah=ABase->GetPageDataPhase(phase);
			if(Ah!=NULL){
				CheckDataValidationInPage	*Ap=dynamic_cast<CheckDataValidationInPage *>(Ah->GetPageData(page));
				if(Ap!=NULL){
					ParamIntegrationMaster	*Param=GetLayersBase()->GetIntegrationBasePointer()->GetParamIntegrationMaster();
					if(Param!=NULL && Param->Mastered==false){
						int	SlaveNo=Param->GetOwnSlaveNo();
						int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
						IntegrationCmdShowNGMessage	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
						RCmd.Phase		=GetLayersBase()->GetCurrentPhase();
						RCmd.NGMessage	=Ap->NGMessage;
						RCmd.SendFromSlaveToMaster(SlaveNo ,GlobalPage);
					}
				}
			}
		}
	}
}

void	EasyShowNGMessageForDataValidation::SetNGMessage(int SlaveNo,int Phase ,int GlobalPage,const QString &NGMessage)
{
	emit	SignalNGMessage(SlaveNo,Phase ,GlobalPage,NGMessage);
}
void	EasyShowNGMessageForDataValidation::SlotNGMessage(int SlaveNo,int Phase ,int GlobalPage,const QString &NGMessage)
{
	if(NGMessageWindow==NULL){
		NGMessageWindow=new ShowNGMessageForm();
	}
	NGMessageWindow->show();
	NGMessageWindow->SetMessage(NGMessage);
	NGMessageWindow->raise();
}

//================================================================================
IntegrationCmdShowNGMessage::IntegrationCmdShowNGMessage(LayersBase *Base 
									,const QString &EmitterRoot,const QString &EmitterName 
									,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}

bool	IntegrationCmdShowNGMessage::Load(QIODevice *f)
{
	if(::Load(f,Phase		)==false)	return false;
	if(::Load(f,NGMessage	)==false)	return false;
	return true;
}
bool	IntegrationCmdShowNGMessage::Save(QIODevice *f)
{
	if(::Save(f,Phase		)==false)	return false;
	if(::Save(f,NGMessage	)==false)	return false;
	return true;
}
void	IntegrationCmdShowNGMessage::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	EasyShowNGMessageForDataValidation	*f=(EasyShowNGMessageForDataValidation	*)(GetLayersBase()->FindByName(sRoot,sName,/**/""));	
	if(f!=NULL){
		EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(slaveNo);
		if(m!=NULL){
			int GlobalPage=cmd;
			f->SetNGMessage(slaveNo,Phase ,GlobalPage,NGMessage);
		}
	}
}