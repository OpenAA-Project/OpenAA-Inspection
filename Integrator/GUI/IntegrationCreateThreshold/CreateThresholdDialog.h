#ifndef CREATETHRESHOLDDIALOG_H
#define CREATETHRESHOLDDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include <QModelIndex>
#include <QTreeWidgetItem>
#include "XPasswordQWidget.h"


namespace Ui {
class CreateThresholdDialog;
}
class LevelFolder;

class CreateThresholdDialog : public QDialog,public ServiceForLayers,public PasswordInQWodget
{
    Q_OBJECT
    int SourceLevelID;
public:
    explicit CreateThresholdDialog(LayersBase *Base ,QWidget *parent = 0);
    ~CreateThresholdDialog();
    
private slots:
    void on_pushButtonTopRoot_clicked();
    void on_treeWidgetLevel_itemSelectionChanged();
    void on_pushButtonCreateNew_clicked();
    void on_pushButtonUpdate_clicked();
    void on_pushButtonDelete_clicked();
    void on_pushButtonClose_clicked();
    void on_pushButtonCopy_clicked();
    void on_pushButtonPaste_clicked();

    void on_pushButtonSetCurrent_clicked();

private:
    Ui::CreateThresholdDialog *ui;

    void    ShowTreeGrid(void);
    void    ShowTreeGrid(QTreeWidgetItem *Item,LevelFolder *Parent);
    void    ShowLevelItem(int LevelID);
    void    ShowCurrentParent(void);

    virtual void resizeEvent(QResizeEvent *event)   override;
    QTreeWidgetItem *GetCurrentItem(void);
};

#endif // CREATETHRESHOLDDIALOG_H
