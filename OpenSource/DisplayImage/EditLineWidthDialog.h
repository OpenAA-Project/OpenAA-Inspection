#ifndef EDITLINEWIDTHDIALOG_H
#define EDITLINEWIDTHDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class EditLineWidthDialog;
}

class EditLineWidthDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit EditLineWidthDialog(LayersBase *Base,QWidget *parent = nullptr);
    ~EditLineWidthDialog();

    int LineWidth;

private slots:
    void on_pushButtonOK_clicked();

private:
    Ui::EditLineWidthDialog *ui;
};

#endif // EDITLINEWIDTHDIALOG_H
