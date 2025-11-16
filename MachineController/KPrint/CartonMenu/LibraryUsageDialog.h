#ifndef LIBRARYUSAGEDIALOG_H
#define LIBRARYUSAGEDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include"XParamCustomized.h"
#include "XServiceForLayers.h"

namespace Ui {
class LibraryUsageDialog;
}

class CartonMenuForm;
class LibFolderForm;

class LibraryUsageDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
    CartonMenuForm  *Parent;
public:
    explicit LibraryUsageDialog(LayersBase *Base ,CartonMenuForm *p ,QWidget *parent = 0);
    ~LibraryUsageDialog();
    
private slots:
    void on_toolButtonSide1_clicked();
    void on_toolButtonSide2_clicked();
    void on_toolButtonSide3_clicked();
    void on_tableWidget_itemSelectionChanged();
    void on_comboBoxLibTypeSelect_currentIndexChanged(int index);
    void on_tableWidgetLibListSelect_doubleClicked(const QModelIndex &index);
    void on_pushButtonUpdate_clicked();
    void on_pushButtonAdd_clicked();
    void on_pushButtonDelete_clicked();
    void on_pushButtonCancel_clicked();
    void	SlotSelectLibFolder(int LibFolderID ,QString FolderName);
    void on_pushButtonPickup_clicked();
    void on_pushButtonPushBack_clicked();
    void on_toolButtonSide4_clicked();

private:
    Ui::LibraryUsageDialog *ui;
    LibFolderForm		*pLibFolderForm;
    AlgorithmLibraryListContainer	LibIDList;
    AlgorithmLibraryListContainer	LibIDListUsage;

    void    ShowList(LibraryUsageContainer &Container);
    void    ShowUsageLibList(void);
};

#endif // LIBRARYUSAGEDIALOG_H
