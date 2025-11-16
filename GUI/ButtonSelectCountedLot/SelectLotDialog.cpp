#include "SelectLotDialog.h"
#include "ui_SelectLotDialog.h"
#include "XGeneralFunc.h"
#include "XRememberer.h"

void	SelectLotFormForDialog::TxSync(QBuffer &Buff)
{
	ParentDialog->LoadFromWindow();
	::Save(&Buff,ParentDialog->LotCountNumber);
	SelectLotForm::TxSync(Buff);
}

SelectLotDialog::SelectLotDialog(LayersBase *Base,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectLotDialog),ServiceForLayers(Base)
{
    ui->setupUi(this);
	SelectLot=new SelectLotFormForDialog(GetLayersBase(),this,ui->frame,parent);
	SelectLot->move(0,0);

	connect(SelectLot,SIGNAL(SignalClose()),this,SLOT(SlotClose()));
	ui->spinBoxLotCountNumber	->setValue(ControlRememberer::GetInt(ui->spinBoxLotCountNumber,50));
}

SelectLotDialog::~SelectLotDialog()
{
    delete ui;
}
void	SelectLotDialog::LoadFromWindow(void)
{
	LotCountNumber=ui->spinBoxLotCountNumber->value();
}
void	SelectLotDialog::SlotClose()
{
	LotCountNumber=ui->spinBoxLotCountNumber->value();

	RetMode				=SelectLot->RetMode;
	SelectedLotAutoCount=SelectLot->SelectedLotAutoCount;
	SelectedLotID		=SelectLot->SelectedLotID;
	SelectedLotName		=SelectLot->SelectedLotName;
	SelectedLastUpdated	=SelectLot->SelectedLastUpdated;
	SelectedRemark		=SelectLot->SelectedRemark;

	ControlRememberer::SetValue(ui->spinBoxLotCountNumber ,ui->spinBoxLotCountNumber->value());

	close();
}

bool	SelectLotDialog::RxSync(QByteArray &f)
{
	QBuffer	Buff(&f);
	Buff.open(QIODevice::ReadWrite);

	bool	ret=SelectLot->RxSync(Buff);
	if(ret==false)
		return false;

	if(::Load(&Buff,LotCountNumber)==false)
		return false;

	SelectedLotAutoCount=SelectLot->SelectedLotAutoCount;
	SelectedLotID		=SelectLot->SelectedLotID;
	SelectedLotName		=SelectLot->SelectedLotName;
	SelectedLastUpdated	=SelectLot->SelectedLastUpdated;
	SelectedRemark		=SelectLot->SelectedRemark;
	return true;
}

void	LotInformationWithCounted::ExecuteEveryInspectInMaster(int InspectionID)
{
}
void	LotInformationWithCounted::ExecuteEveryInspectInSlave(int InspectionID,int Phase ,int Page)
{
}
