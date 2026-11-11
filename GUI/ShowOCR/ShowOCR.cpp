/*
 * Copyright (C) 2026
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



#include "ShowOCR.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XGeneralFunc.h"

static	const	char	*sRoot=/**/"Panel";
static	const	char	*sName=/**/"ShowOCR";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Display OCR result");
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ShowOCR(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdReqOCRResult	(Base,sRoot,sName);
	(*Base)=new GUICmdAckOCRResult	(Base,sRoot,sName);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<4)
		return(-1);
	Data[0].Type				 =/**/"QFont";
	Data[0].VariableNameWithRoute=/**/"MessageSize";
	Data[0].Pointer				 =&((ShowOCR *)Instance)->MessageSize;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"ColorOCR";
	Data[1].Pointer				 =&((ShowOCR *)Instance)->ColorOCR;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"ColorNoOCR";
	Data[2].Pointer				 =&((ShowOCR *)Instance)->ColorNoOCR;
	Data[3].Type				 =/**/"int32";
	Data[3].VariableNameWithRoute=/**/"Phase";
	Data[3].Pointer				 =&((ShowOCR *)Instance)->Phase;
	Data[4].Type				 =/**/"int32";
	Data[4].VariableNameWithRoute=/**/"Page";
	Data[4].Pointer				 =&((ShowOCR *)Instance)->Page;
	Data[5].Type				 =/**/"QString";
	Data[5].VariableNameWithRoute=/**/"ItemName";
	Data[5].Pointer				 =&((ShowOCR *)Instance)->ItemName;

	return(6);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ShowOCR.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
ShowOCR::ShowOCR(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
,OCRTextEdit(this)
{
	ColorOCR		=Qt::green;
	ColorNoOCR		=Qt::red;
	Phase			=0;
	Page			=0;
	OkOCR			= false;

	resize(250,250);
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

void	ShowOCR::Prepare(void)
{
	ShowInPlayer(-1);
}

void	ShowOCR::ResizeAction()
{
	OCRTextEdit.move(0,0);
	OCRTextEdit.resize(width(),height());
}
void	ShowOCR::ShowInPlayer(int64 shownInspectionID)
{
	bool	OkBarcode=false;
	ResultOCR.clear();

	int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(Page);
	GUICmdReqOCRResult		CmdReq(GetLayersBase(),sRoot,sName,GlobalPage);
	GUICmdAckOCRResult		CmdAck(GetLayersBase(),sRoot,sName,GlobalPage);
	CmdReq.Phase = Phase;
	CmdReq.ItemName = ItemName;
	if(CmdReq.Send(GlobalPage ,0,CmdAck)==true){
		if(CmdAck.ResultOCR.isEmpty()==false){
			ResultOCR=CmdAck.ResultOCR;
			OkOCR	=true;
			OCRTextEdit.document()->setPlainText(ResultOCR);
			OCRTextEdit.setTextColor(ColorOCR);
		}
		else{
			OCRTextEdit.document()->setPlainText(/**/"No OCR result");
			OCRTextEdit.setTextColor(ColorNoOCR);
		}
	}
}

//=====================================================================================
GUICmdReqOCRResult::GUICmdReqOCRResult(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqOCRResult::Load(QIODevice *f)
{
	if(::Load(f,ItemName)==false)
		return false;
	if(::Load(f,Phase)==false)
		return false;
	return true;
}
bool	GUICmdReqOCRResult::Save(QIODevice *f)
{
	if(::Save(f,ItemName)==false)
		return false;
	if(::Save(f,Phase)==false)
		return false;
	return true;
}

void	GUICmdReqOCRResult::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckOCRResult	*SendBack=GetSendBack(GUICmdAckOCRResult,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	OCRInspectionBase	*ABase=(OCRInspectionBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"OCRInspection");
	if(ABase!=NULL){
		AlgorithmInPageInOnePhase *Ah = ABase->GetPageDataPhase(Phase);
		if(Ah!=NULL){
			AlgorithmInPageRoot		*APage=ABase->GetPageData(localPage);
			if(APage!=NULL){
				CmdReqOCRResults		D(GetLayersBase());
				APage->TransmitDirectly(&D);
				SendBack->ResultOCR	=D.ResultOCR;
			}
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckOCRResult::GUICmdAckOCRResult(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAckOCRResult::Load(QIODevice *f)
{
	if(::Load(f,ResultOCR)==false)
		return false;
	return true;
}
bool	GUICmdAckOCRResult::Save(QIODevice *f)
{
	if(::Save(f,ResultOCR)==false)
		return false;
	return true;
}

