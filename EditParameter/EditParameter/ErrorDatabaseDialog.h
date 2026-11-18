#ifndef ERRORDATABASEDIALOG_H
#define ERRORDATABASEDIALOG_H

#include <QDialog>

namespace Ui {
class ErrorDatabaseDialog;
}

class ErrorDatabaseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ErrorDatabaseDialog(QString &RetErr, QStringList &RetDrvList,QWidget *parent = nullptr);
    ~ErrorDatabaseDialog();

private slots:
    void on_pushButtonOK_clicked();

private:
    Ui::ErrorDatabaseDialog *ui;
};

#endif // ERRORDATABASEDIALOG_H
