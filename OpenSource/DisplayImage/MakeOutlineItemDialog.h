#ifndef MAKEOUTLINEITEMDIALOG_H
#define MAKEOUTLINEITEMDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class MakeOutlineItemDialog;
}

class MakeOutlineItemDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit MakeOutlineItemDialog(LayersBase *Base,QWidget *parent = nullptr);
    ~MakeOutlineItemDialog();

    int OutlineWidth;
private slots:
    void on_pushButtonGenerate_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::MakeOutlineItemDialog *ui;
};

#endif // MAKEOUTLINEITEMDIALOG_H
