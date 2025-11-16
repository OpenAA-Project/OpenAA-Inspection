#include "SetThresholdForm.h"
#include "ui_SetThresholdForm.h"
#include "XMatchShiftRotation.h"
#include "XGeneralDialog.h"
#include "XDataInLayer.h"
#include "XDataInLayerCommander.h"
#include <QToolButton>

extern	const	char	*sRoot;
extern	const	char	*sName;

SetThresholdForm::SetThresholdForm(LayersBase *Base,QWidget *parent) :
    QWidget(parent),ServiceForLayers(Base),PasswordInQWodget(Base,this),
    ui(new Ui::SetThresholdForm)
{
    ui->setupUi(this);
	//LangSolver.SetUI(this);

	connect(this,SIGNAL(SignalStartCalc()),this,SLOT(SlotStartCalc()),Qt::QueuedConnection);
	LayerBar.setParent(ui->frameLayer);
	LayerBar.move(0,0);
	LayerBar.resize(ui->frameLayer->width(),ui->frameLayer->height());
	LButtonList	=NULL;
	Page		=-1;
	IData=NULL;

	ui->labelResultDx			->setText(/**/"");
	ui->labelResultDy			->setText(/**/"");
	ui->labelResultAngle		->setText(/**/"");
	ui->labelResultMatchingRate	->setText(/**/"");
								
	ui->labelResultDxUnit		->setText(/**/"");
	ui->labelResultDyUnit		->setText(/**/"");

}

SetThresholdForm::~SetThresholdForm()
{
    delete ui;
	if(IData!=NULL)
		delete	IData;
	IData=NULL;
	if(LButtonList!=NULL){
		delete	[]LButtonList;
		LButtonList=NULL;
	}
}
void	SetThresholdForm::GetActiveLayerList(IntList &LayerList)
{
	if(0<=Page && LButtonList!=NULL){
		for(int Layer=0;Layer<GetLayerNumb(Page);Layer++){
			if(LButtonList[Layer]->isChecked()==true){
				LayerList.Add(Layer);
			}
		}
	}
}
void	SetThresholdForm::Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data)
{
	AlgorithmLibraryContainerForEnum		LibList(InstBase->GetLayersBase());
	LibIDList.RemoveAll();
	LibList.EnumAllLibraries(GetLayersBase()->GetDatabase(),InstBase->GetLibType(),LibIDList);

	if(IData!=NULL)
		delete	IData;
	IData=new AlgorithmItemIndependentPack(InstBase->GetLayersBase());
	*IData=Data;
	//ui->pushButtonRestore->setEnabled(false);
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		Page=D->GlobalPage;
		LButtonList=new QToolButton*[GetLayerNumb(Page)];
		LastLayer=0;
		for(int Layer=0;Layer<GetLayerNumb(Page);Layer++){
			LButtonList[Layer]=new QToolButton();
			LButtonList[Layer]->setText(QString("Ly")+QString::number(Layer));
			LButtonList[Layer]->setAutoExclusive(true);
			LButtonList[Layer]->setCheckable(true);
			LButtonList[Layer]->setAutoRaise(true);
			if(Layer==0)
				LButtonList[Layer]->setChecked(true);
			else
				LButtonList[Layer]->setChecked(false);
			LButtonList[Layer]->resize(48,32);
			LayerBar.addWidget(LButtonList[Layer]);
			connect(LButtonList[Layer],SIGNAL(clicked()),this,SLOT(SlotLayerClicked()));
		}
		LButtonList[D->Layer]->setChecked(true);
	}

	CreateThreshld();
}

void	SetThresholdForm::CreateThreshld(void)
{
	IntList LayerList;
	GetActiveLayerList(LayerList);
	if(LayerList.GetFirst()==NULL)
		return;
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		if(LayerList.GetFirst()->GetValue()!=D->Layer)
			continue;
		MatchShiftRotationItem	*BData=dynamic_cast<MatchShiftRotationItem *>(DA);
		if(BData==NULL)
			continue;
		GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.BuildData(sRoot,sName,MatchShiftRotationReqThresholdReqCommand ,MatchShiftRotationReqThresholdSendCommand);
		((MatchShiftRotationThresholdReq *)PacketReq.Data)->GlobalPage	=D->GlobalPage;
		((MatchShiftRotationThresholdReq *)PacketReq.Data)->ItemID		=DA->GetID();
		((MatchShiftRotationThresholdReq *)PacketReq.Data)->Mastered=true;
		GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		if(PacketReq.Send(D->GlobalPage,0,PacketSend)==true){

			MatchShiftRotationThresholdSend	*ThrePoint=(MatchShiftRotationThresholdSend *)PacketSend.GetData();
			SearchArea			=ThrePoint->SearchArea	;
			SearchAngle			=ThrePoint->SearchAngle	;
			TargetLayer			=ThrePoint->TargetLayer	;
			SearchLittleInItem	=ThrePoint->SearchLittleInItem	;
			MatchingRate		=ThrePoint->MatchingRate;		
			break;
		}
	}
	ShowLibrary();
}

