#ifndef ALGORITHMPARAMETERDIALOG_H
#define ALGORITHMPARAMETERDIALOG_H

#include <QDialog>

namespace Ui {
class AlgorithmParameterDialog;
}

class AlgorithmParameterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AlgorithmParameterDialog(QWidget *parent = 0);
    ~AlgorithmParameterDialog();

private:
    Ui::AlgorithmParameterDialog *ui;
};

#endif // ALGORITHMPARAMETERDIALOG_H
