#ifndef PARAMETERHELPDIALOG_H
#define PARAMETERHELPDIALOG_H

#include <QDialog>

namespace Ui {
class ParameterHelpDialog;
}

class ParameterHelpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ParameterHelpDialog(QWidget *parent = 0);
    ~ParameterHelpDialog();

private:
    Ui::ParameterHelpDialog *ui;
};

#endif // PARAMETERHELPDIALOG_H
