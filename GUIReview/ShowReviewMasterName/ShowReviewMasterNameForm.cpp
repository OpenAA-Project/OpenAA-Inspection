#include "ShowReviewMasterNameResource.h"
#include "ShowReviewMasterNameForm.h"
#include "ui_ShowReviewMasterNameForm.h"
#include "ReviewStructurePacket.h"
#include "..\XGUIReviewGlobal.h"
#include "XReviewStructure.h"

ShowReviewMasterNameForm::ShowReviewMasterNameForm(LayersBase *base ,QWidget *parent) :
    GUIFormBase(base,parent),
    ui(new Ui::ShowReviewMasterNameForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ShowReviewMasterNameForm::~ShowReviewMasterNameForm()
{
    delete ui;
}
void	ShowReviewMasterNameForm::Prepare(void)
{
	ResizeAction();
}

void	ShowReviewMasterNameForm::BuildForShow(void)
{
	ReviewPIBase *RBase = GetReviewAlgorithm();
	CmdReqMasterDataInfo LoadedMaster(GetLayersBase());
	RBase->TransmitDirectly(&LoadedMaster);

	CmdReqCurrentLotInfoData	LoadedLot(GetLayersBase());
	RBase->TransmitDirectly(&LoadedLot);

	ui->lineEditMasterCode1	->setText(QString::number(LoadedMaster.FrontMasterDataInfo.MasterCode));
	ui->lineEditMasterName1	->setText(LoadedMaster.FrontMasterDataInfo.MasterName);
	ui->lineEditLotID1	->setText(LoadedLot.FrontLotName);
	ui->lineEditLotName1->setText(LoadedLot.FrontLotID);

	ui->lineEditMasterCode2	->setText(QString::number(LoadedMaster.BackMasterDataInfo.MasterCode));
	ui->lineEditMasterName2	->setText(LoadedMaster.BackMasterDataInfo.MasterName);
	ui->lineEditLotID2	->setText(LoadedLot.BackLotName);
	ui->lineEditLotName2->setText(LoadedLot.BackLotID);
}

void	ShowReviewMasterNameForm::ResizeAction()
{
	ui->WholeLayout->resize(width(),height());
}
