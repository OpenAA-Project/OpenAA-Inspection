#include "InfoDynamicClassifyForm.h"
#include "XDynamicClassify.h"
#include "XDataInLayerCommander.h"
#include "XPieceArchitect.h"
#include "mtColorFrame.h"
#include "XGeneralDialog.h"
#include "XDisplayImage.h"
#include "swap.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

InfoDynamicClassifyForm::InfoDynamicClassifyForm(ShowAndSetItemsBaseClass *Something ,LayersBase *Base,QWidget *parent)
	: QWidget(parent),ServiceForLayers(Base),ColorSamples(Base)
{
	ui.setupUi(this);

	IData=NULL;

	ColorThre		.setParent(ui.frameThreshold);
	ColorThre		.Fit(ui.frameThreshold);

	connect(&ColorThre,SIGNAL(AddEliminated(void)),this,SLOT(SlotAddEliminated(void)));
	connect(&ColorThre,SIGNAL(DelEliminated(void)),this,SLOT(SlotDelEliminated(void)));

	ColorSamples.setParent(ui.frameColorSample);
	ColorSamples.move(0,0);
	GUIFormBase	*GProp=NULL;
	if(Something==NULL)
		GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"DisplayTargetImage" ,/**/"");
	else{
		ShowAndSetItemsDynamicClassify	*k=dynamic_cast<ShowAndSetItemsDynamicClassify *>(Something);
		if(k!=NULL){
			GProp=k->Form;
		}
	}
	Display=NULL;
	if(GProp!=NULL){
		Display=dynamic_cast<DisplayImage *>(GProp);
		PickupColor=Display->GetPickedColor();
		PickupColorFrame.setParent(ui.framePickupColor);
		PickupColorFrame.move(0,0);
		PickupColorFrame.resize(ui.framePickupColor->width(),ui.framePickupColor->height());
		PickupColorFrame.SetColor(PickupColor);
	}

	connect(&ColorSamples,SIGNAL(SignalBeforeSave ()),this,SLOT(SlotColorSampleBeforeSave()));
	connect(&ColorSamples,SIGNAL(SignalSelectCData()),this,SLOT(SlotColorSampleSelectOne()));

	InstallOperationLog(this);
}

InfoDynamicClassifyForm::~InfoDynamicClassifyForm()
{
	if(IData!=NULL)
		delete	IData;
	IData=NULL;
}

void	InfoDynamicClassifyForm::Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data)
{
	AlgorithmLibraryContainerForEnum		LibList(InstBase->GetLayersBase());
	LibIDList.RemoveAll();
	LibList.EnumAllLibraries(GetLayersBase()->GetDatabase(),InstBase->GetLibType(),LibIDList);

	if(IData!=NULL)
		delete	IData;
	IData=new AlgorithmItemIndependentPack(InstBase->GetLayersBase());
	*IData=Data;
	ShowLibrary();
	//CreateThreshld();
}

void	InfoDynamicClassifyForm::ShowLibrary(void)
{
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		DynamicClassifyItem	*BData=dynamic_cast<DynamicClassifyItem *>(DA);
		if(BData==NULL)
			continue;

		if(DA->GetLibID()<0){
			ui.EditLibID->setText(/**/"");
			ui.EditLibName->setText(/**/"");
		}
		else{
			ui.EditLibID	->setText(QString::number(DA->GetLibID()));
			ui.EditLibName->setText(/**/"");
			for(AlgorithmLibraryList *L=LibIDList.GetFirst();L!=NULL;L=L->GetNext()){
				if(L->GetLibID()==DA->GetLibID()){
					ui.EditLibName	->setText(L->GetLibName());
					break;
				}
			}
		}

		ColorThre.Cube=BData->GetThresholdR(GetLayersBase())->PickupColor;
		ColorThre.InitializedDoneCube();

		ui.EditNoiseDot			->setValue(BData->GetThresholdR(GetLayersBase())->NoiseDot		);
		ui.EditShrinkDot		->setValue(BData->GetThresholdR(GetLayersBase())->ShrinkDot	);
		ui.EditPriority			->setValue(BData->GetThresholdR(GetLayersBase())->Priority		);
		ui.EditVariableWidth	->setValue(BData->GetThresholdR(GetLayersBase())->VariableWidth);

		ui.EditOutlineOWidth	->setValue(BData->GetThresholdR(GetLayersBase())->OutlineOWidth);
		ui.EditOutlineTWidth	->setValue(BData->GetThresholdR(GetLayersBase())->OutlineTWidth);
		ui.EditOutlineIWidth	->setValue(BData->GetThresholdR(GetLayersBase())->OutlineIWidth);
		ui.EditOverlapInEachArea->setValue(BData->GetThresholdR(GetLayersBase())->OverlapInEachArea);

		ui.EditAdjustBlack		->setValue(BData->GetThresholdR(GetLayersBase())->AdjustBrightL);
		ui.EditAdjustWhite		->setValue(BData->GetThresholdR(GetLayersBase())->AdjustBrightH);

		ShowColorMap();

		return;
	}
}

