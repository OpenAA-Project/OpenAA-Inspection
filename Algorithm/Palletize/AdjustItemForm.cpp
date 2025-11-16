#include "AdjustItemForm.h"
#include "ui_AdjustItemForm.h"
#include "XPalletize.h"
#include "XPalletizeLibrary.h"
#include "XDataInLayerCommander.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "swap.h"
#include "MasterPositionDialog.h"

extern	const	char	*sRoot;
extern	const	char	*sName;


DisplayAdjustPanel::DisplayAdjustPanel(LayersBase *base ,AdjustItemForm *p, QWidget *parent)
	:QWidget(parent),ServiceForLayers(base)
	,Parent(p)
{
	ItemID		=-1;
	MovX		=0;
	MovY		=0;
	ZoomRate	=1.0;
	GlobalPage	=0;
	Result		=NULL;
	OldGWidth	=-1;
	OldGHeight	=-1;
	NGResultImage=NULL;
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

	int		RotIndex ,ZoomIndex;
	Parent->GetRotZoomIndex(RotIndex ,ZoomIndex);
	QPainter	Pnt(this);

	GUICmdReqPanelImage	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
	GUICmdAckPanelImage	ACmd(GetLayersBase(),sRoot,sName,GlobalPage);
	RCmd.PanelStructData.Phase		=PhaseCode;
	RCmd.PanelStructData.GWidth		=GWidth	;
	RCmd.PanelStructData.GHeight	=GHeight;
	RCmd.PanelStructData.MovX		=MovX;
	RCmd.PanelStructData.MovY		=MovY;
	RCmd.PanelStructData.ZoomRate	=ZoomRate;
	RCmd.PanelStructData.ItemID		=Parent->GetItemID();
	RCmd.PanelStructData.RotIndex	=RotIndex;
	RCmd.PanelStructData.ZoomIndex	=ZoomIndex;
	QImage	*TargetImage=NULL;
	if(RCmd.Send(GlobalPage,0,ACmd)==true){
		TargetImage=ACmd.TargetImage;
	}

	Pnt.setCompositionMode(QPainter::CompositionMode_SourceOver);
	if(TargetImage!=NULL){
		Pnt.drawImage(0,0,*TargetImage);
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

//===========================================================================
AdjustItemForm::AdjustItemForm(LayersBase *Base,QWidget *parent) :
    QWidget(parent),ServiceForLayers(Base),PasswordInQWodget(Base,this)
	,DPanel(Base,this)
    ,ui(new Ui::AdjustItemForm)
{
    ui->setupUi(this);
	OnChanging	=false;
	InstBase	=NULL;
	IData=NULL;

	DPanel.setParent(ui->frame);
	DPanel.SetAlgo(sRoot,sName);
	DPanel.setGeometry(0,0,ui->frame->width(),ui->frame->height());

	SetupPassword();
	InstallOperationLog(this);
}

AdjustItemForm::~AdjustItemForm()
{
    delete ui;
	if(IData!=NULL)
		delete	IData;
	IData=NULL;
}

void	AdjustItemForm::Initial(AlgorithmBase *_InstBase ,AlgorithmItemIndependentPack &Data)
{
	InstBase	=_InstBase;
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
			PalletizeItem	*BData=dynamic_cast<PalletizeItem *>(DA);
			if(BData!=NULL){
				QBuffer	Buff(&D->Something);
				Buff.open(QIODevice::ReadWrite);
				BData->MasterPositions.Load(&Buff);

				ui->listWidgetZoom->clear();
				GUICmdReqItemInfo	RCmd(GetLayersBase(),sRoot,sName,BData->GetPage());
				GUICmdAckItemInfo	ACmd(GetLayersBase(),sRoot,sName,BData->GetPage());
				RCmd.Phase		=BData->GetPhaseCode();
				RCmd.ItemID		=BData->GetID();
				if(RCmd.Send(BData->GetPage(),0,ACmd)==true){
					for(DoubleClass *d=ACmd.ZoomSizeList.GetFirst();d!=NULL;d=d->GetNext()){
						ui->listWidgetZoom->addItem(QString::number(d->GetValue(),'f',3));
					}
					for(DoubleClass *d=ACmd.RotationList.GetFirst();d!=NULL;d=d->GetNext()){
						ui->listWidgetAngle->addItem(QString::number(d->GetValue()*180/M_PI,'f',3));
					}
				}
				DPanel.GlobalPage	=D->GlobalPage;
				DPanel.PhaseCode	=D->PhaseCode;
				DPanel.ZoomRate		=1.0;
				DPanel.GWidth		=ui->frame->width();
				DPanel.GHeight		=ui->frame->height();
				DPanel.MovX			=-(Data.LocalX-DPanel.GWidth /DPanel.ZoomRate/2);
				DPanel.MovY			=-(Data.LocalY-DPanel.GHeight/DPanel.ZoomRate/2);
				DPanel.show();
			}
		}
	}
	ShowLibrary();
}
int     AdjustItemForm::GetItemID(void)
{
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA!=NULL){
			return DA->GetID();
		}
	}
	return -1;
}
void    AdjustItemForm::GetRotZoomIndex(int &RotIndex ,int &ZoomIndex)
{
	ZoomIndex	=ui->listWidgetZoom	->currentRow();
	RotIndex	=ui->listWidgetAngle->currentRow();
}

