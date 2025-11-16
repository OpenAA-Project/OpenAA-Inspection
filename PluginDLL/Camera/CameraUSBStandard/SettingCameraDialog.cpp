#include "SettingCameraDialog.h"
#include "ui_SettingCameraDialog.h"
#include "XGUIFormBase.h"
#include <QFileDialog>
#include <QMessageBox>
#include "swap.h"

SettingCameraDialog::SettingCameraDialog(LayersBase *Base ,LibWMFCamera	*C ,QWidget *parent) :
    QDialog(NULL)
 	,ServiceForLayers(Base)
	,Camera(C)
	,ui(new Ui::SettingCameraDialog)
{
    ui->setupUi(this);

	OnSetting=0;
	MediaCount=Camera->EnumMediaType(MediaDim ,100);
	Camera->GetMediaType(PrevType);

	CurrentXLen=GetDotPerLine(0);
	CurrentYLen=GetMaxLines(0);

	for(int i=0;i<MediaCount;i++){
		CamResolutionDim[i].CamViewSizeX	=MediaDim[i].Width;
		CamResolutionDim[i].CamViewSizeY	=MediaDim[i].Height;
		CamResolutionDim[i].CamViewFPS	=MediaDim[i].FPS;
	}
	StructUSBCamInfoCount=MediaCount;
	for(int i=0;i<StructUSBCamInfoCount;i++){
		for(int j=i+1;j<StructUSBCamInfoCount;){
			if(CamResolutionDim[i].CamViewSizeX	==CamResolutionDim[j].CamViewSizeX
			&& CamResolutionDim[i].CamViewSizeY	==CamResolutionDim[j].CamViewSizeY){
				if(CamResolutionDim[i].CamViewFPS<CamResolutionDim[j].CamViewFPS){
					swap(CamResolutionDim[i].CamViewFPS,CamResolutionDim[j].CamViewFPS);
				}
				memmove(&CamResolutionDim[j],&CamResolutionDim[j+1],(StructUSBCamInfoCount-j-1)*sizeof(CamResolutionDim[0]));
				StructUSBCamInfoCount--;
			}
			else{
				j++;
			}
		}
	}

	Brightness		=*Camera->GetBrightness		();
	Contrast		=*Camera->GetContrast		();
	Color			=*Camera->GetColor			();
	Vivid			=*Camera->GetVivid			();
	Vividation		=*Camera->GetVividation		();
	Gamma			=*Camera->GetGamma			();
	WhiteBalance	=*Camera->GetWhiteBalance	();
	Reflection		=*Camera->GetReflection		();
	Gain			=*Camera->GetGain			();
	Zoom			=*Camera->GetZoom			();
	Focus			=*Camera->GetFocus			();
	Exposure		=*Camera->GetExposure		();
	Iris			=*Camera->GetIris			();
	Pan				=*Camera->GetPan			();
	Tilt			=*Camera->GetTilt			();
	Rotation		=*Camera->GetRotation		();
	PowerlineFrequency	=*Camera->GetPowerlineFrequency();

	SavedBrightness		=Brightness		;
	SavedContrast		=Contrast		;
	SavedColor			=Color			;
	SavedVivid			=Vivid			;
	SavedVividation		=Vividation		;
	SavedGamma			=Gamma			;
	SavedWhiteBalance	=WhiteBalance	;
	SavedReflection		=Reflection		;
	SavedGain			=Gain			;
	SavedZoom			=Zoom			;
	SavedFocus			=Focus			;
	SavedExposure		=Exposure		;
	SavedIris			=Iris			;
	SavedPan			=Pan			;
	SavedTilt			=Tilt			;
	SavedRotation		=Rotation		;
	SavedPowerlineFrequency	=PowerlineFrequency;

	ui->lineEditCamDevice->setText(Camera->GetDeviceName());

	ui->spinBoxTotalCamCount->setValue(Camera->GetDeviceNo());
	on_spinBoxTotalCamCount_valueChanged(Camera->GetDeviceNo());

	ShowInfo();

	on_checkBoxBrightness_clicked	();
	on_checkBoxContrast_clicked		();
	on_checkBoxColor_clicked		();
	on_checkBoxVivid_clicked		();
	on_checkBoxVividation_clicked	();
	on_checkBoxGamma_clicked		();
	on_checkBoxWhiteBalance_clicked	();
	on_checkBoxReflection_clicked	();
	on_checkBoxGain_clicked			();
	on_checkBoxZoom_clicked			();
	on_checkBoxFocus_clicked		();
	on_checkBoxExposure_clicked		();
	on_checkBoxIris_clicked			();
	on_checkBoxPan_clicked			();
	on_checkBoxTilt_clicked			();
	on_checkBoxRotation_clicked		();

	ui->tabWidget->removeTab(2);
	ui->tabWidget->setCurrentIndex(0);

	ReflectDataIntoWindow();
}

