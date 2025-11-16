#include "AdjustMultipectalForm.h"
#include "ui_AdjustMultipectalForm.h"
#include "XDataInLayerCommander.h"
#include "XMultiSpectral.h"
#include "XMultiSpectralLibrary.h"
#include "XPieceArchitect.h"
#include "XAlgorithmLibrary.h"
#include "XGeneralDialog.h"
#include "XDrawFunc.h"
#include "swap.h"

extern	const	char	*sRoot;
extern	const	char	*sName;


DisplayAdjustPanel::DisplayAdjustPanel(LayersBase *base ,AdjustMultipectalForm *p, QWidget *parent)
	:QWidget(parent),ServiceForLayers(base)
	,Parent(p)
{
	ItemID				=-1;
	MovX				=0;
	MovY				=0;
	ZoomRate			=1.0;
	GlobalPage			=0;
	Result				=NULL;
	OldGWidth			=-1;
	OldGHeight			=-1;
	NGResultImage		=NULL;
	setMouseTracking(true);
}
DisplayAdjustPanel::~DisplayAdjustPanel(void)
{
	if(NGResultImage!=NULL){
		delete	NGResultImage;
		NGResultImage=NULL;
	}
}

void	DisplayAdjustPanel::SetAlgo(const QString	&_AlgoRoot ,const QString &_AlgoName)
{	
	AlgoRoot=_AlgoRoot;
	AlgoName=_AlgoName;	
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);
	if(Ab!=NULL){
		Result=Ab->GetPageData(0)->CreateResult();
	}
}
void	DisplayAdjustPanel::SetResult(ResultInItemRoot *res)
{
	QBuffer	Buff;

	Buff.open(QIODevice::ReadWrite);

	res->Save(&Buff);
	Buff.seek(0);
	if(Result!=NULL){
		Result->Load(&Buff);
	}
}

