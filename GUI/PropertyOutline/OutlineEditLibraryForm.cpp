#include "PropertyOutlineResource.h"
#include "OutlineEditLibraryForm.h"
#include "ui_OutlineEditLibraryForm.h"
#include "OutlinePickupForm.h"
#include "XDLLOnly.h"
#include <QMessageBox>
#include "XGeneralDialog.h"

OutlineEditLibraryForm::OutlineEditLibraryForm(LayersBase* base, QWidget *parent) :
    QDialog(parent), ServiceForLayers(base),
    ui(new Ui::OutlineEditLibraryForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	LibFolderID = -1;
	OutlineBase* BBase = GetOutlineBase();
	LibType = -1;
	if (BBase != NULL)
		LibType = BBase->GetLibType();
	pLibFolderForm = new GeneralLibFolderForm(LibType, GetLayersBase(), ui->frameLibFolder);
	connect(pLibFolderForm, SIGNAL(SelectLibFolder(int, QString)), this, SLOT(SlotSelectLibFolder(int, QString)));
	pLibFolderForm->SetCurrentLibFolder(GetLayersBase()->GetLibFolderID());

	ui->tableWidgetLibList->setColumnWidth(0, 30);
	ui->tableWidgetLibList->setColumnWidth(1, 80);
	TempLib = NULL;
	if (BBase != NULL) {
		CmdCreateTempOutlineLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		TempLib = Packet.Point;
	}
	for (int Layer = 0; Layer < GetLayerNumb(0); Layer++) {
		QToolButton* LayerButton = new QToolButton(ui->framePickLayer);
		LayerButton->move(Layer * 90, 0);
		LayerButton->resize(88, 20);
		LayerButton->setCheckable(true);
		LayerButton->setAutoExclusive(true);
		LayerButton->setText(GetParamGlobal()->GetLayerName(Layer));
		QPalette	PL = LayerButton->palette();
		PL.setColor(QPalette::Button, GetParamGlobal()->GetOneGraphLayerColor(Layer));
		LayerButton->setPalette(PL);
		LayerPickButtons.append(LayerButton);
	}
	for (int Layer = 0; Layer < GetLayerNumb(0); Layer++) {
		QToolButton* LayerButton = new QToolButton(ui->frameGenLayer);
		LayerButton->move(Layer * 90, 0);
		LayerButton->resize(88, 20);
		LayerButton->setCheckable(true);
		LayerButton->setAutoExclusive(true);
		LayerButton->setText(GetParamGlobal()->GetLayerName(Layer));
		QPalette	PL = LayerButton->palette();
		PL.setColor(QPalette::Button, GetParamGlobal()->GetOneGraphLayerColor(Layer));
		LayerButton->setPalette(PL);
		LayerGenButtons.append(LayerButton);
	}

	ui->stackedWidgetInside->setCurrentIndex(1);
	ui->stackedWidgetOutside->setCurrentIndex(1);
	ui->stackedWidgetBInside->setCurrentIndex(1);
	ui->stackedWidgetBOutside->setCurrentIndex(1);
	ui->stackedWidgetPickup->setCurrentIndex(1);

	ui->ButtonLibSave->setEnabled(false);
	ui->ButtonLibDelete->setEnabled(false);
	on_toolButtonPickup_clicked();
	on_toolButtonInspect_clicked();
	InstallOperationLog(this);
}

OutlineEditLibraryForm::~OutlineEditLibraryForm()
{
    delete ui;
}

OutlineBase* OutlineEditLibraryForm::GetOutlineBase(void)
{
	return (OutlineBase*)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"OutlineInspection");
}

