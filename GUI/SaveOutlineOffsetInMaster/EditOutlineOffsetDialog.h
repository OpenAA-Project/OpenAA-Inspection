#ifndef EDITOUTLINEOFFSETDIALOG_H
#define EDITOUTLINEOFFSETDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class EditOutlineOffsetDialog;
}

class EditOutlineOffsetDialog : public QDialog ,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit EditOutlineOffsetDialog(LayersBase *Base ,QWidget *parent = 0);
    ~EditOutlineOffsetDialog();

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::EditOutlineOffsetDialog *ui;
};

#endif // EDITOUTLINEOFFSETDIALOG_H
