#include "CartonMenuResource.h"
#include "SetThresholdDialog.h"
#include "ui_SetThresholdDialog.h"
#include "CartonMenuForm.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

SetThresholdDialog::SetThresholdDialog(int _SlaveNo ,LayersBase *Base ,CartonMenuForm *p, QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(Base)
	,Parent(p)
	,SlaveNo(_SlaveNo)
    ,ui(new Ui::SetThresholdDialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);
	setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

	if(SlaveNo==0){
		ui->horizontalSliderLevelCharBright	->setValue(Parent->Param.LevelTopCharBrightness);
		ui->horizontalSliderLevelCharSize	->setValue(Parent->Param.LevelTopCharSize);
		ui->horizontalSliderLevelFlatBright	->setValue(Parent->Param.LevelTopFlatBrightness);
		ui->horizontalSliderLevelFlatSize	->setValue(Parent->Param.LevelTopFlatSize);
	}
	else{
		ui->horizontalSliderLevelCharBright	->setValue(Parent->Param.LevelBottomCharBrightness);
		ui->horizontalSliderLevelCharSize	->setValue(Parent->Param.LevelBottomCharSize);
		ui->horizontalSliderLevelFlatBright	->setValue(Parent->Param.LevelBottomFlatBrightness);
		ui->horizontalSliderLevelFlatSize	->setValue(Parent->Param.LevelBottomFlatSize);
	}
}

SetThresholdDialog::~SetThresholdDialog()
{
    delete ui;
}

void SetThresholdDialog::on_horizontalSliderLevelCharBright_valueChanged(int value)
{
	int	Level=ui->horizontalSliderLevelCharBright->value();
	ui->label_LevelCharBright	->setText(QString::number(Level));
 
	IntegrationSendInsectionLevel	Cmd(GetLayersBase(),sRoot,sName,SlaveNo);
	switch(Level){
	case 0:		Cmd.Level=2.0;	break;
	case 1:		Cmd.Level=1.7;	break;
	case 2:		Cmd.Level=1.5;	break;
	case 3:		Cmd.Level=1.4;	break;
	case 4:		Cmd.Level=1.2;	break;
	case 5:		Cmd.Level=1.0;	break;
	case 6:		Cmd.Level=0.9;	break;
	case 7:		Cmd.Level=0.8;	break;
	case 8:		Cmd.Level=0.7;	break;
	case 9:		Cmd.Level=0.6;	break;
	case 10:	Cmd.Level=0.5;	break;
	}
	Cmd.Type=0;
	Cmd.Send(NULL,SlaveNo,0);
}

void SetThresholdDialog::on_horizontalSliderLevelCharSize_valueChanged(int value)
{
	int	Level=ui->horizontalSliderLevelCharSize->value();
	ui->label_LevelCharSize	->setText(QString::number(Level));
 
	IntegrationSendInsectionLevel	Cmd(GetLayersBase(),sRoot,sName,SlaveNo);
	switch(Level){
	case 0:		Cmd.Level=2.0;	break;
	case 1:		Cmd.Level=1.7;	break;
	case 2:		Cmd.Level=1.5;	break;
	case 3:		Cmd.Level=1.4;	break;
	case 4:		Cmd.Level=1.2;	break;
	case 5:		Cmd.Level=1.0;	break;
	case 6:		Cmd.Level=0.9;	break;
	case 7:		Cmd.Level=0.8;	break;
	case 8:		Cmd.Level=0.7;	break;
	case 9:		Cmd.Level=0.6;	break;
	case 10:	Cmd.Level=0.5;	break;
	}
	Cmd.Type=1;
	Cmd.Send(NULL,SlaveNo,0);
}

void SetThresholdDialog::on_horizontalSliderLevelFlatBright_valueChanged(int value)
{
	int	Level=ui->horizontalSliderLevelFlatBright->value();
	ui->label_LevelFlatBright	->setText(QString::number(Level));
 
	IntegrationSendInsectionLevel	Cmd(GetLayersBase(),sRoot,sName,SlaveNo);
	switch(Level){
	case 0:		Cmd.Level=2.0;	break;
	case 1:		Cmd.Level=1.7;	break;
	case 2:		Cmd.Level=1.5;	break;
	case 3:		Cmd.Level=1.4;	break;
	case 4:		Cmd.Level=1.2;	break;
	case 5:		Cmd.Level=1.0;	break;
	case 6:		Cmd.Level=0.9;	break;
	case 7:		Cmd.Level=0.8;	break;
	case 8:		Cmd.Level=0.7;	break;
	case 9:		Cmd.Level=0.6;	break;
	case 10:	Cmd.Level=0.5;	break;
	}
	Cmd.Type=2;
	Cmd.Send(NULL,SlaveNo,0);
}

void SetThresholdDialog::on_horizontalSliderLevelFlatSize_valueChanged(int value)
{
	int	Level=ui->horizontalSliderLevelFlatSize->value();
	ui->label_LevelFlatSize	->setText(QString::number(Level));
 
	IntegrationSendInsectionLevel	Cmd(GetLayersBase(),sRoot,sName,SlaveNo);
	switch(Level){
	case 0:		Cmd.Level=2.0;	break;
	case 1:		Cmd.Level=1.7;	break;
	case 2:		Cmd.Level=1.5;	break;
	case 3:		Cmd.Level=1.4;	break;
	case 4:		Cmd.Level=1.2;	break;
	case 5:		Cmd.Level=1.0;	break;
	case 6:		Cmd.Level=0.9;	break;
	case 7:		Cmd.Level=0.8;	break;
	case 8:		Cmd.Level=0.7;	break;
	case 9:		Cmd.Level=0.6;	break;
	case 10:	Cmd.Level=0.5;	break;
	}
	Cmd.Type=3;
	Cmd.Send(NULL,SlaveNo,0);
}

void SetThresholdDialog::on_PushButtonClose_clicked()
{
	if(SlaveNo==0){
		Parent->Param.LevelTopCharBrightness=ui->horizontalSliderLevelCharBright->value();
		Parent->Param.LevelTopCharSize		=ui->horizontalSliderLevelCharSize	->value();
		Parent->Param.LevelTopFlatBrightness=ui->horizontalSliderLevelFlatBright->value();
		Parent->Param.LevelTopFlatSize		=ui->horizontalSliderLevelFlatSize	->value();
	}
	else{
		Parent->Param.LevelBottomCharBrightness	=ui->horizontalSliderLevelCharBright->value();
		Parent->Param.LevelBottomCharSize		=ui->horizontalSliderLevelCharSize	->value();
		Parent->Param.LevelBottomFlatBrightness	=ui->horizontalSliderLevelFlatBright->value();
		Parent->Param.LevelBottomFlatSize		=ui->horizontalSliderLevelFlatSize	->value();
	}
	Parent->Param.SaveDefault(GetLayersBase()->GetUserPath());
	done(true);
}
