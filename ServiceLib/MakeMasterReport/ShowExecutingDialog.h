/*
 * Copyright (C) 2023
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

#ifndef SHOWEXECUTINGDIALOG_H
#define SHOWEXECUTINGDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XReportStructure.h"

namespace Ui {
    class ShowExecutingDialog;
}

class ParamGlobal;

class ShowExecutingDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

	ThreadReport	RunningThread;
public:
    ParamGlobal     *GlobalParam;
public:
    explicit ShowExecutingDialog(int masterCode
                                ,ParamGlobal *GlobalParam
                                ,LayersBase *Base 
                                ,QWidget *parent = 0);
    ~ShowExecutingDialog();

private slots:
    void on_pushButtonSaveEXCEL_clicked();
    void on_pushButtonClose_clicked();

private:
    Ui::ShowExecutingDialog *ui;
private slots:
	void	SlotStep(QString Msg);
	void	SlotReqLibrary();
	void	SlotFinished();
};

#endif // SHOWEXECUTINGDIALOG_H