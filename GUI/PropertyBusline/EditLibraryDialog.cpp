#include "PropertyBuslineFormResource.h"
#include "EditLibraryDialog.h"
#include "ui_EditLibraryDialog.h"
#include <QMessageBox>
#include "XGeneralDialog.h"

EditLibraryDialog::EditLibraryDialog(LayersBase *Base ,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(Base)
    ,ui(new Ui::EditLibraryDialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	LibFolderID =-1;
	BuslineBase	*BBase=GetBuslineBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();
	pLibFolderForm=new GeneralLibFolderForm(LibType,GetLayersBase(),ui->frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
	pLibFolderForm->SetCurrentLibFolder(GetLayersBase()->GetLibFolderID());

	TempLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempBuslineLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		TempLib=Packet.Point;
	}
	int	Page=0;
	ui->tableWidgetLibList->setColumnWidth ( 0, 32);
	ui->tableWidgetLibList->setColumnWidth ( 1, 160);

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

EditLibraryDialog::~EditLibraryDialog()
{
    delete ui;
}
BuslineBase	*EditLibraryDialog::GetBuslineBase(void)
{
	return (BuslineBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Busline");
}
void	EditLibraryDialog::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	ui->tableWidgetLibList->setRowCount(0);
	BuslineBase	*BBase=GetBuslineBase();
	if(BBase!=NULL){
		CmdGetBuslineLibraryListPacket	Packet(GetLayersBase());
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

		CmdLoadBuslineLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		BuslineBase	*BBase=GetBuslineBase();
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
	CmdClearBuslineLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	BuslineBase	*BBase=GetBuslineBase();
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
		CmdDeleteBuslineLibraryPacket 	Packet(GetLayersBase());
		Packet.Point=TempLib;
		BuslineBase	*BBase=GetBuslineBase();
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
	CmdInsertBuslineLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	BuslineBase	*BBase=GetBuslineBase();
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

		CmdInsertBuslineLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		BuslineBase	*BBase=GetBuslineBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			ShowLibrary(*TempLib);
			ui->ButtonLibSave	->setEnabled(true);
			ui->ButtonLibDelete	->setEnabled(true);
		}
	}
	else{
		CmdUpdateBuslineLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		BuslineBase	*BBase=GetBuslineBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
		}
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}

void EditLibraryDialog::on_pushButton_clicked()
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

	BuslineLibrary	*ALib=dynamic_cast<BuslineLibrary *>(data.GetLibrary());
	ui->lineEditBlockMinArea		->setText(QString::number(ALib->BlockMinArea));
	ui->lineEditBlockMaxArea		->setText(QString::number(ALib->BlockMaxArea));
	ui->EditMinWidth				->setValue(ALib->MinWidth);
	ui->EditMinGap					->setValue(ALib->MinGap);
	ui->EditLimitDot				->setValue(ALib->LimitDot);
	ui->lineEditMinArea				->setText(QString::number(ALib->MinArea));
	ui->lineEditMaxArea				->setText(QString::number(ALib->MaxArea));
	ui->EditMinSize					->setValue	(ALib->MinSize);
	ui->checkBoxDarkside			->setChecked(ALib->Darkside);
	ui->checkBoxCompareToMaster		->setChecked(ALib->CompareToMaster);
	ui->checkBoxAutoBinarize		->setChecked(ALib->AutoBinarize);
	ui->checkBoxReduceNoise			->setChecked(ALib->ReduceNoise);
	ui->EditBinarizedLength			->setValue	(ALib->BinarizedLength);
	ui->EditReferredBrightness		->setValue	(ALib->ReferredBrightness);
	ui->EditSearchDotToMaster		->setValue	(ALib->SearchDotToMaster);
	ui->EditWidthToIgnoreEdge		->setValue	(ALib->WidthToIgnoreEdge);
	ui->EditOKNickRate				->setValue	(ALib->OKNickRate);
	ui->EditOKShortRate				->setValue	(ALib->OKShortRate);
	ui->EditBrightnessWidthInsideL 	->setValue	(ALib->BrightnessWidthInsideL );
	ui->EditBrightnessWidthInsideH 	->setValue	(ALib->BrightnessWidthInsideH );
	ui->EditBrightnessWidthOutsideL	->setValue	(ALib->BrightnessWidthOutsideL);
	ui->EditBrightnessWidthOutsideH	->setValue	(ALib->BrightnessWidthOutsideH);
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
	for(IntClass *a=data.GetAdaptedGenLayers().GetFirst();a!=NULL;a=a->GetNext()){
		int	Layer=a->GetValue();
		if(0<=Layer && Layer<GetLayerNumb(Page)){
			LayerGenButtons[Layer]->setChecked(true);
		}
	}
	for(int Layer=0;Layer<GetLayerNumb(Page);Layer++){
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

	BuslineLibrary	*ALib=dynamic_cast<BuslineLibrary *>(data.GetLibrary());
	ALib->BlockMinArea				=ui->lineEditBlockMinArea->text().toLongLong();
	ALib->BlockMaxArea				=ui->lineEditBlockMaxArea->text().toLongLong();
	ALib->MinWidth					=ui->EditMinWidth			->value();
	ALib->MinGap					=ui->EditMinGap				->value();
	ALib->LimitDot					=ui->EditLimitDot			->value();
	ALib->MinArea					=ui->lineEditMinArea->text().toLongLong();
	ALib->MaxArea					=ui->lineEditMaxArea->text().toLongLong();
	ALib->MinSize					=ui->EditMinSize			->value();
	ALib->Darkside					=ui->checkBoxDarkside		->isChecked();
	ALib->CompareToMaster			=ui->checkBoxCompareToMaster->isChecked();
	ALib->AutoBinarize				=ui->checkBoxAutoBinarize	->isChecked();
	ALib->ReduceNoise				=ui->checkBoxReduceNoise	->isChecked();
	ALib->BinarizedLength			=ui->EditBinarizedLength	->value();
	ALib->ReferredBrightness		=ui->EditReferredBrightness	->value();
	ALib->SearchDotToMaster			=ui->EditSearchDotToMaster	->value();
	ALib->WidthToIgnoreEdge			=ui->EditWidthToIgnoreEdge	->value();
	ALib->OKNickRate				=ui->EditOKNickRate			->value();
	ALib->OKShortRate				=ui->EditOKShortRate		->value();
	ALib->BrightnessWidthInsideL 	=ui->EditBrightnessWidthInsideL ->value();
	ALib->BrightnessWidthInsideH 	=ui->EditBrightnessWidthInsideH ->value();
	ALib->BrightnessWidthOutsideL	=ui->EditBrightnessWidthOutsideL->value();
	ALib->BrightnessWidthOutsideH	=ui->EditBrightnessWidthOutsideH->value();

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
