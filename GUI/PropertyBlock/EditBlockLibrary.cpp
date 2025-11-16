/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyBlock\EditBlockLibrary.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "PropertyBlockFormResource.h"
#include "EditBlockLibrary.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "SelectBlockLibraryForm.h"
#include "ImageControlTools.h"
#include "XGUI.h"
#include "XPropertyBlockPacket.h"
#include<QMessageBox>
#include "XGeneralDialog.h"

EditBlockLibrary::EditBlockLibrary(LayersBase *base ,QWidget *parent)
	: QDialog(parent),ServiceForLayers(base)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);

	LibFolderID =-1;
	BlockBase	*BBase=GetBlockBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();
	pLibFolderForm=new GeneralLibFolderForm(LibType,GetLayersBase(),ui.frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));

	ui.tableWidgetSubtractLibList->setColumnWidth (0, 48);
	ui.tableWidgetSubtractLibList->setColumnWidth (1, 120);
	TempLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempBlockLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		TempLib=Packet.Point;
	}

	for(int Layer=0;Layer<GetLayerNumb(0);Layer++){
		QToolButton	*LayerButton=new QToolButton(ui.framePickLayer);
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
	for(int Layer=0;Layer<GetLayerNumb(0);Layer++){
		QToolButton	*LayerButton=new QToolButton(ui.frameGenLayer);
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
	ui.tableWidgetLibList	->setColumnWidth(0,56);
	ui.tableWidgetLibList	->setColumnWidth(1,110);

	ui.ButtonLibSave	->setEnabled(false);
	ui.ButtonLibDelete	->setEnabled(false);
	on_toolButtonPickup_clicked();
	on_toolButtonInspect_clicked();

	LibSortType	=KOS_ID_Up;
	connect(ui.tableWidgetLibList->horizontalHeader() ,SIGNAL(sectionClicked (int)),this,SLOT(MListSectionClicked (int)));

	pLibFolderForm->SetCurrentLibFolder(GetLayersBase()->GetLibFolderID());
	InstallOperationLog(this);
}

EditBlockLibrary::~EditBlockLibrary()
{
	if(TempLib!=NULL){
		delete	TempLib;
		TempLib=NULL;
	}
}

BlockBase	*EditBlockLibrary::GetBlockBase(void)
{
	return (BlockBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"BlockInspection");
}
void	EditBlockLibrary::MListSectionClicked ( int logicalIndex )
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
void	EditBlockLibrary::SlotSelectLibFolder(int libFolderID ,QString FolderName)
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
void	EditBlockLibrary::ShowLibList(void)
{
	//ui.tableWidgetLibList->clear();
	ui.tableWidgetLibList->setRowCount(0);
	BlockBase	*BBase=GetBlockBase();
	if(BBase!=NULL){
		CmdGetBlockLibraryListPacket	Packet(GetLayersBase());
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
		ui.tableWidgetLibList->setRowCount(LibList.GetNumber());
		for(AlgorithmLibraryList *a=LibList.GetFirst();a!=NULL;a=a->GetNext(),row++){
			QTableWidgetItem *W;
			W=ui.tableWidgetLibList->item ( row, 0);
			if(W==NULL){
				W=new QTableWidgetItem();
				ui.tableWidgetLibList->setItem ( row, 0,W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);			
			}
			W->setText(QString::number(a->GetLibID()));
			W=ui.tableWidgetLibList->item ( row, 1);
			if(W==NULL){
				W=new QTableWidgetItem();
				ui.tableWidgetLibList->setItem ( row, 1,W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			W->setText(a->GetLibName());
		}
	}
}

void EditBlockLibrary::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());

		CmdLoadBlockLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		BlockBase	*BBase=GetBlockBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				ShowLibrary(*TempLib);
				ui.ButtonLibSave	->setEnabled(true);
				ui.ButtonLibDelete	->setEnabled(true);
			}
			else{
				QMessageBox::critical(NULL
									, LangSolver.GetString(EditBlockLibrary_LS,LID_51)/*"Library error"*/
									, LangSolver.GetString(EditBlockLibrary_LS,LID_52)/*"Not loaded this library record"*/);
			}
		}
	}
}

