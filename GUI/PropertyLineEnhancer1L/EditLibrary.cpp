#include "PropertyLineEnhancer1LFormResource.h"
#include "EditLibrary.h"
#include "ui_EditLibrary.h"
#include "XLineEnhancer1L.h"
#include "XDataInLayer.h"
#include "XDisplayImage.h"
#include "XGUIFormBase.h"
#include <QMessageBox>
#include "XGeneralDialog.h"

EditLibrary::EditLibrary(LayersBase *Base,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(Base)
    ,ui(new Ui::EditLibrary)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	LibFolderID =-1;
	LineEnhancer1LBase	*BBase=GetLineEnhancer1LBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();
	pLibFolderForm=new GeneralLibFolderForm(LibType,GetLayersBase(),ui->frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
	pLibFolderForm->SetCurrentLibFolder(GetLayersBase()->GetLibFolderID());

	ui->tableWidgetLibList->setColumnWidth (0, 40);
	ui->tableWidgetLibList->setColumnWidth (1, 100);

	TempLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempLineEnhancer1LLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		TempLib=Packet.Point;
	}
	int	Page=0;
	for(int Layer=0;Layer<GetLayerNumb(Page);Layer++){
		QToolButton	*LayerButton=new QToolButton(ui->framePickLayer);
		LayerButton->move(Layer*90,0);
		LayerButton->resize(88,20);
		LayerButton->setCheckable(true);
		LayerButton->setAutoExclusive(true);
		LayerButton->setText(GetParamGlobal()->GetLayerName(Layer));
		QPalette	PL=LayerButton->palette();
		PL.setColor(QPalette::Button,GetParamGlobal()->GetOneGraphLayerColor(Layer));
		LayerButton->setPalette(PL);
		LayerPickButtons.append(LayerButton);
	}
	for(int Layer=0;Layer<GetLayerNumb(Page);Layer++){
		QToolButton	*LayerButton=new QToolButton(ui->frameSourceLayer);
		LayerButton->move(Layer*90,0);
		LayerButton->resize(88,20);
		LayerButton->setCheckable(true);
		LayerButton->setAutoExclusive(true);
		LayerButton->setText(GetParamGlobal()->GetLayerName(Layer));
		QPalette	PL=LayerButton->palette();
		PL.setColor(QPalette::Button,GetParamGlobal()->GetOneGraphLayerColor(Layer));
		LayerButton->setPalette(PL);
		LayerSourceButtons.append(LayerButton);
	}
	for(int Layer=0;Layer<GetLayerNumb(Page);Layer++){
		QToolButton	*LayerButton=new QToolButton(ui->frameGenLayer);
		LayerButton->move(Layer*90,0);
		LayerButton->resize(88,20);
		LayerButton->setCheckable(true);
		LayerButton->setAutoExclusive(true);
		LayerButton->setText(GetParamGlobal()->GetLayerName(Layer));
		QPalette	PL=LayerButton->palette();
		PL.setColor(QPalette::Button,GetParamGlobal()->GetOneGraphLayerColor(Layer));
		LayerButton->setPalette(PL);
		LayerGenButtons.append(LayerButton);
	}
	ui->ButtonLibSave	->setEnabled(false);
	ui->ButtonLibDelete	->setEnabled(false);
	InstallOperationLog(this);
}

EditLibrary::~EditLibrary()
{
    delete ui;
}

LineEnhancer1LBase	*EditLibrary::GetLineEnhancer1LBase(void)
{
	return (LineEnhancer1LBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"LineEnhancer1L");
}

void	EditLibrary::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	ui->tableWidgetLibList->setRowCount(0);
	LineEnhancer1LBase	*BBase=GetLineEnhancer1LBase();
	if(BBase!=NULL){
		CmdGetLineEnhancer1LLibraryListPacket	Packet(GetLayersBase());
		Packet.LibFolderID=LibFolderID;
		BBase->TransmitDirectly(&Packet);
		LibList	=Packet.AList;
		int	row=0;
		ui->tableWidgetLibList->setRowCount(Packet.AList.GetNumber());
		for(AlgorithmLibraryList *a=Packet.AList.GetFirst();a!=NULL;a=a->GetNext(),row++){
			QTableWidgetItem *W;
			W=ui->tableWidgetLibList->item ( row, 0);
			if(W==NULL){
				W=new QTableWidgetItem();
				ui->tableWidgetLibList->setItem ( row, 0,W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);			
			}
			W->setText(QString::number(a->GetLibID()));
			W=ui->tableWidgetLibList->item ( row, 1);
			if(W==NULL){
				W=new QTableWidgetItem();
				ui->tableWidgetLibList->setItem ( row, 1,W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			W->setText(a->GetLibName());
		}
	}
}

void	EditLibrary::Initial(AlgorithmBase *InstBase)
{
	AlgorithmLibraryContainerForEnum		LibList(InstBase->GetLayersBase());
	LibIDList.RemoveAll();
	LibList.EnumAllLibraries(GetLayersBase()->GetDatabase(),InstBase->GetLibType(),LibIDList);
}
void EditLibrary::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());

		CmdLoadLineEnhancer1LLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		LineEnhancer1LBase	*BBase=GetLineEnhancer1LBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				ShowLibrary(*TempLib);
				ui->ButtonLibSave	->setEnabled(true);
				ui->ButtonLibDelete	->setEnabled(true);
			}
			else{
				QMessageBox::critical(NULL	,/**/"Library error"
											,/**/"Not loaded this library record");
			}
		}
	}
}

