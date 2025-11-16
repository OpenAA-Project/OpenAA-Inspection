#ifndef SETDEFINITIONDIALOG_H
#define SETDEFINITIONDIALOG_H

#include <QDialog>

namespace Ui {
class SetDefinitionDialog;
}

class	LEDControl16DPanel;

class SetDefinitionDialog : public QDialog
{
    Q_OBJECT

	LEDControl16DPanel	*Panel;
public:
    explicit SetDefinitionDialog(LEDControl16DPanel *p,QWidget *parent = 0);
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
