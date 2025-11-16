#include "PropertyDotColorMatchingResource.h"
#include "EditDotColorMatchingLibraryDialog.h"
#include "ui_EditDotColorMatchingLibraryDialog.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "ImageControlTools.h"
#include "XGUI.h"
#include "XPropertyDotColorMatchingPacket.h"
#include <QMessageBox>
#include <QColorDialog> 
#include "XGeneralDialog.h"
#include "SubtractLibIDDialog.h"

EditDotColorMatchingLibraryDialog::EditDotColorMatchingLibraryDialog(LayersBase *base ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(base),
    ui(new Ui::EditDotColorMatchingLibraryDialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	OnChanging	=false;
	LibFolderID =-1;
	MasterNoOriginCode	=-1;
	DotColorMatchingBase	*BBase=GetDotColorMatchingBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();
	pLibFolderForm=new GeneralLibFolderForm(LibType,GetLayersBase(),ui->frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
	pLibFolderForm->SetCurrentLibFolder(GetLayersBase()->GetLibFolderID());

	LLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempDotColorMatchingLibraryPacket	Packet(GetLayersBase());
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

EditDotColorMatchingLibraryDialog::~EditDotColorMatchingLibraryDialog()
{
    delete ui;

	delete	LLib;
	LLib=NULL;
}

DotColorMatchingBase	*EditDotColorMatchingLibraryDialog::GetDotColorMatchingBase(void)
{
	return (DotColorMatchingBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DotColorMatching");
}

void	EditDotColorMatchingLibraryDialog::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	//ui->tableWidgetLibList->clear();
	ui->tableWidgetLibList->setRowCount(0);
	DotColorMatchingBase	*BBase=GetDotColorMatchingBase();
	if(BBase!=NULL){
		CmdGetDotColorMatchingLibraryListPacket	Packet(GetLayersBase());
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
void EditDotColorMatchingLibraryDialog::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		LLib->SetLibID(a->GetLibID());

		CmdLoadDotColorMatchingLibraryPacket	Packet(GetLayersBase());
		Packet.Point=LLib;
		DotColorMatchingBase	*BBase=GetDotColorMatchingBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				ShowLibrary(*LLib);
				ui->ButtonLibSave	->setEnabled(true);
				ui->ButtonLibDelete	->setEnabled(true);
			}
			else{
				QMessageBox::critical(NULL
									, LangSolver.GetString(EditDotColorMatchingLibraryDialog_LS,LID_2)/*"Library error"*/
									, LangSolver.GetString(EditDotColorMatchingLibraryDialog_LS,LID_3)/*"Not loaded this library record"*/);
			}
		}
	}
}

void	EditDotColorMatchingLibraryDialog::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	if(data.GetLibID()<0)
		ui->EditLibID->setText(/**/"");
	else
		ui->EditLibID->setText(QString::number(data.GetLibID()));
	ui->EditLibName	->setText(data.GetLibName());

	DotColorMatchingLibrary *d=(DotColorMatchingLibrary *)data.GetLibrary();

	ui->EditPickupRL					->setValue(d->PickupRL);
	ui->EditPickupRH					->setValue(d->PickupRH);
	ui->EditPickupGL					->setValue(d->PickupGL);
	ui->EditPickupGH					->setValue(d->PickupGH);
	ui->EditPickupBL					->setValue(d->PickupBL);
	ui->EditPickupBH					->setValue(d->PickupBH);
	ui->EditEvenWidth0					->setValue(d->EvenWidth0);
	ui->EditEvenWidth255				->setValue(d->EvenWidth255);
	ui->EditPriorityToShow				->setValue(d->PriorityToShow);

	ui->EditMinDotColorMatchingSize		->setValue(d->MinDotColorMatchingSize);
	ui->EditMaxDotColorMatchingSize		->setValue(d->MaxDotColorMatchingSize);
	ui->EditMinDotColorMatchingDots		->setValue(d->MinDotColorMatchingDots);
	ui->EditMaxDotColorMatchingDots		->setValue(d->MaxDotColorMatchingDots);
	ui->EditLimitDotColorMatchingSize	->setValue(d->LimitDotColorMatchingSize);
	ui->EditOverlappedLength			->setValue(d->OverlappedLength);
	ui->EditSpaceToOutline				->setValue(d->SpaceToOutline);
	ui->EditNoiseSize					->setValue(d->NoiseSize);
	ui->EditNoiseSizePinHole			->setValue(d->NoiseSizePinHole);
	ui->EditPriority					->setValue(d->Priority);
	ui->comboBoxAreaType				->setCurrentIndex(d->AreaType);
	ui->checkBoxEnableOverlap			->setChecked(d->EnableOverlap);
	ui->checkBoxGenerateOutlineMode		->setChecked(d->GenerateOutlineMode);
	ui->EditGenerateOnEdgeWidth			->setValue(d->GenerateOnEdgeWidth);
	ui->EditOutlineAroundPriorItems		->setValue(d->OutlineAroundPriorItems);
	ui->EditSearchDotForBrightnessRange	->setValue(d->SearchDotForBrightnessRange);
	ui->EditBindGroupArea				->setValue(d->BindGroupArea);
	ui->checkBoxGenerateHalfPitch		->setChecked(d->GenerateHalfPitch);
	ui->doubleSpinBoxThresholdPickupEdge->setValue(d->ThresholdPickupEdge);
	ui->doubleSpinBoxThresholdFlatPattern->setValue(d->ThresholdFlatPattern);

	ui->EditBrightWidthBRL			->setValue(d->Broad.BrightWidthRL);
	ui->EditBrightWidthBRH			->setValue(d->Broad.BrightWidthRH);
	ui->EditBrightWidthBGL			->setValue(d->Broad.BrightWidthGL);
	ui->EditBrightWidthBGH			->setValue(d->Broad.BrightWidthGH);
	ui->EditBrightWidthBBL			->setValue(d->Broad.BrightWidthBL);
	ui->EditBrightWidthBBH			->setValue(d->Broad.BrightWidthBH);
	ui->EditOKDotB					->setValue(d->Broad.OKDot);
	ui->EditOKLengthB				->setValue(d->Broad.OKLength);
	ui->EditRThrOffsetBL			->setValue(d->Broad.RThrOffsetL);
	ui->EditRThrOffsetBH			->setValue(d->Broad.RThrOffsetH);
	ui->EditGThrOffsetBL			->setValue(d->Broad.GThrOffsetL);
	ui->EditGThrOffsetBH			->setValue(d->Broad.GThrOffsetH);
	ui->EditBThrOffsetBL			->setValue(d->Broad.BThrOffsetL);
	ui->EditBThrOffsetBH			->setValue(d->Broad.BThrOffsetH);

	ui->EditBrightWidthNRL			->setValue(d->Narrow.BrightWidthRL);
	ui->EditBrightWidthNRH			->setValue(d->Narrow.BrightWidthRH);
	ui->EditBrightWidthNGL			->setValue(d->Narrow.BrightWidthGL);
	ui->EditBrightWidthNGH			->setValue(d->Narrow.BrightWidthGH);
	ui->EditBrightWidthNBL			->setValue(d->Narrow.BrightWidthBL);
	ui->EditBrightWidthNBH			->setValue(d->Narrow.BrightWidthBH);
	ui->EditOKDotN					->setValue(d->Narrow.OKDot);
	ui->EditOKLengthN				->setValue(d->Narrow.OKLength);
	ui->EditRThrOffsetNL			->setValue(d->Narrow.RThrOffsetL);
	ui->EditRThrOffsetNH			->setValue(d->Narrow.RThrOffsetH);
	ui->EditGThrOffsetNL			->setValue(d->Narrow.GThrOffsetL);
	ui->EditGThrOffsetNH			->setValue(d->Narrow.GThrOffsetH);
	ui->EditBThrOffsetNL			->setValue(d->Narrow.BThrOffsetL);
	ui->EditBThrOffsetNH			->setValue(d->Narrow.BThrOffsetH);

	ui->doubleSpinBoxVarietySigma	->setValue(d->VarietySigma);
	ui->EditMultiSpotDot			->setValue(d->MultiSpotDot	);
	ui->EditMultiSpotCount			->setValue(d->MultiSpotCount);
	ui->EditMultiSpotDotGathered	->setValue(d->MultiSpotDotGathered	);
	ui->EditMultiSpotCountGathered	->setValue(d->MultiSpotCountGathered);
	ui->EditMultiSpotLengthGathered	->setValue(d->MultiSpotLengthGathered);
	ui->EditBackGroundOKDot			->setValue(d->BackGroundOKDot);
	ui->EditBackGroundOKLength		->setValue(d->BackGroundOKLength);
	ui->checkBoxUseBackGround		->setChecked(d->UseBackGround);
	ui->checkBoxGenerateOnlyLimitedMask	->setChecked(d->GenerateOnlyLimitedMask);

	ui->EditAdjustBlack				->setValue	(d->AdjustBlack);
	ui->EditAdjustWhite				->setValue	(d->AdjustWhite);
	ui->EditAdjustContribute		->setValue	(d->AdjustContribute);
	ui->EditAreaSearchX				->setValue	(d->AreaSearchX);
	ui->EditAreaSearchY				->setValue	(d->AreaSearchY);
	ui->EditSelfSearch				->setValue	(d->SelfSearch);
	ui->checkBoxPreciseSearch		->setChecked(d->PreciseSearch);
	ui->checkBoxClusterize			->setChecked(d->Clusterize);
	ui->checkBoxEnableT2M			->setChecked(d->EnableT2M);
	ui->checkBoxEnableM2T			->setChecked(d->EnableM2T);
	ui->checkBoxUseMaster2			->setChecked(d->UseMaster2);
	ui->EditExpandToSubBlock		->setValue	(d->ExpandToSubBlock);
	ui->EditMaxAreaSearch			->setValue	(d->MaxAreaSearch);
	ui->EditMaxSelfSearch			->setValue	(d->MaxSelfSearch);

	ui->doubleSpinBoxScratchStartDirection	->setValue(d->ScratchStartDirection	);
	ui->doubleSpinBoxScratchRotationAngle	->setValue(d->ScratchRotationAngle	);
	ui->doubleSpinBoxScratchVariety			->setValue(d->ScratchVariety		);
	ui->EditScratchDetectLevelH				->setValue(d->ScratchDetectLevelH	);
	ui->EditScratchDetectLevelL				->setValue(d->ScratchDetectLevelL	);
	ui->EditScratchMaxWidth					->setValue(d->ScratchMaxWidth		);
	ui->checkBoxScratchEnable				->setChecked(d->ScratchEnable		);
	ui->checkBoxScratchUseMaster			->setChecked(d->ScratchUseMaster	);
	ui->doubleSpinBoxScratchVOffset			->setValue	(d->ScratchVOffset		);
	ui->doubleSpinBoxScratchDiff			->setValue	(d->ScratchDiff			);

	ui->checkBoxRedCheckMode			->setChecked(d->RedCheckMode		);
	ui->EditRedHighRate					->setValue	(d->RedHighRate			);
	ui->EditRedMinBrightness			->setValue	(d->RedMinBrightness	);
	ui->EditRedGBMerginRate				->setValue	(d->RedGBMerginRate		);
	ui->EditRedGBMerginOffset			->setValue	(d->RedGBMerginOffset	);
	ui->EditRedOKDot					->setValue	(d->RedOKDot			);
	ui->EditRedShrink					->setValue	(d->RedShrink			);

	ui->EditMatchBrightnessByLayerH		->setValue	(d->MatchBrightnessByLayerH);
	ui->EditMatchBrightnessByLayerL		->setValue	(d->MatchBrightnessByLayerL);

	ui->comboBoxUseOneLayer	->clear();
	ui->comboBoxUseOneLayer	->addItem(LangSolver.GetString(EditDotColorMatchingLibraryDialog_LS,LID_10)/*"Color"*/);
	int	LayerNumb=GetLayersBase()->GetMaxLayerNumb();
	for(int layer=0;layer<LayerNumb;layer++){
		ui->comboBoxUseOneLayer	->addItem(QString(LangSolver.GetString(EditDotColorMatchingLibraryDialog_LS,LID_11)/*"Layer"*/)+QString::number(layer));
	}
	ui->comboBoxUseOneLayer	->setCurrentIndex((d->UseOneLayer==0xFF)?0:d->UseOneLayer+1);
	MasterNoOriginCode	=d->MasterNoOriginCode;
	ui->plainTextEditExplain	->setPlainText(d->GetLibComment());

	ui->checkBoxHsvCheckMode		->setChecked(d->HsvCheckMode);
	ui->checkBoxHsvFixedColorMode	->setChecked(d->HsvFixedColorMode);

	ui->EditHsvPHL	->setValue(d->HsvPHL);
	ui->EditHsvPHH	->setValue(d->HsvPHH);
	ui->EditHsvPSL	->setValue(d->HsvPSL);
	ui->EditHsvPSH	->setValue(d->HsvPSH);
	ui->EditHsvPVL	->setValue(d->HsvPVL);
	ui->EditHsvPVH	->setValue(d->HsvPVH);

	ui->EditHsvDHL	->setValue(d->HsvDHL);
	ui->EditHsvDHH	->setValue(d->HsvDHH);
	ui->EditHsvDSL	->setValue(d->HsvDSL);
	ui->EditHsvDSH	->setValue(d->HsvDSH);
	ui->EditHsvDVL	->setValue(d->HsvDVL);
	ui->EditHsvDVH	->setValue(d->HsvDVH);

	ui->EditHsvH	->setValue(d->HsvH);
	ui->EditHsvS	->setValue(d->HsvS);
	ui->EditHsvV	->setValue(d->HsvV);

	ui->EditHsvOKDot	->setValue(d->HsvOKDot);
	ui->EditHsvOKLength	->setValue(d->HsvOKLength);

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

	ui->checkBoxPitMode				->setChecked(d->PitMode);
	ui->EditPitBrightWidthRL		->setValue(d->PitBrightWidthRL);
	ui->EditPitBrightWidthRH		->setValue(d->PitBrightWidthRH);
	ui->EditPitBrightWidthGL		->setValue(d->PitBrightWidthGL);
	ui->EditPitBrightWidthGH		->setValue(d->PitBrightWidthGH);
	ui->EditPitBrightWidthBL		->setValue(d->PitBrightWidthBL);
	ui->EditPitBrightWidthBH		->setValue(d->PitBrightWidthBH);

	ui->checkBoxLineMode			->setChecked(d->LineMode		);
	ui->EditLineOKMinLength			->setValue(d->LineOKMinLength		);
	ui->EditLineMaxWidth			->setValue(d->LineMaxWidth			);
	ui->EditLineMinDensityPercent	->setValue(d->LineMinDensityPercent	);
	ui->EditLineMinCluster			->setValue(d->LineMinCluster		);
}

