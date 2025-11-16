#include "MinMaxDialog.h"
#include "ui_MinMaxDialog.h"
#include "SelectLibForValidationForm.h"
#include "XCheckDataValidation.h"
#include "XPropertyCheckDataValidationPacket.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

MinMaxDialog::MinMaxDialog(LayersBase *Base ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(Base),
    ui(new Ui::MinMaxDialog)
{
    ui->setupUi(this);

    SelectedLibType =-1;
    SelectedLibID   =-1;

    SelectLibPanel=new SelectLibForValidationForm(Base);
    SelectLibPanel->setParent(ui->frame);
    SelectLibPanel->move(0,0);
    connect(SelectLibPanel,SIGNAL(SignalSelectedLib(int ,int)),this,SLOT(SlotSelectedLib(int,int)));

    ui->pushButtonModify    ->setVisible(false);
    ui->pushButtonDelete    ->setVisible(false);

    ::SetColumnWidthInTable(ui->tableWidget ,0, 93);
}

MinMaxDialog::~MinMaxDialog()
{
    delete ui;
}

void    MinMaxDialog::SetCurrentItem(const CheckDataValidationCheckMinMaxThreshold *RThr)
{
    ui->pushButtonModify    ->setVisible(true);
    ui->pushButtonDelete    ->setVisible(true);

    SelectedLibType =RThr->LibType;
    SelectedLibID   =RThr->LibID;

    SelectLibPanel->Initial(SelectedLibType, SelectedLibID);

    ui->doubleSpinBoxMinValue  ->setValue(RThr->Value.MinValueDouble);
    ui->doubleSpinBoxMaxValue  ->setValue(RThr->Value.MaxValueDouble);
    ui->comboBoxBool->setCurrentIndex(RThr->Value.FixedValueBool==true?0:1);
    ui->spinBoxMinValue         ->setValue(RThr->Value.MinValueInt64);
    ui->spinBoxMaxValue         ->setValue(RThr->Value.MaxValueInt64);
    SlotSelectedLib(SelectedLibType,SelectedLibID);
    ::SetCurrentRow(ui->tableWidget,RThr->ParamID);
}

void    MinMaxDialog::GetCurrentItem(CheckDataValidationCheckMinMaxThreshold *WThr)
{
    WThr->LibType=SelectedLibType;
    WThr->LibID  =SelectedLibID;
    WThr->Value.MinValueDouble  =ui->doubleSpinBoxMinValue ->value();
    WThr->Value.MaxValueDouble  =ui->doubleSpinBoxMaxValue ->value();
    WThr->Value.FixedValueBool  =ui->comboBoxBool->currentIndex()==0?true:false;
    WThr->Value.MinValueInt64   =ui->spinBoxMinValue ->value();
    WThr->Value.MaxValueInt64   =ui->spinBoxMaxValue ->value();
    int CurrentRow=ui->tableWidget->currentRow();
    if(CurrentRow<0)
        return;
    WThr->ParamID=CurrentRow;
}

void    MinMaxDialog::SlotSelectedLib(int LibType,int LibID)
{
    ui->spinBoxLibID    ->setValue(LibID);
    QString LibName=GetLayersBase()->GetLibraryName(LibType,LibID);
    ui->lineEditLibName ->setText(LibName);
    SelectedLibType =LibType;
    SelectedLibID   =LibID;

    LContainer.RemoveAll();
    int GlobalPage=0;
    GUICmdReqThresholdMemberString  RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
    GUICmdAckThresholdMemberString  SCmd(GetLayersBase(),sRoot,sName,GlobalPage);
    RCmd.LibType=SelectedLibType;
    RCmd.LibID  =SelectedLibID;
    if(RCmd.Send(GlobalPage,0,SCmd)==true){
        LContainer=SCmd.LContainer;
    }
    int Row=0;
    ui->tableWidget->setRowCount(LContainer.GetCount());
    for(ThresholdMemberList *r=LContainer.GetFirst();r!=NULL;r=r->GetNext(),Row++){
        ::SetDataToTable(ui->tableWidget, 0, Row,r->MemberName);
    }

}

void MinMaxDialog::on_pushButtonCreateNew_clicked()
{
    int CurrentRow=ui->tableWidget->currentRow();
    if(CurrentRow<0)
        return;
    done(1);
}

void MinMaxDialog::on_pushButtonModify_clicked()
{
    int CurrentRow=ui->tableWidget->currentRow();
    if(CurrentRow<0)
        return;
    done(2);
}

void MinMaxDialog::on_pushButtonDelete_clicked()
{
    done(3);
}

void MinMaxDialog::on_pushButtonClose_clicked()
{
    done(-1);
}


void MinMaxDialog::on_tableWidget_clicked(const QModelIndex &index)
{
    int CurrentRow=ui->tableWidget->currentRow();
    if(CurrentRow<0)
        return;
    ThresholdMemberList *r=LContainer[CurrentRow];
    if(r!=NULL){
        switch(r->VType){
			case _DT_bool			:   ui->stackedWidget->setCurrentIndex(1);  break;
			case _DT_byte			:   
                ui->stackedWidget->setCurrentIndex(2);
                ui->spinBoxMinValue->setMinimum(0);
                ui->spinBoxMaxValue->setMaximum(255);
                break;
			case _DT_char			:
                ui->stackedWidget->setCurrentIndex(2);
                ui->spinBoxMinValue->setMinimum(-128);
                ui->spinBoxMaxValue->setMaximum(127);
                break;
            case _DT_short			:
                ui->stackedWidget->setCurrentIndex(2);
                ui->spinBoxMinValue->setMinimum(-32768);
                ui->spinBoxMaxValue->setMaximum(32767);
                break;
			case _DT_ushort			:
                ui->stackedWidget->setCurrentIndex(2);
                ui->spinBoxMinValue->setMinimum(0);
                ui->spinBoxMaxValue->setMaximum(65535);
                break;
			case _DT_int			:
                ui->stackedWidget->setCurrentIndex(2);
                ui->spinBoxMinValue->setMinimum(-2147483648);
                ui->spinBoxMaxValue->setMaximum(2147483647);
                break;
			case _DT_int32			:
                ui->stackedWidget->setCurrentIndex(2);
                ui->spinBoxMinValue->setMinimum(-2147483648);
                ui->spinBoxMaxValue->setMaximum(2147483647);
                break;
			case _DT_uint32			:
                ui->stackedWidget->setCurrentIndex(2);
                ui->spinBoxMinValue->setMinimum(0);
                ui->spinBoxMaxValue->setMaximum(2147483647);    //4294967295);
                break;
			case _DT_int64			:
                ui->stackedWidget->setCurrentIndex(2);
                ui->spinBoxMinValue->setMinimum(-2147483648);
                ui->spinBoxMaxValue->setMaximum(2147483647);
                break;
			case _DT_uint64			:
                ui->stackedWidget->setCurrentIndex(2);
                ui->spinBoxMinValue->setMinimum(0);
                ui->spinBoxMaxValue->setMaximum(2147483647);    //4294967295);
                break;
			case _DT_QString		:
                ui->stackedWidget->setCurrentIndex(0);
                break;
            case _DT_double			:
                ui->stackedWidget->setCurrentIndex(0);
                break;
			case _DT_longdouble		:
                ui->stackedWidget->setCurrentIndex(0);
                break;
			case _DT_float			:
                ui->stackedWidget->setCurrentIndex(0);
                break;
        }
    }
}