void	OutlineEditLibraryForm::SlotSelectLibFolder(int libFolderID, QString FolderName)
{
	LibFolderID = libFolderID;
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
void OutlineEditLibraryForm::on_toolButtonPickup_clicked()
{
	if (ui->toolButtonPickup->isChecked() == true)
		ui->stackedWidget->setCurrentIndex(0);
}

void OutlineEditLibraryForm::on_toolButtonInspect_clicked()
{
	if (ui->toolButtonInspect->isChecked() == true)
		ui->stackedWidget->setCurrentIndex(1);
}

void	OutlineEditLibraryForm::ShowLibrary(AlgorithmLibraryLevelContainer& data)
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

	ui->EditInsideMergin	->setValue(ALib->InsideNMergin);
	ui->EditInsideOKDot		->setValue(ALib->InsideNOKDot);

	ui->EditOutsideMergin	->setValue(ALib->OutsideNMergin);
	ui->EditOutsideOKDot	->setValue(ALib->OutsideNOKDot);

	ui->EditInsideBMergin	->setValue(ALib->InsideBMergin);
	ui->EditInsideBOKDot	->setValue(ALib->InsideBOKDot);

	ui->EditOutsideBMergin	->setValue(ALib->OutsideBMergin);
	ui->EditOutsideBOKDot	->setValue(ALib->OutsideBOKDot);

	ui->checkBoxEffectiveNInside	->setChecked(ALib->EffectiveNInside);
	ui->checkBoxEffectiveNOutside	->setChecked(ALib->EffectiveNOutside);
	ui->checkBoxEffectiveBInside	->setChecked(ALib->EffectiveBInside);
	ui->checkBoxEffectiveBOutside	->setChecked(ALib->EffectiveBOutside);

	ui->EditSelfSearch			->setValue	(ALib->SelfSearch);
	ui->checkBoxAdjustMode		->setChecked(ALib->AdjustMode);
	ui->checkBoxDiffMode		->setChecked(ALib->DiffMode);
	ui->EditAdjustLimitLInside	->setValue	(ALib->AdjustLimitLInside);
	ui->EditAdjustLimitHInside	->setValue	(ALib->AdjustLimitHInside);
	ui->EditAdjustLimitLOutside	->setValue	(ALib->AdjustLimitLOutside);
	ui->EditAdjustLimitHOutside	->setValue	(ALib->AdjustLimitHOutside);

	ui->checkBoxAbsMode->setChecked(ALib->AbsMode);

	int	ColL, ColH;
	ALib->PickupColor.GetMonoColorRange(ColL, ColH);
	ui->EditPickupL->setValue(ColL);
	ui->EditPickupH->setValue(ColH);

	ALib->InsideNOKColor.GetRelMonoRange(ColL, ColH);
	ui->EditInsideColorL->setValue(ColL);
	ui->EditInsideColorH->setValue(ColH);

	ALib->OutsideNOKColor.GetRelMonoRange(ColL, ColH);
	ui->EditOutsideColorL->setValue(ColL);
	ui->EditOutsideColorH->setValue(ColH);

	ALib->InsideNTrOKColor.GetRelMonoRange(ColL, ColH);
	ui->EditInsideTrColorL->setValue(ColL);
	ui->EditInsideTrColorH->setValue(ColH);

	ALib->OutsideNTrOKColor.GetRelMonoRange(ColL, ColH);
	ui->EditOutsideTrColorL->setValue(ColL);
	ui->EditOutsideTrColorH->setValue(ColH);

	ALib->InsideBOKColor.GetRelMonoRange(ColL, ColH);
	ui->EditInsideBColorL->setValue(ColL);
	ui->EditInsideBColorH->setValue(ColH);

	ALib->OutsideBOKColor.GetRelMonoRange(ColL, ColH);
	ui->EditOutsideBColorL->setValue(ColL);
	ui->EditOutsideBColorH->setValue(ColH);

	ALib->InsideBTrOKColor.GetRelMonoRange(ColL, ColH);
	ui->EditInsideTrBColorL->setValue(ColL);
	ui->EditInsideTrBColorH->setValue(ColH);

	ALib->OutsideBTrOKColor.GetRelMonoRange(ColL, ColH);
	ui->EditOutsideTrBColorL->setValue(ColL);
	ui->EditOutsideTrBColorH->setValue(ColH);

	int	Page=0;

	for (IntClass* a = data.GetAdaptedPickLayers().GetFirst(); a != NULL; a = a->GetNext()) {
		int	Layer = a->GetValue();
		if (0 <= Layer && Layer < GetLayerNumb(Page)) {
			LayerPickButtons[Layer]->setChecked(true);
		}
	}
	for (int Layer = 0; Layer < GetLayerNumb(Page); Layer++) {
		bool	Found = false;
		for (IntClass* a = data.GetAdaptedPickLayers().GetFirst(); a != NULL; a = a->GetNext()) {
			if (Layer == a->GetValue()) {
				Found = true;
				break;
			}
		}
		if (Found == false) {
			LayerPickButtons[Layer]->setChecked(false);
		}
	}
	for (IntClass* a = data.GetAdaptedGenLayers().GetFirst(); a != NULL; a = a->GetNext()) {
		int	Layer = a->GetValue();
		if (0 <= Layer && Layer < GetLayerNumb(Page)) {
			LayerGenButtons[Layer]->setChecked(true);
		}
	}
	for (int Layer = 0; Layer < GetLayerNumb(Page); Layer++) {
		bool	Found = false;
		for (IntClass* a = data.GetAdaptedGenLayers().GetFirst(); a != NULL; a = a->GetNext()) {
			if (Layer == a->GetValue()) {
				Found = true;
				break;
			}
		}
		if (Found == false) {
			LayerGenButtons[Layer]->setChecked(false);
		}
	}
}

