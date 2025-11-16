#ifndef ERRORMESSAGEDIALOG_H
#define ERRORMESSAGEDIALOG_H

#include <QDialog>
#include "XDataInLayer.h"

namespace Ui {
class ErrorMessageDialog;
}

class ErrorMessageDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ErrorMessageDialog(NPListPack<ErrorInfoList> &Errors ,QWidget *parent = 0);
    ~ErrorMessageDialog();
    
private slots:
    void on_pushButtonOK_clicked();

private:
    Ui::ErrorMessageDialog *ui;
};

#endif // ERRORMESSAGEDIALOG_H
