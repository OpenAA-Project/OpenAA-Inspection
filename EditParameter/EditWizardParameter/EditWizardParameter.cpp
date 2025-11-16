#include "EditWizardParameter.h"
#include "XDataInLayer.h"
#include <QFile>
#include <QFileDialog>
#include "XDatabase.h"
#include "XGeneralFunc.h"
#include "XDatabaseLoader.h"
#include "XLanguageClass.h"
#include "CameraAllocationDialog.h"
#include "FilterInPhaseForm.h"

extern	int	LanguageCode;
extern	LangSolverNew	LangSolverGUILib;

EditWizardParameter::EditWizardParameter(LayersBase *base
					,const QString &_ParamGlobalFileName
					,ParamComm	*ParamCommData
					,QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
	,ServiceForLayers(base)
	,CurrentParam(base)
{
	ui.setupUi(this);

	ParamGlobalFileName=_ParamGlobalFileName;
	ui.progressBar	->setMaximum(16);
	ui.stackedWidget->setCurrentIndex(0);

	if(ParamGlobalFileName.isEmpty()==true)
		return;
	if(CurrentParam.LoadFromFile(ParamGlobalFileName)==true){
		ui.lineEditFileName	->setText(ParamGlobalFileName);
		ShowData(CurrentParam);
	}
	ShowData(CurrentParam);
}

EditWizardParameter::~EditWizardParameter()
{

}

void EditWizardParameter::ShowData(ParamGlobal &Param)
{
	ui.doubleSpinBoxTransformUnitPerPixel	->setValue(Param.TransformUnitPerPixel);
	ui.spinBoxSmallNumberFigure				->setValue(Param.SmallNumberFigure);

	ui.radioButtonMono	->setChecked((Param.GetLayerNumb(0)!=3)?true:false);
	ui.radioButtonColor	->setChecked((Param.GetLayerNumb(0)>=3)?true:false);
	ui.spinBoxLayerNumb						->setValue(Param.LayerNumb);

	ui.spinBoxDotPerLine					->setValue(Param.DotPerLine);
	ui.spinBoxMaxLines						->setValue(Param.MaxLines);
	on_pushButtonPixelToMM_clicked();

	ui.spinBoxPhaseNumb						->setValue(Param.PhaseNumb);
	ui.spinBoxPageNumb						->setValue(Param.PageNumb);
	ui.spinBoxTotalCameraNumb				->setValue(Param.TotalCameraNumb);

	ui.lineEditLocalDatabase_HostName		->setText(Param.LocalDatabase_HostName);
	ui.lineEditLocalDatabase_FileName		->setText(Param.LocalDatabase_FileName);
	ui.lineEditDatabaseDDL_FileName			->setText(Param.DatabaseDDL_FileName);
	ui.spinBoxLocalDatabase_Port			->setValue(Param.LocalDatabase_Port);

	ui.lineEditImageFilePath				->setText(Param.ImageFilePath);

	ui.lineEditSequence_FileName			->setText(Param.Sequence_FileName);
	ui.lineEditIODLL_FileName				->setText(Param.IODLL_FileName);
	ui.lineEditIODefine_FileName			->setText(Param.IODefine_FileName);
	ui.lineEditIOSomething					->setText(Param.IOSomething);

	ui.lineEditCameraSetting_FileName		->setText(Param.CameraSetting_FileName);
	ui.lineEditCameraDLL_FileName			->setText(Param.CameraDLL_FileName);
	ui.lineEditCameraAllocation				->setText(Param.CameraAllocation);
	ui.lineEditCameraDLL_FileName2			->setText(Param.CameraDLL_FileName2);
	ui.lineEditCameraAllocation2			->setText(Param.CameraAllocation2);

	ui.lineEditResultDLLFileName			->setText(Param.ResultDLLFileName);
	ui.spinBoxNGCacheNumb					->setValue(Param.NGCacheNumb);
	ui.spinBoxMaxNGCountsPerCam				->setValue(Param.MaxNGCountsPerCam);
	ui.spinBoxMaxNGImageNumbPerPage			->setValue(Param.MaxNGImageNumbPerPage);
	ui.spinBoxMaxInspectMilisec				->setValue(Param.MaxInspectMilisec);
	ui.checkBoxOutputResult					->setChecked(Param.OutputResult);

	ui.checkBoxAllocateMasterBuff			->setChecked(Param.AllocateMasterBuff);
	ui.checkBoxAllocateTargetBuff			->setChecked(Param.AllocateTargetBuff);
	ui.checkBoxAllocRawTargetBuffForNGImage	->setChecked(Param.AllocRawTargetBuffForNGImage);
	ui.checkBoxAllocCamTargetBuffer			->setChecked(Param.AllocCamTargetBuffer);
	ui.checkBoxAllocViewTargetBuffer		->setChecked(Param.AllocViewTargetBuffer);
	ui.spinBoxSwapOutSizeMegaByte			->setValue(Param.SwapOutSizeMegaByte);

    ui.lineEditFilterDefFile				->setText(Param.FilterDefFile);
	ShoeFilterList();

	ui.spinBoxMaxWaitingCommMilisec			->setValue(Param.MaxWaitingCommMilisec);
	ShowMasterSlave();
	ShowOutlineOffset();

	ui.lineEditLightSettingFileName			->setText(Param.LightSettingFileName);
	ui.checkBoxInitialLightON				->setChecked(Param.InitialLightON);
	ui.lineEditLightDLLFileName				->setText(Param.LightDLLFileName);
	ui.lineEditLightParamStr				->setText(Param.LightParamStr);
	ui.lineEditLightDLLFileName2			->setText(Param.LightDLLFileName2);
	ui.lineEditLightParamStr2				->setText(Param.LightParamStr2);

	ui.lineEditSyncGUIFileName				->setText(Param.SyncGUIFileName);
	ui.spinBoxSyncGUIPort					->setValue(Param.SyncGUIPort);
	ShowSyncGUI();

	ShowImageDirection();
}

void EditWizardParameter::ShoeFilterList(void)
{
}
void EditWizardParameter::ShowMasterSlave(void)
{
}
void EditWizardParameter::ShowOutlineOffset(void)
{
}
void EditWizardParameter::ShowSyncGUI(void)
{
}
void EditWizardParameter::ShowImageDirection(void)
{
}

void EditWizardParameter::on_spinBoxPhaseNumb_valueChanged(int arg1)
{
	int	iPhaseNumb=ui.spinBoxPhaseNumb->value();

	if(ui.comboBoxPhaseForFIlter->count()<iPhaseNumb){
		for(int i=ui.comboBoxPhaseForFIlter->count();i<iPhaseNumb;i++){
			ui.comboBoxPhaseForFIlter->addItem(QString(/**/"Phase ")+QString::number(i));
		}
	}
	else if(ui.comboBoxPhaseForFIlter->count()>iPhaseNumb){
		while(ui.comboBoxPhaseForFIlter->count()>iPhaseNumb){
			int	n=ui.comboBoxPhaseForFIlter->count()-1;
			ui.comboBoxPhaseForFIlter->removeItem(n);
		}
	}
	if(ui.comboBoxOutlineOffsetPhase->count()<iPhaseNumb){
		for(int i=ui.comboBoxOutlineOffsetPhase->count();i<iPhaseNumb;i++){
			ui.comboBoxOutlineOffsetPhase->addItem(QString(/**/"Phase ")+QString::number(i));
		}
	}
	else if(ui.comboBoxOutlineOffsetPhase->count()>iPhaseNumb){
		while(ui.comboBoxOutlineOffsetPhase->count()>iPhaseNumb){
			int	n=ui.comboBoxOutlineOffsetPhase->count()-1;
			ui.comboBoxOutlineOffsetPhase->removeItem(n);
		}
	}
	on_pushButtonCalcMemory_clicked();
}

void EditWizardParameter::on_pushButtonSearchFileName_clicked()
{
	QString	FileName=QFileDialog::getOpenFileName (0
											, "Load GlobalParam file"
											, QString()
											, /**/"GlobalParam(Global.dat);;dat(*.dat);;All file(*.*)");
	if(FileName.isEmpty()==true)
		return;
	ParamGlobalFileName	=FileName;
	if(CurrentParam.LoadFromFile(ParamGlobalFileName)==true){
		ui.lineEditFileName	->setText(ParamGlobalFileName);
		ShowData(CurrentParam);
	}
}

void EditWizardParameter::on_pushButtonSaveNew_clicked()
{

}

void EditWizardParameter::on_pushButtonUpdate_clicked()
{

}

void EditWizardParameter::on_pushButtonClose_clicked()
{
	close();
}

void EditWizardParameter::on_pushButtonNext1_clicked()
{
	ui.stackedWidget	->setCurrentIndex(1);
}

void EditWizardParameter::on_radioButtonMono_clicked()
{

}

void EditWizardParameter::on_radioButtonColor_clicked()
{

}

void EditWizardParameter::on_pushButtonPrevious2_clicked()
{
	ui.stackedWidget	->setCurrentIndex(0);
}

void EditWizardParameter::on_pushButtonNext2_clicked()
{
	ui.stackedWidget	->setCurrentIndex(2);
}

void EditWizardParameter::on_pushButtonMMToPixel_clicked()
{

}

void EditWizardParameter::on_pushButtonPixelToMM_clicked()
{

}

void EditWizardParameter::on_pushButtonPrevious3_clicked()
{
	ui.stackedWidget	->setCurrentIndex(1);
}

void EditWizardParameter::on_pushButtonNext3_clicked()
{
	ui.stackedWidget	->setCurrentIndex(3);
}

void EditWizardParameter::on_pushButtonPrevious4_clicked()
{
	ui.stackedWidget	->setCurrentIndex(2);
}

void EditWizardParameter::on_pushButtonNext4_clicked()
{
	ui.stackedWidget	->setCurrentIndex(4);
}

void EditWizardParameter::on_pushButtonLocalDatabase_FileName_clicked()
{

}

void EditWizardParameter::on_pushButtonDatabaseDDL_FileName_clicked()
{

}

void EditWizardParameter::on_pushButtonPrevious5_clicked()
{
	ui.stackedWidget	->setCurrentIndex(3);
}

void EditWizardParameter::on_pushButtonNext5_clicked()
{
	ui.stackedWidget	->setCurrentIndex(5);
}

void EditWizardParameter::on_pushButtonPrevious6_clicked()
{
	ui.stackedWidget	->setCurrentIndex(4);
}

void EditWizardParameter::on_pushButtonNext6_clicked()
{
	ui.stackedWidget	->setCurrentIndex(6);
}

void EditWizardParameter::on_pushButtonPrevious7_clicked()
{
	ui.stackedWidget	->setCurrentIndex(5);
}

void EditWizardParameter::on_pushButtonNext7_clicked()
{
	ui.stackedWidget	->setCurrentIndex(7);
}

void EditWizardParameter::on_pushButtonCameraSetting_FileName_clicked()
{

}

void EditWizardParameter::on_pushButtonCameraDLL_FileName_clicked()
{

}

void EditWizardParameter::on_pushButtonCameraAllocation_clicked()
{

}

void EditWizardParameter::on_pushButtonCameraDLL_FileName2_clicked()
{

}

void EditWizardParameter::on_pushButtonCameraAllocation2_clicked()
{

}

void EditWizardParameter::on_pushButtonPrevious8_clicked()
{
	ui.stackedWidget	->setCurrentIndex(6);
}

void EditWizardParameter::on_pushButtonNext8_clicked()
{
	ui.stackedWidget	->setCurrentIndex(8);
}

void EditWizardParameter::on_pushButtonResultDLLFileName_clicked()
{

}

void EditWizardParameter::on_pushButtonPrevious9_clicked()
{
	ui.stackedWidget	->setCurrentIndex(7);
}

void EditWizardParameter::on_pushButtonNext9_clicked()
{
	ui.stackedWidget	->setCurrentIndex(9);
}

void EditWizardParameter::on_pushButtonCalcMemory_clicked()
{

}

void EditWizardParameter::on_pushButtonPrevious10_clicked()
{
	ui.stackedWidget	->setCurrentIndex(8);
}

void EditWizardParameter::on_pushButtonNext10_clicked()
{
	ui.stackedWidget	->setCurrentIndex(10);
}

void EditWizardParameter::on_pushButtonFilterDefFile_clicked()
{

}

void EditWizardParameter::on_comboBoxPhaseForFIlter_currentIndexChanged(int index)
{

}

void EditWizardParameter::on_tableWidgetFilterListInPage_clicked(const QModelIndex &index)
{

}

void EditWizardParameter::on_tableWidgetFilterListInPage_doubleClicked(const QModelIndex &index)
{

}

void EditWizardParameter::on_pushButtonPrevious11_clicked()
{
	ui.stackedWidget	->setCurrentIndex(9);
}

void EditWizardParameter::on_pushButtonNext11_clicked()
{
	ui.stackedWidget	->setCurrentIndex(11);
}

void EditWizardParameter::on_checkBoxMaster_clicked()
{

}

void EditWizardParameter::on_pushButtonPrevious12_clicked()
{
	ui.stackedWidget	->setCurrentIndex(10);
}

void EditWizardParameter::on_pushButtonNext12_clicked()
{
	ui.stackedWidget	->setCurrentIndex(12);
}

void EditWizardParameter::on_comboBoxOutlineOffsetMachine_currentIndexChanged(int index)
{

}

void EditWizardParameter::on_comboBoxOutlineOffsetPhase_currentIndexChanged(int index)
{

}

void EditWizardParameter::on_pushButtonOTileXutlineOffset_clicked()
{

}

void EditWizardParameter::on_pushButtonOutlineOffsetTileY_clicked()
{

}

void EditWizardParameter::on_pushButtonPrevious13_clicked()
{
	ui.stackedWidget	->setCurrentIndex(11);
}

void EditWizardParameter::on_pushButtonNext13_clicked()
{
	ui.stackedWidget	->setCurrentIndex(13);
}

void EditWizardParameter::on_pushButtonLightSettingFileName_clicked()
{

}

void EditWizardParameter::on_pushButtonLightDLLFileName_clicked()
{

}

void EditWizardParameter::on_pushButtonLightDLLFileName2_clicked()
{

}

void EditWizardParameter::on_pushButtonPrevious14_clicked()
{
	ui.stackedWidget	->setCurrentIndex(12);
}

void EditWizardParameter::on_pushButtonNext14_clicked()
{
	ui.stackedWidget	->setCurrentIndex(14);
}

void EditWizardParameter::on_pushButtonSyncGUIFileName_clicked()
{

}

void EditWizardParameter::on_pushButtonPrevious15_clicked()
{
	ui.stackedWidget	->setCurrentIndex(13);
}

void EditWizardParameter::on_pushButtonNext15_clicked()
{
	ui.stackedWidget	->setCurrentIndex(15);
}

void EditWizardParameter::on_pushButtonPrevious16_clicked()
{
	ui.stackedWidget	->setCurrentIndex(14);
}

void EditWizardParameter::on_pushButtonNext16_clicked()
{
	ui.stackedWidget	->setCurrentIndex(16);
}

void EditWizardParameter::on_pushButtonGUIFileName_clicked()
{

}

void EditWizardParameter::on_pushButtonEditParameter_clicked()
{

}

void EditWizardParameter::on_pushButtonEditAlgorithmParam_clicked()
{

}

void EditWizardParameter::on_pushButtonEditGUIParam_clicked()
{

}

void EditWizardParameter::on_pushButtonEditResultParam_clicked()
{

}

void EditWizardParameter::on_pushButtonEditCameraParam_clicked()
{

}

void EditWizardParameter::on_pushButtonEditLightParam_clicked()
{

}

void EditWizardParameter::on_pushButtonPrevious17_clicked()
{
	ui.stackedWidget	->setCurrentIndex(15);
}

void EditWizardParameter::on_pushButtonNext17_clicked()
{

}

void EditWizardParameter::on_stackedWidget_currentChanged(int arg1)
{
	int	n=ui.stackedWidget->currentIndex();
	ui.progressBar	->setValue(n);
}

void EditWizardParameter::on_spinBoxPageNumb_valueChanged(int arg1)
{
	on_pushButtonCalcMemory_clicked();
}

void EditWizardParameter::on_spinBoxLayerNumb_valueChanged(int arg1)
{
	on_pushButtonCalcMemory_clicked();
}

void EditWizardParameter::on_spinBoxDotPerLine_valueChanged(int arg1)
{
	on_pushButtonCalcMemory_clicked();
}

void EditWizardParameter::on_spinBoxMaxLines_valueChanged(int arg1)
{
	on_pushButtonCalcMemory_clicked();
}

void EditWizardParameter::on_checkBoxAllocateMasterBuff_clicked()
{
	on_pushButtonCalcMemory_clicked();
}

void EditWizardParameter::on_checkBoxAllocateTargetBuff_clicked()
{
	on_pushButtonCalcMemory_clicked();
}

void EditWizardParameter::on_checkBoxAllocRawTargetBuffForNGImage_clicked()
{
	on_pushButtonCalcMemory_clicked();
}

void EditWizardParameter::on_checkBoxAllocCamTargetBuffer_clicked()
{
	on_pushButtonCalcMemory_clicked();
}

void EditWizardParameter::on_checkBoxAllocViewTargetBuffer_clicked()
{
	on_pushButtonCalcMemory_clicked();
}
