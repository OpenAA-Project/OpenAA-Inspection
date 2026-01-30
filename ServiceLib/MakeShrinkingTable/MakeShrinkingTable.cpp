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

#include "MakeShrinkingTable.h"
#include <omp.h>

MakeShrinkingTable::MakeShrinkingTable(QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	ShrinkingPackContainerInstance.LoadDefault();
}

MakeShrinkingTable::~MakeShrinkingTable()
{

}

void MakeShrinkingTable::on_pushButtonStart_clicked()
{
	int	Numb=ui.spinBoxNumb->value();
	QString	FileName	=ui.lineEditFileName->text();
	ShrinkingPackContainerInstance.Clear();

	#pragma omp parallel
	{
		#pragma omp for
		for(int i=0;i<Numb;i++){
			ShrinkingPackContainerInstance.GetPack(i);
		}
	}
	ShrinkingPackContainerInstance.SaveDefault(FileName);
}