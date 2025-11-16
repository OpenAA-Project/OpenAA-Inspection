#include "ButtonSettingColorDifferenceResource.h"
#include "ButtonSettingColorDifferenceForm.h"
#include "ui_ButtonSettingColorDifferenceForm.h"
#include "SettingColorDifferenceDialog.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

ButtonSettingColorDifferenceForm::ButtonSettingColorDifferenceForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::ButtonSettingColorDifferenceForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	SlaveNo=0;
	Msg=/**/"Set Threshold";
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonSettingColorDifferenceForm::~ButtonSettingColorDifferenceForm()
{
    delete ui;
}
void	ButtonSettingColorDifferenceForm::Prepare(void)
{
	ui->PushButtonThreshold->setText(Msg);
	ui->PushButtonThreshold->setFont (CFont);
	ResizeAction();
}
void	ButtonSettingColorDifferenceForm::ResizeAction()
{
	ui->PushButtonThreshold->resize(width(),height());
}

void ButtonSettingColorDifferenceForm::on_PushButtonThreshold_clicked()
{
	SettingColorDifferenceDialog	D(GetLayersBase(),this);
	D.exec();
	//delete	D;
}
