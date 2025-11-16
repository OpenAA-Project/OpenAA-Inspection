#include "BuslineInspectionResource.h"
#include "ShowOperationalPanel.h"
#include "ui_ShowOperationalPanel.h"
#include "XBuslineInspection.h"
#include "XDataInLayerCommander.h"
#include "XDisplayBitImage.h"
#include "XLibraryType.h"
#include "XGeneralFunc.h"
#include "swap.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

DisplaySimPanelBusLine::DisplaySimPanelBusLine(LayersBase* base, QWidget* parent)
	:DisplaySimPanel(base, parent)
{
	BMapOpen	=NULL;
	BMapShort	=NULL;
	BMapBinary	=NULL;
	BMapXByte	=0;
	BMapYLen	=0;
	MapXPos		=0;
	MapYPos		=0;
	ModeShowMapOpen		=true;
	ModeShowMapShort	=true;
	ModeShowMapBinary	=false;
	ResultImageOpen		=NULL;
	ResultImageShort	=NULL;
	ResultImageBinary	=NULL;
}
DisplaySimPanelBusLine::~DisplaySimPanelBusLine(void)
{
	if (BMapOpen != NULL) {
		DeleteMatrixBuff(BMapOpen, BMapYLen);
		BMapOpen = NULL;
	}
	if (BMapShort != NULL) {
		DeleteMatrixBuff(BMapShort, BMapYLen);
		BMapShort = NULL;
	}
	if (BMapBinary != NULL) {
		DeleteMatrixBuff(BMapBinary, BMapYLen);
		BMapBinary = NULL;
	}
	BMapXByte = 0;
	BMapYLen = 0;
	MapXPos = 0;
	MapYPos = 0;

	if (ResultImageOpen != NULL) {
		delete	ResultImageOpen;
		ResultImageOpen=NULL;
	}
	if (ResultImageShort != NULL) {
		delete	ResultImageShort;
		ResultImageShort = NULL;
	}
	if (ResultImageBinary != NULL) {
		delete	ResultImageBinary;
		ResultImageBinary = NULL;
	}
}

void	DisplaySimPanelBusLine::SetInitial(int ItemID, FlexArea& InitialArea)
{
	DisplaySimPanel::SetInitial(ItemID, InitialArea);
	if (ResultImageOpen != NULL) {
		delete	ResultImageOpen;
	}
	ResultImageOpen = new QImage(width(), height(), QImage::Format_ARGB32);

	if (ResultImageShort != NULL) {
		delete	ResultImageShort;
	}
	ResultImageShort = new QImage(width(), height(), QImage::Format_ARGB32);

	if (ResultImageBinary != NULL) {
		delete	ResultImageBinary;
	}
	ResultImageBinary = new QImage(width(), height(), QImage::Format_ARGB32);
}

void	DisplaySimPanelBusLine::CopyMap(BYTE** MapOpen, BYTE** MapShort, BYTE** MapBinary, int XByte, int YLen
	, int XPos, int YPos)
{
	if (BMapOpen != NULL) {
		DeleteMatrixBuff(BMapOpen, BMapYLen);
		BMapOpen = NULL;
	}
	if (BMapShort != NULL) {
		DeleteMatrixBuff(BMapShort, BMapYLen);
		BMapShort = NULL;
	}
	if (BMapBinary != NULL) {
		DeleteMatrixBuff(BMapBinary, BMapYLen);
		BMapBinary = NULL;
	}
	BMapXByte	=XByte;
	BMapYLen	=YLen;
	MapXPos		=XPos;
	MapYPos		=YPos;

	BMapOpen = MakeMatrixBuff(BMapXByte, BMapYLen);
	BMapShort = MakeMatrixBuff(BMapXByte, BMapYLen);
	BMapBinary = MakeMatrixBuff(BMapXByte, BMapYLen);

	::MatrixBuffCopy(BMapOpen, BMapXByte, BMapYLen
					, (const BYTE **)MapOpen, XByte, YLen);
	::MatrixBuffCopy(BMapShort, BMapXByte, BMapYLen
					, (const BYTE**)MapShort, XByte, YLen);
	::MatrixBuffCopy(BMapBinary, BMapXByte, BMapYLen
					, (const BYTE**)MapBinary, XByte, YLen);
}

