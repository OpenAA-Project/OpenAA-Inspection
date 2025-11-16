//#include "PropertyFlatInspectionResource.h"
#include "EditFlatInspectionLibraryDialog.h"
#include "ui_EditFlatInspectionLibraryDialog.h"
#include "XFlatInspection.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "ImageControlTools.h"
#include "XGUI.h"
#include "XPropertyFlatInspectionPacket.h"
#include <QMessageBox>
#include <QColorDialog> 
#include "XGeneralDialog.h"

EditFlatInspectionLibraryDialog::EditFlatInspectionLibraryDialog(LayersBase *base ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(base),
    ui(new Ui::EditFlatInspectionLibraryDialog)
{
    ui->setupUi(this);
	//LangSolver.SetUI(this);

	OnChanging	=false;
	LibFolderID =-1;

	FlatInspectionBase	*BBase=GetFlatInspectionBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();
	pLibFolderForm=new GeneralLibFolderForm(LibType,GetLayersBase(),ui->frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
	pLibFolderForm->SetCurrentLibFolder(GetLayersBase()->GetLibFolderID());

	LLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempFlatInspectionLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		LLib=Packet.Point;
	}
	ui->tableWidgetLibList	->setColumnWidth(0,48);
	ui->tableWidgetLibList	->setColumnWidth(1,120);

	ui->ButtonLibSave	->setEnabled(false);
	ui->ButtonLibDelete	->setEnabled(false);

	ui->tabWidgetGeneration	->setCurrentIndex(0);
	ui->tabWidget			->setCurrentIndex(0);
	on_toolButtonPickup_clicked();
	on_toolButtonInspect_clicked();
	InstallOperationLog(this);
}

EditFlatInspectionLibraryDialog::~EditFlatInspectionLibraryDialog()
{
    delete ui;

	delete	LLib;
	LLib=NULL;
}

FlatInspectionBase	*EditFlatInspectionLibraryDialog::GetFlatInspectionBase(void)
{
	return (FlatInspectionBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"FlatInspection");
}

void	EditFlatInspectionLibraryDialog::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	//ui->tableWidgetLibList->clear();
	ui->tableWidgetLibList->setRowCount(0);
	FlatInspectionBase	*BBase=GetFlatInspectionBase();
	if(BBase!=NULL){
		CmdGetFlatInspectionLibraryListPacket	Packet(GetLayersBase());
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
void EditFlatInspectionLibraryDialog::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		LLib->SetLibID(a->GetLibID());

		CmdLoadFlatInspectionLibraryPacket	Packet(GetLayersBase());
		Packet.Point=LLib;
		FlatInspectionBase	*BBase=GetFlatInspectionBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				ShowLibrary(*LLib);
				ui->ButtonLibSave	->setEnabled(true);
				ui->ButtonLibDelete	->setEnabled(true);
			}
			else{
				QMessageBox::critical(NULL
									, "Library error"
									, "Not loaded this library record");
			}
		}
	}
}

