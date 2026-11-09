#ifndef PROPERTYEDGEMATCHINGFORM_H
#define PROPERTYEDGEMATCHINGFORM_H

#include <QWidget>
#include <QModelIndex>
#include "XGUIFormBase.h"
#include "EdgeMatchingPropertyForm.h"
#include "ui_EdgeMatchingPropertyForm.h"
#include "WMultiGrid.h"
#include "XPropertyEdgeMatchingPacket.h"
#include "XEdgeMatching.h"
#include "XStandardPropertyForm.h"

namespace Ui {
class EdgeMatchingPropertyForm;
}

class EdgeMatchingPropertyForm : public GUIFormBase, public StandardPropertyForm
{
    Q_OBJECT

public:
    explicit EdgeMatchingPropertyForm(LayersBase *Base, QWidget *parent = nullptr);
    ~EdgeMatchingPropertyForm();

    virtual void TransmitDirectly(GUIDirectMessage *packet) override;
    virtual void BuildForShow(void) override;
    virtual void StartPage(void) override;
    virtual void ShowInEdit(void) override;

private slots:
    void on_toolButtonArea_clicked();
    void on_toolButtonDirection_clicked();
    void on_toolButtonEdge_clicked();
    void on_pushButtonEditLibFolder_clicked();
    void on_tableWidgetLibList_doubleClicked(const QModelIndex &index);
    void on_tableWidgetGeneratedLibList_doubleClicked(const QModelIndex &index);
    void on_pushButtonEditLibrary_clicked();
    void on_tableWidgetItemList_itemSelectionChanged();
    void on_tableWidgetItemList_cellDoubleClicked(int row, int column);
    void on_pushButtonSetFrom_clicked();
    void on_pushButtonGetBack_clicked();
    void on_pushButtonSetFromAll_clicked();
    void on_pushButtonGetBackAll_clicked();

private:
    Ui::EdgeMatchingPropertyForm *ui;

    EdgeMatchingBase *GetEdgeMatchingBase(void);

    virtual void SetLibFolder(int _LibFolderID, const QString &LinFolderName) override;

    AlgorithmLibraryListContainer LibList;
    AlgorithmLibraryListContainer SelectedLibList;
    int LibFolderID;

    AlgorithmLibraryLevelContainer *LLib;
    int LibType;
    
    void ShowLibrary(AlgorithmLibraryLevelContainer &data);
    void GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);
    void ShowLibList(void);
    void ShowSelectedLibList(void);

    EdgeMatchingItemListPack ItemList;
    void ShowItemList(void);
};

#endif // PROPERTYEDGEMATCHINGFORM_H
