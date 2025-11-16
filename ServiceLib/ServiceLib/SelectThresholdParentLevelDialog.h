#ifndef SELECTTHRESHOLDPARENTLEVELDIALOG_H
#define SELECTTHRESHOLDPARENTLEVELDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>
#include "XServiceForLayers.h"

namespace Ui {
class SelectThresholdParentLevelDialog;
}

class LevelFolder;

class SelectThresholdParentLevelDialog : public QDialog, public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit SelectThresholdParentLevelDialog(LayersBase *Base, QWidget *parent = 0);
    ~SelectThresholdParentLevelDialog();
    
    int SelectedLevelID;
private slots:
    void on_pushButtonSelect_clicked();
    void on_pushButtonCancel_clicked();
    void on_treeWidgetLevel_itemDoubleClicked(QTreeWidgetItem *item, int column);
    void on_treeWidgetLevel_itemSelectionChanged();
    void on_treeWidgetLevel_clicked(const QModelIndex &index);
    void on_pushButtonTopRoot_clicked();

private:
    Ui::SelectThresholdParentLevelDialog *ui;

    void    ShowTreeGrid(void);
    void    ShowTreeGrid(QTreeWidgetItem *Item,LevelFolder *Parent);
    QTreeWidgetItem *GetCurrentItem(void);

    virtual void resizeEvent(QResizeEvent *event)   override;
};

#endif // SELECTTHRESHOLDPARENTLEVELDIALOG_H
