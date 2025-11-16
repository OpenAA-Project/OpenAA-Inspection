#include "XTypeDef.h"
#include "PasswordDropper.h"
#include "ui_PasswordDropper.h"
#include <QDrag>
#include <QMimeData>
#include "XDataInLayer.h"
#include "XPassword.h"
#include "XGeneralFunc.h"
#include "CreateClassForm.h"
#include "CreatePasswordForm.h"
#include "SelectObjectForm.h"
#include "XGUIFormBase.h"
#include "XPasswordQWidget.h"
#include <QMessageBox>


void DragLabel::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        QDrag *drag = new QDrag(this);
        QMimeData *mimeData = new QMimeData;

        mimeData->setText("PasswordTarget");
        drag->setMimeData(mimeData);
        //drag->setPixmap(Qt::ReturnByValue);

        Qt::DropAction dropAction = drag->exec();
     }
}

PasswordDropper::PasswordDropper(LayersBase *Base,QWidget *parent) :
    QWidget(parent)
    ,ServiceForLayers(Base)
    ,ui(new Ui::PasswordDropper)
    
{
    ui->setupUi(this);
    dragLabel=new DragLabel(this);
    dragLabel->setText("Drag");
    dragLabel->setGeometry(ui->labelDrag->geometry());
    delete	ui->labelDrag;
    ui->labelDrag=NULL;

    ShowList();
    if(GetLayersBase()->GetPasswordHolder()->GetPasswordClassDataCount()!=0){
        ui->listWidgetClass->setCurrentRow(0);
        ClicklistWidgetClass();
    }
    ui->spinBoxExpiredTime->setValue(GetLayersBase()->GetPasswordHolder()->GetExpiredTimeSec());
}

PasswordDropper::~PasswordDropper()
{
    delete ui;
}

void PasswordDropper::ShowList(void)
{
    ui->listWidgetClass->clear();
    for(PasswordClass *c=GetLayersBase()->GetPasswordHolder()->GetPasswordClassDataFirst();c!=NULL;c=c->GetNext()){
        ui->listWidgetClass->addItem(c->GetClassName());
    }
    ClicklistWidgetClass();
}

void PasswordDropper::on_pushButtonSave_clicked()
{
    QString FileName=GetLayersBase()->LGetSaveFileName(0, "Save Password file");
    if(FileName.isEmpty()==false){
        QFile	FL(FileName);
        if(FL.open(QIODevice::ReadWrite)==true){
            GetLayersBase()->GetPasswordHolder()->SetExpiredTimeSec(ui->spinBoxExpiredTime->value());
            GetLayersBase()->GetPasswordHolder()->Save(&FL);
        }
    }
}

void PasswordDropper::on_pushButtonLoad_clicked()
{
    QString FileName=GetLayersBase()->LGetOpenFileName(0, "Load Password file");
    if(FileName.isEmpty()==false){
        QFile	FL(FileName);
        if(FL.open(QIODevice::ReadOnly)==true){
            if(GetLayersBase()->GetPasswordHolder()->Load(&FL)==true){
                ShowList();
                ui->spinBoxExpiredTime->setValue(GetLayersBase()->GetPasswordHolder()->GetExpiredTimeSec());
            }
        }
    }
}

void PasswordDropper::on_pushButtonSetDropFilter_clicked()
{
    NPListPack<PasswordFilterPointerList>	PasswordFilterPointerData;
    GetLayersBase()->GetPasswordHolder()->Setup(*GUIPack,PasswordFilterPointerData,this);
    for(PasswordFilterPointerList *p=PasswordFilterPointerData.GetFirst();p!=NULL;p=p->GetNext()){
        connect(p->IndexPoint,SIGNAL(SignalDropped(QObject*)),this,SLOT(SlotDropped (QObject*)));
    }
}

void PasswordDropper::on_listWidgetClass_clicked(const QModelIndex &)
{
    ClicklistWidgetClass();
}

void PasswordDropper::ClicklistWidgetClass(void)
{
    int	R=ui->listWidgetClass->currentRow();
    ui->listWidgetPassword->clear();
    ui->listWidgetControl->clear();
    if(R>=0){
        for(PasswordPass *c=GetLayersBase()->GetPasswordHolder()->GetPasswordPassDataFirst();c!=NULL;c=c->GetNext()){
            ui->listWidgetPassword->addItem(c->GetPassword());
        }
        for(PasswordInControl *c=GetLayersBase()->GetPasswordHolder()->GetPasswordInControlDataFirst();c!=NULL;c=c->GetNext()){
            ui->listWidgetControl->addItem(c->GetControlPathName());
        }
    }
}

