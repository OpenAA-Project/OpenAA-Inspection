#include "PanelOkNgResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PanelOkNg\PanelOkNg.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "PanelOkNg.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XGeneralFunc.h"
#include "ThreadSequence.h"
#include "XExecuteInspectBase.h"
#include "XEntryPoint.h"

static	const	char	*sRoot=/**/"Panel";
static	const	char	*sName=/**/"PanelOkNg";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Display panel for OK/NG");
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new PanelOkNg(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdReqOkNG	(Base,sRoot,sName);
	(*Base)=new GUICmdSendOkNG(Base,sRoot,sName);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<6)
		return(-1);
	Data[0].Type				 =/**/"QFont";
	Data[0].VariableNameWithRoute=/**/"MessageSize";
	Data[0].Pointer				 =&((PanelOkNg *)Instance)->MessageSize;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"ColorOK";
	Data[1].Pointer				 =&((PanelOkNg *)Instance)->ColorOK;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"ColorNG";
	Data[2].Pointer				 =&((PanelOkNg *)Instance)->ColorNG;
	Data[3].Type				 =/**/"QString";
	Data[3].VariableNameWithRoute=/**/"MsgOK";
	Data[3].Pointer				 =&((PanelOkNg *)Instance)->MsgOK;
	Data[3].Translatable		 =true;
	Data[4].Type				 =/**/"QString";
	Data[4].VariableNameWithRoute=/**/"MsgNG";
	Data[4].Pointer				 =&((PanelOkNg *)Instance)->MsgNG;
	Data[4].Translatable		 =true;
	Data[5].Type				 =/**/"QColor";
	Data[5].VariableNameWithRoute=/**/"ColorHalt";
	Data[5].Pointer				 =&((PanelOkNg *)Instance)->ColorHalt;

	return(6);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/PanelOkNg.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
PanelOkNg::PanelOkNg(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	ColorOK	=Qt::green;
	ColorNG	=Qt::red;
	ColorHalt=Qt::yellow;
	MsgOK=/**/"OK";
	MsgNG=/**/"NG";
	resize(250,250);

	CriticalError	=ResultInspection::_NoError;
	ResultOk		=none3;
	ResultTimeOut	=false;
	ResultMaxError	=false;
	iLostResult		=NULL;
}

void	PanelOkNg::Prepare(void)
{
	ShowInPlayer(-1);
	ResultOk		=none3;

	if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL
	&& GetLayersBase()->GetShadowLevel()==0){
		SeqLocalParam	*Param=(SeqLocalParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
		if(Param!=NULL){
			iLostResult		=new SignalOperandBit(this,31,/**/"PanelOkNg:iLostResult");
			SeqErrorInfo	Error;
			if(Param->SetSpecialOperand(iLostResult,&Error)==false){
				iLostResult->ShowErrorMessage(Error);
			}
			iLostResult			->Set(false);
		}
	}
}

void	PanelOkNg::ShowInEdit	(void)
{
	//ShowInPlayer(GetLayersBase()->GetCurrentInspectIDForDisplay());
}

