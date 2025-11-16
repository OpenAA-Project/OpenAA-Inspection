#ifndef EDITEACHPAGELOCALDIALOG_H
#define EDITEACHPAGELOCALDIALOG_H

#include <QDialog>
#include <QListWidgetItem>
#include "XServiceForLayers.h"
#include "WEditParameterTab.h"

namespace Ui {
class EditEachPageLocalDialog;
}

class EditEachPageLocalDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

    int     OldPage;
    WEditParameterTab	*WTab;
public:
    explicit EditEachPageLocalDialog(LayersBase *base ,QWidget *parent = nullptr);
    ~EditEachPageLocalDialog();

private slots:
    void on_ButtonOK_clicked();

    void on_listWidgetPageList_itemSelectionChanged();
    void on_listWidgetPageList_itemClicked(QListWidgetItem *item);

private:
    Ui::EditEachPageLocalDialog *ui;
};

#endif // EDITEACHPAGELOCALDIALOG_H