void	EditDotColorMatchingLibraryDialog::GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data)
{
	data.SetLibName(ui->EditLibName	->text());

	DotColorMatchingLibrary *d=(DotColorMatchingLibrary *)data.GetLibrary();

	d->PickupRL						=ui->EditPickupRL			->value();
	d->PickupRH						=ui->EditPickupRH			->value();
	d->PickupGL						=ui->EditPickupGL			->value();
	d->PickupGH						=ui->EditPickupGH			->value();
	d->PickupBL						=ui->EditPickupBL			->value();
	d->PickupBH						=ui->EditPickupBH			->value();
	d->PriorityToShow				=ui->EditPriorityToShow		->value();

	d->EvenWidth0					=ui->EditEvenWidth0			->value();
	d->EvenWidth255					=ui->EditEvenWidth255		->value();
	d->MinDotColorMatchingSize		=ui->EditMinDotColorMatchingSize	->value();
	d->MaxDotColorMatchingSize		=ui->EditMaxDotColorMatchingSize	->value();
	d->MinDotColorMatchingDots		=ui->EditMinDotColorMatchingDots	->value();
	d->MaxDotColorMatchingDots		=ui->EditMaxDotColorMatchingDots	->value();
	d->LimitDotColorMatchingSize	=ui->EditLimitDotColorMatchingSize	->value();
	d->OverlappedLength				=ui->EditOverlappedLength			->value();
	d->SpaceToOutline				=ui->EditSpaceToOutline				->value();
	d->NoiseSize					=ui->EditNoiseSize					->value();
	d->NoiseSizePinHole				=ui->EditNoiseSizePinHole			->value();
	d->Priority						=ui->EditPriority					->value();
	d->AreaType						=ui->comboBoxAreaType				->currentIndex();
	d->EnableOverlap				=ui->checkBoxEnableOverlap			->isChecked();
	d->GenerateOutlineMode			=ui->checkBoxGenerateOutlineMode	->isChecked();
	d->GenerateOnEdgeWidth			=ui->EditGenerateOnEdgeWidth		->value();
	d->OutlineAroundPriorItems		=ui->EditOutlineAroundPriorItems	->value();
	d->SearchDotForBrightnessRange	=ui->EditSearchDotForBrightnessRange->value();
	d->BindGroupArea				=ui->EditBindGroupArea				->value();
	d->GenerateHalfPitch			=ui->checkBoxGenerateHalfPitch		->isChecked();
	d->ThresholdPickupEdge			=ui->doubleSpinBoxThresholdPickupEdge->value();
	d->ThresholdFlatPattern			=ui->doubleSpinBoxThresholdFlatPattern->value();

	d->Broad.BrightWidthRL		=ui->EditBrightWidthBRL	->value();
	d->Broad.BrightWidthRH		=ui->EditBrightWidthBRH	->value();
	d->Broad.BrightWidthGL		=ui->EditBrightWidthBGL	->value();
	d->Broad.BrightWidthGH		=ui->EditBrightWidthBGH	->value();
	d->Broad.BrightWidthBL		=ui->EditBrightWidthBBL	->value();
	d->Broad.BrightWidthBH		=ui->EditBrightWidthBBH	->value();
	d->Broad.OKDot				=ui->EditOKDotB			->value();
	d->Broad.OKLength			=ui->EditOKLengthB		->value();
	d->Broad.RThrOffsetL		=ui->EditRThrOffsetBL	->value();
	d->Broad.RThrOffsetH		=ui->EditRThrOffsetBH	->value();
	d->Broad.GThrOffsetL		=ui->EditGThrOffsetBL	->value();
	d->Broad.GThrOffsetH		=ui->EditGThrOffsetBH	->value();
	d->Broad.BThrOffsetL		=ui->EditBThrOffsetBL	->value();
	d->Broad.BThrOffsetH		=ui->EditBThrOffsetBH	->value();

	d->Narrow.BrightWidthRL		=ui->EditBrightWidthNRL	->value();
	d->Narrow.BrightWidthRH		=ui->EditBrightWidthNRH	->value();
	d->Narrow.BrightWidthGL		=ui->EditBrightWidthNGL	->value();
	d->Narrow.BrightWidthGH		=ui->EditBrightWidthNGH	->value();
	d->Narrow.BrightWidthBL		=ui->EditBrightWidthNBL	->value();
	d->Narrow.BrightWidthBH		=ui->EditBrightWidthNBH	->value();
	d->Narrow.OKDot				=ui->EditOKDotN			->value();
	d->Narrow.OKLength			=ui->EditOKLengthN		->value();
	d->Narrow.RThrOffsetL		=ui->EditRThrOffsetNL	->value();
	d->Narrow.RThrOffsetH		=ui->EditRThrOffsetNH	->value();
	d->Narrow.GThrOffsetL		=ui->EditGThrOffsetNL	->value();
	d->Narrow.GThrOffsetH		=ui->EditGThrOffsetNH	->value();
	d->Narrow.BThrOffsetL		=ui->EditBThrOffsetNL	->value();
	d->Narrow.BThrOffsetH		=ui->EditBThrOffsetNH	->value();

	d->VarietySigma				=ui->doubleSpinBoxVarietySigma	->value();
	d->MultiSpotDot				=ui->EditMultiSpotDot		->value();
	d->MultiSpotCount			=ui->EditMultiSpotCount		->value();
	d->MultiSpotDotGathered		=ui->EditMultiSpotDotGathered	->value();
	d->MultiSpotCountGathered	=ui->EditMultiSpotCountGathered	->value();
	d->MultiSpotLengthGathered	=ui->EditMultiSpotLengthGathered->value();
	d->BackGroundOKDot			=ui->EditBackGroundOKDot	->value();
	d->BackGroundOKLength		=ui->EditBackGroundOKLength	->value();
	d->UseBackGround			=ui->checkBoxUseBackGround	->isChecked();
	d->GenerateOnlyLimitedMask	=ui->checkBoxGenerateOnlyLimitedMask	->isChecked();

	d->AdjustBlack			=ui->EditAdjustBlack		->value();
	d->AdjustWhite			=ui->EditAdjustWhite		->value();
	d->AdjustContribute		=ui->EditAdjustContribute	->value	();
	d->AreaSearchX			=ui->EditAreaSearchX		->value();
	d->AreaSearchY			=ui->EditAreaSearchY		->value();
	d->SelfSearch			=ui->EditSelfSearch			->value();
	d->PreciseSearch		=ui->checkBoxPreciseSearch	->isChecked();
	d->Clusterize			=ui->checkBoxClusterize		->isChecked();
	d->EnableT2M			=ui->checkBoxEnableT2M		->isChecked();
	d->EnableM2T			=ui->checkBoxEnableM2T		->isChecked();
	d->UseMaster2			=ui->checkBoxUseMaster2		->isChecked();
	d->ExpandToSubBlock		=ui->EditExpandToSubBlock	->value();
	d->MaxAreaSearch		=ui->EditMaxAreaSearch		->value();
	d->MaxSelfSearch		=ui->EditMaxSelfSearch		->value();

	d->ScratchStartDirection=ui->doubleSpinBoxScratchStartDirection	->value();
	d->ScratchRotationAngle	=ui->doubleSpinBoxScratchRotationAngle	->value();
	d->ScratchVariety		=ui->doubleSpinBoxScratchVariety		->value();
	d->ScratchDetectLevelH	=ui->EditScratchDetectLevelH			->value();
	d->ScratchDetectLevelL	=ui->EditScratchDetectLevelL			->value();
	d->ScratchMaxWidth		=ui->EditScratchMaxWidth				->value();
	d->ScratchEnable		=ui->checkBoxScratchEnable				->isChecked();
	d->ScratchUseMaster		=ui->checkBoxScratchUseMaster			->isChecked();
	d->ScratchVOffset		=ui->doubleSpinBoxScratchVOffset		->value();
	d->ScratchDiff			=ui->doubleSpinBoxScratchDiff			->value();

	d->RedCheckMode			=ui->checkBoxRedCheckMode				->isChecked();
	d->RedHighRate			=ui->EditRedHighRate					->value	();
	d->RedMinBrightness		=ui->EditRedMinBrightness				->value	();
	d->RedGBMerginRate		=ui->EditRedGBMerginRate				->value	();
	d->RedGBMerginOffset	=ui->EditRedGBMerginOffset				->value	();
	d->RedOKDot				=ui->EditRedOKDot						->value	();
	d->RedShrink			=ui->EditRedShrink						->value	();

	d->MatchBrightnessByLayerH=ui->EditMatchBrightnessByLayerH		->value	();
	d->MatchBrightnessByLayerL=ui->EditMatchBrightnessByLayerL		->value	();

	int	L=ui->comboBoxUseOneLayer	->currentIndex();
	if(L==0){
		d->UseOneLayer=0xFF;
	}
	else{
		d->UseOneLayer=L-1;
	}
	d->MasterNoOriginCode	=MasterNoOriginCode;

	QString	LComment=ui->plainTextEditExplain->toPlainText();
	d->SetLibComment(LComment);

	d->HsvCheckMode			=ui->checkBoxHsvCheckMode		->isChecked();
	d->HsvFixedColorMode	=ui->checkBoxHsvFixedColorMode	->isChecked();

	d->HsvPHL	=ui->EditHsvPHL	->value();
	d->HsvPHH	=ui->EditHsvPHH	->value();
	d->HsvPSL	=ui->EditHsvPSL	->value();
	d->HsvPSH	=ui->EditHsvPSH	->value();
	d->HsvPVL	=ui->EditHsvPVL	->value();
	d->HsvPVH	=ui->EditHsvPVH	->value();

	d->HsvDHL	=ui->EditHsvDHL	->value();
	d->HsvDHH	=ui->EditHsvDHH	->value();
	d->HsvDSL	=ui->EditHsvDSL	->value();
	d->HsvDSH	=ui->EditHsvDSH	->value();
	d->HsvDVL	=ui->EditHsvDVL	->value();
	d->HsvDVH	=ui->EditHsvDVH	->value();

	d->HsvH		=ui->EditHsvH	->value();
	d->HsvS		=ui->EditHsvS	->value();
	d->HsvV		=ui->EditHsvV	->value();

	d->HsvOKDot					=ui->EditHsvOKDot	->value();
	d->HsvOKLength				=ui->EditHsvOKLength->value();

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

	d->PitMode			=ui->checkBoxPitMode			->isChecked();
	d->PitBrightWidthRL	=ui->EditPitBrightWidthRL		->value();
	d->PitBrightWidthRH	=ui->EditPitBrightWidthRH		->value();
	d->PitBrightWidthGL	=ui->EditPitBrightWidthGL		->value();
	d->PitBrightWidthGH	=ui->EditPitBrightWidthGH		->value();
	d->PitBrightWidthBL	=ui->EditPitBrightWidthBL		->value();
	d->PitBrightWidthBH	=ui->EditPitBrightWidthBH		->value();

	d->LineMode				=ui->checkBoxLineMode			->isChecked();
	d->LineOKMinLength		=ui->EditLineOKMinLength		->value();
	d->LineMaxWidth			=ui->EditLineMaxWidth			->value();
	d->LineMinDensityPercent=ui->EditLineMinDensityPercent	->value();
	d->LineMinCluster		=ui->EditLineMinCluster			->value();

}
void EditDotColorMatchingLibraryDialog::on_toolButtonPickup_clicked()
{
	if(ui->toolButtonPickup->isChecked()==true){
		ui->stackedWidget->setCurrentIndex(0);
	}
}