void	InfoDynamicClassifyForm::ShowColorMap(void)
{
	ColorThre.Repaint();
	ui.listWidgetBaseColor->clear();
	ui.listWidgetEliminatedColor->clear();
	int	N=1;
	for(ColorSpace *c=ColorThre.Cube.GetFirstBase();c!=NULL;c=c->GetNext(),N++){
		ui.listWidgetBaseColor->addItem(QString::number(N));
	}
	N=1;
	for(ColorSpace *c=ColorThre.Cube.GetFirstEliminated();c!=NULL;c=c->GetNext(),N++){
		ui.listWidgetEliminatedColor->addItem(QString::number(N));
	}
}

void	InfoDynamicClassifyForm::GetDataFromWindow(void)
{
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		DynamicClassifyItem	*BData=dynamic_cast<DynamicClassifyItem *>(DA);
		if(BData==NULL)
			continue;
		DynamicClassifyThreshold	*Thr=BData->GetThresholdW(GetLayersBase());

		Thr->PickupColor			=ColorThre.Cube;

		Thr->NoiseDot			=ui.EditNoiseDot		->value();
		Thr->ShrinkDot			=ui.EditShrinkDot		->value();
		Thr->Priority			=ui.EditPriority		->value();
		Thr->VariableWidth		=ui.EditVariableWidth	->value();

		Thr->OutlineOWidth		=ui.EditOutlineOWidth	->value();
		Thr->OutlineTWidth		=ui.EditOutlineTWidth	->value();
		Thr->OutlineIWidth		=ui.EditOutlineIWidth	->value();
		Thr->OverlapInEachArea	=ui.EditOverlapInEachArea->value();

		Thr->AdjustBrightL		=ui.EditAdjustBlack		->value();
		Thr->AdjustBrightH		=ui.EditAdjustWhite		->value();
		//return;
	}
}
void	InfoDynamicClassifyForm::SlotColorSampleBeforeSave()
{
	ColorSamples.CData.Set(ColorThre.Cube);
}

void	InfoDynamicClassifyForm::SlotColorSampleSelectOne()
{
	if(ColorSamples.CData.GetColorLogic()==NULL)
		return;
	ColorThre.Cube=*ColorSamples.CData.GetColorLogic();
	ColorThre.InitializedDoneCube();
	ColorThre.Repaint();
}

void	InfoDynamicClassifyForm::SlotAddEliminated(void)
{
}

void	InfoDynamicClassifyForm::SlotDelEliminated(void)
{
}

void InfoDynamicClassifyForm::on_pushButtonChangeLib_clicked()
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
			DynamicClassifyItem	*BData=dynamic_cast<DynamicClassifyItem *>(DA);
			if(BData==NULL)
				continue;
			int	OldID=DA->GetLibID();
			DA->SetLibID(RetSelectedLibID);

			ui.EditLibID	->setText(QString::number(DA->GetLibID()));
			for(AlgorithmLibraryList *L=LibIDList.GetFirst();L!=NULL;L=L->GetNext()){
				if(L->GetLibID()==OldID){
					L->SetLibID(RetSelectedLibID);
					ABase->GetLibraryContainer()->GetLibraryNames(LibIDList);
					ui.EditLibName	->setText(L->GetLibName());
					break;
				}
			}
		}
	}
}

