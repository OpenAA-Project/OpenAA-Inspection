#ifndef SETDEFINITIONDIALOG_H
#define SETDEFINITIONDIALOG_H

#include <QDialog>

namespace Ui {
class SetDefinitionDialog;
}

class	LEDControl16BPanel;

class SetDefinitionDialog : public QDialog
{
    Q_OBJECT

	LEDControl16BPanel	*Panel;
public:
    explicit SetDefinitionDialog(LEDControl16BPanel *p,QWidget *parent = 0);
    ~SetDefinitionDialog();

private slots:
    void on_pushButtonSetCount_clicked();

    void on_pushButton_clicked();

private:
    Ui::SetDefinitionDialog *ui;

	void	ShowTable(void);
};

#endif // SETDEFINITIONDIALOG_H
