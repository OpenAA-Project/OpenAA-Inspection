/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\SingleExecute.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "SingleExecute.h"
#include <QDebug>
#include <QDir>

#ifdef _MSC_VER
#include <windows.h>
#include <psapi.h>

bool SingleExecute(const QString &exeName)
{
	DWORD ProcessIDs[1000];
	DWORD ProcessNum;
	HMODULE Modules[1000];
	DWORD ModuleNum;
	wchar_t FileName[1000];
	DWORD RetSize;
	DWORD i, j;
	HANDLE hProcess;
	BOOL bResult;

	int Cnt=0;

	QString ProcFileName;

	/* プロセスの一覧と数を取得 */
	EnumProcesses(ProcessIDs, sizeof(ProcessIDs), &RetSize);
	ProcessNum = RetSize / sizeof(DWORD);

	for(i=0; i<ProcessNum; i++)
	{
		hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, false, ProcessIDs[i]);

		if(hProcess == NULL)
		{
			printf("\tオープン失敗.\n");
		}
		else{
			/* プロセス中のモジュールの一覧を取得 */
			bResult = ::EnumProcessModules(hProcess, Modules, sizeof(Modules), &RetSize);
			if(bResult) {
				ModuleNum = RetSize / sizeof(HMODULE);

				/* 各モジュールのファイル名を表示 */
				for(j=0; j<ModuleNum; j++) {
					::GetModuleFileNameEx(hProcess, Modules[j], FileName, 1000);
					//if(FileName[0]=='c' || FileName[0]=='C'){
					ProcFileName = QString::fromWCharArray(FileName);
					int sepIndex = ProcFileName.lastIndexOf(QDir::separator());
					if(sepIndex!=-1 && sepIndex+1 < ProcFileName.size()){
						ProcFileName = ProcFileName.mid(sepIndex+1);
					}
					if(exeName==ProcFileName/*wcsstr(FileName,ExeFileName)!=NULL*/){
						if(Cnt > 0){
							return false;
						}
						Cnt++;
					}
					//}
				}
			}
			CloseHandle(hProcess);
		}
	}
    return true;
}

bool KillDupProcess(const QString &exeName)
{
	DWORD ProcessIDs[1000];
	DWORD ProcessNum;
	HMODULE Modules[1000];
	DWORD ModuleNum;
	DWORD RetSize;
	DWORD i, j;
	HANDLE hProcess;
	BOOL bResult;
	wchar_t ExeFileName[1000];

	wcscpy(ExeFileName,exeName.toStdWString().c_str());


	/* プロセスの一覧と数を取得 */
	EnumProcesses(ProcessIDs, sizeof(ProcessIDs), &RetSize);
	ProcessNum = RetSize / sizeof(DWORD);

	for(i=0; i<ProcessNum; i++)
	{
		if(GetCurrentProcessId()==ProcessIDs[i]){
			continue;
		}
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, ProcessIDs[i]);

		if(hProcess == NULL)
		{
			printf("\tオープン失敗.\n");
		}
		else{
			/* プロセス中のモジュールの一覧を取得 */
			bResult = ::EnumProcessModules(hProcess, Modules, sizeof(Modules), &RetSize);
			if(bResult) {
				ModuleNum = RetSize / sizeof(HMODULE);

				/* 各モジュールのファイル名を表示 */
				for(j=0; j<ModuleNum; j++) {
					wchar_t FileName[1000];
					//LPSTR	FileName[1000];

					::GetModuleFileNameEx(hProcess, Modules[j], FileName, 1000);
					//if(FileName[0]=='c' || FileName[0]=='C'){
					if(wcsstr(FileName,ExeFileName)!=NULL){
						::TerminateProcess(hProcess,0);
					}
					//}
				}
			}
			CloseHandle(hProcess);
		}
	}
    return true;
}
#else


#include <unistd.h>
#include <dirent.h>
#include <sys/types.h> // for opendir(), readdir(), closedir()
#include <sys/stat.h> // for stat()

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdarg>
#include <signal.h>
#include "XGeneralFunc.h"

#define PROC_DIRECTORY "/proc/"
#define CASE_SENSITIVE    1
#define CASE_INSENSITIVE  0
#define EXACT_MATCH       1
#define INEXACT_MATCH     0


static	int IsNumeric(const char* ccharptr_CharacterList)
{
    for ( ; *ccharptr_CharacterList; ccharptr_CharacterList++)
        if (*ccharptr_CharacterList < '0' || *ccharptr_CharacterList > '9')
            return 0; // false
    return 1; // true
}


