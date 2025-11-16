#ifndef ALERTMESSAGEDIALOG_H
#define ALERTMESSAGEDIALOG_H

#include <QDialog>

namespace Ui {
class AlertMessageDialog;
}

class AlertMessageDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit AlertMessageDialog(QWidget *parent = 0);
    ~AlertMessageDialog();
    
private slots:
    void on_toolButtonYes_clicked();
    void on_toolButtonNo_clicked();

private:
    Ui::AlertMessageDialog *ui;
};

#endif // ALERTMESSAGEDIALOG_H
