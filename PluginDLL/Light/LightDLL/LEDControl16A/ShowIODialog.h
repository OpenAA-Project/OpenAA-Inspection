/*
 * Copyright (C) 2016
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