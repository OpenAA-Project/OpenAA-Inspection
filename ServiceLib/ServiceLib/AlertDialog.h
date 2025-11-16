#ifndef ALERTDIALOG_H
#define ALERTDIALOG_H

#include <QDialog>

namespace Ui {
class AlertDialog;
}

class AlertDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit AlertDialog(QWidget *parent = 0);
	AlertDialog(const QString &Msg ,QWidget *parent = 0);
    ~AlertDialog();
    
private slots:
    void on_pushButtonOK_clicked();

private:
    Ui::AlertDialog *ui;
};

#endif // ALERTDIALOG_H
