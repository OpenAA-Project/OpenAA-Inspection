#ifndef CHOICEPHASEDIALOG_H
#define CHOICEPHASEDIALOG_H

#include <QDialog>
#include<XDataInLayer.h>

namespace Ui {
class ChoicePhaseDialog;
}

class ChosenPhase{
	int PhaseNumber;
public:
	ChosenPhase(int phase){PhaseNumber = phase;}
	int getPhaseNumber(void){ return PhaseNumber;}
	void setPhaseNumber(int phase){ PhaseNumber = phase;}
};

class ChoicePhaseDialog : public QDialog
{
    Q_OBJECT
    
public:
    //explicit ChoicePhaseDialog(QWidget *parent = 0);
	explicit ChoicePhaseDialog(ChosenPhase *selectedPhase,LayersBase *LBase = 0,QWidget *parent = 0);
    ~ChoicePhaseDialog();
	bool	isQuit(){ return _isQuit;}
private slots:
    void on_pbFront_clicked();
    void on_pbBack_clicked();
    void on_pbClose_clicked();

private:
    Ui::ChoicePhaseDialog *ui;
	bool	_isQuit;
	LayersBase *_LBase;
	ChosenPhase *_chosenPhase;
};

#endif // CHOICEPHASEDIALOG_H