SettingCameraDialog::~SettingCameraDialog()
{
    delete ui;
}

void SettingCameraDialog::on_spinBoxTotalCamCount_valueChanged(int arg1)
{
	//int	CamCount=ui->spinBoxTotalCamCount->value();
	//for(int i=0;i<CamCount;i++){
	//	ui->comboBoxCurrentCamNo->addItem(QString("Camera-")+QString::number(i+1));
	//}
}

void	SetRange(QSlider *SBar ,QCheckBox *CheckAuto ,PropertyItem &Item)
{
	if(Item.CapsFlags==1){
		SBar->setEnabled(false);
		CheckAuto->setChecked(Item.ModeAuto);
	}
	else{
		SBar->setEnabled(true);
		CheckAuto->setChecked(false);
	}
	SBar->setMinimum(Item.MinValue);
	SBar->setMaximum(Item.MaxValue);
	SBar->setSingleStep(Item.Step);
}

void SettingCameraDialog::ShowInfo(void)
{
	SetRange(ui->horizontalSliderBrightness		,ui->checkBoxBrightness		,Brightness	);
	SetRange(ui->horizontalSliderContrast		,ui->checkBoxContrast		,Contrast	);
	SetRange(ui->horizontalSliderColor			,ui->checkBoxColor			,Color		);
	SetRange(ui->horizontalSliderVivid			,ui->checkBoxVivid			,Vivid		);
	SetRange(ui->horizontalSliderVividation		,ui->checkBoxVividation		,Vividation	);
	SetRange(ui->horizontalSliderGamma			,ui->checkBoxGamma			,Gamma		);
	SetRange(ui->horizontalSliderWhiteBalance	,ui->checkBoxWhiteBalance	,WhiteBalance);
	SetRange(ui->horizontalSliderReflection		,ui->checkBoxReflection		,Reflection	);
	SetRange(ui->horizontalSliderGain			,ui->checkBoxGain			,Gain		);
	SetRange(ui->horizontalSliderZoom			,ui->checkBoxZoom			,Zoom		);
	SetRange(ui->horizontalSliderFocus			,ui->checkBoxFocus			,Focus		);
	SetRange(ui->horizontalSliderExposure		,ui->checkBoxExposure		,Exposure	);
	SetRange(ui->horizontalSliderIris			,ui->checkBoxIris			,Iris		);
	SetRange(ui->horizontalSliderPan			,ui->checkBoxPan			,Pan			);
	SetRange(ui->horizontalSliderTilt			,ui->checkBoxTilt			,Tilt		);
	SetRange(ui->horizontalSliderRotation		,ui->checkBoxRotation		,Rotation	);
}

