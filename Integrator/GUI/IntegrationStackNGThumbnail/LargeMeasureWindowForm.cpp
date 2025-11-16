#include "IntegrationStackNGThumbnailResource.h"
#include "LargeMeasureWindowForm.h"
#include "ui_LargeMeasureWindowForm.h"
#include "IntegrationStackNGThumbnailForm.h"
#include <QPainter>
#include "XMeasureLineMove.h"
#include "XIntegrationStackNGThumbnailPacket.h"

extern	const	char	*sRoot;
extern	const	char	*sName;


LargeMeasureWindowForm::LargeMeasureWindowForm(ThumbnailPanel *p ,QWidget *parent) :
    QWidget(parent)
	,ServiceForLayers(p->GetLayersBase())
 	,PasswordInQWodget(p->GetLayersBase(),this)
	,Parent(p)
    ,ui(new Ui::LargeMeasureWindowForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

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
}

LargeMeasureWindowForm::~LargeMeasureWindowForm()
{
    delete ui;
}

void	LargeMeasureWindowForm::Initial(void)
{
	QBuffer	Buff(&Parent->RepresentativePoint->ExtraData);
	if(Buff.open(QIODevice::ReadOnly)==true){
		struct ResultDistanceForExtraData	RData;
		if(Buff.read((char *)&RData,sizeof(RData))!=sizeof(RData))
			return;
		if(::Load(&Buff,TargetSide1Image	)==false)	return;
		if(::Load(&Buff,NGTargetSide1Image	)==false)	return;
		if(::Load(&Buff,TargetSide2Image	)==false)	return;
		if(::Load(&Buff,NGTargetSide2Image	)==false)	return;
		if(::Load(&Buff,TargetImage			)==false)	return;
		if(::Load(&Buff,NGTargetImage		)==false)	return;

		double	Lx=abs(RData.DistanceX1-RData.DistanceX2);
		double	Ly=abs(RData.DistanceY1-RData.DistanceY2);

		if(Lx<Ly){
			ui->stackedWidgetMaster->setCurrentIndex(1);
			ui->stackedWidgetTarget->setCurrentIndex(1);

			LabelMasterImage.setParent(ui->frameMasterWholeV);
			LabelTargetImage.setParent(ui->frameTargetWholeV);
			if(RData.DistanceY1<RData.DistanceY2){
				LabelMasterSide1Image	.setParent(ui->frameMasteEdge1V);
				LabelMasterSide2Image	.setParent(ui->frameMasteEdge2V);
				LabelTargetSide1Image	.setParent(ui->frameTargetEdge1V);
				LabelTargetSide2Image	.setParent(ui->frameTargetEdge2V);
			}
			else{
				LabelMasterSide1Image	.setParent(ui->frameMasteEdge2V);
				LabelMasterSide2Image	.setParent(ui->frameMasteEdge1V);
				LabelTargetSide1Image	.setParent(ui->frameTargetEdge2V);
				LabelTargetSide2Image	.setParent(ui->frameTargetEdge1V);
			}
		}
		else{
			ui->stackedWidgetMaster->setCurrentIndex(0);
			ui->stackedWidgetTarget->setCurrentIndex(0);

			LabelMasterImage.setParent(ui->frameMasterWholeH);
			LabelTargetImage.setParent(ui->frameTargetWholeH);
			if(RData.DistanceX1<RData.DistanceX2){
				LabelMasterSide1Image	.setParent(ui->frameMasteEdge1H);
				LabelMasterSide2Image	.setParent(ui->frameMasteEdge2H);
				LabelTargetSide1Image	.setParent(ui->frameTargetEdge1H);
				LabelTargetSide2Image	.setParent(ui->frameTargetEdge2H);
			}
			else{
				LabelMasterSide1Image	.setParent(ui->frameMasteEdge2H);
				LabelMasterSide2Image	.setParent(ui->frameMasteEdge1H);
				LabelTargetSide1Image	.setParent(ui->frameTargetEdge2H);
				LabelTargetSide2Image	.setParent(ui->frameTargetEdge1H);
			}
		}
		TargetImageWithLine		=TargetImage;
		TargetSide1ImageWithLine=TargetSide1Image;
		TargetSide2ImageWithLine=TargetSide2Image;
		QPainter	PntTarget(&TargetImageWithLine);
		PntTarget.drawImage(0,0,NGTargetImage);
		QPainter	PntSide1(&TargetSide1ImageWithLine);
		PntSide1.drawImage(0,0,NGTargetSide1Image);
		QPainter	PntSide2(&TargetSide2ImageWithLine);
		PntSide2.drawImage(0,0,NGTargetSide2Image);

		PixmapTargetImage		=QPixmap::fromImage(TargetImage)		;
		PixmapTargetSide1Image	=QPixmap::fromImage(TargetSide1Image)	;
		PixmapTargetSide2Image	=QPixmap::fromImage(TargetSide2Image)	;
		LabelTargetImage	 .setPixmap(PixmapTargetImage		);
		LabelTargetSide1Image.setPixmap(PixmapTargetSide1Image	);
		LabelTargetSide2Image.setPixmap(PixmapTargetSide2Image	);

		ImagePointerContainer MasterImageList;
		Parent->Master->GetMasterImage(Parent->Phase,Parent->RPage->Page,MasterImageList);

		int	W=TargetImage.width();
		int	H=TargetImage.height();
		MasterImage		=QImage(W,H,QImage::Format_ARGB32);
		MasterSide1Image=QImage(W,H,QImage::Format_ARGB32);
		MasterSide2Image=QImage(W,H,QImage::Format_ARGB32);
		
		MasterImageList.MakeImage(MasterImage		,-RData.TargetImageX1	  ,-RData.TargetImageY1	    ,RData.TargetImageZoomRate);
		MasterImageList.MakeImage(MasterSide1Image	,-RData.TargetImageSide1X1,-RData.TargetImageSide1Y1,RData.TargetImageSide1ZoomRate);
		MasterImageList.MakeImage(MasterSide2Image	,-RData.TargetImageSide2X1,-RData.TargetImageSide2Y1,RData.TargetImageSide2ZoomRate);

		PixmapMasterImage		=QPixmap::fromImage(MasterImage)		;
		PixmapMasterSide1Image	=QPixmap::fromImage(MasterSide1Image)	;
		PixmapMasterSide2Image	=QPixmap::fromImage(MasterSide2Image)	;
		LabelMasterImage	 .setPixmap(PixmapMasterImage		);
		LabelMasterSide1Image.setPixmap(PixmapMasterSide1Image	);
		LabelMasterSide2Image.setPixmap(PixmapMasterSide2Image	);


		ui->doubleSpinBoxMinDistance	->setValue(RData.DistanceThresholdM);
		ui->doubleSpinBoxMaxDistance	->setValue(RData.DistanceThresholdP);
		ui->doubleSpinBoxMinDistanceMM	->setValue(RData.DistanceThresholdMMM);
		ui->doubleSpinBoxMaxDistanceMM	->setValue(RData.DistanceThresholdPMM);

		ui->doubleSpinBoxResultMM->setValue(RData.ResultDistanceMM);
		ui->doubleSpinBoxResult	 ->setValue(RData.ResultDistance);
	}

	ShowingMasterImage=false;
	FlipTimer.setInterval(300);
	FlipTimer.setSingleShot(false);
	connect(&FlipTimer,SIGNAL(timeout()),this,SLOT(SlotTimeOut()));

	FlipTimer.start();
}
void	LargeMeasureWindowForm::closeEvent ( QCloseEvent * event )
{
	if(Parent!=NULL){
		if(Parent->Parent!=NULL){
			Parent->Parent->LargeMeasureWindow=NULL;
			Parent=NULL;
		}
	}
}
void	LargeMeasureWindowForm::SlotTimeOut()
{
	if(ShowingMasterImage==false){
		LabelTargetImage	 .setPixmap(QPixmap::fromImage(TargetImage));
		LabelTargetSide1Image.setPixmap(QPixmap::fromImage(TargetSide1Image));
		LabelTargetSide2Image.setPixmap(QPixmap::fromImage(TargetSide2Image));
	}
	else{
		LabelTargetImage	 .setPixmap(QPixmap::fromImage(TargetImageWithLine));
		LabelTargetSide1Image.setPixmap(QPixmap::fromImage(TargetSide1ImageWithLine));
		LabelTargetSide2Image.setPixmap(QPixmap::fromImage(TargetSide2ImageWithLine));
	}
	ShowingMasterImage=!ShowingMasterImage;
}
void LargeMeasureWindowForm::on_PushButtonExpand1Side_clicked()
{
	if(LearningMenuDimNumb>=3){
		Parent->SendLearning(LearningMenu_MeasureLineMove_OK_BySide1,false);
	}
	close();
}

void LargeMeasureWindowForm::on_PushButtonExpand2Side_clicked()
{
	if(LearningMenuDimNumb>=3){
		Parent->SendLearning(LearningMenu_MeasureLineMove_OK_BySide2,false);
	}
	close();
}

void LargeMeasureWindowForm::on_PushButtonOKbyDistance_clicked()
{
	if(LearningMenuDimNumb>=3){
		Parent->SendLearning(LearningMenu_MeasureLineMove_OK_ByDistance,false);
	}
	close();
}


void LargeMeasureWindowForm::on_pushButtonClose_clicked()
{
	close();
}
