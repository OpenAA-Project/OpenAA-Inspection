#ifndef SELECTCOLORDIALOG_H
#define SELECTCOLORDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class SelectColorDialog;
}

class SelectColorDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit SelectColorDialog(LayersBase *base,QWidget *parent = 0);
    ~SelectColorDialog();

    QColor	Color;

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();
    void on_pushButtonColor_clicked();

private:
    Ui::SelectColorDialog *ui;
};

#endif // SELECTCOLORDIALOG_H
