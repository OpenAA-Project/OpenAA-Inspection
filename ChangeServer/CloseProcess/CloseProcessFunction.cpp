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
        return false;
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
			false, allProc[i]);

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
			false, allProc[i]);

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