void	PanelOkNg::ShowInPlayer(int64 shownInspectionID)
{
	CurrentInspectionID	=shownInspectionID;
	ResultOk		=true3;
	ResultTimeOut	=false;
	ResultMaxError	=false;
	LayersBase	*LBase	=GetLayersBase();
	CriticalError	=ResultInspection::_NoError;
	if(shownInspectionID>=0 && GetParamComm()->Mastered==true){
		for(int page=0;page<LBase->GetPageNumb();page++){
			int	GlobalPage=LBase->GetGlobalPageFromLocal(page);
			GUICmdReqOkNG		CmdReq(LBase,sRoot,sName,GlobalPage);
			CmdReq.ShownInspectionID=CurrentInspectionID;
			//LBase->GetCurrentPhaseFromScanPhase(CmdReq.PhaseCodes);
			ParamGlobal	*ParamG	=GetParamGlobal();
			if(ParamG->ModePhaseOutputResult==-2 || ParamG->ModePhaseOutputResult==-3){
				for(int phase=0;phase<GetPhaseNumb();phase++){
					CmdReq.PhaseCodes.Add(phase);
				}
			}
			else
			if(ParamG->ModePhaseOutputResult==-1){
				int	phase=GetLayersBase()->GetCurrentPhase();
				CmdReq.PhaseCodes.Add(phase);
			}
			else
			if(ParamG->ModePhaseOutputResult>=0){
				int	phase=ParamG->ModePhaseOutputResult;
				CmdReq.PhaseCodes.Add(phase);
			}

			GUICmdSendOkNG		CmdAck(LBase,sRoot,sName,GlobalPage);
			if(CmdReq.Send(GlobalPage ,0,CmdAck)==true){
				if(CmdAck.CriticalError!=ResultInspection::_NoError){
					CriticalError	=CmdAck.CriticalError;
				}
				if(CmdAck.ResultTimeOut==true){
					ResultOk=false3;
					ResultTimeOut=true;
				}
				if(CmdAck.ResultMaxError==true){
					ResultOk=false3;
					ResultMaxError=true;
				}
				if(ResultTimeOut==false && ResultMaxError==false){
					if(CmdAck.ResultOk==false){
						ResultOk=false3;
					}
				}
			}
		}
		int	ErrorCount=LBase->GetErrorCount();
		for(int i=0;i<ErrorCount;i++){
			ErrorCodeList Ret;
			LBase->GetError(i,Ret);
			if(Ret.GetLevel()==ErrorCodeList::_Critical){
				if(Ret.GetErrorCode()==Error_ResultServer){
					CriticalError	=ResultInspection::_ErrorCantWrite;
					break;
				}
			}
		}
	}
	else{
		ResultOk=none3;
	}
	//update();
	repaint();
}
void	PanelOkNg::paintEvent ( QPaintEvent * event )
{
	QPainter	pnt(this);

	pnt.setFont(MessageSize);

	QString	Msg;
	if(CriticalError==ResultInspection::_ErrorOverflowBuffer){
		QBrush	B(Qt::magenta);
		Msg=LangSolver.GetString(PanelOkNg_LS,LID_0)/*"Overflow"*/;
		pnt.fillRect(0,0,width(),height(),B);
	}
	else if(CriticalError==ResultInspection::_ErrorOverrun){
		QBrush	B(Qt::magenta);
		Msg=LangSolver.GetString(PanelOkNg_LS,LID_1)/*"OverRun"*/;
		pnt.fillRect(0,0,width(),height(),B);
	}
	else if(CriticalError==ResultInspection::_ErrorCantWrite){
		QBrush	B(Qt::magenta);
		Msg=LangSolver.GetString(PanelOkNg_LS,LID_2)/*"Lost Result"*/;
		pnt.fillRect(0,0,width(),height(),B);
		iLostResult->Set(true);
	}
	else if(ResultOk==true3){
		QBrush	B(ColorOK);
		Msg=MsgOK;
		pnt.fillRect(0,0,width(),height(),B);
	}
	else if(ResultOk==none3){
		QBrush	B(Qt::gray);
		Msg=/**/"--";
		pnt.fillRect(0,0,width(),height(),B);
	}
	else{
		if(ResultTimeOut==false && ResultMaxError==false){
			QBrush	B(ColorNG);
			Msg=MsgNG;
			pnt.fillRect(0,0,width(),height(),B);
		}
		if(ResultTimeOut==true && ResultMaxError==false){
			QBrush	B(ColorHalt);
			Msg=LangSolver.GetString(PanelOkNg_LS,LID_3)/*"Time out"*/;
			pnt.fillRect(0,0,width(),height(),B);
		}
		if(ResultTimeOut==false && ResultMaxError==true){
			QBrush	B(ColorHalt);
			Msg=LangSolver.GetString(PanelOkNg_LS,LID_4)/*"Max Error"*/;
			pnt.fillRect(0,0,width(),height(),B);
		}
		if(ResultTimeOut==true && ResultMaxError==true){
			QBrush	B(ColorHalt);
			Msg=LangSolver.GetString(PanelOkNg_LS,LID_5)/*"Halt"*/;
			pnt.fillRect(0,0,width(),height(),B);
		}
	}

	QBrush	B(Qt::black);
	pnt.setBrush(B);
	int	H=height();
	int	Row=1;
	if(Message1.isEmpty()==false)
		Row++;
	if(Message2.isEmpty()==false)
		Row++;
	H/=Row;

	int	Y=0;
	if(Message1.isEmpty()==false){
		if(ResultOk==true3){
			QBrush	B(ColorOK);
			Msg=MsgOK;
			pnt.fillRect(0,0,width(),height(),B);
			pnt.drawText(0,0,width(),H,Qt::AlignHCenter | Qt::AlignVCenter ,LangSolver.GetString(PanelOkNg_LS,LID_6)/*"OK"*/+Msg);
		}
		else if(ResultOk==false3){
			QBrush	B(ColorNG);
			Msg=/**/"--";
			pnt.fillRect(0,0,width(),height(),B);
			pnt.drawText(0,0,width(),H,Qt::AlignHCenter | Qt::AlignVCenter ,LangSolver.GetString(PanelOkNg_LS,LID_7)/*"NG"*/+Msg);
		}
		else if(ResultOk==none3){
			QBrush	B(Qt::gray);
			Msg=/**/"--";
			pnt.fillRect(0,0,width(),height(),B);
			pnt.drawText(0,0,width(),H,Qt::AlignHCenter | Qt::AlignVCenter ,LangSolver.GetString(PanelOkNg_LS,LID_8)/*"NG"*/+Msg);
		}
		Y=H;
		pnt.drawText(0,Y,width(),H,Qt::AlignHCenter | Qt::AlignVCenter ,Message1);
		Y+=H;
	}
	else{
		pnt.drawText(0,0,width(),H,Qt::AlignHCenter | Qt::AlignVCenter ,Msg);
	}
	if(Message2.isEmpty()==false){
		pnt.drawText(0,Y,width(),H,Qt::AlignHCenter | Qt::AlignVCenter ,Message2);
		Y+=H;
	}
}

