#ifndef SELECTDIALOG_H
#define SELECTDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include <QModelIndex>

namespace Ui {
class SelectDialog;
}

class SelectDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit SelectDialog(LayersBase *Base ,QWidget *parent = 0);
    ~SelectDialog();

private slots:
    void on_listWidget_currentRowChanged(int currentRow);
    void on_listWidget_doubleClicked(const QModelIndex &index);

    void on_pushButtonSelect_clicked();

    void on_pushButtonSave_clicked();

    void on_pushButtonSaveAll_clicked();

    void on_pushButtonLoadAppend_clicked();

    void on_pushButtonClear_clicked();

private:
    Ui::SelectDialog *ui;
};

#endif // SELECTDIALOG_H