void	DisplaySimPanelBusLine::SetModeMap(bool _ModeShowMapOpen, bool _ModeShowMapShort, bool _ModeShowMapBinary)
{
	ModeShowMapOpen		=_ModeShowMapOpen;
	ModeShowMapShort	=_ModeShowMapShort;
	ModeShowMapBinary	=_ModeShowMapBinary;
	repaint();
}

void	DisplaySimPanelBusLine::PaintAfter(QPainter& pnt)
{
	if(ModeShowMapOpen==true){
		const QColor	ColOpen=QColor(255,255,0,128);
		ResultImageOpen->fill(0);
		::DrawBitImage(*ResultImageOpen, (const BYTE **)BMapOpen, BMapXByte*8, BMapXByte, BMapYLen
					, MovX, MovY, ZoomRate
					, MapXPos, MapYPos
					, ColOpen);
		pnt.drawImage(0, 0, *ResultImageOpen);
	}
	if (ModeShowMapShort == true) {
		const QColor	ColShort = QColor(0, 255, 255, 128);
		ResultImageShort->fill(0);
		::DrawBitImage(*ResultImageShort, (const BYTE**)BMapShort, BMapXByte * 8, BMapXByte, BMapYLen
			, MovX, MovY, ZoomRate
			, MapXPos, MapYPos
			, ColShort);
		pnt.drawImage(0, 0, *ResultImageShort);
	}
	if (ModeShowMapBinary == true) {
		const QColor	ColBinary = QColor(255, 0, 255, 128);
		ResultImageBinary->fill(0);
		::DrawBitImage(*ResultImageBinary, (const BYTE**)BMapBinary, BMapXByte * 8, BMapXByte, BMapYLen
			, MovX, MovY, ZoomRate
			, MapXPos, MapYPos
			, ColBinary);
		pnt.drawImage(0, 0, *ResultImageBinary);
	}
}

//==========================================================================================================

ShowOperationalPanel::ShowOperationalPanel(LayersBase *Base,QWidget *parent) :
    QWidget(parent),ServiceForLayers(Base),PasswordInQWodget(Base,this),
    ui(new Ui::ShowOperationalPanel)
	,SimPanel(Base,parent)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	SimPanel.setParent(ui->frame_SimImage);
	SimPanel.SetAlgo(/**/"Basic",/**/"Busline");
	SimPanel.SetGUI(/**/"Button",/**/"PropertyBusline");
	SimPanel.setGeometry(0, 0, ui->frame_SimImage->width(), ui->frame_SimImage->height());
	OnChanging = true;

	IData=NULL;
	InstallOperationLog(this);
}

ShowOperationalPanel::~ShowOperationalPanel()
{
	if(IData!=NULL)
		delete	IData;
	IData=NULL;

    delete ui;
}

void	ShowOperationalPanel::Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data)
{
	AlgorithmLibraryContainerForEnum		LibList(InstBase->GetLayersBase());
	LibIDList.RemoveAll();
	LibList.EnumAllLibraries(GetLayersBase()->GetDatabase(),InstBase->GetLibType(),LibIDList);
	OnChanging = true;

	if(IData!=NULL)
		delete	IData;
	IData=new AlgorithmItemIndependentPack(InstBase->GetLayersBase());
	*IData=Data;

	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		SimPanel.SetLayer(D->Layer);
		AlgorithmItemRoot	*DA=D->Data;
		if(DA!=NULL){
			BuslineItem	*BData=dynamic_cast<BuslineItem *>(DA);
			if(BData!=NULL){
				SimPanel.SetGlobalPage(D->GlobalPage);
				SimPanel.SetInitial(BData->GetID(),BData->GetArea());
				//SimPanel.SetModeShowBlock		(ui->toolButtonSimShowBlock ->isChecked());
				SimPanel.SetModeShowBrightnessNG(false);

				SimPanel.SetModeMap(  ui->toolButtonSimShowOpen->isChecked()
									, ui->toolButtonSimShowShort->isChecked()
									, ui->toolButtonSimShowBinary->isChecked());
			}
		}
	}
	CreateThreshld();
	OnChanging = false;
	on_pushButtonCalc_clicked();
}

