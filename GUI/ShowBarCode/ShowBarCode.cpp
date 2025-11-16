#include "InputCodeDialogResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ShowBarCode\ShowBarCode.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ShowBarCode.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XGeneralFunc.h"
#include "InputCodeDialog.h"
#include "ThreadSequence.h"
#include "XSequenceLocal.h"
#include "XExecuteInspectBase.h"
#include "XEntryPoint.h"

static	const	char	*sRoot=/**/"Panel";
static	const	char	*sName=/**/"ShowBarCode";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Display Barcode result");
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ShowBarCode(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdReqBarcode	(Base,sRoot,sName);
	(*Base)=new GUICmdAckBarcode	(Base,sRoot,sName);
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
	Data[0].Pointer				 =&((ShowBarCode *)Instance)->MessageSize;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"ColorBarcode";
	Data[1].Pointer				 =&((ShowBarCode *)Instance)->ColorBarcode;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"ColorNoBarcode";
	Data[2].Pointer				 =&((ShowBarCode *)Instance)->ColorNoBarcode;
	Data[3].Type				 =/**/"int32";
	Data[3].VariableNameWithRoute=/**/"SysNoCurrentBarcode";
	Data[3].Pointer				 =&((ShowBarCode *)Instance)->SysNoCurrentBarcode;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ShowBarCode.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
ShowBarCode::ShowBarCode(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent),ManualButton(this)
{
	ColorBarcode	=Qt::green;
	ColorNoBarcode	=Qt::red;
	SysNoCurrentBarcode	=50;

	resize(250,250);

	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
	connect(&ManualButton ,SIGNAL(clicked()),this,SLOT(on_pushButtonManual_clicked()));

	ioCurrentBarcode=NULL;
}

void	ShowBarCode::Prepare(void)
{
	ShowInPlayer(-1);

	if(GetLayersBase()->GetInsideLearningEditor()==false 
	&& GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL
	&& GetLayersBase()->GetShadowLevel()==0){
		SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
		if(Param!=NULL){
			ioCurrentBarcode			=new SignalOperandString(this,SysNoCurrentBarcode,/**/"ShowBarCode:ioCurrentBarcode");
			ioCurrentBarcode			->Set(/**/"");
			SeqErrorInfo	Error;
			if(Param->SetSpecialOperand(ioCurrentBarcode,&Error)==false){
				ioCurrentBarcode->ShowErrorMessage(Error);
			}
		}
	}
	ManualButton.setText(LangSolver.GetString(ShowBarCode_LS,LID_1)/*"Žè“ü—Í"*/);
}

void	ShowBarCode::ResizeAction()
{
	ManualButton.move(width()-40,height()/2-10);
	ManualButton.resize(40,20);
}
void	ShowBarCode::ShowInPlayer(int64 shownInspectionID)
{
	bool	OkBarcode=false;
	ResultBarcode.clear();
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqBarcode		CmdReq(GetLayersBase(),sRoot,sName,GlobalPage);
		GUICmdAckBarcode		CmdAck(GetLayersBase(),sRoot,sName,GlobalPage);
		if(CmdReq.Send(GlobalPage ,0,CmdAck)==true){
			if(CmdAck.ResultBarcode.isEmpty()==false){
				ResultBarcode.append(CmdAck.ResultBarcode);
				if(ioCurrentBarcode!=NULL){
					ioCurrentBarcode->Set(CmdAck.ResultBarcode[0]);
				}
				OkBarcode=true;
			}
		}
	}
	if(OkBarcode==false){
		if(ioCurrentBarcode!=NULL){
			ioCurrentBarcode->Set(/**/"");
		}
	}

	//update();
	repaint();
}

void	ShowBarCode::on_pushButtonManual_clicked(void)
{
	BCRInspectionBase	*ABase=(BCRInspectionBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"BCRInspection");
	if(ABase==NULL)
		return;

	InputCodeDialog	Dlg(this);
	if(Dlg.exec()==(int)true){
		ResultBarcode.clear();
		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
			AlgorithmInPageRoot		*APage=ABase->GetPageData(page);
			if(APage!=NULL){
				CmdSetBCodeResults		D(GetLayersBase());
				D.ResultBarcode.append(Dlg.BarCode);
				APage->TransmitDirectly(&D);
				if(D.OK==true){
					ResultBarcode.append(Dlg.BarCode);
				}
			}
		}
	}
	repaint();
}

void	ShowBarCode::paintEvent ( QPaintEvent * event )
{
	QPainter	pnt(this);

	pnt.setFont(MessageSize);

	int	BarCount=0;
	for(int i=0;i<ResultBarcode.count();i++){
		if(ResultBarcode[i].isEmpty()==false){
			BarCount++;
		}
	}
	QStringList	Msg;
	if(BarCount>0 && BarCount==ResultBarcode.count()){
		QBrush	B(ColorBarcode);
		Msg=ResultBarcode;
		pnt.fillRect(0,0,width(),height(),B);
	}
	else if(BarCount>0 && BarCount!=ResultBarcode.count()){
		QBrush	B(QColor((ColorBarcode.red()	+ColorNoBarcode.red())/2
						,(ColorBarcode.green()	+ColorNoBarcode.green())/2
						,(ColorBarcode.blue()	+ColorNoBarcode.blue())/2));
		Msg=ResultBarcode;
		pnt.fillRect(0,0,width(),height(),B);
	}
	else{
		QBrush	B(ColorNoBarcode);
		Msg.append(LangSolver.GetString(ShowBarCode_LS,LID_0)/*"No barcode"*/);
		pnt.fillRect(0,0,width(),height(),B);
	}

	QBrush	B(Qt::black);
	pnt.setBrush(B);
	int	HCount=Msg.count();
	if(HCount!=0){
		int	HCell=height()/HCount;
		for(int i=0;i<Msg.count();i++){
			pnt.drawText(0,HCell*i,width(),HCell,Qt::AlignHCenter | Qt::AlignVCenter ,Msg[i]);
		}
	}
}

//=====================================================================================
GUICmdReqBarcode::GUICmdReqBarcode(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqBarcode::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckBarcode	*SendBack=GetSendBack(GUICmdAckBarcode,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	BCRInspectionBase	*ABase=(BCRInspectionBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"BCRInspection");
	if(ABase==NULL)
		return;
	AlgorithmInPageRoot		*APage=ABase->GetPageData(localPage);
	if(APage!=NULL){
		CmdReqBCodeResults		D(GetLayersBase());
		APage->TransmitDirectly(&D);
		SendBack->ResultBarcode	=D.ResultBarcode;
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckBarcode::GUICmdAckBarcode(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAckBarcode::Load(QIODevice *f)
{
	if(::Load(f,ResultBarcode)==false)
		return false;
	return true;
}
bool	GUICmdAckBarcode::Save(QIODevice *f)
{
	if(::Save(f,ResultBarcode)==false)
		return false;
	return true;
}