void	SetThresholdForm::ShowLibrary(void)
{
	IntList LayerList;
	GetActiveLayerList(LayerList);
	if(LayerList.GetFirst()==NULL)
		return;
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		if(LayerList.GetFirst()->GetValue()!=D->Layer)
			continue;
		MatchShiftRotationItem	*BData=dynamic_cast<MatchShiftRotationItem *>(DA);
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
		QBuffer	Buff(&D->Something);
		if(Buff.open(QIODevice::ReadOnly)==true){
			WORD		AreaID;
			int32		SearchArea;	
			int32		SearchAngle;
			if(::Load(&Buff,AreaID)==true){
				if(::Load(&Buff,SearchArea)==true){
					if(::Load(&Buff,SearchAngle)==true){		
						ui->spinBoxGlobalSearchDot		->setValue(SearchArea);
						ui->EditSearchAngle				->setValue(SearchAngle);
					}
				}
			}
		}
		ui->spinBoxSearchLittleInItem	->setValue(BData->GetThresholdR(GetLayersBase())->SearchLittleInItem	);
		ui->doubleSpinBoxMatchingRate	->setValue(BData->GetThresholdR(GetLayersBase())->MatchingRate);

		return;
	}
}

void	SetThresholdForm::GetDataFromWindow(void)
{
	IntList LayerList;
	GetActiveLayerList(LayerList);
	if(LayerList.GetFirst()==NULL)
		return;
	GetDataFromWindowFromNo(LayerList.GetFirst()->GetValue());
}
void	SetThresholdForm::GetDataFromWindowFromNo(int LayerNo)
{
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		if(LayerNo!=D->Layer)
			continue;
		MatchShiftRotationItem	*BData=dynamic_cast<MatchShiftRotationItem *>(DA);
		if(BData==NULL)
			continue;
		MatchShiftRotationThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		BData->SetItemName(ui->EditItemName	->text());

		Thr->SearchLittleInItem	=ui->spinBoxSearchLittleInItem	->value();
		Thr->MatchingRate		=ui->doubleSpinBoxMatchingRate	->value();

		int32		SearchArea	=ui->spinBoxGlobalSearchDot	->value();	
		int32		SearchAngle	=ui->EditSearchAngle		->value();
		QBuffer	Buff;
		Buff.open(QIODevice::WriteOnly);
		::Save(&Buff,BData->AreaID);
		::Save(&Buff,SearchArea);
		::Save(&Buff,SearchAngle);

		D->Something=Buff.buffer();

		//return;
	}
}

void SetThresholdForm::on_pushButtonCalc_clicked()
{
	IntList LayerList;
	GetActiveLayerList(LayerList);
	if(LayerList.GetFirst()==NULL)
		return;
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		if(LayerList.GetFirst()->GetValue()!=D->Layer)
			continue;
		MatchShiftRotationItem	*nBData=dynamic_cast<MatchShiftRotationItem *>(DA);
		if(nBData==NULL)
			continue;

		GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.BuildData(sRoot,sName,MatchShiftRotationReqTryThresholdCommand ,MatchShiftRotationSendTryThresholdCommand);
		MatchShiftRotationItem	*BData=&((MatchShiftRotationReqTryThreshold *)PacketReq.Data)->Threshold;
		((MatchShiftRotationReqTryThreshold *)PacketReq.Data)->GlobalPage	=D->GlobalPage;
		((MatchShiftRotationReqTryThreshold *)PacketReq.Data)->ItemID		=DA->GetID();

		MatchShiftRotationThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		Thr->SearchLittleInItem	=ui->spinBoxSearchLittleInItem	->value();
		Thr->MatchingRate		=ui->doubleSpinBoxMatchingRate	->value();

		((MatchShiftRotationReqTryThreshold *)PacketReq.Data)->SearchArea	=ui->spinBoxGlobalSearchDot	->value();
		((MatchShiftRotationReqTryThreshold *)PacketReq.Data)->SearchAngle	=ui->EditSearchAngle		->value();

		GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		if(PacketReq.Send(D->GlobalPage,0,PacketSend)==true){

			MatchShiftRotationSendTryThreshold	*R=((MatchShiftRotationSendTryThreshold *)PacketSend.Data);

			ui->labelResultDx			->setText(QString::number(R->ResultDx			));
			ui->labelResultDy			->setText(QString::number(R->ResultDy			));
			ui->labelResultAngle		->setText(QString::number(R->ResultAngle*180.0/M_PI));
			ui->labelResultMatchingRate	->setText(QString::number(R->ResultMatchingRate	));

			ui->labelResultDxUnit		->setText(TransformPixelToUnitStr(Page,R->ResultDx	));
			ui->labelResultDyUnit		->setText(TransformPixelToUnitStr(Page,R->ResultDy	));

			//SimPanel.SetResult(R->Result);
			//SimPanel.repaint();
			break;
		}
	}
}

void SetThresholdForm::on_ButtonRelrectOnlyBlock_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Reflecting ONE Item threshold");

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

void SetThresholdForm::on_ButtonReflectAllBlocks_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Reflecting All Item\' threshold");

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

