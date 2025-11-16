#ifndef POURIMAGEDIALOG_H
#define POURIMAGEDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class PourImageDialog;
}

class PourImageDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit PourImageDialog(LayersBase *Base,QWidget *parent = nullptr);
    ~PourImageDialog();

    int     PickupBrightness;
    int     ExpandedDot;

private slots:
    void on_pushButtonGo_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::PourImageDialog *ui;
};

#endif // POURIMAGEDIALOG_H
