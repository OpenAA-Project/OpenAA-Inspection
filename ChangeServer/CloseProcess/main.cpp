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

#include <QtCore/QCoreApplication>
#include <stdio.h>
#include <string.h>
#include "XMacro.h"

void	ShowHelp(void)
{
	printf("");
}

bool	CloseProcessFunction(char *ProcessImageName,int MaxWaitForTerminte);


int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	int	MaxWaitForTerminte=0;

	char ProcessImageName[256];
	for(int i=0;i<argc;i++){
		if(stricmp(argv[i],"/?")==0){
			ShowHelp();
			break;
		}
		else if(stricmp(argv[i],"-?")==0){
			ShowHelp();
			break;
		}
		else if(strnicmp(argv[i],"-W",2)==0){
			char	*fp=argv[i]+2;
			sscanf(fp,"%d",&MaxWaitForTerminte);
		}
		else{
			strcpy(ProcessImageName,argv[i]);
		}
	}
	CloseProcessFunction(ProcessImageName,MaxWaitForTerminte);


	return 0;
}