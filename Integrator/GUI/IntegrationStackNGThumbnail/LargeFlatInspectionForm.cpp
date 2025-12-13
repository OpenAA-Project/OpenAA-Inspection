#include "IntegrationStackNGThumbnailResource.h"
#include "LargeFlatInspectionForm.h"
#include "ui_LargeFlatInspectionForm.h"
#include "IntegrationStackNGThumbnailForm.h"
#include <QPainter>
#include "XIntegrationStackNGThumbnailPacket.h"


extern	const	char	*sRoot;
extern	const	char	*sName;

LFIFrameLargeWindow::LFIFrameLargeWindow(LargeFlatInspectionForm *p)
	:Parent(p)
{	
	ShowingMasterImage=false;
	FlipTimer.setInterval(300);
	FlipTimer.setSingleShot(false);
	connect(&FlipTimer,SIGNAL(timeout()),this,SLOT(SlotTimeOut()));
}
void	LFIFrameLargeWindow::StartTimer(void)
{
	FlipTimer.start();
}
void	LFIFrameLargeWindow::SlotTimeOut()
{
	ShowingMasterImage=!ShowingMasterImage;
	repaint();
}
void	LFIFrameLargeWindow::paintEvent(QPaintEvent *event)
{
	QPainter	Pnt(this);
	Pnt.drawImage(0,0,Parent->NGImage);
	if(ShowingMasterImage==true){
		if(Parent->ShowDrawNGMark()==true){
			Pnt.drawImage(0,0,Parent->NGMarkImage);
		}
	}
}

LFIFrameMasterWindow::LFIFrameMasterWindow(LargeFlatInspectionForm *p)
	:Parent(p)
{	
}
void	LFIFrameMasterWindow::paintEvent(QPaintEvent *event)
{
	QPainter	Pnt(this);
	Pnt.drawImage(0,0,Parent->MasterImage);
}

//----------------------------------------------------------------------------

LargeFlatInspectionForm::LargeFlatInspectionForm(ThumbnailPanel *p ,QWidget *parent) :
    QWidget(parent)
	,ServiceForLayers(p->GetLayersBase())
 	,PasswordInQWodget(p->GetLayersBase(),this)
	,Parent(p)
	,ImagePanel(this)
	,MasterPanel(this)
    ,ui(new Ui::LargeFlatInspectionForm)
{
    ui->setupUi(this);

	LangSolver.SetUI(this);

	SavedFlag=windowFlags();
	setWindowFlags(SavedFlag | Qt::WindowStaysOnTopHint);

	int	W=ui->frame->width();
	int	H=ui->frame->height();

	ImagePanel.setParent(ui->frame);
	ImagePanel.setGeometry(0,0,W,H);

	MasterPanel.setParent(ui->frameMaster);
	MasterPanel.setGeometry(0,0,W,H);

	int	W1=Parent->NGImage	 .width();
	int	H1=Parent->NGImage	 .height();
	int	W2=Parent->NGMarkImage->width();
	int	H2=Parent->NGMarkImage->height();
	int	W3=Parent->MasterImage->width();
	int	H3=Parent->MasterImage->height();

	NGImage		=Parent->NGImage	 .scaled(W,H,Qt::KeepAspectRatio,Qt::FastTransformation);
	NGMarkImage	=Parent->NGMarkImage->scaled(W,H,Qt::KeepAspectRatio,Qt::FastTransformation);
	MasterImage	=Parent->MasterImage->scaled(W,H,Qt::KeepAspectRatio,Qt::FastTransformation);

	//ui->labelMaster->setPixmap(QPixmap::fromImage(MasterImage));
	ImagePanel.StartTimer();

	if(Parent->RepresentativePoint!=NULL){
		int	LibType=Parent->RepresentativePoint->LibType;

		IntegrationCmdReqLearningMenu	RCmd(GetLayersBase(),sRoot,sName,0);
		IntegrationCmdAckLearningMenu	ACmd(GetLayersBase(),sRoot,sName,0);
		RCmd.LibType=LibType;
		LearningMenuDimNumb=0;
		if(RCmd.Send(0,0,ACmd)==true){
			for(int i=0;i<ACmd.MenuDimNumb && i<sizeof(LearningMenuDim)/sizeof(LearningMenuDim[0]);i++){
				LearningMenuDim[i]=ACmd.LearningMenuDim[i];
				LearningMenuDimNumb++;
			}
		}
	}
	if(Parent->RepresentativePoint!=NULL){
		EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(Parent->Parent->SlaveNo);
		if(m==NULL){
			m=GetLayersBase()->GetIntegrationBasePointer()->FindMaster(Parent->Parent->MachineID);
		}
		//if(m!=NULL){
		//	IntegrationCmdReqItemInfo	RCmd(GetLayersBase(),sRoot,sName,m->GetIntegrationSlaveNo());
		//	RCmd.LibType	=Parent->RepresentativePoint->LibType;
		//	RCmd.Phase		=m->GetCurrentPhase();
		//	RCmd.Layer		=0;
		//	RCmd.ItemID		=Parent->RepresentativePoint->UniqueID;
		//	IntegrationCmdAckItemInfo	ACmd(GetLayersBase(),sRoot,sName,m->GetIntegrationSlaveNo());
		//	if(RCmd.Send(m->GetIntegrationSlaveNo(),Parent->RPage->Page,ACmd)==true){
		//		ReportedTopic	*AreaSearch	=ACmd.ReportedContainer.FindTopic(/**/"AreaSearch");
		//		ReportedTopic	*SelfSearch	=ACmd.ReportedContainer.FindTopic(/**/"SelfSearch");
		//
		//		ReportedTopic	*OKDot		=ACmd.ReportedContainer.FindTopic(/**/"OKDot");
		//		ReportedTopic	*OKLength	=ACmd.ReportedContainer.FindTopic(/**/"OKLength");
		//
		//		if(RL!=NULL && RH!=NULL
		//		&& GL!=NULL && GH!=NULL
		//		&& BL!=NULL && BH!=NULL
		//		&& AreaSearch!=NULL && SelfSearch!=NULL
		//		&& OKDot!=NULL && OKLength!=NULL){
		//
		//			QString	s1	=QString("赤暗側:")+QString::number(RL->Data.toInt())+QString(" 明側:")+QString::number(RH->Data.toInt())
		//						+QString(/**/"\n")
		//						+QString("緑暗側:")+QString::number(GL->Data.toInt())+QString(" 明側:")+QString::number(GH->Data.toInt())
		//						+QString(/**/"\n")
		//						+QString("青暗側:")+QString::number(BL->Data.toInt())+QString(" 明側:")+QString::number(BH->Data.toInt());
		//			QString	s2	=QString("領域探索:")+QString::number(AreaSearch->Data.toInt())
		//						+QString(/**/"\n")
		//						+QString("ピクセル探索:")+QString::number(SelfSearch->Data.toInt());
		//			QString	s3	=QString("OKドット:")+QString::number(OKDot->Data.toInt())
		//						+QString(/**/"\n")
		//						+QString("長さ:")+QString::number(OKLength->Data.toInt());
		//
		//			ui->textEditBrightness	->setPlainText(s1);
		//			ui->textEditSearch		->setPlainText(s2);
		//			ui->textEditSizeLen		->setPlainText(s3);
		//		}
		//	}
		//}
	}
	QString StrLibID;
	QString LibName;
	QString CauseStr;
	Parent->Parent->GetInformation(Parent->Result,Parent->RepresentativePoint
									,StrLibID ,LibName ,CauseStr);
	ui->labelLibID	->setText(StrLibID);
	ui->labelLibName->setText(LibName);
	ui->labelResult	->setText(CauseStr);

	connect(this,SIGNAL(SignalShowDetail()),Parent,SLOT(SlotShowDetail()));
}

