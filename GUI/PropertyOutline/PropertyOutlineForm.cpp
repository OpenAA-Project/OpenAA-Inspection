#include "PropertyOutlineResource.h"
#include "PropertyOutlineForm.h"
#include "ui_PropertyOutlineForm.h"
#include "XDLLOnly.h"
//#include "ImageControlTools.h"
#include "OutlinePickupMonoForm.h"
#include "XPropertyOutlinePacket.h"
#include "OutlinePickupForm.h"
#include "OutlineEditLibraryForm.h"
#include "XDatabaseLoader.h"
#include "XDisplayImagePacket.h"
#include "XGUIPacketGeneral.h"
#include <QMessageBox>
#include "XGeneralDialog.h"
#include "XRememberer.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

PropertyOutlineForm::PropertyOutlineForm(LayersBase* Base, QWidget *parent) :
    GUIFormBase(Base, parent),
    ui(new Ui::PropertyOutlineForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	LibFolderID = -1;
	OutlineBase* BBase = GetOutlineBase();
	LibType = -1;
	if (BBase != NULL)
		LibType = BBase->GetLibType();
	ui->tableWidgetLibList->setColumnWidth(0, 30);
	ui->tableWidgetLibList->setColumnWidth(1, 80);
	ui->tableWidgetGeneratedLibList->setColumnWidth(0, 30);
	ui->tableWidgetGeneratedLibList->setColumnWidth(1, 80);

	ui->tableWidgetBlockInfo->setColumnCount(3);
	ui->tableWidgetBlockInfo->setColumnWidth(0, 30);
	ui->tableWidgetBlockInfo->setColumnWidth(1, 150);
	ui->tableWidgetBlockInfo->setColumnWidth(2, 80);
	QStringList	HeaderLabel;
	HeaderLabel.append(LangSolver.GetString(PropertyOutlineForm_LS, LID_0)/*"ID"*/);
	HeaderLabel.append(LangSolver.GetString(PropertyOutlineForm_LS, LID_1)/*"??????C??u????????????"*/);
	HeaderLabel.append(LangSolver.GetString(PropertyOutlineForm_LS, LID_2)/*"??u??????b??N????????"*/);
	ui->tableWidgetBlockInfo->setHorizontalHeaderLabels(HeaderLabel);

	TabBarBlockOnMouse.setParent(ui->frameBlockInfoOnMouse);
	TabBarBlockOnMouse.setGeometry(ui->frame->geometry().left(), ui->frame->geometry().top() - 30, ui->frame->geometry().width(), 30);
	connect(&TabBarBlockOnMouse, SIGNAL(currentChanged(int)), this, SLOT(TabBarBlockOnMouseChanged(int)));

	for (int i = 0; i < sizeof(BInfo) / sizeof(BInfo[0]); i++) {
		BInfo[i].OutlineInfoOnMouse = NULL;
	}

	TempLib = NULL;
	if (BBase != NULL) {
		CmdCreateTempOutlineLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		TempLib = Packet.Point;
	}

	if (GetLayerNumb(0) >= 3) {
		ui->stackedWidgetOutside->setCurrentIndex(0);
		ui->stackedWidgetInside->setCurrentIndex(0);
		ui->stackedWidgetBOutside->setCurrentIndex(0);
		ui->stackedWidgetBInside->setCurrentIndex(0);

		ColorInside.setParent(ui->stackedframeInside->widget(0));
		ColorOutside.setParent(ui->stackedframeOutside->widget(0));
		TrColorInside.setParent(ui->stackedframeInside->widget(1));
		TrColorOutside.setParent(ui->stackedframeOutside->widget(1));
		ColorBInside.setParent(ui->stackedframeBInside->widget(0));
		ColorBOutside.setParent(ui->stackedframeBOutside->widget(0));
		TrColorBInside.setParent(ui->stackedframeBInside->widget(1));
		TrColorBOutside.setParent(ui->stackedframeBOutside->widget(1));

		ColorInside.Fit(ui->stackedframeInside->widget(0));
		ColorOutside.Fit(ui->stackedframeOutside->widget(0));
		TrColorInside.Fit(ui->stackedframeInside->widget(1));
		TrColorOutside.Fit(ui->stackedframeOutside->widget(1));
		ColorBInside.Fit(ui->stackedframeBInside->widget(0));
		ColorBOutside.Fit(ui->stackedframeBOutside->widget(0));
		TrColorBInside.Fit(ui->stackedframeBInside->widget(1));
		TrColorBOutside.Fit(ui->stackedframeBOutside->widget(1));
	}
	else if (GetLayerNumb(0) == 1) {
		ui->stackedWidgetOutside->setCurrentIndex(1);
		ui->stackedWidgetInside->setCurrentIndex(1);
		ui->stackedWidgetBOutside->setCurrentIndex(1);
		ui->stackedWidgetBInside->setCurrentIndex(1);
	}

	if (ui->toolButtonLibrary->isChecked() == true) {
		ui->stackedWidget->setCurrentIndex(0);
	}
	if (ui->toolButtonCreateBlock->isChecked() == true) {
		ui->stackedWidget->setCurrentIndex(1);
		ShowBlockInfoList();
	}
	
	int	LibFolderID=ControlRememberer::GetInt(objectName()+/**/"\\LibFolderID",-1);
	if(LibFolderID>=0){
		QString	FolderName=GetLayersBase()->GetLibFolderName(LibFolderID);
		SetLibFolder(LibFolderID,FolderName);
	}
	InstallIgnoreKeyForChild();
}

PropertyOutlineForm::~PropertyOutlineForm()
{
    delete ui;
	if (TempLib != NULL)
		delete	TempLib;
}

OutlineBase* PropertyOutlineForm::GetOutlineBase(void)
{
	return (OutlineBase*)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"OutlineInspection");
}

void	PropertyOutlineForm::ShowTab(void)
{
	int	r = TabBarBlockOnMouse.currentIndex();
	while (TabBarBlockOnMouse.count() != 0) {
		TabBarBlockOnMouse.removeTab(0);
	}
	for (int i = 0; i < sizeof(BInfo) / sizeof(BInfo[0]); i++) {
		if (BInfo[i].OutlineInfoOnMouse != NULL) {
			TabBarBlockOnMouse.addTab(QString(/**/"Page-") + QString::number(BInfo[i].Page));
		}
	}
	if (0 <= r && TabBarBlockOnMouse.count() > r) {
		TabBarBlockOnMouse.setCurrentIndex(r);
	}
}

