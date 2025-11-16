#ifndef SHOWIOFORM_H
#define SHOWIOFORM_H

#include <QWidget>
#include "XIntClass.h";
#include <QTimer>

namespace Ui {
class ShowIOForm;
}
class	IntegratePlayer;

class ShowIOForm : public QWidget
{
    Q_OBJECT

	IntegratePlayer	*Parent;
	IntList			PIOIDList;
	QTimer	TM;
public:
    explicit ShowIOForm(IntegratePlayer *P,QWidget *parent = 0);
    ~ShowIOForm();

	void	SlotShowIO();
private slots:
    void on_comboBoxBoardNumber_currentIndexChanged(int index);
    void on_chkEchoBack_clicked();

	void	SlotTimeout();
private:
    Ui::ShowIOForm *ui;
};

#endif // SHOWIOFORM_H
