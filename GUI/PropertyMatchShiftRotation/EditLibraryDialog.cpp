#include "EditLibraryDialog.h"
#include "ui_EditLibraryDialog.h"
#include "XMatchShiftRotation.h"
#include "XDataInLayer.h"
#include "XDisplayImage.h"
#include "XGeneralDialog.h"
#include "XGUIFormBase.h"
#include <QMessageBox>
#include "XGeneralDialog.h"

EditLibraryDialog::EditLibraryDialog(LayersBase *base ,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(base)
    ,ui(new Ui::EditLibraryDialog)
{
    ui->setupUi(this);
	//LangSolver.SetUI(this);

	LibFolderID =-1;
	MatchShiftRotationBase	*BBase=GetMatchShiftRotationBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();
	pLibFolderForm=new GeneralLibFolderForm(LibType,GetLayersBase(),ui->frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
	pLibFolderForm->SetCurrentLibFolder(GetLayersBase()->GetLibFolderID());

	TempLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempMatchShiftRotationLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		TempLib=Packet.Point;
	}
	for(int Layer=0;Layer<GetLayersBase()->GetMaxLayerNumb();Layer++){
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
	for(int Layer=0;Layer<GetLayersBase()->GetMaxLayerNumb();Layer++){
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
	ui->tableWidgetLibList	->setColumnWidth(0,56);
	ui->tableWidgetLibList	->setColumnWidth(1,110);
	ui->ButtonLibSave	->setEnabled(false);
	ui->ButtonLibDelete	->setEnabled(false);

	ui->tabWidget->setCurrentIndex(0);

	InstallOperationLog(this);
}

EditLibraryDialog::~EditLibraryDialog()
{
    delete ui;
}

MatchShiftRotationBase	*EditLibraryDialog::GetMatchShiftRotationBase(void)
{
	return (MatchShiftRotationBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"MatchShiftRotation");
}

void	EditLibraryDialog::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	ui->tableWidgetLibList->setRowCount(0);
	MatchShiftRotationBase	*BBase=GetMatchShiftRotationBase();
	if(BBase!=NULL){
		CmdGetMatchShiftRotationLibraryListPacket	Packet(GetLayersBase());
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

void	EditLibraryDialog::Initial(AlgorithmBase *InstBase)
{
	AlgorithmLibraryContainerForEnum		LibList(InstBase->GetLayersBase());
	LibIDList.RemoveAll();
	LibList.EnumAllLibraries(GetLayersBase()->GetDatabase(),InstBase->GetLibType(),LibIDList);
}

void EditLibraryDialog::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());

		CmdLoadMatchShiftRotationLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		MatchShiftRotationBase	*BBase=GetMatchShiftRotationBase();
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

void EditLibraryDialog::on_ButtonLibNew_clicked()
{
	if(TempLib==NULL)
		return;
	TempLib->Reset();
	CmdClearMatchShiftRotationLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	MatchShiftRotationBase	*BBase=GetMatchShiftRotationBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);
	}
	ShowLibrary(*TempLib);
	ui->ButtonLibSave	->setEnabled(false);
	ui->ButtonLibDelete	->setEnabled(false);
}

void EditLibraryDialog::on_ButtonLibDelete_clicked()
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
		CmdDeleteMatchShiftRotationLibraryPacket 	Packet(GetLayersBase());
		Packet.Point=TempLib;
		MatchShiftRotationBase	*BBase=GetMatchShiftRotationBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			on_ButtonLibNew_clicked();
			SlotSelectLibFolder(LibFolderID ,/**/"");
		}
	}
}

void EditLibraryDialog::on_ButtonLibSaveNew_clicked()
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
	CmdInsertMatchShiftRotationLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	MatchShiftRotationBase	*BBase=GetMatchShiftRotationBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);		
		ShowLibrary(*TempLib);
		ui->ButtonLibSave	->setEnabled(true);
		ui->ButtonLibDelete	->setEnabled(true);
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}

void EditLibraryDialog::on_ButtonLibSave_clicked()
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

		CmdInsertMatchShiftRotationLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		MatchShiftRotationBase	*BBase=GetMatchShiftRotationBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			ShowLibrary(*TempLib);
			ui->ButtonLibSave	->setEnabled(true);
			ui->ButtonLibDelete	->setEnabled(true);
		}
	}
	else{
		CmdUpdateMatchShiftRotationLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		MatchShiftRotationBase	*BBase=GetMatchShiftRotationBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
		}
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}

