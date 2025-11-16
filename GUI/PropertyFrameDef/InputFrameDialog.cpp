#include "InputFrameDialog.h"
#include "ui_InputFrameDialog.h"
#include "XRememberer.h"
#include"XPropertyFrameDefPacket.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

InputFrameDialog::InputFrameDialog(bool _EditMode ,LayersBase *Base ,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(Base)
    ,ui(new Ui::InputFrameDialog)
{
    ui->setupUi(this);
	//LangSolver.SetUI(this);

	EditMode=_EditMode;
	ui->spinBoxGroupNumber	->setValue(ControlRememberer::GetInt(ui->spinBoxGroupNumber,0));
	ui->spinBoxFrameNumber	->setValue(ControlRememberer::GetInt(ui->spinBoxFrameNumber,0));
	ui->checkBoxOrigin		->setChecked(ControlRememberer::GetBool(ui->checkBoxOrigin,true));
	on_spinBoxGroupNumber_valueChanged(0);
	InstallOperationLog(this);
}

InputFrameDialog::~InputFrameDialog()
{
    delete ui;
}
void	InputFrameDialog::Initial(int groupNumber ,int frameNumber ,bool origin)
{
	GroupNumber	=groupNumber;
	FrameNumber	=frameNumber;
	Origin		=origin;
	ui->spinBoxGroupNumber->setValue(GroupNumber);
	ui->spinBoxFrameNumber->setValue(FrameNumber);
	ui->checkBoxOrigin		->setChecked(Origin);
}
void InputFrameDialog::on_pushButtonOK_clicked()
{
	GroupNumber		=ui->spinBoxGroupNumber	->value();
	FrameNumber		=ui->spinBoxFrameNumber	->value();
	Origin			=ui->checkBoxOrigin		->isChecked();
	ControlRememberer::SetValue(ui->spinBoxGroupNumber	,ui->spinBoxGroupNumber->value());
	ControlRememberer::SetValue(ui->spinBoxFrameNumber	,ui->spinBoxFrameNumber->value());
	ControlRememberer::SetValue(ui->checkBoxOrigin		,ui->checkBoxOrigin->isChecked());
	done(true);
}

void InputFrameDialog::on_pushButtonCancel_clicked()
{
	done(false);
}

void InputFrameDialog::on_spinBoxGroupNumber_valueChanged(int arg1)
{
	if(EditMode==false){
		int	GroupNumber=ui->spinBoxGroupNumber->value();
		int		MaxFrameNumber=0;
		bool	origin=true;
		for(int page=0;page<GetPageNumb();page++){
			int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
			GUICmdReqMaxFrameNumber		RCmd(GetLayersBase(),sRoot,sName,globalPage);
			GUICmdAckMaxFrameNumber		ACmd(GetLayersBase(),sRoot,sName,globalPage);
			RCmd.GroupNumber	=GroupNumber;
			if(RCmd.Send(globalPage,0,ACmd)==true
			&& ACmd.IsReceived()==true){
				if(MaxFrameNumber<ACmd.FrameNumber){
					MaxFrameNumber=ACmd.FrameNumber;
				}
				if(ACmd.OriginExists==true)
					origin=false;
			}
		}
		ui->spinBoxFrameNumber	->setValue(MaxFrameNumber+1);
		ui->checkBoxOrigin		->setChecked(origin);
	}
}
