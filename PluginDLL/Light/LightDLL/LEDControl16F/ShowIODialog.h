#ifndef SHOWIODIALOG_H
#define SHOWIODIALOG_H

#include <QDialog>
#include <QTimer>

namespace Ui {
class ShowIODialog;
}
class	LEDControl16FPanel;

class ShowIODialog : public QDialog
{
    Q_OBJECT

	LEDControl16FPanel	*Panel;
	QTimer	TM;
public:
    explicit ShowIODialog(LEDControl16FPanel *p,QWidget *parent = 0);
    ~ShowIODialog();

private slots:
    void on_pushButton_clicked();
	void	SlotTimeOut();

private:
    Ui::ShowIODialog *ui;
};

#endif // SHOWIODIALOG_H