void	OutlineEditLibraryForm::GetLibraryFromWindow(AlgorithmLibraryLevelContainer& data)
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

	ALib->InsideTrWidth	= ui->EditInsideTrWidth->value();
	ALib->OutsideTrWidth= ui->EditOutsideTrWidth->value();

	ALib->InsideNMergin = ui->EditInsideMergin->value();
	ALib->InsideNOKDot	= ui->EditInsideOKDot->value();

	ALib->OutsideNMergin= ui->EditOutsideMergin->value();
	ALib->OutsideNOKDot = ui->EditOutsideOKDot->value();

	ALib->InsideBMergin = ui->EditInsideBMergin->value();
	ALib->InsideBOKDot	= ui->EditInsideBOKDot->value();

	ALib->OutsideBMergin	= ui->EditOutsideBMergin->value();
	ALib->OutsideBOKDot		= ui->EditOutsideBOKDot->value();
	ALib->EffectiveNInside	= ui->checkBoxEffectiveNInside->isChecked();
	ALib->EffectiveNOutside = ui->checkBoxEffectiveNOutside->isChecked();
	ALib->EffectiveBInside	= ui->checkBoxEffectiveBInside->isChecked();
	ALib->EffectiveBOutside = ui->checkBoxEffectiveBOutside->isChecked();

	ALib->SelfSearch			= ui->EditSelfSearch->value();
	ALib->AdjustMode			= ui->checkBoxAdjustMode->isChecked();
	ALib->DiffMode				= ui->checkBoxDiffMode->isChecked();
	ALib->AdjustLimitLInside	= ui->EditAdjustLimitLInside->value();
	ALib->AdjustLimitHInside	= ui->EditAdjustLimitHInside->value();
	ALib->AdjustLimitLOutside	= ui->EditAdjustLimitLOutside->value();
	ALib->AdjustLimitHOutside	= ui->EditAdjustLimitHOutside->value();
	ALib->AbsMode = ui->checkBoxAbsMode->isChecked();

	int	ColL, ColH;
	ColL = ui->EditPickupL->value();
	ColH = ui->EditPickupH->value();
	ALib->PickupColor.SetMonoColorRange(ColL, ColH);

	ColL = ui->EditInsideColorL->value();
	ColH = ui->EditInsideColorH->value();
	ALib->InsideNOKColor.SetRelMonoRange(ColL, ColH);

	ColL = ui->EditOutsideColorL->value();
	ColH = ui->EditOutsideColorH->value();
	ALib->OutsideNOKColor.SetRelMonoRange(ColL, ColH);

	ColL = ui->EditInsideTrColorL->value();
	ColH = ui->EditInsideTrColorH->value();
	ALib->InsideNTrOKColor.SetRelMonoRange(ColL, ColH);

	ColL = ui->EditOutsideTrColorL->value();
	ColH = ui->EditOutsideTrColorH->value();
	ALib->OutsideNTrOKColor.SetRelMonoRange(ColL, ColH);

	ColL = ui->EditInsideBColorL->value();
	ColH = ui->EditInsideBColorH->value();
	ALib->InsideBOKColor.SetRelMonoRange(ColL, ColH);

	ColL = ui->EditOutsideBColorL->value();
	ColH = ui->EditOutsideBColorH->value();
	ALib->OutsideBOKColor.SetRelMonoRange(ColL, ColH);

	ColL = ui->EditInsideTrBColorL->value();
	ColH = ui->EditInsideTrBColorH->value();
	ALib->InsideBTrOKColor.SetRelMonoRange(ColL, ColH);

	ColL = ui->EditOutsideTrBColorL->value();
	ColH = ui->EditOutsideTrBColorH->value();
	ALib->OutsideBTrOKColor.SetRelMonoRange(ColL, ColH);

	IntList	LayersPickList;
	for (int Layer = 0; Layer < LayerPickButtons.count(); Layer++) {
		if (LayerPickButtons[Layer]->isChecked() == true) {
			LayersPickList.Add(Layer);
		}
	}
	data.SetAdaptedPickLayers(LayersPickList);

	IntList	LayersGenList;
	for (int Layer = 0; Layer < LayerGenButtons.count(); Layer++) {
		if (LayerGenButtons[Layer]->isChecked() == true) {
			LayersGenList.Add(Layer);
		}
	}
	data.SetAdaptedGenLayers(LayersGenList);
}

