#include "SettingLED500Dialog.h"
#include "ui_SettingLED500Dialog.h"
#include "XLight500.h"

SettingLED500Dialog::SettingLED500Dialog(LayersBase *base, LED500Panel	*p ,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
	,LightAccessor(p)
    ,ui(new Ui::SettingLED500Dialog)
{
    ui->setupUi(this);
	EnabledChanged=true;

	ui->spinBoxAll		->setMaximum(MaxBrightness);
	ui->spinBoxLBar0	->setMaximum(MaxBrightness);
	ui->spinBoxLBar1	->setMaximum(MaxBrightness);
	ui->spinBoxLBar2	->setMaximum(MaxBrightness);
	ui->spinBoxLBar3	->setMaximum(MaxBrightness);
	ui->spinBoxLBar4	->setMaximum(MaxBrightness);
	ui->spinBoxLBar5	->setMaximum(MaxBrightness);
	ui->spinBoxLBar6	->setMaximum(MaxBrightness);
	ui->spinBoxRBar0	->setMaximum(MaxBrightness);
	ui->spinBoxRBar1	->setMaximum(MaxBrightness);
	ui->spinBoxRBar2	->setMaximum(MaxBrightness);
	ui->spinBoxRBar3	->setMaximum(MaxBrightness);
	ui->spinBoxRBar4	->setMaximum(MaxBrightness);
	ui->spinBoxRBar5	->setMaximum(MaxBrightness);
	ui->spinBoxRBar6	->setMaximum(MaxBrightness);

	if(LightAccessor!=NULL){
		ui->checkBoxSyncMode->setChecked(LightAccessor->SyncMode);
		ui->spinBoxSyncForward		->setValue(LightAccessor->SyncForward);
		ui->spinBoxSyncPulsePerBar	->setValue(LightAccessor->SyncPulsePerBar);
		ui->spinBoxSyncBackward		->setValue(LightAccessor->SyncBackward);

		ui->comboBoxComm	->setCurrentIndex(LightAccessor->CommPort);
		ui->dsbGradValue->setValue(LightAccessor->GradValue);
		on_comboBoxLeft_currentIndexChanged(0);
		on_comboBoxRight_currentIndexChanged(0);
	}
	
	InstallOperationLog(this);
}

SettingLED500Dialog::~SettingLED500Dialog()
{
    delete ui;
}

void SettingLED500Dialog::on_comboBoxLeft_currentIndexChanged(int index)
{
	EnabledChanged=false;
	ui->spinBoxLBar0	->setValue(LightAccessor->Brightness[index][0]);
	ui->spinBoxLBar1	->setValue(LightAccessor->Brightness[index][1]);
	ui->spinBoxLBar2	->setValue(LightAccessor->Brightness[index][2]);
	ui->spinBoxLBar3	->setValue(LightAccessor->Brightness[index][3]);
	ui->spinBoxLBar4	->setValue(LightAccessor->Brightness[index][4]);
	ui->spinBoxLBar5	->setValue(LightAccessor->Brightness[index][5]);
	ui->spinBoxLBar6	->setValue(LightAccessor->Brightness[index][6]);
	EnabledChanged=true;
}

void SettingLED500Dialog::on_comboBoxRight_currentIndexChanged(int index)
{
	EnabledChanged=false;
	ui->spinBoxRBar0	->setValue(LightAccessor->Brightness[15+index][0]);
	ui->spinBoxRBar1	->setValue(LightAccessor->Brightness[15+index][1]);
	ui->spinBoxRBar2	->setValue(LightAccessor->Brightness[15+index][2]);
	ui->spinBoxRBar3	->setValue(LightAccessor->Brightness[15+index][3]);
	ui->spinBoxRBar4	->setValue(LightAccessor->Brightness[15+index][4]);
	ui->spinBoxRBar5	->setValue(LightAccessor->Brightness[15+index][5]);
	ui->spinBoxRBar6	->setValue(LightAccessor->Brightness[15+index][6]);
	EnabledChanged=true;
}

void SettingLED500Dialog::on_spinBoxLBar0_valueChanged(int arg1)
{
	if(EnabledChanged==true){
		LightAccessor	->Brightness[ui->comboBoxLeft->currentIndex()][0]	=ui->spinBoxLBar0	->value();
	}
}

void SettingLED500Dialog::on_spinBoxLBar1_valueChanged(int arg1)
{
	if(EnabledChanged==true){
		LightAccessor	->Brightness[ui->comboBoxLeft->currentIndex()][1]	=ui->spinBoxLBar1	->value();
	}
}

void SettingLED500Dialog::on_spinBoxLBar2_valueChanged(int arg1)
{
	if(EnabledChanged==true){
		LightAccessor	->Brightness[ui->comboBoxLeft->currentIndex()][2]	=ui->spinBoxLBar2	->value();
	}
}

void SettingLED500Dialog::on_spinBoxLBar3_valueChanged(int arg1)
{
	if(EnabledChanged==true){
		LightAccessor	->Brightness[ui->comboBoxLeft->currentIndex()][3]	=ui->spinBoxLBar3	->value();
	}
}

void SettingLED500Dialog::on_spinBoxLBar4_valueChanged(int arg1)
{
	if(EnabledChanged==true){
		LightAccessor	->Brightness[ui->comboBoxLeft->currentIndex()][4]	=ui->spinBoxLBar4	->value();
	}
}

void SettingLED500Dialog::on_spinBoxLBar5_valueChanged(int arg1)
{
	if(EnabledChanged==true){
		LightAccessor	->Brightness[ui->comboBoxLeft->currentIndex()][5]	=ui->spinBoxLBar5	->value();
	}
}

void SettingLED500Dialog::on_spinBoxLBar6_valueChanged(int arg1)
{
	if(EnabledChanged==true){
		LightAccessor	->Brightness[ui->comboBoxLeft->currentIndex()][6]	=ui->spinBoxLBar6	->value();
	}

}

void SettingLED500Dialog::on_spinBoxRBar0_valueChanged(int arg1)
{
	if(EnabledChanged==true){
		LightAccessor	->Brightness[15+ui->comboBoxRight->currentIndex()][0]	=ui->spinBoxRBar0	->value();
	}
}

void SettingLED500Dialog::on_spinBoxRBar1_valueChanged(int arg1)
{
	if(EnabledChanged==true){
		LightAccessor	->Brightness[15+ui->comboBoxRight->currentIndex()][1]	=ui->spinBoxRBar1	->value();
	}
}

void SettingLED500Dialog::on_spinBoxRBar2_valueChanged(int arg1)
{
	if(EnabledChanged==true){
		LightAccessor	->Brightness[15+ui->comboBoxRight->currentIndex()][2]	=ui->spinBoxRBar2	->value();
	}
}

void SettingLED500Dialog::on_spinBoxRBar3_valueChanged(int arg1)
{
	if(EnabledChanged==true){
		LightAccessor	->Brightness[15+ui->comboBoxRight->currentIndex()][3]	=ui->spinBoxRBar3	->value();
	}
}

void SettingLED500Dialog::on_spinBoxRBar4_valueChanged(int arg1)
{
	if(EnabledChanged==true){
		LightAccessor	->Brightness[15+ui->comboBoxRight->currentIndex()][4]	=ui->spinBoxRBar4	->value();
	}
}

void SettingLED500Dialog::on_spinBoxRBar5_valueChanged(int arg1)
{
	if(EnabledChanged==true){
		LightAccessor	->Brightness[15+ui->comboBoxRight->currentIndex()][5]	=ui->spinBoxRBar5	->value();
	}
}

void SettingLED500Dialog::on_spinBoxRBar6_valueChanged(int arg1)
{
	if(EnabledChanged==true){
		LightAccessor	->Brightness[15+ui->comboBoxRight->currentIndex()][6]	=ui->spinBoxRBar6	->value();
	}
}

void SettingLED500Dialog::on_pushButtonSetAll_clicked()
{
	qreal gval = ui->dsbGradValue->value();
	LightAccessor	->SetAll(ui->spinBoxAll->value(), gval);
	on_comboBoxLeft_currentIndexChanged(ui->comboBoxLeft->currentIndex());
	on_comboBoxRight_currentIndexChanged(ui->comboBoxRight->currentIndex());
}


void SettingLED500Dialog::on_pushButtonSetLeft_clicked()
{
	qreal gval = ui->dsbGradValue->value();
	LightAccessor	->SetLeft(ui->spinBoxLeft->value(), gval);
	on_comboBoxLeft_currentIndexChanged(ui->comboBoxLeft->currentIndex());
}

void SettingLED500Dialog::on_pushButtonSetRight_clicked()
{
	qreal gval = ui->dsbGradValue->value();
	LightAccessor	->SetRight(ui->spinBoxRight->value(), gval);
	on_comboBoxRight_currentIndexChanged(ui->comboBoxRight->currentIndex());
}

void SettingLED500Dialog::on_pushButtonClose_clicked()
{
	if(LightAccessor!=NULL){
		LightAccessor->CommPort	=ui->comboBoxComm	->currentIndex();

		LightAccessor->SyncMode		=ui->checkBoxSyncMode			->isChecked();
		LightAccessor->SyncForward	=ui->spinBoxSyncForward			->value();
		LightAccessor->SyncPulsePerBar	=ui->spinBoxSyncPulsePerBar	->value();
		LightAccessor->SyncBackward		=ui->spinBoxSyncBackward	->value();
	}
	done(true);
}

void SettingLED500Dialog::on_checkBoxSyncMode_clicked()
{
	if(ui->checkBoxSyncMode->isChecked()==true){
		ui->spinBoxSyncForward		->setEnabled(true);
		ui->spinBoxSyncPulsePerBar	->setEnabled(true);
		ui->spinBoxSyncBackward		->setEnabled(true);
	}
	else{
		ui->spinBoxSyncForward		->setEnabled(false);
		ui->spinBoxSyncPulsePerBar	->setEnabled(false);
		ui->spinBoxSyncBackward		->setEnabled(false);
	}
}

void SettingLED500Dialog::on_toolButtonOnOff_clicked()
{
	if(LightAccessor!=NULL){
		LightAccessor->CommPort	=ui->comboBoxComm	->currentIndex();
		LightAccessor->SetOnOff(ui->toolButtonOnOff->isChecked());
	}
}

void SettingLED500Dialog::on_spinBoxSyncForward_valueChanged(int arg1)
{

}

void SettingLED500Dialog::on_spinBoxSyncPulsePerBar_valueChanged(int arg1)
{

}

void SettingLED500Dialog::on_spinBoxSyncBackward_valueChanged(int arg1)
{

}

void SettingLED500Dialog::on_pushButtonTransfer_clicked()
{
	if(LightAccessor!=NULL){
		LightAccessor->CommPort	=ui->comboBoxComm	->currentIndex();

		LightAccessor->SyncMode		=ui->checkBoxSyncMode			->isChecked();
		LightAccessor->SyncForward	=ui->spinBoxSyncForward			->value();
		LightAccessor->SyncPulsePerBar	=ui->spinBoxSyncPulsePerBar	->value();
		LightAccessor->SyncBackward		=ui->spinBoxSyncBackward	->value();

		LightAccessor->SendSync();
		ui->progressBar->setMaximum(SheetCountInSystem*LEDCountInSheet);
		int	n=0;
		for(int s=0;s<SheetCountInSystem;s++){
			if(LightAccessor->IsSameBrightness(s)==true){
				if(LightAccessor->SendBrightnessAllLED(s)==false){
					return;
				}
				ui->progressBar->setValue(n);
				n+=LEDCountInSheet;
			}
			else{
				for(int c=0;c<LEDCountInSheet;c++){
					if(LightAccessor->SendBrightness(s,c)==false){
						return;
					}
					ui->progressBar->setValue(n);
					n++;
				}
			}
			qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
		}
		ui->progressBar->setValue(ui->progressBar->maximum());
		LightAccessor->SendReflect();
	}
}
