/*
 * Copyright (C) 2020
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

#ifndef SETSTATISTICTHRESHOLDDIALOG_H
#define SETSTATISTICTHRESHOLDDIALOG_H

#include <QDialog>

namespace Ui {
class SetStatisticThresholdDialog;
}

class SetStatisticThresholdDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit SetStatisticThresholdDialog(QWidget *parent = 0);
    ~SetStatisticThresholdDialog();
    
	double	SigmaH;
	double	SigmaS;
	double	SigmaV;

private slots:
    void on_pushButtonSet_clicked();
    void on_pushButtonCancel_clicked();
    void on_pushButtonPanelH_clicked();
    void on_pushButtonPanelS_clicked();
    void on_pushButtonPanelV_clicked();

private:
    Ui::SetStatisticThresholdDialog *ui;
};

#endif // SETSTATISTICTHRESHOLDDIALOG_H