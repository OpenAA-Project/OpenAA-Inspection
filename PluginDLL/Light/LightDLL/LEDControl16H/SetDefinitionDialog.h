#ifndef SETDEFINITIONDIALOG_H
#define SETDEFINITIONDIALOG_H

#include <QDialog>

namespace Ui {
class SetDefinitionDialog;
}

class	LEDControl16HPanel;

class SetDefinitionDialog : public QDialog
{
    Q_OBJECT

	LEDControl16HPanel	*Panel;
public:
    explicit SetDefinitionDialog(LEDControl16HPanel *p,QWidget *parent = 0);
    ~SetDefinitionDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::SetDefinitionDialog *ui;

	void	ShowTable(void);
};

#endif // SETDEFINITIONDIALOG_H