void PasswordDropper::SlotDropped ( QObject * newTarget )
{
    QObject * hTarget=newTarget;

    for(;;){
        if(hTarget==NULL){
            SlotDroppedQWidget( newTarget );
            return;
        }
        if(dynamic_cast<GUIFormBase	*>(hTarget)!=NULL){
            break;
        }
        hTarget=hTarget->parent();
    }
    GUIFormBase *StartObject=dynamic_cast<GUIFormBase *>(hTarget);
    if(StartObject==NULL){
        return;
    }

    SelectObjectForm	DSelect(StartObject);

    if(DSelect.exec()==false)
        return;
    QString	ObjPath=DSelect.SelectedObjPath;

    std::shared_ptr<PasswordManager>	P=GetLayersBase()->GetPasswordHolder();
    /*
    QString	ObjPath;
    GetObjectPath(newTarget,ObjPath);
    */

    //PasswordInControl	*C=new PasswordInControl(GetPasswordClassID(),ObjPath,newTarget->objectName());
    QStringList	ObjPathList=ObjPath.split(QChar('/'));
    PasswordInControl	*C=new PasswordInControl(GetPasswordClassID(),ObjPath,ObjPathList[ObjPathList.count()-1]);
    C->SetControlMode(DSelect.ControlMode);
    PasswordInControl	*m=P->Search(C);
    if(m==NULL){
        P->AppendList(C);
        ClicklistWidgetClass();
    }
    else{
        delete	C;
    }
}

void PasswordDropper::SlotDroppedQWidget( QObject * newTarget )
{
    QObject * hTarget=newTarget;
    for(;;){
        if(hTarget==NULL){
            return;
        }
        if(dynamic_cast<PasswordInQWodget *>(hTarget)!=NULL){
            break;
        }
        hTarget=hTarget->parent();
    }
    QWidget *StartObject=dynamic_cast<QWidget *>(hTarget);
    if(StartObject==NULL){
        return;
    }

    SelectObjectForm	DSelect(StartObject);

    if(DSelect.exec()==false)
        return;
    QString	ObjPath=DSelect.SelectedObjPath;

    std::shared_ptr<PasswordManager>	P=GetLayersBase()->GetPasswordHolder();
    /*
    QString	ObjPath;
    GetObjectPath(newTarget,ObjPath);
    */

    //PasswordInControl	*C=new PasswordInControl(GetPasswordClassID(),ObjPath,newTarget->objectName());
    QStringList	ObjPathList=ObjPath.split(QChar('/'));
    PasswordInControl	*C=new PasswordInControl(GetPasswordClassID(),ObjPath,ObjPathList[ObjPathList.count()-1]);
    PasswordInControl	*m=P->Search(C);
    if(m==NULL){
        P->AppendList(C);
        ClicklistWidgetClass();
    }
    else{
        delete	C;
    }
}

int32	PasswordDropper::GetPasswordClassID(void)
{
    int	R=ui->listWidgetClass->currentRow();
    if(R<0){
        return -1;
    }
    PasswordClass *c=GetLayersBase()->GetPasswordHolder()->GetPasswordClassDataItem(R);
    if(c==NULL){
        return -1;
    }
    return c->GetPasswordClassID();
}




void PasswordDropper::on_pushButtonCreateClass_clicked()
{
    CreateClassForm	Q(this);
    if(Q.exec()==(int)true){
        GetLayersBase()->GetPasswordHolder()->AppendClass(Q.ClassName);
        ShowList();
    }
}

void PasswordDropper::on_pushButtonDeleteClass_clicked()
{
    int	R=ui->listWidgetClass->currentRow();
    if(R>=0){
        PasswordClass *c=GetLayersBase()->GetPasswordHolder()->GetPasswordClassDataItem(R);
        if(c!=NULL){
            if(QMessageBox::question ( 0, "Delete Class", "Delete class?",QMessageBox::Yes,QMessageBox::No)==QMessageBox::Yes){
                GetLayersBase()->GetPasswordHolder()->RemoveClass(c);
                delete	c;
                ShowList();
            }
        }
    }
}

