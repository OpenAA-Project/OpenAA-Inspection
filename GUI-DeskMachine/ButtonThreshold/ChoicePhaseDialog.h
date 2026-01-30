/*
 * Copyright (C) 2014
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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