void	EditFlatInspectionLibraryDialog::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	if(data.GetLibID()<0)
		ui->EditLibID->setText(/**/"");
	else
		ui->EditLibID->setText(QString::number(data.GetLibID()));
	ui->EditLibName	->setText(data.GetLibName());

	FlatInspectionLibrary *d=(FlatInspectionLibrary *)data.GetLibrary();

	ui->EditPickupRL					->setValue(d->PickupRL);
	ui->EditPickupRH					->setValue(d->PickupRH);
	ui->EditPickupGL					->setValue(d->PickupGL);
	ui->EditPickupGH					->setValue(d->PickupGH);
	ui->EditPickupBL					->setValue(d->PickupBL);
	ui->EditPickupBH					->setValue(d->PickupBH);


	ui->EditMinFlatInspectionSize		->setValue(d->MinFlatInspectionSize);
	ui->EditMaxFlatInspectionSize		->setValue(d->MaxFlatInspectionSize);
	ui->EditMinFlatInspectionDots		->setValue(d->MinFlatInspectionDots);
	ui->EditMaxFlatInspectionDots		->setValue(d->MaxFlatInspectionDots);
	ui->EditLimitFlatInspectionSize		->setValue(d->LimitFlatInspectionSize);
	ui->EditOverlappedLength			->setValue(d->OverlappedLength);
	ui->EditSpaceToOutline				->setValue(d->SpaceToOutline);
	ui->EditNoiseSize					->setValue(d->NoiseSize);
	ui->EditNoiseSizePinHole			->setValue(d->NoiseSizePinHole);

	ui->EditOKDotB					->setValue(d->Broad.OKDot);
	ui->EditOKLengthB				->setValue(d->Broad.OKLength);
	ui->EditRThrOffsetBL			->setValue(d->Broad.RThrOffsetL);
	ui->EditRThrOffsetBH			->setValue(d->Broad.RThrOffsetH);
	ui->EditGThrOffsetBL			->setValue(d->Broad.GThrOffsetL);
	ui->EditGThrOffsetBH			->setValue(d->Broad.GThrOffsetH);
	ui->EditBThrOffsetBL			->setValue(d->Broad.BThrOffsetL);
	ui->EditBThrOffsetBH			->setValue(d->Broad.BThrOffsetH);

	ui->EditOKDotN					->setValue(d->Narrow.OKDot);
	ui->EditOKLengthN				->setValue(d->Narrow.OKLength);
	ui->EditRThrOffsetNL			->setValue(d->Narrow.RThrOffsetL);
	ui->EditRThrOffsetNH			->setValue(d->Narrow.RThrOffsetH);
	ui->EditGThrOffsetNL			->setValue(d->Narrow.GThrOffsetL);
	ui->EditGThrOffsetNH			->setValue(d->Narrow.GThrOffsetH);
	ui->EditBThrOffsetNL			->setValue(d->Narrow.BThrOffsetL);
	ui->EditBThrOffsetNH			->setValue(d->Narrow.BThrOffsetH);

	ui->EditMultiSpotDot			->setValue(d->MultiSpotDot	);
	ui->EditMultiSpotCount			->setValue(d->MultiSpotCount);
	ui->EditMultiSpotDotGathered	->setValue(d->MultiSpotDotGathered	);
	ui->EditMultiSpotCountGathered	->setValue(d->MultiSpotCountGathered);
	ui->EditMultiSpotLengthGathered	->setValue(d->MultiSpotLengthGathered);
	ui->EditBackGroundOKDot			->setValue(d->BackGroundOKDot);
	ui->EditBackGroundOKLength		->setValue(d->BackGroundOKLength);
	ui->checkBoxUseBackGround		->setChecked(d->UseBackGround);

	ui->EditAdjustBlack				->setValue	(d->AdjustBlack);
	ui->EditAdjustWhite				->setValue	(d->AdjustWhite);
	ui->EditAreaSearchX				->setValue	(d->AreaSearchX);
	ui->EditAreaSearchY				->setValue	(d->AreaSearchY);
	ui->EditSelfSearch				->setValue	(d->SelfSearch);
	ui->EditMaxAreaSearch			->setValue	(d->MaxAreaSearch);
	ui->EditMaxSelfSearch			->setValue	(d->MaxSelfSearch);

	ui->checkBoxRedCheckMode			->setChecked(d->RedCheckMode		);
	ui->EditRedHighRate					->setValue	(d->RedHighRate			);
	ui->EditRedMinBrightness			->setValue	(d->RedMinBrightness	);
	ui->EditRedGBMerginRate				->setValue	(d->RedGBMerginRate		);
	ui->EditRedGBMerginOffset			->setValue	(d->RedGBMerginOffset	);
	ui->EditRedOKDot					->setValue	(d->RedOKDot			);
	ui->EditRedShrink					->setValue	(d->RedShrink			);


	ui->checkBoxVariationMode				->setChecked(d->VariationMode);
	ui->doubleSpinBoxVariationRL			->setValue(d->VariationRL);
	ui->doubleSpinBoxVariationRH			->setValue(d->VariationRH);
	ui->doubleSpinBoxVariationGL			->setValue(d->VariationGL);
	ui->doubleSpinBoxVariationGH			->setValue(d->VariationGH);
	ui->doubleSpinBoxVariationBL			->setValue(d->VariationBL);
	ui->doubleSpinBoxVariationBH			->setValue(d->VariationBH);
	ui->EditVariationAdaptMinSize			->setValue(d->VariationAdaptMinSize);
	ui->doubleSpinBoxVariationMultiplyMaster->setValue(d->VariationMultiplyMaster);
	ui->checkBoxVariationDifMaster			->setChecked(d->VariationDifMaster);
	ui->checkBoxVariationAndLogic			->setChecked(d->VariationAndLogic);
	ui->doubleSpinBoxVariationSubMasterVari	->setValue(d->VariationSubMasterVari);

	ui->checkBoxLineMode			->setChecked(d->LineMode		);
	ui->EditLineOKMinLength			->setValue(d->LineOKMinLength		);
	ui->EditLineMaxWidth			->setValue(d->LineMaxWidth			);
	ui->EditLineMinDensityPercent	->setValue(d->LineMinDensityPercent	);
	ui->EditLineMinCluster			->setValue(d->LineMinCluster		);
}

