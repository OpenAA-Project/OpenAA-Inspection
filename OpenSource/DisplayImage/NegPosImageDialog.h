#ifndef NEGPOSIMAGEDIALOG_H
#define NEGPOSIMAGEDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class NegPosImageDialog;
}

class NegPosImageDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit NegPosImageDialog(LayersBase *Base,QWidget *parent = 0);
    ~NegPosImageDialog();

    bool	MasterBuff;
    bool	TargetBuff;

private slots:
    void on_pushButtonConvert_clicked();

private:
    Ui::NegPosImageDialog *ui;
};

#endif // NEGPOSIMAGEDIALOG_H
