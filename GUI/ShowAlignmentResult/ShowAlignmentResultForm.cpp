#include "ShowAlignmentResultForm.h"
#include "ui_ShowAlignmentResultForm.h"

#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "ThreadSequence.h"
#include "XSequenceLocal.h"
#include "XExecuteInspectBase.h"
#include "XEntryPoint.h"
#include "XAlgorithmBase.h"
#include "XAlgorithmDLL.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

ShowAlignmentResultForm::ShowAlignmentResultForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::ShowAlignmentResultForm)
{
    ui->setupUi(this);

	iRegDx		=NULL;
	iRegDy		=NULL;
	iRegTheta	=NULL;

	RegDxNo		=395;
	RegDyNo		=396;
	RegThetaNo	=397;

	AlignmentPage	=0;
	AlignmentLocalPx=0;
	AlignmentLocalPy=0;

	AllocatedPageNumb=0;
	ResultCmd	=NULL;
	ResultACmd	=NULL;
}

ShowAlignmentResultForm::~ShowAlignmentResultForm()
{
    delete ui;

	if(iRegDx!=NULL)
		delete	iRegDx;
	iRegDx=NULL;

	//if(iRegDy!=NULL)
	//	delete	iRegDy;
	iRegDy=NULL;

	if(iRegTheta!=NULL)
		delete	iRegTheta;
	iRegTheta=NULL;

	for(int page=0;page<AllocatedPageNumb;page++){
		if(ResultCmd!=NULL && ResultCmd[page]!=NULL){
			delete	ResultCmd[page];
			ResultCmd[page]=NULL;
		}

		if(ResultACmd!=NULL && ResultACmd[page]!=NULL){
			delete	ResultACmd[page];
			ResultACmd[page]=NULL;
		}
	}
	if(ResultCmd!=NULL)
		delete	[]ResultCmd;
	ResultCmd=NULL;

	if(ResultACmd!=NULL)
		delete	[]ResultACmd;
	ResultACmd=NULL;

}

void	ShowAlignmentResultForm::Prepare(void)
{
	if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL
	&& GetLayersBase()->GetShadowLevel()==0){
		SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
		if(Param!=NULL){
			iRegDx		=new SignalOperandInt(this,RegDxNo	,/**/"ShowAlignmentResultForm:iRegDx");
			iRegDy		=new SignalOperandInt(this,RegDyNo	,/**/"ShowAlignmentResultForm:iRegDy");
			iRegTheta	=new SignalOperandInt(this,RegThetaNo,/**/"ShowAlignmentResultForm:iRegTheta");

			SeqErrorInfo	Error;
			if(Param->SetSpecialOperand(iRegDx		,&Error)==false){
				iRegDx->ShowErrorMessage(Error);
			}
			if(Param->SetSpecialOperand(iRegDy		,&Error)==false){
				iRegDy->ShowErrorMessage(Error);
			}
			if(Param->SetSpecialOperand(iRegTheta	,&Error)==false){
				iRegTheta->ShowErrorMessage(Error);
			}
		}
	}
	AllocatedPageNumb=GetPageNumb();
	ResultCmd	=new GUICmdReqAlignmentResult*[AllocatedPageNumb];
	ResultACmd	=new GUICmdAckAlignmentResult*[AllocatedPageNumb];
	for(int page=0;page<AllocatedPageNumb;page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		ResultCmd[page]	=new GUICmdReqAlignmentResult(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		ResultACmd[page]=new GUICmdAckAlignmentResult(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
	}
}
void	ShowAlignmentResultForm::BuildForShow(void)
{
	FlexArea	TotalArea;
	PureFlexAreaListContainer	AreaList;
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqAllAlignmentArea	RCmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		GUICmdAckAllAlignmentArea	ACmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		if(RCmd.Send(GlobalPage,0,ACmd)==true){
			XYData	*XY=GetLayersBase()->GetGlobalOutlineOffset(GlobalPage);
			PureFlexAreaList	*A=new PureFlexAreaList();
			*A=ACmd.Area;
			AreaList.AppendList(A);
			ACmd.Area.MoveToNoClip(XY->x,XY->y);
			TotalArea+=ACmd.Area;
		}
		else{
			PureFlexAreaList	*A=new PureFlexAreaList();
			AreaList.AppendList(A);
		}
	}
	int	Cx,Cy;
	TotalArea.GetCenter(Cx,Cy);
	IntList	PageList;
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		XYData	*XY=GetLayersBase()->GetGlobalOutlineOffset(GlobalPage);
		PureFlexAreaList *a=AreaList[GlobalPage];
		int	LocalCx=Cx-XY->x;
		int	LocalCy=Cy-XY->y;
		if(a!=NULL){
			if(a->IsInclude(LocalCx,LocalCy)==true){
				PageList.Add(GlobalPage);
			}
		}
	}
	if(PageList.GetCount()==0){
		int	H=TotalArea.GetHeight();
		int	W=TotalArea.GetWidth();
		int	dH=H/8;
		int	dW=W/8;
		for(int ix=0;ix<8;ix++){
			for(int iy=0;iy<8;iy++){
				Cx=dW*ix+TotalArea.GetMinX();
				Cy=dH*iy+TotalArea.GetMinY();
				for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
					int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
					XYData	*XY=GetLayersBase()->GetGlobalOutlineOffset(GlobalPage);
					PureFlexAreaList *a=AreaList[GlobalPage];
					int	LocalCx=Cx-XY->x;
					int	LocalCy=Cy-XY->y;
					if(a!=NULL){
						if(a->IsInclude(LocalCx,LocalCy)==true){
							PageList.Add(GlobalPage);
						}
					}
				}
				if(PageList.GetCount()!=0)
					goto	Found;
			}
		}
	}
