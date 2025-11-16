#ifndef SELECTLIBRARYINLISTDIALOG_H
#define SELECTLIBRARYINLISTDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XIntClass.h"

namespace Ui {
class SelectLibraryInListDialog;
}

class SelectLibraryInListDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

    int     LibType;
    IntList LibList;
public:
    explicit SelectLibraryInListDialog(int libType ,IntList &LibList
                                        ,LayersBase *Base,QWidget *parent = nullptr);
    ~SelectLibraryInListDialog();

    int     SelectedLibID;

private slots:
    void on_pushButtonSelect_clicked();
    void on_pushButtonCancel_clicked();
    void on_tableWidget_doubleClicked(const QModelIndex &index);

private:
    Ui::SelectLibraryInListDialog *ui;
};

#endif // SELECTLIBRARYINLISTDIALOG_H