void OutlineEditLibraryForm::on_pushButtonGColor_clicked()
{

}

void OutlineEditLibraryForm::on_ButtonLibNew_clicked()
{
	if (TempLib == NULL)
		return;
	TempLib->Reset();
	ShowLibrary(*TempLib);
	ui->ButtonLibSave->setEnabled(false);
	ui->ButtonLibDelete->setEnabled(false);
}

void OutlineEditLibraryForm::on_ButtonLibDelete_clicked()
{
	if (TempLib == NULL)
		return;
	if (TempLib->GetLibID() < 0)
		return;
	QString  msg = LangSolver.GetString(OutlineEditLibraryForm_LS, LID_18)/*"Delete OK?"*/;
	int	ret = QMessageBox::question(NULL, LangSolver.GetString(OutlineEditLibraryForm_LS, LID_19)/*"Choose"*/
		, msg
		, QMessageBox::Yes, QMessageBox::No, QMessageBox::NoButton);
	if (ret == QMessageBox::Yes) {
		CmdDeleteOutlineLibraryPacket	Packet(GetLayersBase());
		Packet.Point = TempLib;
		OutlineBase* BBase = GetOutlineBase();
		if (BBase != NULL) {
			BBase->TransmitDirectly(&Packet);
			on_ButtonLibNew_clicked();
			SlotSelectLibFolder(LibFolderID,/**/"");
		}
	}
}

void OutlineEditLibraryForm::on_ButtonLibSaveNew_clicked()
{
	if (TempLib == NULL)
		return;
	GetLibraryFromWindow(*TempLib);

	if (TempLib->GetLibName() ==/**/"") {
		QMessageBox::StandardButton ret = QMessageBox::warning(NULL, LangSolver.GetString(OutlineEditLibraryForm_LS, LID_20)/*"Warning"*/
			, LangSolver.GetString(OutlineEditLibraryForm_LS, LID_21)/*"No Library Name"*/
			, QMessageBox::Ok | QMessageBox::Cancel);
		if (ret != QMessageBox::Ok)
			return;
	}
	TempLib->SetLibFolderID(LibFolderID);

	CmdInsertOutlineLibraryPacket	Packet(GetLayersBase());
	Packet.Point = TempLib;
	OutlineBase* BBase = GetOutlineBase();
	if (BBase != NULL) {
		BBase->TransmitDirectly(&Packet);
		ShowLibrary(*TempLib);
		ui->ButtonLibSave->setEnabled(true);
		ui->ButtonLibDelete->setEnabled(true);
	}
	SlotSelectLibFolder(LibFolderID,/**/"");
}

