/*
 * Copyright (C) 2021
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

#include "ControllerAccessor.h"
#include "XGeneralFunc.h"

ControllerAccessor::ControllerAccessor(QWidget *parent)
    : QMainWindow(parent)
	,Socket(this)
{
    ui.setupUi(this);
}

void ControllerAccessor::on_pushButtonSend_clicked()
{

}

void ControllerAccessor::on_pushButtonClose_clicked()
{

}

void ControllerAccessor::on_pushButtonSignal_clicked()
{

}

void	ControllerAccessor::ShowInfo(void)
{
	ui.doubleSpinBoxMMPerPulse->setValue(CInfo.EncoderMMPerPulse);
}
void	ControllerAccessor::GetInfoFromWindow(void)
{
}

bool	ControllerAccessor::Save(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==true)
		return false;
	if(f->write((const char *)&CInfo,sizeof(CInfo))!=sizeof(CInfo))
		return false;
	return true;
}

bool	ControllerAccessor::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==true)
		return false;
	if(f->read((char *)&CInfo,sizeof(CInfo))!=sizeof(CInfo))
		return false;
	return true;
}