void	EditFlatInspectionLibraryDialog::GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data)
{
	data.SetLibName(ui->EditLibName	->text());

	FlatInspectionLibrary *d=(FlatInspectionLibrary *)data.GetLibrary();

	d->PickupRL						=ui->EditPickupRL			->value();
	d->PickupRH						=ui->EditPickupRH			->value();
	d->PickupGL						=ui->EditPickupGL			->value();
	d->PickupGH						=ui->EditPickupGH			->value();
	d->PickupBL						=ui->EditPickupBL			->value();
	d->PickupBH						=ui->EditPickupBH			->value();

	d->MinFlatInspectionSize		=ui->EditMinFlatInspectionSize	->value();
	d->MaxFlatInspectionSize		=ui->EditMaxFlatInspectionSize	->value();
	d->MinFlatInspectionDots		=ui->EditMinFlatInspectionDots	->value();
	d->MaxFlatInspectionDots		=ui->EditMaxFlatInspectionDots	->value();
	d->LimitFlatInspectionSize	=ui->EditLimitFlatInspectionSize	->value();
	d->OverlappedLength				=ui->EditOverlappedLength			->value();
	d->SpaceToOutline				=ui->EditSpaceToOutline				->value();
	d->NoiseSize					=ui->EditNoiseSize					->value();
	d->NoiseSizePinHole				=ui->EditNoiseSizePinHole			->value();

	d->Broad.OKDot				=ui->EditOKDotB			->value();
	d->Broad.OKLength			=ui->EditOKLengthB		->value();
	d->Broad.RThrOffsetL		=ui->EditRThrOffsetBL	->value();
	d->Broad.RThrOffsetH		=ui->EditRThrOffsetBH	->value();
	d->Broad.GThrOffsetL		=ui->EditGThrOffsetBL	->value();
	d->Broad.GThrOffsetH		=ui->EditGThrOffsetBH	->value();
	d->Broad.BThrOffsetL		=ui->EditBThrOffsetBL	->value();
	d->Broad.BThrOffsetH		=ui->EditBThrOffsetBH	->value();

	d->Narrow.OKDot				=ui->EditOKDotN			->value();
	d->Narrow.OKLength			=ui->EditOKLengthN		->value();
	d->Narrow.RThrOffsetL		=ui->EditRThrOffsetNL	->value();
	d->Narrow.RThrOffsetH		=ui->EditRThrOffsetNH	->value();
	d->Narrow.GThrOffsetL		=ui->EditGThrOffsetNL	->value();
	d->Narrow.GThrOffsetH		=ui->EditGThrOffsetNH	->value();
	d->Narrow.BThrOffsetL		=ui->EditBThrOffsetNL	->value();
	d->Narrow.BThrOffsetH		=ui->EditBThrOffsetNH	->value();

	d->MultiSpotDot				=ui->EditMultiSpotDot		->value();
	d->MultiSpotCount			=ui->EditMultiSpotCount		->value();
	d->MultiSpotDotGathered		=ui->EditMultiSpotDotGathered	->value();
	d->MultiSpotCountGathered	=ui->EditMultiSpotCountGathered	->value();
	d->MultiSpotLengthGathered	=ui->EditMultiSpotLengthGathered->value();
	d->BackGroundOKDot			=ui->EditBackGroundOKDot	->value();
	d->BackGroundOKLength		=ui->EditBackGroundOKLength	->value();
	d->UseBackGround			=ui->checkBoxUseBackGround	->isChecked();

	d->AdjustBlack			=ui->EditAdjustBlack		->value();
	d->AdjustWhite			=ui->EditAdjustWhite		->value();
	d->AreaSearchX			=ui->EditAreaSearchX		->value();
	d->AreaSearchY			=ui->EditAreaSearchY		->value();
	d->SelfSearch			=ui->EditSelfSearch			->value();
	d->MaxAreaSearch		=ui->EditMaxAreaSearch		->value();
	d->MaxSelfSearch		=ui->EditMaxSelfSearch		->value();

	d->RedCheckMode			=ui->checkBoxRedCheckMode				->isChecked();
	d->RedHighRate			=ui->EditRedHighRate					->value	();
	d->RedMinBrightness		=ui->EditRedMinBrightness				->value	();
	d->RedGBMerginRate		=ui->EditRedGBMerginRate				->value	();
	d->RedGBMerginOffset	=ui->EditRedGBMerginOffset				->value	();
	d->RedOKDot				=ui->EditRedOKDot						->value	();
	d->RedShrink			=ui->EditRedShrink						->value	();

	QString	LComment=ui->plainTextEditExplain->toPlainText();
	d->SetLibComment(LComment);

	d->VariationMode			=ui->checkBoxVariationMode		->isChecked();
	d->VariationRL				=ui->doubleSpinBoxVariationRL	->value();
	d->VariationRH				=ui->doubleSpinBoxVariationRH	->value();
	d->VariationGL				=ui->doubleSpinBoxVariationGL	->value();
	d->VariationGH				=ui->doubleSpinBoxVariationGH	->value();
	d->VariationBL				=ui->doubleSpinBoxVariationBL	->value();
	d->VariationBH				=ui->doubleSpinBoxVariationBH	->value();
	d->VariationMultiplyMaster	=ui->doubleSpinBoxVariationMultiplyMaster->value();
	d->VariationDifMaster		=ui->checkBoxVariationDifMaster	->isChecked();
	d->VariationAndLogic		=ui->checkBoxVariationAndLogic	->isChecked();
	d->VariationSubMasterVari	=ui->doubleSpinBoxVariationSubMasterVari->value();

	d->VariationAdaptMinSize=ui->EditVariationAdaptMinSize	->value();

	d->LineMode				=ui->checkBoxLineMode			->isChecked();
	d->LineOKMinLength		=ui->EditLineOKMinLength		->value();
	d->LineMaxWidth			=ui->EditLineMaxWidth			->value();
	d->LineMinDensityPercent=ui->EditLineMinDensityPercent	->value();
	d->LineMinCluster		=ui->EditLineMinCluster			->value();

}
void EditFlatInspectionLibraryDialog::on_toolButtonPickup_clicked()
{
	if(ui->toolButtonPickup->isChecked()==true){
		ui->stackedWidget->setCurrentIndex(0);
	}
}

