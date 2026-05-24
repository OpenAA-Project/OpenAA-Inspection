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

#include "ShowStatusComment.h"
#include <QApplication>
#include <QFileInfo>
#include "SingleExecute.h"
#include "XMainGUIFormBase.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QFileInfo	FInfo(argv[0]);
	if(SingleExecute(FInfo.fileName())==false){
		KillDupProcess(FInfo.fileName());
		//return 100;
	}

	ShowStatusComment w;
	w.show();
	return a.exec();
}