void	PanelOkNg::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdSpecialOkNgMessagePacket	*CmdSpecialOkNgMessagePacketVar=dynamic_cast<CmdSpecialOkNgMessagePacket *>(packet);
	if(CmdSpecialOkNgMessagePacketVar!=NULL){
		MsgOK=CmdSpecialOkNgMessagePacketVar->Message;
		MsgNG=CmdSpecialOkNgMessagePacketVar->Message;
		Message1=CmdSpecialOkNgMessagePacketVar->Message1;
		Message2=CmdSpecialOkNgMessagePacketVar->Message2;
		repaint();
		return;
	}
	CmdSendOkNG	*CmdSendOkNGVar=dynamic_cast<CmdSendOkNG *>(packet);
	if(CmdSendOkNGVar!=NULL){
		if(CmdSendOkNGVar->ResultOk==true)
			ResultOk		=true3;
		else
			ResultOk		=false3;
		ResultTimeOut	=CmdSendOkNGVar->ResultTimeOut;
		ResultMaxError	=CmdSendOkNGVar->ResultMaxError;
		CriticalError	=CmdSendOkNGVar->CriticalError;
		repaint();
		return;
	}

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
	if(PhaseCodes.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdReqOkNG::Save(QIODevice *f)
{
	if(::Save(f,ShownInspectionID)==false)
		return false;
	if(PhaseCodes.Save(f)==false)
		return false;
	return true;
}

void	GUICmdReqOkNG::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendOkNG	*SendBack=GetSendBack(GUICmdSendOkNG,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	ResultInspection	*R=GetLayersBase()->GetBufferedResult(ShownInspectionID);
	if(R!=NULL){
		bool	ResultOk1;
		R->GetResultInPhases(PhaseCodes,ResultOk1);
		bool	ResultOk2=R->IsResultOK();

		SendBack->CriticalError	=R->GetCriticalError();
		SendBack->ResultOk		=(ResultOk1==true && ResultOk2==true)?true:false;
		SendBack->ResultTimeOut	=R->IsResultTimeOut();
		SendBack->ResultMaxError=R->IsResultMaxError();
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendOkNG::GUICmdSendOkNG(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	CriticalError	=ResultInspection::_NoError;
	ResultOk		=true;
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

