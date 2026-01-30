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

#ifndef OTHERSDIALOG_H
#define OTHERSDIALOG_H

#include <QDialog>
#include <QTimer>
#include "XServiceForLayers.h"
#include "XTypeDef.h"

namespace Ui {
class OthersDialog;
}
class	CartonMenuForm;
class	IntegrationShowMemoryForm;

class OthersDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
	friend	class CartonMenuForm;

    CartonMenuForm	*Parent;
	IntegrationShowMemoryForm	*Mem;
	QTimer		TM;
public:
    explicit OthersDialog(LayersBase *Base ,CartonMenuForm *p,QWidget *parent = 0);
    ~OthersDialog();
    
private slots:
    void on_PushButtonLevel_clicked();
    void on_PushButtonCheck_clicked();
    void on_PushButtonSetting_clicked();
    void on_PushButtonNew_clicked();
    void on_PushButtonSwitchImage_clicked();
    void on_PushButtonClose_clicked();
	void	SlotInspectionDone(int SlaveNo,int64 InspectionID ,bool OK);
	void	SlotTimeOut();

private slots:
	void	SlotShowMemory();
    void on_PushButtonSetBeltVelocity_clicked();

private:
    Ui::OthersDialog *ui;

	void	SetRunningGray(void);
};

#endif // OTHERSDIALOG_H