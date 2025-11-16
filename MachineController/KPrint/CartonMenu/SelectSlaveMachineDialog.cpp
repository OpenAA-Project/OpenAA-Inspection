#include "CartonMenuResource.h"
#include "SelectSlaveMachineDialog.h"
#include "ui_SelectSlaveMachineDialog.h"
#include "XIntegrationBase.h"
#include "XRememberer.h"

SelectSlaveMachineDialog::SelectSlaveMachineDialog(LayersBase *Base ,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(Base)
    ,ui(new Ui::SelectSlaveMachineDialog)
{
    ui->setupUi(this);
    LangSolver.SetUI(this);

    SelectedSlaveNoList.RemoveAll();
    IntegrationBase *IBase=GetLayersBase()->GetIntegrationBasePointer();
    if(IBase!=NULL){
        int N=IBase->GetIntegrationSlaveCount();

        {
            int X1=ui->checkBoxSlave->geometry().left();
            int Y =ui->checkBoxSlave->geometry().top();
            int W =ui->checkBoxSlave->width();
            int H =ui->checkBoxSlave->height();

            delete  ui->checkBoxSlave;
            ui->checkBoxSlave=NULL;

            for(int i=0;i<N;i++){
                CBoxDim[i]=new QCheckBox(this);
                CBoxDim[i]->setCheckable(true);
                CBoxDim[i]->setGeometry(X1,Y+i*(H+4),W,H);
                EachMaster	*m=IBase->GetMaster(i);
                if(m!=NULL){
                    CBoxDim[i]->setText(m->GetMachineName());
                }
                CBoxDim[i]->setObjectName(QString(/**/"CBoxSlave")+QString::number(i));
                CBoxDim[i]->setChecked(ControlRememberer::GetBool(CBoxDim[i]));
            }
        }
        {
            int X1=ui->checkBoxReGenSlave->geometry().left();
            int Y =ui->checkBoxReGenSlave->geometry().top();
            int W =ui->checkBoxReGenSlave->width();
            int H =ui->checkBoxReGenSlave->height();

            delete  ui->checkBoxReGenSlave;
            ui->checkBoxReGenSlave=NULL;

            for(int i=0;i<N;i++){
                CBoxDimRGen[i]=new QCheckBox(this);
                CBoxDimRGen[i]->setCheckable(true);
                CBoxDimRGen[i]->setGeometry(X1,Y+i*(H+4),W,H);
                //EachMaster	*m=IBase->GetMaster(i);
                CBoxDimRGen[i]->setText(LangSolver.GetString(SelectSlaveMachineDialog_LS,LID_235)/*"蜀咲函謌�*/);
                CBoxDimRGen[i]->setObjectName(QString(/**/"CBoxRegen")+QString::number(i));
                CBoxDimRGen[i]->setChecked(ControlRememberer::GetBool(CBoxDimRGen[i]));
            }
        }
        {
            int X1=ui->checkBoxKeepMark->geometry().left();
            int Y =ui->checkBoxKeepMark->geometry().top();
            int W =ui->checkBoxKeepMark->width();
            int H =ui->checkBoxKeepMark->height();

            delete  ui->checkBoxKeepMark;
            ui->checkBoxKeepMark=NULL;

            for(int i=0;i<N;i++){
                CBoxDimKeepMark[i]=new QCheckBox(this);
                CBoxDimKeepMark[i]->setCheckable(true);
                CBoxDimKeepMark[i]->setGeometry(X1,Y+i*(H+4),W,H);
                //EachMaster	*m=IBase->GetMaster(i);
                CBoxDimKeepMark[i]->setText(LangSolver.GetString(SelectSlaveMachineDialog_LS,LID_234)/*"Keep Mark"*/);
                CBoxDimKeepMark[i]->setObjectName(QString(/**/"CBoxKeepMark")+QString::number(i));
                CBoxDimKeepMark[i]->setChecked(ControlRememberer::GetBool(CBoxDimKeepMark[i]));
            }
        }
    }
}

SelectSlaveMachineDialog::~SelectSlaveMachineDialog()
{
    delete ui;
}

void SelectSlaveMachineDialog::on_pushButtonOK_clicked()
{
    IntegrationBase *IBase=GetLayersBase()->GetIntegrationBasePointer();
    if(IBase!=NULL){
        int N=IBase->GetIntegrationSlaveCount();
        for(int i=0;i<N;i++){
            ControlRememberer::SetValue(CBoxDim[i]);
            if(CBoxDim[i]->isChecked()==true){
                SelectedSlaveNoList.Add(i);
            }
        }
        for(int i=0;i<N;i++){
            ControlRememberer::SetValue(CBoxDimRGen[i]);
            if(CBoxDimRGen[i]->isChecked()==true){
                ReGenList.Add(i);
            }
        }
         for(int i=0;i<N;i++){
            ControlRememberer::SetValue(CBoxDimKeepMark[i]);
            if(CBoxDimKeepMark[i]->isChecked()==true){
                KeepMarkList.Add(i);
            }
         }
    }
    ResetSwitchPhase=ui->PushButtonResetSwitchPhase->isChecked();
    ResetMakeAverage=ui->PushButtonResetMakeAverage->isChecked();
    done(true);
}


void SelectSlaveMachineDialog::on_pushButtonCancel_clicked()
{
    done(false);
}

