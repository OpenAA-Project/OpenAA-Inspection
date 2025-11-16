#ifndef SETDEFINITIONDIALOG_H
#define SETDEFINITIONDIALOG_H

#include <QDialog>

namespace Ui {
class SetDefinitionDialog;
}

class	LEDControl16EPanel;

class SetDefinitionDialog : public QDialog
{
    Q_OBJECT

	LEDControl16EPanel	*Panel;
public:
    explicit SetDefinitionDialog(LEDControl16EPanel *p,QWidget *parent = 0);
    ~SetDefinitionDialog();

private slots:
    void on_pushButtonSetCount_clicked();
    void on_pushButton_clicked();

    void on_toolButtonTestLED_clicked();

private:
    Ui::SetDefinitionDialog *ui;

	void	ShowTable(void);
};

#endif // SETDEFINITIONDIALOG_H