void 	DisplayAdjustPanel::paintEvent ( QPaintEvent * event )
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	ReEntrant=true;

	QPainter	Pnt(this);

	GUICmdReqPanelImage	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
	GUICmdAckPanelImage	ACmd(GetLayersBase(),sRoot,sName,GlobalPage);
	RCmd.PanelStructData.Phase		=PhaseCode;
	RCmd.PanelStructData.GWidth		=GWidth	;
	RCmd.PanelStructData.GHeight	=GHeight;
	RCmd.PanelStructData.Mx1		=MovX;
	RCmd.PanelStructData.My1		=MovY;
	RCmd.PanelStructData.ZoomRate	=ZoomRate;
	QImage	*TargetImage=NULL;
	if(RCmd.Send(GlobalPage,0,ACmd)==true){
		TargetImage=ACmd.TargetImage;
	}

	Pnt.setCompositionMode(QPainter::CompositionMode_SourceOver);
	if(TargetImage!=NULL){
		Pnt.drawImage(0,0,*TargetImage);
	}

	int	CircleWidth=0;
	if(GetParamGlobal()!=NULL){
		CircleWidth=GetParamGlobal()->ResultNGCircleWidth;
	}
	if(OldGWidth!=GWidth || OldGHeight!=GHeight){
		if(NGResultImage!=NULL){
			delete	NGResultImage;
		}
		NGResultImage=new QImage(GWidth,GHeight,QImage::Format_ARGB32);
		OldGWidth	=GWidth;
		OldGHeight	=GHeight;
	}
	NGResultImage->fill(0);
	if(Parent->GetSimShowNGMark()==true && Result!=NULL){
		int	Kx=Result->GetTotalShiftedX() ;
		int	Ky=Result->GetTotalShiftedY() ;
		QRgb Col=qRgba(255,0,0,120);
		for(ResultPosList *r=Result->GetPosListFirst();r!=NULL;r=r->GetNext()){
			if(r->result>=0x10000){
				r->DrawResultDetail(Result,*NGResultImage,Pnt
									,MovX-Kx
									,MovY-Ky
									,ZoomRate,5
									,Col,CircleWidth
									,true);
			}
		}
	}
	else{
		QRgb Col=qRgba(255,0,0,0);
		if(Result!=NULL){
			int	Kx=Result->GetTotalShiftedX() ;
			int	Ky=Result->GetTotalShiftedY() ;
			for(ResultPosList *r=Result->GetPosListFirst();r!=NULL;r=r->GetNext()){
				if(r->result>=0x10000){
					r->DrawResult(Result,*NGResultImage,Pnt
										,MovX-Kx
										,MovY-Ky
										,ZoomRate,5
										,Col,CircleWidth
										,true);
				}
			}
		}
	};
	Pnt.setCompositionMode(QPainter::CompositionMode_SourceOver);
	Pnt.drawImage(0,0,*NGResultImage);

	if(Parent->GetSimShowNGMark()==true && Result!=NULL){
		Pnt.setBrush(Qt::yellow);
		Pnt.setPen(Qt::yellow);
		for(ResultPosList *r=Result->GetPosListFirst();r!=NULL;r=r->GetNext()){
			if(r->result>=0x10000){
				int	GCx=(r->Px+MovX)*ZoomRate;
				int	GCy=(r->Py+MovY)*ZoomRate;
				if(-100<GCx && GCx<(GWidth+100)
				&& -100<GCy && GCy<(GHeight+100)){
					QString Msg=QString("Area:")  +QString::number(r->NGSize);
					Pnt.drawText(GCx,GCy   ,Msg);					
				}
			}
		}
	}
	ReEntrant=false;
}
void	DisplayAdjustPanel::mousePressEvent ( QMouseEvent *Ev )	
{
	int GlobalX	=Ev->x()/ZoomRate-MovX;
	int GlobalY	=Ev->y()/ZoomRate-MovY;
}
void	DisplayAdjustPanel::mouseMoveEvent ( QMouseEvent * Ev )
{
	int GlobalX	=Ev->x()/ZoomRate-MovX;
	int GlobalY	=Ev->y()/ZoomRate-MovY;
}
void	DisplayAdjustPanel::mouseReleaseEvent ( QMouseEvent * Ev )
{
	int GlobalX	=Ev->x()/ZoomRate-MovX;
	int GlobalY	=Ev->y()/ZoomRate-MovY;
}
void	DisplayAdjustPanel::wheelEvent ( QWheelEvent * e )
{
	int	D=e->pixelDelta().y();

	if(D>0){
	    int LX=(int)((double)e->position().x()/ZoomRate)/2;
		int LY=(int)((double)e->position().y()/ZoomRate)/2;
		MovX=MovX-LX;
		MovY=MovY-LY;
		ZoomRate=ZoomRate*2.0;
		repaint();
	}
	else if(D<0){
	    int LX=(int)((double)e->position().x()/ZoomRate);
		int LY=(int)((double)e->position().y()/ZoomRate);
		MovX=MovX+LX;
		MovY=MovY+LY;
		ZoomRate=ZoomRate/2.0;
		repaint();
	}
}

//====================================================================

DisplayComparedPanel::DisplayComparedPanel(LayersBase *base 
											,AdjustMultipectalForm *p
											,DisplayComparedPanel *LinkedPanel
											, QWidget *parent)
	:QWidget(parent),ServiceForLayers(base)
	,Parent(p)
	,Linked(LinkedPanel)
{
	ItemID			=-1;
	GlobalPage		=0;
	Result			=NULL;
	OldGWidth		=-1;
	OldGHeight		=-1;
	ImageByLayer	=NULL;
	Mastered		=true;
	setMouseTracking(true);
}
DisplayComparedPanel::~DisplayComparedPanel(void)
{
	if(ImageByLayer!=NULL){
		delete	ImageByLayer;
		ImageByLayer=NULL;
	}
}

void	DisplayComparedPanel::SetAlgo(const QString	&_AlgoRoot ,const QString &_AlgoName)
{	
	AlgoRoot=_AlgoRoot;
	AlgoName=_AlgoName;	
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);
	if(Ab!=NULL){
		Result=Ab->GetPageData(0)->CreateResult();
	}
}
void	DisplayComparedPanel::SetResult(ResultInItemRoot *res)
{
	QBuffer	Buff;

	Buff.open(QIODevice::ReadWrite);

	res->Save(&Buff);
	Buff.seek(0);
	if(Result!=NULL){
		Result->Load(&Buff);
	}
}

