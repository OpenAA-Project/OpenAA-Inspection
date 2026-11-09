#ifndef EDGEMATCHINGLIBRARYDIALOG_H
#define EDGEMATCHINGLIBRARYDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include <QTableWidget>
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include "XDataAlgorithm.h"
#include "XEdgeMatching.h" // EdgeMatching用のベースヘッダ（想定）
#include "XEdgeMatchingLibrary.h"

namespace Ui {
class EdgeMatchingLibraryDialog;
}

class GeneralLibFolderForm;
class AlgorithmLibraryLevelContainer;
class EdgeMatchingBase;

class EdgeMatchingLibraryDialog : public QDialog, public ServiceForLayers
{
    Q_OBJECT

public:
    explicit EdgeMatchingLibraryDialog(LayersBase *Base, QWidget *parent = nullptr);
    ~EdgeMatchingLibraryDialog();

    void Initial(AlgorithmBase *InstBase);

private slots:
    void on_tableWidgetLibList_itemSelectionChanged();
    void on_ButtonLibNew_clicked();
    void on_ButtonLibDelete_clicked();
    void on_ButtonLibSaveNew_clicked();
    void on_ButtonLibSave_clicked();
    void on_pushButtonClose_clicked();
    
    void SlotSelectLibFolder(int libFolderID, QString FolderName);

private:
    Ui::EdgeMatchingLibraryDialog *ui;

    GeneralLibFolderForm *pLibFolderForm;

    int LibFolderID;
    AlgorithmLibraryLevelContainer *LLib;
    int LibType;
    
    void ShowLibrary(AlgorithmLibraryLevelContainer &data);
    void GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);

    AlgorithmLibraryListContainer LibIDList;
    AlgorithmLibraryListContainer LibList;

    EdgeMatchingBase *GetEdgeMatchingBase(void);
};

#endif // EDGEMATCHINGLIBRARYDIALOG_H