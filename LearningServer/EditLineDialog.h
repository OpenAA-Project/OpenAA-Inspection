#ifndef EDITLINEDIALOG_H
#define EDITLINEDIALOG_H

#include <QDialog>

namespace Ui {
class EditLineDialog;
}

class EditLineDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditLineDialog(int SampleType,int Priority,QWidget *parent = nullptr);
    ~EditLineDialog();

    int SampleType;
    int Priority;

private slots:
    void on_horizontalSliderPriority_valueChanged(int value);
    void on_spinBoxPriority_valueChanged(int arg1);
    void on_pushButtonSave_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::EditLineDialog *ui;
};

#endif // EDITLINEDIALOG_H