void 	DisplayComparedPanel::paintEvent ( QPaintEvent * event )
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	ReEntrant=true;

	QPainter	Pnt(this);

	GUICmdReqComparedPanelImage	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
	GUICmdAckComparedPanelImage	ACmd(GetLayersBase(),sRoot,sName,GlobalPage);
	RCmd.PanelStructData.Phase		=PhaseCode;
	RCmd.PanelStructData.GWidth		=GWidth	;
	RCmd.PanelStructData.GHeight	=GHeight;
	RCmd.PanelStructData.Mx1		=MovX;
	RCmd.PanelStructData.My1		=MovY;
	RCmd.PanelStructData.ZoomRate	=ZoomRate;
	RCmd.PanelStructData.CurrentLayer	=Parent->GetCurrentLayer();
	RCmd.PanelStructData.Mastered	=Mastered;
	QImage	*ImageByLayer=NULL;
	if(RCmd.Send(GlobalPage,0,ACmd)==true){
		ImageByLayer=ACmd.ImageByLayer;
	}

	Pnt.setCompositionMode(QPainter::CompositionMode_SourceOver);
	if(ImageByLayer!=NULL){
		Pnt.drawImage(0,0,*ImageByLayer);
	}
	ReEntrant=false;
}
void	DisplayComparedPanel::mousePressEvent ( QMouseEvent *Ev )	
{
	int GlobalX	=Ev->x()/ZoomRate-MovX;
	int GlobalY	=Ev->y()/ZoomRate-MovY;
}
void	DisplayComparedPanel::mouseMoveEvent ( QMouseEvent * Ev )
{
	int GlobalX	=Ev->x()/ZoomRate-MovX;
	int GlobalY	=Ev->y()/ZoomRate-MovY;
}
void	DisplayComparedPanel::mouseReleaseEvent ( QMouseEvent * Ev )
{
	int GlobalX	=Ev->x()/ZoomRate-MovX;
	int GlobalY	=Ev->y()/ZoomRate-MovY;
}
void	DisplayComparedPanel::wheelEvent ( QWheelEvent * e )
{
	int	D=e->pixelDelta().y();

	if(D>0){
	    int LX=(int)((double)e->position().x()/ZoomRate)/2;
		int LY=(int)((double)e->position().y()/ZoomRate)/2;
		MovX=MovX-LX;
		MovY=MovY-LY;
		ZoomRate=ZoomRate*2.0;
		Linked->SetZoomPos(MovX,MovY,ZoomRate);
		repaint();
	}
	else if(D<0){
	    int LX=(int)((double)e->position().x()/ZoomRate);
		int LY=(int)((double)e->position().y()/ZoomRate);
		MovX=MovX+LX;
		MovY=MovY+LY;
		ZoomRate=ZoomRate/2.0;
		Linked->SetZoomPos(MovX,MovY,ZoomRate);
		repaint();
	}
}
void    DisplayComparedPanel::SetZoomPos(int _MovX,int _MovY,double _ZoomRate)
{
	MovX=_MovX;
	MovY=_MovY;
	ZoomRate=_ZoomRate;
	repaint();
}

//===========================================================================

AdjustMultipectalForm::AdjustMultipectalForm(LayersBase *Base,QWidget *parent) :
    AlgorithmComponentWindow(parent)
    ,ServiceForLayers(Base)
	,PasswordInQWodget(Base,this)
	,DPanel(Base,this)
	,MasterPanel(Base,this,&TargetPanel)
	,TargetPanel(Base,this,&MasterPanel)
    ,ui(new Ui::AdjustMultipectalForm)
{
    ui->setupUi(this);
	OnChanging	=false;
	InstBase	=NULL;
	IData		=NULL;

	DPanel.setParent(ui->frame_SimImage);
	DPanel.SetAlgo(sRoot,sName);
	DPanel.setGeometry(0,0,ui->frame_SimImage->width(),ui->frame_SimImage->height());

	MasterPanel.Mastered=true;
	MasterPanel.setParent(ui->frameMasterImage);
	MasterPanel.SetAlgo(sRoot,sName);
	MasterPanel.setGeometry(0,0,ui->frameMasterImage->width(),ui->frameMasterImage->height());

	TargetPanel.Mastered=false;
	TargetPanel.setParent(ui->frameTargetImage);
	TargetPanel.SetAlgo(sRoot,sName);
	TargetPanel.setGeometry(0,0,ui->frameTargetImage->width(),ui->frameTargetImage->height());

	SetupPassword();
	InstallOperationLog(this);
}

