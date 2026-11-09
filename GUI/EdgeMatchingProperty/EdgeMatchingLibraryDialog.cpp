#include "EdgeMatchingLibraryDialog.h"
#include "ui_EdgeMatchingLibraryDialog.h"
#include <QMessageBox>
#include "XGeneralDialog.h"
#include "XEdgeMatchingPacket.h"

EdgeMatchingLibraryDialog::EdgeMatchingLibraryDialog(LayersBase *Base, QWidget *parent)
    : QDialog(parent)
    , ServiceForLayers(Base)
    , ui(new Ui::EdgeMatchingLibraryDialog)
{
    ui->setupUi(this);

    bool Ret;

    LibFolderID = -1;
    EdgeMatchingBase *BBase = GetEdgeMatchingBase();
    LibType = -1;
    if (BBase != NULL) {
        LibType = BBase->GetLibType();
    }

    LLib = NULL;
    if (BBase != NULL) {
        CmdCreateTempEdgeMatchingLibraryPacket Packet(GetLayersBase());
        BBase->TransmitDirectly(&Packet);
        LLib = Packet.Point;
    }

    // ƒe[ƒuƒ‹‚Ì—ñ•’²®
    ::SetColumnWidthInTable(ui->tableWidgetLibList, 0, 45);
    ::SetColumnWidthInTable(ui->tableWidgetLibList, 1, 140);

    pLibFolderForm = new GeneralLibFolderForm(LibType, GetLayersBase(), ui->frameLibFolder);
    Ret = connect(pLibFolderForm, SIGNAL(SelectLibFolder(int, QString)), this, SLOT(SlotSelectLibFolder(int, QString)));
    
    if (GetLayersBase() != NULL) {
        pLibFolderForm->SetCurrentLibFolder(GetLayersBase()->GetLibFolderID());
    }

    ui->ButtonLibSave->setEnabled(false);
    ui->ButtonLibDelete->setEnabled(false);
    InstallOperationLog(this);
}

EdgeMatchingLibraryDialog::~EdgeMatchingLibraryDialog()
{
    delete ui;
}

EdgeMatchingBase *EdgeMatchingLibraryDialog::GetEdgeMatchingBase(void)
{
    return (EdgeMatchingBase *)GetLayersBase()->GetAlgorithmBase("Basic", "EdgeMatching");
}

void EdgeMatchingLibraryDialog::SlotSelectLibFolder(int libFolderID, QString FolderName)
{
    LibFolderID = libFolderID;
    ui->tableWidgetLibList->setRowCount(0);
    EdgeMatchingBase *BBase = GetEdgeMatchingBase();
    
    if (BBase != NULL) {
        CmdGetEdgeMatchingLibraryListPacket Packet(GetLayersBase());
        Packet.LibFolderID = LibFolderID;
        BBase->TransmitDirectly(&Packet);
        LibList = Packet.AList;
        
        int row = 0;
        ui->tableWidgetLibList->setRowCount(Packet.AList.GetNumber());
        for (AlgorithmLibraryList *a = Packet.AList.GetFirst(); a != NULL; a = a->GetNext(), row++) {
            QTableWidgetItem *W;
            W = ui->tableWidgetLibList->item(row, 0);
            if (W == NULL) {
                W = new QTableWidgetItem();
                ui->tableWidgetLibList->setItem(row, 0, W);
                W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
            }
            W->setText(QString::number(a->GetLibID()));
            
            W = ui->tableWidgetLibList->item(row, 1);
            if (W == NULL) {
                W = new QTableWidgetItem();
                ui->tableWidgetLibList->setItem(row, 1, W);
                W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
            }
            W->setText(a->GetLibName());
        }
    }
}

void EdgeMatchingLibraryDialog::Initial(AlgorithmBase *InstBase)
{
    AlgorithmLibraryContainerForEnum LibList(InstBase->GetLayersBase());
    LibIDList.RemoveAll();
    LibList.EnumAllLibraries(GetLayersBase()->GetDatabase(), InstBase->GetLibType(), LibIDList);
}

void EdgeMatchingLibraryDialog::on_tableWidgetLibList_itemSelectionChanged()
{
    int r = ui->tableWidgetLibList->currentRow();
    AlgorithmLibraryList *a = LibList.GetItem(r);
    
    if (a != NULL && LLib != NULL) {
        LLib->SetLibID(a->GetLibID());

        CmdLoadEdgeMatchingLibraryPacket Packet(GetLayersBase());
        Packet.Point = LLib;
        EdgeMatchingBase *BBase = GetEdgeMatchingBase();
        if (BBase != NULL) {
            BBase->TransmitDirectly(&Packet);
            if (Packet.Success == true) {
                ShowLibrary(*LLib);
                ui->ButtonLibSave->setEnabled(true);
                ui->ButtonLibDelete->setEnabled(true);
            } else {
                QMessageBox::critical(NULL, "Library error", "Not loaded this library record");
            }
        }
    }
}

