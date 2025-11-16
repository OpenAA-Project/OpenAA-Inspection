#include "ServiceLibResource.h"
#include "CopyAlgorithmDialog.h"
#include "ui_CopyAlgorithmDialog.h"
#include "XDataInLayer.h"
#include "XIntegrationBase.h"
#include "XIntegrationSimpleImagePanel.h"

SlaveButton::SlaveButton(int _SlaveNo)
{
    SlaveNo=_SlaveNo;
    bool    Ret=connect(this,SIGNAL(clicked(bool)),this,SLOT(SlotClicked(bool)));

}
SlaveButton::~SlaveButton(void)
{
}

void    SlaveButton::SlotClicked(bool)
{
    emit    SignalClicked(SlaveNo);
}

CopyAlgorithmDialog::CopyAlgorithmDialog(LayersBase *base
                                        ,IntegrationAlgoSimpleImagePanel *P
                                        ,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(base)
    ,Parent(P)
    ,ui(new Ui::CopyAlgorithmDialog)
{
    ui->setupUi(this);
    LangLibSolver.SetUI(this);

    int OwnSlaveNo=Parent->GetSlaveNo();

    memset(RxSlaveButton,0,sizeof(RxSlaveButton));
    int SlaveCount=GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveCount();
    if(SlaveCount>0){
        int H=ui->stackedWidget->height()-20;
        int Hn=H/SlaveCount;
        int n=0;
        for(int i=0;i<SlaveCount;i++){
            if(i!=OwnSlaveNo){
                RxSlaveButton[n]=new SlaveButton(i);
                RxSlaveButton[n]->setParent(ui->stackedWidget->widget(0));
                RxSlaveButton[n]->setGeometry(10,10+Hn*i,ui->stackedWidget->width()-20,Hn);
                EachMaster  *m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(i);
                if(m!=NULL){
                    RxSlaveButton[n]->setText(m->GetMachineName());
                }
                bool    Ret=connect(RxSlaveButton[n],SIGNAL(SignalClicked(int)),this,SLOT(SlotRxClicked(int)));
                n++;
            }
        }
    }
    TxButtonDim[0]=ui->pushButtonTxPC1;
    TxButtonDim[1]=ui->pushButtonTxPC2;
    TxButtonDim[2]=ui->pushButtonTxPC3;
    TxButtonDim[3]=ui->pushButtonTxPC4;
    int n=0;
    for(int i=0;i<SlaveCount && i<4;i++){
        if(i!=OwnSlaveNo){
            EachMaster  *m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(i);
            if(m!=NULL){
                TxButtonDim[n]->setText(m->GetMachineName());
                n++;
            }
        }
    }
    for(int i=n;i<4;i++){
        TxButtonDim[i]->hide();
    }
    ui->toolButtonRx->setChecked(true);
    ui->stackedWidget->setCurrentIndex(0);
}

CopyAlgorithmDialog::~CopyAlgorithmDialog()
{
    delete ui;

    for(int i=0;i<sizeof(RxSlaveButton)/sizeof(RxSlaveButton[0]);i++){
        if(RxSlaveButton[i]!=NULL){
            RxSlaveButton[i]->deleteLater();
            RxSlaveButton[i]=NULL;
        }
    }
}

void CopyAlgorithmDialog::on_toolButtonRx_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void CopyAlgorithmDialog::on_toolButtonTx_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void    CopyAlgorithmDialog::SlotRxClicked(int SlaveNo)
{
    Parent->CopyFromSlave(SlaveNo);
    close();
}
void CopyAlgorithmDialog::on_pushButtonExeTx_clicked()
{
    int OwnSlaveNo=Parent->GetSlaveNo();
    int SlaveCount=GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveCount();
    IntList DestSlaveList;
    int     n=0;
    for(int i=0;i<SlaveCount && i<4;i++){
        if(i!=OwnSlaveNo){
            EachMaster  *m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(i);
            if(m!=NULL){
                if(TxButtonDim[n]->isChecked()==true){
                    DestSlaveList.Add(i);
                }
            }
            n++;
        }
    }
    Parent->CopyToSlave(DestSlaveList);
    close();
}