AdjustMultipectalForm::~AdjustMultipectalForm()
{
    delete ui;
	if(IData!=NULL)
		delete	IData;
	IData=NULL;
}

void	AdjustMultipectalForm::Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data)
{
	AlgorithmLibraryContainerForEnum		LibList(InstBase->GetLayersBase());
	LibIDList.RemoveAll();
	LibList.EnumAllLibraries(GetLayersBase()->GetDatabase(),InstBase->GetLibType(),LibIDList);

	if(IData!=NULL)
		delete	IData;
	IData=new AlgorithmItemIndependentPack(InstBase->GetLayersBase());
	*IData=Data;

	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA!=NULL){
			MultiSpectralItem	*BData=dynamic_cast<MultiSpectralItem *>(DA);
			if(BData!=NULL){
				OldLibID		=DA->GetLibID();
				NewLibID		=OldLibID	;
				const	MultiSpectralThreshold	*d=BData->GetThresholdR(GetLayersBase());
				ui->spinBoxSearchDot			->setValue(d->SearchDot);
				ui->doubleSpinBoxThresholdLength->setValue(d->ThresholdLength);
				ui->spinBoxOKDot				->setValue(d->OKDot);

				DPanel.GlobalPage	=D->GlobalPage;
				DPanel.PhaseCode	=D->PhaseCode;
				DPanel.GWidth		=ui->frame_SimImage->width();
				DPanel.GHeight		=ui->frame_SimImage->height();
				DPanel.ZoomRate		=1.0;
				DPanel.MovX			=-(Data.LocalX-DPanel.GWidth /DPanel.ZoomRate/2);
				DPanel.MovY			=-(Data.LocalY-DPanel.GHeight/DPanel.ZoomRate/2);
				DPanel.show();

				MasterPanel.GlobalPage	=D->GlobalPage;
				MasterPanel.PhaseCode	=D->PhaseCode;
				MasterPanel.GWidth		=ui->frameMasterImage->width();
				MasterPanel.GHeight		=ui->frameMasterImage->height();
				MasterPanel.ZoomRate	=1.0;
				MasterPanel.MovX		=-(Data.LocalX-MasterPanel.GWidth /MasterPanel.ZoomRate/2);
				MasterPanel.MovY		=-(Data.LocalY-MasterPanel.GHeight/MasterPanel.ZoomRate/2);
				MasterPanel.show();

				TargetPanel.GlobalPage	=D->GlobalPage;
				TargetPanel.PhaseCode	=D->PhaseCode;
				TargetPanel.GWidth		=ui->frameTargetImage->width();
				TargetPanel.GHeight		=ui->frameTargetImage->height();
				TargetPanel.ZoomRate	=1.0;
				TargetPanel.MovX		=-(Data.LocalX-TargetPanel.GWidth /TargetPanel.ZoomRate/2);
				TargetPanel.MovY		=-(Data.LocalY-TargetPanel.GHeight/TargetPanel.ZoomRate/2);
				TargetPanel.show();
			}
		}
	}
	ShowLibrary();
}
bool    AdjustMultipectalForm::GetSimShowNGMark(void)
{
	return ui->toolButtonSimShowNGMark->isChecked();
}

int     AdjustMultipectalForm::GetCurrentLayer(void)
{
	return ui->spinBoxCurrentLayer->value();
}

void	AdjustMultipectalForm::ShowLibrary(void)
{
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;

		MultiSpectralItem	*BData=dynamic_cast<MultiSpectralItem *>(DA);
		if(BData==NULL)
			continue;

		if(DA->GetLibID()<0){
			ui->EditLibID->setText(/**/"");
			ui->EditLibName->setText(/**/"");
		}
		else{
			ui->EditLibID	->setText(QString::number(DA->GetLibID()));
			ui->EditLibName->setText(/**/"");
			for(AlgorithmLibraryList *L=LibIDList.GetFirst();L!=NULL;L=L->GetNext()){
				if(L->GetLibID()==DA->GetLibID()){
					ui->EditLibName	->setText(L->GetLibName());
					break;
				}
			}
		}

		const	MultiSpectralThreshold	*d=BData->GetThresholdR(GetLayersBase());

		ui->spinBoxSearchDot			->setValue(d->SearchDot);
		ui->doubleSpinBoxThresholdLength->setValue(d->ThresholdLength);
		ui->spinBoxOKDot				->setValue(d->OKDot);

		if(BData->IsOriginParts()==true){
			ui->stackedWidgetParts->setCurrentIndex(1);
		}
		else{
			ui->stackedWidgetParts->setCurrentIndex(0);
		}
		SlotStartCalc();
		return;
	}
}
void	AdjustMultipectalForm::GetDataFromWindow(void)
{
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		MultiSpectralItem	*BData=dynamic_cast<MultiSpectralItem *>(DA);
		if(BData==NULL)
			continue;

		MultiSpectralThreshold	*d=BData->GetThresholdW(GetLayersBase());

		d->SearchDot		=ui->spinBoxSearchDot				->value();
		d->ThresholdLength	=ui->doubleSpinBoxThresholdLength	->value();
		d->OKDot			=ui->spinBoxOKDot					->value();
	}
}