void EditLibrary::on_ButtonLibNew_clicked()
{
	if(TempLib==NULL)
		return;
	TempLib->Reset();
	CmdClearLineEnhancer1LLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	LineEnhancer1LBase	*BBase=GetLineEnhancer1LBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);
	}
	ShowLibrary(*TempLib);
	ui->ButtonLibSave	->setEnabled(false);
	ui->ButtonLibDelete	->setEnabled(false);
}

void EditLibrary::on_ButtonLibDelete_clicked()
{
	if(TempLib==NULL)
		return;
	if(TempLib->GetLibID()<0)
		return;
	QString  msg=QString(/**/"Delete OK?");
	int	ret=QMessageBox::question(NULL, /**/"Choose"
					, msg
					, QMessageBox::Yes , QMessageBox::No, QMessageBox::NoButton);
	if(ret==QMessageBox::Yes){
		CmdDeleteLineEnhancer1LLibraryPacket 	Packet(GetLayersBase());
		Packet.Point=TempLib;
		LineEnhancer1LBase	*BBase=GetLineEnhancer1LBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			on_ButtonLibNew_clicked();
			SlotSelectLibFolder(LibFolderID ,/**/"");
		}
	}
}

void EditLibrary::on_ButtonLibSaveNew_clicked()
{
	if(TempLib==NULL)
		return;
	GetLibraryFromWindow(*TempLib);

	if(TempLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL
			, /**/"Warning"
			, /**/"No Library Name"
			, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	TempLib->SetLibFolderID(LibFolderID);
	CmdInsertLineEnhancer1LLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	LineEnhancer1LBase	*BBase=GetLineEnhancer1LBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);		
		ShowLibrary(*TempLib);
		ui->ButtonLibSave	->setEnabled(true);
		ui->ButtonLibDelete	->setEnabled(true);
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}

void EditLibrary::on_ButtonLibSave_clicked()
{
	if(TempLib==NULL)
		return;
	GetLibraryFromWindow(*TempLib);
	if(TempLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL
			, /**/"Warning"
			, /**/"No Library Name"
			, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	if(TempLib->GetLibID()<0){
		TempLib->SetLibFolderID(LibFolderID);

		CmdInsertLineEnhancer1LLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		LineEnhancer1LBase	*BBase=GetLineEnhancer1LBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			ShowLibrary(*TempLib);
			ui->ButtonLibSave	->setEnabled(true);
			ui->ButtonLibDelete	->setEnabled(true);
		}
	}
	else{
		CmdUpdateLineEnhancer1LLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		LineEnhancer1LBase	*BBase=GetLineEnhancer1LBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
		}
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}

void EditLibrary::on_pushButton_clicked()
{
	close();
}

