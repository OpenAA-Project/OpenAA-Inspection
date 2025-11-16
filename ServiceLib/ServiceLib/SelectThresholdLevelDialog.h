#ifndef SELECTTHRESHOLDLEVELDIALOG_H
#define SELECTTHRESHOLDLEVELDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>
#include "XServiceForLayers.h"

namespace Ui {
class SelectThresholdLevelDialog;
}
class LevelFolder;

class SelectThresholdLevelDialog : public QDialog, public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit SelectThresholdLevelDialog(LayersBase *Base, QWidget *parent = 0);
    ~SelectThresholdLevelDialog();
    int SelectedLevelID;

private slots:
    void on_treeWidgetLevel_itemSelectionChanged();
    void on_treeWidgetLevel_doubleClicked(const QModelIndex &index);
    void on_pushButtonSelect_clicked();
    void on_pushButtonClose_clicked();

private:
    Ui::SelectThresholdLevelDialog *ui;

    void    ShowTreeGrid(void);
    void    ShowTreeGrid(QTreeWidgetItem *Item,LevelFolder *Parent);
    void    ShowCurrentParent(void);
    void    ShowLevelItem(int LevelID);
    QTreeWidgetItem *GetCurrentItem(void);

    virtual void resizeEvent(QResizeEvent *event)   override;
};

#endif // SELECTTHRESHOLDLEVELDIALOG_H
