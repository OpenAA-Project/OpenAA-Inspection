#include "EditEdgeMatchingForm.h"
#include "ui_EditEdgeMatchingForm.h"
#include "XEdgeMatching.h"
#include "XDataInLayerCommander.h"
#include "swap.h"

EditEdgeMatchingForm::EditEdgeMatchingForm(LayersBase *Base, QWidget *parent)
    : QWidget(parent)
    , ServiceForLayers(Base)
    , PasswordInQWodget(Base, this)
    , ui(new Ui::EditEdgeMatchingForm)
{
    ui->setupUi(this);

    OnChanging = false;
    IData = NULL;

    InstallOperationLog(this);
}

EditEdgeMatchingForm::~EditEdgeMatchingForm()
{
    delete ui;
}

void EditEdgeMatchingForm::Initial(AlgorithmBase *InstBase, AlgorithmItemIndependentPack &Data)
{
    if (IData != NULL) {
        delete IData;
    }
    IData = new AlgorithmItemIndependentPack(InstBase->GetLayersBase());
    *IData = Data;
    GlobalPage = 0;

    ShowDataToWindow();
}

void EditEdgeMatchingForm::GetDataFromWindow(void)
{
    for (AlgorithmItemIndependent *D = IData->Items.GetFirst(); D != NULL; D = D->GetNext()) {
        AlgorithmItemRoot *DA = D->Data;
        if (DA == NULL) continue;
        
        EdgeMatchingItem *BData = dynamic_cast<EdgeMatchingItem *>(DA);
        if (BData == NULL) continue;
        
        EdgeMatchingThreshold *Thr = BData->GetThresholdW(GetLayersBase());

        Thr->FocusRadius = ui->EditFocusRadius->value();
        Thr->Layer = ui->EditLayer->value();
        Thr->SearchDotX = ui->EditSearchDotX->value();
        Thr->SearchDotY = ui->EditSearchDotY->value();
        Thr->SearchByPixel = ui->EditSearchByPixel->value();
        Thr->ThresholdDiv = ui->EditThresholdDiv->value();
        Thr->ThresholdDirection = ui->EditThresholdDirection->value();
    }
}

void EditEdgeMatchingForm::ShowDataToWindow(void)
{
    for (AlgorithmItemIndependent *D = IData->Items.GetFirst(); D != NULL; D = D->GetNext()) {
        AlgorithmItemRoot *DA = D->Data;
        if (DA != NULL) {
            EdgeMatchingItem *BData = dynamic_cast<EdgeMatchingItem *>(DA);
            if (BData != NULL) {
                const EdgeMatchingThreshold *Thr = BData->GetThresholdR(GetLayersBase());

                ui->EditFocusRadius->setValue(Thr->FocusRadius);
                ui->EditLayer->setValue(Thr->Layer);
                ui->EditSearchDotX->setValue(Thr->SearchDotX);
                ui->EditSearchDotY->setValue(Thr->SearchDotY);
                ui->EditSearchByPixel->setValue(Thr->SearchByPixel);
                ui->EditThresholdDiv->setValue(Thr->ThresholdDiv);
                ui->EditThresholdDirection->setValue(Thr->ThresholdDirection);
                break;
            }
        }
    }
}

void EditEdgeMatchingForm::on_EditFocusRadius_valueChanged(int arg1)
{
}

void EditEdgeMatchingForm::on_EditLayer_valueChanged(int arg1)
{
}

void EditEdgeMatchingForm::on_EditSearchDotX_valueChanged(int arg1)
{
}

void EditEdgeMatchingForm::on_EditSearchDotY_valueChanged(int arg1)
{
}

void EditEdgeMatchingForm::on_EditSearchByPixel_valueChanged(int arg1)
{
}

void EditEdgeMatchingForm::on_EditThresholdDiv_valueChanged(double arg1)
{
}

void EditEdgeMatchingForm::on_EditThresholdDirection_valueChanged(double arg1)
{
}

void EditEdgeMatchingForm::on_pushButtonReflectOnly_clicked()
{
    GetLayersBase()->ClearAllAckFlag();
    GetLayersBase()->ShowProcessingForm("Change one point");

    GetLayersBase()->GetUndoStocker().SetNewTopic("Change one point");
    GetDataFromWindow();
    
    GUICmdSendAlgorithmItemIndependentPack Packet(IData->Base, QString("ANY"), QString("ANY"), -1, true);
    Packet.Command = SetIndependentItemDataCommand_OnlyOne;
    Packet.IData = *IData;
    
    for (int page = 0; page < GetPageNumb(); page++) {
        Packet.Send(NULL, page, 0);
    }
    
    GetLayersBase()->WaitAllAcknowledged(60 * 10);
    GetLayersBase()->CloseProcessingForm();
}

void EditEdgeMatchingForm::on_pushButtonReflectAll_clicked()
{
    GetLayersBase()->ClearAllAckFlag();
    GetLayersBase()->ShowProcessingForm("Change all points");

    GetLayersBase()->GetUndoStocker().SetNewTopic("Change all points");
    GetDataFromWindow();
    
    GUICmdSendAlgorithmItemIndependentPack Packet(IData->Base, QString("ANY"), QString("ANY"), -1, true);
    Packet.Command = SetIndependentItemDataCommand_All;
    Packet.IData = *IData;
    
    for (int page = 0; page < GetPageNumb(); page++) {
        Packet.Send(NULL, page, 0);
    }
    
    GetLayersBase()->WaitAllAcknowledged(60 * 10);
    GetLayersBase()->CloseProcessingForm();
}

void EditEdgeMatchingForm::on_pushButtonClose_clicked()
{
    close();
}