void	EditLibrary::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	if(data.GetLibID()<0)
		ui->EditLibID->setText(/**/"");
	else
		ui->EditLibID->setText(QString::number(data.GetLibID()));
	ui->EditLibName	->setText(data.GetLibName());

	LineEnhancer1LLibrary	*ALib=dynamic_cast<LineEnhancer1LLibrary *>(data.GetLibrary());
	ui->EditPickupH					->setValue	(ALib->PickupColorH);
	ui->EditPickupL					->setValue	(ALib->PickupColorL);
	ui->checkBoxGenerateOverlap		->setChecked(ALib->GenerateOverlap);

	ui->EditMinDot					->setValue	(ALib->MinDot);
	ui->EditMaxDot					->setValue	(ALib->MaxDot);
	ui->EditMinSize					->setValue	(ALib->MinSize);
	ui->EditMaxSize					->setValue	(ALib->MaxSize);
	ui->EditLimitDot				->setValue	(ALib->LimitDot);
	ui->EditShrinkDot				->setValue	(ALib->ShrinkDot);
	ui->doubleSpinBoxEmphasizeRate	->setValue	(ALib->EmphasizeRate);
	ui->EditPriority				->setValue	(ALib->Priority);
	ui->EditMaxLineWidth			->setValue	(ALib->MaxLineWidth);
	ui->EditStepDot					->setValue	(ALib->StepDot);
	ui->EditSearchBlockWidth		->setValue	(ALib->SearchBlockWidth);
	ui->EditSelfSearch				->setValue	(ALib->SelfSearch);
	ui->checkBoxExcludeDynamicMask	->setChecked(ALib->ExcludeDynamicMask);
	ui->doubleSpinBoxStartAngle		->setValue	(ALib->StartAngle);
	ui->doubleSpinBoxEndAngle		->setValue	(ALib->EndAngle);
	ui->checkBoxFixedAngle			->setChecked(ALib->FixedAngle);

	on_checkBoxFixedAngle_clicked();
	int	Page=0;
	for(IntClass *a=data.GetAdaptedPickLayers().GetFirst();a!=NULL;a=a->GetNext()){
		int	Layer=a->GetValue();
		if(0<=Layer && Layer<GetLayerNumb(Page)){
			LayerPickButtons[Layer]->setChecked(true);
		}
	}
	for(int Layer=0;Layer<GetLayerNumb(Page);Layer++){
		bool	Found=false;
		for(IntClass *a=data.GetAdaptedPickLayers().GetFirst();a!=NULL;a=a->GetNext()){
			if(Layer==a->GetValue()){
				Found=true;
				break;
			}
		}
		if(Found==false){
			LayerPickButtons[Layer]->setChecked(false);
		}
	}
	if(0<=ALib->SourceLayer && ALib->SourceLayer<GetLayerNumb(Page)){
		LayerSourceButtons[ALib->SourceLayer]->setChecked(true);
	}
	else{
		LayerSourceButtons[0]->setChecked(true);
		ALib->SourceLayer=0;
	}
	for(int Layer=0;Layer<GetLayerNumb(Page);Layer++){
		if(ALib->SourceLayer!=Layer){
			LayerGenButtons[Layer]->setChecked(false);
		}
	}

	for(IntClass *a=ALib->GetAdaptedGenLayers().GetFirst();a!=NULL;a=a->GetNext()){
		int	Layer=a->GetValue();
		if(0<=Layer && Layer<GetLayerNumb(Page)){
			LayerGenButtons[Layer]->setChecked(true);
		}
	}
	for(int Layer=0;Layer<GetLayerNumb(Page);Layer++){
		bool	Found=false;
		for(IntClass *a=ALib->GetAdaptedGenLayers().GetFirst();a!=NULL;a=a->GetNext()){
			if(Layer==a->GetValue()){
				Found=true;
				break;
			}
		}
		if(Found==false){
			LayerGenButtons[Layer]->setChecked(false);
		}
	}
}

void	EditLibrary::GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data)
{
	data.SetLibName(ui->EditLibName	->text());

	LineEnhancer1LLibrary	*ALib=dynamic_cast<LineEnhancer1LLibrary *>(data.GetLibrary());
	ALib->PickupColorH		=ui->EditPickupH	->value();
	ALib->PickupColorL		=ui->EditPickupL	->value();
	ALib->GenerateOverlap	=ui->checkBoxGenerateOverlap->isChecked();

	ALib->MinDot			=ui->EditMinDot				->value();
	ALib->MaxDot			=ui->EditMaxDot				->value();
	ALib->MinSize			=ui->EditMinSize			->value();
	ALib->MaxSize			=ui->EditMaxSize			->value();
	ALib->LimitDot			=ui->EditLimitDot			->value();
	ALib->ShrinkDot			=ui->EditShrinkDot			->value();
	ALib->EmphasizeRate		=ui->doubleSpinBoxEmphasizeRate	->value();
	ALib->Priority			=ui->EditPriority			->value();
	ALib->MaxLineWidth		=ui->EditMaxLineWidth		->value();
	ALib->StepDot			=ui->EditStepDot			->value();
	ALib->SearchBlockWidth	=ui->EditSearchBlockWidth	->value();
	ALib->SelfSearch		=ui->EditSelfSearch			->value();
	ALib->ExcludeDynamicMask=ui->checkBoxExcludeDynamicMask	->isChecked();
	ALib->StartAngle		=ui->doubleSpinBoxStartAngle->value();
	ALib->EndAngle			=ui->doubleSpinBoxEndAngle	->value();
	ALib->FixedAngle		=ui->checkBoxFixedAngle		->isChecked();

	IntList	LayersPickList;
	for(int Layer=0;Layer<LayerPickButtons.count();Layer++){
		if(LayerPickButtons[Layer]->isChecked()==true){
			LayersPickList.Add(Layer);
		}
	}
	data.SetAdaptedPickLayers(LayersPickList);

	for(int Layer=0;Layer<LayerPickButtons.count();Layer++){
		if(LayerSourceButtons[Layer]->isChecked()==true){
			ALib->SourceLayer=Layer;
		}
	}

	IntList	LayersGenList;
	for(int Layer=0;Layer<LayerGenButtons.count();Layer++){
		if(LayerGenButtons[Layer]->isChecked()==true){
			LayersGenList.Add(Layer);
		}
	}
	data.SetAdaptedGenLayers(LayersGenList);
}


void EditLibrary::on_checkBoxFixedAngle_clicked()
{
	if(ui->checkBoxFixedAngle->isChecked()==true){
		ui->doubleSpinBoxEndAngle	->setEnabled(false);
	}
	else{
		ui->doubleSpinBoxEndAngle	->setEnabled(true);
	}
}