void OutlineEditLibraryForm::on_ButtonLibSave_clicked()
{
	if (TempLib == NULL)
		return;
	GetLibraryFromWindow(*TempLib);
	if (TempLib->GetLibName() ==/**/"") {
		QMessageBox::StandardButton ret = QMessageBox::warning(NULL, LangSolver.GetString(OutlineEditLibraryForm_LS, LID_22)/*"Warning"*/
			, LangSolver.GetString(OutlineEditLibraryForm_LS, LID_23)/*"No Library Name"*/
			, QMessageBox::Ok | QMessageBox::Cancel);
		if (ret != QMessageBox::Ok)
			return;
	}
	if (TempLib->GetLibID() < 0) {
		TempLib->SetLibFolderID(LibFolderID);
		CmdInsertOutlineLibraryPacket	Packet(GetLayersBase());
		Packet.Point = TempLib;
		OutlineBase* BBase = GetOutlineBase();
		if (BBase != NULL) {
			BBase->TransmitDirectly(&Packet);
			ShowLibrary(*TempLib);
			ui->ButtonLibSave->setEnabled(true);
			ui->ButtonLibDelete->setEnabled(true);
		}
	}
	else {
		CmdUpdateOutlineLibraryPacket	Packet(GetLayersBase());
		Packet.Point = TempLib;
		OutlineBase* BBase = GetOutlineBase();
		if (BBase != NULL) {
			BBase->TransmitDirectly(&Packet);
		}
	}
	SlotSelectLibFolder(LibFolderID,/**/"");
}

void OutlineEditLibraryForm::on_pushButtonClose_clicked()
{
	close();
}

void OutlineEditLibraryForm::on_pushButtonInsideColor_clicked()
{
	/*
	OutlinePickupForm	D(GetLayersBase()
						,NULL
						,&ColorInside.Cube
						,this);
	//D.ColorPanel.Cube	=ColorNarrow.Cube;
	D.ColorPanel.InitializedDoneCube();
	if(D.exec()==(int)true){
		if(ui->radioButtonInsideStable->isChecked()==true){
			ColorInside.Cube=D.ColorPanel.Cube;
			ColorInside.InitializedDoneCube();
			ColorInside.Repaint();
			TempLib->InsideNOKColor	=D.ColorPanel.Cube;
		}
		else{
			TrColorInside.Cube=D.ColorPanel.Cube;
			TrColorInside.InitializedDoneCube();
			TrColorInside.Repaint();
			TempLib->InsideNTrOKColor	=D.ColorPanel.Cube;
		}
	}
	*/
}

void OutlineEditLibraryForm::on_pushButtonOutsideColor_clicked()
{
	/*
	OutlinePickupForm	D(GetLayersBase()
						,NULL
						,&ColorOutside.Cube
						,this);
	//D.ColorPanel.Cube	=ColorNarrow.Cube;
	D.ColorPanel.InitializedDoneCube();
	if(D.exec()==(int)true){
		if(ui->radioButtonOutsideStable->isChecked()==true){
			ColorOutside.Cube=D.ColorPanel.Cube;
			ColorOutside.InitializedDoneCube();
			ColorOutside.Repaint();
			TempLib->OutsideNOKColor	=D.ColorPanel.Cube;
		}
		else{
			TrColorOutside.Cube=D.ColorPanel.Cube;
			TrColorOutside.InitializedDoneCube();
			TrColorOutside.Repaint();
			TempLib->OutsideNTrOKColor	=D.ColorPanel.Cube;
		}
	}
	*/
}

