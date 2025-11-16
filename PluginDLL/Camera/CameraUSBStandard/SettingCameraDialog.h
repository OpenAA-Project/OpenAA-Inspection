#ifndef SETTINGCAMERADIALOG_H
#define SETTINGCAMERADIALOG_H

#include <QDialog>
#include <QCheckBox>
#include <QSlider>
#include <QComboBox>
#include "CameraUSBStandard.h"
#include "XServiceForLayers.h"
#include "LibWMFCamera.h"

namespace Ui {
class SettingCameraDialog;
}

class SettingCameraDialog : public QDialog, public ServiceForLayers
{
    Q_OBJECT

	struct StructMediaType MediaDim[100];
	int					MediaCount;
	StructUSBCamInfo	CamResolutionDim[100];
	int					StructUSBCamInfoCount;	
	int					CurrentXLen,CurrentYLen;

	struct StructMediaType	PrevType;

	PropertyItem	Brightness;
	PropertyItem	Contrast;
	PropertyItem	Color;
	PropertyItem	Vivid;
	PropertyItem	Vividation;
	PropertyItem	Gamma;
	PropertyItem	WhiteBalance;
	PropertyItem	Reflection;
	PropertyItem	Gain;
	PropertyItem	Zoom;
	PropertyItem	Focus;
	PropertyItem	Exposure;
	PropertyItem	Iris;
	PropertyItem	Pan;
	PropertyItem	Tilt;
	PropertyItem	Rotation;
	PropertyItemPowerlineFrequency	PowerlineFrequency;

	PropertyItem	SavedBrightness;
	PropertyItem	SavedContrast;
	PropertyItem	SavedColor;
	PropertyItem	SavedVivid;
	PropertyItem	SavedVividation;
	PropertyItem	SavedGamma;
	PropertyItem	SavedWhiteBalance;
	PropertyItem	SavedReflection;
	PropertyItem	SavedGain;
	PropertyItem	SavedZoom;
	PropertyItem	SavedFocus;
	PropertyItem	SavedExposure;
	PropertyItem	SavedIris;
	PropertyItem	SavedPan;
	PropertyItem	SavedTilt;
	PropertyItem	SavedRotation;
	PropertyItemPowerlineFrequency	SavedPowerlineFrequency;

	LibWMFCamera	*Camera;
public:
    explicit SettingCameraDialog(LayersBase *Base ,LibWMFCamera	*C,QWidget *parent = 0);
    ~SettingCameraDialog();

private slots:
    void on_spinBoxTotalCamCount_valueChanged(int arg1);
    void on_comboBoxImageSize_currentIndexChanged(int index);
    void on_horizontalSliderBrightness_valueChanged(int value);
    void on_horizontalSliderContrast_valueChanged(int value);
    void on_horizontalSliderColor_valueChanged(int value);
    void on_horizontalSliderVivid_valueChanged(int value);
    void on_horizontalSliderVividation_valueChanged(int value);
    void on_horizontalSliderGamma_valueChanged(int value);
    void on_horizontalSliderWhiteBalance_valueChanged(int value);
    void on_horizontalSliderReflection_valueChanged(int value);
    void on_horizontalSliderGain_valueChanged(int value);
    void on_horizontalSliderZoom_valueChanged(int value);
    void on_horizontalSliderFocus_valueChanged(int value);
    void on_horizontalSliderExposure_valueChanged(int value);
    void on_horizontalSliderIris_valueChanged(int value);
    void on_horizontalSliderPan_valueChanged(int value);
    void on_horizontalSliderTilt_valueChanged(int value);
    void on_horizontalSliderRotation_valueChanged(int value);
    void on_checkBoxAdjustLow_clicked();
    void on_pushButtonDefault_clicked();
    void on_checkBoxBrightness_clicked();
    void on_checkBoxContrast_clicked();
    void on_checkBoxColor_clicked();
    void on_checkBoxVivid_clicked();
    void on_checkBoxVividation_clicked();
    void on_checkBoxGamma_clicked();
    void on_checkBoxWhiteBalance_clicked();
    void on_checkBoxReflection_clicked();
    void on_checkBoxGain_clicked();
    void on_comboBoxPowerFrequency_currentIndexChanged(int index);
    void on_checkBoxZoom_clicked();
    void on_checkBoxFocus_clicked();
    void on_checkBoxExposure_clicked();
    void on_checkBoxIris_clicked();
    void on_checkBoxPan_clicked();
    void on_checkBoxTilt_clicked();
    void on_checkBoxRotation_clicked();
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();
    void on_pushButtonSave_clicked();
    void on_pushButtonLoad_clicked();
    void on_pushButtonResetSettingEachCamera_clicked();

private:
    Ui::SettingCameraDialog *ui;

	void	ReflectDataIntoWindow(void);
	int		OnSetting;

	void ShowInfo(void);
	void LoadDataFromWindow(void);
	void	SetItemValue(PropertyItem &Prop,QSlider *s);
	void	SetItemValue(PropertyItem &Prop,QSlider *s ,QCheckBox *c);
	void	SetItemValue(PropertyItemPowerlineFrequency &Prop,QComboBox *s);

	int	GetMediaIndexFromDim(int DimIndex);
};

#endif // SETTINGCAMERADIALOG_H
