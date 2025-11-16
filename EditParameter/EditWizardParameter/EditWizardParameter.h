#ifndef EDITWIZARDPARAMETER_H
#define EDITWIZARDPARAMETER_H

#include <QMainWindow>
#include "ui_EditWizardParameter.h"
#include "XServiceForLayers.h"
#include "XParamGlobal.h"

class EditWizardParameter : public QMainWindow,public ServiceForLayers
{
	Q_OBJECT

	QString	ParamGlobalFileName;
public:
	EditWizardParameter(LayersBase *base
					,const QString &ParamGlobalFileName
					,ParamComm	*ParamCommData
					,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~EditWizardParameter();

private slots:
    void on_pushButtonSearchFileName_clicked();
    void on_pushButtonSaveNew_clicked();
    void on_pushButtonUpdate_clicked();
    void on_pushButtonClose_clicked();
    void on_pushButtonNext1_clicked();
    void on_radioButtonMono_clicked();
    void on_radioButtonColor_clicked();
    void on_pushButtonPrevious2_clicked();
    void on_pushButtonNext2_clicked();
    void on_pushButtonMMToPixel_clicked();
    void on_pushButtonPixelToMM_clicked();
    void on_pushButtonPrevious3_clicked();
    void on_pushButtonNext3_clicked();
    void on_pushButtonPrevious4_clicked();
    void on_pushButtonNext4_clicked();
    void on_pushButtonLocalDatabase_FileName_clicked();
    void on_pushButtonDatabaseDDL_FileName_clicked();
    void on_pushButtonPrevious5_clicked();
    void on_pushButtonNext5_clicked();
    void on_pushButtonPrevious6_clicked();
    void on_pushButtonNext6_clicked();
    void on_pushButtonPrevious7_clicked();
    void on_pushButtonNext7_clicked();
    void on_pushButtonCameraSetting_FileName_clicked();
    void on_pushButtonCameraDLL_FileName_clicked();
    void on_pushButtonCameraAllocation_clicked();
    void on_pushButtonCameraDLL_FileName2_clicked();
    void on_pushButtonCameraAllocation2_clicked();
    void on_pushButtonPrevious8_clicked();
    void on_pushButtonNext8_clicked();
    void on_pushButtonResultDLLFileName_clicked();
    void on_pushButtonPrevious9_clicked();
    void on_pushButtonNext9_clicked();
    void on_pushButtonPrevious10_clicked();
    void on_pushButtonNext10_clicked();
    void on_pushButtonFilterDefFile_clicked();
    void on_comboBoxPhaseForFIlter_currentIndexChanged(int index);
    void on_tableWidgetFilterListInPage_clicked(const QModelIndex &index);
    void on_tableWidgetFilterListInPage_doubleClicked(const QModelIndex &index);
    void on_pushButtonPrevious11_clicked();
    void on_pushButtonNext11_clicked();
    void on_checkBoxMaster_clicked();
    void on_pushButtonPrevious12_clicked();
    void on_pushButtonNext12_clicked();
    void on_comboBoxOutlineOffsetMachine_currentIndexChanged(int index);
    void on_comboBoxOutlineOffsetPhase_currentIndexChanged(int index);
    void on_pushButtonOTileXutlineOffset_clicked();
    void on_pushButtonOutlineOffsetTileY_clicked();
    void on_pushButtonPrevious13_clicked();
    void on_pushButtonNext13_clicked();
    void on_pushButtonLightSettingFileName_clicked();
    void on_pushButtonLightDLLFileName_clicked();
    void on_pushButtonLightDLLFileName2_clicked();
    void on_pushButtonPrevious14_clicked();
    void on_pushButtonNext14_clicked();
    void on_pushButtonSyncGUIFileName_clicked();
    void on_pushButtonPrevious15_clicked();
    void on_pushButtonNext15_clicked();
    void on_pushButtonPrevious16_clicked();
    void on_pushButtonNext16_clicked();
    void on_pushButtonGUIFileName_clicked();
    void on_pushButtonEditParameter_clicked();
    void on_pushButtonEditAlgorithmParam_clicked();
    void on_pushButtonEditGUIParam_clicked();
    void on_pushButtonEditResultParam_clicked();
    void on_pushButtonEditCameraParam_clicked();
    void on_pushButtonEditLightParam_clicked();
    void on_pushButtonPrevious17_clicked();
    void on_pushButtonNext17_clicked();

    void on_stackedWidget_currentChanged(int arg1);
    void on_pushButtonCalcMemory_clicked();
    void on_spinBoxPhaseNumb_valueChanged(int arg1);
    void on_spinBoxPageNumb_valueChanged(int arg1);
    void on_spinBoxLayerNumb_valueChanged(int arg1);
    void on_spinBoxDotPerLine_valueChanged(int arg1);
    void on_spinBoxMaxLines_valueChanged(int arg1);
    void on_checkBoxAllocateMasterBuff_clicked();
    void on_checkBoxAllocateTargetBuff_clicked();
    void on_checkBoxAllocRawTargetBuffForNGImage_clicked();
    void on_checkBoxAllocCamTargetBuffer_clicked();
    void on_checkBoxAllocViewTargetBuffer_clicked();

private:
	Ui::EditWizardParameterClass ui;

	ParamGlobal		CurrentParam;

	void ShowData(ParamGlobal &Param);
	void ShoeFilterList(void);
	void ShowMasterSlave(void);
	void ShowOutlineOffset(void);
	void ShowSyncGUI(void);
	void ShowImageDirection(void);
};

#endif // EDITWIZARDPARAMETER_H
