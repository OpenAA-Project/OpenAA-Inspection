#ifndef EDITANGLERANGEDIALOG_H
#define EDITANGLERANGEDIALOG_H

#include <QDialog>

namespace Ui {
class EditAngleRangeDialog;
}

class EditAngleRangeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditAngleRangeDialog(QWidget *parent = nullptr);
    ~EditAngleRangeDialog();

	double  RetMinAngle;
	double  RetMaxAngle;

	void    Initial(double MinAngle,double MaxAngle);

private slots:
    void on_pushButtonOK_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::EditAngleRangeDialog *ui;
};

#endif // EDITANGLERANGEDIALOG_H
