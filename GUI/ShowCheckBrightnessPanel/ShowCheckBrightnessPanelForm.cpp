#include "ShowCheckBrightnessPanelResource.h"
#include "ShowCheckBrightnessPanelForm.h"
#include "ui_ShowCheckBrightnessPanelForm.h"
#include <QPalette>
#include <QLineEdit>
#include "XDataInLayer.h"
#include "ThreadSequence.h"
#include "XSequenceLocal.h"
#include "XExecuteInspectBase.h"
#include "XGeneralFunc.h"
#include "XEntryPoint.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

ShowCheckBrightnessPanelForm::ShowCheckBrightnessPanelForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::ShowCheckBrightnessPanelForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	iResultNG=NULL;
}

ShowCheckBrightnessPanelForm::~ShowCheckBrightnessPanelForm()
{
    delete ui;
}

void	ShowCheckBrightnessPanelForm::Prepare(void)
{
	if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL
	&& GetLayersBase()->GetShadowLevel()==0){
		SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
		if(Param!=NULL){
			iResultNG		=new SignalOperandInt(this,499,/**/"ShowCheckBrightnessPanelForm:iResultNG");
			SeqErrorInfo	Error;
			if(Param->SetSpecialOperand(iResultNG,&Error)==false){
				iResultNG->ShowErrorMessage(Error);
			}
			iResultNG		->Set(0);
		}
	}
}

void	ShowCheckBrightnessPanelForm::BuildForShow(void)
{
	QString	EmitterRoot=sRoot;
	QString	EmitterName=sName;
	int row=0;
	for(CBPanelList *d=CBContainer.GetFirst();d!=NULL;d=d->GetNext()){
		d->Check=false;
	}
	for(int phase=0;phase<GetPhaseNumb();phase++){
		GetLayersBase()->TF_SetCurrentScanPhaseNumber(phase);
		for(int page=0;page<GetParamGlobal()->PageNumb;page++){
			for(int Layer=0;Layer<GetLayerNumb(page);Layer++){
				int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
				GUICmdSendCBInfo	BmpReceiver	(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
				GUICmdReqCBInfo		BmpRequester(GetLayersBase(),EmitterRoot,EmitterName,globalPage);

				BmpRequester.Layer=Layer;
				if(BmpRequester.Send(globalPage,0,BmpReceiver)==true
				&& BmpReceiver.IsReceived()==true){
					for(CBPanelList *s=BmpReceiver.CBList.GetFirst();s!=NULL;s=s->GetNext()){
						s->GlobalPage=globalPage;
						bool	Found=false;
						for(CBPanelList *d=CBContainer.GetFirst();d!=NULL;d=d->GetNext()){
							if(s->GlobalPage==d->GlobalPage
							&& s->Layer==d->Layer
							&& s->ItemID==d->ItemID
							&& s->RegNumber==d->RegNumber){
								d->ItemName=s->ItemName;
								d->Check=true;
								Found=true;
								break;
							}
						}
						if(Found==false){
							CBPanelList	*item=new CBPanelList();
							item->GlobalPage		=globalPage;
							item->ItemID			=s->ItemID;
							item->Layer				=s->Layer;
							item->ItemName			=s->ItemName;
							item->RegNumber			=s->RegNumber;
							CBContainer.AppendList(item);
						}
					}
				}
			}
		}
	}
	GetLayersBase()->TF_SetCurrentScanPhaseNumber(0);

	RAgain:;
	for(CBPanelList *d=CBContainer.GetFirst();d!=NULL;d=d->GetNext()){
		if(d->Check==false){
			CBContainer.RemoveList(d);
			delete	d;
			goto	RAgain;
		}
	}

	ui->tableWidget	->setColumnCount(CBContainer.GetCount());
	
	int	Col=0;
	QStringList	Headers;
	for(CBPanelList *d=CBContainer.GetFirst();d!=NULL;d=d->GetNext()){
		Headers.append(d->ItemName);
	}
	ui->tableWidget->setHorizontalHeaderLabels(Headers);
}

void	ShowCheckBrightnessPanelForm::ShowInPlayer(int64 shownInspectionID)
{
	int	Col=0;
	int	Res=1;
	for(CBPanelList *d=CBContainer.GetFirst();d!=NULL;d=d->GetNext()){
		GUICmdSendCBResult		BmpReceiver	(GetLayersBase(),sRoot,sName,d->GlobalPage);
		GUICmdReqCBResult		BmpRequester(GetLayersBase(),sRoot,sName,d->GlobalPage);
		BmpRequester.Layer	=d->Layer;
		BmpRequester.ItemID	=d->ItemID;
		if(BmpRequester.Send(d->GlobalPage,0,BmpReceiver)==true){
			if(BmpReceiver.ResultOK==true){
				::SetDataToTable(ui->tableWidget ,Col ,0 ,/**/"OK");
			}
			else{
				::SetDataToTable(ui->tableWidget ,Col ,0 ,/**/"NG");
				Res=2;
			}
		}
		Col++;
	}
	if(iResultNG!=NULL){
		if(Res==2){
			iResultNG->Set(Res);
		}
	}
}

//======================================================================
GUICmdReqCBInfo::GUICmdReqCBInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Layer=-1;
}
bool	GUICmdReqCBInfo::Load(QIODevice *f)
{
	if(::Load(f,Layer)==false)
		return false;
	return true;
}

bool	GUICmdReqCBInfo::Save(QIODevice *f)
{
	if(::Save(f,Layer)==false)
		return false;
	return true;
}


void	GUICmdReqCBInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendCBInfo	*SendBack=GetSendBack(GUICmdSendCBInfo,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"CheckBrightness");
	if(PBase==NULL)
		return;
	CheckBrightnessInPage	*PPage=dynamic_cast<CheckBrightnessInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdReqCBPanelInfo	Da(GetLayersBase());
		Da.Layer	=Layer;
		Da.Info		=&SendBack->CBList;
		PPage->TransmitDirectly(&Da);
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendCBInfo::GUICmdSendCBInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendCBInfo::Load(QIODevice *f)
{
	if(CBList.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendCBInfo::Save(QIODevice *f)
{
	if(CBList.Save(f)==false)
		return false;
	return true;
}
	
GUICmdReqCBResult::GUICmdReqCBResult(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Layer	=0;
	ItemID	=0;
}

bool	GUICmdReqCBResult::Load(QIODevice *f)
{
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	return true;
}
bool	GUICmdReqCBResult::Save(QIODevice *f)
{
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	return true;
}

void	GUICmdReqCBResult::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendCBResult	*SendBack=GetSendBack(GUICmdSendCBResult,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*PBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"CheckBrightness");
	if(PBase==NULL)
		return;
	CheckBrightnessInPage	*PPage=dynamic_cast<CheckBrightnessInPage *>(PBase->GetPageData(localPage));
	if(PPage!=NULL){
		CmdReqCBPanelResult	Da(GetLayersBase());
		Da.Layer	=Layer;
		Da.ItemID	=ItemID;
		PPage->TransmitDirectly(&Da);
		SendBack->ResultOK=	Da.ResultOK;
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendCBResult::GUICmdSendCBResult(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ResultOK=true;
}
bool	GUICmdSendCBResult::Load(QIODevice *f)
{
	if(::Load(f,ResultOK)==false)
		return false;
	return true;
}
bool	GUICmdSendCBResult::Save(QIODevice *f)
{
	if(::Save(f,ResultOK)==false)
		return false;
	return true;
}