void	AdjustItemForm::ShowLibrary(void)
{
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;

		PalletizeItem	*BData=dynamic_cast<PalletizeItem *>(DA);
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

		const	PalletizeThreshold	*d=BData->GetThresholdR(GetLayersBase());

		ui->doubleSpinBoxAngleRange	->setValue(d->AngleRange);
		ui->doubleSpinBoxMinZoomSize->setValue(d->MinZoomSize);
		ui->doubleSpinBoxMaxZoomSize->setValue(d->MaxZoomSize);
		ui->spinBoxPieceSize		->setValue(d->PieceSize);
		ui->spinBoxSearchDotPiece	->setValue(d->SearchDotPiece);
		ui->doubleSpinBoxThresholdV	->setValue(d->ThresholdV);
		ui->spinBoxMaxCountOfPiece	->setValue(d->MaxCountOfPiece);
		ui->doubleSpinBoxThreshCoeff->setValue(d->ThreshCoeff);
		ui->spinBoxSearchNearBy		->setValue(d->SearchNearBy);
		//OnChanging=false;
		SlotStartCalc();
		return;
	}
}
void	AdjustItemForm::GetDataFromWindow(void)
{
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		PalletizeItem	*BData=dynamic_cast<PalletizeItem *>(DA);
		if(BData==NULL)
			continue;

		PalletizeThreshold	*d=BData->GetThresholdW(GetLayersBase());

		d->AngleRange		=ui->doubleSpinBoxAngleRange	->value();
		d->MinZoomSize		=ui->doubleSpinBoxMinZoomSize	->value();
		d->MaxZoomSize		=ui->doubleSpinBoxMaxZoomSize	->value();
		d->PieceSize		=ui->spinBoxPieceSize			->value();
		d->SearchDotPiece	=ui->spinBoxSearchDotPiece		->value();
		d->ThresholdV		=ui->doubleSpinBoxThresholdV	->value();
		d->MaxCountOfPiece	=ui->spinBoxMaxCountOfPiece		->value();
		d->ThreshCoeff		=ui->doubleSpinBoxThreshCoeff	->value();
		d->SearchNearBy		=ui->spinBoxSearchNearBy		->value();
	}
}
void AdjustItemForm::on_listWidgetZoom_itemSelectionChanged()
{
	DPanel.repaint();
}


void AdjustItemForm::on_listWidgetAngle_itemSelectionChanged()
{
	DPanel.repaint();
}