void EdgeMatchingLibraryDialog::on_ButtonLibNew_clicked()
{
    if (LLib == NULL) return;
    
    LLib->Reset();
    CmdClearEdgeMatchingLibraryPacket Packet(GetLayersBase());
    Packet.Point = LLib;
    EdgeMatchingBase *BBase = GetEdgeMatchingBase();
    if (BBase != NULL) {
        BBase->TransmitDirectly(&Packet);
    }
    ShowLibrary(*LLib);
    
    ui->ButtonLibSave->setEnabled(false);
    ui->ButtonLibDelete->setEnabled(false);
}

void EdgeMatchingLibraryDialog::on_ButtonLibDelete_clicked()
{
    if (LLib == NULL || LLib->GetLibID() < 0) return;
    
    QString msg = QString("Delete OK?");
    int ret = QMessageBox::question(NULL, "Choose", msg, QMessageBox::Yes | QMessageBox::No, QMessageBox::NoButton);
    if (ret == QMessageBox::Yes) {
        CmdDeleteEdgeMatchingLibraryPacket Packet(GetLayersBase());
        Packet.Point = LLib;
        EdgeMatchingBase *BBase = GetEdgeMatchingBase();
        if (BBase != NULL) {
            BBase->TransmitDirectly(&Packet);
            on_ButtonLibNew_clicked();
            SlotSelectLibFolder(LibFolderID, "");
        }
    }
}

void EdgeMatchingLibraryDialog::on_ButtonLibSaveNew_clicked()
{
    if (LLib == NULL) return;
    
    GetLibraryFromWindow(*LLib);

    if (LLib->GetLibName() == "") {
        QMessageBox::StandardButton ret = QMessageBox::warning(NULL, "Warning", "No Library Name", QMessageBox::Ok | QMessageBox::Cancel);
        if (ret != QMessageBox::Ok) return;
    }
    
    LLib->SetLibFolderID(LibFolderID);
    CmdInsertEdgeMatchingLibraryPacket Packet(GetLayersBase());
    Packet.Point = LLib;
    EdgeMatchingBase *BBase = GetEdgeMatchingBase();
    if (BBase != NULL) {
        BBase->TransmitDirectly(&Packet);
        ShowLibrary(*LLib);
        ui->ButtonLibSave->setEnabled(true);
        ui->ButtonLibDelete->setEnabled(true);
    }
    SlotSelectLibFolder(LibFolderID, "");
}

void EdgeMatchingLibraryDialog::on_ButtonLibSave_clicked()
{
    if (LLib == NULL) return;
    
    GetLibraryFromWindow(*LLib);
    
    if (LLib->GetLibName() == "") {
        QMessageBox::StandardButton ret = QMessageBox::warning(NULL, "Warning", "No Library Name", QMessageBox::Ok | QMessageBox::Cancel);
        if (ret != QMessageBox::Ok) return;
    }
    
    if (LLib->GetLibID() < 0) {
        LLib->SetLibFolderID(LibFolderID);

        CmdInsertEdgeMatchingLibraryPacket Packet(GetLayersBase());
        Packet.Point = LLib;
        EdgeMatchingBase *BBase = GetEdgeMatchingBase();
        if (BBase != NULL) {
            BBase->TransmitDirectly(&Packet);
            ShowLibrary(*LLib);
            ui->ButtonLibSave->setEnabled(true);
            ui->ButtonLibDelete->setEnabled(true);
        }
    } else {
        CmdUpdateEdgeMatchingLibraryPacket Packet(GetLayersBase());
        Packet.Point = LLib;
        EdgeMatchingBase *BBase = GetEdgeMatchingBase();
        if (BBase != NULL) {
            BBase->TransmitDirectly(&Packet);
        }
    }
    SlotSelectLibFolder(LibFolderID, "");
}

void EdgeMatchingLibraryDialog::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
    if (data.GetLibID() < 0) {
        ui->EditLibID->setText("");
    } else {
        ui->EditLibID->setText(QString::number(data.GetLibID()));
    }
    ui->EditLibName->setText(data.GetLibName());

    EdgeMatchingLibrary *ALib = static_cast<EdgeMatchingLibrary *>(data.GetLibrary());

    ui->EditFocusRadius->setValue(ALib->FocusRadius);
    ui->EditLayer->setValue(ALib->Layer);
    ui->EditSearchDotX->setValue(ALib->SearchDotX);
    ui->EditSearchDotY->setValue(ALib->SearchDotY);
    ui->EditSearchByPixel->setValue(ALib->SearchByPixel);
    ui->EditThresholdDiv->setValue(ALib->ThresholdDiv);
    ui->EditThresholdDirection->setValue(ALib->ThresholdDirection);
}

void EdgeMatchingLibraryDialog::GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data)
{
    data.SetLibName(ui->EditLibName->text());

    EdgeMatchingLibrary *ALib = static_cast<EdgeMatchingLibrary *>(data.GetLibrary());

    ALib->FocusRadius = ui->EditFocusRadius->value();
    ALib->Layer = ui->EditLayer->value();
    ALib->SearchDotX = ui->EditSearchDotX->value();
    ALib->SearchDotY = ui->EditSearchDotY->value();
    ALib->SearchByPixel = ui->EditSearchByPixel->value();
    ALib->ThresholdDiv = ui->EditThresholdDiv->value();
    ALib->ThresholdDirection = ui->EditThresholdDirection->value();
}

void EdgeMatchingLibraryDialog::on_pushButtonClose_clicked()
{
    close();
}