void EditBlockLibrary::on_ButtonAddSubtractLib_clicked()
{
	if(TempLib==NULL)
		return;
	SelectBlockLibraryForm	D(GetLayersBase(),this);
	if(D.exec()==QDialog::Accepted){
		int	LibID=D.SelectedLibID;
		BlockLibrary	*ALib=dynamic_cast<BlockLibrary *>(TempLib->GetLibrary());
		if(ALib->SubtractBlock.IsInclude(LibID)==true)
			return;
		ALib->SubtractBlock.Add(LibID);
		ShowSubtractList(*ALib);
	}
}

void EditBlockLibrary::on_ButtonDelSubtractLib_clicked()
{
	QModelIndex	RIndex=ui.tableWidgetSubtractLibList->currentIndex();
	if(RIndex.isValid()==false)
		return;
	int	R=RIndex.row();
	BlockLibrary	*ALib=dynamic_cast<BlockLibrary *>(TempLib->GetLibrary());
	IntClass *c=ALib->SubtractBlock.GetItem(R);
	if(c!=NULL){
		ALib->SubtractBlock.RemoveList(c);
		delete	c;
		ShowSubtractList(*ALib);
	}
}

void EditBlockLibrary::ShowSubtractList(BlockLibrary &data)
{
	if(TempLib==NULL)
		return;
	CmdGetBlockLibraryNamePacket	LNamePacket(GetLayersBase());

	for(IntClass *c=data.SubtractBlock.GetFirst();c!=NULL;c=c->GetNext()){
		LNamePacket.AList.AppendList(new AlgorithmLibraryList(LibType,c->GetValue(),/**/""));
	}
	BlockBase	*BBase=GetBlockBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&LNamePacket);
	}
	int	row=0;
	ui.tableWidgetSubtractLibList->setRowCount(data.SubtractBlock.GetCount());
	for(IntClass *c=data.SubtractBlock.GetFirst();c!=NULL;c=c->GetNext(),row++){
		QTableWidgetItem *W;
		W=ui.tableWidgetSubtractLibList->item ( row, 0);
		if(W==NULL){
			W=new QTableWidgetItem();
			ui.tableWidgetSubtractLibList->setItem ( row, 0,W);
			W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		}
		W->setText(QString::number(c->GetValue()));
		AlgorithmLibraryList	*a=LNamePacket.AList.GetItem(row);
		W=ui.tableWidgetSubtractLibList->item ( row, 1);
		if(W==NULL){
			W=new QTableWidgetItem();
			ui.tableWidgetSubtractLibList->setItem ( row, 1,W);
			W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		}
		W->setText(a->GetLibName());
	}
}

