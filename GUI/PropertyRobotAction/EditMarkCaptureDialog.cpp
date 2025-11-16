#include "EditMarkCaptureDialog.h"
#include "ui_EditMarkCaptureDialog.h"
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XLibraryType.h"
#include "XRobotAction.h"

EditMarkCaptureDialog::EditMarkCaptureDialog(LayersBase *base,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(base)
    ,ui(new Ui::EditMarkCaptureDialog)
{
    ui->setupUi(this);

    ui->comboBLibType->clear();
    for(LibraryTypeList *L=GetLayersBase()->GetInstalledLibType()->GetFirst();L!=NULL;L=L->GetNext()){
        AlgorithmBase   *ABase=GetLayersBase()->GetAlgorithmBase(L->GetLibType());
        ui->comboBLibType->addItem(ABase->GetNameByCurrentLanguage(),(int)L->GetLibType());
    }
}

EditMarkCaptureDialog::~EditMarkCaptureDialog()
{
    delete ui;
}
void    EditMarkCaptureDialog::Initial(ActionMarkBase *src)
{
    ActionMarkCapture  *a=dynamic_cast<ActionMarkCapture *>(src);
    if(a!=NULL){
        int Row=0;
        for(LibraryTypeList *L=GetLayersBase()->GetInstalledLibType()->GetFirst();L!=NULL;L=L->GetNext(),Row++){
            if(L->GetLibType()==a->AlgorithmType){
                ui->comboBLibType->setCurrentIndex(Row);
                break;
            }
        }
        ui->spinBoxPage             ->setValue(a->AlgorithmPage);
        ui->spinBoxLayer            ->setValue(a->AlgorithmLayer);
        ui->spinBoxItemID           ->setValue(a->AlgorithmItemID);
        ui->doubleSpinBoxStopMilisec->setValue(a->StopMilisec);
    }
}
void EditMarkCaptureDialog::on_pushButtonOK_clicked()
{
    int	Index=ui->comboBLibType->currentIndex();
    LibraryTypeList *L=GetLayersBase()->GetInstalledLibType()->GetItem(Index);
    if(L==NULL)
        return;
    AlgorithmType=L->GetLibType();
    AlgorithmPhase  =0;
    AlgorithmPage   =ui->spinBoxPage    ->value();
    AlgorithmLayer  =ui->spinBoxLayer   ->value();
    AlgorithmItemID =ui->spinBoxItemID  ->value();
    StopMilisec=ui->doubleSpinBoxStopMilisec->value();
    done(true);
}


void EditMarkCaptureDialog::on_pushButtonCancel_clicked()
{
    done(false);
}