void	ShowOperationalPanel::CreateThreshld(void)
{
	IntList LayerList;
	//GetActiveLayerList(LayerList);
	//if(LayerList.GetFirst()==NULL)
	//	return;
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		//if(LayerList.GetFirst()->GetValue()!=D->Layer)
		//	continue;
		BuslineItem	*BData=dynamic_cast<BuslineItem *>(DA);
		if(BData==NULL)
			continue;
		GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.BuildData(sRoot,sName,BuslineReqThresholdReqCommand ,BuslineReqThresholdSendCommand);
		((BuslineThresholdReq *)PacketReq.Data)->GlobalPage	=D->GlobalPage;
		((BuslineThresholdReq *)PacketReq.Data)->Layer		=D->Layer;
		((BuslineThresholdReq *)PacketReq.Data)->ItemID	=DA->GetID();
		((BuslineThresholdReq *)PacketReq.Data)->Mastered=true;
		GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		if(PacketReq.Send(D->GlobalPage,0,PacketSend)==true){

			BuslineThresholdSend	*ThrePoint=(BuslineThresholdSend *)PacketSend.GetData();
			MinWidth			=ThrePoint->MinWidth;
			MinGap				=ThrePoint->MinGap;
			MinArea				=ThrePoint->MinArea;
			MaxArea				=ThrePoint->MaxArea;
			MinSize				=ThrePoint->MinSize;
			Darkside			=ThrePoint->Darkside;
			CompareToMaster		=ThrePoint->CompareToMaster;		
			AutoBinarize		=ThrePoint->AutoBinarize;
			ReduceNoise			=ThrePoint->ReduceNoise;
			BinarizedLength		=ThrePoint->BinarizedLength;
			ReferredBrightness	=ThrePoint->ReferredBrightness;		
			SearchDotToMaster	=ThrePoint->SearchDotToMaster;	
			WidthToIgnoreEdge	=ThrePoint->WidthToIgnoreEdge;	
			OKNickRate			=ThrePoint->OKNickRate;	
			OKShortRate			=ThrePoint->OKShortRate;
			BrightnessWidthInsideL =ThrePoint->BrightnessWidthInsideL ;	
			BrightnessWidthInsideH =ThrePoint->BrightnessWidthInsideH ;	
			BrightnessWidthOutsideL=ThrePoint->BrightnessWidthOutsideL;	
			BrightnessWidthOutsideH=ThrePoint->BrightnessWidthOutsideH;	
			break;
		}
	}
	ShowLibrary();
}