void EditLibraryDialog::on_pushButtonClose_clicked()
{
	close();
}

void	EditLibraryDialog::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	if(data.GetLibID()<0)
		ui->EditLibID->setText(/**/"");
	else
		ui->EditLibID->setText(QString::number(data.GetLibID()));
	ui->EditLibName	->setText(data.GetLibName());

	MatchShiftRotationLibrary	*ALib=dynamic_cast<MatchShiftRotationLibrary *>(data.GetLibrary());
	ui->EditPickupH					->setValue(ALib->PickupH);
	ui->EditPickupL					->setValue(ALib->PickupL);

	ui->EditMinAreaSize				->setValue(ALib->MinAreaSize);
	ui->EditMaxAreaSize				->setValue(ALib->MaxAreaSize);
	ui->EditMinAreaDots				->setValue(ALib->MinAreaDots);
	ui->EditMaxAreaDots				->setValue(ALib->MaxAreaDots);

	ui->EditExpansionDot			->setValue(ALib->ExpansionDot);
	ui->EditLimitSize				->setValue(ALib->LimitSize);

	ui->spinBoxSearchArea			->setValue(ALib->SearchArea);
	ui->EditSearchAngle				->setValue(ALib->SearchAngle);
	ui->spinBoxSearchLittleInItem	->setValue(ALib->SearchLittleInItem);
	ui->doubleSpinBoxMatchingRate	->setValue(ALib->MatchingRate);

	for(IntClass *a=data.GetAdaptedPickLayers().GetFirst();a!=NULL;a=a->GetNext()){
		int	Layer=a->GetValue();
		if(0<=Layer && Layer<GetLayersBase()->GetMaxLayerNumb()){
			LayerPickButtons[Layer]->setChecked(true);
		}
	}
	for(int Layer=0;Layer<GetLayersBase()->GetMaxLayerNumb();Layer++){
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
	for(IntClass *a=data.GetAdaptedGenLayers().GetFirst();a!=NULL;a=a->GetNext()){
		int	Layer=a->GetValue();
		if(0<=Layer && Layer<GetLayersBase()->GetMaxLayerNumb()){
			LayerGenButtons[Layer]->setChecked(true);
		}
	}
	for(int Layer=0;Layer<GetLayersBase()->GetMaxLayerNumb();Layer++){
		bool	Found=false;
		for(IntClass *a=data.GetAdaptedGenLayers().GetFirst();a!=NULL;a=a->GetNext()){
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

void	EditLibraryDialog::GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data)
{
	data.SetLibName(ui->EditLibName	->text());

	MatchShiftRotationLibrary	*ALib=dynamic_cast<MatchShiftRotationLibrary *>(data.GetLibrary());
	ALib->PickupH			=ui->EditPickupH				->value();
	ALib->PickupL			=ui->EditPickupL				->value();

	ALib->MinAreaSize		=ui->EditMinAreaSize			->value();
	ALib->MaxAreaSize		=ui->EditMaxAreaSize			->value();
	ALib->MinAreaDots		=ui->EditMinAreaDots			->value();
	ALib->MaxAreaDots		=ui->EditMaxAreaDots			->value();

	ALib->ExpansionDot		=ui->EditExpansionDot			->value();
	ALib->LimitSize			=ui->EditLimitSize				->value();

	ALib->SearchArea		=ui->spinBoxSearchArea			->value();
	ALib->SearchAngle		=ui->EditSearchAngle			->value();
	ALib->SearchLittleInItem=ui->spinBoxSearchLittleInItem	->value();
	ALib->MatchingRate		=ui->doubleSpinBoxMatchingRate	->value();

	IntList	LayersPickList;
	for(int Layer=0;Layer<LayerPickButtons.count();Layer++){
		if(LayerPickButtons[Layer]->isChecked()==true){
			LayersPickList.Add(Layer);
		}
	}
	data.SetAdaptedPickLayers(LayersPickList);

	IntList	LayersGenList;
	for(int Layer=0;Layer<LayerGenButtons.count();Layer++){
		if(LayerGenButtons[Layer]->isChecked()==true){
			LayersGenList.Add(Layer);
		}
	}
	data.SetAdaptedGenLayers(LayersGenList);
}