void EditDotColorMatchingLibraryDialog::on_toolButtonInspect_clicked()
{
	if(ui->toolButtonInspect->isChecked()==true){
		ui->stackedWidget->setCurrentIndex(1);
	}
}

void EditDotColorMatchingLibraryDialog::on_ButtonLibNew_clicked()
{
	if(LLib==NULL)
		return;
	LLib->Reset();
	CmdClearDotColorMatchingLibraryPacket	Packet(GetLayersBase());
	Packet.Point=LLib;
	DotColorMatchingBase	*BBase=GetDotColorMatchingBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);
	}
	ShowLibrary(*LLib);
	ui->ButtonLibSave	->setEnabled(false);
	ui->ButtonLibDelete	->setEnabled(false);
}

void EditDotColorMatchingLibraryDialog::on_ButtonLibDelete_clicked()
{
	if(LLib==NULL)
		return;
	if(LLib->GetLibID()<0)
		return;
	QString  msg=LangSolver.GetString(EditDotColorMatchingLibraryDialog_LS,LID_4)/*"Delete OK?"*/;
	int	ret=QMessageBox::question(NULL, LangSolver.GetString(EditDotColorMatchingLibraryDialog_LS,LID_5)/*"Choose"*/
					, msg
					, QMessageBox::Yes , QMessageBox::No, QMessageBox::NoButton);
	if(ret==QMessageBox::Yes){
		CmdDeleteDotColorMatchingLibraryPacket	Packet(GetLayersBase());
		Packet.Point=LLib->GetLibrary();
		DotColorMatchingBase	*BBase=GetDotColorMatchingBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			on_ButtonLibNew_clicked();
			SlotSelectLibFolder(LibFolderID ,/**/"");
		}
	}
}