void OutlineEditLibraryForm::on_tableWidgetLibList_clicked(const QModelIndex& Index)
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
				ShowLibrary(*TempLib);
				ui->ButtonLibSave->setEnabled(true);
				ui->ButtonLibDelete->setEnabled(true);
			}
			else {
				QMessageBox::critical(NULL, LangSolver.GetString(OutlineEditLibraryForm_LS, LID_24)/*"Library error"*/
					, LangSolver.GetString(OutlineEditLibraryForm_LS, LID_25)/*"Not loaded this library record"*/);
			}
		}
	}
}

void OutlineEditLibraryForm::on_radioButtonInsideStable_toggled(bool)
{
	ui->stackedframeInside->setCurrentIndex(0);
}

void OutlineEditLibraryForm::on_radioButtonInsideTrans_toggled(bool)
{
	ui->stackedframeInside->setCurrentIndex(1);
}

void OutlineEditLibraryForm::on_radioButtonOutsideStable_toggled(bool)
{
	ui->stackedframeOutside->setCurrentIndex(0);
}

void OutlineEditLibraryForm::on_radioButtonOutsideTrans_toggled(bool)
{
	ui->stackedframeOutside->setCurrentIndex(1);
}

void OutlineEditLibraryForm::on_pushButtonInsideBColor_clicked()
{
	/*
	OutlinePickupForm	D(GetLayersBase()
						,NULL
						,&ColorBInside.Cube
						,this);
	//D.ColorPanel.Cube	=ColorNarrow.Cube;
	D.ColorPanel.InitializedDoneCube();
	if(D.exec()==(int)true){
		if(ui->radioButtonInsideStable->isChecked()==true){
			ColorBInside.Cube		=D.ColorPanel.Cube;
			ColorBInside.InitializedDoneCube();
			ColorBInside.Repaint();
			TempLib->InsideBOKColor	=D.ColorPanel.Cube;
		}
		else{
			TrColorBInside.Cube			=D.ColorPanel.Cube;
			TrColorBInside.InitializedDoneCube();
			TrColorBInside.Repaint();
			TempLib->InsideBTrOKColor	=D.ColorPanel.Cube;
		}
	}
	*/
}

void OutlineEditLibraryForm::on_pushButtonOutsideBColor_clicked()
{
	/*
	OutlinePickupForm	D(GetLayersBase()
						,NULL
						,&ColorBOutside.Cube
						,this);
	//D.ColorPanel.Cube	=ColorNarrow.Cube;
	D.ColorPanel.InitializedDoneCube();
	if(D.exec()==(int)true){
		if(ui->radioButtonOutsideStable->isChecked()==true){
			ColorBOutside.Cube			=D.ColorPanel.Cube;
			ColorBOutside.InitializedDoneCube();
			ColorBOutside.Repaint();
			TempLib->OutsideBOKColor	=D.ColorPanel.Cube;
		}
		else{
			TrColorBOutside.Cube		=D.ColorPanel.Cube;
			TrColorBOutside.InitializedDoneCube();
			TrColorBOutside.Repaint();
			TempLib->OutsideBTrOKColor	=D.ColorPanel.Cube;
		}
	}
	*/
}

void OutlineEditLibraryForm::on_radioButtonInsideBStable_toggled(bool)
{
	ui->stackedframeBInside->setCurrentIndex(0);
}

void OutlineEditLibraryForm::on_radioButtonInsideBTrans_toggled(bool)
{
	ui->stackedframeBInside->setCurrentIndex(1);
}

void OutlineEditLibraryForm::on_radioButtonOutsideBStable_toggled(bool)
{
	ui->stackedframeBOutside->setCurrentIndex(0);
}

void OutlineEditLibraryForm::on_radioButtonOutsideBTrans_toggled(bool)
{
	ui->stackedframeBOutside->setCurrentIndex(1);
}