void InfoDynamicClassifyForm::on_listWidgetBaseColor_doubleClicked(QModelIndex)
{
	int	row=ui.listWidgetBaseColor->currentRow();
	if(row<0)
		return;
	ColorSpace	*c=ColorThre.Cube.GetBase(row);
	if(c!=NULL){
		ColorThre.Cube.RemoveBase(c);
		delete	c;
	}
	ShowColorMap();
}

void InfoDynamicClassifyForm::on_listWidgetEliminatedColor_doubleClicked(QModelIndex)
{
	int	row=ui.listWidgetEliminatedColor->currentRow();
	if(row<0)
		return;
	ColorSpace	*c=ColorThre.Cube.GetEliminated(row);
	if(c!=NULL){
		ColorThre.Cube.RemoveEliminated(c);
		delete	c;
	}
	ShowColorMap();
}

void InfoDynamicClassifyForm::on_ButtonRelrectOnlyBlock_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Reflecting ONE Block threshold");

	GetDataFromWindow();
	GUICmdSendAlgorithmItemIndependentPack	Packet(IData->Base,QString(/**/"ANY"),QString(/**/"ANY"));
	Packet.Command=SetIndependentItemDataCommand_OnlyOne;
	Packet.IData=*IData;
	for(int page=0;page<GetPageNumb();page++){
		Packet.Send(NULL,page,0);
	}
	GetLayersBase()->WaitAllAcknowledged(60*10);
	GetLayersBase()->CloseProcessingForm();
}

void InfoDynamicClassifyForm::on_ButtonReflectAllBlocks_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Reflecting ALL Blocks\' threshold");

	GetDataFromWindow();
	GUICmdSendAlgorithmItemIndependentPack	Packet(IData->Base,QString(/**/"ANY"),QString(/**/"ANY"));
	Packet.Command=SetIndependentItemDataCommand_All;
	Packet.IData=*IData;
	for(int page=0;page<GetPageNumb();page++){
		Packet.Send(NULL,page,0);
	}
	GetLayersBase()->WaitAllAcknowledged(60*10);
	GetLayersBase()->CloseProcessingForm();
}

void InfoDynamicClassifyForm::on_ButtonSaveToLibrary_clicked()
{
	GetDataFromWindow();

	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		DynamicClassifyItem	*BData=dynamic_cast<DynamicClassifyItem *>(DA);
		if(BData==NULL)
			continue;

		int	LibID=BData->GetLibID();
		AlgorithmLibraryContainer	*Container=BData->GetLibraryContainer();
		AlgorithmLibraryLevelContainer	DestLib(Container);
		if(Container->GetLibrary(LibID ,DestLib)==true){
			DynamicClassifyLibrary	*ALib=dynamic_cast<DynamicClassifyLibrary *>(DestLib.GetLibrary());
			DynamicClassifyThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
			Thr->ToLibrary(ALib);
			Container->Update(DestLib);
			return;
		}
	}
}

void InfoDynamicClassifyForm::on_ButtonLoadFromLibrary_clicked()
{
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		DynamicClassifyItem	*BData=dynamic_cast<DynamicClassifyItem *>(DA);
		if(BData==NULL)
			continue;

		int	LibID=BData->GetLibID();
		AlgorithmLibraryContainer	*Container=BData->GetLibraryContainer();
		AlgorithmLibraryLevelContainer	SrcLib(Container);
		if(Container->GetLibrary(LibID ,SrcLib)==true){
			DynamicClassifyLibrary	*ALib=dynamic_cast<DynamicClassifyLibrary *>(SrcLib.GetLibrary());
			DynamicClassifyThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
			Thr->FromLibrary(ALib);
			ShowLibrary();
			//ShowThreshold();
			return;
		}
	}
}

void InfoDynamicClassifyForm::on_ButtonClose_clicked()
{
	close();
}

void InfoDynamicClassifyForm::on_ButtonRelrectSaveParts_clicked()
{

}

void InfoDynamicClassifyForm::on_pushButtonAddPickupColor_clicked()
{
	ColorThre.Cube.Add(PickupColor.rgb(),ui.spinBoxMerginAddPickupColor->value());
	ShowColorMap();
}

