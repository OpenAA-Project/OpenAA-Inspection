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

#include "CameraBufferResource.h"

#include "CameraBuffer.h"
#include "ThreadSequence.h"
#include "XSequenceLocal.h"
#include "XExecuteInspectBase.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "XGeneralFunc.h"
#include "XGUIDLL.h"
#include "XCameraClass.h"
#include "XEntryPoint.h"

static	const	char	*sRoot=/**/"Camera";
static	const	char	*sName=/**/"Buffer";


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Check camera buffer for sequence");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdReqCameraBuffer	(Base ,sRoot,sName ,-1);
	(*Base)=new GUICmdSendCameraBuffer(Base ,sRoot,sName ,-1);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new CameraBuffer(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<1)
		return(-1);
	Data[0].Type				 =/**/"int32";
	Data[0].VariableNameWithRoute=/**/"SystemRegisterNo";
	Data[0].Pointer				 =&((CameraBuffer *)Instance)->SystemRegisterNo;

	return(1);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ResetCameraSeq.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
CameraBuffer::CameraBuffer(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	SystemRegisterNo=65;
	ioMode			=NULL;
}

CameraBuffer::~CameraBuffer(void)
{
}

void	CameraBuffer::Prepare(void)
{
	if(GetLayersBase()->GetInsideLearningEditor()==false 
	&& GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL
	&& GetLayersBase()->GetShadowLevel()==0){
		SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
		if(Param!=NULL){
			ioMode		=new SignalOperandBit(this,SystemRegisterNo,/**/"CameraBuffer:ioMode");
			connect(ioMode			,SIGNAL(changed())	,this	,SLOT(OperandChanged()));
			SeqErrorInfo	Error;
			if(Param->SetSpecialOperand(ioMode,&Error)==false){
				ioMode->ShowErrorMessage(Error);
			}
			connect(ioMode	,SIGNAL(loaded())	,this	,SLOT(OperandLoaded()));
		}
	}
}

void	CameraBuffer::OperandLoaded()
{
	bool	TotalEmpty=true;
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqCameraBuffer		CmdReq(GetLayersBase(),sRoot,sName,GlobalPage);
		GUICmdSendCameraBuffer		CmdAck(GetLayersBase(),sRoot,sName,GlobalPage);
		if(CmdReq.Send(GlobalPage ,0,CmdAck)==true){
			if(CmdAck.Empty==false){
				TotalEmpty=false;
			}
		}
	}
	if(ioMode!=NULL){
		ioMode->Set(TotalEmpty);
	}
}

GUICmdReqCameraBuffer::GUICmdReqCameraBuffer(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqCameraBuffer::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendCameraBuffer	*SendBack=GetSendBack(GUICmdSendCameraBuffer,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	
	SendBack->Empty=true;
	if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
		CameraClass	*C=GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetCamera(localPage);
		if(C->IsBufferFull()==true)
			SendBack->Empty=false;
		else
			SendBack->Empty=true;
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendCameraBuffer::GUICmdSendCameraBuffer(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendCameraBuffer::Load(QIODevice *f)
{
	if(::Load(f,Empty)==false)
		return false;
	return true;
}

bool	GUICmdSendCameraBuffer::Save(QIODevice *f)
{
	if(::Save(f,Empty)==false)
		return false;
	return true;
}

