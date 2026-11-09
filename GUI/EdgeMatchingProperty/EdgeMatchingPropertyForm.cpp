#include "EdgeMatchingPropertyForm.h"
#include "ui_EdgeMatchingPropertyForm.h"
#include "XGeneralFunc.h"
#include "XEdgeMatching.h"
#include "SelectLibFolderDialog.h"
//#include "ImageControlTools.h"
#include "XDisplayImagePacket.h"
#include "EdgeMatchingLibraryDialog.h" // EdgeMatching用のライブラリダイアログ（想定）

extern const char *sRoot;
extern const char *sName;

EdgeMatchingPropertyForm::EdgeMatchingPropertyForm(LayersBase *Base, QWidget *parent)
    : GUIFormBase(Base, parent),
      ui(new Ui::EdgeMatchingPropertyForm)
{
    ui->setupUi(this);

    // テーブルの列幅初期化
    ::SetColumnWidthInTable(ui->tableWidgetLibList, 0, 30);
    ::SetColumnWidthInTable(ui->tableWidgetLibList, 1, 60);

    ::SetColumnWidthInTable(ui->tableWidgetGeneratedLibList, 0, 30);
    ::SetColumnWidthInTable(ui->tableWidgetGeneratedLibList, 1, 60);
    
    ::SetColumnWidthInTable(ui->tableWidgetItemList, 0, 10);
    ::SetColumnWidthInTable(ui->tableWidgetItemList, 1, 10);
    ::SetColumnWidthInTable(ui->tableWidgetItemList, 2, 10);
    ::SetColumnWidthInTable(ui->tableWidgetItemList, 3, 30);
    ::SetColumnWidthInTable(ui->tableWidgetItemList, 4, 30);
    
    InstallIgnoreKeyForChild();
}

EdgeMatchingPropertyForm::~EdgeMatchingPropertyForm()
{
    delete ui;
}

EdgeMatchingBase *EdgeMatchingPropertyForm::GetEdgeMatchingBase(void)
{
    EdgeMatchingBase *BBase = (EdgeMatchingBase *)GetLayersBase()->GetAlgorithmBase("Basic", "EdgeMatching");
    return BBase;
}

void EdgeMatchingPropertyForm::on_toolButtonArea_clicked()
{
    // Area描画時の処理（必要に応じて実装）
}

void EdgeMatchingPropertyForm::on_toolButtonDirection_clicked()
{
    // Direction描画時の処理（必要に応じて実装）
}

void EdgeMatchingPropertyForm::on_toolButtonEdge_clicked()
{
    // Edge描画時の処理（必要に応じて実装）
}

void EdgeMatchingPropertyForm::on_pushButtonEditLibFolder_clicked()
{
    EdgeMatchingBase *BBase = GetEdgeMatchingBase();
    if (BBase == NULL) return;
    
    SelectLibFolderDialog D(BBase->GetLibType(), GetLayersBase(), this);
    if (D.exec() == (int)true) {
        SetLibFolder(D.SelectedLibFolderID, D.SelectedFolderName);
    }
}

void EdgeMatchingPropertyForm::SetLibFolder(int _LibFolderID, const QString &LinFolderName)
{
    ui->labelLibFolderName->setText(LinFolderName);
    LibFolderID = _LibFolderID;
    ShowLibList();
}

void EdgeMatchingPropertyForm::on_tableWidgetLibList_doubleClicked(const QModelIndex &index)
{
    on_pushButtonSetFrom_clicked();
}

void EdgeMatchingPropertyForm::on_tableWidgetGeneratedLibList_doubleClicked(const QModelIndex &index)
{
    on_pushButtonGetBack_clicked();
}

void EdgeMatchingPropertyForm::on_pushButtonEditLibrary_clicked()
{
    EdgeMatchingLibraryDialog D(GetLayersBase(), this);
    D.Initial(GetEdgeMatchingBase());
    D.exec();
}

