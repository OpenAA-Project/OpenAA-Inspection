#ifndef SELECTPRIORITYINAREADIALOG_H
#define SELECTPRIORITYINAREADIALOG_H

#include <QDialog>
#include "XAlignmentLarge.h"
#include "XServiceForLayers.h"

namespace Ui {
class SelectPriorityInAreaDialog;
}

class SelectPriorityInAreaDialog : public QDialog,public ServiceForLayers 
{
    Q_OBJECT

public:
    explicit SelectPriorityInAreaDialog(LayersBase *base,QWidget *parent = nullptr);
    ~SelectPriorityInAreaDialog();

    XAlignmentLargeArea::_EnumPriority  Priority;

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SelectPriorityInAreaDialog *ui;
};

#endif // SELECTPRIORITYINAREADIALOG_H
