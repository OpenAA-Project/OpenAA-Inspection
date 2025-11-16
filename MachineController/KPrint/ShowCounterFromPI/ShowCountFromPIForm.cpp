#include "ShowCountFromPIResource.h"
#include "ShowCountFromPIForm.h"
#include "ui_ShowCountFromPIForm.h"
#include "XGeneralFunc.h"
#include "CartonMenuForm.h"
#include "WindowMismatchForm.h"

ShowCountFromPIForm::ShowCountFromPIForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::ShowCountFromPIForm)
{
    ui->setupUi(this);
    LangSolver.SetUI(this);
    WindowMismatchFormInst  =NULL;

    CartonProp  =NULL;
    TM.setInterval(1000);
    TM.setSingleShot(false);
    connect(&TM,SIGNAL(timeout()),this,SLOT(SlotTimeOut()));
}

ShowCountFromPIForm::~ShowCountFromPIForm()
{
    delete ui;
}

void	ShowCountFromPIForm::ReadyParam(void)
{
	CartonProp=(CartonMenuForm *)GetLayersBase()->FindByName(/**/"KidaPrint" ,/**/"CartonMenu" ,/**/"");
     TM.start();
}
void	ShowCountFromPIForm::ResizeAction()
{
    ui->tableWidget->setGeometry(0,0,width(),height());
    ::SetColumnWidthInTable(ui->tableWidget ,0, 70);
    ::SetColumnWidthInTable(ui->tableWidget ,1, 30);
}
void	ShowCountFromPIForm::TransmitDirectly(GUIDirectMessage *packet)
{
}
void	ShowCountFromPIForm::SpecifiedDirectly(SpecifiedBroadcaster *v)
{
    CmdChangeLotID  *CmdChangeLotIDVar=dynamic_cast<CmdChangeLotID *>(v);
    if(CmdChangeLotIDVar!=NULL){
        if(CartonProp!=NULL){
            CmdResetCounter   Cmd(GetLayersBase());
            CartonProp->TransmitDirectly(&Cmd);
        }
        return;
    }
    CmdClearCounter *CmdClearCounterVar=dynamic_cast<CmdClearCounter *>(v);
    if(CmdClearCounterVar!=NULL){
        if(CartonProp!=NULL){
            CmdResetCounter   Cmd(GetLayersBase());
            CartonProp->TransmitDirectly(&Cmd);
        }
        return;
    }
}

void    ShowCountFromPIForm::SlotTimeOut()
{
    if(CartonProp!=NULL){
        CmdRequestCounter   Cmd(GetLayersBase());
        CartonProp->TransmitDirectly(&Cmd);
        if(Cmd.Ret==true){
            ::SetDataToTable(ui->tableWidget,0,0, QString::number(Cmd.TotalCount));
            ::SetDataToTable(ui->tableWidget,0,1, QString::number(Cmd.OKCount));
            ::SetDataToTable(ui->tableWidget,0,2, QString::number(Cmd.NGCount));
            ::SetDataToTable(ui->tableWidget,0,3, QString::number(Cmd.TMCount));

            if(Cmd.Mismatch==true){
                ShowMismatch();
            }
        }
    }
}

void    ShowCountFromPIForm::ShowMismatch(void)
{
    if(WindowMismatchFormInst==NULL){
        WindowMismatchFormInst=new WindowMismatchForm();
    }
    WindowMismatchFormInst->show();
    WindowMismatchFormInst->raise();
}