void	PropertyOutlineForm::TabBarBlockOnMouseChanged(int index)
{
	if (index >= 0 && BInfo[index].OutlineInfoOnMouse != NULL) {
		ui->EditLibIDInBlock->setText(QString::number(BInfo[index].OutlineInfoOnMouse->GetLibID()));
		OutlineBase* BBase = GetOutlineBase();
		CmdGetLibName	Cmd(GetLayersBase());
		Cmd.LibID = BInfo[index].OutlineInfoOnMouse->GetLibID();
		BBase->TransmitDirectly(&Cmd);
		ui->EditLibNameInBlock->setText(Cmd.LibName);

		ui->EditInsideMergin->setValue(BInfo[index].OutlineInfoOnMouse->GetThresholdR()->InsideNMergin);
		ui->EditInsideOKDot->setValue(BInfo[index].OutlineInfoOnMouse->GetThresholdR()->InsideNOKDot);

		ui->EditOutsideMergin->setValue(BInfo[index].OutlineInfoOnMouse->GetThresholdR()->OutsideNMergin);
		ui->EditOutsideOKDot->setValue(BInfo[index].OutlineInfoOnMouse->GetThresholdR()->OutsideNOKDot);

		ui->EditInsideBMergin->setValue(BInfo[index].OutlineInfoOnMouse->GetThresholdR()->InsideBMergin);
		ui->EditInsideBOKDot->setValue(BInfo[index].OutlineInfoOnMouse->GetThresholdR()->InsideBOKDot);

		ui->EditOutsideBMergin->setValue(BInfo[index].OutlineInfoOnMouse->GetThresholdR()->OutsideBMergin);
		ui->EditOutsideBOKDot->setValue(BInfo[index].OutlineInfoOnMouse->GetThresholdR()->OutsideBOKDot);

		ui->checkBoxEffectiveNInside->setChecked(BInfo[index].OutlineInfoOnMouse->GetThresholdR()->EffectiveNInside);
		ui->checkBoxEffectiveNOutside->setChecked(BInfo[index].OutlineInfoOnMouse->GetThresholdR()->EffectiveNOutside);
		ui->checkBoxEffectiveBInside->setChecked(BInfo[index].OutlineInfoOnMouse->GetThresholdR()->EffectiveBInside);
		ui->checkBoxEffectiveBOutside->setChecked(BInfo[index].OutlineInfoOnMouse->GetThresholdR()->EffectiveBOutside);

		ui->EditSelfSearch->setValue(BInfo[index].OutlineInfoOnMouse->GetThresholdR()->SelfSearch);
		//ui->checkBoxAdjustMode	->setChecked(BInfo[index].OutlineInfoOnMouse->GetThresholdR()->AdjustMode);
		//ui->EditAdjustLimitL		->setValue(BInfo[index].OutlineInfoOnMouse->GetThresholdR()->AdjustLimitL);
		//ui->EditAdjustLimitH		->setValue(BInfo[index].OutlineInfoOnMouse->GetThresholdR()->AdjustLimitH);


		int	ColL, ColH;
		BInfo[index].OutlineInfoOnMouse->GetThresholdW()->InsideNOKColor.GetRelMonoRange(ColL, ColH);
		ui->EditInsideColorL->setValue(ColL);
		ui->EditInsideColorH->setValue(ColH);

		BInfo[index].OutlineInfoOnMouse->GetThresholdW()->OutsideNOKColor.GetRelMonoRange(ColL, ColH);
		ui->EditOutsideColorL->setValue(ColL);
		ui->EditOutsideColorH->setValue(ColH);

		BInfo[index].OutlineInfoOnMouse->GetThresholdW()->InsideBOKColor.GetRelMonoRange(ColL, ColH);
		ui->EditInsideBColorL->setValue(ColL);
		ui->EditInsideBColorH->setValue(ColH);

		BInfo[index].OutlineInfoOnMouse->GetThresholdW()->OutsideBOKColor.GetRelMonoRange(ColL, ColH);
		ui->EditOutsideBColorL->setValue(ColL);
		ui->EditOutsideBColorH->setValue(ColH);
		/*
		ui->EditNOKDot			->setValue(BInfo[index].OutlineInfoOnMouse->GetThresholdR()->NOKDot		);
		ui->EditNMergin			->setValue(BInfo[index].OutlineInfoOnMouse->GetThresholdR()->NMergin		);
		ui->EditBOKDot			->setValue(BInfo[index].OutlineInfoOnMouse->GetThresholdR()->BOKDot		);
		ui->EditBMergin			->setValue(BInfo[index].OutlineInfoOnMouse->GetThresholdR()->BMergin		);

		ui->checkBModeAdjustable	->setChecked(BInfo[index].OutlineInfoOnMouse->GetThresholdR()->PointMove.ModeAdjustable	);
		ui->EditAdjustBlack		->setValue(BInfo[index].OutlineInfoOnMouse->GetThresholdR()->AdjustBlack	);
		ui->EditAdjustWhite		->setValue(BInfo[index].OutlineInfoOnMouse->GetThresholdR()->AdjustWhite	);

		ui->EditNMinNGCount		->setValue(BInfo[index].OutlineInfoOnMouse->GetThresholdR()->NMinNGCount);
		ui->EditBMinNGCount		->setValue(BInfo[index].OutlineInfoOnMouse->GetThresholdR()->BMinNGCount);

		ui->EditSelfSearch		->setValue(BInfo[index].OutlineInfoOnMouse->GetThresholdR()->SelfSearch		);
		*/
	}
	else {
		/*
		ui->EditLibIDInBlock		->clear();
		ui->EditLibNameInBlock	->clear();

		ui->EditNOKDot			->clear();
		ui->EditNMergin			->clear();
		ui->EditBOKDot			->clear();
		ui->EditBMergin			->clear();

		ui->EditNMinNGCount		->clear();
		ui->EditBMinNGCount		->clear();


		ui->checkBModeAdjustable	->setChecked(false);
		ui->EditAdjustBlack		->clear();
		ui->EditAdjustWhite		->clear();

		ui->EditSelfSearch		->clear();
		*/
	}
}

