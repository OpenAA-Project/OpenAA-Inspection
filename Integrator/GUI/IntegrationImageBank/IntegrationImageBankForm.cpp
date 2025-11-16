#include "IntegrationImageBankResource.h"
#include "IntegrationImageBankForm.h"
#include "ui_IntegrationImageBankForm.h"
#include "IntegrationImageBank.h"
#include "XGeneralFunc.h"
#include "XCriticalFunc.h"

extern  const	char	*sRoot;
extern  const	char	*sName;

IntegrationImageBankForm::IntegrationImageBankForm(LayersBase *Base,IntegrationImageBank *p ,QWidget *parent) :
    QWidget(parent),ServiceForLayers(Base)
    ,Parent(p)
    ,ui(new Ui::IntegrationImageBankForm)
{
    ui->setupUi(this);
    LangSolver.SetUI(this);

    ui->pushButtonBankON        ->setChecked(Parent->BootON);
    ui->toolButtonStoreOnlyOK   ->setChecked(Parent->StoreOnlyOK);
    ui->toolButtonStoreOnlyNG   ->setChecked(Parent->StoreOnlyNG);
    ui->spinBoxCount            ->setValue  (Parent->ListCount);

    ShowGrid();
}

IntegrationImageBankForm::~IntegrationImageBankForm()
{
    delete ui;
}

void IntegrationImageBankForm::ShowGrid(void)
{
    CmdReqImageBankGridList Cmd(GetLayersBase());
    Parent->TransmitDirectly(&Cmd);
    GridList=Cmd.GridList;

    int	N=GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveCount();
    ui->tableWidgetImages->setColumnCount(N+1);
    QStringList HLabelList;
    HLabelList.append(LangSolver.GetString(IntegrationImageBankForm_LS,LID_0)/*"InspectionID"*/);
    for(int SlaveNo=0;SlaveNo<N;SlaveNo++){
        EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
        if(m!=NULL){
            HLabelList.append(m->GetMachineName());
        }
    }
    ui->tableWidgetImages->setHorizontalHeaderLabels(HLabelList);

    int RowCount=GridList.GetCount();
    ui->tableWidgetImages->setRowCount(RowCount);
    int Row=0;
    for(ListImageBankPointerContainer *s=GridList.GetFirst();s!=NULL;s=s->GetNext(),Row++){
        ListImageBankPointer   *p=s->NPListPack<ListImageBankPointer>::GetFirst();
        ::SetDataToTable(ui->tableWidgetImages, 0, Row, QString::number(p->Pointer->InspectionID));

        for(int SlaveNo=0;SlaveNo<N;SlaveNo++){
            ListImageBankPointer *q;
             for(q=p;q!=NULL;q=q->GetNext()){
                 if(q->Pointer->SlaveID==SlaveNo){
                     break;
                 }
             }
             if(q!=NULL){
                 if(q->Pointer->ResultOK==true){
                    ::SetDataToTable(ui->tableWidgetImages, 1+SlaveNo, Row, QString(LangSolver.GetString(IntegrationImageBankForm_LS,LID_1)/*"OK"*/));
                 }
                 else{
                    ::SetDataToTable(ui->tableWidgetImages, 1+SlaveNo, Row, QString(LangSolver.GetString(IntegrationImageBankForm_LS,LID_2)/*"NG"*/));
                 }
             }
             else{
                 ::SetDataToTable(ui->tableWidgetImages, 1+SlaveNo, Row, QString(/**/""));
             }
        }
    }
}

void IntegrationImageBankForm::on_tableWidgetImages_doubleClicked(const QModelIndex &index)
{
    int Row=ui->tableWidgetImages->currentRow();
    if(Row<0)
        return;
    ListImageBankPointerContainer *d=GridList[Row];
    if(d==NULL)
        return;
    IntList SlaveList;
    int	N=GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveCount();
    for(int SlaveNo=0;SlaveNo<N;SlaveNo++){
        ListImageBankPointer *q;
        for(q=d->NPListPack<ListImageBankPointer>::GetFirst();q!=NULL;q=q->GetNext()){
            if(q->Pointer->SlaveID==SlaveNo){
                break;
            }
        }
        if(q!=NULL){
	        IntegrationReqImageBankSwitch	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
            RCmd.LoadedID=q->Pointer->LoadedID;
    	    if(RCmd.Send(NULL,SlaveNo,0)==true){
                SlaveList.Add(SlaveNo);
            }
        }
    }
	DWORD	t=::GetComputerMiliSec();
	while((::GetComputerMiliSec()-t)<GetParamGlobal()->MaxInspectMilisec){
		for(IntClass *v=SlaveList.GetFirst();v!=NULL;v=v->GetNext()){
			if(GetLayersBase()->HasReceivedIntegrationAck(v->GetValue())==true){
				SlaveList.RemoveList(v);
				break;
			}
		}
		if(SlaveList.GetCount()==0){
			break;
		}
	}
    Parent->BroadcastShowInPlayer();
}

void IntegrationImageBankForm::on_pushButtonCountSet_clicked()
{
    int	N=GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveCount();

    for(int SlaveNo=0;SlaveNo<N;SlaveNo++){
	    IntegrationSetStateImageBank	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
        RCmd.ONMode         =ui->pushButtonBankON       ->isChecked();
        RCmd.StoreOnlyOK    =ui->toolButtonStoreOnlyOK  ->isChecked();
        RCmd.StoreOnlyNG    =ui->toolButtonStoreOnlyOK  ->isChecked();
        RCmd.ListCount      =ui->spinBoxCount           ->value();
	    RCmd.Send(NULL,SlaveNo,0);
    }
}

void IntegrationImageBankForm::on_pushButtonClear_clicked()
{
    int	N=GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveCount();

    for(int SlaveNo=0;SlaveNo<N;SlaveNo++){
	    IntegrationSetImageBankClear	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
	    RCmd.Send(NULL,SlaveNo,0);
    }
}

void IntegrationImageBankForm::on_pushButtonClose_clicked()
{
    close();
}

void IntegrationImageBankForm::on_toolButtonStoreOnlyOK_clicked()
{
    on_pushButtonCountSet_clicked();
}

void IntegrationImageBankForm::on_toolButtonStoreOnlyNG_clicked()
{
    on_pushButtonCountSet_clicked();
}

void IntegrationImageBankForm::on_pushButtonBankON_clicked()
{
    ui->frameStore->setEnabled(ui->pushButtonBankON->isChecked());
    on_pushButtonCountSet_clicked();
}