void EditFlatInspectionLibraryDialog::on_toolButtonInspect_clicked()
{
	if(ui->toolButtonInspect->isChecked()==true){
		ui->stackedWidget->setCurrentIndex(1);
	}
}

void EditFlatInspectionLibraryDialog::on_ButtonLibNew_clicked()
{
	if(LLib==NULL)
		return;
	LLib->Reset();
	CmdClearFlatInspectionLibraryPacket	Packet(GetLayersBase());
	Packet.Point=LLib;
	FlatInspectionBase	*BBase=GetFlatInspectionBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);
	}
	ShowLibrary(*LLib);
	ui->ButtonLibSave	->setEnabled(false);
	ui->ButtonLibDelete	->setEnabled(false);
}

void EditFlatInspectionLibraryDialog::on_ButtonLibDelete_clicked()
{
	if(LLib==NULL)
		return;
	if(LLib->GetLibID()<0)
		return;
	QString  msg="Delete OK?";
	int	ret=QMessageBox::question(NULL, "Choose"
					, msg
					, QMessageBox::Yes , QMessageBox::No, QMessageBox::NoButton);
	if(ret==QMessageBox::Yes){
		CmdDeleteFlatInspectionLibraryPacket	Packet(GetLayersBase());
		Packet.Point=LLib->GetLibrary();
		FlatInspectionBase	*BBase=GetFlatInspectionBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			on_ButtonLibNew_clicked();
			SlotSelectLibFolder(LibFolderID ,/**/"");
		}
	}
}

void EditFlatInspectionLibraryDialog::on_ButtonLibSaveNew_clicked()
{
	if(LLib==NULL)
		return;
	GetLibraryFromWindow(*LLib);

	if(LLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL, "Warning"
																, "No Library Name"
																, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	LLib->SetLibFolderID(LibFolderID);
	CmdInsertFlatInspectionLibraryPacket	Packet(GetLayersBase());
	Packet.Point=LLib;
	FlatInspectionBase	*BBase=GetFlatInspectionBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);		
		ShowLibrary(*LLib);
		ui->ButtonLibSave	->setEnabled(true);
		ui->ButtonLibDelete	->setEnabled(true);
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}