void EdgeMatchingPropertyForm::on_tableWidgetItemList_itemSelectionChanged()
{
    int Row = ui->tableWidgetItemList->currentRow();
    EdgeMatchingItemList *a = ItemList[Row];
    if (a != NULL) {
        DataInPage *P = GetLayersBase()->GetPageData(a->Data.Page);
        if (P != NULL) {
            CmdDrawImageRectPacket Cmd(GetLayersBase(),
                                       a->Data.x1 + P->GetOutlineOffset()->x, a->Data.y1 + P->GetOutlineOffset()->y,
                                       a->Data.x2 + P->GetOutlineOffset()->x, a->Data.y2 + P->GetOutlineOffset()->y);
            
            GUIFormBase *GProp = GetLayersBase()->FindByName("Inspection", "EdgeMatchingImagePanel", "");
            if (GProp != NULL)
                GProp->TransmitDirectly(&Cmd);
            
            CmdDrawImageActivate ACmd(GetLayersBase(), a->Data.Page, 0, a->Data.ItemID);
            if (GProp != NULL)
                GProp->TransmitDirectly(&ACmd);
        }
    }
}

void EdgeMatchingPropertyForm::on_tableWidgetItemList_cellDoubleClicked(int row, int column)
{
    // 必要に応じてダブルクリック時の挙動を追加
}

void EdgeMatchingPropertyForm::on_pushButtonSetFrom_clicked()
{
    int r = ui->tableWidgetLibList->currentRow();
    if (r < 0) return;
    
    AlgorithmLibraryList *a = LibList.GetItem(r);
    for (AlgorithmLibraryList *c = SelectedLibList.GetFirst(); c != NULL; c = c->GetNext()) {
        if (c->GetLibID() == a->GetLibID())
            return;
    }
    SelectedLibList.AppendList(new AlgorithmLibraryList(LibType, a->GetLibID(), a->GetLibName()));
    ShowSelectedLibList();
}

void EdgeMatchingPropertyForm::on_pushButtonGetBack_clicked()
{
    int r = ui->tableWidgetGeneratedLibList->currentRow();
    if (r < 0) return;
    
    AlgorithmLibraryList *a = SelectedLibList.GetItem(r);
    if (a != NULL) {
        SelectedLibList.RemoveList(a);
        delete a;
        ShowSelectedLibList();
    }
}

void EdgeMatchingPropertyForm::on_pushButtonSetFromAll_clicked()
{
    SelectedLibList.RemoveAll();
    for (AlgorithmLibraryList *a = LibList.GetFirst(); a != NULL; a = a->GetNext()) {
        SelectedLibList.AppendList(new AlgorithmLibraryList(LibType, a->GetLibID(), a->GetLibName()));
    }
    ShowSelectedLibList();
}

void EdgeMatchingPropertyForm::on_pushButtonGetBackAll_clicked()
{
    SelectedLibList.RemoveAll();
    ShowSelectedLibList();
}

