#include "PropertyThinMetalFormResource.h"
#include "EditLibraryDialog.h"
#include "ui_EditLibraryDialog.h"

#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "ImageControlTools.h"
#include "XGUI.h"
#include "XPropertyThinMetalPacket.h"
#include "XThinMetalLibrary.h"
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
	ThinMetalBase	*BBase=GetThinMetalBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();
	pLibFolderForm=new GeneralLibFolderForm(LibType,GetLayersBase(),ui->frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
	pLibFolderForm->SetCurrentLibFolder(GetLayersBase()->GetLibFolderID());

	LLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempThinMetalLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		LLib=Packet.Point;
	}
	int	LayerNumb=GetLayersBase()->GetMaxLayerNumb();
	for(int Layer=0;Layer<LayerNumb;Layer++){
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
	for(int Layer=0;Layer<LayerNumb;Layer++){
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
	on_toolButtonPickup_clicked();
	on_toolButtonInspect_clicked();

	LibSortType	=KOS_ID_Up;
	connect(ui->tableWidgetLibList->horizontalHeader() ,SIGNAL(sectionClicked (int)),this,SLOT(MListSectionClicked (int)));

	InstallOperationLog(this);
}

EditLibraryDialog::~EditLibraryDialog()
{
    delete ui;
	if(LLib!=NULL){
		delete	LLib;
		LLib=NULL;
	}
}

ThinMetalBase	*EditLibraryDialog::GetThinMetalBase(void)
{
	return (ThinMetalBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ThinMetal");
}
void	EditLibraryDialog::MListSectionClicked ( int logicalIndex )
{
	switch(logicalIndex){
		case 0:
			if(LibSortType==KOS_ID_Up)
				LibSortType=KOS_ID_Dn;
			else
				LibSortType=KOS_ID_Up;
			break;
		case 1:
			if(LibSortType==KOS_Name_Up)
				LibSortType=KOS_Name_Dn;
			else
				LibSortType=KOS_Name_Up;
			break;
	}
	ShowLibList();
}
void	EditLibraryDialog::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	ShowLibList();
}

static	int	FuncIDUp(const void *a ,const void *b)
{
	AlgorithmLibraryList	*pa=((AlgorithmLibraryList **)a)[0];
	AlgorithmLibraryList	*pb=((AlgorithmLibraryList **)b)[0];
	return pa->GetLibID() - pb->GetLibID();
}

static	int	FuncIDDn(const void *a ,const void *b)
{
	AlgorithmLibraryList	*pa=((AlgorithmLibraryList **)a)[0];
	AlgorithmLibraryList	*pb=((AlgorithmLibraryList **)b)[0];
	return pb->GetLibID() - pa->GetLibID();
}

static	int	FuncNameUp(const void *a ,const void *b)
{
	AlgorithmLibraryList	*pa=((AlgorithmLibraryList **)a)[0];
	AlgorithmLibraryList	*pb=((AlgorithmLibraryList **)b)[0];
	if(pa->GetLibName() < pb->GetLibName())
		return 1;
	if(pa->GetLibName() > pb->GetLibName())
		return -1;
	return 0;
}

static	int	FuncNameDn(const void *a ,const void *b)
{
	AlgorithmLibraryList	*pa=((AlgorithmLibraryList **)a)[0];
	AlgorithmLibraryList	*pb=((AlgorithmLibraryList **)b)[0];
	if(pa->GetLibName() < pb->GetLibName())
		return -1;
	if(pa->GetLibName() > pb->GetLibName())
		return 1;
	return 0;
}

void	EditLibraryDialog::ShowLibList(void)
{
	//ui->tableWidgetLibList->clear();
	ui->tableWidgetLibList->setRowCount(0);
	ThinMetalBase	*BBase=GetThinMetalBase();
	if(BBase!=NULL){
		CmdGetThinMetalLibraryListPacket	Packet(GetLayersBase());
		Packet.LibFolderID=LibFolderID;
		BBase->TransmitDirectly(&Packet);
		//LibList	=Packet.AList;
		LibList.RemoveAll();

		AlgorithmLibraryList	**Dim=new AlgorithmLibraryList*[Packet.AList.GetCount()];
		int	row=0;
		for(AlgorithmLibraryList *a=Packet.AList.GetFirst();a!=NULL;a=a->GetNext(),row++){
			Dim[row]=a;
		}
		if(LibSortType==KOS_ID_Up)
			QSort(Dim,row,sizeof(Dim[0]),FuncIDUp);
		else if(LibSortType==KOS_ID_Dn)
			QSort(Dim,row,sizeof(Dim[0]),FuncIDDn);
		else if(LibSortType==KOS_Name_Up)
			QSort(Dim,row,sizeof(Dim[0]),FuncNameUp);
		else if(LibSortType==KOS_Name_Dn)
			QSort(Dim,row,sizeof(Dim[0]),FuncNameDn);

		for(int i=0;i<row;i++){
			Packet.AList.RemoveList(Dim[i]);
			LibList.AppendList(Dim[i]);
		}
		delete	[]Dim;

		row=0;
		ui->tableWidgetLibList->setRowCount(LibList.GetNumber());
		for(AlgorithmLibraryList *a=LibList.GetFirst();a!=NULL;a=a->GetNext(),row++){
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
void EditLibraryDialog::on_tableWidgetLibList_clicked(const QModelIndex &index)
{
	int	r=index.row();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		LLib->SetLibID(a->GetLibID());

		CmdLoadThinMetalLibraryPacket	Packet(GetLayersBase());
		Packet.Point=LLib;
		ThinMetalBase	*BBase=GetThinMetalBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				ShowLibrary(*LLib);
				ui->ButtonLibSave	->setEnabled(true);
				ui->ButtonLibDelete	->setEnabled(true);
			}
			else{
				QMessageBox::critical(NULL
					, LangSolver.GetString(EditLibraryDialog_LS,LID_8)/*"Library error"*/
					, LangSolver.GetString(EditLibraryDialog_LS,LID_9)/*"Not loaded this library record"*/);
			}
		}
	}
}

void	EditLibraryDialog::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	ThinMetalLibrary	*d=dynamic_cast<ThinMetalLibrary *>(data.GetLibrary());
	if(data.GetLibID()<0)
		ui->EditLibID->setText(/**/"");
	else
		ui->EditLibID->setText(QString::number(data.GetLibID()));
	ui->EditLibName	->setText(data.GetLibName());

	ui->EditPickupL			->setValue(d->PickupL);
	ui->EditPickupH			->setValue(d->PickupH);
	ui->EditMinSize			->setValue(d->MinSize);
	ui->EditMaxSize			->setValue(d->MaxSize);
	ui->EditMinDots			->setValue(d->MinDots);
	ui->EditMaxDots			->setValue(d->MaxDots);
	ui->EditLimitSize		->setValue(d->LimitSize);
	ui->EditSpaceToOutline	->setValue(d->SpaceToOutline);
	ui->EditNoiseSize		->setValue(d->NoiseSize);
	ui->EditNoiseSizePinHole->setValue(d->NoiseSizePinHole);
	ui->EditPriority		->setValue(d->Priority);

	ui->EditBrightWidthL	->setValue(d->BrightWidthL);
	ui->EditBrightWidthH	->setValue(d->BrightWidthH);
	ui->EditOKDotL			->setValue(d->OKDotL);
	ui->EditOKDotH			->setValue(d->OKDotH);
	ui->EditMaxNGDotL		->setValue(d->MaxNGDotL);
	ui->EditMaxNGDotH		->setValue(d->MaxNGDotH);
	ui->EditOKLengthL		->setValue(d->OKLengthL);
	ui->EditOKLengthH		->setValue(d->OKLengthH);
	ui->EditShrinkDot		->setValue(d->ShrinkDot);
	ui->EditEnlargeDot		->setValue(d->EnlargeDot);

	int	LayerNumb=GetLayersBase()->GetMaxLayerNumb();
	for(IntClass *a=data.GetAdaptedPickLayers().GetFirst();a!=NULL;a=a->GetNext()){
		int	Layer=a->GetValue();
		if(0<=Layer && Layer<LayerNumb){
			LayerPickButtons[Layer]->setChecked(true);
		}
	}
	for(int Layer=0;Layer<LayerNumb;Layer++){
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
		if(0<=Layer && Layer<LayerNumb){
			LayerGenButtons[Layer]->setChecked(true);
		}
	}
	for(int Layer=0;Layer<LayerNumb;Layer++){
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
	ThinMetalLibrary	*d=dynamic_cast<ThinMetalLibrary *>(data.GetLibrary());
	data.SetLibName(ui->EditLibName	->text());

	d->PickupL			=ui->EditPickupL		->value();
	d->PickupH			=ui->EditPickupH		->value();
	d->MinSize			=ui->EditMinSize		->value();
	d->MaxSize			=ui->EditMaxSize		->value();
	d->MinDots			=ui->EditMinDots		->value();
	d->MaxDots			=ui->EditMaxDots		->value();
	d->LimitSize		=ui->EditLimitSize		->value();
	d->SpaceToOutline	=ui->EditSpaceToOutline	->value();
	d->NoiseSize		=ui->EditNoiseSize		->value();
	d->NoiseSizePinHole	=ui->EditNoiseSizePinHole->value();
	d->Priority			=ui->EditPriority		->value();

	d->BrightWidthL		=ui->EditBrightWidthL	->value();
	d->BrightWidthH		=ui->EditBrightWidthH	->value();
	d->OKDotL			=ui->EditOKDotL			->value();
	d->OKDotH			=ui->EditOKDotH			->value();
	d->MaxNGDotL		=ui->EditMaxNGDotL		->value();
	d->MaxNGDotH		=ui->EditMaxNGDotH		->value();
	d->OKLengthL		=ui->EditOKLengthL		->value();
	d->OKLengthH		=ui->EditOKLengthH		->value();
	d->ShrinkDot		=ui->EditShrinkDot		->value();
	d->EnlargeDot		=ui->EditEnlargeDot		->value();

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

void EditLibraryDialog::on_ButtonLibNew_clicked()
{
	if(LLib==NULL)
		return;
	LLib->Reset();
	CmdClearThinMetalLibraryPacket	Packet(GetLayersBase());
	Packet.Point=LLib;
	ThinMetalBase	*BBase=GetThinMetalBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);
	}
	ShowLibrary(*LLib);
	ui->ButtonLibSave	->setEnabled(false);
	ui->ButtonLibDelete	->setEnabled(false);
}