void	ShowOperationalPanel::ShowLibrary(void)
{
	IntList LayerList;
	//GetActiveLayerList(LayerList);
	//if(LayerList.GetFirst()==NULL)
	//	return;
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		//if(LayerList.GetFirst()->GetValue()!=D->Layer)
		//	continue;
		BuslineItem	*BData=dynamic_cast<BuslineItem *>(DA);
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
		ui->EditMinWidth			->setValue	(BData->GetThresholdR(GetLayersBase())->MinWidth);
		ui->EditMinGap				->setValue	(BData->GetThresholdR(GetLayersBase())->MinGap);
		ui->lineEditMinArea			->setText	(QString::number(BData->GetThresholdR(GetLayersBase())->MinArea));
		ui->lineEditMaxArea			->setText	(QString::number(BData->GetThresholdR(GetLayersBase())->MaxArea));
		ui->EditMinSize				->setValue	(BData->GetThresholdR(GetLayersBase())->MinSize);
		ui->checkBoxDarkside		->setChecked(BData->GetThresholdR(GetLayersBase())->Darkside);
		ui->checkBoxCompareToMaster	->setChecked(BData->GetThresholdR(GetLayersBase())->CompareToMaster);
		ui->checkBoxAutoBinarize	->setChecked(BData->GetThresholdR(GetLayersBase())->AutoBinarize);
		ui->checkBoxReduceNoise		->setChecked(BData->GetThresholdR(GetLayersBase())->ReduceNoise);
		ui->EditBinarizedLength		->setValue	(BData->GetThresholdR(GetLayersBase())->BinarizedLength);
		ui->EditReferredBrightness	->setValue	(BData->GetThresholdR(GetLayersBase())->ReferredBrightness);
		ui->EditSearchDotToMaster	->setValue	(BData->GetThresholdR(GetLayersBase())->SearchDotToMaster);
		ui->EditWidthToIgnoreEdge	->setValue	(BData->GetThresholdR(GetLayersBase())->WidthToIgnoreEdge);
		ui->EditOKNickRate			->setValue	(BData->GetThresholdR(GetLayersBase())->OKNickRate);
		ui->EditOKShortRate			->setValue	(BData->GetThresholdR(GetLayersBase())->OKShortRate);
		ui->EditBrightnessWidthInsideL ->setValue	(BData->GetThresholdR(GetLayersBase())->BrightnessWidthInsideL );
		ui->EditBrightnessWidthInsideH ->setValue	(BData->GetThresholdR(GetLayersBase())->BrightnessWidthInsideH );
		ui->EditBrightnessWidthOutsideL->setValue	(BData->GetThresholdR(GetLayersBase())->BrightnessWidthOutsideL);
		ui->EditBrightnessWidthOutsideH->setValue	(BData->GetThresholdR(GetLayersBase())->BrightnessWidthOutsideH);

		int32		PeakH=0,PeakL=0;
		int32		ThresholdBrightness=0;
		bool	Ret=false;
		QBuffer	Buff(&D->Something);
		if(Buff.open(QIODevice::ReadOnly)==true){
			if(::Load(&Buff,ThresholdBrightness)==true){
				if(::Load(&Buff,PeakL)==true){
					if(::Load(&Buff,PeakH)==true){
						ui->labelPeakL				->setText(QString::number(PeakL));
						ui->labelThresholdBrightness->setText(QString::number(ThresholdBrightness));
						ui->labelPeakH				->setText(QString::number(PeakH));
						Ret=true;
					}
				}
			}
		}
		if(Ret==false){
			ui->labelPeakL				->setText(/**/"");
			ui->labelThresholdBrightness->setText(/**/"");
			ui->labelPeakH				->setText(/**/"");
		}

		return;
	}
}
void	ShowOperationalPanel::GetDataFromWindow(void)
{
	IntList LayerList;
	//GetActiveLayerList(LayerList);
	//if(LayerList.GetFirst()==NULL)
	//	return;

	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		BuslineItem	*BData=dynamic_cast<BuslineItem *>(DA);
		if(BData==NULL)
			continue;
		BuslineThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		Thr->MinWidth				=ui->EditMinWidth				->value();
		Thr->MinGap					=ui->EditMinGap					->value();
		Thr->MinArea				=ui->lineEditMinArea			->text().toLongLong();
		Thr->MaxArea				=ui->lineEditMaxArea			->text().toLongLong();
		Thr->MinSize				=ui->EditMinSize				->value();
		Thr->Darkside				=ui->checkBoxDarkside			->isChecked();
		Thr->CompareToMaster		=ui->checkBoxCompareToMaster	->isChecked();
		Thr->AutoBinarize			=ui->checkBoxAutoBinarize		->isChecked();
		Thr->ReduceNoise			=ui->checkBoxReduceNoise		->isChecked();
		Thr->BinarizedLength		=ui->EditBinarizedLength		->value();
		Thr->ReferredBrightness		=ui->EditReferredBrightness		->value();
		Thr->SearchDotToMaster		=ui->EditSearchDotToMaster		->value();
		Thr->WidthToIgnoreEdge		=ui->EditWidthToIgnoreEdge		->value();
		Thr->OKNickRate				=ui->EditOKNickRate				->value();
		Thr->OKShortRate			=ui->EditOKShortRate			->value();
		Thr->BrightnessWidthInsideL =ui->EditBrightnessWidthInsideL ->value();
		Thr->BrightnessWidthInsideH =ui->EditBrightnessWidthInsideH ->value();
		Thr->BrightnessWidthOutsideL=ui->EditBrightnessWidthOutsideL->value();
		Thr->BrightnessWidthOutsideH=ui->EditBrightnessWidthOutsideH->value();

		//return;
	}
}

void ShowOperationalPanel::on_ButtonRelrectOnlyBlock_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(ShowOperationalPanel_LS,LID_6)/*"Reflecting ONE block threshold"*/);

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

void ShowOperationalPanel::on_ButtonSaveToLibrary_clicked()
{
	GetDataFromWindow();
	int	ThresholdLevel=GetLayersBase()->SelectThresholdLevel();

	IntList LayerList;
	//GetActiveLayerList(LayerList);
	//if(LayerList.GetFirst()==NULL)
	//	return;
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		BuslineItem	*BData=dynamic_cast<BuslineItem *>(DA);
		if(BData==NULL)
			continue;

		int	LibID=BData->GetLibID();
		AlgorithmLibraryContainer	*Container=BData->GetLibraryContainer();
		AlgorithmLibraryLevelContainer	DestLib(Container);
		if(Container->GetLibrary(LibID ,DestLib)==true){
			BuslineLibrary	*ALib=dynamic_cast<BuslineLibrary *>(DestLib.GetLibrary(ThresholdLevel));
			BuslineThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
			Thr->ToLibrary(ALib);
			BData->GetLibraryContainer()->Update(DestLib);
			return;
		}
	}
}