void EditDotColorMatchingLibraryDialog::on_ButtonLibSaveNew_clicked()
{
	if(LLib==NULL)
		return;
	GetLibraryFromWindow(*LLib);

	if(LLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL, LangSolver.GetString(EditDotColorMatchingLibraryDialog_LS,LID_6)/*"Warning"*/
																, LangSolver.GetString(EditDotColorMatchingLibraryDialog_LS,LID_7)/*"No Library Name"*/
																, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	LLib->SetLibFolderID(LibFolderID);
	CmdInsertDotColorMatchingLibraryPacket	Packet(GetLayersBase());
	Packet.Point=LLib;
	DotColorMatchingBase	*BBase=GetDotColorMatchingBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);		
		ShowLibrary(*LLib);
		ui->ButtonLibSave	->setEnabled(true);
		ui->ButtonLibDelete	->setEnabled(true);
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}

void EditDotColorMatchingLibraryDialog::on_ButtonLibSave_clicked()
{
	if(LLib==NULL)
		return;
	GetLibraryFromWindow(*LLib);
	if(LLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL, LangSolver.GetString(EditDotColorMatchingLibraryDialog_LS,LID_8)/*"Warning"*/
																, LangSolver.GetString(EditDotColorMatchingLibraryDialog_LS,LID_9)/*"No Library Name"*/
																, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	if(LLib->GetLibID()<0){
		LLib->SetLibFolderID(LibFolderID);

		CmdInsertDotColorMatchingLibraryPacket	Packet(GetLayersBase());
		Packet.Point=LLib;
		DotColorMatchingBase	*BBase=GetDotColorMatchingBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			ShowLibrary(*LLib);
			ui->ButtonLibSave	->setEnabled(true);
			ui->ButtonLibDelete	->setEnabled(true);
		}
	}
	else{
		CmdUpdateDotColorMatchingLibraryPacket	Packet(GetLayersBase());
		Packet.Point=LLib;
		DotColorMatchingBase	*BBase=GetDotColorMatchingBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
		}
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}

