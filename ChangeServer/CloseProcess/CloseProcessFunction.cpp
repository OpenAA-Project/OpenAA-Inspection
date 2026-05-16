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
#include "Windows.h"
#include <string.h>
#include <time.h>
#include <Psapi.h>
#include <QString>

bool	FindProcess(char *ProcessImageName);

// ウィンドウハンドルを取得しアプリケーションを終了させる。
BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam)
{
    // CreateProcess()で取得したPROCESS_INFORMATION構造体のポインタを取得
    PROCESS_INFORMATION* pi = (PROCESS_INFORMATION*)lParam;

    // ウインドウを作成したプロセスIDを取得。
    DWORD lpdwProcessId = 0;
    ::GetWindowThreadProcessId(hWnd, &lpdwProcessId);

    // CreateProcessで起動したアプリのプロセスIDとメインウィンドウを
    // 作成したプロセスIDが同じ場合、起動したアプリを終了させる。
    if(pi->dwProcessId == lpdwProcessId)
    {
        ::PostMessage(hWnd, WM_CLOSE, 0, 0);
        return FALSE;
    }
    return TRUE;
}

bool	CloseProcessFunction(char *ProcessImageName ,int MaxWaitForTerminte)
{
	DWORD allProc[1024];
	DWORD cbNeeded;
	int nProc;
	bool	ClosedMode=false;

	// PID一覧を取得
	if (!::EnumProcesses(allProc, sizeof(allProc), &cbNeeded)) {
		return false;
	}

	nProc = cbNeeded / sizeof(DWORD);

	for (int i = 0; i < nProc; i++) {

		HANDLE hProcess = ::OpenProcess(
			PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_TERMINATE	,
			FALSE, allProc[i]);

		// プロセス名を取得
		if (NULL != hProcess) {
			HMODULE hMod;
			DWORD cbNeeded;

			if (::EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded)) {
				TCHAR procName[MAX_PATH] = TEXT("<unknown>");
				::GetModuleBaseName(hProcess, hMod, procName, sizeof(procName)/sizeof(TCHAR));
				QString	s=QString::fromWCharArray(procName);
				if(s.toLower()==QString(ProcessImageName).toLower()){
//					::TerminateProcess(hProcess,0);

					PROCESS_INFORMATION pi;
					pi.dwProcessId=allProc[i];
					// コールバック関数の呼び出し。
					EnumWindows(EnumWindowsProc, (LPARAM)&pi);
					ClosedMode=true;
				}
			}
	        CloseHandle(hProcess);
		}
    }
	if(ClosedMode==true){
		for(time_t t=time(NULL);time(NULL)-t<=MaxWaitForTerminte;){
			if(FindProcess(ProcessImageName)==false){
				break;
			}
		}
	}
	return true;
}

bool	FindProcess(char *ProcessImageName)
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

		HANDLE hProcess = ::OpenProcess(
			PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_TERMINATE	,
			FALSE, allProc[i]);

		// プロセス名を取得
		if (NULL != hProcess) {
			HMODULE hMod;
			DWORD cbNeeded;

			if (::EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded)) {
				TCHAR procName[MAX_PATH] = TEXT("<unknown>");
				::GetModuleBaseName(hProcess, hMod, procName, sizeof(procName)/sizeof(TCHAR));
				QString	s=QString::fromWCharArray(procName);
				if(s.toLower()==QString(ProcessImageName).toLower()){
					return true;
				}
			}
	        CloseHandle(hProcess);
		}
    }
	return false;
}

#else

#include <QString>
#include <QStringList>
#include <QProcess>

bool	CloseProcessFunction(char *ProcessImageName ,int MaxWaitForTerminte)
{
    // pkill -9 <プロセス名> を実行する
    // -9 は SIGKILL (強制終了) を意味します
    QProcess::execute("pkill", QStringList() << "-9" << QString::fromUtf8(ProcessImageName));
}

#endif