void	SettingCameraDialog::ReflectDataIntoWindow(void)
{
	OnSetting++;
	ui->comboBoxImageSize->clear();

	for(int i=0;i<StructUSBCamInfoCount;i++){
		ui->comboBoxImageSize->addItem(  QString("幅:")
										+QString::number(CamResolutionDim[i].CamViewSizeX)
										+QString("- 高さ:")
										+QString::number(CamResolutionDim[i].CamViewSizeY)
										+QString("  FPS")
										+QString::number(CamResolutionDim[i].CamViewFPS));
	}
	int	XLen=GetDotPerLine(0);
	int	YLen=GetMaxLines(0);
	for(int i=0;i<StructUSBCamInfoCount;i++){
		if(CamResolutionDim[i].CamViewSizeX==XLen
		&& CamResolutionDim[i].CamViewSizeY==YLen){
			ui->comboBoxImageSize->setCurrentIndex(i);
		}
	}
	//struct StructMediaType	CType;
	//Camera->GetMediaType(CType);
	//ui->comboBoxImageSize->setCurrentIndex(CType.Index);

	ui->horizontalSliderBrightness	->setValue(Brightness	.CurrentValue*Brightness	.MaxValue);
	ui->horizontalSliderContrast	->setValue(Contrast		.CurrentValue*Contrast		.MaxValue);
	ui->horizontalSliderColor		->setValue(Color		.CurrentValue*Color			.MaxValue);
	ui->horizontalSliderVivid		->setValue(Vivid		.CurrentValue*Vivid			.MaxValue);
	ui->horizontalSliderVividation	->setValue(Vividation	.CurrentValue*Vividation	.MaxValue);
	ui->horizontalSliderGamma		->setValue(Gamma		.CurrentValue*Gamma			.MaxValue);
	ui->horizontalSliderWhiteBalance->setValue(WhiteBalance	.CurrentValue*WhiteBalance	.MaxValue);
	ui->horizontalSliderReflection	->setValue(Reflection	.CurrentValue*Reflection	.MaxValue);
	ui->horizontalSliderGain		->setValue(Gain			.CurrentValue*Gain			.MaxValue);
	ui->horizontalSliderZoom		->setValue(Zoom			.CurrentValue*Zoom			.MaxValue);
	ui->horizontalSliderFocus		->setValue(Focus		.CurrentValue*Focus			.MaxValue);
	ui->horizontalSliderExposure	->setValue(Exposure		.CurrentValue*Exposure		.MaxValue);
	ui->horizontalSliderIris		->setValue(Iris			.CurrentValue*Iris			.MaxValue);
	ui->horizontalSliderPan			->setValue(Pan			.CurrentValue*Pan			.MaxValue);
	ui->horizontalSliderTilt		->setValue(Tilt			.CurrentValue*Tilt			.MaxValue);
	ui->horizontalSliderRotation	->setValue(Rotation		.CurrentValue*Rotation		.MaxValue);

	ui->checkBoxBrightness	->setChecked(	Brightness	.ModeAuto);
	ui->checkBoxContrast	->setChecked(	Contrast	.ModeAuto);
	ui->checkBoxColor		->setChecked(	Color		.ModeAuto);
	ui->checkBoxVivid		->setChecked(	Vivid		.ModeAuto);
	ui->checkBoxVividation	->setChecked(	Vividation	.ModeAuto);
	ui->checkBoxGamma		->setChecked(	Gamma		.ModeAuto);
	ui->checkBoxWhiteBalance->setChecked(	WhiteBalance.ModeAuto);
	ui->checkBoxReflection	->setChecked(	Reflection	.ModeAuto);
	ui->checkBoxGain		->setChecked(	Gain		.ModeAuto);
	ui->checkBoxZoom		->setChecked(	Zoom		.ModeAuto);
	ui->checkBoxFocus		->setChecked(	Focus		.ModeAuto);
	ui->checkBoxExposure	->setChecked(	Exposure	.ModeAuto);
	ui->checkBoxIris		->setChecked(	Iris		.ModeAuto);
	ui->checkBoxPan			->setChecked(	Pan			.ModeAuto);
	ui->checkBoxTilt		->setChecked(	Tilt		.ModeAuto);
	ui->checkBoxRotation	->setChecked(	Rotation	.ModeAuto);
	ui->comboBoxPowerFrequency	->setCurrentIndex(PowerlineFrequency.CurrentValue);
	OnSetting--;
}

