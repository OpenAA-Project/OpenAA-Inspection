#ifndef LOADTHRESHOLDDIALOG_H
#define LOADTHRESHOLDDIALOG_H

#include <QDialog>

namespace Ui {
class LoadThresholdDialog;
}

class LoadThresholdDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoadThresholdDialog(QWidget *parent = nullptr);
    ~LoadThresholdDialog();

private slots:
    void on_pushButtonSelect_clicked();

    void on_pushButtonClose_clicked();

    void on_tableWidget_itemSelectionChanged();

private:
    Ui::LoadThresholdDialog *ui;
};

#endif // LOADTHRESHOLDDIALOG_H