static	int strcmp_Wrapper(const char *s1, const char *s2, int intCaseSensitive)
{
    if (intCaseSensitive)
        return !strcmp(s1, s2);
    else
        return !strcasecmp(s1, s2);
}

static	int strstr_Wrapper(const char* haystack, const char* needle, int intCaseSensitive)
{
    if (intCaseSensitive)
        return (strstr(haystack, needle)!=NULL)?(int)true:(int)false;
    else
        return (strcasestr(haystack, needle)!=NULL)?(int)true:(int)false;
}


int GetPIDbyName(const char* cchrptr_ProcessName
				,int intCaseSensitiveness
				,int intExactMatch
				,pid_t PidDim[]
				,int MaxPidCount)
{
    char chrarry_CommandLinePath[100]  ;
    char chrarry_NameOfProcess[300]  ;
    char* chrptr_StringToCompare = NULL ;
    pid_t pid_ProcessIdentifier = (pid_t) -1 ;
	int	PidCount=0;
    struct dirent* de_DirEntity = NULL ;
    DIR* dir_proc = NULL ;

    int (*CompareFunction) (const char*, const char*, int) ;

    if (intExactMatch)
        CompareFunction = &strcmp_Wrapper;
    else
        CompareFunction = &strstr_Wrapper;


    dir_proc = opendir(PROC_DIRECTORY) ;
    if (dir_proc == NULL)
    {
        perror("Couldn't open the " PROC_DIRECTORY " directory") ;
        return 0;
    }

    // Loop while not NULL
    while ( (de_DirEntity = readdir(dir_proc)) )
    {
        if (de_DirEntity->d_type == DT_DIR)
        {
            if (IsNumeric(de_DirEntity->d_name))
            {
                strcpy(chrarry_CommandLinePath, PROC_DIRECTORY) ;
                strcat(chrarry_CommandLinePath, de_DirEntity->d_name) ;
                strcat(chrarry_CommandLinePath, "/cmdline") ;
                FILE* fd_CmdLineFile = fopen (chrarry_CommandLinePath, "rt") ;  // open the file for reading text
                if (fd_CmdLineFile)
                {
                    fscanf(fd_CmdLineFile, "%s", chrarry_NameOfProcess) ; // read from /proc/<NR>/cmdline
                    fclose(fd_CmdLineFile);  // close the file prior to exiting the routine

                    if (strrchr(chrarry_NameOfProcess, '/'))
                        chrptr_StringToCompare = strrchr(chrarry_NameOfProcess, '/') +1 ;
                    else
                        chrptr_StringToCompare = chrarry_NameOfProcess ;

                    //printf("Process name: %s\n", chrarry_NameOfProcess);
                    //printf("Pure Process name: %s\n", chrptr_StringToCompare );

                    if ( CompareFunction(chrptr_StringToCompare, cchrptr_ProcessName, intCaseSensitiveness) )
                    {
                        pid_ProcessIdentifier = (pid_t) atoi(de_DirEntity->d_name) ;
                        closedir(dir_proc) ;
						if(PidCount<MaxPidCount){
							PidDim[PidCount]=pid_ProcessIdentifier;
							PidCount++;
						}
						else{
							break;
						}
                    }
                }
            }
        }
    }
    closedir(dir_proc) ;
    return PidCount ;
}
    
int	GetPIDbyName(const char* cchrptr_ProcessName
				,pid_t PidDim[]
				,int MaxPidCount)
{
	return GetPIDbyName(cchrptr_ProcessName
						,CASE_INSENSITIVE
						,EXACT_MATCH
						,PidDim
						,MaxPidCount);
}

bool SingleExecute(const QString &exeName)
{
	char	exeNameBuff[1024];
	QString2Char(exeName, exeNameBuff, sizeof(exeNameBuff)-1);
	pid_t PidDim[1000];
	int	n=GetPIDbyName(exeNameBuff,PidDim,sizeof(PidDim)/sizeof(PidDim[0]));
	pid_t pid=getpid();
	for(int i=0;i<n;i++){
		if(PidDim[i]==pid){
			return false;
		}
		else{
			return true;
		}
	}
	return false;
}

bool KillDupProcess(const QString &exeName)
{
	char	exeNameBuff[1024];
	QString2Char(exeName, exeNameBuff, sizeof(exeNameBuff)-1);
	pid_t PidDim[1000];
	int	n=GetPIDbyName(exeNameBuff,PidDim,sizeof(PidDim)/sizeof(PidDim[0]));
	pid_t pid=getpid();
	for(int i=0;i<n;i++){
		if(PidDim[i]!=pid){
			kill(PidDim[i],0);
		}
	}
	return true;
}

#endif