void SettingCameraDialog::LoadDataFromWindow(void)
{
	Brightness	.ModeAuto	=ui->checkBoxBrightness		->isChecked();
	Contrast	.ModeAuto	=ui->checkBoxContrast		->isChecked();
	Color		.ModeAuto	=ui->checkBoxColor			->isChecked();
	Vivid		.ModeAuto	=ui->checkBoxVivid			->isChecked();
	Vividation	.ModeAuto	=ui->checkBoxVividation		->isChecked();
	Gamma		.ModeAuto	=ui->checkBoxGamma			->isChecked();
	WhiteBalance.ModeAuto	=ui->checkBoxWhiteBalance	->isChecked();
	Reflection	.ModeAuto	=ui->checkBoxReflection		->isChecked();
	Gain		.ModeAuto	=ui->checkBoxGain			->isChecked();
	Zoom		.ModeAuto	=ui->checkBoxZoom			->isChecked();
	Focus		.ModeAuto	=ui->checkBoxFocus			->isChecked();
	Exposure	.ModeAuto	=ui->checkBoxExposure		->isChecked();
	Iris		.ModeAuto	=ui->checkBoxIris			->isChecked();
	Pan			.ModeAuto	=ui->checkBoxPan			->isChecked();
	Tilt		.ModeAuto	=ui->checkBoxTilt			->isChecked();
	Rotation	.ModeAuto	=ui->checkBoxRotation		->isChecked();
}

void SettingCameraDialog::on_comboBoxImageSize_currentIndexChanged(int index)
{
	if(OnSetting!=0)
		return;
	int	DimIndex=ui->comboBoxImageSize->currentIndex();
	int	k=GetMediaIndexFromDim(DimIndex);
	if(0<=k){
		Camera->SetMediaType(MediaDim[k]);
		int	XLen=MediaDim[k].Width;
		int	YLen=MediaDim[k].Height;
		if(GetDotPerLine(0)!=XLen || GetMaxLines(0)!=YLen){
			GetLayersBase()->ReallocXYPixels(XLen,YLen);
		}
	}
}

void	SettingCameraDialog::SetItemValue(PropertyItem &Prop,QSlider *s)
{
	Prop.CurrentValue=s->value()/(double)Prop.MaxValue;
	Prop.setProperty(Camera);
}

void SettingCameraDialog::on_horizontalSliderBrightness_valueChanged(int value)
{
	ui->labelBrightness		->setText(QString::number(ui->horizontalSliderBrightness	->value()));
	if(OnSetting!=0)
		return;

	SetItemValue(Brightness	,ui->horizontalSliderBrightness);
}

void SettingCameraDialog::on_horizontalSliderContrast_valueChanged(int value)
{
	ui->labelContrast		->setText(QString::number(ui->horizontalSliderContrast		->value()));
	if(OnSetting!=0)
		return;

	SetItemValue(Contrast,ui->horizontalSliderContrast);
}

void SettingCameraDialog::on_horizontalSliderColor_valueChanged(int value)
{
	ui->labelColor			->setText(QString::number(ui->horizontalSliderColor			->value()));
	if(OnSetting!=0)
		return;
	SetItemValue(Color,ui->horizontalSliderColor);
}

void SettingCameraDialog::on_horizontalSliderVivid_valueChanged(int value)
{
	ui->labelVivid			->setText(QString::number(ui->horizontalSliderVivid			->value()));
	if(OnSetting!=0)
		return;
	SetItemValue(Vivid,ui->horizontalSliderVivid);
}

