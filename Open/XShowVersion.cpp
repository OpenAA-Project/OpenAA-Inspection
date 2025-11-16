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
