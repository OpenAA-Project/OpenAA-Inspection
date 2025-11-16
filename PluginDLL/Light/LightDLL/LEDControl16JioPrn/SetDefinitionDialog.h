#ifndef SETDEFINITIONDIALOG_H
#define SETDEFINITIONDIALOG_H

#include <QDialog>

namespace Ui {
class SetDefinitionDialog;
}

class	LEDControl16JioPanel;

class SetDefinitionDialog : public QDialog
{
    Q_OBJECT

	LEDControl16JioPanel	*Panel;
public:
    explicit SetDefinitionDialog(LEDControl16JioPanel *p,QWidget *parent = 0);
    ~SetDefinitionDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::SetDefinitionDialog *ui;

	void	ShowTable(void);
};

#endif // SETDEFINITIONDIALOG_H