void SettingCameraDialog::on_horizontalSliderVividation_valueChanged(int value)
{
	ui->labelVividation		->setText(QString::number(ui->horizontalSliderVividation	->value()));
	if(OnSetting!=0)
		return;
	SetItemValue(Vividation	,ui->horizontalSliderVividation);
}

void SettingCameraDialog::on_horizontalSliderGamma_valueChanged(int value)
{
	ui->labelGamma			->setText(QString::number(ui->horizontalSliderGamma			->value()));
	if(OnSetting!=0)
		return;
	SetItemValue(Gamma,ui->horizontalSliderGamma);
}

void SettingCameraDialog::on_horizontalSliderWhiteBalance_valueChanged(int value)
{
	ui->labelWhiteBalance	->setText(QString::number(ui->horizontalSliderWhiteBalance	->value()));
	if(OnSetting!=0)
		return;
	SetItemValue(WhiteBalance,ui->horizontalSliderWhiteBalance);
}

void SettingCameraDialog::on_horizontalSliderReflection_valueChanged(int value)
{
	ui->labelReflection		->setText(QString::number(ui->horizontalSliderReflection	->value()));
	if(OnSetting!=0)
		return;
	SetItemValue(Reflection,ui->horizontalSliderReflection);
}

void SettingCameraDialog::on_horizontalSliderGain_valueChanged(int value)
{
	ui->labelGain			->setText(QString::number(ui->horizontalSliderGain			->value()));
	if(OnSetting!=0)
		return;
	SetItemValue(Gain,ui->horizontalSliderGain);
}

void SettingCameraDialog::on_horizontalSliderZoom_valueChanged(int value)
{
	ui->labelZoom			->setText(QString::number(ui->horizontalSliderZoom			->value()));
	if(OnSetting!=0)
		return;
	SetItemValue(Zoom,ui->horizontalSliderZoom);
}

void SettingCameraDialog::on_horizontalSliderFocus_valueChanged(int value)
{
	ui->labelFocus			->setText(QString::number(ui->horizontalSliderFocus			->value()));
	if(OnSetting!=0)
		return;
	SetItemValue(Focus,ui->horizontalSliderFocus);
}

void SettingCameraDialog::on_horizontalSliderExposure_valueChanged(int value)
{
	ui->labelExposure		->setText(QString::number(ui->horizontalSliderExposure		->value()));
	if(OnSetting!=0)
		return;
	SetItemValue(Exposure,ui->horizontalSliderExposure);
}

void SettingCameraDialog::on_horizontalSliderIris_valueChanged(int value)
{
	ui->labelIris			->setText(QString::number(ui->horizontalSliderIris			->value()));
	if(OnSetting!=0)
		return;
	SetItemValue(Iris,ui->horizontalSliderIris);
}

void SettingCameraDialog::on_horizontalSliderPan_valueChanged(int value)
{
	ui->labelPan			->setText(QString::number(ui->horizontalSliderPan			->value()));
	if(OnSetting!=0)
		return;
	SetItemValue(Pan,ui->horizontalSliderPan);
}

void SettingCameraDialog::on_horizontalSliderTilt_valueChanged(int value)
{
	ui->labelTilt			->setText(QString::number(ui->horizontalSliderTilt			->value()));
	if(OnSetting!=0)
		return;
	SetItemValue(Tilt,ui->horizontalSliderTilt);
}

void SettingCameraDialog::on_horizontalSliderRotation_valueChanged(int value)
{
	ui->labelRotation		->setText(QString::number(ui->horizontalSliderRotation		->value()));
	if(OnSetting!=0)
		return;
	SetItemValue(Rotation,ui->horizontalSliderRotation);
}

void SettingCameraDialog::on_checkBoxAdjustLow_clicked()
{

}

