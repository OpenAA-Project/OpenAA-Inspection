#ifndef MANUALINPUTSTEPLINEENHANCERLDIALOG_H
#define MANUALINPUTSTEPLINEENHANCERLDIALOG_H

#include <QDialog>

namespace Ui {
class ManualInputStepLineEnhancerLDialog;
}

class ManualInputStepLineEnhancerLDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ManualInputStepLineEnhancerLDialog(QWidget *parent = 0);
    ~ManualInputStepLineEnhancerLDialog();

private slots:
    void on_tableWidgetLibList_clicked(const QModelIndex &index);

    void on_ButtonOK_clicked();

    void on_ButtonCancel_clicked();

private:
    Ui::ManualInputStepLineEnhancerLDialog *ui;
};

#endif // MANUALINPUTSTEPLINEENHANCERLDIALOG_H
