#ifndef SHOWIODIALOG_H
#define SHOWIODIALOG_H

#include <QDialog>
#include <QTimer>

namespace Ui {
class ShowIODialog;
}

class	LEDControl16APanel;

class ShowIODialog : public QDialog
{
    Q_OBJECT
	
	LEDControl16APanel	*Panel;
	QTimer	TM;

	int	CurrentBoard;
	int	CurrentADNumber;

public:
    explicit ShowIODialog(LEDControl16APanel *p,QWidget *parent = 0);
    ~ShowIODialog();

private slots:
	void	SlotTimeOut();
    void on_comboBoxLineNumber_currentIndexChanged(int index);
    void on_pushButtonReadAD_clicked();
    void on_pushButtonReadInput_clicked();
    void on_toolButtonTestLED_clicked();

private:
    Ui::ShowIODialog *ui;

	void	ShowData(void);
};

#endif // SHOWIODIALOG_H
