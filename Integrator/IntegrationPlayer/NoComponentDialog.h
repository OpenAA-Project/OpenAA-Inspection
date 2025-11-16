#ifndef NOCOMPONENTDIALOG_H
#define NOCOMPONENTDIALOG_H

#include <QDialog>
#include "XDLLType.h"

namespace Ui {
class NoComponentDialog;
}

class NoComponentDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit NoComponentDialog(ComponentListContainer &NoComponentList,QWidget *parent = 0);
    ~NoComponentDialog();
    
private slots:
    void on_pushButtonOK_clicked();

private:
    Ui::NoComponentDialog *ui;
};

#endif // NOCOMPONENTDIALOG_H