void EdgeMatchingPropertyForm::ShowLibList(void)
{
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

struct AlgorithmLibraryListClass
{
    AlgorithmLibraryList *a;
};

void EdgeMatchingPropertyForm::ShowSelectedLibList(void)
{
    struct AlgorithmLibraryListClass DDim[100];

    EdgeMatchingBase *BBase = GetEdgeMatchingBase();
    if (BBase != NULL) {
        CmdCreateTempEdgeMatchingLibraryPacket Packet(GetLayersBase());
        BBase->TransmitDirectly(&Packet);
        AlgorithmLibraryLevelContainer *SLib = Packet.Point;

        int row = 0;
        for (AlgorithmLibraryList *a = SelectedLibList.GetFirst(); a != NULL; a = a->GetNext(), row++) {
            DDim[row].a = a;
            SLib->SetLibID(a->GetLibID());

            CmdLoadEdgeMatchingLibraryPacket LPacket(GetLayersBase());
            LPacket.Point = SLib;
            BBase->TransmitDirectly(&LPacket);
        }
        for (;;) {
            AlgorithmLibraryList *a = SelectedLibList.GetFirst();
            if (a == NULL) break;
            SelectedLibList.RemoveList(a);
        }
        for (int i = 0; i < row; i++) {
            SelectedLibList.AppendList(DDim[i].a);
        }
    }

    int row = 0;
    ui->tableWidgetGeneratedLibList->setRowCount(SelectedLibList.GetNumber());
    for (AlgorithmLibraryList *a = SelectedLibList.GetFirst(); a != NULL; a = a->GetNext(), row++) {
        QTableWidgetItem *W;
        W = ui->tableWidgetGeneratedLibList->item(row, 0);
        if (W == NULL) {
            W = new QTableWidgetItem();
            ui->tableWidgetGeneratedLibList->setItem(row, 0, W);
            W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        }
        W->setText(QString::number(a->GetLibID()));
        
        W = ui->tableWidgetGeneratedLibList->item(row, 1);
        if (W == NULL) {
            W = new QTableWidgetItem();
            ui->tableWidgetGeneratedLibList->setItem(row, 1, W);
            W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        }
        W->setText(a->GetLibName());
    }
}

void EdgeMatchingPropertyForm::TransmitDirectly(GUIDirectMessage *packet)
{
    CmdEdgeMatchingDrawModePacket *DrawModePacket = dynamic_cast<CmdEdgeMatchingDrawModePacket *>(packet);
    if (DrawModePacket != NULL) {
        if (ui->toolButtonArea->isChecked() == true) {
            DrawModePacket->DrawModeArea = true;
        } else {
            DrawModePacket->DrawModeArea = false;
        }

        if (ui->toolButtonEdge->isChecked() == true) {
            DrawModePacket->DrawModeEdge = true;
        } else {
            DrawModePacket->DrawModeEdge = false;
        }
        
        if (ui->toolButtonDirection->isChecked() == true) {
            DrawModePacket->DrawModeDirection = true;
        } else {
            DrawModePacket->DrawModeDirection = false;
        }
        return;
    }
    
    CmdEdgeMatchingDrawEnd *DrawEndPacket = dynamic_cast<CmdEdgeMatchingDrawEnd *>(packet);
    if (DrawEndPacket != NULL) {
        int Row = ui->tableWidgetGeneratedLibList->currentRow();
        if (Row >= 0) {
            AlgorithmLibraryList *a = SelectedLibList.GetItem(Row);
            if (a != NULL) {
                GetLayersBase()->GetUndoStocker().SetNewTopic("Create EdgeMatching point");

                IntList PageList;
                GetLayersBase()->GetLocalPageFromArea(DrawEndPacket->Area, PageList);
                for (IntClass *P = PageList.GetFirst(); P != NULL; P = P->GetNext()) {
                    int page = P->GetValue();
                    DataInPage *pdata = GetLayersBase()->GetPageData(page);
                    FlexArea A = DrawEndPacket->Area;
                    pdata->ClipMoveAreaFromGlobal(A);
                    if (A.GetPatternByte() > 0) {
                        int GlobalPage = GetLayersBase()->GetGlobalPageFromLocal(page);
                        GUICmdAddEdgeMatching Cmd(GetLayersBase(), sRoot, sName, GlobalPage);
                        Cmd.Area = A;
                        Cmd.LibID = a->GetLibID();
                        Cmd.Send(NULL, GlobalPage, 0);
                    }
                }
            }
            ShowItemList();
        }
        return;
    }
}

void EdgeMatchingPropertyForm::BuildForShow(void)
{
    ShowItemList();
}

void EdgeMatchingPropertyForm::StartPage(void)
{
}

void EdgeMatchingPropertyForm::ShowInEdit(void)
{
}

void EdgeMatchingPropertyForm::ShowItemList(void)
{
    ItemList.RemoveAll();
    for (int Page = 0; Page < GetPageNumb(); Page++) {
        for (int Phase = 0; Phase < GetPhaseNumb(); Phase++) {
            int GlobalPage = GetLayersBase()->GetGlobalPageFromLocal(Page);
            GUICmdReqEdgeMatchingItemList RCmd(GetLayersBase(), sRoot, sName, GlobalPage);
            GUICmdSendEdgeMatchingItemList SCmd(GetLayersBase(), sRoot, sName, GlobalPage);
            RCmd.Phase = Phase;
            if (RCmd.Send(GlobalPage, 0, SCmd) == true) {
                ItemList.AddMove(SCmd.ItemList);
            }
        }
    }

    int row = 0;
    ui->tableWidgetItemList->setRowCount(ItemList.GetNumber());
    for (EdgeMatchingItemList *a = ItemList.GetFirst(); a != NULL; a = a->GetNext(), row++) {
        ::SetDataToTable(ui->tableWidgetItemList, 0, row, QString::number(a->Data.Page));
        ::SetDataToTable(ui->tableWidgetItemList, 1, row, QString::number(a->Data.ItemID));
        ::SetDataToTable(ui->tableWidgetItemList, 2, row, QString::number(a->Data.LibID));

        QString LibName = GetEdgeMatchingBase()->GetLibraryName(a->Data.LibID);
        ::SetDataToTable(ui->tableWidgetItemList, 3, row, LibName);

        QString CenterStr = QString::number(a->Data.CenterX) + QString(",") + QString::number(a->Data.CenterY);
        ::SetDataToTable(ui->tableWidgetItemList, 4, row, CenterStr);
    }
}