Found:;
	if(PageList.GetCount()==0)
		return;

	double	MinLen=99999999;
	for(IntClass *c=PageList.GetFirst();c!=NULL;c=c->GetNext()){
		int	GlobalPage=c->GetValue();
		XYData	*XY=GetLayersBase()->GetGlobalOutlineOffset(GlobalPage);
		PureFlexAreaList *a=AreaList[GlobalPage];
		int	LocalCx=Cx-XY->x;
		int	LocalCy=Cy-XY->y;
		double	Len=hypot(GetDotPerLine(GlobalPage)/2-LocalCx,GetMaxLines(GlobalPage)/2-LocalCy);
		if(Len<MinLen){
			MinLen=Len;
			AlignmentPage	=GlobalPage;
			AlignmentLocalPx=LocalCx;
			AlignmentLocalPy=LocalCy;
		}
	}
}

void	ShowAlignmentResultForm::ShowInPlayer(int64 shownInspectionID)
{
	int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(AlignmentPage);
	ResultCmd[AlignmentPage]->AlignmentLocalPx	=AlignmentLocalPx;
	ResultCmd[AlignmentPage]->AlignmentLocalPy	=AlignmentLocalPy;
	if(ResultCmd[AlignmentPage]->Send(GlobalPage,0,*ResultACmd[AlignmentPage])==true){
		ui->lineEditResultDx->setText(QString::number(ResultACmd[AlignmentPage]->ResultDx));
		if(iRegDx!=NULL){
			iRegDx->Set(ResultACmd[AlignmentPage]->ResultDx);
		}
		ui->lineEditResultDy->setText(QString::number(ResultACmd[AlignmentPage]->ResultDy));
		if(iRegDy!=NULL){
			iRegDy->Set(ResultACmd[AlignmentPage]->ResultDy);
		}
		ui->lineEditResultAngle->setText(QString::number(ResultACmd[AlignmentPage]->ResultTheta,'f',1));
		if(iRegTheta!=NULL){
			iRegTheta->Set((int)ResultACmd[AlignmentPage]->ResultTheta);
		}
	}
}

//=============================================================================================

