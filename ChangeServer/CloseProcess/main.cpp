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
