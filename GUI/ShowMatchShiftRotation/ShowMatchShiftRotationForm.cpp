#include "ShowMatchShiftRotationForm.h"
#include "ui_ShowMatchShiftRotationForm.h"
#include "XDataInLayer.h"
#include "XGeneralFunc.h"
#include "ThreadSequence.h"
#include "XSequenceLocal.h"
#include "XMatchShiftRotation.h"
#include "XEntryPoint.h"

extern	const	char	*sRoot;
extern	const	char	*sName;


ShowMatchShiftRotationForm::ShowMatchShiftRotationForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::ShowMatchShiftRotationForm)
{
    ui->setupUi(this);

	iAngle	=NULL;
	iShiftX	=NULL;
	iShiftY	=NULL;
	iDone	=NULL;

	RegNo_Angle	=376;
	RegNo_ShiftX=377;
	RegNo_ShiftY=378;
	RegNo_Done	=376;
}

ShowMatchShiftRotationForm::~ShowMatchShiftRotationForm()
{
    delete ui;
}

void	ShowMatchShiftRotationForm::Prepare(void)
{
	if(GetLayersBase()->GetInsideLearningEditor()==false 
	&& GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL
	&& GetLayersBase()->GetShadowLevel()==0){
		SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
		if(Param!=NULL){
			if(RegNo_Angle>0)
				iAngle	=new SignalOperandFloat	(this,RegNo_Angle	,/**/"ShowMatchShiftRotationForm:iAngle");
			if(RegNo_ShiftX>0)
				iShiftX	=new SignalOperandInt	(this,RegNo_ShiftX	,/**/"ShowMatchShiftRotationForm:iShiftX");
			if(RegNo_ShiftY>0)
				iShiftY	=new SignalOperandInt	(this,RegNo_ShiftY	,/**/"ShowMatchShiftRotationForm:iShiftY");
			if(RegNo_Done>0)
				iDone	=new SignalOperandBit	(this,RegNo_Done		,/**/"ShowMatchShiftRotationForm:iDone");

			SeqErrorInfo	Error;
			if(Param->SetSpecialOperand(iAngle	,&Error)==false){
				iAngle->ShowErrorMessage(Error);
			}
			if(Param->SetSpecialOperand(iShiftX	,&Error)==false){
				iShiftX->ShowErrorMessage(Error);
			}
			if(Param->SetSpecialOperand(iShiftY	,&Error)==false){
				iShiftY->ShowErrorMessage(Error);
			}
			if(Param->SetSpecialOperand(iDone	,&Error)==false){
				iDone->ShowErrorMessage(Error);
			}
		}
	}
}

void	ShowMatchShiftRotationForm::ShowInPlayer(int64 shownInspectionID)
{
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqRotation		CmdReq(GetLayersBase(),sRoot,sName,GlobalPage);
		CmdReq.AreaID=-1;
		GUICmdSendRotation	CmdAck(GetLayersBase(),sRoot,sName,GlobalPage);
		if(CmdReq.Send(GlobalPage ,0,CmdAck)==true){
			if(CmdAck.Found==true){
				CurrentAngle	=CmdAck.Angle;
				CurrentShiftX	=CmdAck.ShiftX;
				CurrentShiftY	=CmdAck.ShiftY;
				CurrnetDone		=true;

				ui->lineEditAngle	->setText(QString::number(CmdAck.Angle,'f',3));
				if(iAngle!=NULL)
					iAngle->Set(CmdAck.Angle);
				ui->lineEditShift	->setText(QString::number(CmdAck.ShiftX)
											+ QString(/**/",")
											+ QString::number(CmdAck.ShiftY));
				if(iShiftX!=NULL)
					iShiftX->Set(CmdAck.ShiftX);
				if(iShiftY!=NULL)
					iShiftY->Set(CmdAck.ShiftY);
				if(iDone!=NULL)
					iDone->Set(true);
				break;
			}
		}
	}

}
void	ShowMatchShiftRotationForm::TransmitDirectly(GUIDirectMessage *packet)
{
	ReqShiftRotaionResult	*ReqShiftRotaionResultVar=dynamic_cast<ReqShiftRotaionResult *>(packet);
	if(ReqShiftRotaionResultVar!=NULL){
		ReqShiftRotaionResultVar->Angle	=CurrentAngle	;
		ReqShiftRotaionResultVar->ShiftX=CurrentShiftX	;
		ReqShiftRotaionResultVar->ShiftY=CurrentShiftY	;
		ReqShiftRotaionResultVar->Found	=CurrnetDone	;
		CurrnetDone=false;
		return;
	}
}

//=====================================================================================================

GUICmdReqRotation::GUICmdReqRotation(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	AreaID=-1;
}

bool	GUICmdReqRotation::Load(QIODevice *f)
{
	if(::Load(f,AreaID)==false)
		return false;
	return true;
}
bool	GUICmdReqRotation::Save(QIODevice *f)
{
	if(::Save(f,AreaID)==false)
		return false;
	return true;
}

void	GUICmdReqRotation::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendRotation	*SendBack=GetSendBack(GUICmdSendRotation,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	AlgorithmBase	*AlignBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"MatchShiftRotation");
	if(AlignBase==NULL)
		return;
	AlgorithmInPagePI	*PData=dynamic_cast<AlgorithmInPagePI	*>(AlignBase->GetPageData(localPage));
	if(PData!=NULL){
		ReqShiftRotaionResult	RCmd(GetLayersBase());
		RCmd.AreaID			=AreaID	;
		PData->TransmitDirectly(&RCmd);

		SendBack->Angle	=RCmd.Angle;
		SendBack->ShiftX	=RCmd.ShiftX;
		SendBack->ShiftY	=RCmd.ShiftY;
		SendBack->Found		=RCmd.Found;
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}
	
GUICmdSendRotation::GUICmdSendRotation(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Angle	=0;
	ShiftX	=0;
	ShiftY	=0;
	Found	=false;
}
bool	GUICmdSendRotation::Load(QIODevice *f)
{
	if(::Load(f,Angle)==false)
		return false;
	if(::Load(f,ShiftX)==false)
		return false;
	if(::Load(f,ShiftY)==false)
		return false;
	if(::Load(f,Found)==false)
		return false;
	return true;
}
bool	GUICmdSendRotation::Save(QIODevice *f)
{
	if(::Save(f,Angle)==false)
		return false;
	if(::Save(f,ShiftX)==false)
		return false;
	if(::Save(f,ShiftY)==false)
		return false;
	if(::Save(f,Found)==false)
		return false;
	return true;
}