void AdjustItemForm::on_ButtonRelrectOnlyPalletize_clicked()
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


void AdjustItemForm::on_ButtonReflectAllPalletize_clicked()
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


void AdjustItemForm::on_ButtonSaveToLibrary_clicked()
{
	GetDataFromWindow();

	int	ThresholdLevel=GetLayersBase()->SelectThresholdLevel();
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		PalletizeItem	*BData=dynamic_cast<PalletizeItem *>(DA);
		if(BData==NULL)
			continue;

		int	LibID=BData->GetLibID();
		AlgorithmLibraryContainer	*Container=BData->GetLibraryContainer();
		AlgorithmLibraryLevelContainer	DestLib(Container);
		if(Container->GetLibrary(LibID ,DestLib)==true){
			PalletizeLibrary	*ALib=dynamic_cast<PalletizeLibrary *>(DestLib.GetLibrary(ThresholdLevel));
			PalletizeThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
			Thr->ToLibrary(ALib);
			Container->Update(DestLib);
			return;
		}
	}
}


void AdjustItemForm::on_ButtonLoadFromLibrary_clicked()
{
	int	ThresholdLevel=GetLayersBase()->SelectThresholdLevel();
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		PalletizeItem	*BData=dynamic_cast<PalletizeItem *>(DA);
		if(BData==NULL)
			continue;

		int	LibID=BData->GetLibID();
		AlgorithmLibraryContainer	*Container=BData->GetLibraryContainer();
		AlgorithmLibraryLevelContainer	SrcLib(Container);
		if(Container->GetLibrary(LibID ,SrcLib)==true){
			PalletizeLibrary	*ALib=dynamic_cast<PalletizeLibrary *>(SrcLib.GetLibrary(ThresholdLevel));
			PalletizeThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
			Thr->FromLibrary(ALib);
			ShowLibrary();
			return;
		}
	}
}


void AdjustItemForm::on_ButtonClose_clicked()
{
	close();
}


void AdjustItemForm::SlotStartCalc()
{
	//for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
	//	AlgorithmItemRoot	*DA=D->Data;
	//	if(DA==NULL)
	//		continue;
	//	PalletizeItem	*nBData=dynamic_cast<PalletizeItem *>(DA);
	//	if(nBData==NULL)
	//		continue;
	//
	//	GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
	//	PacketReq.BuildData(sRoot,sName,PalletizeReqTryThresholdCommand ,PalletizeSendTryThresholdCommand);
	//	PalletizeItem	*BData=&((PalletizeReqTryThreshold *)PacketReq.Data)->Threshold;
	//	PalletizeThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
	//	Thr->CopyFrom(*nBData->GetThresholdW());
	//	((PalletizeReqTryThreshold *)PacketReq.Data)->Data.GlobalPage	=D->GlobalPage;
	//	((PalletizeReqTryThreshold *)PacketReq.Data)->Data.ItemID		=DA->GetID();
	//
	//
	//	GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
	//	if(PacketReq.Send(D->GlobalPage,0,PacketSend)==true){
	//
	//		PalletizeSendTryThreshold	*R=((PalletizeSendTryThreshold *)PacketSend.Data);
	//
	//		R->Result->SetAlignedXY(0,0);
	//
	//		break;
	//	}
	//}	
}

