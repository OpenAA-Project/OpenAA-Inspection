#include "EditSyncGUIForm.h"
#include "ui_EditSyncGUIForm.h"
#include "XSyncGUI.h"
#include "XDataInLayer.h"
#include <QFileDialog>
#include "XGeneralFunc.h"


EditSyncGUIForm::EditSyncGUIForm(LayersBase *base ,QWidget *parent) :
    QWidget(parent),ServiceForLayers(base),
    ui(new Ui::EditSyncGUIForm)
{
    ui->setupUi(this);

    ui->tableWidget->setColumnWidth(0,200);
    ui->tableWidget->setColumnWidth(1,100);

    SetFileNameFromGlobalParam();
    Show();
}

EditSyncGUIForm::~EditSyncGUIForm()
{
    delete ui;
}
void EditSyncGUIForm::SetFileNameFromGlobalParam(void)
{
    ui->lineEditFileName->setText(GetParamGlobal()->SyncGUIFileName);
}

void EditSyncGUIForm::Show(void)
{
    ui->tableWidget->setRowCount(GetLayersBase()->GetSyncGUIData()->GetCount());
    int	Row=0;
    for(SyncGUIPipe *a=GetLayersBase()->GetSyncGUIData()->GetFirst();a!=NULL;a=a->GetNext(),Row++){
        SetDataToTable(ui->tableWidget,0,Row ,a->IPAddress,Qt::ItemIsEditable);
        SetDataToTable(ui->tableWidget,1,Row ,a->Port,Qt::ItemIsEditable);
    }
}

void EditSyncGUIForm::LoadFromWindow(void)
{
    GetLayersBase()->GetSyncGUIData()->RemoveAll();
    int	N=ui->tableWidget->rowCount();
    for(int Row=0;Row<N;Row++){
        QString	StrIPAddress=GetDataToTable(ui->tableWidget,0,Row);
        QString	StrPort		=GetDataToTable(ui->tableWidget,1,Row);
        if(StrIPAddress.isEmpty()==false && StrPort.isEmpty()==false){
            bool	ok;
            int	Port=StrPort.toInt(&ok);
            if(ok==true){
                SyncGUIPipe	*a=new SyncGUIPipe(GetLayersBase()->GetSyncGUIData(),GetLayersBase());
                a->IPAddress=StrIPAddress;
                a->Port		=Port;
                GetLayersBase()->GetSyncGUIData()->AppendList(a);
            }
        }
    }
}


void EditSyncGUIForm::on_pushButtonFileName_clicked()
{
    QString	FileName=QFileDialog::getOpenFileName(0
                                   ,/**/"File name for SyncGUI file"
                                   ,QString()
                                   ,"*.dat(*.dat)");
    if(FileName.isEmpty()==false){
        ui->lineEditFileName->setText(FileName);
    }
}

void EditSyncGUIForm::on_pushButtonLoad_clicked()
{
    QString	FileName=ui->lineEditFileName->text();
    if(QFile::exists(FileName)==true){
        QFile	File(FileName);
        if(File.open(QIODevice::ReadOnly)==true){
            GetLayersBase()->GetSyncGUIData()->Load(&File);
            Show();
        }
    }
}

void EditSyncGUIForm::on_pushButtonAddLine_clicked()
{
    ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
}

void EditSyncGUIForm::on_pushButtonDelLine_clicked()
{
    ui->tableWidget->setRowCount(ui->tableWidget->rowCount()-1);
}

void EditSyncGUIForm::on_pushButtonUpdate_clicked()
{
    LoadFromWindow();
    QString	FileName=ui->lineEditFileName->text();
    QFile	File(FileName);
    if(File.open(QIODevice::WriteOnly)==true){
        GetLayersBase()->GetSyncGUIData()->Save(&File);
    }
}

void EditSyncGUIForm::on_pushButtonSaveNew_clicked()
{
    QString	FileName=QFileDialog::getSaveFileName(0
                                   ,/**/"File name for SyncGUI file"
                                   ,QString()
                                   ,"*.dat(*.dat)");
    if(FileName.isEmpty()==false){
        ui->lineEditFileName->setText(FileName);
        LoadFromWindow();
        QFile	File(FileName);
        if(File.open(QIODevice::WriteOnly)==true){
            GetLayersBase()->GetSyncGUIData()->Save(&File);
        }
    }
}

void EditSyncGUIForm::on_pushButtonClose_clicked()
{
    close();
}