void AdjustMultipectalForm::on_ButtonRelrectOnlyDotColorMatching_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Reflecting ONE block threshold");

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Reflect one block threshold");
	GetDataFromWindow();
	GUICmdSendAlgorithmItemIndependentPack	Packet(IData->Base,QString(/**/"ANY"),QString(/**/"ANY"),-1,true);
	Packet.Command=SetIndependentItemDataCommand_OnlyOne;
	Packet.IData=*IData;
	for(int page=0;page<GetPageNumb();page++){
		Packet.Send(NULL,page,0);
	}
	GetLayersBase()->WaitAllAcknowledged(60*10);
	GetLayersBase()->CloseProcessingForm();
}


void AdjustMultipectalForm::on_ButtonReflectAllDotColorMatchings_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Reflecting ALL blocks\' threshold");

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Reflect all blocks threshold");
	GetDataFromWindow();
	GUICmdSendAlgorithmItemIndependentPack	Packet(IData->Base,QString(/**/"ANY"),QString(/**/"ANY"),-1,true);
	Packet.Command=SetIndependentItemDataCommand_All;
	Packet.IData=*IData;
	for(int page=0;page<GetPageNumb();page++){
		Packet.Send(NULL,page,0);
	}

	GetLayersBase()->WaitAllAcknowledged(60*10);
	GetLayersBase()->CloseProcessingForm();
}


void AdjustMultipectalForm::on_ButtonSaveToLibrary_clicked()
{
	GetDataFromWindow();

	int	ThresholdLevel=GetLayersBase()->SelectThresholdLevel();
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		MultiSpectralItem	*BData=dynamic_cast<MultiSpectralItem *>(DA);
		if(BData==NULL)
			continue;

		int	LibID=BData->GetLibID();
		AlgorithmLibraryContainer	*Container=BData->GetLibraryContainer();
		AlgorithmLibraryLevelContainer	DestLib(Container);
		if(Container->GetLibrary(LibID ,DestLib)==true){
			MultiSpectralLibrary	*ALib=dynamic_cast<MultiSpectralLibrary *>(DestLib.GetLibrary(ThresholdLevel));
			MultiSpectralThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
			Thr->ToLibrary(ALib);
			Container->Update(DestLib);
			return;
		}
	}
}


void AdjustMultipectalForm::on_ButtonLoadFromLibrary_clicked()
{
	int	ThresholdLevel=GetLayersBase()->SelectThresholdLevel();
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		MultiSpectralItem	*BData=dynamic_cast<MultiSpectralItem *>(DA);
		if(BData==NULL)
			continue;

		int	LibID=BData->GetLibID();
		AlgorithmLibraryContainer	*Container=BData->GetLibraryContainer();
		AlgorithmLibraryLevelContainer	SrcLib(Container);
		if(Container->GetLibrary(LibID ,SrcLib)==true){
			MultiSpectralLibrary	*ALib=dynamic_cast<MultiSpectralLibrary *>(SrcLib.GetLibrary(ThresholdLevel));
			MultiSpectralThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
			Thr->FromLibrary(ALib);
			ShowLibrary();
			return;
		}
	}
}


void AdjustMultipectalForm::on_ButtonClose_clicked()
{
	close();
}


void AdjustMultipectalForm::on_horizontalSliderLayer_valueChanged(int value)
{
	SlotStartCalc();
}


void AdjustMultipectalForm::on_spinBoxCurrentLayer_valueChanged(int arg1)
{
	SlotStartCalc();
}