void PasswordDropper::on_pushButtonCreatePassword_clicked()
{
    int	R=ui->listWidgetClass->currentRow();
    if(R>=0){
        PasswordClass *c=GetLayersBase()->GetPasswordHolder()->GetPasswordClassDataItem(R);
        if(c!=NULL){
            CreatePasswordForm	Q(this);
            if(Q.exec()==(int)true){
                GetLayersBase()->GetPasswordHolder()->AppendPassword(c,Q.Password);
                ClicklistWidgetClass();
            }
        }
    }
}

void PasswordDropper::on_pushButtonDeletPassword_clicked()
{
    int	R=ui->listWidgetClass->currentRow();
    if(R>=0){
        PasswordClass *c=GetLayersBase()->GetPasswordHolder()->GetPasswordClassDataItem(R);
        if(c!=NULL){
            int	Pn=ui->listWidgetPassword->currentRow();
            PasswordPass	*p=GetLayersBase()->GetPasswordHolder()->GetPasswordPassDataItem(Pn);
            if(p!=NULL){
                if(QMessageBox::question ( 0, "Delete Password", "Delete password?",QMessageBox::Yes,QMessageBox::No)==QMessageBox::Yes){
                    GetLayersBase()->GetPasswordHolder()->RemoveList(p);
                    delete	p;
                    ClicklistWidgetClass();
                }
            }
        }
    }
}

void PasswordDropper::on_pushButtonDeleteControl_clicked()
{
    int	R=ui->listWidgetClass->currentRow();
    if(R>=0){
        PasswordClass *c=GetLayersBase()->GetPasswordHolder()->GetPasswordClassDataItem(R);
        if(c!=NULL){
            int	Pn=ui->listWidgetControl->currentRow();
            PasswordInControl	*p=GetLayersBase()->GetPasswordHolder()->GetPasswordInControlDataItem(Pn);
            if(p!=NULL){
                if(QMessageBox::question ( 0, "Delete Control", "Delete control?",QMessageBox::Yes,QMessageBox::No)==QMessageBox::Yes){
                    GetLayersBase()->GetPasswordHolder()->RemoveList(p);
                    delete	p;
                    ClicklistWidgetClass();
                }
            }
        }
    }
}

void PasswordDropper::on_pushButtonSaveDefault_clicked()
{
    GetLayersBase()->GetPasswordHolder()->SetExpiredTimeSec(ui->spinBoxExpiredTime->value());
    GetLayersBase()->GetPasswordHolder()->SaveDefaultFile();
}

void PasswordDropper::on_pushButtonLoadDefault_clicked()
{
    GetLayersBase()->GetPasswordHolder()->LoadDefaultFile();
    ui->spinBoxExpiredTime->setValue(GetLayersBase()->GetPasswordHolder()->GetExpiredTimeSec());
}

void PasswordDropper::on_pushButtonModifyClass_clicked()
{
    int	R=ui->listWidgetClass->currentRow();
    if(R<0)
        return;
    PasswordClass *c=GetLayersBase()->GetPasswordHolder()->GetPasswordClassDataItem(R);
    if(c!=NULL){
        CreateClassForm	Q(this);
        Q.Initial(c->GetClassName());
        if(Q.exec()==(int)true){
            c->SetClassName(Q.ClassName);
            ShowList();
        }
    }
}

void PasswordDropper::on_pushButtonModifyPassword_clicked()
{
    int	R=ui->listWidgetPassword->currentRow();
    if(R<0)
        return;
    PasswordPass	*p=GetLayersBase()->GetPasswordHolder()->GetPasswordPassDataItem(R);
    if(p!=NULL){
        CreatePasswordForm	Q(this);
        Q.Initial(p->GetPassword());
        if(Q.exec()==(int)true){
            p->SetPassword(Q.Password);
            ClicklistWidgetClass();
        }
    }
}

void PasswordDropper::on_listWidgetClass_doubleClicked(const QModelIndex &index)
{
    on_pushButtonModifyClass_clicked();
}

void PasswordDropper::on_listWidgetPassword_doubleClicked(const QModelIndex &index)
{
    on_pushButtonModifyPassword_clicked();
}