void	PropertyOutlineForm::ShowLibList(void)
{
	ui->tableWidgetLibList->setRowCount(0);
	OutlineBase* BBase = GetOutlineBase();
	if (BBase != NULL) {
		CmdGetOutlineLibraryListPacket	Packet(GetLayersBase());
		Packet.LibFolderID = LibFolderID;
		BBase->TransmitDirectly(&Packet);
		LibList = Packet.AList;
		int	row = 0;
		ui->tableWidgetLibList->setRowCount(Packet.AList.GetNumber());
		for (AlgorithmLibraryList* a = Packet.AList.GetFirst(); a != NULL; a = a->GetNext(), row++) {
			QTableWidgetItem* W;
			W = ui->tableWidgetLibList->item(row, 0);
			if (W == NULL) {
				W = new QTableWidgetItem();
				ui->tableWidgetLibList->setItem(row, 0, W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			W->setText(QString::number(a->GetLibID()));
			W = ui->tableWidgetLibList->item(row, 1);
			if (W == NULL) {
				W = new QTableWidgetItem();
				ui->tableWidgetLibList->setItem(row, 1, W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			W->setText(a->GetLibName());
		}
	}
}
void	PropertyOutlineForm::ShowInEdit(void)
{
	GUIFormBase* GProp = GetLayersBase()->FindByName(	/**/"Inspection"
		,/**/"OutlineImagePanel"
		,/**/"");
	if (GProp != NULL) {
		DisplayImage* d = dynamic_cast<DisplayImage*>(GProp);
		if (d != NULL) {
			IntList	LayerList;
			d->GetActiveLayerList(LayerList);
			if (LayerList.GetCount() < 3) {
				ui->stackedWidgetOutside->setCurrentIndex(1);
				ui->stackedWidgetInside->setCurrentIndex(1);
				ui->stackedWidgetBOutside->setCurrentIndex(1);
				ui->stackedWidgetBInside->setCurrentIndex(1);
			}
			else {
				ui->stackedWidgetOutside->setCurrentIndex(0);
				ui->stackedWidgetInside->setCurrentIndex(0);
				ui->stackedWidgetBOutside->setCurrentIndex(0);
				ui->stackedWidgetBInside->setCurrentIndex(0);
			}
		}
	}
	ShowBlockInfoList();
}
void	PropertyOutlineForm::StartPage(void)
{
	int	MasterID = GetLayersBase()->GetMasterCode();
	if (MasterID >= 0 && LibFolderID < 0) {
		QString		FolderName;
		LibFolderID = GetLayersBase()->GetDatabaseLoader()->S_GetFirstLibFolderByMasterCode(GetLayersBase()->GetDatabase(), MasterID, FolderName);
		ui->labelLibFolderName->setText(FolderName);
	}
	ShowBlockInfoList();
}

void	PropertyOutlineForm::BuildForShow(void)
{
	StartPage();
}

void	PropertyOutlineForm::TransmitDirectly(GUIDirectMessage* packet)
{
	OutlineBase* BBase = GetOutlineBase();
	CmdOutlineDrawModePacket* BDrawModePacket = dynamic_cast<CmdOutlineDrawModePacket*>(packet);
	if (BDrawModePacket != NULL) {
		if (ui->toolButtonLibrary->isChecked() == true)
			BDrawModePacket->Mode = CmdOutlineDrawModePacket::_LibTest;
		else if (ui->toolButtonCreateBlock->isChecked() == true)
			BDrawModePacket->Mode = CmdOutlineDrawModePacket::_CreatedBlock;
		if (ui->toolButtonArea->isChecked() == true)
			BDrawModePacket->DType = CmdOutlineDrawModePacket::_Area;
		else if (ui->toolButtonEdge->isChecked() == true)
			BDrawModePacket->DType = CmdOutlineDrawModePacket::_Edge;
		else if (ui->toolButtonInside->isChecked() == true)
			BDrawModePacket->DType = CmdOutlineDrawModePacket::_Inside;
		return;
	}
	CmdOutlineDrawEnd* BlockDEnd = dynamic_cast<CmdOutlineDrawEnd*>(packet);
	if (BlockDEnd != NULL) {
		if (ui->toolButtonLibrary->isChecked() == true) {
			IntList PageList;
			GetLayersBase()->GetLocalPageFromArea(BlockDEnd->Area, PageList);
			if (PageList.GetFirst() == NULL) {
				return;
			}
			RGBStock	RGBColors;
			for (IntClass* PageClass = PageList.GetFirst(); PageClass != NULL; PageClass = PageClass->GetNext()) {
				int	globalPage = PageClass->GetValue();
				FlexArea	A;
				A = BlockDEnd->Area;
				GetLayersBase()->GetPageData(globalPage)->ClipMoveAreaFromGlobal(A);

				GUICmdReqRGBStockFromArea	RCmd(GetLayersBase(), sRoot, sName, globalPage);
				GUICmdSendRGBStockFromArea	SCmd(GetLayersBase(), sRoot, sName, globalPage);
				RCmd.Area = A;
				RCmd.LayerList = BlockDEnd->LayerList;
				RCmd.Send(globalPage, 0, SCmd);
				RGBColors += SCmd.RGBColors;
			}
			/*
			if(GetLayerNumb()>=3){
				OutlinePickupForm	D(GetLayersBase()
									,&RGBColors
									,&ColorGenerator.Cube
									,this);
				if(D.exec()==(int)true){
					ColorGenerator.Cube=D.ColorPanel.Cube;
					ColorGenerator.InitializedDoneCube();
					ColorGenerator.Repaint();
					TempLib->PickupColor	=D.ColorPanel.Cube;
				}
			}
			else if(GetLayerNumb()==1){
			}
			*/
			if (BlockDEnd->LayerList.IsEmpty() == false) {
				GUIFormBase* GProp = GetLayersBase()->FindByName(	/**/"Inspection"
					,/**/"OutlineImagePanel"
					,/**/"");
				if (GProp != NULL) {
					OutlineInspectLibrary	*ALib=dynamic_cast<OutlineInspectLibrary *>(TempLib->GetLibrary());
					int pickupL, pickupH;
					ALib->PickupColor.GetMonoColorRange(pickupL, pickupH);
					OutlinePickupMonoForm	D(BlockDEnd->Area
						, (OutlineImagePanel*)GProp, pickupL, pickupH);
					if (D.exec() == (int)true) {
						/*
						if(BlockDEnd->LayerList.GetFirst()->GetValue()==0){
							TempLib->PickupColor.SetMonoColorRange(D.PickupL,D.PickupH
																,  0,255
																,  0,255);
						}
						else if(BlockDEnd->LayerList.GetFirst()->GetValue()==1){
							TempLib->PickupColor.SetMonoColorRange(0,255
																,  D.PickupL,D.PickupH
																,  0,255);
						}
						else if(BlockDEnd->LayerList.GetFirst()->GetValue()==2){
							TempLib->PickupColor.SetMonoColorRange(0,255
																,  0,255
																,  D.PickupL,D.PickupH);
						}
						*/
						ALib->PickupColor.SetMonoColorRange(D.PickupL, D.PickupH
							, 0, 255
							, 0, 255);

					}
				}
			}
		}
		/*
		else if(ui->toolButtonCreateBlock->isChecked()==true){
			TrueColorCreateManualBlockForm	D(GetLayersBase(),NULL);
			if(D.exec()==(int)true && D.BItem->GetLibID()>=0){
				IntList PageList;
				GetLayersBase()->GetLocalPageFromArea(BlockDEnd->Area,PageList);
				for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
					int	page=P->GetValue();
					DataInPage	*pdata=GetLayersBase()->GetPageData(page);
					FlexArea	A=BlockDEnd->Area;
					pdata->ClipMoveAreaFromGlobal(A);
					if(A.GetPatternByte()>0){
						GUICmdSendAddManualOutline	Cmd(GetLayersBase(),sRoot,sName,page);
						Cmd.Area=A;
						CmdCreateByteArrayFromOutlineItemPacket	BCmd;
						BCmd.Point=D.BItem;
						BBase->TransmitDirectly(&BCmd);
						Cmd.BItem=BCmd.Buff;
						Cmd.Send(NULL,page,0);
					}
				}
				ShowBlockInfoList();
			}
		}
		*/
	}
	/*
	CmdOutlineShowAttrPacket	*ShowAttr=dynamic_cast<CmdOutlineShowAttrPacket *>(packet);
	if(ShowAttr!=NULL){

	}
	*/
	CmdExecuteMouseLDown* CmdExecuteMouseLDownVar = dynamic_cast<CmdExecuteMouseLDown*>(packet);
	if (CmdExecuteMouseLDownVar != NULL) {
		for (int i = 0; i < sizeof(BInfo) / sizeof(BInfo[0]); i++) {
			//if(BInfo[i].BlockInfoOnMouse!=NULL)
			//	delete	BInfo[i].BlockInfoOnMouse;
			BInfo[i].OutlineInfoOnMouse = NULL;
		}
		int	N = 0;
		for (IntClass* p = CmdExecuteMouseLDownVar->PageList.GetFirst(); p != NULL; p = p->GetNext()) {
			int page = p->GetValue();
			ListLayerAndIDPack	Items;
			if (N >= sizeof(BInfo) / sizeof(BInfo[0]))
				break;
			for (ListPageLayerID* a = CmdExecuteMouseLDownVar->CurrentItem.GetFirst(); a != NULL; a = a->GetNext()) {
				if (a->Page == page) {
					Items.AppendList(new ListLayerAndID(0, a->ID));
				}
			}
			if (Items.GetNumber() != NULL) {
				GUICmdReqOutlineFromList	ReqCmd(GetLayersBase(), sRoot, sName, page);
				GUICmdAckOutlineFromList	AckCmd(GetLayersBase(), sRoot, sName, page);
				ReqCmd.CurrentItem = Items;
				ReqCmd.Send(page, 0, AckCmd);
				for (int i = 0; i < sizeof(AckCmd.OutlineInfoOnMouse) / sizeof(AckCmd.OutlineInfoOnMouse[0]); i++) {
					if (AckCmd.OutlineInfoOnMouse[i] != NULL) {
						BInfo[N].OutlineInfoOnMouse = AckCmd.OutlineInfoOnMouse[i];
						AckCmd.OutlineInfoOnMouse[i] = NULL;
						BInfo[N].Page = page;
						BInfo[N].Layer = 0;
						N++;
						if (N >= sizeof(BInfo) / sizeof(BInfo[0]))
							break;
					}
				}
			}
		}
		ShowTab();
		return;
	}
	/*
	CmdExecuteMouseRDownWithShift	*ShiftRight=dynamic_cast<CmdExecuteMouseRDownWithShift *>(packet);
	if(ShiftRight!=NULL){
		QByteArray	BlockItemData;
		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
			GUICmdReqSelectedOutlineItemAttr		ReqCmd(GetLayersBase(),sRoot,sName,page);
			GUICmdSendSelectedOutlineItemAttr	SendCmd(GetLayersBase(),sRoot,sName,page);
			if(ReqCmd.Send(ReqCmd.GetGlobalPage(),0,SendCmd)==true
			&& SendCmd.IsReceived()==true){
				if(SendCmd.ExistSelected==true){
					BlockItemData=SendCmd.BItem;
					break;
				}
			}
		}
		if(BlockItemData.size()!=0){
		}
	}
	*/
	CmdReqSetButtonMode* CmdReqSetButtonModeVar = dynamic_cast<CmdReqSetButtonMode*>(packet);
	if (CmdReqSetButtonModeVar != NULL) {
		if (CmdReqSetButtonModeVar->Mode == GUICmdReqSetButtonMode::_LibraryTest) {
			ui->toolButtonLibrary->setChecked(true);
		}
		if (CmdReqSetButtonModeVar->Mode == GUICmdReqSetButtonMode::_CreateBlock) {
			ui->toolButtonCreateBlock->setChecked(true);
		}
		if (CmdReqSetButtonModeVar->DType == GUICmdReqSetButtonMode::_Area) {
			ui->toolButtonArea->setChecked(true);
		}
		if (CmdReqSetButtonModeVar->DType == GUICmdReqSetButtonMode::_Edge) {
			ui->toolButtonEdge->setChecked(true);
		}
		if (CmdReqSetButtonModeVar->DType == GUICmdReqSetButtonMode::_Inside) {
			ui->toolButtonInside->setChecked(true);
		}
	}
}


bool	PropertyOutlineForm::SaveContent(QIODevice* f)
{
	WORD	Ver = 1;
	if (::Save(f, Ver) == false)
		return false;

	if (::Save(f, LibType) == false)
		return false;
	if (LibList.Save(f) == false)
		return false;
	if (SelectedLibList.Save(f) == false)
		return false;
	if (::Save(f, LibFolderID) == false)
		return false;
	if (GlobalPickupArea.Save(f) == false)
		return false;
	return true;
}
bool	PropertyOutlineForm::LoadContent(QIODevice* f)
{
	WORD	Ver;
	if (::Load(f, Ver) == false)
		return false;

	if (::Load(f, LibType) == false)
		return false;
	if (LibList.Load(f) == false)
		return false;
	if (SelectedLibList.Load(f) == false)
		return false;
	if (::Load(f, LibFolderID) == false)
		return false;
	if (GlobalPickupArea.Load(f) == false)
		return false;
	ShowLibList();
	ShowSelectedLibList();

	QString FolderName;
	int ParentID;
	int NumberInFolder;
	if (GetLayersBase()->GetDatabaseLoader()->S_LibFolderFindData(GetLayersBase()->GetDatabase(), LibFolderID, FolderName, ParentID, NumberInFolder) == true) {
		SetLibFolder(LibFolderID, FolderName);
	}
	return true;
}

void	PropertyOutlineForm::ShowLibrary(AlgorithmLibraryLevelContainer& data)
{
	if (data.GetLibID() < 0)
		ui->EditLibID->setText(/**/"");
	else
		ui->EditLibID->setText(QString::number(data.GetLibID()));
	ui->EditLibName->setText(data.GetLibName());

	OutlineInspectLibrary	*ALib=dynamic_cast<OutlineInspectLibrary *>(data.GetLibrary());
	ui->EditTransDot		->setValue(ALib->TransDot);
	ui->EditInsideWidth		->setValue(ALib->InsideWidth);
	ui->EditOutsideWidth	->setValue(ALib->OutsideWidth);
	ui->EditNoiseDot		->setValue(ALib->NoiseDot);
	ui->EditPriority		->setValue(ALib->Priority);
	ui->EditChoppedLength	->setValue(ALib->ChoppedLength);
	ui->checkBoxMatchSlideOnMaster->setChecked(ALib->MatchSlideOnMaster);

	ui->EditMinAreaSize		->setValue(ALib->MinAreaSize);
	ui->EditMaxAreaSize		->setValue(ALib->MaxAreaSize);
	ui->EditMinAreaDot		->setValue(ALib->MinAreaDot);
	ui->EditMaxAreaDot		->setValue(ALib->MaxAreaDot);

	ui->EditInsideTrWidth	->setValue(ALib->InsideTrWidth);
	ui->EditOutsideTrWidth	->setValue(ALib->OutsideTrWidth);
}

void	PropertyOutlineForm::GetLibraryFromWindow(AlgorithmLibraryLevelContainer& data)
{
	data.SetLibName(ui->EditLibName->text());

	OutlineInspectLibrary	*ALib=dynamic_cast<OutlineInspectLibrary *>(data.GetLibrary());
	ALib->TransDot		= ui->EditTransDot->value();
	ALib->InsideWidth	= ui->EditInsideWidth->value();
	ALib->OutsideWidth	= ui->EditOutsideWidth->value();
	ALib->NoiseDot		= ui->EditNoiseDot->value();
	ALib->Priority		= ui->EditPriority->value();
	ALib->ChoppedLength = ui->EditChoppedLength->value();
	ALib->MatchSlideOnMaster = ui->checkBoxMatchSlideOnMaster->isChecked();

	ALib->MinAreaSize	= ui->EditMinAreaSize->value();
	ALib->MaxAreaSize	= ui->EditMaxAreaSize->value();
	ALib->MinAreaDot	= ui->EditMinAreaDot->value();
	ALib->MaxAreaDot	= ui->EditMaxAreaDot->value();

	ALib->InsideTrWidth = ui->EditInsideTrWidth->value();
	ALib->OutsideTrWidth= ui->EditOutsideTrWidth->value();
}


void PropertyOutlineForm::on_ButtonLibSave_clicked()
{
	if (TempLib == NULL || TempLib->GetLibID() < 0)
		return;
	GetLibraryFromWindow(*TempLib);
	if (TempLib->GetLibName() ==/**/"") {
		QMessageBox::StandardButton ret = QMessageBox::warning(NULL, LangSolver.GetString(PropertyOutlineForm_LS, LID_6)/*"Warning"*/
			, LangSolver.GetString(PropertyOutlineForm_LS, LID_7)/*"No Library Name"*/
			, QMessageBox::Ok | QMessageBox::Cancel);
		if (ret != QMessageBox::Ok)
			return;
	}
	CmdUpdateOutlineLibraryPacket	Packet(GetLayersBase());
	Packet.Point = TempLib;
	OutlineBase* BBase = GetOutlineBase();
	if (BBase != NULL) {
		BBase->TransmitDirectly(&Packet);
	}
	for (AlgorithmLibraryList* a = SelectedLibList.GetFirst(); a != NULL; a = a->GetNext()) {
		if (a->GetLibID() == TempLib->GetLibID()) {
			a->SetLibName(TempLib->GetLibName());
		}
	}
	ShowLibList();
	ShowSelectedLibList();
}

void PropertyOutlineForm::on_tableWidgetLibList_clicked(const QModelIndex& Index)
{
	int	r = Index.row();
	AlgorithmLibraryList* a = LibList.GetItem(r);
	if (a != NULL) {
		TempLib->SetLibID(a->GetLibID());
		CmdLoadOutlineLibraryPacket	Packet(GetLayersBase());
		Packet.Point = TempLib;
		OutlineBase* BBase = GetOutlineBase();
		if (BBase != NULL) {
			BBase->TransmitDirectly(&Packet);
			if (Packet.Success == true) {
				SetLayersFromLib(TempLib->GetAdaptedPickLayers());
				ShowLibrary(*TempLib);
			}
			else {
				QMessageBox::critical(NULL, LangSolver.GetString(PropertyOutlineForm_LS, LID_8)/*"Library error"*/
					, LangSolver.GetString(PropertyOutlineForm_LS, LID_9)/*"Not loaded this library record"*/);
			}
		}
	}
}
void PropertyOutlineForm::SetLayersFromLib(IntList& LayerList)
{
	GUIFormBase* GProp = GetLayersBase()->FindByName(/**/"Inspection",/**/"OutlineImagePanel",/**/"");
	if (GProp != NULL) {
		DisplayImage* di = dynamic_cast<DisplayImage*>(GProp);
		if (di != NULL) {
			di->SetActiveLayerList(LayerList);
		}
	}
}
void PropertyOutlineForm::on_tableWidgetLibList_doubleClicked(const QModelIndex &)
{
	on_pushButtonSetFrom_clicked();
}

void PropertyOutlineForm::on_tableWidgetGeneratedLibList_doubleClicked(const QModelIndex &)
{
	on_pushButtonGetBack_clicked();
}

struct	AlgorithmLibraryListClass
{
	AlgorithmLibraryList* a;
	int						Priority;
};

int	DDimFunc(const void* a, const void* b)
{
	if (((struct AlgorithmLibraryListClass*)a)->Priority > ((struct AlgorithmLibraryListClass*)b)->Priority)
		return 1;
	if (((struct AlgorithmLibraryListClass*)a)->Priority < ((struct AlgorithmLibraryListClass*)b)->Priority)
		return -1;
	return 0;
}


void	PropertyOutlineForm::ShowSelectedLibList(void)
{
	struct	AlgorithmLibraryListClass	DDim[100];

	OutlineBase* BBase = GetOutlineBase();
	if (BBase != NULL) {
		CmdCreateTempOutlineLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		AlgorithmLibraryLevelContainer* SLib = Packet.Point;
		OutlineInspectLibrary	*ALib=dynamic_cast<OutlineInspectLibrary *>(SLib->GetLibrary());
		int	row = 0;
		for (AlgorithmLibraryList* a = SelectedLibList.GetFirst(); a != NULL; a = a->GetNext(), row++) {
			DDim[row].a = a;
			SLib->SetLibID(a->GetLibID());

			CmdLoadOutlineLibraryPacket	Packet(GetLayersBase());
			Packet.Point = SLib;
			BBase->TransmitDirectly(&Packet);
			DDim[row].Priority = ALib->Priority;
		}
		for (;;) {
			AlgorithmLibraryList* a = SelectedLibList.GetFirst();
			if (a == NULL)
				break;
			SelectedLibList.RemoveList(a);
		}
		QSort(DDim, row, sizeof(DDim[0]), DDimFunc);
		for (int i = 0; i < row; i++) {
			SelectedLibList.AppendList(DDim[i].a);
		}
	}

	int	row = 0;
	ui->tableWidgetGeneratedLibList->setRowCount(SelectedLibList.GetNumber());
	for (AlgorithmLibraryList* a = SelectedLibList.GetFirst(); a != NULL; a = a->GetNext(), row++) {
		QTableWidgetItem* W;
		W = ui->tableWidgetGeneratedLibList->item(row, 0);
		if (W == NULL) {
			W = new QTableWidgetItem();
			ui->tableWidgetGeneratedLibList->setItem(row, 0, W);
			W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		}
		W->setText(QString::number(a->GetLibID()));
		W = ui->tableWidgetGeneratedLibList->item(row, 1);
		if (W == NULL) {
			W = new QTableWidgetItem();
			ui->tableWidgetGeneratedLibList->setItem(row, 1, W);
			W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		}
		W->setText(a->GetLibName());
	}
}



void PropertyOutlineForm::on_ButtonPickupTest_clicked()
{
	if (TempLib == NULL)
		return;
	IntList	LayerList;
	GUIFormBase* GProp = GetLayersBase()->FindByName(	/**/"Inspection"
		,/**/"OutlineImagePanel"
		,/**/"");
	if (GProp != NULL) {
		DisplayImage* DImg = dynamic_cast<DisplayImage*>(GProp);
		if (DImg != NULL) {
			DImg->GetActiveLayerList(LayerList);
		}
	}

	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(PropertyOutlineForm_LS, LID_3)/*"Pickup Test"*/);

	GetLibraryFromWindow(*TempLib);

	for (int page = 0; page < GetLayersBase()->GetPageNumb(); page++) {
		GUICmdPickupTestList	Cmd(GetLayersBase(), QString(sRoot), QString(sName), page);
		Cmd.LibPoint = TempLib;
		Cmd.LayerList = LayerList;
		Cmd.Send(NULL, page, 0);
	}

	GetLayersBase()->CloseProcessingForm();
}

void PropertyOutlineForm::on_ButtonGenerateLibs_clicked()
{
	if (TempLib == NULL)
		return;

	GUIFormBase* GProp = GetLayersBase()->FindByName(/**/"Inspection",/**/"OutlineImagePanel",/**/"");
	if (GProp != NULL) {
		DisplayImage* DImg = dynamic_cast<DisplayImage*>(GProp);
		if (DImg != NULL) {
			IntList	LayerList;
			DImg->GetActiveLayerList(LayerList);

			GetLayersBase()->ClearAllAckFlag();
			GetLayersBase()->ShowProcessingForm(LangSolver.GetString(PropertyOutlineForm_LS, LID_4)/*"Generating items"*/, GetLayersBase()->GetPageNumb() * 10);
			for (int page = 0; page < GetLayersBase()->GetPageNumb(); page++) {
				GUICmdGenerateOutlines	Cmd(GetLayersBase(), QString(sRoot), QString(sName), page);
				Cmd.LibList = SelectedLibList.GetIDList();
				Cmd.LayerList = LayerList;
				Cmd.Send(NULL, page, 0);
			}
			GetLayersBase()->WaitAllAcknowledged(60 * 20);
			GetLayersBase()->CloseProcessingForm();
		}
	}
}

void PropertyOutlineForm::on_ButtonPickupClearTest_clicked()
{
	for (int page = 0; page < GetLayersBase()->GetPageNumb(); page++) {
		GUICmdTestClear	Cmd(GetLayersBase(), QString(sRoot), QString(sName), page);
		Cmd.Send(NULL, page, 0);
	}
	BroadcastShowInEdit();
}

void PropertyOutlineForm::on_tableWidgetGeneratedLibList_clicked(const QModelIndex& Index)
{
	int	r = Index.row();
	AlgorithmLibraryList* a = SelectedLibList.GetItem(r);
	if (a != NULL) {
		TempLib->SetLibID(a->GetLibID());
		CmdLoadOutlineLibraryPacket	Packet(GetLayersBase());
		Packet.Point = TempLib;
		OutlineBase* BBase = GetOutlineBase();
		if (BBase != NULL) {
			BBase->TransmitDirectly(&Packet);
			if (Packet.Success == true) {
				SetLayersFromLib(TempLib->GetAdaptedPickLayers());
				ShowLibrary(*TempLib);
			}
			else {
				QMessageBox::critical(NULL, LangSolver.GetString(PropertyOutlineForm_LS, LID_16)/*"Library error"*/
					, LangSolver.GetString(PropertyOutlineForm_LS, LID_17)/*"Not loaded this library record"*/);
			}
		}
	}
}

void PropertyOutlineForm::on_toolButtonLibrary_clicked()
{
	if (ui->toolButtonLibrary->isChecked() == true) {
		ui->stackedWidget->setCurrentIndex(0);
		if (GetLayersBase()->GetParamComm()->Mastered == true && GetLayersBase()->GetParamComm()->ConnectedPCNumb != 0) {
			for (int page = 0; page < GetPageNumb(); page++) {
				GUICmdReqSetButtonMode	RCmd(GetLayersBase(), sRoot, sName, page);
				RCmd.Mode = GUICmdReqSetButtonMode::_LibraryTest;
				RCmd.InstForm = GetName();

				if (ui->toolButtonArea->isChecked() == true)
					RCmd.DType = GUICmdReqSetButtonMode::_Area;
				else if (ui->toolButtonEdge->isChecked() == true)
					RCmd.DType = GUICmdReqSetButtonMode::_Edge;
				else if (ui->toolButtonInside->isChecked() == true)
					RCmd.DType = GUICmdReqSetButtonMode::_Inside;

				RCmd.Send(NULL, page, 0);
			}
		}
	}
	BroadcastShowInEdit();
}

void PropertyOutlineForm::on_toolButtonCreateBlock_clicked()
{
	if (ui->toolButtonCreateBlock->isChecked() == true) {
		ui->stackedWidget->setCurrentIndex(1);
		if (GetLayersBase()->GetParamComm()->Mastered == true && GetLayersBase()->GetParamComm()->ConnectedPCNumb != 0) {
			for (int page = 0; page < GetPageNumb(); page++) {
				GUICmdReqSetButtonMode	RCmd(GetLayersBase(), sRoot, sName, page);
				RCmd.Mode = GUICmdReqSetButtonMode::_CreateBlock;
				RCmd.InstForm = GetName();

				if (ui->toolButtonArea->isChecked() == true)
					RCmd.DType = GUICmdReqSetButtonMode::_Area;
				else if (ui->toolButtonEdge->isChecked() == true)
					RCmd.DType = GUICmdReqSetButtonMode::_Edge;
				else if (ui->toolButtonInside->isChecked() == true)
					RCmd.DType = GUICmdReqSetButtonMode::_Inside;

				RCmd.Send(NULL, page, 0);
			}
		}
		ShowBlockInfoList();
	}
	BroadcastShowInEdit();
}

void PropertyOutlineForm::ShowBlockInfoList(void)
{
	OutlineInfos.RemoveAll();
	for (int page = 0; page < GetPageNumb(); page++) {
		GUICmdReqOutlineInfoList		CmdReq(GetLayersBase(), sRoot, sName, page);
		GUICmdSendOutlineInfoList		CmdSend(GetLayersBase(), sRoot, sName, page);
		CmdReq.Send(GetLayersBase()->GetGlobalPageFromLocal(page), 0, CmdSend);
		for (OutlineInfoList* a = CmdSend.OutlineInfos.GetFirst(); a != NULL; a = a->GetNext()) {
			OutlineInfoList* b;
			for (b = OutlineInfos.GetFirst(); b != NULL; b = b->GetNext()) {
				if (a->LibID == b->LibID) {
					IntClass* d = b->OutlineCount.GetItem(0);
					IntClass* s = a->OutlineCount.GetItem(0);
					d->SetValue(d->GetValue() + s->GetValue());
					break;
				}
			}
			if (b == NULL) {
				b = new OutlineInfoList();
				b->LibID = a->LibID;
				IntClass* s = a->OutlineCount.GetItem(0);
				b->OutlineCount.Add(s->GetValue());
				OutlineInfos.AppendList(b);
			}
		}
	}
	int	N = OutlineInfos.GetNumber();
	ui->tableWidgetBlockInfo->setRowCount(N);
	AlgorithmLibraryListContainer LibIDList;
	for (OutlineInfoList* a = OutlineInfos.GetFirst(); a != NULL; a = a->GetNext()) {
		AlgorithmLibraryList* k = new AlgorithmLibraryList();
		k->SetLibID(a->GetLibID());
		LibIDList.AppendList(k);
	}
	OutlineBase* BBase = GetOutlineBase();
	GetLayersBase()->GetDatabaseLoader()->G_GetLibraryNames(*GetLayersBase()->GetDataBase(), BBase->GetLibraryContainer(), LibIDList);
	int	row = 0;
	for (OutlineInfoList* a = OutlineInfos.GetFirst(); a != NULL; a = a->GetNext(), row++) {
		QString	LibName;
		for (AlgorithmLibraryList* m = LibIDList.GetFirst(); m != NULL; m = m->GetNext()) {
			if (m->GetLibID() == a->GetLibID()) {
				LibName = m->GetLibName();
				break;
			}
		}
		QTableWidgetItem* W;
		W = ui->tableWidgetBlockInfo->item(row, 0);
		if (W == NULL) {
			W = new QTableWidgetItem();
			ui->tableWidgetBlockInfo->setItem(row, 0, W);
			W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		}
		W->setText(QString::number(a->LibID));

		W = ui->tableWidgetBlockInfo->item(row, 1);
		if (W == NULL) {
			W = new QTableWidgetItem();
			ui->tableWidgetBlockInfo->setItem(row, 1, W);
			W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		}
		W->setText(LibName);

		W = ui->tableWidgetBlockInfo->item(row, 2);
		if (W == NULL) {
			W = new QTableWidgetItem();
			ui->tableWidgetBlockInfo->setItem(row, 2, W);
			W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		}
		int	TotalCount = 0;
		for (IntClass* h = a->OutlineCount.GetFirst(); h != NULL; h = h->GetNext()) {
			TotalCount += h->GetValue();
		}
		W->setText(QString::number(TotalCount));
	}
}

void PropertyOutlineForm::on_pushButtonEditLibFolder_clicked()
{
	OutlineBase* BBase = GetOutlineBase();
	int		RetSelectedLibFolderID;
	QString RetSelectedFolderName;
	if(ExeSelectLibFolderDialog(BBase->GetLibType(),GetLayersBase(),this
								,RetSelectedLibFolderID
								,RetSelectedFolderName)==true){
		ControlRememberer::SetValue(objectName()+/**/"\\LibFolderID",RetSelectedLibFolderID);
		SetLibFolder(RetSelectedLibFolderID,RetSelectedFolderName);
	}
}

void	PropertyOutlineForm::SetLibFolder(int _LibFolderID, const QString& LinFolderName)
{
	ui->labelLibFolderName->setText(LinFolderName);
	LibFolderID = _LibFolderID;
	ShowLibList();
}


void PropertyOutlineForm::on_pushButtonSetFrom_clicked()
{
	int	r = ui->tableWidgetLibList->currentRow();
	if (r < 0)
		return;
	AlgorithmLibraryList* a = LibList.GetItem(r);
	for (AlgorithmLibraryList* c = SelectedLibList.GetFirst(); c != NULL; c = c->GetNext()) {
		if (c->GetLibID() == a->GetLibID())
			return;
	}
	SelectedLibList.AppendList(new AlgorithmLibraryList(LibType, a->GetLibID(), a->GetLibName()));
	ShowSelectedLibList();
}

void PropertyOutlineForm::on_pushButtonGetBack_clicked()
{
	int	r = ui->tableWidgetGeneratedLibList->currentRow();
	if (r < 0)
		return;
	AlgorithmLibraryList* a = SelectedLibList.GetItem(r);
	if (a != NULL) {
		SelectedLibList.RemoveList(a);
		delete	a;
		ShowSelectedLibList();
	}
}

void PropertyOutlineForm::on_pushButtonEditLibrary_clicked()
{
	OutlineEditLibraryForm	D(GetLayersBase(), this);
	D.exec();
	//on_ButtonLibSave_clicked();
}

void PropertyOutlineForm::on_tableWidgetBlockInfo_clicked(const QModelIndex&)
{
	OutlineBase* BBase = GetOutlineBase();

	for (int page = 0; page < GetLayersBase()->GetPageNumb(); page++) {
		GUICmdReleaseSelectImagePanel	Cmd(GetLayersBase(), sRoot, sName, page);
		Cmd.AlgoRoot =/**/"Basic";
		Cmd.AlgoName =/**/"OutlineInspection";
		Cmd.Send(NULL, page, 0);
	}

	for (int page = 0; page < GetLayersBase()->GetPageNumb(); page++) {
		GUICmdSelectByLibs	Cmd(BBase, sRoot, sName, page);
		for (int row = 0; row < ui->tableWidgetBlockInfo->rowCount(); row++) {
			OutlineInfoList* a = OutlineInfos.GetItem(row);
			int	c = 2;
			QTableWidgetItem* item = ui->tableWidgetBlockInfo->item(row, c);
			if (item == NULL)
				continue;
			if (item->isSelected() == true) {
				SelectLibList* v = new SelectLibList();
				v->LibType = BBase->GetLibType();
				v->LibID = a->LibID;
				v->Layer = 0;
				Cmd.SelectedList.AppendList(v);
			}
		}
		Cmd.Send(NULL, page, 1);
	}
	BroadcastShowInEdit();
}

void PropertyOutlineForm::on_pushButtonInsideColor_clicked()
{
}

void PropertyOutlineForm::on_pushButtonOutsideColor_clicked()
{
}

void PropertyOutlineForm::on_pushButtonInsideBColor_clicked()
{
}
void PropertyOutlineForm::on_pushButtonOutsideBColor_clicked()
{
}

void PropertyOutlineForm::on_radioButtonInsideStable_toggled(bool)
{
	ui->stackedframeInside->setCurrentIndex(0);
}

void PropertyOutlineForm::on_radioButtonInsideTrans_toggled(bool)
{
	ui->stackedframeInside->setCurrentIndex(1);
}

void PropertyOutlineForm::on_radioButtonOutsideStable_toggled(bool)
{
	ui->stackedframeOutside->setCurrentIndex(0);
}

void PropertyOutlineForm::on_radioButtonOutsideTrans_toggled(bool)
{
	ui->stackedframeOutside->setCurrentIndex(1);
}


void PropertyOutlineForm::on_radioButtonInsideBStable_toggled(bool)
{
	ui->stackedframeBInside->setCurrentIndex(0);
}

void PropertyOutlineForm::on_radioButtonInsideBTrans_toggled(bool)
{
	ui->stackedframeBInside->setCurrentIndex(1);
}

void PropertyOutlineForm::on_radioButtonOutsideBStable_toggled(bool)
{
	ui->stackedframeBOutside->setCurrentIndex(0);
}

void PropertyOutlineForm::on_radioButtonOutsideBTrans_toggled(bool)
{
	ui->stackedframeBOutside->setCurrentIndex(1);
}

void PropertyOutlineForm::on_pushButtonSetFromAll_clicked()
{
	SelectedLibList.RemoveAll();
	for (AlgorithmLibraryList* a = LibList.GetFirst(); a != NULL; a = a->GetNext()) {
		SelectedLibList.AppendList(new AlgorithmLibraryList(LibType, a->GetLibID(), a->GetLibName()));
	}
	ShowSelectedLibList();
}

void PropertyOutlineForm::on_pushButtonGetBackAll_clicked()
{
	SelectedLibList.RemoveAll();
	ShowSelectedLibList();
}
void PropertyOutlineForm::on_toolButtonArea_clicked()
{
	if (GetLayersBase()->GetParamComm()->Mastered == true && GetLayersBase()->GetParamComm()->ConnectedPCNumb != 0) {
		for (int page = 0; page < GetPageNumb(); page++) {
			GUICmdReqSetButtonMode	RCmd(GetLayersBase(), sRoot, sName, page);
			if (ui->toolButtonLibrary->isChecked() == true)
				RCmd.Mode = GUICmdReqSetButtonMode::_LibraryTest;
			else if (ui->toolButtonCreateBlock->isChecked() == true)
				RCmd.Mode = GUICmdReqSetButtonMode::_CreateBlock;
			RCmd.InstForm = GetName();

			if (ui->toolButtonArea->isChecked() == true)
				RCmd.DType = GUICmdReqSetButtonMode::_Area;
			else if (ui->toolButtonEdge->isChecked() == true)
				RCmd.DType = GUICmdReqSetButtonMode::_Edge;
			else if (ui->toolButtonInside->isChecked() == true)
				RCmd.DType = GUICmdReqSetButtonMode::_Inside;

			RCmd.Send(NULL, page, 0);
		}
	}
	BroadcastShowInEdit();
}

void PropertyOutlineForm::on_toolButtonEdge_clicked()
{
	on_toolButtonArea_clicked();
}

void PropertyOutlineForm::on_toolButtonInside_clicked()
{
	on_toolButtonArea_clicked();
}