void InfoDynamicClassifyForm::on_pushButtonSubPickupColor_clicked()
{
	ColorThre.Cube.Eliminame(PickupColor.rgb(),ui.spinBoxMerginSubPickupColor->value());
	ShowColorMap();
}

void InfoDynamicClassifyForm::on_pushButtonAddColor_clicked()
{
	if(ColorSamples.CData.GetColorLogic()==NULL)
		return;
	ColorThre.Cube.Add(*ColorSamples.CData.GetColorLogic());
	ShowColorMap();
}

void InfoDynamicClassifyForm::on_pushButtonEliminateColor_clicked()
{
	if(ColorSamples.CData.GetColorLogic()==NULL)
		return;
	ColorThre.Cube.Eliminate(*ColorSamples.CData.GetColorLogic());
	ShowColorMap();
}

void InfoDynamicClassifyForm::on_pushButtonAddColorArea_clicked()
{

}

void InfoDynamicClassifyForm::on_pushButtonEliminateColorArea_clicked()
{

}

void InfoDynamicClassifyForm::on_toolButtonCoreArea_clicked()
{
	if(Display!=NULL){
		Display->Repaint();
	}
}

void InfoDynamicClassifyForm::on_toolButtonMaxZone_clicked()
{
	if(Display!=NULL){
		Display->Repaint();
	}
}

void InfoDynamicClassifyForm::on_toolButtonMinZone_clicked()
{
	if(Display!=NULL){
		Display->Repaint();
	}
}

void InfoDynamicClassifyForm::on_toolButtonOutlineIArea_clicked()
{
	if(Display!=NULL){
		Display->Repaint();
	}
}

void InfoDynamicClassifyForm::on_toolButtonOutlineTArea_clicked()
{
	if(Display!=NULL){
		Display->Repaint();
	}
}

void InfoDynamicClassifyForm::on_toolButtonOutlineOArea_clicked()
{
	if(Display!=NULL){
		Display->Repaint();
	}
}

void InfoDynamicClassifyForm::on_pushButtonReCalc_clicked()
{
	if(IData==NULL)
		return;
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		DynamicClassifyItem	*nBData=dynamic_cast<DynamicClassifyItem *>(DA);
		if(nBData==NULL)
			continue;

		GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.BuildData(sRoot,sName,DynamicClassifyReqTryThresholdCommand ,DynamicClassifySendTryThresholdCommand);
		DynamicClassifyItem	*BData=&((DynamicClassifyReqTryThreshold *)PacketReq.Data)->Threshold;
		((DynamicClassifyReqTryThreshold *)PacketReq.Data)->GlobalPage	=D->GlobalPage;
		((DynamicClassifyReqTryThreshold *)PacketReq.Data)->ItemID	=DA->GetID();

		DynamicClassifyThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		Thr->PickupColor			=ColorThre.Cube;

		Thr->NoiseDot			=ui.EditNoiseDot		->value();
		Thr->ShrinkDot			=ui.EditShrinkDot		->value();
		Thr->Priority			=ui.EditPriority		->value();
		Thr->VariableWidth		=ui.EditVariableWidth	->value();

		Thr->OutlineOWidth		=ui.EditOutlineOWidth	->value();
		Thr->OutlineTWidth		=ui.EditOutlineTWidth	->value();
		Thr->OutlineIWidth		=ui.EditOutlineIWidth	->value();
		Thr->OverlapInEachArea	=ui.EditOverlapInEachArea->value();

		Thr->AdjustBrightL		=ui.EditAdjustBlack		->value();
		Thr->AdjustBrightH		=ui.EditAdjustWhite		->value();


		GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.Send(D->GlobalPage,0,PacketSend);

		DynamicClassifySendTryThreshold	*R=((DynamicClassifySendTryThreshold *)PacketSend.Data);
		//ui.labelResultNDark	->setText(QString::number(R->NGDotInN	));
		//ui.labelResultBDark	->setText(QString::number(R->NGDotInB	));
		break;
	}
}

void InfoDynamicClassifyForm::on_toolButtonBareArea_clicked()
{
	if(Display!=NULL){
		Display->Repaint();
	}
}

void InfoDynamicClassifyForm::on_toolButtonInside_clicked()
{
	if(Display!=NULL){
		Display->Repaint();
	}
}