void EditDotColorMatchingLibraryDialog::on_pushButton_clicked()
{
	close();
}

void EditDotColorMatchingLibraryDialog::on_EditAreaSearchX_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	OnChanging=true;
	ui->doubleSpinBoxAreaSearchX->setValue(TransformPixelToUnit(-1,arg1));
	OnChanging=false;
}


void EditDotColorMatchingLibraryDialog::on_doubleSpinBoxAreaSearchX_valueChanged(double arg1)
{
	if(OnChanging==true){
		return;
	}
	OnChanging=true;
	ui->EditAreaSearchX->setValue(TransformUnitToPixel(-1,arg1));
	OnChanging=false;
}


void EditDotColorMatchingLibraryDialog::on_EditAreaSearchY_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	OnChanging=true;
	ui->doubleSpinBoxAreaSearchY->setValue(TransformPixelToUnit(-1,arg1));
	OnChanging=false;
}


void EditDotColorMatchingLibraryDialog::on_doubleSpinBoxAreaSearchY_valueChanged(double arg1)
{
	if(OnChanging==true){
		return;
	}
	OnChanging=true;
	ui->EditAreaSearchY->setValue(TransformUnitToPixel(-1,arg1));
	OnChanging=false;
}


void EditDotColorMatchingLibraryDialog::on_EditSelfSearch_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	OnChanging=true;
	ui->doubleSpinBoxSelfSearch->setValue(TransformPixelToUnit(-1,arg1));
	OnChanging=false;
}

