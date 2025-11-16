#include "AlignmentFlexAreaResource.h"
#include "AdjustAlignmentFlexAreaForm.h"
#include "ui_AdjustAlignmentFlexAreaForm.h"
#include "XDataInLayerCommander.h"
#include "XAlignmentFlexArea.h"
#include "XPieceArchitect.h"
#include "XGeneralDialog.h"
#include "XAlignmentFlexAreaLibrary.h"
#include "swap.h"

AdjustAlignmentFlexAreaForm::AdjustAlignmentFlexAreaForm(LayersBase *Base,QWidget *parent) :
    QWidget(parent),ServiceForLayers(Base),PasswordInQWodget(Base,this),
    ui(new Ui::AdjustAlignmentFlexAreaForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	OnChanging=false;
	IData=NULL;

	InstallOperationLog(this);
}

AdjustAlignmentFlexAreaForm::~AdjustAlignmentFlexAreaForm()
{
    delete ui;
}

void	AdjustAlignmentFlexAreaForm::Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data)
{
	if(IData!=NULL)
		delete	IData;
	IData=new AlgorithmItemIndependentPack(InstBase->GetLayersBase());
	*IData=Data;
	GlobalPage=0;

	ShowDataToWindow();
}

void	AdjustAlignmentFlexAreaForm::GetDataFromWindow(void)
{
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		AlignmentFlexAreaItem	*BData=dynamic_cast<AlignmentFlexAreaItem *>(DA);
		if(BData==NULL)
			continue;
		AlignmentFlexAreaThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		Thr->GlobalSearchDot	=ui->spinBoxGlobalSearchDot	->value();
		Thr->SearchDot			=ui->spinBoxSearchDot		->value();
		Thr->SmallSearch		=ui->EditSmallSearch		->value();
		Thr->CloserRate			=ui->doubleSpinBoxCloserRate->value();
		Thr->KeepBW				=ui->checkBoxKeepBW			->isChecked();
		//return;
	}
}
void	AdjustAlignmentFlexAreaForm::ShowDataToWindow(void)
{
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA!=NULL){
			AlignmentFlexAreaItem	*BData=dynamic_cast<AlignmentFlexAreaItem *>(DA);
			if(BData!=NULL){
				ui->spinBoxGlobalSearchDot	->setValue(BData->GetThresholdR(GetLayersBase())->GlobalSearchDot	);
				ui->spinBoxSearchDot		->setValue(BData->GetThresholdR(GetLayersBase())->SearchDot		);
				ui->EditSmallSearch			->setValue(BData->GetThresholdR(GetLayersBase())->SmallSearch		);
				ui->doubleSpinBoxCloserRate	->setValue(BData->GetThresholdR(GetLayersBase())->CloserRate		);
				ui->checkBoxKeepBW			->setChecked(BData->GetThresholdR(GetLayersBase())->KeepBW			);
				BData->TF_EnumHistList(HContainer);
				break;
			}
		}
	}
	ui->doubleSpinBoxSearchDotUnit->setDecimals(GetParamGlobal()->SmallNumberFigure);
	ui->labelUnitName	->setText(GetParamGlobal()->UnitName);
	ui->labelUnitName_2	->setText(GetParamGlobal()->UnitName);
	ui->labelUnitName_3	->setText(GetParamGlobal()->UnitName);
}

void AdjustAlignmentFlexAreaForm::on_pushButtonSetOne_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(AdjustAlignmentFlexAreaForm_LS,LID_0)/*"Change one point"*/);

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Change one point");
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

void AdjustAlignmentFlexAreaForm::on_pushButtonSetAll_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(AdjustAlignmentFlexAreaForm_LS,LID_1)/*"Change all points"*/);

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Change all points");
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

void AdjustAlignmentFlexAreaForm::on_pushButtonHistogramX_clicked()
{
    IntList LayerList;
    HistgramTypeListInAlgo	*H=HContainer[0];
    for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
        AlgorithmItemRoot	*DA=D->Data;
        if(DA==NULL)
            continue;
        AlignmentFlexAreaItem	*BData=dynamic_cast<AlignmentFlexAreaItem *>(DA);
        if(BData==NULL)
            continue;

        BData->TF_ShowHistgramGraph(H->HistID);
        return;
    }
}

