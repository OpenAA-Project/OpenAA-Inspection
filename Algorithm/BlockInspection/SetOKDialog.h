#ifndef SETOKDIALOG_H
#define SETOKDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class SetOKDialog;
}

class SetOKDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit SetOKDialog(LayersBase *base, QWidget *parent = 0);
    ~SetOKDialog();
    
private slots:
    void on_pushButtonBOKBright_clicked();
    void on_pushButtonBOKSize_clicked();
    void on_pushButtonNOKBright_clicked();
    void on_pushButtonNOKSize_clicked();
    void on_pushButtonOKSearch_clicked();
    void on_pushButtonClose_clicked();

private:
    Ui::SetOKDialog *ui;
};

#endif // SETOKDIALOG_H
