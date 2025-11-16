#ifndef SAVETHRESHOLDDIALOG_H
#define SAVETHRESHOLDDIALOG_H

#include <QDialog>

namespace Ui {
class SaveThresholdDialog;
}

class SaveThresholdDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SaveThresholdDialog(QWidget *parent = nullptr);
    ~SaveThresholdDialog();

private slots:
    void on_pushButtonCreateNew_clicked();

    void on_pushButtonModify_clicked();

    void on_pushButtonDelete_clicked();

    void on_pushButtonClose_clicked();

    void on_tableWidget_itemSelectionChanged();

private:
    Ui::SaveThresholdDialog *ui;
};

#endif // SAVETHRESHOLDDIALOG_H
