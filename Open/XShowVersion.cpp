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

#include "XShowVersion.h"
#include "Regulus64Version.h"
#define	__cplusplus__strings__
#include <stdio.h>
#include <string.h>
#include <QFileInfo>
#include <QFile>
#include <QTextStream>
#include "XGeneralFuncCore.h"

bool	CheckExeVersion(int argc, char *argv[])
{
	for(int i=1;i<argc;i++){
		if(strcmp(argv[i],/**/"Revision")==0){
			QFileInfo	FInfo(argv[0]);
			QString	VersionFile=FInfo.path()+::GetSeparator()+FInfo.baseName()+QString(/**/".ver");
			QFile	File(VersionFile);
			if(File.open(QIODevice::WriteOnly)==true){
				QTextStream		TextStream(&File);

				TextStream<</**/"FileName=";
				TextStream<<FInfo.fileName();
				TextStream<<"\n";

				TextStream<</**/"RegulusVersion=";
				TextStream<<QString::number(RegulusVersion);
				TextStream<<"\n";
				
				TextStream<</**/"VersionDate=";
				TextStream<<RegulusVersionDate;
				TextStream<<"\n";

				TextStream<</**/"Revision=";
				TextStream<<RegulusVersionRevision;
				TextStream<<"\n";

				return false;
			}
		}
	}
	return true;
}