void SettingCameraDialog::on_pushButtonDefault_clicked()
{
	Brightness		.CurrentValue	=Brightness	.DefaultValue;
	Contrast		.CurrentValue	=Contrast		.DefaultValue;
	Color			.CurrentValue	=Color			.DefaultValue;
	Vivid			.CurrentValue	=Vivid			.DefaultValue;
	Vividation		.CurrentValue	=Vividation	.DefaultValue;
	Gamma			.CurrentValue	=Gamma			.DefaultValue;
	WhiteBalance	.CurrentValue	=WhiteBalance	.DefaultValue;
	Reflection		.CurrentValue	=Reflection	.DefaultValue;
	Gain			.CurrentValue	=Gain			.DefaultValue;
	Zoom			.CurrentValue	=Zoom			.DefaultValue;
	Focus			.CurrentValue	=Focus			.DefaultValue;
	Exposure		.CurrentValue	=Exposure		.DefaultValue;
	Iris			.CurrentValue	=Iris			.DefaultValue;
	Pan				.CurrentValue	=Pan			.DefaultValue;
	Tilt			.CurrentValue	=Tilt			.DefaultValue;
	Rotation		.CurrentValue	=Rotation		.DefaultValue;
	PowerlineFrequency.CurrentValue	=PowerlineFrequency.DefaultValue;
	ReflectDataIntoWindow();
}

void	SettingCameraDialog::SetItemValue(PropertyItem &Prop,QSlider *s,QCheckBox *c)
{
	s->setEnabled(!c->isChecked());
	Prop.ModeAuto	=c->isChecked();
}

void SettingCameraDialog::on_checkBoxBrightness_clicked()
{
	if(OnSetting!=0)
		return;
	SetItemValue(Brightness,ui->horizontalSliderBrightness,ui->checkBoxBrightness);
}

void SettingCameraDialog::on_checkBoxContrast_clicked()
{
	if(OnSetting!=0)
		return;
	SetItemValue(Contrast,ui->horizontalSliderContrast,ui->checkBoxContrast);
}

void SettingCameraDialog::on_checkBoxColor_clicked()
{
	if(OnSetting!=0)
		return;
	SetItemValue(Color,ui->horizontalSliderColor,ui->checkBoxColor);
}

void SettingCameraDialog::on_checkBoxVivid_clicked()
{
	if(OnSetting!=0)
		return;
	SetItemValue(Vivid,ui->horizontalSliderVivid,ui->checkBoxVivid);
}

void SettingCameraDialog::on_checkBoxVividation_clicked()
{
	if(OnSetting!=0)
		return;
	SetItemValue(Vividation,ui->horizontalSliderVividation,ui->checkBoxVividation);
}

void SettingCameraDialog::on_checkBoxGamma_clicked()
{
	if(OnSetting!=0)
		return;
	SetItemValue(Gamma,ui->horizontalSliderGamma,ui->checkBoxGamma);
}

void SettingCameraDialog::on_checkBoxWhiteBalance_clicked()
{
	if(OnSetting!=0)
		return;
	SetItemValue(WhiteBalance,ui->horizontalSliderWhiteBalance,ui->checkBoxWhiteBalance);
}

void SettingCameraDialog::on_checkBoxReflection_clicked()
{
	if(OnSetting!=0)
		return;
	SetItemValue(Reflection,ui->horizontalSliderReflection,ui->checkBoxReflection);
}

void SettingCameraDialog::on_checkBoxGain_clicked()
{
	if(OnSetting!=0)
		return;
	SetItemValue(Gain,ui->horizontalSliderGain,ui->checkBoxGain);
}

void SettingCameraDialog::on_comboBoxPowerFrequency_currentIndexChanged(int index)
{
	if(OnSetting!=0)
		return;
	SetItemValue(PowerlineFrequency,ui->comboBoxPowerFrequency);
}

void SettingCameraDialog::on_checkBoxZoom_clicked()
{
	if(OnSetting!=0)
		return;
	SetItemValue(Zoom,ui->horizontalSliderZoom,ui->checkBoxZoom);
}

