#include "XForLinux.h"

#ifndef _MSC_VER

#include <unistd.h>
#include <limits.h>
#include <dirent.h>
#include <sys/types.h> // for opendir(), readdir(), closedir()
#include <sys/stat.h> // for stat()

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdarg>
#include <signal.h>
#include "XGeneralFuncCore.h"

#define PROC_DIRECTORY "/proc/"
#define CASE_SENSITIVE    1
#define CASE_INSENSITIVE  0
#define EXACT_MATCH       1
#define INEXACT_MATCH     0

bool	MtGetVolumeInformation(
  QString RootPathName,				// ルートディレクトリ
  QString &RetVolumeNameBuffer,     // ボリューム名バッファ
  int32 &VolumeSerialNumber,		// ボリュームのシリアル番号
  int32 &MaximumComponentLength,	// ファイル名の最大の長さ
  int32 &FileSystemFlags,			// ファイルシステムのオプション
  QString &FileSystemNameBuffer		// ファイルシステム名を格納するバッファ
)
{
	return true;
}


// 仕様はXForWindows.cpp内のコメントに記載
bool	MtShutdownSelfPC( bool BoolForciblyExitsOthers, bool BoolReboot )
{
	return true;
}


void	MtAdjustTime(int hour,int minute ,int second)
{
}

int64	MtGetDiskFreeSpace(char *DriveStr)
{
	return 0;
}

bool	MtGetComputerName(char CName[],int size)
{
	char hostname[HOST_NAME_MAX];
	char username[LOGIN_NAME_MAX];
	gethostname(hostname, HOST_NAME_MAX);
	getlogin_r(username, LOGIN_NAME_MAX);

	strncpy(CName,hostname,size);
	return true;
}

bool	MtGetComputerName(QString &CName)
{
	char hostname[HOST_NAME_MAX];
	char username[LOGIN_NAME_MAX];
	gethostname(hostname, HOST_NAME_MAX);
	getlogin_r(username, LOGIN_NAME_MAX);

	CName=hostname;
	return true;
}

static	int IsNumeric(const char* ccharptr_CharacterList)
{
    for ( ; *ccharptr_CharacterList; ccharptr_CharacterList++)
        if (*ccharptr_CharacterList < '0' || *ccharptr_CharacterList > '9')
            return 0; // false
    return 1; // true
}

bool	GetProcessNames(QStringList &Processes)
{
    char chrarry_CommandLinePath[100]  ;
    char chrarry_NameOfProcess[300]  ;
    char* chrptr_StringToCompare = NULL ;
    pid_t pid_ProcessIdentifier = (pid_t) -1 ;
	int	PidCount=0;
    struct dirent* de_DirEntity = NULL ;
    DIR* dir_proc = NULL ;


    dir_proc = opendir(PROC_DIRECTORY) ;
    if (dir_proc == NULL)
    {
        perror("Couldn't open the " PROC_DIRECTORY " directory") ;
        return false;
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
                if (fd_CmdLineFile){
                    fscanf(fd_CmdLineFile, "%s", chrarry_NameOfProcess) ; // read from /proc/<NR>/cmdline
                    fclose(fd_CmdLineFile);  // close the file prior to exiting the routine

                    if (strrchr(chrarry_NameOfProcess, '/'))
                        chrptr_StringToCompare = strrchr(chrarry_NameOfProcess, '/') +1 ;
                    else
                        chrptr_StringToCompare = chrarry_NameOfProcess ;

                    //printf("Process name: %s\n", chrarry_NameOfProcess);
                    //printf("Pure Process name: %s\n", chrptr_StringToCompare );

                    pid_ProcessIdentifier = (pid_t) atoi(de_DirEntity->d_name);
                    closedir(dir_proc) ;

					Processes.append(chrptr_StringToCompare);
                }
            }
        }
    }
    closedir(dir_proc) ;

	return true;
}

bool	MTCopyFile(const QString &SourceFileName ,const QString &DestFileName ,bool failIfExist)
{
}
DWORD	MtGetCurrentProcessId(void)
{
	pid_t pid=getpid();
	return (DWORD)pid;
}
bool	KillProcess(DWORD dwProcessId, unsigned int uExitCode)
{
	kill(dwProcessId,0);
	return true;
}
void	KillPreviousDupProcess(void)
{
}
void	KillOtherProcesses(const QString &ProcessName)
{
}

int		MtEnumProcess(DWORD ProcessID[], int MaxCountOfProcessID)
{
    char chrarry_CommandLinePath[100]  ;
    char chrarry_NameOfProcess[300]  ;
    char* chrptr_StringToCompare = NULL ;
    pid_t pid_ProcessIdentifier = (pid_t) -1 ;
	int	PidCount=0;
    struct dirent* de_DirEntity = NULL ;
    DIR* dir_proc = NULL ;


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

					pid_ProcessIdentifier = (pid_t) atoi(de_DirEntity->d_name) ;
					closedir(dir_proc) ;
					if(PidCount<MaxCountOfProcessID){
						ProcessID[PidCount]=pid_ProcessIdentifier;
						PidCount++;
					}
					else{
						break;
                    }
                }
            }
        }
    }
    closedir(dir_proc) ;
	return PidCount;
}
bool	GetProcessName(int ProcessID ,QString &ProcessName)
{
	return true;
}

bool	GetWindowPosition(int ProcessID ,QRect &rect)
{
	return true;
}
bool	SetWindowPosition(int ProcessID ,QRect &rect)
{
	return true;
}
bool	SetWindowCmdShow(int ProcessID ,int nCmdShow)
{
	return true;
}
#endif