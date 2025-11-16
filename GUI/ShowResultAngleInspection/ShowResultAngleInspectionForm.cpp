#include "ShowResultAngleInspectionForm.h"
#include "ui_ShowResultAngleInspectionForm.h"
#include "XAngleInspection.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

ShowResultAngleInspectionForm::ShowResultAngleInspectionForm(LayersBase *base,QWidget *parent) :
    GUIFormBase(base,parent),
    ui(new Ui::ShowResultAngleInspectionForm)
{
    ui->setupUi(this);
    Page=0;
}

ShowResultAngleInspectionForm::~ShowResultAngleInspectionForm()
{
    delete ui;
}

void	ShowResultAngleInspectionForm::ShowInPlayer		(int64 shownInspectionID)
{
	GUICmdReqShowResultAngleInspection	RCmd(GetLayersBase(),sRoot,sName,Page);
	GUICmdAckShowResultAngleInspection	ACmd(GetLayersBase(),sRoot,sName,Page);
	if(RCmd.Send(Page,0,ACmd)==true){
		ui->doubleSpinBoxAngle	->setValue(ACmd.ResultAngle);
		if(ACmd.Result==true3){
			QPalette	P=ui->labelResult->palette();
			P.setColor(QPalette::Window,Qt::green);
			ui->labelResult->setPalette(P);
			ui->labelResult->setText("OK");
		}
		else
		if(ACmd.Result==false3){
			QPalette	P=ui->labelResult->palette();
			P.setColor(QPalette::Window,Qt::red);
			ui->labelResult->setPalette(P);
			ui->labelResult->setText("NG");
		}
		else{
			QPalette	P=ui->labelResult->palette();
			P.setColor(QPalette::Window,Qt::gray);
			ui->labelResult->setPalette(P);
			ui->labelResult->setText("");
		}
	}
}
//=======================================================================================

GUICmdReqShowResultAngleInspection::GUICmdReqShowResultAngleInspection(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base ,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqShowResultAngleInspection::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckShowResultAngleInspection	*SendBack=GetSendBack(GUICmdAckShowResultAngleInspection,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	AlgorithmBase	*Base=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AngleInspection");
	SendBack->Result=none3;
	if(Base!=NULL){
		AngleInspectionInPage	*PPage=dynamic_cast<AngleInspectionInPage *>(Base->GetPageData(localPage));
		AngleInspectionItem	*Item=(AngleInspectionItem *)PPage->GetFirstData();
		if(Item!=NULL){
			ResultInItemRoot	*R=Item->GetCurrentResult();
			if(R!=NULL){
				SendBack->ResultAngle	=R->GetResultDouble();
				if(R->GetError()==0)
					SendBack->Result=none3;
				if(R->GetError()==1)
					SendBack->Result=true3;
				if(R->GetError()==2)
					SendBack->Result=false3;
			}
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}
GUICmdAckShowResultAngleInspection::GUICmdAckShowResultAngleInspection(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base ,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckShowResultAngleInspection::Load(QIODevice *f)
{
	if(::Load(f,ResultAngle)==false)	return false;
	if(::Load(f,Result)==false)	return false;
	return true;
}
bool	GUICmdAckShowResultAngleInspection::Save(QIODevice *f)
{
	if(::Save(f,ResultAngle)==false)	return false;
	if(::Save(f,Result)==false)	return false;
	return true;
}