void SettingCameraDialog::on_checkBoxFocus_clicked()
{
	if(OnSetting!=0)
		return;
	SetItemValue(Focus,ui->horizontalSliderFocus,ui->checkBoxFocus);
}

void SettingCameraDialog::on_checkBoxExposure_clicked()
{
	if(OnSetting!=0)
		return;
	SetItemValue(Exposure,ui->horizontalSliderExposure,ui->checkBoxExposure);
}

void SettingCameraDialog::on_checkBoxIris_clicked()
{
	if(OnSetting!=0)
		return;
	SetItemValue(Iris,ui->horizontalSliderIris,ui->checkBoxIris);
}

void SettingCameraDialog::on_checkBoxPan_clicked()
{
	if(OnSetting!=0)
		return;
	SetItemValue(Pan,ui->horizontalSliderPan,ui->checkBoxPan);
}

void SettingCameraDialog::on_checkBoxTilt_clicked()
{
	if(OnSetting!=0)
		return;
	SetItemValue(Tilt,ui->horizontalSliderTilt,ui->checkBoxTilt);
}

void SettingCameraDialog::on_checkBoxRotation_clicked()
{
	if(OnSetting!=0)
		return;
	SetItemValue(Rotation,ui->horizontalSliderRotation,ui->checkBoxRotation);
}

void SettingCameraDialog::on_pushButtonOK_clicked()
{
	LoadDataFromWindow();

	*Camera->GetBrightness			()=Brightness	;
	*Camera->GetContrast			()=Contrast		;
	*Camera->GetColor				()=Color		;
	*Camera->GetVivid				()=Vivid		;
	*Camera->GetVividation			()=Vividation	;
	*Camera->GetGamma				()=Gamma		;
	*Camera->GetWhiteBalance		()=WhiteBalance	;
	*Camera->GetReflection			()=Reflection	;
	*Camera->GetGain				()=Gain			;
	*Camera->GetZoom				()=Zoom			;
	*Camera->GetFocus				()=Focus		;
	*Camera->GetExposure			()=Exposure		;
	*Camera->GetIris				()=Iris			;
	*Camera->GetPan					()=Pan			;
	*Camera->GetTilt				()=Tilt			;
	*Camera->GetRotation			()=Rotation		;
	*Camera->GetPowerlineFrequency	()=PowerlineFrequency;

	int	DimIndex=ui->comboBoxImageSize->currentIndex();
	int	k=GetMediaIndexFromDim(DimIndex);
	if(0<=k){
		Camera->SetMediaType(MediaDim[k]);
	}

	/*
	GUIFormBase	*f=dynamic_cast<GUIFormBase	*>(Parent);
	if(f!=NULL){
		if(CameraUSBStandardData->CamData[CamNo]->XLen!=f->GetLayersBase()->GetDotPerLine()
		|| CameraUSBStandardData->CamData[CamNo]->YLen!=f->GetLayersBase()->GetMaxLines()){
			f->GetLayersBase()->ReallocXYPixels( CameraUSBStandardData->CamData[CamNo]->XLen
												,CameraUSBStandardData->CamData[CamNo]->YLen);
			f->GetLayersBase()->SetAreaSizeInImagePanel(true);
		}
	}
	*/

	done(true);
}