void AdjustAlignmentFlexAreaForm::on_pushButtonHistogramY_clicked()
{
    IntList LayerList;
    HistgramTypeListInAlgo	*H=HContainer[1];
    for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
        AlgorithmItemRoot	*DA=D->Data;
        if(DA==NULL)
            continue;
        AlignmentFlexAreaItem	*BData=dynamic_cast<AlignmentFlexAreaItem *>(DA);
        if(BData==NULL)
            continue;

        BData->TF_ShowHistgramGraph(H->HistID);
        return;
    }
}

void AdjustAlignmentFlexAreaForm::on_pushButtonClose_clicked()
{
	close();
}

void AdjustAlignmentFlexAreaForm::on_spinBoxSearchDot_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ui->doubleSpinBoxSearchDotUnit->setValue(TransformPixelToUnit(GlobalPage,arg1));
	OnChanging=false;
}

void AdjustAlignmentFlexAreaForm::on_doubleSpinBoxSearchDotUnit_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ui->spinBoxSearchDot->setValue(TransformUnitToPixel(GlobalPage,arg1));
	OnChanging=false;
}

void AdjustAlignmentFlexAreaForm::on_spinBoxGlobalSearchDot_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ui->doubleSpinBoxGlobalSearchDotUnit->setValue(TransformPixelToUnit(GlobalPage,arg1));
	OnChanging=false;
}

void AdjustAlignmentFlexAreaForm::on_doubleSpinBoxGlobalSearchDotUnit_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ui->spinBoxGlobalSearchDot->setValue(TransformUnitToPixel(GlobalPage,arg1));
	OnChanging=false;
}

void AdjustAlignmentFlexAreaForm::on_pushButtonSaveLibrary_clicked()
{
	GetDataFromWindow();

	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		AlignmentFlexAreaItem	*BData=dynamic_cast<AlignmentFlexAreaItem *>(DA);
		if(BData==NULL)
			continue;

		int	LibID=BData->GetLibID();
		AlgorithmLibraryContainer	*Container=BData->GetLibraryContainer();
		AlgorithmLibraryLevelContainer	DestLib(Container);
		if(Container->GetLibrary(LibID ,DestLib)==true){
			AlignmentFlexAreaLibrary	*ALib=dynamic_cast<AlignmentFlexAreaLibrary *>(DestLib.GetLibrary());
			BData->GetThresholdW(GetLayersBase())->ToLibrary(ALib);
			BData->GetLibraryContainer()->Update(DestLib);
			return;
		}
	}
}

void AdjustAlignmentFlexAreaForm::on_pushButtonLoadLibrary_clicked()
{
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		AlignmentFlexAreaItem	*BData=dynamic_cast<AlignmentFlexAreaItem *>(DA);
		if(BData==NULL)
			continue;

		int	LibID=BData->GetLibID();
		AlgorithmLibraryContainer	*Container=BData->GetLibraryContainer();
		AlgorithmLibraryLevelContainer	SrcLib(Container);
		if(BData->GetLibraryContainer()->GetLibrary(LibID ,SrcLib)==true){
			AlignmentFlexAreaLibrary	*ALib=dynamic_cast<AlignmentFlexAreaLibrary *>(SrcLib.GetLibrary());
			BData->GetThresholdW(GetLayersBase())->FromLibrary(ALib);
			ShowDataToWindow();
			return;
		}
	}
}

void AdjustAlignmentFlexAreaForm::on_EditSmallSearch_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ui->doubleSpinBoxSmallSearchUnit->setValue(TransformPixelToUnit(GlobalPage,arg1));
	OnChanging=false;
}

void AdjustAlignmentFlexAreaForm::on_doubleSpinBoxSmallSearchUnit_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ui->EditSmallSearch->setValue(TransformUnitToPixel(GlobalPage,arg1));
	OnChanging=false;
}