void ShowOperationalPanel::on_ButtonLoadFromLibrary_clicked()
{
	int	ThresholdLevel=GetLayersBase()->SelectThresholdLevel();
	IntList LayerList;
	//GetActiveLayerList(LayerList);
	//if(LayerList.GetFirst()==NULL)
	//	return;
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		BuslineItem	*BData=dynamic_cast<BuslineItem *>(DA);
		if(BData==NULL)
			continue;

		int	LibID=BData->GetLibID();
		AlgorithmLibraryContainer	*Container=BData->GetLibraryContainer();
		AlgorithmLibraryLevelContainer	SrcLib(Container);
		if(Container->GetLibrary(LibID ,SrcLib)==true){
			BuslineLibrary	*ALib=dynamic_cast<BuslineLibrary *>(SrcLib.GetLibrary(ThresholdLevel));
			BuslineThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
			Thr->FromLibrary(ALib);
			ShowLibrary();
			return;
		}
	}
}

void ShowOperationalPanel::on_ButtonReflectAllBlocks_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(ShowOperationalPanel_LS,LID_7)/*"Reflecting ALL blocks\' threshold"*/);

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

void ShowOperationalPanel::on_ButtonClose_clicked()
{
	close();
}

void ShowOperationalPanel::on_pushButtonCalc_clicked()
{
	for (AlgorithmItemIndependent* D = IData->Items.GetFirst(); D != NULL; D = D->GetNext()) {
		AlgorithmItemRoot* DA = D->Data;
		if (DA == NULL)
			continue;

		BuslineItem* nBData = dynamic_cast<BuslineItem*>(DA);
		if (nBData == NULL)
			continue;

		GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY", D->GlobalPage);
		PacketReq.BuildData(sRoot, sName, BuslineReqTryThresholdCommand, BuslineSendTryThresholdCommand);
		BuslineItem* BData = &((BuslineReqTryThreshold*)PacketReq.Data)->Threshold;
		((BuslineReqTryThreshold*)PacketReq.Data)->GlobalPage	= D->GlobalPage;
		((BuslineReqTryThreshold*)PacketReq.Data)->Layer		= D->Layer;
		((BuslineReqTryThreshold*)PacketReq.Data)->ItemID		= DA->GetID();

		BuslineThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		Thr->MinWidth				= ui->EditMinWidth				->value();
		Thr->MinGap					= ui->EditMinGap				->value();
		Thr->MinArea				= ui->lineEditMinArea			->text().toLongLong();
		Thr->MaxArea				= ui->lineEditMaxArea			->text().toLongLong();
		Thr->MinSize				= ui->EditMinSize				->value();
		Thr->Darkside				= ui->checkBoxDarkside			->isChecked();
		Thr->CompareToMaster		= ui->checkBoxCompareToMaster	->isChecked();
		Thr->AutoBinarize			= ui->checkBoxAutoBinarize		->isChecked();
		Thr->ReduceNoise			= ui->checkBoxReduceNoise		->isChecked();
		Thr->BinarizedLength		= ui->EditBinarizedLength		->value();
		Thr->ReferredBrightness		= ui->EditReferredBrightness	->value();
		Thr->SearchDotToMaster		= ui->EditSearchDotToMaster		->value();
		Thr->WidthToIgnoreEdge		= ui->EditWidthToIgnoreEdge		->value();
		Thr->OKNickRate				= ui->EditOKNickRate			->value();
		Thr->OKShortRate			= ui->EditOKShortRate			->value();
		Thr->BrightnessWidthInsideL	= ui->EditBrightnessWidthInsideL->value();
		Thr->BrightnessWidthInsideH	= ui->EditBrightnessWidthInsideH->value();
		Thr->BrightnessWidthOutsideL= ui->EditBrightnessWidthOutsideL->value();
		Thr->BrightnessWidthOutsideH= ui->EditBrightnessWidthOutsideH->value();

		GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY", D->GlobalPage);
		if (PacketReq.Send(D->GlobalPage, 0, PacketSend) == true) {

			BuslineSendTryThreshold* R = ((BuslineSendTryThreshold*)PacketSend.Data);
			SimPanel.SetResult(R->Result);
			ui->labelResultNGOpen	->setText(QString::number(R->NGDotOpen));
			ui->labelResultNGShort	->setText(QString::number(R->NGDotShort));

			SimPanel.CopyMap(R->BMapOpen, R->BMapShort, R->BMapBinary, R->BMapXByte, R->BMapYLen
					,		-DA->GetArea().GetMinX() + BuslineAreaMergin, -DA->GetArea().GetMinY() + BuslineAreaMergin);
			SimPanel.repaint();
			break;
		}
	}
}

