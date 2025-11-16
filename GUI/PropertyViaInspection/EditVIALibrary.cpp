#include "PropertyVIAInspectionFormResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyVIA\EditVIALibrary.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "EditVIALibrary.h"
#include "ui_EditVIALibrary.h"
//#include "PropertyVIAFormResource.h"
#include "EditVIALibrary.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "ImageControlTools.h"
#include "XGUI.h"
#include "XPropertyVIAPacket.h"
#include "XViaInspectionLibrary.h"
#include <QMessageBox>
#include "XGeneralDialog.h"

EditVIALibrary::EditVIALibrary(LayersBase *base ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(base),
    ui(new Ui::EditVIALibrary)
{
    ui->setupUi(this);

	//LangSolver.SetUI(this);

	LibFolderID =-1;
	VIABase	*BBase=GetVIABase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();
	pLibFolderForm=new GeneralLibFolderForm(LibType,GetLayersBase(),ui->frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
	pLibFolderForm->SetCurrentLibFolder(GetLayersBase()->GetLibFolderID());

	TempLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempVIALibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		TempLib=Packet.Point;
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

EditVIALibrary::~EditVIALibrary()
{
    delete ui;
	if(TempLib!=NULL){
		delete	TempLib;
		TempLib=NULL;
	}
}

VIABase	*EditVIALibrary::GetVIABase(void)
{
	return (VIABase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"VIAInspection");
}
void	EditVIALibrary::MListSectionClicked ( int logicalIndex )
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
void	EditVIALibrary::SlotSelectLibFolder(int libFolderID ,QString FolderName)
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

void	EditVIALibrary::ShowLibList(void)
{
	//ui->tableWidgetLibList->clear();
	ui->tableWidgetLibList->setRowCount(0);
	VIABase	*BBase=GetVIABase();
	if(BBase!=NULL){
		CmdGetVIALibraryListPacket	Packet(GetLayersBase());
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

void EditVIALibrary::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());

		CmdLoadVIALibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		VIABase	*BBase=GetVIABase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				ShowLibrary(*TempLib);
				ui->ButtonLibSave	->setEnabled(true);
				ui->ButtonLibDelete	->setEnabled(true);
			}
			else{
				QMessageBox::critical(NULL
					, LangSolver.GetString(EditVIALibrary_LS,LID_8)/*"Library error"*/
					, LangSolver.GetString(EditVIALibrary_LS,LID_9)/*"Not loaded this library record"*/);
			}
		}
	}
}

void	EditVIALibrary::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	if(data.GetLibID()<0)
		ui->EditLibID->setText(/**/"");
	else
		ui->EditLibID->setText(QString::number(data.GetLibID()));
	ui->EditLibName	->setText(data.GetLibName());

	VIALibrary	*ALib=dynamic_cast<VIALibrary *>(data.GetLibrary());
	ui->EditPickupL			->setValue(ALib->PickupL);
	ui->EditPickupH			->setValue(ALib->PickupH);
	ui->EditMinVIASize		->setValue(ALib->MinVIASize);
	ui->EditMaxVIASize		->setValue(ALib->MaxVIASize);
	ui->EditMinVIADots		->setValue(ALib->MinVIADots);
	ui->EditMaxVIADots		->setValue(ALib->MaxVIADots);
	ui->EditLimitVIASize	->setValue(ALib->LimitVIASize);
	ui->EditSpaceToOutline	->setValue(ALib->SpaceToOutline);
	ui->EditNoiseSize		->setValue(ALib->NoiseSize);
	ui->EditNoiseSizePinHole->setValue(ALib->NoiseSizePinHole);
	ui->EditPriority		->setValue(ALib->Priority);

	ui->EditBrightWidthL	->setValue(ALib->BrightWidthL);
	ui->EditBrightWidthH	->setValue(ALib->BrightWidthH);
	ui->EditOKDotL			->setValue(ALib->OKDotL);
	ui->EditOKDotH			->setValue(ALib->OKDotH);
	ui->EditMaxNGDotL		->setValue(ALib->MaxNGDotL);
	ui->EditMaxNGDotH		->setValue(ALib->MaxNGDotH);
	ui->EditOKLengthL		->setValue(ALib->OKLengthL);
	ui->EditOKLengthH		->setValue(ALib->OKLengthH);
	ui->EditShrinkDot		->setValue(ALib->ShrinkDot);
	ui->EditEnlargeDot		->setValue(ALib->EnlargeDot);
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

