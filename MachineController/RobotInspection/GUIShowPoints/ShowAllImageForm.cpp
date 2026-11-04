#include "ShowAllImageForm.h"
#include "ui_ShowAllImageForm.h"
#include "GUIShowPointsButtonForm.h"
#include "XCameraRobotCommon.h"
#include "XCameraClass.h"
#include "XGeneralFunc.h"
#include "ListSelectFixedPage.h"

ShowAllImageForm::ShowAllImageForm(GUIShowPointsButtonForm *P ,LayersBase *Base,QWidget *parent)
    : QWidget(parent)
    ,ServiceForLayers(Base)
    ,Parent(P)
    , ui(new Ui::ShowAllImageForm)
{
    ui->setupUi(this);

    CmdReqJointFrameClass   Cmd(GetLayersBase());
    Parent->Cam[0]->TransmitDirectly(&Cmd);
    
    ui->tableWidget->setRowCount(Cmd.DimCount);
    for(int row=0;row<Cmd.DimCount;row++){
        ::SetDataToTable(ui->tableWidget,0, row, QString::number(Cmd.Dim[row].CurrentPos[0]));
        ::SetDataToTable(ui->tableWidget,1, row, QString::number(Cmd.Dim[row].CurrentPos[1]));
        ::SetDataToTable(ui->tableWidget,2, row, QString::number(Cmd.Dim[row].CurrentPos[2]));
        ::SetDataToTable(ui->tableWidget,3, row, QString::number(Cmd.Dim[row].CurrentPos[3]));
        ::SetDataToTable(ui->tableWidget,4, row, QString::number(Cmd.Dim[row].CurrentPos[4]));
        ::SetDataToTable(ui->tableWidget,5, row, QString::number(Cmd.Dim[row].CurrentPos[5]));
    }
}

ShowAllImageForm::~ShowAllImageForm()
{
    delete ui;
}

void ShowAllImageForm::showEvent(QShowEvent *event)
{
    CmdLockCapture   LCmd(GetLayersBase());
    Parent->Cam[0]->TransmitDirectly(&LCmd);
}


void ShowAllImageForm::closeEvent(QCloseEvent *event)
{
    CmdUnlockCapture   Cmd(GetLayersBase());
    Parent->Cam[0]->TransmitDirectly(&Cmd);
}

void ShowAllImageForm::on_tableWidget_cellDoubleClicked(int row, int column)
{
    CmdImageToTarget   Cmd(GetLayersBase());
    Cmd.TargetPhase=0;

    GUIFormBase *f=GetLayersBase()->FindByName(/**/"List",/**/"SelectFixedPage",/**/"");
	CmdGetCurrentPage	LCmd(GetLayersBase());
	if(f!=NULL){
		f->TransmitDirectly(&LCmd);
	}
    if(LCmd.CurrentPage<0)
        LCmd.CurrentPage=0;

    Cmd.TargetPage  =LCmd.CurrentPage;
    Cmd.Index=row;
    Parent->Cam[0]->TransmitDirectly(&Cmd);
}


void ShowAllImageForm::resizeEvent(QResizeEvent *event)
{
     ui->tableWidget->resize(width(),height());
     ::SetColumnWidthInTable(ui->tableWidget,0, 14);
     ::SetColumnWidthInTable(ui->tableWidget,1, 14);
     ::SetColumnWidthInTable(ui->tableWidget,2, 14);
     ::SetColumnWidthInTable(ui->tableWidget,3, 14);
     ::SetColumnWidthInTable(ui->tableWidget,4, 14);
     ::SetColumnWidthInTable(ui->tableWidget,5, 14);
}