void ShowOperationalPanel::on_checkBoxDarkside_clicked()
{
	if (OnChanging == true) {
		return;
	}
	on_pushButtonCalc_clicked();
}

void ShowOperationalPanel::on_checkBoxCompareToMaster_clicked()
{
	if (OnChanging == true) {
		return;
	}
	on_pushButtonCalc_clicked();
}

void ShowOperationalPanel::on_checkBoxReduceNoise_clicked()
{
	if (OnChanging == true) {
		return;
	}
	on_pushButtonCalc_clicked();
}

void ShowOperationalPanel::on_EditBinarizedLength_valueChanged(int arg1)
{
	if (OnChanging == true) {
		return;
	}
	on_pushButtonCalc_clicked();
}

void ShowOperationalPanel::on_EditReferredBrightness_valueChanged(int arg1)
{
	if (OnChanging == true) {
		return;
	}
	on_pushButtonCalc_clicked();
}

void ShowOperationalPanel::on_checkBoxAutoBinarize_clicked()
{
	if (OnChanging == true) {
		return;
	}
	on_pushButtonCalc_clicked();
}

void ShowOperationalPanel::on_EditSearchDotToMaster_valueChanged(int arg1)
{
	if (OnChanging == true) {
		return;
	}
	on_pushButtonCalc_clicked();
}

void ShowOperationalPanel::on_EditMinWidth_valueChanged(int arg1)
{
	if (OnChanging == true) {
		return;
	}
	on_pushButtonCalc_clicked();
}

void ShowOperationalPanel::on_EditMinGap_valueChanged(int arg1)
{
	if (OnChanging == true) {
		return;
	}
	on_pushButtonCalc_clicked();
}

void ShowOperationalPanel::on_EditOKNickRate_valueChanged(int arg1)
{
	if (OnChanging == true) {
		return;
	}
	on_pushButtonCalc_clicked();
}

void ShowOperationalPanel::on_EditOKShortRate_valueChanged(int arg1)
{
	if (OnChanging == true) {
		return;
	}
	on_pushButtonCalc_clicked();
}
void ShowOperationalPanel::on_EditMinSize_valueChanged(int arg1)
{
	if (OnChanging == true) {
		return;
	}
	on_pushButtonCalc_clicked();
}
void ShowOperationalPanel::on_toolButtonSimShowOpen_clicked()
{
	SimPanel.SetModeMap( ui->toolButtonSimShowOpen->isChecked()
						,ui->toolButtonSimShowShort->isChecked()
						,ui->toolButtonSimShowBinary->isChecked());
}

void ShowOperationalPanel::on_toolButtonSimShowShort_clicked()
{
	SimPanel.SetModeMap(  ui->toolButtonSimShowOpen->isChecked()
						, ui->toolButtonSimShowShort->isChecked()
						, ui->toolButtonSimShowBinary->isChecked());
}

void ShowOperationalPanel::on_toolButtonSimShowBinary_clicked()
{
	SimPanel.SetModeMap(  ui->toolButtonSimShowOpen->isChecked()
						, ui->toolButtonSimShowShort->isChecked()
						, ui->toolButtonSimShowBinary->isChecked());

}

void ShowOperationalPanel::on_pushButtonSimShowCenterPos_clicked()
{
	for (AlgorithmItemIndependent* D = IData->Items.GetFirst(); D != NULL; D = D->GetNext()) {
		AlgorithmItemRoot* DA = D->Data;
		if (DA != NULL) {
			SimPanel.SetInitial(DA->GetID(), DA->GetArea());
			SimPanel.repaint();
		}
	}
}


