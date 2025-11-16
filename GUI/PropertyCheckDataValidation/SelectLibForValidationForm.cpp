#include "SelectLibForValidationForm.h"
#include "ui_SelectLibForValidationForm.h"
#include "XAlgorithmBase.h"
#include "XDataInLayer.h"
#include "LibFolderForm.h"
#include "XGeneralFunc.h"
#include "XLibraryType.h"

SelectLibForValidationForm::SelectLibForValidationForm(LayersBase *base ,QWidget *parent) :
    QWidget(parent),ServiceForLayers(base),
    ui(new Ui::SelectLibForValidationForm)
{
    ui->setupUi(this);


    pLibFolderForm=new LibFolderForm(-1,GetLayersBase(),ui->frameLibFolder);
    connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
    ::SetColumnWidthInTable(ui->tableWidgetLibList ,0, 25);
    ::SetColumnWidthInTable(ui->tableWidgetLibList ,1, 75);

    ui->comboBoxAlgorithm->clear();
    for(LogicDLL *L=GetLayersBase()->GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
        AlgorithmBase   *A=L->GetInstance();
        if(A->GetLibType()>0){
            QString Txt=QString::number(A->GetLibType())
                        +QString(":")
                        +A->GetNameByCurrentLanguage();
            ui->comboBoxAlgorithm->addItem(Txt,A->GetLibType());
        }
    }
}

SelectLibForValidationForm::~SelectLibForValidationForm()
{
    delete ui;
}

bool    SelectLibForValidationForm::Initial(int LibType, int LibID)
{
    int N=ui->comboBoxAlgorithm->count();
    for(int i=0;i<N;i++){ 
        QVariant v=ui->comboBoxAlgorithm->itemData(i);
        bool    ok;
        int _LibType=v.toInt(&ok);
        if(ok==true){
            if(_LibType==LibType){
                ui->comboBoxAlgorithm->setCurrentIndex(i);
                ShowFolder(LibType);
                AlgorithmBase   *ABase=GetLayersBase()->GetAlgorithmBase(LibType);
                AlgorithmLibraryContainer   *ALibC=ABase->GetLibraryContainer();
                if(ALibC!=NULL){
                    AlgorithmLibraryLevelContainer  ALib(ABase);
                    if(ALibC->GetLibrary(LibID,ALib)==true){
                        SelectedLibType=LibType;
                        SlotSelectLibFolder(ALib.GetLibFolderID(),/**/"");

                        int row=0;
                        for(AlgorithmLibraryList *a=LibIDList.GetFirst();a!=NULL;a=a->GetNext(),row++){
                            if(a->GetLibID()==LibType){
                                ::SetCurrentRow(ui->tableWidgetLibList,row);
                            }
                        }                     
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

void	SelectLibForValidationForm::ShowFolder(int LibType)
{
    SelectedLibType=LibType;
    pLibFolderForm->SetLibType(LibType);
}

void	SelectLibForValidationForm::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
    LibFolderID=libFolderID;
    ui->tableWidgetLibList->setRowCount(0);
    AlgorithmLibraryContainerForEnum		LibList(GetLayersBase());
    LibIDList.RemoveAll();
    LibList.EnumLibrary(GetLayersBase()->GetDatabase(),SelectedLibType,LibFolderID ,LibIDList);

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
void SelectLibForValidationForm::on_comboBoxAlgorithm_currentIndexChanged(int index)
{
    QVariant v=ui->comboBoxAlgorithm->itemData(index);
    bool    ok;
    int LibType=v.toInt(&ok);
    if(ok==true){
        ui->comboBoxAlgorithm->setCurrentIndex(index);
        ShowFolder(LibType);
        ui->tableWidgetLibList->setRowCount(0);
        LibIDList.RemoveAll();
    }
}


void SelectLibForValidationForm::on_tableWidgetLibList_clicked(const QModelIndex &index)
{
    int Row=ui->tableWidgetLibList->currentRow();
    AlgorithmLibraryList    *L=LibIDList[Row];
    if(L!=NULL){
        emit    SignalSelectedLib(SelectedLibType,L->GetLibID());
    }
}

