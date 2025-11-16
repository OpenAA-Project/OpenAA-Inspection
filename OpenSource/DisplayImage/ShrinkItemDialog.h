#ifndef SHRINKITEMDIALOG_H
#define SHRINKITEMDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class ShrinkItemDialog;
}

class ShrinkItemDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit ShrinkItemDialog(LayersBase *Base,QWidget *parent = 0);
    ~ShrinkItemDialog();
    
	int		ExpandPixels;
    bool    MaskForSameLib;
private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::ShrinkItemDialog *ui;
};

#endif // SHRINKITEMDIALOG_H
