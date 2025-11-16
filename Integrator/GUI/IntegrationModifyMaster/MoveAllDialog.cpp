#include "IntegrationModifyMasterResource.h"
#include "MoveAllDialog.h"
#include "ui_MoveAllDialog.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"

extern  const	char	*sRoot;
extern  const	char	*sName;

MoveAllDialog::MoveAllDialog(LayersBase *Base ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(Base),
    ui(new Ui::MoveAllDialog)
{
    ui->setupUi(this);

    for(int i=0;i<sizeof(Button)/sizeof(Button[0]);i++){
        Button[i]=NULL;
    }

    ui->toolButtonMachine->deleteLater();
    ui->toolButtonMachine=NULL;
    SlaveNumbers.RemoveAll();

    IntegrationBase *IBase=GetLayersBase()->GetIntegrationBasePointer();
    int N=IBase->GetIntegrationSlaveCount();
    if(N>0){
        int W=ui->frame->width()/N;
        for(int SlaveNo=0;SlaveNo<N;SlaveNo++){
            Button[SlaveNo]=new MachineButton(SlaveNo);
            EachMaster	*m=IBase->GetMaster(SlaveNo);
            Button[SlaveNo]->setParent(ui->frame);
            Button[SlaveNo]->setGeometry(W*SlaveNo,0,W-2,ui->frame->height()-2);
            Button[SlaveNo]->setText(m->GetMachineName());
            Button[SlaveNo]->setCheckable(true);
            Button[SlaveNo]->setAutoExclusive(false);
        }
    }
}

MoveAllDialog::~MoveAllDialog()
{
    delete ui;
}

void MoveAllDialog::on_pushButtonGo_clicked()
{
    IntegrationBase *IBase=GetLayersBase()->GetIntegrationBasePointer();
    int N=IBase->GetIntegrationSlaveCount();
    for(int SlaveNo=0;SlaveNo<N;SlaveNo++){
        if(Button[SlaveNo]!=NULL){
            if(Button[SlaveNo]->isChecked()==true){
                SlaveNumbers.Add(SlaveNo);
            }
        }
    }
    Mastered=ui->checkBoxMaster->isChecked();
    Targeted=ui->checkBoxTarget->isChecked();
    XDir    =ui->spinBoxXDir->value();
    YDir    =ui->spinBoxYDir->value();

    if(SlaveNumbers.GetCount()>0){
        for(IntClass *v=SlaveNumbers.GetFirst();v!=NULL;v=v->GetNext()){
            int SlaveNo=v->GetValue();
            EachMaster  *m=IBase->GetMaster(SlaveNo);
            if(m!=NULL){
                m->MoveAll(Mastered,Targeted,XDir,YDir);
            }
            IntegrationMoveAll  RCmd(GetLayersBase(),sRoot,sName ,SlaveNo);
            RCmd.Mastered=Mastered;
            RCmd.Targeted=Targeted;
            RCmd.XDir    =XDir    ;
            RCmd.YDir    =YDir    ;
            RCmd.Send(NULL,SlaveNo,0);
        }
    }

    done(true);
}


void MoveAllDialog::on_pushButtonCancel_clicked()
{
    done(false);
}

//================================================================================
IntegrationMoveAll::IntegrationMoveAll(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationMoveAll::Load(QIODevice *f)
{
    if(::Load(f,Mastered)==false)  return false;
    if(::Load(f,Targeted)==false)  return false;
    if(::Load(f,XDir    )==false)  return false;
    if(::Load(f,YDir    )==false)  return false;
    return true;
}
bool	IntegrationMoveAll::Save(QIODevice *f)
{
    if(::Save(f,Mastered)==false)  return false;
    if(::Save(f,Targeted)==false)  return false;
    if(::Save(f,XDir    )==false)  return false;
    if(::Save(f,YDir    )==false)  return false;
    return true;
}

void	IntegrationMoveAll::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
    GUIFormBase *f=GetLayersBase()->FindByName(/**/"Button",/**/"MoveAll",/**/"");
    if(f!=NULL){
		QStringList Args;
        if(Mastered==true)
            Args.append(/**/"true");
        else
            Args.append(/**/"false");

        if(Targeted==true)
            Args.append(/**/"true");
        else
            Args.append(/**/"false");

        Args.append(QString::number(XDir));
        Args.append(QString::number(YDir));
        Args.append(/**/"-1");

		bool ExeReturn;
		f->ExecuteMacro(/**/"Move", Args, ExeReturn);
    }
}

