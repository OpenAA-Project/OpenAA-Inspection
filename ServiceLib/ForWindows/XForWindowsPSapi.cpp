/*
 * Copyright (C) 2025
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

#ifdef _MSC_VER
#include "swap.h"
#define	_USE_MATH_DEFINES
#include <math.h>
#include "XForWindows.h"
#include "ForWindows.h"
#include "XGeneralFunc.h"
#include "Windows.h"
#include <Psapi.h>

bool	GetProcessNames(QStringList &Processes)
{
	DWORD allProc[1024];
	DWORD cbNeeded;
	int nProc;

	// PID一覧を取得
	if (!::EnumProcesses(allProc, sizeof(allProc), &cbNeeded)) {
		return false;
	}

	nProc = cbNeeded / sizeof(DWORD);

	for (int i = 0; i < nProc; i++) {
		TCHAR procName[MAX_PATH] = TEXT("<unknown>");

		HANDLE hProcess = ::OpenProcess(
			PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
			false, allProc[i]);

		// プロセス名を取得
		if (NULL != hProcess) {
			HMODULE hMod;
			DWORD cbNeeded;

			if (::EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded)) {
				::GetModuleBaseName(hProcess, hMod, procName, sizeof(procName)/sizeof(TCHAR));
				Processes.append(QString::fromWCharArray(procName));
			}
	        CloseHandle(hProcess);
		}
    }
	return true;
}


int	MtEnumProcess(DWORD ProcessID[], int MaxCountOfProcessID)
{
	DWORD cbNeeded;
	if(!EnumProcesses( ProcessID, MaxCountOfProcessID, &cbNeeded )){
		return 0;
	}
	return cbNeeded;
}

bool	GetProcessName(int ProcessID ,QString &ProcessName)
{
    TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");

    // Get a handle to the process.

    HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |
                                   PROCESS_VM_READ,
                                   false, ProcessID );

    // Get the process name.

    if (NULL != hProcess )
    {
        HMODULE hMod;
        DWORD cbNeeded;

        if ( EnumProcessModules( hProcess, &hMod, sizeof(hMod), 
             &cbNeeded) ){
            GetModuleBaseName( hProcess, hMod, szProcessName, 
                               sizeof(szProcessName)/sizeof(TCHAR) );
        }
		else{
			CloseHandle( hProcess );
			return false;
		}
    }
	else{
		return false;
	}
	ProcessName=QString::fromWCharArray(szProcessName);
    // Release the handle to the process.
    CloseHandle( hProcess );
	return true;
}

void	KillPreviousDupProcess(void)
{
	DWORD	ID=MtGetCurrentProcessId();
	QString ProcessName;
	GetProcessName(ID,ProcessName);
	DWORD ProcessID[1000];
	int		N=MtEnumProcess(ProcessID, 1000);
	for(int i=0;i<N;i++){
		QString OtherProcessName;
		GetProcessName(ProcessID[i],OtherProcessName);
		if(OtherProcessName==ProcessName && ProcessID[i]!=ID){
			KillProcess(ProcessID[i], 0);
		}
	}
}

void	KillOtherProcesses(const QString &ProcessName)
{
	DWORD	MyID=MtGetCurrentProcessId();
	DWORD ProcessID[1000];
	int		N=MtEnumProcess(ProcessID, 1000);
	for(int i=0;i<N;i++){
		QString OtherProcessName;
		GetProcessName(ProcessID[i],OtherProcessName);
		if(OtherProcessName==ProcessName && ProcessID[i]!=MyID){
			KillProcess(ProcessID[i], 0);
		}
	}
}

struct	FindWindowProc
{
	int		ProcessID;
	HWND	hWnd[1000];
	int		hWndNumb;
};


static	BOOL  CALLBACK  EnumWndProc( HWND hWnd, LPARAM lParam )
{
	struct	FindWindowProc	*C=(struct	FindWindowProc *)lParam;

	DWORD lpdwProcessId;
	DWORD	ThreadID=GetWindowThreadProcessId(hWnd,             // ウィンドウのハンドル
							&lpdwProcessId  // プロセス ID
							);
	if(lpdwProcessId==C->ProcessID){
		if(C->hWndNumb<sizeof(C->hWnd)/sizeof(C->hWnd[0])){
			C->hWnd		[C->hWndNumb]=hWnd;
			C->hWndNumb++;
		}
	}
	return TRUE;
}
static	BOOL  CALLBACK  EnumChildProc( HWND hWnd, LPARAM lParam )
{
	struct	FindWindowProc	*C=(struct	FindWindowProc *)lParam;

	if(C->hWndNumb<sizeof(C->hWnd)/sizeof(C->hWnd[0])){
		C->hWnd		[C->hWndNumb]=hWnd;
		C->hWndNumb++;
	}
	return TRUE;
}

bool	GetWindowPosition(int ProcessID ,QRect &rect)
{
	struct	FindWindowProc	C;
	C.ProcessID=ProcessID;
	C.hWndNumb=0;
		
	EnumWindows(EnumWndProc,(LPARAM)&C);
	if(C.hWndNumb==0){
		return false;
	}
	int	KNumb=0;
	for(int i=0;i<C.hWndNumb;i++){
		RECT Rect;
		if(GetWindowRect(C.hWnd[i],      // ウィンドウのハンドル
						&Rect   // クライアント座標
						)==false){
			return false;
		}
		WINDOWINFO wi;

		if(GetWindowInfo(C.hWnd[i],&wi)==false)
			return false;
		if((wi.dwWindowStatus & WS_ACTIVECAPTION)==0){
			continue;
		}
		if((wi.dwStyle & WS_VISIBLE)==0)
			continue;
		if(KNumb==0){
			rect.setRect(Rect.left,Rect.top,Rect.right-Rect.left ,Rect.bottom-Rect.top);
			KNumb++;
		}
		else{
			rect.setLeft  (min((long)rect.left(),Rect.left));
			rect.setTop   (min((long)rect.top (),Rect.top));
			rect.setRight (max((long)rect.right(),Rect.right));
			rect.setBottom(max((long)rect.bottom(),Rect.bottom));
			KNumb++;
		}
	}
	if(KNumb!=0)
		return true;
	if(KNumb==0)
		return false;

	return true;
}
bool	SetWindowPosition(int ProcessID ,QRect &rect)
{
	QRect SRect;
	if(GetWindowPosition(ProcessID ,SRect)==false){
		return false;
	}

	int	Dx=rect.left()-SRect.left();
	int	Dy=rect.top() -SRect.top();
	double	Zx=(double)rect.width() /(double)SRect.width();
	double	Zy=(double)rect.height()/(double)SRect.height();

	struct	FindWindowProc	C;
	C.ProcessID=ProcessID;
	C.hWndNumb=0;
		
	EnumWindows(EnumWndProc,(LPARAM)&C);
	if(C.hWndNumb==0){
		return false;
	}
	int	KNumb=0;
	for(int i=0;i<C.hWndNumb;i++){
		RECT Rect;
		if(GetWindowRect(C.hWnd[i],      // ウィンドウのハンドル
						&Rect   // クライアント座標
						)==false){
			return false;
		}
		WINDOWINFO wi;

		if(GetWindowInfo(C.hWnd[i],&wi)==false)
			return false;
		if((wi.dwWindowStatus & WS_ACTIVECAPTION)==0){
			continue;
		}
		if((wi.dwStyle & WS_VISIBLE)==0)
			continue;

		if(MoveWindow(C.hWnd[i]      // ウィンドウのハンドル
					,Rect.left+Dx
					,Rect.top+Dy
					,(Rect.right -Rect.left)*Zx
					,(Rect.bottom-Rect.top )*Zy
					,TRUE
					)==false){
			return false;
		}
		KNumb++;
	}
	if(KNumb==0)
		return false;
	return true;
}

bool	SetWindowCmdShow(int ProcessID ,int nCmdShow)
{
	struct	FindWindowProc	C;
	C.ProcessID=ProcessID;
	C.hWndNumb=0;
		
	EnumWindows(EnumWndProc,(LPARAM)&C);
	if(C.hWndNumb==0){
		return false;
	}
	int	KNumb=0;
	for(int i=0;i<C.hWndNumb;i++){
		RECT Rect;
		if(GetWindowRect(C.hWnd[i],      // ウィンドウのハンドル
						&Rect   // クライアント座標
						)==false){
			return false;
		}
		WINDOWINFO wi;

		if(GetWindowInfo(C.hWnd[i],&wi)==false)
			return false;
		if((wi.dwWindowStatus & WS_ACTIVECAPTION)==0){
			continue;
		}
		if((wi.dwStyle & WS_VISIBLE)==0)
			continue;

		if(ShowWindow(C.hWnd[i]      // ウィンドウのハンドル
					,nCmdShow
					)==false){
			return false;
		}
		KNumb++;
	}
	if(KNumb==0)
		return false;
	return true;
}

bool	SetForegroundOtherWindow(int ProcessID)
{
	struct	FindWindowProc	C;
	C.ProcessID=ProcessID;
	C.hWndNumb=0;
		
	EnumWindows(EnumWndProc,(LPARAM)&C);
	if(C.hWndNumb==0){
		return false;
	}
	int	KNumb=0;
	for(int i=0;i<C.hWndNumb;i++){
		SetForegroundWindow(C.hWnd[i]);
	}
	return true;
}

#else

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
#include <time.h>
#include "XGeneralFuncCore.h"

#include <QString>
#include <QProcess>
#include <QCoreApplication>
#include <QStorageInfo>
#include <QByteArray>
#include <sys/statvfs.h>
#include <cstdint>

int IsNumeric(const char* ccharptr_CharacterList);
#define PROC_DIRECTORY "/proc/"


bool GetProcessNames(QStringList &Processes)
{
    char chrarry_CommandLinePath[100];
    char chrarry_NameOfProcess[300];
    char* chrptr_StringToCompare = NULL;
    struct dirent* de_DirEntity = NULL;
    DIR* dir_proc = NULL;

    dir_proc = opendir(PROC_DIRECTORY);
    if (dir_proc == NULL)
    {
        perror("Couldn't open the " PROC_DIRECTORY " directory");
        return false;
    }

    // Loop while not NULL
    while ( (de_DirEntity = readdir(dir_proc)) )
    {
        if (de_DirEntity->d_type == DT_DIR)
        {
            if (IsNumeric(de_DirEntity->d_name))
            {
                strcpy(chrarry_CommandLinePath, PROC_DIRECTORY);
                strcat(chrarry_CommandLinePath, de_DirEntity->d_name);
                strcat(chrarry_CommandLinePath, "/cmdline");
                
                FILE* fd_CmdLineFile = fopen (chrarry_CommandLinePath, "rt");
                if (fd_CmdLineFile) {
                    // fscanfの戻り値をチェックして警告を回避
                    if (fscanf(fd_CmdLineFile, "%s", chrarry_NameOfProcess) == 1) {
                        if (strrchr(chrarry_NameOfProcess, '/'))
                            chrptr_StringToCompare = strrchr(chrarry_NameOfProcess, '/') + 1;
                        else
                            chrptr_StringToCompare = chrarry_NameOfProcess;

                        Processes.append(chrptr_StringToCompare);
                    }
                    fclose(fd_CmdLineFile);
                    // 【修正】ここに記述されていた closedir(dir_proc); はループ破壊を招くため削除しました
                }
            }
        }
    }
    closedir(dir_proc); // 正しいクローズ位置

    return true;
}

bool	SetForegroundOtherWindow(int ProcessID)
{
    if (ProcessID <= 0) return false;
    std::string command = "xdotool search --all --pid " + std::to_string(ProcessID) + " windowactivate 2>/dev/null";
    int result = std::system(command.c_str());
    return (result == 0);
}

#endif
