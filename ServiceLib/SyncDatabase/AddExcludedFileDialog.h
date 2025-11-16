#ifndef ADDEXCLUDEDFILEDIALOG_H
#define ADDEXCLUDEDFILEDIALOG_H

#include <QDialog>

namespace Ui {
class AddExcludedFileDialog;
}

class AddExcludedFileDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit AddExcludedFileDialog(QWidget *parent = 0);
    ~AddExcludedFileDialog();
    QString	TableName;
private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::AddExcludedFileDialog *ui;
};

#endif // ADDEXCLUDEDFILEDIALOG_H
