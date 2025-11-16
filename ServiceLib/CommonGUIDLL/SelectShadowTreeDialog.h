#ifndef SELECTSHADOWTREEDIALOG_H
#define SELECTSHADOWTREEDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>
#include "XServiceForLayers.h"

namespace Ui {
class SelectShadowTreeDialog;
}
class	ShadowTree;
class	LayersBase;

class SelectShadowTreeDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit SelectShadowTreeDialog(LayersBase *pbase ,QWidget *parent = nullptr);
    ~SelectShadowTreeDialog();

    void    Initial(int ShadowLevel,int ShadowNumber);

    ShadowTree  *ShadowTreePoint;
private slots:
    void on_treeWidgetShadowTree_itemSelectionChanged();
    void on_treeWidgetShadowTree_itemDoubleClicked(QTreeWidgetItem *item, int column);
    void on_pushButtonSelect_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SelectShadowTreeDialog *ui;

    void    ShowTree(void);
    void    AddShowTree(QTreeWidgetItem *ParentW,LayersBase *ParentBase);
    virtual void resizeEvent(QResizeEvent *)    override;
};

#endif // SELECTSHADOWTREEDIALOG_H