GUICmdReqAlignmentResult::GUICmdReqAlignmentResult(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
GUICmdReqAlignmentResult::~GUICmdReqAlignmentResult(void)
{
}

bool	GUICmdReqAlignmentResult::Load(QIODevice *f)
{
	if(::Load(f,AlignmentLocalPx)==false)
		return false;
	if(::Load(f,AlignmentLocalPy)==false)
		return false;
	return true;
}
bool	GUICmdReqAlignmentResult::Save(QIODevice *f)
{
	if(::Save(f,AlignmentLocalPx)==false)
		return false;
	if(::Save(f,AlignmentLocalPy)==false)
		return false;
	return true;
}

void	GUICmdReqAlignmentResult::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckAlignmentResult	*SendBack=GetSendBack(GUICmdAckAlignmentResult,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlignmentPacket2D	P;
	P.PosXOnTarget	=AlignmentLocalPx;
	P.PosYOnTarget	=AlignmentLocalPy;
	GetLayersBase()->GetAlignmentForProcessing(localPage ,P);

	SendBack->ResultDx	=P.ShiftX;
	SendBack->ResultDy	=P.ShiftY;
	//AlignmentPacket2D	Q;
	//Q.PosXOnTarget	=AlignmentLocalPx+100;
	//Q.PosYOnTarget	=AlignmentLocalPy;
	//GetLayersBase()->GetAlignmentForProcessing(localPage ,Q);
	//double	s=((double)(Q.ShiftY-P.ShiftY))/((double)(100+Q.ShiftX-P.ShiftX));
	//SendBack->ResultTheta	=atan(s)*180/M_PI;
	SendBack->ResultTheta	=P.Rotation*180.0/M_PI;

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);

}

GUICmdAckAlignmentResult::GUICmdAckAlignmentResult(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
GUICmdAckAlignmentResult::~GUICmdAckAlignmentResult(void)
{
}

bool	GUICmdAckAlignmentResult::Load(QIODevice *f)
{
	if(::Load(f,ResultDx)==false)
		return false;
	if(::Load(f,ResultDy)==false)
		return false;
	if(::Load(f,ResultTheta)==false)
		return false;
	return true;
}
bool	GUICmdAckAlignmentResult::Save(QIODevice *f)
{
	if(::Save(f,ResultDx)==false)
		return false;
	if(::Save(f,ResultDy)==false)
		return false;
	if(::Save(f,ResultTheta)==false)
		return false;
	return true;
}

//=============================================================================================

GUICmdReqAllAlignmentArea::GUICmdReqAllAlignmentArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
GUICmdReqAllAlignmentArea::~GUICmdReqAllAlignmentArea(void)
{
}

void	GUICmdReqAllAlignmentArea::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckAllAlignmentArea	*SendBack=GetSendBack(GUICmdAckAllAlignmentArea,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	for(LogicDLL	*Algo=GetLayersBase()->GetLogicDLLBase()->SearchByAlgorithmType(AlgorithmBit_TypePreAlignment | AlgorithmBit_TypeAlignment)
	;Algo!=NULL;Algo=GetLayersBase()->GetLogicDLLBase()->NextByAlgorithmType(Algo,AlgorithmBit_TypePreAlignment | AlgorithmBit_TypeAlignment)){
		AlgorithmBase	*ABase=Algo->GetInstance();
		AlgorithmInPageRoot	*Ap=ABase->GetPageData(localPage);
		CmdReqAlignmentArea	Cmd(GetLayersBase());
		Ap->TransmitDirectly(&Cmd);
		SendBack->Area+=Cmd.Area;
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckAllAlignmentArea::GUICmdAckAllAlignmentArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
GUICmdAckAllAlignmentArea::~GUICmdAckAllAlignmentArea(void)
{
}

bool	GUICmdAckAllAlignmentArea::Load(QIODevice *f)
{
	if(Area.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdAckAllAlignmentArea::Save(QIODevice *f)
{
	if(Area.Save(f)==false)
		return false;
	return true;
}