void AdjustMultipectalForm::on_spinBoxSearchDot_valueChanged(int arg1)
{
	SlotStartCalc();
}


void AdjustMultipectalForm::on_doubleSpinBoxThresholdLength_valueChanged(double arg1)
{
	SlotStartCalc();
}


void AdjustMultipectalForm::on_spinBoxOKDot_valueChanged(int arg1)
{
	SlotStartCalc();
}

void AdjustMultipectalForm::SlotStartCalc()
{
	if(OnChanging==true){
		return;
	}
	OnChanging=true;
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		MultiSpectralItem	*nBData=dynamic_cast<MultiSpectralItem *>(DA);
		if(nBData==NULL)
			continue;

		GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.BuildData(sRoot,sName,MultiSpectralReqTryThresholdCommand ,MultiSpectralSendTryThresholdCommand);
		MultiSpectralItem	*BData=&((MultiSpectralReqTryThreshold *)PacketReq.Data)->Threshold;
		MultiSpectralThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		Thr->CopyFrom(*nBData->GetThresholdW());
		((MultiSpectralReqTryThreshold *)PacketReq.Data)->Data.GlobalPage	=D->GlobalPage;
		((MultiSpectralReqTryThreshold *)PacketReq.Data)->Data.ItemID		=DA->GetID();
		((MultiSpectralReqTryThreshold *)PacketReq.Data)->Data.SearchDot		=ui->spinBoxSearchDot			->value();
		((MultiSpectralReqTryThreshold *)PacketReq.Data)->Data.ThresholdLength	=ui->doubleSpinBoxThresholdLength->value();
		((MultiSpectralReqTryThreshold *)PacketReq.Data)->Data.OKDot			=ui->spinBoxOKDot				->value();

		GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		if(PacketReq.Send(D->GlobalPage,0,PacketSend)==true){

			MultiSpectralSendTryThreshold	*R=((MultiSpectralSendTryThreshold *)PacketSend.Data);
				
			//ui->labelResultNGSize		->setText(QString::number(R->ResultNGSize	));
			//ui->labelResultNGSizeUnit	->setText(TransformPixelToUnitSquareStr(R->ResultNGSize		));

			R->Result->SetAlignedXY(0,0);
			DPanel.SetResult(R->Result);
			DPanel.repaint();
			MasterPanel.repaint();
			TargetPanel.repaint();
			break;
		}
	}
	OnChanging=false;
}


//================================================================

