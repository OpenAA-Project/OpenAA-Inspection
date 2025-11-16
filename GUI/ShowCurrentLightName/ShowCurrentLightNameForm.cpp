#include "ShowCurrentLightNameForm.h"
#include "ui_ShowCurrentLightNameForm.h"
#include "ButtonSelectLightDB.h"
#include "XDatabaseLoader.h"

ShowCurrentLightNameForm::ShowCurrentLightNameForm(LayersBase *base ,QWidget *parent) :
     GUIFormBase(base ,parent),
    ui(new Ui::ShowCurrentLightNameForm)
{
    ui->setupUi(this);

	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ShowCurrentLightNameForm::~ShowCurrentLightNameForm()
{
    delete ui;
}
void	ShowCurrentLightNameForm::Prepare(void)
{
	ui->labelID			->setFont (CFont);
	ui->labelLightName	->setFont (CFont);

	ResizeAction();
	ui->labelID			->setText(/**/"");
	ui->labelLightName	->setText(/**/"");
}

void	ShowCurrentLightNameForm::ResizeAction()
{
	int	w=width();
	ui->labelID			->resize(ui->labelID->width() ,height());		
	ui->labelLightName	->resize(w-ui->labelID->width() ,height());
}

void	ShowCurrentLightNameForm::ShowInEdit	(void)
{
	ui->labelID			->setText(/**/"");
	ui->labelLightName	->setText(/**/"");

	CmdReqCurrentSelectedLightID	RCmd(GetLayersBase());
	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Button" , /**/"ButtonSelectLightDB",/**/"");
	if(f!=NULL){
		f->TransmitDirectly(&RCmd);
		int	LightID=RCmd.SelectedLightID;
		if(LightID>=0){
			std::shared_ptr<DatabaseLoader>	DL=GetLayersBase()->GetDatabaseLoader();
			QSqlQuery *query=DL->S_GetLight(GetLayersBase()->GetDatabase() ,GetLayersBase()->GetMachineID(),LightID);
			if(query!=NULL && DL->S_FindNext(query)==true){
				QVariant vNAME;
				if(DL->S_GetFieldValue(query,/**/"NAME",vNAME)==true){
					ui->labelID			->setText(QString::number(LightID));
					ui->labelLightName	->setText(vNAME.toString());
				}
			}
		}
	}
}
