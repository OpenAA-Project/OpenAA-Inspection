#ifndef QUESTIONADDDELDIALOG_H
#define QUESTIONADDDELDIALOG_H

#include <QDialog>

namespace Ui {
class QuestionAddDelDialog;
}

class QuestionAddDelDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit QuestionAddDelDialog(QWidget *parent = 0);
    ~QuestionAddDelDialog();
    
private slots:
    void on_toolButtonOK_clicked();
    void on_toolButtonNG_clicked();
    void on_toolButtonCancel_clicked();

private:
    Ui::QuestionAddDelDialog *ui;
};

#endif // QUESTIONADDDELDIALOG_H
