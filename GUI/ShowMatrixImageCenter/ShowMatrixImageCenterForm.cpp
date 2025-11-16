#include "ShowMatrixImageCenterResource.h"
#include "ShowMatrixImageCenterForm.h"
#include "ui_ShowMatrixImageCenterForm.h"
#include "ShowMatrixImageCenter.h"

ShowMatrixImageCenterForm::ShowMatrixImageCenterForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::ShowMatrixImageCenterForm)
{
    ui->setupUi(this);

	CenterX=0;
	CenterY=0;

	GetParamGUI()->SetParam(&CenterX, /**/"ShowMatrixImageCenter",/**/"CenterX"		
							,LangSolver.GetString(ShowMatrixImageCenterForm_LS,LID_0)/*"Center X"*/);
	GetParamGUI()->SetParam(&CenterY, /**/"ShowMatrixImageCenter",/**/"CenterY"		
							,LangSolver.GetString(ShowMatrixImageCenterForm_LS,LID_1)/*"Center Y"*/);
}

ShowMatrixImageCenterForm::~ShowMatrixImageCenterForm()
{
    delete ui;
}

void	ShowMatrixImageCenterForm::Prepare(void)
{
	ui->spinBoxCenterX	->setValue(CenterY);
	ui->spinBoxCenterY	->setValue(CenterY);
}

void	ShowMatrixImageCenterForm::SetCenter(int x ,int y)
{
	ui->spinBoxCenterX	->setValue(x);
	ui->spinBoxCenterY	->setValue(y);
}

void	ShowMatrixImageCenterForm::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdSetCenterInImage	*CmdSetCenterInImageVar=dynamic_cast<CmdSetCenterInImage *>(packet);
	if(CmdSetCenterInImageVar!=NULL){
		SetCenter(CmdSetCenterInImageVar->x ,CmdSetCenterInImageVar->y);
		return;
	}
	CmdReqCenterInImage	*CmdReqCenterInImageVar=dynamic_cast<CmdReqCenterInImage *>(packet);
	if(CmdReqCenterInImageVar!=NULL){
		CmdReqCenterInImageVar->x=ui->spinBoxCenterX->value();
		CmdReqCenterInImageVar->y=ui->spinBoxCenterY->value();
		return;
	}
}