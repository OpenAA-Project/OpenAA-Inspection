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

#include "ProjectPropertyManager.h"
#include <QApplication>
#include "XShowVersion.h"
#include <QDomDocument>
#include <QFile>

bool	Test(void)
{
	QString	FileName="C:/Regulus64v3/ServiceLib/CommonGUIDLL/CommonGUIDLL.vcxproj";
	QFile	ProjectFile(FileName);
	if(ProjectFile.open(QFile::ReadOnly | QFile::Text)==false)
		return false;
	QString	ErrorMsg;
	QDomDocument	ProjectData;
	if(ProjectData.setContent(&ProjectFile,&ErrorMsg)==false)
		return false;
	return true;
}


int main(int argc, char *argv[])
{
	if(CheckExeVersion(argc, argv)==false)
		return 1;

	//Test();

	QApplication a(argc, argv);
	ProjectPropertyManager w;
	w.show();
	return a.exec();
}