void	EditVIALibrary::GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data)
{
	data.SetLibName(ui->EditLibName	->text());

	VIALibrary	*ALib=dynamic_cast<VIALibrary *>(data.GetLibrary());
	ALib->PickupL			=ui->EditPickupL		->value();
	ALib->PickupH			=ui->EditPickupH		->value();
	ALib->MinVIASize		=ui->EditMinVIASize		->value();
	ALib->MaxVIASize		=ui->EditMaxVIASize		->value();
	ALib->MinVIADots		=ui->EditMinVIADots		->value();
	ALib->MaxVIADots		=ui->EditMaxVIADots		->value();
	ALib->LimitVIASize		=ui->EditLimitVIASize	->value();
	ALib->SpaceToOutline	=ui->EditSpaceToOutline	->value();
	ALib->NoiseSize			=ui->EditNoiseSize		->value();
	ALib->NoiseSizePinHole	=ui->EditNoiseSizePinHole->value();
	ALib->Priority			=ui->EditPriority		->value();

	ALib->BrightWidthL		=ui->EditBrightWidthL	->value();
	ALib->BrightWidthH		=ui->EditBrightWidthH	->value();
	ALib->OKDotL			=ui->EditOKDotL			->value();
	ALib->OKDotH			=ui->EditOKDotH			->value();
	ALib->MaxNGDotL			=ui->EditMaxNGDotL		->value();
	ALib->MaxNGDotH			=ui->EditMaxNGDotH		->value();
	ALib->OKLengthL			=ui->EditOKLengthL		->value();
	ALib->OKLengthH			=ui->EditOKLengthH		->value();
	ALib->ShrinkDot			=ui->EditShrinkDot		->value();
	ALib->EnlargeDot		=ui->EditEnlargeDot		->value();

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
void EditVIALibrary::on_toolButtonPickup_clicked()
{
	if(ui->toolButtonPickup->isChecked()==true)
		ui->stackedWidget->setCurrentIndex(0);
}

void EditVIALibrary::on_toolButtonInspect_clicked()
{
	if(ui->toolButtonInspect->isChecked()==true)
		ui->stackedWidget->setCurrentIndex(1);
}

void EditVIALibrary::on_ButtonLibNew_clicked()
{
	if(TempLib==NULL)
		return;
	TempLib->Reset();
	CmdClearVIALibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	VIABase	*BBase=GetVIABase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);
	}
	ShowLibrary(*TempLib);
	ui->ButtonLibSave	->setEnabled(false);
	ui->ButtonLibDelete	->setEnabled(false);
}

void EditVIALibrary::on_ButtonLibDelete_clicked()
{
	if(TempLib==NULL)
		return;
	if(TempLib->GetLibID()<0)
		return;
	QString  msg=LangSolver.GetString(EditVIALibrary_LS,LID_10)/*"Delete OK?"*/;
	int	ret=QMessageBox::question(NULL
					, LangSolver.GetString(EditVIALibrary_LS,LID_11)/*"Choose"*/
					, msg
					, QMessageBox::Yes , QMessageBox::No, QMessageBox::NoButton);
	if(ret==QMessageBox::Yes){
		CmdDeleteVIALibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		VIABase	*BBase=GetVIABase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			on_ButtonLibNew_clicked();
			SlotSelectLibFolder(LibFolderID 
								,/**/"");
		}
	}
}

void EditVIALibrary::on_ButtonLibSaveNew_clicked()
{
	if(TempLib==NULL)
		return;
	GetLibraryFromWindow(*TempLib);

	if(TempLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL
														, LangSolver.GetString(EditVIALibrary_LS,LID_12)/*"Warning"*/
														, LangSolver.GetString(EditVIALibrary_LS,LID_13)/*"No Library Name"*/
														, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	TempLib->SetLibFolderID(LibFolderID);
	CmdInsertVIALibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	VIABase	*BBase=GetVIABase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);		
		ShowLibrary(*TempLib);
		ui->ButtonLibSave	->setEnabled(true);
		ui->ButtonLibDelete	->setEnabled(true);
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}

void EditVIALibrary::on_ButtonLibSave_clicked()
{
	if(TempLib==NULL)
		return;
	GetLibraryFromWindow(*TempLib);
	if(TempLib->GetLibName()==QString(/**/"")){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL
															, LangSolver.GetString(EditVIALibrary_LS,LID_14)/*"Warning"*/
															, LangSolver.GetString(EditVIALibrary_LS,LID_15)/*"No Library Name"*/
															, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	if(TempLib->GetLibID()<0){
		TempLib->SetLibFolderID(LibFolderID);

		CmdInsertVIALibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		VIABase	*BBase=GetVIABase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			ShowLibrary(*TempLib);
			ui->ButtonLibSave	->setEnabled(true);
			ui->ButtonLibDelete	->setEnabled(true);
		}
	}
	else{
		CmdUpdateVIALibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		VIABase	*BBase=GetVIABase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
		}
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}

void EditVIALibrary::on_pushButton_clicked()
{
	close();
}
