#include "PropertyLinePatternFormResource.h"
#include "EditLibraryDialog.h"
#include "ui_EditLibraryDialog.h"
#include "SelectLibraryDialog.h"
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
	LinePatternBase	*BBase=GetLinePatternBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();
	pLibFolderForm=new GeneralLibFolderForm(LibType,GetLayersBase(),ui->frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
	pLibFolderForm->SetCurrentLibFolder(GetLayersBase()->GetLibFolderID());

	TempLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempLinePatternLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		TempLib=Packet.Point;
	}
	ui->tableWidgetLibList->setColumnWidth ( 0, 32);
	ui->tableWidgetLibList->setColumnWidth ( 1, 160);
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
	if(ui->toolButtonPickup->isChecked()==true)
		ui->stackedWidget->setCurrentIndex(0);
	else
		ui->stackedWidget->setCurrentIndex(1);
	InstallOperationLog(this);
}

EditLibraryDialog::~EditLibraryDialog()
{
    delete ui;
}
LinePatternBase	*EditLibraryDialog::GetLinePatternBase(void)
{
	return (LinePatternBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"LinePattern");
}
void	EditLibraryDialog::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	ui->tableWidgetLibList->setRowCount(0);
	LinePatternBase	*BBase=GetLinePatternBase();
	if(BBase!=NULL){
		CmdGetLinePatternLibraryListPacket	Packet(GetLayersBase());
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

		CmdLoadLinePatternLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		LinePatternBase	*BBase=GetLinePatternBase();
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

void EditLibraryDialog::on_ButtonAddSubtractLib_clicked()
{
	if(TempLib==NULL)
		return;
	SelectLibraryDialog	D(GetLayersBase(),this);
	if(D.exec()==QDialog::Accepted){
		int	LibID=D.SelectedID;
		LinePatternLibrary	*ALib=dynamic_cast<LinePatternLibrary *>(TempLib->GetLibrary());
		if(ALib->SubtractBlock.IsInclude(LibID)==true)
			return;
		ALib->SubtractBlock.Add(LibID);
		ShowSubtractList(*ALib);
	}
}

void EditLibraryDialog::on_ButtonDelSubtractLib_clicked()
{
	QModelIndex	RIndex=ui->tableWidgetSubtractLibList->currentIndex();
	if(RIndex.isValid()==false)
		return;
	int	R=RIndex.row();
	LinePatternLibrary	*ALib=dynamic_cast<LinePatternLibrary *>(TempLib->GetLibrary());
	IntClass *c=ALib->SubtractBlock.GetItem(R);
	if(c!=NULL){
		ALib->SubtractBlock.RemoveList(c);
		delete	c;
		ShowSubtractList(*ALib);
	}
}

void EditLibraryDialog::on_ButtonLibNew_clicked()
{
	if(TempLib==NULL)
		return;
	TempLib->Reset();
	CmdClearLinePatternLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	LinePatternBase	*BBase=GetLinePatternBase();
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
		CmdDeleteLinePatternLibraryPacket 	Packet(GetLayersBase());
		Packet.Point=TempLib;
		LinePatternBase	*BBase=GetLinePatternBase();
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
	CmdInsertLinePatternLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	LinePatternBase	*BBase=GetLinePatternBase();
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

		CmdInsertLinePatternLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		LinePatternBase	*BBase=GetLinePatternBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			ShowLibrary(*TempLib);
			ui->ButtonLibSave	->setEnabled(true);
			ui->ButtonLibDelete	->setEnabled(true);
		}
	}
	else{
		CmdUpdateLinePatternLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		LinePatternBase	*BBase=GetLinePatternBase();
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

void EditLibraryDialog::ShowSubtractList(LinePatternLibrary &data)
{
	if(TempLib==NULL)
		return;
	CmdGetLinePatternLibraryNamePacket	LNamePacket(GetLayersBase());

	for(IntClass *c=data.SubtractBlock.GetFirst();c!=NULL;c=c->GetNext()){
		LNamePacket.AList.AppendList(new AlgorithmLibraryList(LibType,c->GetValue(),/**/""));
	}
	LinePatternBase	*BBase=GetLinePatternBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&LNamePacket);
	}
	int	row=0;
	ui->tableWidgetSubtractLibList->setRowCount(data.SubtractBlock.GetCount());
	for(IntClass *c=data.SubtractBlock.GetFirst();c!=NULL;c=c->GetNext(),row++){
		QTableWidgetItem *W;
		W=ui->tableWidgetSubtractLibList->item ( row, 0);
		if(W==NULL){
			W=new QTableWidgetItem();
			ui->tableWidgetSubtractLibList->setItem ( row, 0,W);
			W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		}
		W->setText(QString::number(c->GetValue()));
		AlgorithmLibraryList	*a=LNamePacket.AList.GetItem(row);
		W=ui->tableWidgetSubtractLibList->item ( row, 1);
		if(W==NULL){
			W=new QTableWidgetItem();
			ui->tableWidgetSubtractLibList->setItem ( row, 1,W);
			W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		}
		W->setText(a->GetLibName());
	}
}
void	EditLibraryDialog::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	if(data.GetLibID()<0)
		ui->EditLibID->setText(/**/"");
	else
		ui->EditLibID->setText(QString::number(data.GetLibID()));
	ui->EditLibName	->setText(data.GetLibName());

	LinePatternLibrary	*ALib=dynamic_cast<LinePatternLibrary *>(data.GetLibrary());
	ShowSubtractList(*ALib);

	ui->EditLineWidthInPattern	->setValue(ALib->LineWidthInPattern);
	ui->EditLineWidthOutside	->setValue(ALib->LineWidthOutside);
	ui->EditLimitLength			->setValue(ALib->LimitLength);
	ui->EditGlobalSize			->setValue(ALib->GlobalSize);
	ui->EditMinLineLength		->setValue(ALib->MinLineLength);

	ui->EditBrightWidthIL	->setValue(ALib->BrightWidthIL);
	ui->EditBrightWidthIH	->setValue(ALib->BrightWidthIH);
	ui->EditBrightWidthOL	->setValue(ALib->BrightWidthOL);
	ui->EditBrightWidthOH	->setValue(ALib->BrightWidthOH);
	ui->EditNGSizeIL		->setValue(ALib->NGSizeIL);
	ui->EditNGSizeIH		->setValue(ALib->NGSizeIH);
	ui->EditNGSizeOL		->setValue(ALib->NGSizeOL);
	ui->EditNGSizeOH		->setValue(ALib->NGSizeOH);
	ui->checkBModeEnabled				->setChecked(ALib->PointMove.ModeEnabled);
	ui->checkBModeAbsoluteBright		->setChecked(ALib->PointMove.ModeAbsoluteBright);
	ui->checkBModeCenterBrightFromParts	->setChecked(ALib->PointMove.ModeCenterBrightFromParts);
	ui->checkBModeDynamicMask			->setChecked(ALib->PointMove.ModeDynamicMask);
	ui->checkBModeUseRegularBrightness	->setChecked(ALib->PointMove.ModeUseRegularBrightness);
	ui->EditTransitDot		->setValue(ALib->TransitDot);
	ui->EditAdjustBrightIL	->setValue(ALib->AdjustBrightIL);
	ui->EditAdjustBrightIH	->setValue(ALib->AdjustBrightIH);
	ui->EditAdjustBrightOL	->setValue(ALib->AdjustBrightOL);
	ui->EditAdjustBrightOH	->setValue(ALib->AdjustBrightOH);
	ui->EditSearchDot		->setValue(ALib->SearchDot);
	ui->EditGlobalSearchDot	->setValue(ALib->GlobalSearchDot);
	ui->EditRegulatedColI	->setValue(ALib->RegulatedColI);
	ui->EditRegulatedColO	->setValue(ALib->RegulatedColO);
	ui->EditAngleNumb		->setValue(ALib->AngleNumb);
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

	LinePatternLibrary	*ALib=dynamic_cast<LinePatternLibrary *>(data.GetLibrary());
	ALib->LineWidthInPattern=ui->EditLineWidthInPattern	->value();
	ALib->LineWidthOutside	=ui->EditLineWidthOutside	->value();
	ALib->LimitLength		=ui->EditLimitLength		->value();
	ALib->GlobalSize		=ui->EditGlobalSize			->value();
	ALib->MinLineLength		=ui->EditMinLineLength		->value();

	ALib->BrightWidthIL		=ui->EditBrightWidthIL	->value();
	ALib->BrightWidthIH		=ui->EditBrightWidthIH	->value();
	ALib->BrightWidthOL		=ui->EditBrightWidthOL	->value();
	ALib->BrightWidthOH		=ui->EditBrightWidthOH	->value();
	ALib->NGSizeIL			=ui->EditNGSizeIL		->value();
	ALib->NGSizeIH			=ui->EditNGSizeIH		->value();
	ALib->NGSizeOL			=ui->EditNGSizeOL		->value();
	ALib->NGSizeOH			=ui->EditNGSizeOH		->value();
	ALib->PointMove.ModeEnabled					=ui->checkBModeEnabled				->isChecked();
	ALib->PointMove.ModeAbsoluteBright			=ui->checkBModeAbsoluteBright		->isChecked();
	ALib->PointMove.ModeCenterBrightFromParts	=ui->checkBModeCenterBrightFromParts->isChecked();
	ALib->PointMove.ModeDynamicMask				=ui->checkBModeDynamicMask			->isChecked();
	ALib->PointMove.ModeUseRegularBrightness		=ui->checkBModeUseRegularBrightness	->isChecked();
	ALib->TransitDot		=ui->EditTransitDot		->value();
	ALib->AdjustBrightIL	=ui->EditAdjustBrightIL	->value();
	ALib->AdjustBrightIH	=ui->EditAdjustBrightIH	->value();
	ALib->AdjustBrightOL	=ui->EditAdjustBrightOL	->value();
	ALib->AdjustBrightOH	=ui->EditAdjustBrightOH	->value();

	ALib->SearchDot			=ui->EditSearchDot		->value();
	ALib->GlobalSearchDot	=ui->EditGlobalSearchDot->value();
	ALib->RegulatedColI		=ui->EditRegulatedColI	->value();
	ALib->RegulatedColO		=ui->EditRegulatedColO	->value();

	ALib->AngleNumb			=ui->EditAngleNumb		->value();
		
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

void EditLibraryDialog::on_toolButtonPickup_clicked()
{
	if(ui->toolButtonPickup->isChecked()==true)
		ui->stackedWidget->setCurrentIndex(0);
}

void EditLibraryDialog::on_toolButtonInspect_clicked()
{
	if(ui->toolButtonInspect->isChecked()==true)
		ui->stackedWidget->setCurrentIndex(1);
}
