#include "HookPeakingForm.h"
#include "ui_HookPeakingForm.h"
#include "XDisplayImage.h"
#include "XDisplayImagePacket.h"
#include "XCrossObj.h"
#include "XDisplayBitImage.h"
#include "mtPushButtonColored.h"
#include "HookPeakingCommon.h"
#include "XCriticalFunc.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

HookPeakingForm::HookPeakingForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::HookPeakingForm)
{
    ui->setupUi(this);

	ModeShowModeButton=true;
	ModeShowColorButton=true;
	Calclating	=false;
	LastAlpha	=-1;
	LastPaintTime	=0;
	MemoryType		=/**/"Target";
	InitialValue	=50;
	DrawTurn		=0;

	ButtonColor		=new mtPushButtonColored(this);
	ButtonColor		->setGeometry(ui->toolButtonColor->geometry());
	ButtonColor			->setParent(this);
	delete	ui->toolButtonColor;
	ui->toolButtonColor=NULL;
	connect(ButtonColor			,SIGNAL(clicked()),this,SLOT(on_toolButtonColor_clicked()));
	LastColor	=Qt::magenta;
	ButtonColor	->setColor(LastColor);
    
    connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));

	AllocatedCount=0;
	CRadius	=4;
	Thread	=NULL;
}

HookPeakingForm::~HookPeakingForm()
{
	if(Thread!=NULL){
		Thread->Terminated=true;
		Thread->wait(1000);
		Thread->deleteLater();
		//delete	Thread;
		Thread=NULL;
	}
    delete ui;
}
void	HookPeakingForm::ResizeAction()
{
}
static	bool TargetFunctionPaintLast(FunctionServerClass *Obj,GUIFormBase *TargetObj,QPainter &pnt ,QImage &PntImage)
{
	DisplayImage	*DImage=dynamic_cast<DisplayImage *>(TargetObj);
	if(DImage!=NULL && DImage->IsShown()==true){
		HookPeakingForm	*Form=dynamic_cast<HookPeakingForm *>(Obj);
		if(Form!=NULL && Form->isEnabled()==true){
			DImage->LockPaintMutex();
			if(Form->GetLayersBase()->TryLockWeakDraw()==true){
				Form->Draw(pnt,PntImage,DImage->GetZoomRate(),DImage->GetMovx(),DImage->GetMovy()
						,DImage->GetCanvasWidth(),DImage->GetCanvasHeight());
				Form->GetLayersBase()->UnlockWeakDraw();
			}
			DImage->UnlockPaintMutex();
		}
	}
	return true;
}
void	HookPeakingForm::Prepare(void)
{
	Release();
	if(ModeShowModeButton==false){
		ui->toolButtonMode->setVisible(false);
		ButtonColor	->move(0,0);
		ui->horizontalSliderTransparentRate	->move(ui->horizontalSliderTransparentRate->geometry().left()-50,ui->horizontalSliderTransparentRate->geometry().top());
		ui->labelTransparent				->move(ui->labelTransparent->geometry().left()-50,ui->labelTransparent->geometry().top());
	}
	if(ModeShowColorButton==false){
		ButtonColor	->setVisible(false);
		ui->horizontalSliderTransparentRate	->move(ui->horizontalSliderTransparentRate->geometry().left()-50,ui->horizontalSliderTransparentRate->geometry().top());
		ui->labelTransparent				->move(ui->labelTransparent->geometry().left()-50,ui->labelTransparent->geometry().top());
	}
	ui->horizontalSliderTransparentRate	->setValue(InitialValue);
}
void	HookPeakingForm::Release(void)
{
	AllocatedCount=0;
}
void	HookPeakingForm::ReadyParam(void)
{
	AllocatedCount=GetPageNumb();
	if(GetLayersBase()->IsLocalCamera()==true){
		if(Thread!=NULL){
			Thread->Terminated=true;
			Thread->wait(1000);
			Thread->deleteLater();
		}
		Thread	=new ThreadPeaking(GetLayersBase(),this);
		Thread->CRadius=&CRadius;
		connect(Thread,SIGNAL(SignalShowPeaking()),this,SLOT(SlotShowPeaking()),Qt::QueuedConnection);
		//Thread->start();
	}
	else{
		Thread=NULL;
	}

	for(int i=0;i<HookTargetListInst.count();i++){
		QString	HookTargetInst=HookTargetListInst[i];
		GUIFormBase *s=dynamic_cast<GUIFormBase *>(GetLayersBase()->FindByName(HookTargetInst));
		if(s!=NULL){
			TargetPanels.Add(s);
			DisplayImage *TargetPanel=dynamic_cast<DisplayImage *>(s);
			if(TargetPanel!=NULL){
				TargetPanel->SetHookInPaintLast		(this,TargetFunctionPaintLast);
			}
		}
	}
}

