#ifndef SETLINEWIDTHDIALOG_H
#define SETLINEWIDTHDIALOG_H

#include <QDialog>

namespace Ui {
class SetLineWidthDialog;
}

class SetLineWidthDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetLineWidthDialog(double _LineWidth,QWidget *parent = nullptr);
    ~SetLineWidthDialog();

    double	LineWidth;

private slots:
    void on_pushButtonOK_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::SetLineWidthDialog *ui;
};

#endif // SETLINEWIDTHDIALOG_H