void	EditBlockLibrary::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	if(data.GetLibID()<0)
		ui.EditLibID->setText(/**/"");
	else
		ui.EditLibID->setText(QString::number(data.GetLibID()));
	ui.EditLibName	->setText(data.GetLibName());

	BlockLibrary	*ALib=dynamic_cast<BlockLibrary *>(data.GetLibrary());
	ShowSubtractList(*ALib);

	ui.EditPickupL			->setValue(ALib->PickupL);
	ui.EditPickupH			->setValue(ALib->PickupH);
	ui.EditMinBlockSize		->setValue(ALib->MinBlockSize);
	ui.EditMaxBlockSize		->setValue(ALib->MaxBlockSize);
	ui.EditMinBlockDots		->setValue(ALib->MinBlockDots);
	ui.EditMaxBlockDots		->setValue(ALib->MaxBlockDots);
	ui.EditLimitBlockSize	->setValue(ALib->LimitBlockSize);
	ui.EditSpaceToOutline	->setValue(ALib->SpaceToOutline);
	ui.EditOutlineGeneration->setValue(ALib->OutlineGeneration);
	ui.EditNoiseSize		->setValue(ALib->NoiseSize);
	ui.EditNoiseSizePinHole	->setValue(ALib->NoiseSizePinHole);
	ui.EditPriority			->setValue(ALib->Priority);
	ui.comboBGenerationCategory	->setCurrentIndex((int)ALib->GenerationCategory);
	ui.checkBTransparent			->setChecked(ALib->GenerationMode.Transparent);
	ui.checkBLeftPickup				->setChecked(ALib->GenerationMode.LeftPickup);
	ui.checkBOverlappedGen			->setChecked(ALib->GenerationMode.OverlappedGen);
	ui.checkBPlusHalfDotIsolation	->setChecked(ALib->GenerationMode.PlusHalfDotIsolation);
	ui.checkBBindSmallBlock			->setChecked(ALib->GenerationMode.BindSmallBlock);

	//ui.checkBMatchPosition			->setChecked(data.PointMove.ModeMatchPosition);
	if(ALib->PointMove.ModeMatchPosition==false && ALib->PointMove.ModeMatchPositionBW==false)
		ui.comboBoxMatchPosition	->setCurrentIndex(0);
	else
	if(ALib->PointMove.ModeMatchPosition==true && ALib->PointMove.ModeMatchPositionBW==false)
		ui.comboBoxMatchPosition	->setCurrentIndex(1);
	else
	if(ALib->PointMove.ModeMatchPosition==false && ALib->PointMove.ModeMatchPositionBW==true)
		ui.comboBoxMatchPosition	->setCurrentIndex(2);
	else
	if(ALib->PointMove.ModeMatchPosition==true && ALib->PointMove.ModeMatchPositionBW==true)
		ui.comboBoxMatchPosition	->setCurrentIndex(3);

	ui.checkBModeSearchDetail		->setChecked(ALib->PointMove.ModeSearchDetail);
	ui.checkBModeDynamicMask		->setChecked(ALib->PointMove.ModeDynamicMask);
	ui.checkBModeBindBWBroad		->setChecked(ALib->PointMove.ModeBindBWBroad);
	ui.checkBModeBindBWNarrow		->setChecked(ALib->PointMove.ModeBindBWNarrow);
	ui.checkBModeAdoptBiggest		->setChecked(ALib->PointMove.ModeAdoptBiggest);
	ui.checkBModeUseMasterImage		->setChecked(ALib->PointMove.ModeUseMasterImage);

	ui.EditNBrightWidthL	->setValue(ALib->NBrightWidthL);
	ui.EditNBrightWidthH	->setValue(ALib->NBrightWidthH);
	ui.EditNOKDotL			->setValue(ALib->NOKDotL);
	ui.EditNOKDotH			->setValue(ALib->NOKDotH);
	ui.EditNMaxNGDotL		->setValue(ALib->NMaxNGDotL);
	ui.EditNMaxNGDotH		->setValue(ALib->NMaxNGDotH);
	ui.EditNOKLengthL		->setValue(ALib->NOKLengthL);
	ui.EditNOKLengthH		->setValue(ALib->NOKLengthH);
	ui.EditBBrightWidthL	->setValue(ALib->BBrightWidthL);
	ui.EditBBrightWidthH	->setValue(ALib->BBrightWidthH);
	ui.EditBOKDotL			->setValue(ALib->BOKDotL);
	ui.EditBOKDotH			->setValue(ALib->BOKDotH);
	ui.EditBMaxNGDotL		->setValue(ALib->BMaxNGDotL);
	ui.EditBMaxNGDotH		->setValue(ALib->BMaxNGDotH);
	ui.EditBOKLengthL		->setValue(ALib->BOKLengthL);
	ui.EditBOKLengthH		->setValue(ALib->BOKLengthH);
	ui.EditNMinNGCountL		->setValue(ALib->NMinNGCountL);
	ui.EditNMinNGCountH		->setValue(ALib->NMinNGCountH);
	ui.EditBMinNGCountL		->setValue(ALib->BMinNGCountL);
	ui.EditBMinNGCountH		->setValue(ALib->BMinNGCountH);
	ui.EditNConnectLen		->setValue(ALib->NConnectLen);
	ui.EditBConnectLen		->setValue(ALib->BConnectLen);

	ui.checkBModeEnabled		->setChecked(ALib->PointMove.ModeEnabled);
	ui.checkBModeAbsoluteBright	->setChecked(ALib->PointMove.ModeAbsoluteBright);
	ui.checkBModeNGCluster		->setChecked(ALib->PointMove.ModeNGCluster);
	ui.checkBModeDiffer			->setChecked(ALib->PointMove.ModeDiffer);
	ui.checkBModeOnlyMatching	->setChecked(ALib->PointMove.ModeOnlyMatching);
	ui.checkBModeWhiteMask		->setChecked(ALib->PointMove.ModeWhiteMask);
	ui.checkBModeBlackMask		->setChecked(ALib->PointMove.ModeBlackMask);
	ui.checkBModeCenterBrightFromParts	->setChecked(ALib->PointMove.ModeCenterBrightFromParts);
	ui.checkBModeAdjustable		->setChecked(ALib->PointMove.ModeAdjustable);
	ui.EditAdjustBlack			->setValue	(ALib->AdjustBlack);
	ui.EditAdjustWhite			->setValue	(ALib->AdjustWhite);
	ui.checkBModeCommonMovable	->setChecked(ALib->PointMove.ModeCommonMovable);
	ui.EditSelfSearch			->setValue	(ALib->SelfSearch);
	ui.EditCommonMoveDot		->setValue	(ALib->CommonMoveDot);
	ui.checkBModeInvertLogic	->setChecked(ALib->PointMove.ModeInvertLogic);
	ui.checkBModeOppositeRange	->setChecked(ALib->PointMove.ModeOppositeRange);
	ui.checkBModeUseGlobalLine	->setChecked(ALib->PointMove.ModeUseGlobalLine);

	ui.checkBLockFirst			->setChecked(ALib->GenerationMode.LockFirst);
	ui.EditRegularBrightness	->setValue	(ALib->RegularBrightness);
	ui.EditExpandForGenMask		->setValue	(ALib->ExpandForGenMask);
	ui.EditFollowLineLength		->setValue	(ALib->FollowLineLength);
	ui.checkBGen_Left			->setChecked(ALib->GenFollowLine.Gen_Left	);
	ui.checkBGen_Top			->setChecked(ALib->GenFollowLine.Gen_Top		);
	ui.checkBGen_Right			->setChecked(ALib->GenFollowLine.Gen_Right	);
	ui.checkBGen_Bottom			->setChecked(ALib->GenFollowLine.Gen_Bottom	);
	ui.EditFollowLineLayer		->setValue	(ALib->FollowLineLayer	);

	ui.checkBoxGenerateMultiLayer->setChecked((data.GetAdaptedGenLayers().GetCount()>1)?true:false);
	ui.checkBoxPickupMultiLayer	 ->setChecked((data.GetAdaptedPickLayers().GetCount()>1)?true:false);

	on_checkBoxGenerateMultiLayer_clicked();
	on_checkBoxPickupMultiLayer_clicked();

	for(IntClass *a=data.GetAdaptedPickLayers().GetFirst();a!=NULL;a=a->GetNext()){
		int	Layer=a->GetValue();
		if(0<=Layer && Layer<GetLayerNumb(0)){
			LayerPickButtons[Layer]->setChecked(true);
		}
	}
	for(int Layer=0;Layer<GetLayerNumb(0);Layer++){
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
		if(0<=Layer && Layer<GetLayerNumb(0)){
			LayerGenButtons[Layer]->setChecked(true);
		}
	}
	for(int Layer=0;Layer<GetLayerNumb(0);Layer++){
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

void	EditBlockLibrary::GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data)
{
	data.SetLibName(ui.EditLibName	->text());

	BlockLibrary	*ALib=dynamic_cast<BlockLibrary *>(data.GetLibrary());
	ALib->PickupL			=ui.EditPickupL			->value();
	ALib->PickupH			=ui.EditPickupH			->value();
	ALib->MinBlockSize		=ui.EditMinBlockSize	->value();
	ALib->MaxBlockSize		=ui.EditMaxBlockSize	->value();
	ALib->MinBlockDots		=ui.EditMinBlockDots	->value();
	ALib->MaxBlockDots		=ui.EditMaxBlockDots	->value();
	ALib->LimitBlockSize	=ui.EditLimitBlockSize	->value();
	ALib->SpaceToOutline	=ui.EditSpaceToOutline	->value();
	ALib->OutlineGeneration	=ui.EditOutlineGeneration->value();
	ALib->NoiseSize			=ui.EditNoiseSize		->value();
	ALib->NoiseSizePinHole	=ui.EditNoiseSizePinHole->value();
	ALib->Priority			=ui.EditPriority		->value();
	ALib->GenerationCategory=(BlockLibrary::_GenerationCategory)ui.comboBGenerationCategory	->currentIndex();
	ALib->GenerationMode.Transparent			=ui.checkBTransparent			->isChecked();
	ALib->GenerationMode.LeftPickup				=ui.checkBLeftPickup			->isChecked();
	ALib->GenerationMode.OverlappedGen			=ui.checkBOverlappedGen			->isChecked();
	ALib->GenerationMode.PlusHalfDotIsolation	=ui.checkBPlusHalfDotIsolation	->isChecked();
	ALib->GenerationMode.LockFirst				=ui.checkBLockFirst				->isChecked();
	ALib->GenerationMode.BindSmallBlock			=ui.checkBBindSmallBlock		->isChecked();
	//data.PointMove.ModeMatchPosition			=ui.checkBMatchPosition			->isChecked();
	if(ui.comboBoxMatchPosition	->currentIndex()==0){
		ALib->PointMove.ModeMatchPosition	=false;
		ALib->PointMove.ModeMatchPositionBW	=false;
	}
	else
	if(ui.comboBoxMatchPosition	->currentIndex()==1){
		ALib->PointMove.ModeMatchPosition	=true;
		ALib->PointMove.ModeMatchPositionBW	=false;
	}
	else
	if(ui.comboBoxMatchPosition	->currentIndex()==2){
		ALib->PointMove.ModeMatchPosition	=false;
		ALib->PointMove.ModeMatchPositionBW	=true;
	}
	else
	if(ui.comboBoxMatchPosition	->currentIndex()==3){
		ALib->PointMove.ModeMatchPosition	=true;
		ALib->PointMove.ModeMatchPositionBW	=true;
	}

	ALib->PointMove.ModeSearchDetail	=ui.checkBModeSearchDetail		->isChecked();
	ALib->PointMove.ModeDynamicMask		=ui.checkBModeDynamicMask		->isChecked();
	ALib->PointMove.ModeBindBWBroad		=ui.checkBModeBindBWBroad		->isChecked();
	ALib->PointMove.ModeBindBWNarrow	=ui.checkBModeBindBWNarrow		->isChecked();
	ALib->PointMove.ModeAdoptBiggest	=ui.checkBModeAdoptBiggest		->isChecked();
	ALib->PointMove.ModeUseMasterImage	=ui.checkBModeUseMasterImage	->isChecked();

	ALib->NBrightWidthL		=ui.EditNBrightWidthL	->value();
	ALib->NBrightWidthH		=ui.EditNBrightWidthH	->value();
	ALib->NOKDotL			=ui.EditNOKDotL			->value();
	ALib->NOKDotH			=ui.EditNOKDotH			->value();
	ALib->NMaxNGDotL		=ui.EditNMaxNGDotL		->value();
	ALib->NMaxNGDotH		=ui.EditNMaxNGDotH		->value();
	ALib->NOKLengthL		=ui.EditNOKLengthL		->value();
	ALib->NOKLengthH		=ui.EditNOKLengthH		->value();
	ALib->BBrightWidthL		=ui.EditBBrightWidthL	->value();
	ALib->BBrightWidthH		=ui.EditBBrightWidthH	->value();
	ALib->BOKDotL			=ui.EditBOKDotL			->value();
	ALib->BOKDotH			=ui.EditBOKDotH			->value();
	ALib->BMaxNGDotL		=ui.EditBMaxNGDotL		->value();
	ALib->BMaxNGDotH		=ui.EditBMaxNGDotH		->value();
	ALib->BOKLengthL		=ui.EditBOKLengthL		->value();
	ALib->BOKLengthH		=ui.EditBOKLengthH		->value();
	ALib->NMinNGCountL		=ui.EditNMinNGCountL	->value();
	ALib->NMinNGCountH		=ui.EditNMinNGCountH	->value();
	ALib->BMinNGCountL		=ui.EditBMinNGCountL	->value();
	ALib->BMinNGCountH		=ui.EditBMinNGCountH	->value();
	ALib->NConnectLen		=ui.EditNConnectLen		->value();
	ALib->BConnectLen		=ui.EditBConnectLen		->value();
	ALib->ExpandForGenMask	=ui.EditExpandForGenMask->value();
	ALib->FollowLineLength	=ui.EditFollowLineLength->value();
	ALib->GenFollowLine.Gen_Left	=ui.checkBGen_Left	->isChecked();
	ALib->GenFollowLine.Gen_Top		=ui.checkBGen_Top	->isChecked();
	ALib->GenFollowLine.Gen_Right	=ui.checkBGen_Right	->isChecked();
	ALib->GenFollowLine.Gen_Bottom	=ui.checkBGen_Bottom->isChecked();

	ALib->PointMove.ModeEnabled				=ui.checkBModeEnabled			->isChecked();
	ALib->PointMove.ModeAbsoluteBright		=ui.checkBModeAbsoluteBright	->isChecked();
	ALib->PointMove.ModeNGCluster			=ui.checkBModeNGCluster			->isChecked();
	ALib->PointMove.ModeDiffer				=ui.checkBModeDiffer			->isChecked();
	ALib->PointMove.ModeOnlyMatching		=ui.checkBModeOnlyMatching		->isChecked();
	ALib->PointMove.ModeWhiteMask			=ui.checkBModeWhiteMask			->isChecked();
	ALib->PointMove.ModeBlackMask			=ui.checkBModeBlackMask			->isChecked();
	ALib->PointMove.ModeCenterBrightFromParts=ui.checkBModeCenterBrightFromParts	->isChecked();
	ALib->PointMove.ModeAdjustable			=ui.checkBModeAdjustable		->isChecked();
	ALib->PointMove.ModeInvertLogic			=ui.checkBModeInvertLogic		->isChecked();
	ALib->PointMove.ModeOppositeRange		=ui.checkBModeOppositeRange		->isChecked();
	ALib->PointMove.ModeUseGlobalLine		=ui.checkBModeUseGlobalLine		->isChecked();

	ALib->AdjustBlack						=ui.EditAdjustBlack		->value();
	ALib->AdjustWhite						=ui.EditAdjustWhite		->value();
	ALib->PointMove.ModeCommonMovable		=ui.checkBModeCommonMovable	->isChecked();
	ALib->SelfSearch						=ui.EditSelfSearch		->value();
	ALib->CommonMoveDot						=ui.EditCommonMoveDot	->value();
	ALib->RegularBrightness					=ui.EditRegularBrightness	->value();
	ALib->FollowLineLayer					=ui.EditFollowLineLayer		->value();

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

void EditBlockLibrary::on_ButtonLibNew_clicked()
{
	if(TempLib==NULL)
		return;
	TempLib->Reset();
	CmdClearBlockLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	BlockBase	*BBase=GetBlockBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);
	}
	ShowLibrary(*TempLib);
	ui.ButtonLibSave	->setEnabled(false);
	ui.ButtonLibDelete	->setEnabled(false);
}