void EditDotColorMatchingLibraryDialog::on_doubleSpinBoxSelfSearch_valueChanged(double arg1)
{
	if(OnChanging==true){
		return;
	}
	OnChanging=true;
	ui->EditSelfSearch->setValue(TransformUnitToPixel(-1,arg1));
	OnChanging=false;
}

void EditDotColorMatchingLibraryDialog::on_EditOKDotB_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	OnChanging=true;
	ui->doubleSpinBoxOKDotB->setValue(TransformPixelToUnitSquare(-1,arg1));
	OnChanging=false;
}

void EditDotColorMatchingLibraryDialog::on_doubleSpinBoxOKDotB_valueChanged(double arg1)
{
	if(OnChanging==true){
		return;
	}
	OnChanging=true;
	ui->EditOKDotB->setValue(TransformUnitToPixelSquare(-1,arg1));
	OnChanging=false;
}

void EditDotColorMatchingLibraryDialog::on_EditOKDotN_valueChanged(int arg1)
{
	if(OnChanging==true){
		return;
	}
	OnChanging=true;
	ui->doubleSpinBoxOKDotN->setValue(TransformPixelToUnitSquare(-1,arg1));
	OnChanging=false;
}

void EditDotColorMatchingLibraryDialog::on_doubleSpinBoxOKDotN_valueChanged(double arg1)
{
	if(OnChanging==true){
		return;
	}
	OnChanging=true;
	ui->EditOKDotN->setValue(TransformUnitToPixelSquare(-1,arg1));
	OnChanging=false;
}

