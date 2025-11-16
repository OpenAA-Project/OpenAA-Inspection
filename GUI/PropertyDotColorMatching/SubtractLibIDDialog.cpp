#include "SubtractLibIDDialog.h"
#include "XTypeDef.h"
#include "ui_SubtractLibIDDialog.h"
#include "LibFolderForm.h"
#include "XDataInLayer.h"
#include "XGeneralFunc.h"
#include "XLibraryType.h"
#include "XDotColorMatchingLibrary.h"

SubtractLibIDDialog::SubtractLibIDDialog(LayersBase *base ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(base),
    ui(new Ui::SubtractLibIDDialog)
{
    ui->setupUi(this);

    LibType=DefLibTypeDotColorMatchingInspect;
    pLibFolderForm=new LibFolderForm(-1,GetLayersBase(),ui->frameLibFolder);
    connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
    ::SetColumnWidthInTable(ui->tableWidgetLibList ,0, 25);
    ::SetColumnWidthInTable(ui->tableWidgetLibList ,1, 75);
    ::SetColumnWidthInTable(ui->tableWidgetSelectedList ,0, 25);
    ::SetColumnWidthInTable(ui->tableWidgetSelectedList ,1, 75);

    InstallOperationLog(this);
}

SubtractLibIDDialog::~SubtractLibIDDialog()
{
    delete ui;
}

void	SubtractLibIDDialog::SetSelected(AlgorithmLibraryListContainer &selectedList)
{
    SelectedList=selectedList;
    ShowSelectedList();
}

void	SubtractLibIDDialog::ShowFolder(int LibType)
{
    pLibFolderForm->SetLibType(LibType);
}



void	SubtractLibIDDialog::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
    LibFolderID=libFolderID;
    ui->tableWidgetLibList->setRowCount(0);
    AlgorithmLibraryContainerForEnum		LibList(GetLayersBase());
    LibIDList.RemoveAll();
    LibList.EnumLibrary(GetLayersBase()->GetDatabase(),LibType,LibFolderID ,LibIDList);

    int	row=0;
    ui->tableWidgetLibList->setRowCount(LibIDList.GetNumber());
    for(AlgorithmLibraryList *a=LibIDList.GetFirst();a!=NULL;a=a->GetNext(),row++){
        QTableWidgetItem *W;
        W=ui->tableWidgetLibList->item ( row, 0);
        if(W==NULL){
            W=new QTableWidgetItem();
            ui->tableWidgetLibList->setItem ( row, 0,W);
            W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        }
        W->setText(QString::number(a->GetLibID()));
        W=ui->tableWidgetLibList->item ( row, 1);
        if(W==NULL){
            W=new QTableWidgetItem();
            ui->tableWidgetLibList->setItem ( row, 1,W);
            W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        }
        W->setText(a->GetLibName());
    }
}

void SubtractLibIDDialog::on_tableWidgetLibList_doubleClicked(const QModelIndex &)
{
    on_pushButtonSend_clicked();
}
void SubtractLibIDDialog::ShowSelectedList(void)
{
    int	row=0;
    ui->tableWidgetSelectedList->setRowCount(SelectedList.GetNumber());
    for(AlgorithmLibraryList *a=SelectedList.GetFirst();a!=NULL;a=a->GetNext(),row++){
        QTableWidgetItem *W;
        W=ui->tableWidgetSelectedList->item ( row, 0);
        if(W==NULL){
            W=new QTableWidgetItem();
            ui->tableWidgetSelectedList->setItem ( row, 0,W);
            W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        }
        W->setText(QString::number(a->GetLibID()));
        W=ui->tableWidgetSelectedList->item ( row, 1);
        if(W==NULL){
            W=new QTableWidgetItem();
            ui->tableWidgetSelectedList->setItem ( row, 1,W);
            W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        }
        W->setText(a->GetLibName());
    }
}

void SubtractLibIDDialog::on_tableWidgetSelectedList_doubleClicked(const QModelIndex &)
{
    on_pushButtonBack_clicked();
}

void SubtractLibIDDialog::on_pushButtonSend_clicked()
{
    QModelIndex	RIndex=ui->tableWidgetLibList->currentIndex();
    if(RIndex.isValid()==false)
        return;
    int	R=RIndex.row();
    AlgorithmLibraryList	*d=LibIDList.GetItem(R);
    if(d!=NULL){
        bool	ModeAdd=true;
        for(AlgorithmLibraryList *a=SelectedList.GetFirst();a!=NULL;a=a->GetNext()){
            if(*a==*d){
                ModeAdd=false;
                break;
            }
        }
        if(ModeAdd==true){
            AlgorithmLibraryList *as=new AlgorithmLibraryList(*d);
            SelectedList.AppendList(as);
        }
        ShowSelectedList();
    }
}


void SubtractLibIDDialog::on_pushButtonBack_clicked()
{
    QModelIndex	RIndex=ui->tableWidgetSelectedList->currentIndex();
    if(RIndex.isValid()==false)
        return;
    int	R=RIndex.row();
    AlgorithmLibraryList	*d=SelectedList.GetItem(R);
    if(d!=NULL){
        SelectedList.RemoveList(d);
        delete	d;
        ShowSelectedList();
    }
}


void SubtractLibIDDialog::on_pushButtonOK_clicked()
{
    done(true);
}


void SubtractLibIDDialog::on_pushButtonCancel_clicked()
{
    done(false);
}

