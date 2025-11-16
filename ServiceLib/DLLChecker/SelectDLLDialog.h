#ifndef SELECTDLLDIALOG_H
#define SELECTDLLDIALOG_H

#include <QDialog>

namespace Ui {
class SelectDLLDialog;
}

class SelectDLLDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SelectDLLDialog(QWidget *parent = 0);
    ~SelectDLLDialog();

	bool	CheckCameraDLL;
	bool	CheckPIODLL;
	bool	CheckLightDLL;
	bool	CheckSequenceDLL;

private slots:
    void on_pushButtonOK_clicked();

private:
    Ui::SelectDLLDialog *ui;
};

#endif // SELECTDLLDIALOG_H
