#ifndef CREATETHRESHOLDLEVELDIALOG_H
#define CREATETHRESHOLDLEVELDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include <QDrag>
#include <QMimeData>
#include <QModelIndex>
#include <QTreeWidgetItem>

namespace Ui {
class CreateThresholdLevelDialog;
}

class LevelFolder;

class CreateThresholdLevelDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

    int SourceLevelID;
public:
    explicit CreateThresholdLevelDialog(LayersBase *Base ,QWidget *parent = 0);
    ~CreateThresholdLevelDialog();
    
private slots:
    void on_treeWidgetLevel_itemSelectionChanged();
    void on_pushButtonCreateNew_clicked();
    void on_pushButtonUpdate_clicked();
    void on_pushButtonDelete_clicked();
    void on_pushButtonClose_clicked();
    void on_treeWidgetLevel_clicked(const QModelIndex &index);
    void on_pushButtonTopRoot_clicked();
    void on_pushButtonCopy_clicked();
    void on_pushButtonPaste_clicked();

private:
    Ui::CreateThresholdLevelDialog *ui;

    void    ShowTreeGrid(void);
    void    ShowTreeGrid(QTreeWidgetItem *Item,LevelFolder *Parent);
    void    ShowLevelItem(int LevelID);
    void    ShowCurrentParent(void);

    virtual void    dropEvent(QDropEvent *event)    override;
    virtual void resizeEvent(QResizeEvent *event)   override;
    QTreeWidgetItem *GetCurrentItem(void);
};

#endif // CREATETHRESHOLDLEVELDIALOG_H