void EditFlatInspectionLibraryDialog::on_ButtonLibSave_clicked()
{
	if(LLib==NULL)
		return;
	GetLibraryFromWindow(*LLib);
	if(LLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL, "Warning"
																, "No Library Name"
																, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	if(LLib->GetLibID()<0){
		LLib->SetLibFolderID(LibFolderID);

		CmdInsertFlatInspectionLibraryPacket	Packet(GetLayersBase());
		Packet.Point=LLib;
		FlatInspectionBase	*BBase=GetFlatInspectionBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			ShowLibrary(*LLib);
			ui->ButtonLibSave	->setEnabled(true);
			ui->ButtonLibDelete	->setEnabled(true);
		}
	}
	else{
		CmdUpdateFlatInspectionLibraryPacket	Packet(GetLayersBase());
		Packet.Point=LLib;
		FlatInspectionBase	*BBase=GetFlatInspectionBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
		}
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}

void EditFlatInspectionLibraryDialog::on_pushButton_clicked()
{
	close();
}

void EditFlatInspectionLibraryDialog::on_EditAreaSearchX_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	OnChanging=true;
	ui->doubleSpinBoxAreaSearchX->setValue(TransformPixelToUnit(-1,arg1));
	OnChanging=false;
}


void EditFlatInspectionLibraryDialog::on_doubleSpinBoxAreaSearchX_valueChanged(double arg1)
{
	if(OnChanging==true){
		return;
	}
	OnChanging=true;
	ui->EditAreaSearchX->setValue(TransformUnitToPixel(-1,arg1));
	OnChanging=false;
}


void EditFlatInspectionLibraryDialog::on_EditAreaSearchY_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	OnChanging=true;
	ui->doubleSpinBoxAreaSearchY->setValue(TransformPixelToUnit(-1,arg1));
	OnChanging=false;
}


void EditFlatInspectionLibraryDialog::on_doubleSpinBoxAreaSearchY_valueChanged(double arg1)
{
	if(OnChanging==true){
		return;
	}
	OnChanging=true;
	ui->EditAreaSearchY->setValue(TransformUnitToPixel(-1,arg1));
	OnChanging=false;
}


void EditFlatInspectionLibraryDialog::on_EditSelfSearch_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	OnChanging=true;
	ui->doubleSpinBoxSelfSearch->setValue(TransformPixelToUnit(-1,arg1));
	OnChanging=false;
}

void EditFlatInspectionLibraryDialog::on_doubleSpinBoxSelfSearch_valueChanged(double arg1)
{
	if(OnChanging==true){
		return;
	}
	OnChanging=true;
	ui->EditSelfSearch->setValue(TransformUnitToPixel(-1,arg1));
	OnChanging=false;
}

void EditFlatInspectionLibraryDialog::on_EditOKDotB_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	OnChanging=true;
	ui->doubleSpinBoxOKDotB->setValue(TransformPixelToUnitSquare(-1,arg1));
	OnChanging=false;
}

void EditFlatInspectionLibraryDialog::on_doubleSpinBoxOKDotB_valueChanged(double arg1)
{
	if(OnChanging==true){
		return;
	}
	OnChanging=true;
	ui->EditOKDotB->setValue(TransformUnitToPixelSquare(-1,arg1));
	OnChanging=false;
}

void EditFlatInspectionLibraryDialog::on_EditOKDotN_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	OnChanging=true;
	ui->doubleSpinBoxOKDotN->setValue(TransformPixelToUnitSquare(-1,arg1));
	OnChanging=false;
}

void EditFlatInspectionLibraryDialog::on_doubleSpinBoxOKDotN_valueChanged(double arg1)
{
	if(OnChanging==true){
		return;
	}
	OnChanging=true;
	ui->EditOKDotN->setValue(TransformUnitToPixelSquare(-1,arg1));
	OnChanging=false;
}

void EditFlatInspectionLibraryDialog::on_toolButtonExplain_clicked()
{
	if(ui->toolButtonExplain->isChecked()==true){
		ui->stackedWidget->setCurrentIndex(2);
	}
}



