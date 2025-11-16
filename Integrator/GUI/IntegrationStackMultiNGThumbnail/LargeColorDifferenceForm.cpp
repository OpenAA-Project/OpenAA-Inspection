//#include "IntegrationStackNGThumbnailResource.h"
#include "LargeColorDifferenceForm.h"
#include "ui_LargeColorDifferenceForm.h"
#include "IntegrationStackMultiNGThumbnailForm.h"
#include <QPainter>
#include "XColorDifference.h"
#include "XIntegrationStackNGThumbnailPacket.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

FrameLargeWindowColorDifference::FrameLargeWindowColorDifference(LargeColorDifferenceForm *p)
	:Parent(p)
{	
	ShowingMasterImage=false;
	FlipTimer.setInterval(300);
	FlipTimer.setSingleShot(false);
	connect(&FlipTimer,SIGNAL(timeout()),this,SLOT(SlotTimeOut()));
}
void	FrameLargeWindowColorDifference::StartTimer(void)
{
	FlipTimer.start();
}
void	FrameLargeWindowColorDifference::SlotTimeOut()
{
	ShowingMasterImage=!ShowingMasterImage;
	repaint();
}
void	FrameLargeWindowColorDifference::paintEvent(QPaintEvent *event)
{
	QPainter	Pnt(this);
	Pnt.drawImage(0,0,Parent->NGImage);
	if(ShowingMasterImage==true){
		if(Parent->ShowDrawNGMark()==true){
			Pnt.drawImage(0,0,Parent->NGMarkImage);
		}
	}
}
FrameMasterWindowColorDifference::FrameMasterWindowColorDifference(LargeColorDifferenceForm *p)
	:Parent(p)
{	
}
void	FrameMasterWindowColorDifference::paintEvent(QPaintEvent *event)
{
	QPainter	Pnt(this);
	Pnt.drawImage(0,0,Parent->MasterImage);
}


LargeColorDifferenceForm::LargeColorDifferenceForm(ThumbnailPanel *p ,QWidget *parent) :
    QWidget(parent)
	,ServiceForLayers(p->GetLayersBase())
 	,PasswordInQWodget(p->GetLayersBase(),this)
	,Parent(p)
	,ImagePanel(this)
	,MasterPanel(this)
	,ui(new Ui::LargeColorDifferenceForm)
{
    ui->setupUi(this);
    //LangSolver.SetUI(this);

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
	connect(this,SIGNAL(SignalShowDetail()),Parent,SLOT(SlotShowDetail()));
}

LargeColorDifferenceForm::~LargeColorDifferenceForm()
{
    delete ui;
	if(Parent!=NULL){
		if(Parent->Parent!=NULL){
			Parent->Parent->LargeColorDifferenceWindow=NULL;
			Parent=NULL;
		}
	}
}

void	LargeColorDifferenceForm::closeEvent ( QCloseEvent * event )
{
	if(Parent!=NULL){
		if(Parent->Parent!=NULL){
			Parent->Parent->LargeColorDifferenceWindow=NULL;
			Parent=NULL;
		}
	}
}

void	LargeColorDifferenceForm::Initial(void)
{
	QBuffer	Buff(&Parent->RepresentativePoint->ExtraData);
	if(Buff.open(QIODevice::ReadOnly)==true){
		struct ResultColorDifferenceForExtraData	RData;
		if(Buff.read((char *)&RData,sizeof(RData))!=sizeof(RData))
			return;

		ui->doubleSpinBoxThresholdDeltaE->setValue(RData.ThresholdDeltaE);
		ui->doubleSpinBoxResultDeltaE	->setValue(RData.ResultDeltaE	);
	}
}
bool	LargeColorDifferenceForm::ShowDrawNGMark(void)
{
	return ui->toolButtonShowNGMark->isChecked();
}
void	LargeColorDifferenceForm::showEvent(QShowEvent *event)
{
	ImagePanel.repaint();
}

void LargeColorDifferenceForm::on_PushButtonOKbyDeltaE_clicked()
{
	if(LearningMenuDimNumb>0){
		Parent->SendLearning(LearningMenuDim[0].MenuID,false);
	}
	close();
}


void LargeColorDifferenceForm::on_PushButtonOKbyDeltaEWhole_clicked()
{
	if(LearningMenuDimNumb>0){
		Parent->SendLearning(LearningMenuDim[0].MenuID,true);
	}
	close();
}


void LargeColorDifferenceForm::on_toolButtonShowNGMark_triggered(QAction *arg1)
{
	MasterPanel.repaint();
}


void LargeColorDifferenceForm::on_pushButtonDetail_clicked()
{
	setWindowFlags(SavedFlag);
	emit	SignalShowDetail();
}


void LargeColorDifferenceForm::on_pushButtonClose_clicked()
{
	close();
}