void SetThresholdForm::on_ButtonSaveToLibrary_clicked()
{
	GetDataFromWindow();

	IntList LayerList;
	GetActiveLayerList(LayerList);
	if(LayerList.GetFirst()==NULL)
		return;
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		if(LayerList.GetFirst()->GetValue()!=D->Layer)
			continue;
		MatchShiftRotationItem	*BData=dynamic_cast<MatchShiftRotationItem *>(DA);
		if(BData==NULL)
			continue;

		int	LibID=BData->GetLibID();
		AlgorithmLibraryContainer	*Container=BData->GetLibraryContainer();
		AlgorithmLibraryLevelContainer	DestLib(Container);
		if(BData->GetLibraryContainer()->GetLibrary(LibID ,DestLib)==true){
			MatchShiftRotationLibrary	*ALib=dynamic_cast<MatchShiftRotationLibrary *>(DestLib.GetLibrary());
			MatchShiftRotationThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
			Thr->ToLibrary(ALib);
			BData->GetLibraryContainer()->Update(DestLib);
			return;
		}
	}
}

void SetThresholdForm::on_ButtonLoadFromLibrary_clicked()
{
	IntList LayerList;
	GetActiveLayerList(LayerList);
	if(LayerList.GetFirst()==NULL)
		return;
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		if(LayerList.GetFirst()->GetValue()!=D->Layer)
			continue;
		MatchShiftRotationItem	*BData=dynamic_cast<MatchShiftRotationItem *>(DA);
		if(BData==NULL)
			continue;

		int	LibID=BData->GetLibID();
		AlgorithmLibraryContainer	*Container=BData->GetLibraryContainer();
		AlgorithmLibraryLevelContainer	SrcLib(Container);
		if(BData->GetLibraryContainer()->GetLibrary(LibID ,SrcLib)==true){
			MatchShiftRotationLibrary	*ALib=dynamic_cast<MatchShiftRotationLibrary *>(SrcLib.GetLibrary());
			MatchShiftRotationThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
			Thr->FromLibrary(ALib);
			ShowLibrary();
			CreateThreshld();
			return;
		}
	}
}

void	SetThresholdForm::SlotLayerClicked()
{
	if(LastLayer>=0)
		GetDataFromWindowFromNo(LastLayer);
	CreateThreshld();

	if(GetLayerNumb(Page)>=1 && LButtonList[0]->isChecked()==true){
		LastLayer=0;
	}
	else if(GetLayerNumb(Page)>=2 && LButtonList[1]->isChecked()==true){
		LastLayer=1;
	}
	else if(GetLayerNumb(Page)>=3 && LButtonList[2]->isChecked()==true){
		LastLayer=2;
	}
	ShowLibrary();
	emit	SignalStartCalc();
}
void SetThresholdForm::on_ButtonClose_clicked()
{
	close();
}

void SetThresholdForm::on_listWidgetHistList_doubleClicked(const QModelIndex &index)
{

}

void SetThresholdForm::on_pushButtonChangeLib_clicked()
{
	AlgorithmBase	*ABase=IData->Base->GetAlgorithmBase(sRoot,sName);
	int		RetSelectedLibID;
	QString RetSelectedLibName;
	ExeSelectLibraryForm(ABase->GetLibType(),IData->Base, this
						,RetSelectedLibID
						,RetSelectedLibName);
	if(RetSelectedLibID>=0){
		for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
			AlgorithmItemRoot	*DA=D->Data;
			if(DA==NULL)
				continue;
			MatchShiftRotationItem	*BData=dynamic_cast<MatchShiftRotationItem *>(DA);
			if(BData==NULL)
				continue;
			int	OldID=DA->GetLibID();
			DA->SetLibID(RetSelectedLibID);

			ui->EditLibID	->setText(QString::number(DA->GetLibID()));
		}
	}
}

void SetThresholdForm::on_pushButtonTransmitItemNameAll_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Transmit ItemName all");

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Transmit ItemName all");
	GetDataFromWindow();
	GUICmdSendAlgorithmItemIndependentPack	Packet(IData->Base,QString(/**/"ANY"),QString(/**/"ANY"),-1,true);
	Packet.Command=SetIndependentItemNameDataCommand_All;
	Packet.IData=*IData;
	for(int page=0;page<GetPageNumb();page++){
		Packet.Send(NULL,page,0);
	}
	GetLayersBase()->WaitAllAcknowledged(60*10);
	GetLayersBase()->CloseProcessingForm();
}

void SetThresholdForm::on_spinBoxGlobalSearchDot_valueChanged(int arg1)
{
	emit	SignalStartCalc();
}

void SetThresholdForm::on_EditSearchDot_valueChanged(int arg1)
{
	emit	SignalStartCalc();
}

void SetThresholdForm::on_doubleSpinBoxMatchingRate_valueChanged(double arg1)
{
	emit	SignalStartCalc();
}
void	SetThresholdForm::SlotStartCalc()
{
	on_pushButtonCalc_clicked();
	//SimPanel.repaint();
}