void SettingCameraDialog::on_pushButtonCancel_clicked()
{
	Camera->SetMediaType(PrevType);

	*Camera->GetBrightness	()=SavedBrightness		;
	*Camera->GetContrast	()=SavedContrast		;
	*Camera->GetColor		()=SavedColor			;
	*Camera->GetVivid		()=SavedVivid			;
	*Camera->GetVividation	()=SavedVividation		;
	*Camera->GetGamma		()=SavedGamma			;
	*Camera->GetWhiteBalance()=SavedWhiteBalance	;
	*Camera->GetReflection	()=SavedReflection		;
	*Camera->GetGain		()=SavedGain			;
	*Camera->GetZoom		()=SavedZoom			;
	*Camera->GetFocus		()=SavedFocus			;
	*Camera->GetExposure	()=SavedExposure		;
	*Camera->GetIris		()=SavedIris			;
	*Camera->GetPan			()=SavedPan				;
	*Camera->GetTilt		()=SavedTilt			;
	*Camera->GetRotation	()=SavedRotation		;
	*Camera->GetPowerlineFrequency	()=SavedPowerlineFrequency;

	Camera->setProperty();

	if(CurrentXLen!=GetDotPerLine(0) || CurrentYLen!=GetMaxLines(0)){
		GetLayersBase()->ReallocXYPixels(CurrentXLen,CurrentYLen);
	}

	done(false);
}

void SettingCameraDialog::on_pushButtonSave_clicked()
{
	QString	FileName=QFileDialog::getSaveFileName(NULL,"Save camera setting"
													, QString()
													, "Camera file(*.cam);;All files(*.*)");
	if(FileName.isEmpty()==false){
		QFile	File(FileName);
		if(File.open(QIODevice::WriteOnly)==true){
			if(Camera->Save(&File)==false){
				QMessageBox::warning(NULL,"Error","Error to save camera setting file");
			}
		}
		else{
			QMessageBox::warning(NULL,"Error",QString("Can not open file :")+FileName);
		}
	}
}

void SettingCameraDialog::on_pushButtonLoad_clicked()
{
	QString	FileName=QFileDialog::getOpenFileName(NULL,"Load camera setting"
													, QString()
													, "Camera file(*.cam);;All files(*.*)");
	if(FileName.isEmpty()==false){
		QFile	File(FileName);
		if(File.open(QIODevice::ReadOnly)==true){
			if(Camera->Load(&File)==false){
				QMessageBox::warning(NULL,"Error","Error to load camera setting file");
				return;
			}
			Brightness			=*Camera->GetBrightness		();
			Contrast			=*Camera->GetContrast		();
			Color				=*Camera->GetColor			();
			Vivid				=*Camera->GetVivid			();
			Vividation			=*Camera->GetVividation		();
			Gamma				=*Camera->GetGamma			();
			WhiteBalance		=*Camera->GetWhiteBalance	();
			Reflection			=*Camera->GetReflection		();
			Gain				=*Camera->GetGain			();
			Zoom				=*Camera->GetZoom			();
			Focus				=*Camera->GetFocus			();
			Exposure			=*Camera->GetExposure		();
			Iris				=*Camera->GetIris			();
			Pan					=*Camera->GetPan			();
			Tilt				=*Camera->GetTilt			();
			Rotation			=*Camera->GetRotation		();
			PowerlineFrequency	=*Camera->GetPowerlineFrequency	();
			ReflectDataIntoWindow();
		}
		else{
			QMessageBox::warning(NULL,"Error",QString("Can not open file :")+FileName);
		}
	}
}

void SettingCameraDialog::on_pushButtonResetSettingEachCamera_clicked()
{
	Camera->RestoreDefault();
	ReflectDataIntoWindow();
}
int	SettingCameraDialog::GetMediaIndexFromDim(int DimIndex)
{
	for(int i=0;i<MediaCount;i++){
		if(MediaDim[i].Width ==CamResolutionDim[DimIndex].CamViewSizeX
		&& MediaDim[i].Height==CamResolutionDim[DimIndex].CamViewSizeY
		&& MediaDim[i].FPS	 ==CamResolutionDim[DimIndex].CamViewFPS
		&& (MediaDim[i].ConvertType==_EMT_YUY2 || MediaDim[i].ConvertType==_EMT_MJPG)){
			return i;
		}
	}
	return -1;
}

void	SettingCameraDialog::SetItemValue(PropertyItemPowerlineFrequency &Prop,QComboBox *s)
{
	Prop.CurrentValue=s->currentIndex();
	Prop.setProperty(Camera);
}
