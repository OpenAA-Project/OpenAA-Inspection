#ifndef SELECTEXECUTEDIALOG_H
#define SELECTEXECUTEDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class SelectExecuteDialog;
}

class SelectExecuteDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit SelectExecuteDialog(LayersBase *Base ,QWidget *parent = nullptr);
    ~SelectExecuteDialog();

    int ResultCode;
private slots:
    void on_pushButtonSaveNew_clicked();
    void on_pushButtonOverWrite_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SelectExecuteDialog *ui;
};

#endif // SELECTEXECUTEDIALOG_H