void EditLibraryDialog::on_ButtonLibDelete_clicked()
{
	if(LLib==NULL)
		return;
	if(LLib->GetLibID()<0)
		return;
	QString  msg=LangSolver.GetString(EditLibraryDialog_LS,LID_10)/*"Delete OK?"*/;
	int	ret=QMessageBox::question(NULL
					, LangSolver.GetString(EditLibraryDialog_LS,LID_11)/*"Choose"*/
					, msg
					, QMessageBox::Yes , QMessageBox::No, QMessageBox::NoButton);
	if(ret==QMessageBox::Yes){
		CmdDeleteThinMetalLibraryPacket	Packet(GetLayersBase());
		Packet.Point=LLib;
		ThinMetalBase	*BBase=GetThinMetalBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			on_ButtonLibNew_clicked();
			SlotSelectLibFolder(LibFolderID 
								,/**/"");
		}
	}
}

void EditLibraryDialog::on_ButtonLibSaveNew_clicked()
{
	if(LLib==NULL)
		return;
	GetLibraryFromWindow(*LLib);

	if(LLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL
														, LangSolver.GetString(EditLibraryDialog_LS,LID_12)/*"Warning"*/
														, LangSolver.GetString(EditLibraryDialog_LS,LID_13)/*"No Library Name"*/
														, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	LLib->SetLibFolderID(LibFolderID);
	CmdInsertThinMetalLibraryPacket	Packet(GetLayersBase());
	Packet.Point=LLib;
	ThinMetalBase	*BBase=GetThinMetalBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);		
		ShowLibrary(*LLib);
		ui->ButtonLibSave	->setEnabled(true);
		ui->ButtonLibDelete	->setEnabled(true);
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}

void EditLibraryDialog::on_ButtonLibSave_clicked()
{
	if(LLib==NULL)
		return;
	GetLibraryFromWindow(*LLib);
	if(LLib->GetLibName()==QString(/**/"")){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL
															, LangSolver.GetString(EditLibraryDialog_LS,LID_14)/*"Warning"*/
															, LangSolver.GetString(EditLibraryDialog_LS,LID_15)/*"No Library Name"*/
															, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	if(LLib->GetLibID()<0){
		LLib->SetLibFolderID(LibFolderID);

		CmdInsertThinMetalLibraryPacket	Packet(GetLayersBase());
		Packet.Point=LLib;
		ThinMetalBase	*BBase=GetThinMetalBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			ShowLibrary(*LLib);
			ui->ButtonLibSave	->setEnabled(true);
			ui->ButtonLibDelete	->setEnabled(true);
		}
	}
	else{
		CmdUpdateThinMetalLibraryPacket	Packet(GetLayersBase());
		Packet.Point=LLib;
		ThinMetalBase	*BBase=GetThinMetalBase();
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
