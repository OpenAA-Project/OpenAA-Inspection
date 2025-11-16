#include "PropertyAutoPCBHoleAlignerFormResource.h"
#include "EditAutoPCBHoleAlignerLibrary.h"
#include "ui_EditAutoPCBHoleAlignerLibrary.h"
#include "XAutoPCBHoleAligner.h"
#include "XDataInLayerCommander.h"
#include "XDisplayImage.h"
#include "XGeneralDialog.h"
#include "XGUIFormBase.h"
#include <QMessageBox>

extern	const	char	*sRoot;
extern	const	char	*sName;

EditAutoPCBHoleAlignerLibrary::EditAutoPCBHoleAlignerLibrary(LayersBase* Base, QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(Base)
    ,ui(new Ui::EditAutoPCBHoleAlignerLibrary)
	,ColorSamples(Base)
{
    ui->setupUi(this);

	LibFolderID = -1;
	AutoPCBHoleAlignerBase* BBase = GetAutoPCBHoleAlignerBase();
	LibType = -1;
	if (BBase != NULL)
		LibType = BBase->GetLibType();
	pLibFolderForm = new GeneralLibFolderForm(LibType, GetLayersBase(), ui->frameLibFolder);
	connect(pLibFolderForm, SIGNAL(SelectLibFolder(int, QString)), this, SLOT(SlotSelectLibFolder(int, QString)));
	pLibFolderForm->SetCurrentLibFolder(GetLayersBase()->GetLibFolderID());

	TempLib = NULL;
	if (BBase != NULL) {
		CmdCreateTempAutoPCBHoleAlignerLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		TempLib = Packet.Point;
	}
	ui->ButtonLibSave->setEnabled(false);
	ui->ButtonLibDelete->setEnabled(false);

	ColorThre.setParent(ui->frameThreshold);
	ColorThre.Fit(ui->frameThreshold);

	connect(&ColorThre, SIGNAL(AddEliminated(void)), this, SLOT(SlotAddEliminated(void)));
	connect(&ColorThre, SIGNAL(DelEliminated(void)), this, SLOT(SlotDelEliminated(void)));

	ColorSamples.setParent(ui->frameColorSample);
	ColorSamples.move(0, 0);
	RGBPanel.setParent(ui->frameShowColorSmples);
	RGBPanel.Fit(ui->frameShowColorSmples);
	GUIFormBase* GProp = GetLayersBase()->FindByName(/**/"Inspection",/**/"AutoPCBHoleAlignerImagePanel",/**/"");
	if (GProp != NULL) {
		DisplayImage* Display = dynamic_cast<DisplayImage*>(GProp);
		if (Display != NULL) {
			PickupColor = Display->GetPickedColor();
			PickupColorFrame.setParent(ui->framePickupColor);
			PickupColorFrame.move(0, 0);
			PickupColorFrame.resize(ui->framePickupColor->width(), ui->framePickupColor->height());
			PickupColorFrame.SetColor(PickupColor);
			RGBPanel.Cube = Display->GetRGBStock();
			RGBPanel.InitializedDoneCube();
		}
	}

	connect(&ColorSamples, SIGNAL(SignalBeforeSave()), this, SLOT(SlotColorSampleBeforeSave()));
	connect(&ColorSamples, SIGNAL(SignalSelectCData()), this, SLOT(SlotColorSampleSelectOne()));

	InstallOperationLog(this);
}

EditAutoPCBHoleAlignerLibrary::~EditAutoPCBHoleAlignerLibrary()
{
    delete ui;
}

AutoPCBHoleAlignerBase* EditAutoPCBHoleAlignerLibrary::GetAutoPCBHoleAlignerBase(void)
{
	return (AutoPCBHoleAlignerBase*)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AutoPCBHoleAligner");
}

void	EditAutoPCBHoleAlignerLibrary::SlotSelectLibFolder(int libFolderID, QString FolderName)
{
	LibFolderID = libFolderID;
	ui->tableWidgetLibList->setRowCount(0);
	AutoPCBHoleAlignerBase* BBase = GetAutoPCBHoleAlignerBase();
	if (BBase != NULL) {
		CmdGetAutoPCBHoleAlignerLibraryListPacket	Packet(GetLayersBase());
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

void	EditAutoPCBHoleAlignerLibrary::Initial(AlgorithmBase* InstBase)
{
	AlgorithmLibraryContainerForEnum		LibList(InstBase->GetLayersBase());
	LibIDList.RemoveAll();
	LibList.EnumAllLibraries(GetLayersBase()->GetDatabase(), InstBase->GetLibType(), LibIDList);
}

void	EditAutoPCBHoleAlignerLibrary::SlotAddEliminated(void)
{
	ShowThresholdList();
	AutoPCBHoleAlignerLibrary	*ALib=dynamic_cast<AutoPCBHoleAlignerLibrary *>(TempLib->GetLibrary());
	ALib->PickupHoleColor = ColorThre.Cube;
}
void	EditAutoPCBHoleAlignerLibrary::SlotDelEliminated(void)
{
	ShowThresholdList();
	AutoPCBHoleAlignerLibrary	*ALib=dynamic_cast<AutoPCBHoleAlignerLibrary *>(TempLib->GetLibrary());
	ALib->PickupHoleColor = ColorThre.Cube;
}
void EditAutoPCBHoleAlignerLibrary::ShowThresholdList(void)
{
	ui->listWidgetBaseColor->clear();
	ui->listWidgetEliminatedColor->clear();
	int	N = 1;
	for (ColorSpace* c = ColorThre.Cube.GetFirstBase(); c != NULL; c = c->GetNext(), N++) {
		ui->listWidgetBaseColor->addItem(QString::number(N));
	}
	N = 1;
	for (ColorSpace* c = ColorThre.Cube.GetFirstEliminated(); c != NULL; c = c->GetNext(), N++) {
		ui->listWidgetEliminatedColor->addItem(QString::number(N));
	}
}

void	EditAutoPCBHoleAlignerLibrary::SlotColorSampleBeforeSave()
{
	ColorSamples.CData.Set(ColorThre.Cube);
}
void	EditAutoPCBHoleAlignerLibrary::SlotColorSampleSelectOne()
{
	ColorThre.Cube = *ColorSamples.CData.GetColorLogic();
	ColorThre.InitializedDoneCube();
	ColorThre.Repaint();
	AutoPCBHoleAlignerLibrary	*ALib=dynamic_cast<AutoPCBHoleAlignerLibrary *>(TempLib->GetLibrary());
	ALib->PickupHoleColor = ColorThre.Cube;
}

void EditAutoPCBHoleAlignerLibrary::on_ButtonLibNew_clicked()
{
	if (TempLib == NULL)
		return;
	TempLib->Reset();
	CmdClearAutoPCBHoleAlignerLibraryPacket	Packet(GetLayersBase());
	Packet.Point = TempLib;
	AutoPCBHoleAlignerBase* BBase = GetAutoPCBHoleAlignerBase();
	if (BBase != NULL) {
		BBase->TransmitDirectly(&Packet);
	}
	ShowLibrary(*TempLib);
	ui->ButtonLibSave->setEnabled(false);
	ui->ButtonLibDelete->setEnabled(false);
}

void EditAutoPCBHoleAlignerLibrary::on_ButtonLibDelete_clicked()
{
	if (TempLib == NULL)
		return;
	if (TempLib->GetLibID() < 0)
		return;
	QString  msg = LangSolver.GetString(EditAutoPCBHoleAlignerLibrary_LS, LID_0)/*"Delete OK?"*/;
	int	ret = QMessageBox::question(NULL, LangSolver.GetString(EditAutoPCBHoleAlignerLibrary_LS, LID_1)/*"Choose"*/
		, msg
		, QMessageBox::Yes, QMessageBox::No, QMessageBox::NoButton);
	if (ret == QMessageBox::Yes) {
		CmdDeleteAutoPCBHoleAlignerLibraryPacket 	Packet(GetLayersBase());
		Packet.Point = TempLib;
		AutoPCBHoleAlignerBase* BBase = GetAutoPCBHoleAlignerBase();
		if (BBase != NULL) {
			BBase->TransmitDirectly(&Packet);
			on_ButtonLibNew_clicked();
			SlotSelectLibFolder(LibFolderID,/**/"");
		}
	}
}

void EditAutoPCBHoleAlignerLibrary::on_ButtonLibSaveNew_clicked()
{
	if (TempLib == NULL)
		return;
	GetLibraryFromWindow(*TempLib);

	if (TempLib->GetLibName() ==/**/"") {
		QMessageBox::StandardButton ret = QMessageBox::warning(NULL
			, LangSolver.GetString(EditAutoPCBHoleAlignerLibrary_LS, LID_2)/*"Warning"*/
			, LangSolver.GetString(EditAutoPCBHoleAlignerLibrary_LS, LID_3)/*"No Library Name"*/
			, QMessageBox::Ok | QMessageBox::Cancel);
		if (ret != QMessageBox::Ok)
			return;
	}
	TempLib->SetLibFolderID(LibFolderID);
	CmdInsertAutoPCBHoleAlignerLibraryPacket	Packet(GetLayersBase());
	Packet.Point = TempLib;
	AutoPCBHoleAlignerBase* BBase = GetAutoPCBHoleAlignerBase();
	if (BBase != NULL) {
		BBase->TransmitDirectly(&Packet);
		ShowLibrary(*TempLib);
		ui->ButtonLibSave->setEnabled(true);
		ui->ButtonLibDelete->setEnabled(true);
	}
	SlotSelectLibFolder(LibFolderID,/**/"");
}

void EditAutoPCBHoleAlignerLibrary::on_ButtonLibSave_clicked()
{
	if (TempLib == NULL)
		return;
	GetLibraryFromWindow(*TempLib);
	if (TempLib->GetLibName() ==/**/"") {
		QMessageBox::StandardButton ret = QMessageBox::warning(NULL
			, LangSolver.GetString(EditAutoPCBHoleAlignerLibrary_LS, LID_4)/*"Warning"*/
			, LangSolver.GetString(EditAutoPCBHoleAlignerLibrary_LS, LID_5)/*"No Library Name"*/
			, QMessageBox::Ok | QMessageBox::Cancel);
		if (ret != QMessageBox::Ok)
			return;
	}
	if (TempLib->GetLibID() < 0) {
		TempLib->SetLibFolderID(LibFolderID);

		CmdInsertAutoPCBHoleAlignerLibraryPacket	Packet(GetLayersBase());
		Packet.Point = TempLib;
		AutoPCBHoleAlignerBase* BBase = GetAutoPCBHoleAlignerBase();
		if (BBase != NULL) {
			BBase->TransmitDirectly(&Packet);
			ShowLibrary(*TempLib);
			ui->ButtonLibSave->setEnabled(true);
			ui->ButtonLibDelete->setEnabled(true);
		}
	}
	else {
		CmdUpdateAutoPCBHoleAlignerLibraryPacket	Packet(GetLayersBase());
		Packet.Point = TempLib;
		AutoPCBHoleAlignerBase* BBase = GetAutoPCBHoleAlignerBase();
		if (BBase != NULL) {
			BBase->TransmitDirectly(&Packet);
		}
	}
	SlotSelectLibFolder(LibFolderID,/**/"");
}

void EditAutoPCBHoleAlignerLibrary::on_pushButton_clicked()
{
	close();
}

void EditAutoPCBHoleAlignerLibrary::on_pushButtonAddPickupColor_clicked()
{
	ColorThre.Cube.Add(PickupColor.rgb(), ui->spinBoxMerginAddPickupColor->value());
	ColorThre.Repaint();
	AutoPCBHoleAlignerLibrary	*ALib=dynamic_cast<AutoPCBHoleAlignerLibrary *>(TempLib->GetLibrary());
	ALib->PickupHoleColor = ColorThre.Cube;
	ShowThresholdList();
}

void EditAutoPCBHoleAlignerLibrary::on_pushButtonSubPickupColor_clicked()
{
	ColorThre.Cube.Eliminame(PickupColor.rgb(), ui->spinBoxMerginSubPickupColor->value());
	ColorThre.Repaint();
	AutoPCBHoleAlignerLibrary	*ALib=dynamic_cast<AutoPCBHoleAlignerLibrary *>(TempLib->GetLibrary());
	ALib->PickupHoleColor = ColorThre.Cube;
	ShowThresholdList();
}

void	EditAutoPCBHoleAlignerLibrary::ShowLibrary(AlgorithmLibraryLevelContainer& data)
{
	if (data.GetLibID() < 0)
		ui->EditLibID->setText(/**/"");
	else
		ui->EditLibID->setText(QString::number(data.GetLibID()));
	ui->EditLibName->setText(data.GetLibName());

	AutoPCBHoleAlignerLibrary	*ALib=dynamic_cast<AutoPCBHoleAlignerLibrary *>(data.GetLibrary());
	ui->EditExpandForPickup		->setValue	(ALib->ExpandForPickup);
	ui->checkBoxStartupExecute	->setChecked(ALib->StartupExecute);
	ui->EditMinDiameter			->setValue	(ALib->MinDiameter);
	ui->EditMaxDiameter			->setValue	(ALib->MaxDiameter);
	ui->EditFringeDot			->setValue	(ALib->FringeDot);
	ui->checkBoxCheckOutside	->setChecked(ALib->CheckOutside);
	ui->EditMaxSearch			->setValue	(ALib->MaxSearch);
	ui->EditThresholdDiff		->setValue	(ALib->ThresholdDiff);
}

void	EditAutoPCBHoleAlignerLibrary::GetLibraryFromWindow(AlgorithmLibraryLevelContainer& data)
{
	data.SetLibName(ui->EditLibName->text());

	AutoPCBHoleAlignerLibrary	*ALib=dynamic_cast<AutoPCBHoleAlignerLibrary *>(data.GetLibrary());
	ALib->ExpandForPickup	= ui->EditExpandForPickup	->value();
	ALib->StartupExecute	= ui->checkBoxStartupExecute->isChecked();
	ALib->MinDiameter		= ui->EditMinDiameter		->value();
	ALib->MaxDiameter		= ui->EditMaxDiameter		->value();
	ALib->FringeDot			= ui->EditFringeDot			->value();
	ALib->CheckOutside		= ui->checkBoxCheckOutside	->isChecked();
	ALib->MaxSearch			= ui->EditMaxSearch			->value();
	ALib->ThresholdDiff		= ui->EditThresholdDiff		->value();
}

void EditAutoPCBHoleAlignerLibrary::on_pushButtonAddColor_clicked()
{
	ColorThre.Cube.Add(*ColorSamples.CData.GetColorLogic());
	ColorThre.Repaint();
	AutoPCBHoleAlignerLibrary	*ALib=dynamic_cast<AutoPCBHoleAlignerLibrary *>(TempLib->GetLibrary());
	ALib->PickupHoleColor = ColorThre.Cube;
	ShowThresholdList();
}

void EditAutoPCBHoleAlignerLibrary::on_pushButtonEliminateColor_clicked()
{
	ColorThre.Cube.Eliminate(*ColorSamples.CData.GetColorLogic());
	ColorThre.Repaint();
	AutoPCBHoleAlignerLibrary	*ALib=dynamic_cast<AutoPCBHoleAlignerLibrary *>(TempLib->GetLibrary());
	ALib->PickupHoleColor = ColorThre.Cube;
	ShowThresholdList();
}

void EditAutoPCBHoleAlignerLibrary::on_pushButtonAddAllColor_clicked()
{
	ColorThre.Cube.Add(qRgb(128, 128, 128), 222);
	ColorThre.Repaint();
	AutoPCBHoleAlignerLibrary	*ALib=dynamic_cast<AutoPCBHoleAlignerLibrary *>(TempLib->GetLibrary());
	ALib->PickupHoleColor = ColorThre.Cube;
	ShowThresholdList();

}

void EditAutoPCBHoleAlignerLibrary::on_pushButtonAddColorArea_clicked()
{
	ColorSampleList	Sample;
	Sample.Set(RGBPanel.Cube, RGBPanel.Ext);
	ColorThre.Cube.Add(*Sample.GetColorLogic(), 0);

	ColorThre.Repaint();
	AutoPCBHoleAlignerLibrary	*ALib=dynamic_cast<AutoPCBHoleAlignerLibrary *>(TempLib->GetLibrary());
	ALib->PickupHoleColor = ColorThre.Cube;
	ShowThresholdList();
}

void EditAutoPCBHoleAlignerLibrary::on_pushButtonEliminateColorArea_clicked()
{
	ColorSampleList	Sample;
	Sample.Set(RGBPanel.Cube);
	ColorThre.Cube.Eliminate(*Sample.GetColorLogic(), 0);

	ColorThre.Repaint();
	AutoPCBHoleAlignerLibrary	*ALib=dynamic_cast<AutoPCBHoleAlignerLibrary *>(TempLib->GetLibrary());
	ALib->PickupHoleColor = ColorThre.Cube;
	ShowThresholdList();
}

void EditAutoPCBHoleAlignerLibrary::on_listWidgetBaseColor_doubleClicked(const QModelIndex& index)
{
	int	row = ui->listWidgetBaseColor->currentRow();
	if (row < 0)
		return;
	ColorSpace* c = ColorThre.Cube.GetBase(row);
	if (c != NULL) {
		ColorThre.Cube.RemoveBase(c);
		delete	c;
	}
	ColorThre.Repaint();
	ShowThresholdList();
}

void EditAutoPCBHoleAlignerLibrary::on_listWidgetEliminatedColor_doubleClicked(const QModelIndex& index)
{
	int	row = ui->listWidgetEliminatedColor->currentRow();
	if (row < 0)
		return;
	ColorSpace* c = ColorThre.Cube.GetEliminated(row);
	if (c != NULL) {
		ColorThre.Cube.RemoveEliminated(c);
		delete	c;
	}
	ColorThre.Repaint();
	ShowThresholdList();
}

void EditAutoPCBHoleAlignerLibrary::on_tableWidgetLibList_clicked(const QModelIndex& Index)
{
	int	r = Index.row();
	AlgorithmLibraryList* a = LibList.GetItem(r);
	if (a != NULL) {
		TempLib->SetLibID(a->GetLibID());

		CmdLoadAutoPCBHoleAlignerLibraryPacket	Packet(GetLayersBase());
		Packet.Point = TempLib;
		AutoPCBHoleAlignerBase* BBase = GetAutoPCBHoleAlignerBase();
		if (BBase != NULL) {
			BBase->TransmitDirectly(&Packet);
			if (Packet.Success == true) {
				ShowLibrary(*TempLib);
				AutoPCBHoleAlignerLibrary	*ALib=dynamic_cast<AutoPCBHoleAlignerLibrary *>(TempLib->GetLibrary());
				ColorThre.Cube = ALib->PickupHoleColor;
				ColorThre.Repaint();
				ShowThresholdList();
				ui->ButtonLibSave->setEnabled(true);
				ui->ButtonLibDelete->setEnabled(true);
			}
			else {
				QMessageBox::critical(NULL, /**/"Library error", LangSolver.GetString(EditAutoPCBHoleAlignerLibrary_LS, LID_6)/*"Not loaded this library record"*/);
			}
		}
	}
}

/*
void EditAutoPCBHoleAlignerLibrary::on_listWidgetBaseColor_doubleClicked(QModelIndex)
{

}

void EditAutoPCBHoleAlignerLibrary::on_listWidgetEliminatedColor_doubleClicked(QModelIndex)
{

}

void EditAutoPCBHoleAlignerLibrary::on_ButtonLibNew_clicked()
{

}

void EditAutoPCBHoleAlignerLibrary::on_ButtonLibDelete_clicked()
{

}

void EditAutoPCBHoleAlignerLibrary::on_ButtonLibSaveNew_clicked()
{

}

void EditAutoPCBHoleAlignerLibrary::on_ButtonLibSave_clicked()
{

}

void EditAutoPCBHoleAlignerLibrary::on_pushButton_clicked()
{

}

void EditAutoPCBHoleAlignerLibrary::on_pushButtonAddAllColor_clicked()
{

}

void EditAutoPCBHoleAlignerLibrary::on_pushButtonAddPickupColor_clicked()
{

}

void EditAutoPCBHoleAlignerLibrary::on_pushButtonSubPickupColor_clicked()
{

}

void EditAutoPCBHoleAlignerLibrary::on_pushButtonAddColorArea_clicked()
{

}

void EditAutoPCBHoleAlignerLibrary::on_pushButtonEliminateColorArea_clicked()
{

}

void EditAutoPCBHoleAlignerLibrary::on_pushButtonAddColor_clicked()
{

}

void EditAutoPCBHoleAlignerLibrary::on_pushButtonEliminateColor_clicked()
{

}
*/
