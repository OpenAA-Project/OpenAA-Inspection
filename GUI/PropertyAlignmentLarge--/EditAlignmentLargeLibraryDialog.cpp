#include "EditAlignmentLargeLibraryDialog.h"
#include "ui_EditAlignmentLargeLibraryDialog.h"
#include <QMessageBox>
#include "XGeneralDialog.h"

EditAlignmentLargeLibraryDialog::EditAlignmentLargeLibraryDialog(LayersBase *Base ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(Base),
    ui(new Ui::EditAlignmentLargeLibraryDialog)
{
    ui->setupUi(this);

	//LangSolver.SetUI(this);
	
	bool	Ret;

	LibFolderID =-1;
	AlignmentLargeBase	*BBase=GetAlignmentLargeBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();
	pLibFolderForm=new GeneralLibFolderForm(LibType,GetLayersBase(),ui->frameLibFolder);
	Ret=(connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString))))?true:false;
	Ret=(connect(pLibFolderForm,SIGNAL(SignalDrop(int ,int , QWidget *)),this,SLOT(SlotDrop(int ,int , QWidget *))))?true:false;
	pLibFolderForm->SetCurrentLibFolder(GetLayersBase()->GetLibFolderID());

	ui->tableWidgetLibList->setColumnWidth ( 0, 32);
	ui->tableWidgetLibList->setColumnWidth ( 1, 160);

	TempLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempAlignmentLargeLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		TempLib=Packet.Point;
	}

	for(int Layer=0;Layer<GetLayerNumb();Layer++){
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
	for(int Layer=0;Layer<GetLayerNumb();Layer++){
		QToolButton	*LayerButton=new QToolButton(ui->frameGenLayer);
		LayerButton->move(Layer*90,0);
		LayerButton->resize(88,20);
		LayerButton->setCheckable(true);
		LayerButton->setAutoExclusive(false);
		LayerButton->setText(GetParamGlobal()->GetLayerName(Layer));
		QPalette	PL=LayerButton->palette();
		PL.setColor(QPalette::Button,GetParamGlobal()->GetOneGraphLayerColor(Layer));
		LayerButton->setPalette(PL);
		LayerGenButtons.append(LayerButton);
	}
	//ui->tabWidget->setCurrentIndex(0);

	ui->ButtonLibSave	->setEnabled(false);
	ui->ButtonLibDelete	->setEnabled(false);
	InstallOperationLog(this);
}

EditAlignmentLargeLibraryDialog::~EditAlignmentLargeLibraryDialog()
{
    delete ui;
}

AlignmentLargeBase	*EditAlignmentLargeLibraryDialog::GetAlignmentLargeBase(void)
{
	return (AlignmentLargeBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AlignmentLarge");
}
void	EditAlignmentLargeLibraryDialog::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	AlignmentLargeBase	*BBase=GetAlignmentLargeBase();
	if(BBase!=NULL){
		CmdGetAlignmentLargeLibraryListPacket	Packet(GetLayersBase());
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
void	EditAlignmentLargeLibraryDialog::Initial(AlgorithmBase *InstBase)
{
	AlgorithmLibraryContainerForEnum		LibList(InstBase->GetLayersBase());
	LibIDList.RemoveAll();
	LibList.EnumAllLibraries(GetLayersBase()->GetDatabase(),InstBase->GetLibType(),LibIDList);
}
void EditAlignmentLargeLibraryDialog::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());

		CmdLoadAlignmentLargeLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		AlignmentLargeBase	*BBase=GetAlignmentLargeBase();
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
void EditAlignmentLargeLibraryDialog::on_ButtonLibNew_clicked()
{
	if(TempLib==NULL)
		return;
	TempLib->Reset();
	CmdClearAlignmentLargeLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	AlignmentLargeBase	*BBase=GetAlignmentLargeBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);
	}
	ShowLibrary(*TempLib);
	ui->ButtonLibSave	->setEnabled(false);
	ui->ButtonLibDelete	->setEnabled(false);
}

void EditAlignmentLargeLibraryDialog::on_ButtonLibDelete_clicked()
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
		CmdDeleteAlignmentLargeLibraryPacket 	Packet(GetLayersBase());
		Packet.Point=TempLib;
		AlignmentLargeBase	*BBase=GetAlignmentLargeBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			on_ButtonLibNew_clicked();
			SlotSelectLibFolder(LibFolderID ,/**/"");
		}
	}
}

void EditAlignmentLargeLibraryDialog::on_ButtonLibSaveNew_clicked()
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
	CmdInsertAlignmentLargeLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	AlignmentLargeBase	*BBase=GetAlignmentLargeBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);		
		ShowLibrary(*TempLib);
		ui->ButtonLibSave	->setEnabled(true);
		ui->ButtonLibDelete	->setEnabled(true);
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}

void EditAlignmentLargeLibraryDialog::on_ButtonLibSave_clicked()
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

		CmdInsertAlignmentLargeLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		AlignmentLargeBase	*BBase=GetAlignmentLargeBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			ShowLibrary(*TempLib);
			ui->ButtonLibSave	->setEnabled(true);
			ui->ButtonLibDelete	->setEnabled(true);
		}
	}
	else{
		CmdUpdateAlignmentLargeLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		AlignmentLargeBase	*BBase=GetAlignmentLargeBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
		}
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}

