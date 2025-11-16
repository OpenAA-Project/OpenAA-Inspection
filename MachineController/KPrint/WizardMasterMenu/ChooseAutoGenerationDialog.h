#ifndef CHOOSEAUTOGENERATIONDIALOG_H
#define CHOOSEAUTOGENERATIONDIALOG_H

#include <QDialog>

namespace Ui {
class ChooseAutoGenerationDialog;
}

class ChooseAutoGenerationDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ChooseAutoGenerationDialog(QWidget *parent = 0);
    ~ChooseAutoGenerationDialog();
    
private slots:
    void on_PushButtonAutoGenerate_clicked();
    void on_PushButtonNext_clicked();

private:
    Ui::ChooseAutoGenerationDialog *ui;
};

#endif // CHOOSEAUTOGENERATIONDIALOG_H