GUICmdReqPanelImage::GUICmdReqPanelImage(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqPanelImage::Load(QIODevice *f)
{
	if(f->read((char *)&PanelStructData,sizeof(PanelStructData))!=sizeof(PanelStructData))
		return false;
	return true;
}
bool	GUICmdReqPanelImage::Save(QIODevice *f)
{
	if(f->write((const char *)&PanelStructData,sizeof(PanelStructData))!=sizeof(PanelStructData))
		return false;
	return true;
}

void	GUICmdReqPanelImage::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckPanelImage	*SendBack=GetSendBack(GUICmdAckPanelImage,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	PageDataInOnePhase	*Ph=GetLayersBase()->GetPageDataPhase(PanelStructData.Phase);
	if(Ph!=NULL){
		DataInPage *Dp=Ph->GetPageData(localPage);
		if(Dp!=NULL){
			if(SendBack->TargetImage!=NULL){
				delete	SendBack->TargetImage;
				SendBack->TargetImage=NULL;
			}
			SendBack->TargetImage=new QImage(PanelStructData.GWidth,PanelStructData.GHeight
										 ,QImage::Format_RGB32);
			SendBack->TargetImage->fill(Qt::black);
			ImagePointerContainer Images;
			Dp->GetTargetImages(Images);
			Images.MakeImage(*SendBack->TargetImage 
							 ,PanelStructData.Mx1 ,PanelStructData.My1
							 ,PanelStructData.ZoomRate);
		}
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckPanelImage::GUICmdAckPanelImage(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	TargetImage			=NULL;
}
GUICmdAckPanelImage::~GUICmdAckPanelImage(void)
{
	if(TargetImage!=NULL){
		delete	TargetImage;
		TargetImage=NULL;
	}
}

bool	GUICmdAckPanelImage::Load(QIODevice *f)
{
	int	GWidth	=0;
	int	GHeight	=0;
	if(::Load(f,GWidth)==false)
		return false;
	if(::Load(f,GHeight)==false)
		return false;

	if(GWidth>0 && GHeight>0){
		if(TargetImage!=NULL){
			delete	TargetImage;
			TargetImage=NULL;
		}
		TargetImage=new QImage(GWidth,GHeight,QImage::Format_RGB32);
		if(::Load(f,*TargetImage)==false)
			return false;
	}
	return true;
}
bool	GUICmdAckPanelImage::Save(QIODevice *f)
{
	if(TargetImage!=NULL){
		int	GWidth	=TargetImage->width();
		int	GHeight	=TargetImage->height();
		if(::Save(f,GWidth)==false)
			return false;
		if(::Save(f,GHeight)==false)
			return false;
		if(::Save(f,*TargetImage)==false)
			return false;
	}
	else{
		int	GWidth	=0;
		int	GHeight	=0;
		if(::Save(f,GWidth)==false)
			return false;
		if(::Save(f,GHeight)==false)
			return false;
	}
	return true;
}

//================================================================

GUICmdReqComparedPanelImage::GUICmdReqComparedPanelImage(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqComparedPanelImage::Load(QIODevice *f)
{
	if(f->read((char *)&PanelStructData,sizeof(PanelStructData))!=sizeof(PanelStructData))
		return false;
	return true;
}
bool	GUICmdReqComparedPanelImage::Save(QIODevice *f)
{
	if(f->write((const char *)&PanelStructData,sizeof(PanelStructData))!=sizeof(PanelStructData))
		return false;
	return true;
}

void	GUICmdReqComparedPanelImage::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckComparedPanelImage	*SendBack=GetSendBack(GUICmdAckComparedPanelImage,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	PageDataInOnePhase	*Ph=GetLayersBase()->GetPageDataPhase(PanelStructData.Phase);
	if(Ph!=NULL){
		DataInPage *Dp=Ph->GetPageData(localPage);
		if(Dp!=NULL){
			SendBack->ImageByLayer=new QImage(PanelStructData.GWidth,PanelStructData.GHeight
													,QImage::Format_RGB32);
			SendBack->ImageByLayer->fill(Qt::black);
			DataInLayer	*Ly=Dp->GetLayerData(PanelStructData.CurrentLayer);
			if(Ly!=NULL){
				ImageBuffer *Buff[1];
				if(PanelStructData.Mastered==true)
					Buff[0]=&Ly->GetMasterBuff();
				else
					Buff[0]=&Ly->GetTargetBuff();
				ImageBuffer::MakeImage(*SendBack->ImageByLayer
								,Buff ,1
								,PanelStructData.ZoomRate ,PanelStructData.Mx1 ,PanelStructData.My1
								,255);
			}
		}
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckComparedPanelImage::GUICmdAckComparedPanelImage(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	ImageByLayer	=NULL;
}
GUICmdAckComparedPanelImage::~GUICmdAckComparedPanelImage(void)
{
	if(ImageByLayer!=NULL){
		delete	ImageByLayer;
		ImageByLayer=NULL;
	}
}

bool	GUICmdAckComparedPanelImage::Load(QIODevice *f)
{
	int	GWidth	=0;
	int	GHeight	=0;
	if(::Load(f,GWidth)==false)
		return false;
	if(::Load(f,GHeight)==false)
		return false;

	if(GWidth>0 && GHeight>0){
		if(ImageByLayer!=NULL){
			delete	ImageByLayer;
			ImageByLayer=NULL;
		}
		ImageByLayer=new QImage(GWidth,GHeight,QImage::Format_RGB32);
		if(::Load(f,*ImageByLayer)==false)
			return false;
	}

	return true;
}
bool	GUICmdAckComparedPanelImage::Save(QIODevice *f)
{
	if(ImageByLayer!=NULL){
		int	GWidth	=ImageByLayer->width();
		int	GHeight	=ImageByLayer->height();
		if(::Save(f,GWidth)==false)
			return false;
		if(::Save(f,GHeight)==false)
			return false;
		if(::Save(f,*ImageByLayer)==false)
			return false;
	}
	else{
		int	GWidth	=0;
		int	GHeight	=0;
		if(::Save(f,GWidth)==false)
			return false;
		if(::Save(f,GHeight)==false)
			return false;
	}

	return true;
}
