#ifndef SELECTCHANGEABLEDIALOG_H
#define SELECTCHANGEABLEDIALOG_H

#include <QDialog>


namespace Ui {
class SelectChangeableDialog;
}

class	CameraSharer;

class SelectChangeableDialog : public QDialog
{
    Q_OBJECT

	CameraSharer	*Parent;
public:
    explicit SelectChangeableDialog(CameraSharer *p,QWidget *parent = 0);
    ~SelectChangeableDialog();

private slots:
    void on_pushButtonOK_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::SelectChangeableDialog *ui;
};

#endif // SELECTCHANGEABLEDIALOG_H