LargeFlatInspectionForm::~LargeFlatInspectionForm()
{
    delete ui;
	if(Parent!=NULL){
		if(Parent->Parent!=NULL){
			Parent->Parent->LargeFlatInspectionWindow=NULL;
			Parent=NULL;
		}
	}
}
void	LargeFlatInspectionForm::Initial(void)
{
	//QBuffer	Buff(&Parent->RepresentativePoint->ExtraData);
	//if(Buff.open(QIODevice::ReadOnly)==true){
	//	struct ResultColorDifferenceForExtraData	RData;
	//	if(Buff.read((char *)&RData,sizeof(RData))!=sizeof(RData))
	//		return;
	//
	//	ui->doubleSpinBoxThresholdDeltaE->setValue(RData.ThresholdDeltaE);
	//	ui->doubleSpinBoxResultDeltaE	->setValue(RData.ResultDeltaE	);
	//}
}
bool	LargeFlatInspectionForm::ShowDrawNGMark(void)
{
	return ui->toolButtonShowNGMark->isChecked();
}
void	LargeFlatInspectionForm::closeEvent ( QCloseEvent * event )
{
	if(Parent!=NULL){
		if(Parent->Parent!=NULL){
			Parent->Parent->LargeFlatInspectionWindow=NULL;
			Parent=NULL;
		}
	}
}
void	LargeFlatInspectionForm::showEvent(QShowEvent *event)
{
	ImagePanel.repaint();
}


void LargeFlatInspectionForm::on_PushButtonOKbyColorWhole_clicked()
{
	if(LearningMenuDimNumb>3){
		if(Parent!=NULL){
			Parent->SendLearning(LearningMenuDim[0].MenuID,true);
		}
	}
	close();
}


void LargeFlatInspectionForm::on_PushButtonOKbyShiftWhole_clicked()
{
	if(LearningMenuDimNumb>3){
		if(Parent!=NULL){
			Parent->SendLearning(LearningMenuDim[2].MenuID,true);
		}
	}
	close();
}


void LargeFlatInspectionForm::on_PushButtonOKbySizeWhole_clicked()
{
	if(LearningMenuDimNumb>3){
		if(Parent!=NULL){
			Parent->SendLearning(LearningMenuDim[1].MenuID,true);
		}
	}
	close();
}


void LargeFlatInspectionForm::on_toolButtonShowNGMark_clicked()
{
	MasterPanel.repaint();
}


void LargeFlatInspectionForm::on_pushButtonClose_clicked()
{
	close();
}