void EditDotColorMatchingLibraryDialog::on_pushButtonColor_clicked()
{
	if(LLib!=NULL){
		QColor Col=QColorDialog::getColor(LLib->GetLibColor(), nullptr
										, LangSolver.GetString(EditDotColorMatchingLibraryDialog_LS,LID_12)/*"General library color"*/);
		if(Col.isValid()==true){
			LLib->SetLibColor(Col);
		}
	}	
}

void EditDotColorMatchingLibraryDialog::on_toolButtonExplain_clicked()
{
	if(ui->toolButtonExplain->isChecked()==true){
		ui->stackedWidget->setCurrentIndex(2);
	}
}

void EditDotColorMatchingLibraryDialog::on_pushButtonMasterNo_clicked()
{
	MasterNoOriginCode=GetLayersBase()->ShowSelectMasterNoOriginCodeDialog(MasterNoOriginCode);
}

void EditDotColorMatchingLibraryDialog::on_pushButtonSubtractLibID_clicked()
{
	SubtractLibIDDialog	D(GetLayersBase());
	DotColorMatchingLibrary *d=(DotColorMatchingLibrary *)LLib->GetLibrary();
	AlgorithmLibraryListContainer SelectedList;
	for(IntClass *c=d->SubtractLibID.GetFirst();c!=NULL;c=c->GetNext()){
		int	LibID=c->GetValue();
		QString	LibName=GetLayersBase()->GetLibraryName(DefLibTypeDotColorMatchingInspect,LibID);
		AlgorithmLibraryList	*a=new AlgorithmLibraryList(DefLibTypeDotColorMatchingInspect
															,LibID
															,LibName);
		SelectedList.AppendList(a);
	}
	D.SetSelected(SelectedList);
	if(D.exec()==true){
		d->SubtractLibID.RemoveAll();
		for(AlgorithmLibraryList *a=D.SelectedList.GetFirst();a!=NULL;a=a->GetNext()){
			d->SubtractLibID.Add(a->GetLibID());
		}
	}
}