void HookPeakingForm::on_toolButtonMode_clicked()
{
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdMakePeakData	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		RCmd.Calclating=ui->toolButtonMode->isChecked();
		RCmd.InstName	=GetName();
		RCmd.Send(NULL,GlobalPage,0);
	}
	TargetPanels.Repaint();
}

void HookPeakingForm::on_toolButtonColor_clicked()
{
	TargetPanels.Repaint();
}

void	HookPeakingForm::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdSetPeaking	*CmdSetPeakingVar=dynamic_cast<CmdSetPeaking *>(packet);
	if(CmdSetPeakingVar!=NULL){
		ui->toolButtonMode->setChecked(CmdSetPeakingVar->Active);
		if(CmdSetPeakingVar->Active==true){
			ui->horizontalSliderTransparentRate->setValue(100.0*CmdSetPeakingVar->Alpha);
		}
		on_toolButtonMode_clicked();
		return;
	}
	CmdGetPeaking	*CmdGetPeakingVar=dynamic_cast<CmdGetPeaking *>(packet);
	if(CmdGetPeakingVar!=NULL){
		CmdGetPeakingVar->Active	=ui->toolButtonMode->isChecked();
		CmdGetPeakingVar->Alpha		=ui->horizontalSliderTransparentRate->value()/100.0;
		return;
	}
	CmdSetPeakingColor	*CmdSetPeakingColorVar=dynamic_cast<CmdSetPeakingColor *>(packet);
	if(CmdSetPeakingColorVar!=NULL){
		ButtonColor->setColor(CmdSetPeakingColorVar->Color);
		return;
	}
	CmdGetPeakingColor	*CmdGetPeakingColorVar=dynamic_cast<CmdGetPeakingColor *>(packet);
	if(CmdGetPeakingColorVar!=NULL){
		CmdGetPeakingColorVar->Color=ButtonColor->color();
		return;
	}
	CmdDrawPeaking	*CmdDrawPeakingVar=dynamic_cast<CmdDrawPeaking *>(packet);
	if(CmdDrawPeakingVar!=NULL){
		Draw	(*CmdDrawPeakingVar->Pnt	,*CmdDrawPeakingVar->PntImage
				,CmdDrawPeakingVar->ZoomRate,CmdDrawPeakingVar->movx ,CmdDrawPeakingVar->movy
				,CmdDrawPeakingVar->PntImage->width(),CmdDrawPeakingVar->PntImage->height());
		return;
	}
}

void HookPeakingForm::on_horizontalSliderTransparentRate_valueChanged(int value)
{
	ui->labelTransparent->setText(QString::number(ui->horizontalSliderTransparentRate->value()));
	TargetPanels.Repaint();
}
void	HookPeakingForm::SlotShowPeaking()
{
	DWORD	t=::GetComputerMiliSec();
	if(t-LastPaintTime>500){
		TargetPanels.Repaint();
	}
}

void	HookPeakingForm::SetCalclating(bool b)
{
	if(Thread!=NULL){
		if(b==true && Thread->isRunning()==false){
			Thread->start();
		}
		else{
			if(Thread->isRunning()==true){
				Thread->Terminated=true;
				Thread->wait(1000);
			}
		}
	}
}


//==============================================================================-
GUICmdMakePeakData::GUICmdMakePeakData(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Calclating=false;
}

bool	GUICmdMakePeakData::Load(QIODevice *f)
{
	if(::Load(f,Calclating)==false)
		return false;
	if(::Load(f,InstName)==false)
		return false;
	return true;
}

bool	GUICmdMakePeakData::Save(QIODevice *f)
{
	if(::Save(f,Calclating)==false)
		return false;
	if(::Save(f,InstName)==false)
		return false;
	return true;
}

void	GUICmdMakePeakData::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName )
{
	GUIFormBase	*f=GetLayersBase()->FindByName(sRoot,sName,InstName);
	if(f!=NULL){
		HookPeakingForm	*fm=(HookPeakingForm *)f;
		fm->SetCalclating(Calclating);
		//HookPeakingForm	*h=(HookPeakingForm *)f;
		//h->MakePeakData(localPage);
	}
}