void AdjustItemForm::on_pushButtonMasterPosition_clicked()
{
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;

		PalletizeItem	*BData=dynamic_cast<PalletizeItem *>(DA);
		if(BData==NULL)
			continue;
		MasterPositionDialog	Dg(BData->MasterPositions);
		if(Dg.exec()==true){
			BData->MasterPositions=Dg.MasterPositions;
			GUICmdSendMasterPositions	RCmd(GetLayersBase(),sRoot,sName,BData->GetPage());
			RCmd.Phase		=0;
			RCmd.ItemID		=BData->GetID();
			RCmd.MasterPositions	=Dg.MasterPositions;
			RCmd.Send(NULL,BData->GetPage(),0);
		}
	}
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

	if(SendBack->TargetImage!=NULL){
		delete	SendBack->TargetImage;
		SendBack->TargetImage=NULL;
	}
	SendBack->TargetImage=new QImage(PanelStructData.GWidth,PanelStructData.GHeight
								 ,QImage::Format_RGB32);
	SendBack->TargetImage->fill(Qt::black);

	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(sRoot,sName);
	if(ABase!=NULL){
		AlgorithmInPageInOnePhase	*Ah=ABase->GetPageDataPhase(PanelStructData.Phase);
		if(Ah!=NULL){
			PalletizeInPage	*Ap=(PalletizeInPage *)Ah->GetPageData(localPage);
			if(Ap!=NULL){
				PalletizeItem	*AItem=Ap->tGetItemData(PanelStructData.ItemID);
				if(AItem!=NULL){
					RotatedMatchingPattern	*R=AItem->GetRotPattern(PanelStructData.RotIndex ,PanelStructData.ZoomIndex);
					if(R!=NULL){
						R->Draw(*SendBack->TargetImage
								,PanelStructData.MovX ,PanelStructData.MovY ,PanelStructData.ZoomRate);
					}
				}
			}
		}
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckPanelImage::GUICmdAckPanelImage(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	TargetImage=NULL;
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



GUICmdReqItemInfo::GUICmdReqItemInfo(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqItemInfo::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	return true;
}
bool	GUICmdReqItemInfo::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	return true;
}

void	GUICmdReqItemInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckItemInfo	*SendBack=GetSendBack(GUICmdAckItemInfo,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(sRoot,sName);
	if(ABase!=NULL){
		AlgorithmInPageInOnePhase	*Ah=ABase->GetPageDataPhase(Phase);
		if(Ah!=NULL){
			PalletizeInPage	*Ap=(PalletizeInPage *)Ah->GetPageData(localPage);
			if(Ap!=NULL){
				PalletizeItem	*AItem=Ap->tGetItemData(ItemID);
				if(AItem!=NULL){
					int	SN=AItem->GetCountZoomSize();
					int	RN=AItem->GetCountRotation();
					if(SN!=0 && RN!=0){
						for(int i=0;i<SN;i++){
							RotatedMatchingPattern	*R=AItem->GetRotPattern(0 ,i);
							SendBack->ZoomSizeList.Add(R->ZoomSize);
						}
						for(int i=0;i<RN;i++){
							RotatedMatchingPattern	*R=AItem->GetRotPattern(i ,0);
							SendBack->RotationList.Add(R->Radian);
						}
					}
				}
			}
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckItemInfo::GUICmdAckItemInfo(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckItemInfo::Load(QIODevice *f)
{
	if(ZoomSizeList.Load(f)==false)
		return false;
	if(RotationList.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdAckItemInfo::Save(QIODevice *f)
{
	if(ZoomSizeList.Save(f)==false)
		return false;
	if(RotationList.Save(f)==false)
		return false;
	return true;
}


GUICmdSendMasterPositions::GUICmdSendMasterPositions(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendMasterPositions::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(MasterPositions.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendMasterPositions::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(MasterPositions.Save(f)==false)
		return false;
	return true;
}

void	GUICmdSendMasterPositions::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(sRoot,sName);
	if(ABase!=NULL){
		AlgorithmInPageInOnePhase	*Ah=ABase->GetPageDataPhase(Phase);
		if(Ah!=NULL){
			PalletizeInPage	*Ap=(PalletizeInPage *)Ah->GetPageData(localPage);
			if(Ap!=NULL){
				PalletizeItem	*AItem=Ap->tGetItemData(ItemID);
				if(AItem!=NULL){
					AItem->MasterPositions=MasterPositions;
				}
			}
		}
	}
}