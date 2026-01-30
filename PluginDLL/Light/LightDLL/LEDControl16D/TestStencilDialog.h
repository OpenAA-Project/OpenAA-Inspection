/*
 * Copyright (C) 2022
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

#ifndef TESTSTENCILDIALOG_H
#define TESTSTENCILDIALOG_H

#include <QDialog>

namespace Ui {
class TestStencilDialog;
}
class	LEDControl16DPanel;

class TestStencilDialog : public QDialog
{
    Q_OBJECT

	LEDControl16DPanel	*Panel;
	int				LastUnit;
	int				LastBoard;
public:
    explicit TestStencilDialog(LEDControl16DPanel *p,QWidget *parent = 0);
    ~TestStencilDialog();

private slots:
    void on_pushButtonOK_clicked();
    void on_toolButtonRelay_clicked();
    void on_pushButtonReqCameraResolution_clicked();
    void on_pushButtonSetCameraResolution_clicked();
    void on_pushButtonReqMotorCounter_clicked();
    void on_pushButtonReqEnableComparator_clicked();
    void on_pushButtonSetEnableComparator_clicked();
    void on_spinBoxUnitNo_valueChanged(int arg1);
    void on_spinBoxBoardNo_valueChanged(int arg1);
    void on_pushButtonAllOff_clicked();
    void on_pushButtonCalc_clicked();
    void on_pushButtonSetMotorCounter_clicked();

private:
    Ui::TestStencilDialog *ui;

	virtual	void	showEvent (QShowEvent * event)		override;
	virtual	void 	closeEvent ( QCloseEvent * event )	override;
};

#endif // TESTSTENCILDIALOG_H