void EditBlockLibrary::on_ButtonLibDelete_clicked()
{
	if(TempLib==NULL)
		return;
	if(TempLib->GetLibID()<0)
		return;
	QString  msg=LangSolver.GetString(EditBlockLibrary_LS,LID_55)/*"Delete OK?"*/;
	int	ret=QMessageBox::question(NULL
					, LangSolver.GetString(EditBlockLibrary_LS,LID_56)/*"Choose"*/
					, msg
					, QMessageBox::Yes , QMessageBox::No, QMessageBox::NoButton);
	if(ret==QMessageBox::Yes){
		CmdDeleteBlockLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		BlockBase	*BBase=GetBlockBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			on_ButtonLibNew_clicked();
			SlotSelectLibFolder(LibFolderID 
							,/**/"");
		}
	}
}

void EditBlockLibrary::on_ButtonLibSaveNew_clicked()
{
	if(TempLib==NULL)
		return;
	GetLibraryFromWindow(*TempLib);

	if(TempLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL
															, LangSolver.GetString(EditBlockLibrary_LS,LID_59)/*"Warning"*/
															, LangSolver.GetString(EditBlockLibrary_LS,LID_60)/*"No Library Name"*/
															, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	TempLib->SetLibFolderID(LibFolderID);
	CmdInsertBlockLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	BlockBase	*BBase=GetBlockBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);		
		ShowLibrary(*TempLib);
		ui.ButtonLibSave	->setEnabled(true);
		ui.ButtonLibDelete	->setEnabled(true);
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}

