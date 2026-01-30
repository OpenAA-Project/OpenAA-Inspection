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

#include "ForceRebooter.h"
#include "ForceRebootSettingDialog.h"

ForceRebooter::ForceRebooter(QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
	,Executer(this)
{
	ui.setupUi(this);

	Executer.StartServer(Executer.Param.OwnPortNumber);
}

ForceRebooter::~ForceRebooter()
{

}

void ForceRebooter::on_pushButtonRebootPrograms_clicked()
{
	Executer.RebootPrograms();
}

void ForceRebooter::on_pushButtonRebootPC_clicked()
{
	Executer.RebootPC();
}

void ForceRebooter::on_pushButtonShutdownPC_clicked()
{
	Executer.ShutdownPC();
}

void ForceRebooter::on_pushButtonSetting_clicked()
{
	ForceRebootSettingDialog	D(&Executer.Param);
	if(D.exec()==(int)true){
		Executer.Param=D.Param;
		Executer.Param.Save();
	}
}