void EditAlignmentLargeLibraryDialog::on_pushButtonClose_clicked()
{
	close();
}

void	EditAlignmentLargeLibraryDialog::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	AlignmentLargeLibrary	*d=dynamic_cast<AlignmentLargeLibrary *>(data.GetLibrary());
	if(data.GetLibID()<0)
		ui->EditLibID->setText(/**/"");
	else
		ui->EditLibID->setText(QString::number(data.GetLibID()));
	ui->EditLibName	->setText(data.GetLibName());

	ui->checkBoxGenerateArea	->setChecked(d->GenerateArea);
	ui->checkBoxGenerateMark	->setChecked(d->GenerateMark);
	ui->checkBoxGenerateBitBuff	->setChecked(d->GenerateBitBuff);

	ui->spinBoxMinGenerationAreaDots	->setValue(d->MinGenerationAreaDots);
	ui->spinBoxMinGenerationMarkDots	->setValue(d->MinGenerationMarkDots);

	if(d->Priority==AlignmentLargeLibrary::_PriorityHigh)
		ui->radioButtonPriorityHigh	->setChecked(true);
	if(d->Priority==AlignmentLargeLibrary::_PriorityMiddle)
		ui->radioButtonPriorityMiddle->setChecked(true);
	if(d->Priority==AlignmentLargeLibrary::_PriorityLow)
		ui->radioButtonPriorityLow	->setChecked(true);
	if(d->Priority==AlignmentLargeLibrary::_PriorityGlobal)
		ui->radioButtonPriorityLGlobal->setChecked(true);

	ui->EditMoveDot			->setValue(d->MoveDotX);
	ui->EditMoveDotY		->setValue(d->MoveDotY);
	ui->EditMoveDot2		->setValue(d->MoveDotX2);
	ui->EditMoveDotY2		->setValue(d->MoveDotY2);
	ui->checkBoxUsageGlobal	->setChecked(d->UsageGlobal);

	ui->spinBoxMaxCountHLine->setValue(d->MaxCountHLine);
	ui->spinBoxMaxCountVLine->setValue(d->MaxCountVLine);

	for(IntClass *a=data.GetAdaptedPickLayers().GetFirst();a!=NULL;a=a->GetNext()){
		int	Layer=a->GetValue();
		if(0<=Layer && Layer<GetLayerNumb()){
			LayerPickButtons[Layer]->setChecked(true);
		}
	}
	for(int Layer=0;Layer<GetLayerNumb();Layer++){
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
		if(0<=Layer && Layer<GetLayerNumb()){
			LayerGenButtons[Layer]->setChecked(true);
		}
	}
	for(int Layer=0;Layer<GetLayerNumb();Layer++){
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

void	EditAlignmentLargeLibraryDialog::GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data)
{
	AlignmentLargeLibrary	*d=dynamic_cast<AlignmentLargeLibrary *>(data.GetLibrary());
	data.SetLibName(ui->EditLibName	->text());

	d->GenerateArea	=ui->checkBoxGenerateArea	->isChecked();
	d->GenerateMark	=ui->checkBoxGenerateMark	->isChecked();
	d->GenerateBitBuff=ui->checkBoxGenerateBitBuff->isChecked();

	d->MinGenerationAreaDots	=ui->spinBoxMinGenerationAreaDots->value();
	d->MinGenerationMarkDots	=ui->spinBoxMinGenerationMarkDots->value();
									
	if(ui->radioButtonPriorityHigh->isChecked()==true){
		d->Priority=AlignmentLargeLibrary::_PriorityHigh;
	}
	else if(ui->radioButtonPriorityMiddle->isChecked()==true){
		d->Priority=AlignmentLargeLibrary::_PriorityMiddle;
	}
	else if(ui->radioButtonPriorityLow->isChecked()==true){
		d->Priority=AlignmentLargeLibrary::_PriorityLow;
	}
	else if(ui->radioButtonPriorityLGlobal->isChecked()==true){
		d->Priority=AlignmentLargeLibrary::_PriorityGlobal;
	}

	d->MoveDotX		=ui->EditMoveDot	->value();
	d->MoveDotY		=ui->EditMoveDotY	->value();
	d->MoveDotX2	=ui->EditMoveDot2	->value();
	d->MoveDotY2	=ui->EditMoveDotY2	->value();

	d->UsageGlobal		=ui->checkBoxUsageGlobal	->isChecked();
	d->MaxCountHLine	=ui->spinBoxMaxCountHLine	->value();
	d->MaxCountVLine	=ui->spinBoxMaxCountVLine	->value();

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

void	EditAlignmentLargeLibraryDialog::SlotDrop(int FolderParentID ,int LibFolderID , QWidget *w)
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
	if(TempLib->GetLibID()>=0){
		TempLib->SetLibFolderID(LibFolderID);
		CmdUpdateAlignmentLargeLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		AlignmentLargeBase	*BBase=GetAlignmentLargeBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
		}
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}