void EditBlockLibrary::on_ButtonLibSave_clicked()
{
	if(TempLib==NULL)
		return;
	GetLibraryFromWindow(*TempLib);
	if(TempLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL
															, LangSolver.GetString(EditBlockLibrary_LS,LID_63)/*"Warning"*/
															, LangSolver.GetString(EditBlockLibrary_LS,LID_64)/*"No Library Name"*/
															, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	if(TempLib->GetLibID()<0){
		TempLib->SetLibFolderID(LibFolderID);

		CmdInsertBlockLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		BlockBase	*BBase=GetBlockBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			ShowLibrary(*TempLib);
			ui.ButtonLibSave	->setEnabled(true);
			ui.ButtonLibDelete	->setEnabled(true);
		}
	}
	else{
		CmdUpdateBlockLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		BlockBase	*BBase=GetBlockBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
		}
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}

void EditBlockLibrary::on_pushButton_clicked()
{
	close();
}

void EditBlockLibrary::on_toolButtonPickup_clicked()
{
	if(ui.toolButtonPickup->isChecked()==true)
		ui.stackedWidget->setCurrentIndex(0);
}


void EditBlockLibrary::on_toolButtonInspect_clicked()
{
	if(ui.toolButtonInspect->isChecked()==true)
		ui.stackedWidget->setCurrentIndex(1);
}

void EditBlockLibrary::on_checkBoxGenerateMultiLayer_clicked()
{
	int	n=LayerGenButtons.count();
	for(int i=0;i<n;i++){
		QToolButton	*b=LayerGenButtons[i];
		b->setAutoExclusive(!ui.checkBoxGenerateMultiLayer->isChecked());
	}
}

void EditBlockLibrary::on_checkBoxPickupMultiLayer_clicked()
{
	int	n=LayerPickButtons.count();
	for(int i=0;i<n;i++){
		QToolButton	*b=LayerPickButtons[i];
		b->setAutoExclusive(!ui.checkBoxPickupMultiLayer->isChecked());
	}
}
